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
            serobj.close()
            return False
        else:
            testlib.failmessage("Can't open serial port")
            return True
    except:
        testlib.failmessage("Can't open serial port")
        return True

# setlog()
# 
# Set logging to errors only and clear out the queues
def setlog(serobj):
    serobj.open()
    serobj.write('loglev 3\r') # Log only errors
    clearq(serobj)
    serobj.close()

# clearq()
#
# Just clear out the receive and transmit queues
def clearq(serobj):
    if not serobj.isOpen():
        serobj.open()
    readstr = 'junk'
    while (len(readstr) != 0):
        serobj.write('\r')
        readstr = serobj.read(100)
    serobj.close()


# Test the current period measurement setting
#
# Sends a measurement period in milliseconds, queries the setting.
def curper_test(serobj):
    if not serobj.isOpen():
        serobj.open()
    try:
        # Try to read the original period setting
        serobj.write('curper?\r')
        stockval = int(serobj.read(100))
    except:
        # If we can't read the setting, that's a failure
        testlib.failmessage(
            'Failed to get original curper setting'
        )
        return True
    testval = stockval + 1
    serobj.write('curper {:n}\r'.format(testval)) # Set the current period
    serobj.write('curper?\r') # Query the current period
    readstr = serobj.read(100)
    try:
        if (int(readstr) != testval): # The fail condition
            testlib.failmessage(
                'Failed to set current measurement period using curper'
            )
            return True
        else:
            testlib.passmessage('curper set/query ok')
            # Return the original setting and exit
            serobj.write('curper {:n}\r'.format(stockval))
            return False
    except:
        testlib.failmessage(
            'Failed to set current measurement period using curper'
        )
        return True
        
    

def main():
    fail = False
    serobj = serinit()
    if not fail:
        fail = connect_test(serobj)
    if not fail:
        setlog(serobj) # Turn off most logging
        fail = curper_test(serobj)
    



if __name__ == '__main__':
    main()
