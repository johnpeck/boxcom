# testsuite.py
#
# Automated tests for Boxcom
import serial # For opening serial ports
import testlib

def serinit():
    serobj = serial.Serial()
    serobj.baudrate = 76800
    serobj.port = '/dev/ttyUSB0'
    serobj.timeout = 0.1 # Seconds
    return serobj

def connect_test(serobj):
    try:
        serobj.open()
        if serobj.isOpen():
            testlib.passmessage("Opened serial port")
            return True
        else:
            testlib.failmessage("Can't open serial port")
            return False
    except:
        testlib.failmessage("Can't open serial port")
        return False
    

def main():
    fail = False
    serobj = serinit()
    if not fail:
        fail = connect_test(serobj)
    else:
        return
    



if __name__ == '__main__':
    main()
