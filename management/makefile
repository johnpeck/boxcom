# makefile for boxcom's planning documents

# The main taskjuggler file (without the tjp)
MAINFILE = boxcom



#------------------------- Done with configuration ---------------------


help:
	@echo 'Makefile for the ec100 manual                                  '
	@echo '                                                               '
	@echo 'Usage:                                                         '
	@echo '   make edit                 Edit the plan with emacs          '
	@echo '   make output               Regenerate the output files       '
	@echo '   make view                 View the project with a browser   '


.PHONY: edit
edit :
	emacs --geometry 180x60 \
              --visit $(MAINFILE).tjp &

.PHONY : output
output :
	tj3 $(MAINFILE).tjp

.PHONY : view
view :
	surf file:///$(shell pwd)/Overview.html &
