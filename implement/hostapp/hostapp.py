# Boxcom's host application
import Tkinter

import serial # Provides serial class Serial
from serial.tools.list_ports import comports # For getting list of
                                             # serial ports

import time

# Use matplotlib for plotting
import matplotlib
matplotlib.use('TkAgg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.backends.backend_tkagg import NavigationToolbar2TkAgg
# implement the default mpl key bindings
from matplotlib.backend_bases import key_press_handler
from matplotlib.figure import Figure # The Figure class.  Figures are
                                     # the top-level containers for
                                     # all plot objects.
from matplotlib.widgets import Cursor


class FrontEnd():
    def __init__(self,master):
        self.master = master
        master.title("Instrument Panel")
        self.stopped = False
        self.strvar_port = Tkinter.StringVar()

        # Define arrays for the data
        self.timearray = [0]
        self.curarray = [0]

        # Define the period for data collection.  This will be how
        # often the unit is queried.
        self.query_ms = 100 # milliseconds

        
        # Set up radio buttons for the connection selector.  Only add
        # serial ports to the list that respond to the *idn? query
        # with a string containing the correct vendor name.
        self.rad_port = [] # List of radio buttons
        self.serlist = []  # List of valid serial ports (like /dev/ttyUSB0)
        for serport in comports():
            rawstr = ''
            try:
                # Try to open port and configure it
                self.serobj = serial.Serial()
                self.serobj.baudrate = 76800
                self.serobj.timeout = 0.1 # Set timeout to 100ms
                self.serobj.port = serport[0]
                # If the port can be configured, it might be a boxcom.
                # In that case, we have to configure the logger with
                # serinit().
                self.serinit()
                self.serobj.write('*idn?\r')
                rawstr = self.serobj.read(20) # Read a small number of bytes
                self.serobj.close()
            except serial.serialutil.SerialException as error:
                print('Could not open ' + serport[0])
                print error
            # If we get characters back from the *idn? query, it's
            # most likely a boxcom.  See if there's a vendor string in
            # there just to be sure.
            if rawstr.count('johnpeck') == 1:
                self.rad_port.append(Tkinter.Radiobutton(text = serport[0],
                                                         variable = self.strvar_port, 
                                                         value = serport[0]))
                self.serlist.append(serport[0])
                
        # Always add the dummy port to the end of the list.
        self.rad_port.append(Tkinter.Radiobutton(text= 'Dummy',
                                                 variable = self.strvar_port,
                                                 value = 'dummy'))
        self.serlist.append('dummy')

        # Connect to the first serial port in the list.  If there is
        # no valid serial port, connect to the dummy port.
        for serport in self.serlist:
            if serport != 'dummy':
                self.serobj = serial.Serial()
                self.serobj.baudrate = 76800
                self.serobj.timeout = 0.1 # Set timeout to 100ms
                self.serobj.port = serport
                self.strvar_port.set(str(serport))
                self.serinit() 
                break
            else:
                self.strvar_port.set('dummy')

        
        self.but_conn = []
        for indexnum in range(3):
            self.but_conn.append(Tkinter.Button(text = 'Connect ' + str(indexnum)))

        # Set up go/stop buttons
        self.but_stop = Tkinter.Button(text = 'Stop', 
                                       command = self.stopplot)
        self.but_start = Tkinter.Button(text = 'Start',
                                        command = self.startplot)



        # ------------------- Set up the plot -------------------
        # Make a figure object.
        #   figsize = (width, height) with inch dimensions
        self.pfig = Figure(figsize=(5,4),
                           dpi = 100)
        # Adjust the position of subplots in the figure (fractions of
        # the figure dimensions)
        self.pfig.subplots_adjust(bottom = 0.15,
                                  right = 0.9,
                                  top = 0.9,
                                  left = 0.2,
                                  wspace = 0,
                                  hspace = 0)
                                  
        # Add a plot to the figure.  Using subplot automatically
        # calculates position within figure.
        self.pplot = self.pfig.add_subplot(111)

        # Make a canvas for the figure to be painted on
        self.pfig_can = FigureCanvasTkAgg(self.pfig, master = root)
        self.pfig_can.show()
        
        # Add a toolbar for the plot
        self.ptool = NavigationToolbar2TkAgg(self.pfig_can, root)

        # Add a cursor, but make it invisible.  Stopping the plot will
        # make it visible.
        self.pcursor = Cursor(self.pplot, useblit=True, color='red', linewidth=1 )
        self.pcursor.visible = False

        
        # ---------------- Position everything ------------------
        for radiobutton in self.rad_port:
            radiobutton.pack()
        self.but_stop.pack()
        self.but_start.pack()
        self.pfig_can.get_tk_widget().pack()
        
        # Start sampling the inputs.  This method will call itself
        # over and over again to refresh the data.
        self.readinputs()
        

    # -------------------- Member functions ---------------------
    
    def stopplot(self):
        self.stopped = True
        # Only display a cursor if the plot is stopped
        self.pcursor.visible = True

    def startplot(self):
        self.stopped = False
        self.readinputs()
        self.pcursor.visible = False

    def serinit(self):
        self.serobj.open()
        self.serobj.write('loglev 3\r') # Log only errors
        # Clear out the receive queue by reading until getting a timeout
        readstr = 'junk'
        while (len(readstr) != 0):
            self.serobj.write('\r')
            readstr = self.serobj.read(100)

    def readcur(self):
        if self.strvar_port.get() != 'dummy':
            self.serobj.write('curout?\r')
            rawstr = self.serobj.readline()
            curstr = rawstr.split('\r')[0]
            curnum = int(curstr)
            return curnum
        else:
            return 1000

    # Read from the serial object and refresh the display on a
    # schedule
    def readinputs(self):
        # I have to clear the subplot before I can refresh it.  After
        # plotting new data, refresh the canvas with pfig_can.draw()
        self.pplot.clear()

        if len(self.timearray) == 1:
            # If the array length is 1, this is the first time we've
            # read the current.
            self.curarray = [self.readcur()/1e3]
        if len(self.timearray) == 100:
            # If the array length is 100, start over from time = 0.
            self.timearray = [0]
            self.curarray = [self.curarray[-1]]
        # Keep current values in mA, time values in seconds
        self.timearray.append(self.timearray[-1] + self.query_ms/1e3)
        self.curarray.append(self.readcur()/1e3) # Keep currents in mA 

        self.pplot.plot(self.timearray,self.curarray)        
        self.pplot.set_ylabel('Output current (mA)')
        self.pplot.set_xlabel('Time (s)')
        self.pfig_can.draw()
        self.ptool.update()
                
        if self.stopped == False:
            self.master.after(self.query_ms,self.readinputs)

root = Tkinter.Tk()
frontend = FrontEnd(root)
root.mainloop()
