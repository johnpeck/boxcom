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
    Writes a character to one port, reads it from the other.  Then repeats
    the process in reverse 
    Arguments: portlist -- list of serial objects created with getports()
    Returns: True -- Communication successful in both directions
             False -- Communication failed in one or both directions
"""
def looptest(portlist):
    sendstring = 'some junk that was in my trunk'
    readok = {} # Dictionary of direction : read success
    """ The serial object will accept python's bytes objects, which
        are created from characters with a given encoding. """
    dataflow = ['forward','reverse']
    for direction in dataflow:
        if direction == 'forward':
            writeport = 0
            readport = 1
        else:
            writeport = 1
            readport = 0
        portlist[writeport].write(bytes(sendstring,'ascii'))
        """ Reading from the serial object will give you a bytes object,
            which then has to be decoded. 
        """
        rawread = (portlist[readport].read(len(sendstring)))
        try:
            readstring = rawread.decode('ascii') # Decoding may fail for bad string
            portlist[writeport].flushOutput()
            portlist[readport].flushInput()
            if (sendstring == readstring):
                readok[direction] = True
            else:
                readok[direction] = False
        except:
            portlist[writeport].flushOutput()
            portlist[readport].flushInput()
            return False
    if list(readok.values()).count(False) == 0:
        return True
    else:
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
    # portlist.reverse()
    # testlib.infomessage(portlist[0].name + '  --> ' + portlist[1].name)
    # for rate in stdbauds:
    #     portlist = setbaud(portlist,rate)
    #     time.sleep(1) # Allow 1 second for baud configuration
    #     retval = looptest(portlist)
    #     if retval:
    #         testlib.passmessage(str(int(rate)) + ' baud loopback ok')
    #     else:
    #         testlib.failmessage(str(int(rate)) + ' baud loopback error')


if __name__ == '__main__':
     main()
