# makefile for Boxcom's host application

# The top-level Python source file (without the .py)
MAINFILE=hostapp

#------------------------- Done with configuration ---------------------

help:
	@echo "Makefile for Boxcom's host application                    "
	@echo '                                                          '
	@echo 'Usage:                                                    '
	@echo '   make edit                 Edit the app with emacs      '
	@echo '   make run                  Run the app                  '
	@echo '                                                          '


.PHONY: edit
edit :
	emacs --geometry 180x60 \
              --visit $(MAINFILE).py \
              --funcall auto-complete-mode & 

.PHONY: run
run :
	python $(MAINFILE).py
