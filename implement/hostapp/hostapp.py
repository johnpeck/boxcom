# Boxcom's host application
import Tkinter
import math # Provides functions for converting angles
import serial
import time
 
# The Meter0 class inherits from the Canvas class
class Meter0(Tkinter.Canvas):
    handle = 0
    def __init__(self,side,fsd,grad_maj,grad_min, units, serobj):
        self.handle = Meter0.handle
        Meter0.handle = Meter0.handle + 1
        self.side = side # Major dimension for the speedometer
        self.fsd = fsd # Full scale deflection
        self.grad_maj = grad_maj # Major grid interval
        self.grad_min = grad_min # Minor grid interval
        self.units = units # Units to write on the dial
        self.serobj = serobj # Serial object associated with readout
        self.reading = 0
        self.orig = self.side/2.0 # Set the origin
        self.R = 0.95 * self.side/2
        self.r = 0.9 * self.side/2
        self.num_r = 0.8 * self.side/2
        # Define the background canvas.  This will ultimately be
        # placed when a member of this class is instantiated
        self.can_meter = Tkinter.Canvas(height = self.side, 
                                        width = self.side,
                                        bg = '#707070')
        
        # Create the circle the meter will move in.
        self.can_meter.create_oval(self.orig - self.R, self.orig - self.R,
                                   self.orig + self.R, self.orig + self.R,
                                   fill = '#ffffff', width = 3)
        # Make tics at the major and minor intervals
        for n in range(0, self.fsd + 1):
            alpha_deg = (225 -n * 270/self.fsd)
            alpha = math.radians(alpha_deg)
            
            # Minor tic marks
            if n%self.grad_min == 0:
                y = self.R * math.sin(alpha)
                x = self.R * math.cos(alpha)
                self.can_meter.create_line(self.orig, self.orig,
                                           self.orig + x, self.orig - y)
            # Major tic marks
            if n%self.grad_maj == 0:
                y = self.R * math.sin(alpha)
                x = self.R * math.cos(alpha)
                self.can_meter.create_line(self.orig, self.orig,
                                           self.orig + x, self.orig - y,
                                           fill = '#ff0000', width = 3)

        # Make a second, slightly smaller circle for the needle to
        # move in
        self.can_meter.create_oval(self.orig - self.r, self.orig - self.r,
                                   self.orig + self.r, self.orig + self.r,
                                   fill = '#ffffff')

        # Put numbers on top of the smaller circle
        for n in range(0, self.fsd + 1):
           alpha_deg = (225 -n * 270.0/self.fsd)
           alpha = math.radians(alpha_deg) 
           if n%self.grad_maj == 0:
               y = self.num_r * math.sin(alpha)
               x = self.num_r * math.cos(alpha)
               self.can_meter.create_text(self.orig + x, self.orig - y,
                                          text = str(n/1000.0), fill = '#000000')
        
        # Write the units near the center of the meter
        self.can_meter.create_text(self.orig, self.orig * 1.5,
                                   text = self.units, fill = '#000000')

    def read(self):
        # If the previous read's spindle and needle exist, we need to
        # delete them before they get redrawn
        try:
            self.can_meter.delete(self.spindle)
            self.can_meter.delete(self.needle)
        except:
            pass
        self.device_up = self.serobj.isOpen()
        if self.device_up == True:
            self.serobj.write('curout?\r')
            readstr = self.serobj.readline()
            self.reading_r = int(readstr.split('\r')[0])
        else:
            self.reading_r = -20

        self.reading = self.reading + (self.reading_r - self.reading)/5.0
        alpha_deg = (225 - self.reading * 270.0/self.fsd)
        alpha = math.radians(alpha_deg)
        beta = math.radians(135)
        ax = self.orig + 0.025 * self.side * math.cos(alpha - beta)
        ay = self.orig - 0.025 * self.side * math.sin(alpha - beta)
        bx = self.orig + 0.025 * self.side * math.cos(alpha + beta)
        by = self.orig - 0.025 * self.side * math.sin(alpha + beta)
        cx = self.orig + self.r * math.cos(alpha)
        cy = self.orig - self.r * math.sin(alpha)
        self.needle = self.can_meter.create_polygon(ax,ay,
                                                    bx,by,
                                                    cx,cy,
                                                    fill = '#FF5616')
        self.spindle = self.can_meter.create_oval(self.orig - 0.01 * self.side,
                                                  self.orig - 0.01 * self.side,
                                                  self.orig + 0.01 * self.side,
                                                  self.orig + 0.01 * self.side,
                                                  fill = '#000000')

class PlotHist(Tkinter.Canvas):
    def __init__(self,xfoot):
        self.xfoot = xfoot # Overall x dimension of plot footprint
        self.yfoot = 0.8 * self.xfoot
        self.xorig = 0.2 * self.xfoot # The x origin coordinate
        self.yorig = 0.8 * self.yfoot # The y origin coordinate
        self.yaxlen = 0.8 * self.yfoot # The y axis length
        self.xaxlen = 0.8 * self.xfoot # The x axis length
        # Define the background canvas
        self.can_plot = Tkinter.Canvas(height = self.yfoot, width = self.xfoot, bg = '#707070')
        # Draw ordinate axis
        self.can_plot.create_line(self.xorig, self.yorig - self.yaxlen,
                                  self.xorig, self.yorig,
                                  self.xorig + self.xaxlen, self.yorig,
                                  width = 2, arrow = Tkinter.BOTH)
                                  
        
    






# Class FrontEnd will contain an instance of Meter0
class FrontEnd():
    def __init__(self,master):
        self.master = master
        master.title("Instrument Panel")
        self.serobj = serial.Serial()
        self.serobj.baudrate = 76800
        self.serobj.port = '/dev/ttyUSB0'
        self.serobj.timeout = 0.1
        self.serinit()
        
        # Set up the meter
        # self.meter1 = Meter0(800,20000,1000,1000,'Current (mA)',self.serobj)
        self.plot1 = PlotHist(500)

        
        # Set up connection button
        self.but_conn = Tkinter.Button(text = 'Connect')

        # Set up port entry box
        self.lab_port = Tkinter.Label(text = 'Serial\nPort')
        self.strvar_port = Tkinter.StringVar()
        self.ent_port = Tkinter.Entry(textvariable = self.strvar_port,
                                      borderwidth = 5)
        self.strvar_port.set(self.serobj.port)
        
        # Position everything
        self.lab_port.grid(row = 1,column = 0)
        self.ent_port.grid(row = 1, column = 1,
                           padx = 3, pady = 3)
        self.but_conn.grid(row = 1, column = 2, 
                           rowspan = 1,
                           padx = 0, pady = 0)

        # self.meter1.can_meter.grid(row = 0, column = 3, rowspan = 2)
        self.plot1.can_plot.grid(row = 0, column = 3)
        self.inputs()
        

    def serinit(self):
        self.serobj.open()
        self.serobj.write('loglev 3\r') # Log only errors
        # Clear out the receive queue by reading until getting a timeout
        readstr = 'junk'
        while (len(readstr) != 0):
            self.serobj.write('\r')
            readstr = self.serobj.read(100)

    # Read from the serial object and refresh the display on a
    # schedule
    def inputs(self):
        # print(self.meter1.serobj.port)
        # try:
        #     self.meter1.serobj.port = '/dev/ttyUSB1'
        # except:
        #     print('No /dev/ttyUSB1')
        #     print(self.meter1.serobj.port)
        # self.meter1.read()
        # self.master.after(100,self.inputs)
        print(self.plot1.xfoot)
        self.master.after(100,self.inputs)

root = Tkinter.Tk()
frontend = FrontEnd(root)
root.mainloop()
