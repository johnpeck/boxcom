# Boxcom's host application
import Tkinter
import serial
import time


import matplotlib
matplotlib.use('TkAgg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.backends.backend_tkagg import NavigationToolbar2TkAgg
# implement the default mpl key bindings
from matplotlib.backend_bases import key_press_handler
from matplotlib.figure import Figure # The Figure class
 


class FrontEnd():
    def __init__(self,master):
        self.master = master
        master.title("Instrument Panel")
        self.serobj = serial.Serial()
        self.serobj.baudrate = 76800
        self.serobj.port = '/dev/ttyUSB0'
        self.serobj.timeout = 0.1 # Set timeout to 100ms
        self.serinit()
        self.stopped = False

        # Define arrays for the data
        self.timearray = [0]
        self.curarray = [0]

        
        # Set up connection button
        self.but_conn = Tkinter.Button(text = 'Connect')

        # Set up go/stop buttons
        self.but_stop = Tkinter.Button(text = 'Stop', 
                                       command = self.stopplot)

        # Set up port entry box
        self.lab_port = Tkinter.Label(text = 'Serial\nPort')
        self.strvar_port = Tkinter.StringVar()
        self.ent_port = Tkinter.Entry(textvariable = self.strvar_port,
                                      borderwidth = 5)
        self.strvar_port.set(self.serobj.port)

        # ------------------- Set up the plot -------------------
        # Make a figure object
        self.pfig = Figure(figsize=(5,4), dpi = 100)
        # Add a plot to the figure
        self.pplot = self.pfig.add_subplot(111)


        # Make a canvas for the figure to be painted on
        self.pfig_can = FigureCanvasTkAgg(self.pfig, master = root)
        self.pfig_can.show()
        
        # Add a toolbar
        self.ptool = NavigationToolbar2TkAgg(self.pfig_can, root)
        
        # Position everything
        self.lab_port.pack()
        self.ent_port.pack()
        self.but_conn.pack()
        self.but_stop.pack()
        self.pfig_can.get_tk_widget().pack()
        
        # Start sampling the inputs.  This method will call itself
        # over and over again to refresh the data.
        self.readinputs()

    def stopplot(self):
        self.stopped = True

        

    def serinit(self):
        self.serobj.open()
        self.serobj.write('loglev 3\r') # Log only errors
        # Clear out the receive queue by reading until getting a timeout
        readstr = 'junk'
        while (len(readstr) != 0):
            self.serobj.write('\r')
            readstr = self.serobj.read(100)

    def readcur(self):
        self.serobj.write('curout?\r')
        rawstr = self.serobj.readline()
        curstr = rawstr.split('\r')[0]
        curnum = int(curstr)
        return curnum

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
            # If the array length is 100, we've acquired for 100ms.
            # Start over from time = 0.
            self.timearray = [0]
            self.curarray = [self.curarray[-1]]
        self.timearray.append(self.timearray[-1] + 100)
        self.curarray.append(self.readcur()/1e3) 

        self.pplot.plot(self.timearray,self.curarray)        
        self.pplot.set_ylabel('Junk')
        self.pfig_can.draw()
        self.ptool.update()
        if self.stopped == False:
            self.master.after(100,self.readinputs)

root = Tkinter.Tk()
frontend = FrontEnd(root)
root.mainloop()
