# Makefile for usb board layout

# The name of the board
BOARDNAME = usb_board

# The author
FABAUTHOR = John Peck





#------------------------- Done with configuration ---------------------



help:
	@echo 'Makefile for USB board layout                                         '
	@echo '                                                                      '
	@echo 'Usage:                                                                '
	@echo '   make edit            Open layout with PCB                          '
	@echo '                                                                      '



# Edit schematics
.PHONY: edit
edit:
	pcb --fab-author '$(FABAUTHOR)' $(BOARDNAME).pcb &

.PHONY: clean
clean :

