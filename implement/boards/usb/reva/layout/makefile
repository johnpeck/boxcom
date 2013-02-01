# Makefile for usb board layout

# The name of the board
BOARDNAME = usb_board

# The board's part number (used for purchasing)
PARTNUM = 13-7

# The revision code (used for purchasing)
REVCODE = a

# The submission directory name (can't be named submit)
SUBMITDIR = output

# The printable output directory
PRINTDIR = printable

# The author
FABAUTHOR = John Peck


# --------------------------- Technology settings --------------------------- 


# Default signal trace line width (centimils)
# A 10 mil wide track made in 1 oz copper (1.4 mils) will have 52 milliohms 
# per inch
SIG_TRACK_WIDTH = 1000

# Default signal via drill (centimils)
# 15 mils is standard for Sierra Proto's no-touch products
SIG_VIA_DRILL = 1500

# Default signal via diameter (centimils)
# (30 mil diameter - 15 mil drill)/2 = 7.5 mil copper annulus around vias
SIG_VIA_DIAMETER = 3000

# Default signal track clearance to copper pours (centimils)
# 6 mils is the minimum for Sierra Proto's no-touch products
SIG_CLEARANCE = 1000

# Default power trace line width (centimils)
# A 50 mil wide track made in 1 oz copper (1.4 mils) will have ~10 milliohms 
# per inch
POW_TRACK_WIDTH = 5000

# Default power via drill (centimils)
# The circumference of a hole with a 15 mil diameter is about 50 mils
POW_VIA_DRILL = 1500

# Default power via diameter (centimils)
# (30 mil diameter - 15 mil drill)/2 = 7.5 mil copper annulus around vias
POW_VIA_DIAMETER = 3000

# Default power track clearance to copper pours (centimils)
# 6 mils is the minimum for Sierra Proto's no-touch products
POW_CLEARANCE = 1000

# ------------------------- Layer group settings -----------------------

# When gerber files are created, the inner layers get group number names
# instead of the names in the GUI.  I don't know how the exported layer
# numbers match up to the actual group numbers specified in the software.
# I just open up the gerber file and see which one is which.
GNDGROUP = 3
PWRGROUP = 4



#------------------------- Done with configuration ---------------------

SIGSTYLE = Signal,$(SIG_TRACK_WIDTH),$(SIG_VIA_DIAMETER),$(SIG_VIA_DRILL),$(SIG_CLEARANCE)
POWSTYLE = Power,$(POW_TRACK_WIDTH),$(POW_VIA_DIAMETER),$(POW_VIA_DRILL),$(POW_CLEARANCE)

# The zip file for submission will be called partnum_revcode.zip
# For example, 13_7_a.zip
ZIPNAME = $(subst -,_,$(PARTNUM))_$(REVCODE).zip # Replace dashes with underscores


help:
	@echo 'Makefile for USB board layout                                         '
	@echo '                                                                      '
	@echo 'Usage:                                                                '
	@echo '   make edit            Open layout with PCB                          '
	@echo '   make submit          Export gerbers and create zip file            '
	@echo '   make silkprint       Export silkscreen and board outline to ps     '
	@echo '   make clean           Remove all gerber outputs and temporary files '
	@echo '                                                                      '



# Edit the layout
# Layout configurations like route styles are 'sticky' -- they can't be changed from the
# command line once they're saved.  Using sed to remove the settings allows the makefile
# to be in control of these configurations.
.PHONY: edit
edit:
	sed -i '/Styles/d' $(BOARDNAME).pcb # Smoke the old route styles
	@echo $(# There have to be at least four route styles, or none get processed)
	pcb --route-styles '$(SIGSTYLE):$(POWSTYLE):$(SIGSTYLE):$(SIGSTYLE)' \
            --rat-thickness 1 $(# Here is a comment) \
            --fab-author '$(FABAUTHOR)' \
            $(BOARDNAME).pcb &

.PHONY: silkprint
silkprint: $(PRINTDIR)
	pcb -x ps --psfile $(PRINTDIR)/$(BOARDNAME).ps \
          --media Letter --outline --fill-page --drill-copper \
          --multi-file $(BOARDNAME).pcb
	# Strip out the legend (can't turn it off)
	sed -e '/topsilk/d' $(PRINTDIR)/$(BOARDNAME).topsilk.ps \
          > $(PRINTDIR)/temp1.ps
	sed -e '/$(BOARDNAME)/d' $(PRINTDIR)/temp1.ps \
          > $(PRINTDIR)/temp2.ps
	sed -e '/not to scale/d' $(PRINTDIR)/temp2.ps \
          > $(PRINTDIR)/temp1.ps
	# Create the bounding box -- needed for scaling
	ps2eps -f $(PRINTDIR)/temp1.ps
	# Resize the figure
	gs \
          -o $(PRINTDIR)/resized.eps \
          -sDEVICE=epswrite \
          -dEPSFitPage \
          -dDEVICEWIDTHPOINTS=600 \
          -dDEVICEHEIGHTPOINTS=600 \
          $(PRINTDIR)/temp1.eps
	# Move the figure
	gs \
          -o $(PRINTDIR)/moved.pdf \
          -sPAPERSIZE=letter \
          -sDEVICE=pdfwrite \
          -c "<< /PageOffset [40 102] >> setpagedevice" -f\
          $(PRINTDIR)/resized.eps
	cp $(PRINTDIR)/moved.pdf $(PRINTDIR)/silkprint.pdf
	# Clean up
	rm $(PRINTDIR)/usb_board.*
	rm $(PRINTDIR)/moved.pdf
	rm $(PRINTDIR)/temp*
	rm $(PRINTDIR)/resized.eps



$(PRINTDIR):
	mkdir -p $(PRINTDIR)

.PHONY: submit
submit: $(SUBMITDIR) \
	gerbers \
	checklist.org \
        $(SUBMITDIR)/$(BOARDNAME).top \
	$(SUBMITDIR)/$(BOARDNAME).bottom \
	$(SUBMITDIR)/$(BOARDNAME).ground \
	$(SUBMITDIR)/$(BOARDNAME).power \
	$(SUBMITDIR)/$(BOARDNAME).topsilk \
        $(SUBMITDIR)/$(BOARDNAME).topmask \
        $(SUBMITDIR)/$(BOARDNAME).toppaste \
        $(SUBMITDIR)/$(BOARDNAME).bottommask \
        $(SUBMITDIR)/$(BOARDNAME).drilldraw \
        $(SUBMITDIR)/$(BOARDNAME).outline \
	$(SUBMITDIR)/$(BOARDNAME).plated
	cd $(SUBMITDIR); zip $(ZIPNAME) * -x "./*.zip" # Exclude zip file

# Tell PCB to export gerber files
.PHONY: gerbers
gerbers:
	pcb -x gerber --gerberfile $(BOARDNAME) $(BOARDNAME).pcb

# The top (component) layer artwork
$(SUBMITDIR)/$(BOARDNAME).top:
	cp $(BOARDNAME).top.gbr $@
	@echo -e '\t- [ ] $(notdir $@)' >> checklist.org

# The bottom (solder) layer artwork
$(SUBMITDIR)/$(BOARDNAME).bottom:
	cp $(BOARDNAME).bottom.gbr $@
	@echo -e '\t- [ ] $(notdir $@)' >> checklist.org

# The ground layer artwork
$(SUBMITDIR)/$(BOARDNAME).ground:
	cp $(BOARDNAME).group$(GNDGROUP).gbr $@
	@echo -e '\t- [ ] $(notdir $@)' >> checklist.org

# The power layer artwork
$(SUBMITDIR)/$(BOARDNAME).power:
	cp $(BOARDNAME).group$(PWRGROUP).gbr $@
	@echo -e '\t- [ ] $(notdir $@)' >> checklist.org

# The top layer silkscreen
$(SUBMITDIR)/$(BOARDNAME).topsilk:
	cp $(BOARDNAME).topsilk.gbr $@
	@echo -e '\t- [ ] $(notdir $@)' >> checklist.org

# The top layer soldermask
$(SUBMITDIR)/$(BOARDNAME).topmask:
	cp $(BOARDNAME).topmask.gbr $@
	@echo -e '\t- [ ] $(notdir $@)' >> checklist.org

# The top layer solderpaste
$(SUBMITDIR)/$(BOARDNAME).toppaste:
	cp $(BOARDNAME).toppaste.gbr $@
	@echo -e '\t- [ ] $(notdir $@)' >> checklist.org

# The bottom layer soldermask
$(SUBMITDIR)/$(BOARDNAME).bottommask:
	cp $(BOARDNAME).bottommask.gbr $@
	@echo -e '\t- [ ] $(notdir $@)' >> checklist.org

# The drill drawing
$(SUBMITDIR)/$(BOARDNAME).drilldraw:
	cp $(BOARDNAME).fab.gbr $@
	@echo -e '\t- [ ] $(notdir $@)' >> checklist.org

# The board outline
$(SUBMITDIR)/$(BOARDNAME).outline:
	cp $(BOARDNAME).outline.gbr $@
	@echo -e '\t- [ ] $(notdir $@)' >> checklist.org

# The CNC plated drill file
$(SUBMITDIR)/$(BOARDNAME).plated:
	cp $(BOARDNAME).plated-drill.cnc $@
	@echo -e '\t- [ ] $(notdir $@)' >> checklist.org


# The TODO checklist
checklist.org:
	@echo "Writing checklist.org file"
	@echo "* Gerber files to check in "$(SUBMITDIR) > $@


$(SUBMITDIR):
	mkdir -p $(SUBMITDIR)


.PHONY: clean
clean :
	rm -f *.gbr
	rm -f *.cnc
	rm -f checklist.org
	rm -rf $(SUBMITDIR)

