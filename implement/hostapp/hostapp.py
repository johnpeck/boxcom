# prog_04_16
# Speedometer
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
        self.side = side
        self.fsd = fsd
        self.grad_maj = grad_maj
        self.grad_min = grad_min
        self.units = units
        self.serobj = serobj
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
        # Define the circle the meter will move in.
        self.can_meter.create_oval(self.orig - self.R, self.orig - self.R,
                                   self.orig + self.R, self.orig + self.R,
                                   fill = '#ffffff',
                                   width = 3)
        # fsd = full scale deflection.
        for n in range(0, self.fsd + 1):
            alpha_deg = (225 -n * 270/self.fsd)
            alpha = math.radians(alpha_deg)
            if n%self.grad_min == 0:
                y = self.R * math.sin(alpha)
                x = self.R * math.cos(alpha)
                self.can_meter.create_line(self.orig, self.orig,
                                           self.orig + x, self.orig - y)

            if n%self.grad_maj == 0:
                y = self.R * math.sin(alpha)
                x = self.R * math.cos(alpha)
                self.can_meter.create_line(self.orig, self.orig,
                                           self.orig + x, self.orig - y,
                                           fill = '#ff0000', width = 3)

        # Make a second, slightly smaller circle
        self.can_meter.create_oval(self.orig - self.r, self.orig - self.r,
                                   self.orig + self.r, self.orig + self.r,
                                   fill = '#ffffff')

        # I need a second loop here to let the numbers go on top of
        # the smaller circle
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
        self.meter1 = Meter0(800,20000,1000,1000,'Current (mA)',self.serobj)
        self.meter1.can_meter.grid(row = 0, column = 0, rowspan = 2)
        self.inputs()

    def serinit(self):
        self.serobj.open()
        self.serobj.write('loglev 3\r')
        readstr = 'junk'
        while (len(readstr) != 0):
            self.serobj.write('\r')
            readstr = self.serobj.read(100)
            time.sleep(0.1)
        time.sleep(0.1)
        

    def inputs(self):
        self.meter1.read()
        self.master.after(100,self.inputs)

root = Tkinter.Tk()
frontend = FrontEnd(root)
root.mainloop()
