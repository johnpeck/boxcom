# makefile for Boxcom's host application

# The top-level Python source file (without the .py)
MAINFILE=hostapp

#------------------------- Done with configuration ---------------------

help:
	@echo "Makefile for Boxcom's host application                    "
	@echo '                                                          '
	@echo 'Usage:                                                    '
	@echo '   make edit                 Edit the app with emacs      '
	@echo '   make icon_browse          Browse Tango icons           '
	@echo '   make icons                Convert icons for Tkinter    '
	@echo '   make run                  Run the app                  '
	@echo '                                                          '


.PHONY: edit
edit :
	emacs --geometry 180x60 \
              --visit $(MAINFILE).py \
              --funcall auto-complete-mode & 

.PHONY: icon_browse
icon_browse :
	qiv -w 500 /usr/share/icons/Tango/scalable/actions/*.svg &

.PHONY : icons
icons : images/play_icon.gif \
        images/pause_icon.gif


.PHONY: run
run :
	python $(MAINFILE).py


#--------------------------- Create icons ------------------------------
images/play_icon.gif : images/media-playback-start.svg
	inkscape --export-png=$(basename $@).png $<
	convert $(basename $@).png $@

images/pause_icon.gif : images/media-playback-pause.svg
	inkscape --export-png=$(basename $@).png $<
	convert $(basename $@).png $@
