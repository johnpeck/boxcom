# Makefile for usb board layout

# The name of the board
BOARDNAME = usb_board

# The author
FABAUTHOR = John Peck


# --------------------------- Technology settings --------------------------- 


# Default signal trace line width (centimils)
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






#------------------------- Done with configuration ---------------------

SIGSTYLE = Signal,$(SIG_TRACK_WIDTH),$(SIG_VIA_DIAMETER),$(SIG_VIA_DRILL),$(SIG_CLEARANCE)


help:
	@echo 'Makefile for USB board layout                                         '
	@echo '                                                                      '
	@echo 'Usage:                                                                '
	@echo '   make edit            Open layout with PCB                          '
	@echo '                                                                      '



# Edit schematics
# Layout configurations like route styles are 'sticky' -- they can't be changed from the
# command line once they're saved.  Using sed to remove the settings allows the makefile
# to be in control of these configurations.
.PHONY: edit
edit:
	sed -i '/Styles/d' $(BOARDNAME).pcb # Smoke the old route styles
	pcb --route-styles '$(SIGSTYLE):$(SIGSTYLE):$(SIGSTYLE):$(SIGSTYLE)' \
            --fab-author '$(FABAUTHOR)' \
            $(BOARDNAME).pcb &

.PHONY: clean
clean :

