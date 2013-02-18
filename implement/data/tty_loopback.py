""" tty_loopback.py
    Writes to a specified tty port.  Makes sure the same data
    shows up at a second tty port. """

import serial # For serial communication


""" getports()
    Checks for device nodes /dev/ttyUSB0, dev/ttyUSB1, etc.  If it
    finds them, it creates a serial object to use them.

    Returns: list of serial objects created. """
def getports():
    maxports = 5
    portlist = []
    for portnum in range(maxports):
        try:
            s = serial.Serial('/dev/ttyUSB' + str(portnum),9600,timeout=1)
            print('Opened port at /dev/ttyUSB' + str(portnum))
            portlist.append(s)
        except:
            print('Failed to open port at /dev/ttyUSB' + str(portnum))
    return portlist


def main():
    portlist = getports()


if __name__ == '__main__':
     main()
