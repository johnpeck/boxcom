""" tty_loopback.py
    Writes to a specified tty port.  Makes sure the same data
    shows up at a second tty port. """

import serial # For serial communication
import testlib # For my pretty test outputs
import sys
import time

stdbauds = [110, 300, 600, 1200, 2400, 4800, 9600, 19200, 
            38400, 57600, 115200, 230400, 460800, 921600,
            1e6, 2e6, 3e6, 4e6]

""" getports()
    Checks for device nodes /dev/ttyUSB0, dev/ttyUSB1, etc.  If it
    finds them, it creates a serial object to use them.

    Returns: list of serial objects created. """
def getports():
    maxports = 5 # Maximum number of tries
    needports = 2 # How many ports I need
    portlist = []
    for portnum in range(maxports):
        if (len(portlist) == needports):
            break
        try:
            s = serial.Serial('/dev/ttyUSB' + str(portnum),9600,timeout=1)
            testlib.infomessage('Opened port at /dev/ttyUSB' + str(portnum))
            portlist.append(s)
        except:
            testlib.infomessage('Failed to open port at /dev/ttyUSB' + str(portnum))
    return portlist

""" looptest(portlist)
    Writes a character to one port, reads it from the other """
def looptest(portlist):
    sendstring = 'some junk that was in my trunk'
    """ The serial object will accept python's bytes objects, which
        are created from characters with a given encoding. """
    portlist[0].write(bytes(sendstring,'ascii'))
    """ Reading from the serial object will give you a bytes object,
        which then has to be decoded. """
    try:
        readstring = (portlist[1].read(len(sendstring))).decode('ascii')
        portlist[0].flushOutput()
        portlist[1].flushInput()
        if (sendstring == readstring):
            return True
        else:
            return False
    except:
        portlist[0].flushOutput()
        portlist[1].flushInput()
        return False

""" setorder(portlist)
    Tries to make the first port the sender, and the second the receiver. """
def setorder(portlist):
    revlist = []
    portlist = setbaud(portlist,stdbauds[0])
    if looptest(portlist):
        return portlist
    else:
        revlist.append(portlist[1])
        revlist.append(portlist[0])
    if looptest(revlist):
        return revlist
    else:
        testlib.failmessage('No port order seems to work')
        return portlist


""" setbaud(baud rate)
    Configure the baud rate """
def setbaud(portlist,baud):
    for port in portlist:
        port.baudrate = int(baud)
    return portlist


    


def main():
    portlist = getports()
    if (len(portlist) == 2):
        testlib.passmessage('Found two serial ports')
    else:
        # If we don't find two serial ports, this test is over
        testlib.failmessage('Did not find two serial ports')
        return -1
    testlib.infomessage(portlist[0].name + '  --> ' + portlist[1].name)
    for rate in stdbauds:
        portlist = setbaud(portlist,rate)
        time.sleep(1) # Allow 1 second for baud configuration
        retval = looptest(portlist)
        if retval:
            testlib.passmessage(str(int(rate)) + ' baud loopback ok')
        else:
            testlib.failmessage(str(int(rate)) + ' baud loopback error')
    portlist.reverse()
    testlib.infomessage(portlist[0].name + '  --> ' + portlist[1].name)
    for rate in stdbauds:
        portlist = setbaud(portlist,rate)
        time.sleep(1) # Allow 1 second for baud configuration
        retval = looptest(portlist)
        if retval:
            testlib.passmessage(str(int(rate)) + ' baud loopback ok')
        else:
            testlib.failmessage(str(int(rate)) + ' baud loopback error')


if __name__ == '__main__':
     main()
