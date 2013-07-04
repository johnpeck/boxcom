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
	@echo '   make shot                 Make a screenshot            '
	@echo '   make bundlepmw            Create Pmw.py                '
	@echo '   make exe                  Create windows executable    '
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
        images/pause_icon.gif \
        images/send_icon.gif


.PHONY: run
run :
	python $(MAINFILE).py &

.PHONY: shot
shot :
	@echo 'Click on plot window with crosshair...'
	import screenshot.png
	@echo 'Wrote screenshot to screenshot.png'

.PHONY: bundlepmw
bundlepmw :
	python bundlepmw.py -noblt -nocolor /usr/lib/python2.7/site-packages/Pmw/Pmw_1_3_3/lib

.PHONY: exe
exe :
	python setup.py build


#--------------------------- Create icons ------------------------------
images/play_icon.gif : images/media-playback-start.svg
	inkscape --export-png=$(basename $@).png $<
	convert $(basename $@).png $@

images/pause_icon.gif : images/media-playback-pause.svg
	inkscape --export-png=$(basename $@).png $<
	convert $(basename $@).png $@

images/send_icon.gif : images/forward.svg
	inkscape --export-png=$(basename $@).png $<
	convert $(basename $@).png $@
