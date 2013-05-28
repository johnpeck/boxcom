# testlib.py
# Some commonly used functions for testing

#-------------------- Begin clint requirements -------------------------
from clint.textui import colored # Colored text output
from clint.textui import indent,puts # Allows indenting text
#-------------------- End clint requirements ---------------------------

#------------------- Begin text formatting requirements ----------------
import textwrap
wrapit = textwrap.TextWrapper()
wrapit.width = 70 # Wrap at 70 columns
#------------------- End text formatting requirements ------------------

LOGFILE = 'testlog.log'

""" failmessage( message string )
    Prints a formatted failure message. """
def failmessage(string):
    print('\r' + '[ ' + colored.red('fail') + ' ] ' + string)
    writelog("[ fail ] " + string)
    
""" passmessage( message string ) 
    Prints a formatted passing message. """
def passmessage(string):
    print('\r' + '[ ' + colored.green('pass') + ' ] ' + string)
    writelog("[ pass ] " + string)

""" advicemessage( message string )
    Prints a formatted message with advice on fixing a problem. """
def advicemessage(string):
    with indent(4, quote=''):
        puts('\r' + colored.yellow(wrapit.fill(string)))

""" infomessage( message string )
    Prints a formatted message for information. """
def infomessage(string):
    print('\r' + '[ ' + colored.cyan('info') + ' ] ' + string)
    writelog("[ info ] " + string)

""" writelog(string)
    Writes string to the log file. """
def writelog(outstr):
    flg = open(LOGFILE,'a') # Open logfile for appending
    flg.write(outstr + '\n')
    flg.close()
