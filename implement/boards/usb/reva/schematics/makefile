# Makefile for usb board schematics

# The name of the board
BOARDNAME = usb_board

# Schematic pages in the order you'd like them arranged in the pdf output
PAGES = contents.sch \
	usb_input.sch \
	usbio.sch \
	rs232io.sch \
	aux_power.sch \
	current_monitor.sch \
	hardware.sch

# The Guile script to run in order to print schematics
PRINTSCRIPT = print.scm

# The directory for printed schematics
PRINTDIR = ./printable

# The layout directory
LAYOUTDIR = ../layout

# The netlist name
NETLIST = netlist.net

# Path to scripts directory from jpeda
SCRIPTDIR = ./jpeda/scripts

#------------------------- Done with configuration ---------------------



help:
	@echo 'Makefile for USB board schematics                                     '
	@echo '                                                                      '
	@echo 'Usage:                                                                '
	@echo '   make print           Print schematic pages to PDF                  '
	@echo '   make edit            Open all schematic pages with gschem          '
	@echo '   make netlist         Extract netlist from schematics               '
	@echo '   make kit             Run kitgen on the schematic pages             '
	@echo '                                                                      '

# Create netlist
.PHONY: netlist
netlist : $(LAYOUTDIR)/$(NETLIST)

$(LAYOUTDIR)/$(NETLIST) : $(LAYOUTDIR) \
                          $(PAGES)
	gnetlist -g PCB $^ -o $@

# Run kitgen
.PHONY: kit
kit : $(PAGES)
	python $(SCRIPTDIR)/kitgen.py $^



# Define all postscript files
PSPAGES = $(PAGES:%.sch=$(PRINTDIR)/%.ps)

# Define all pdf files
PDFPAGES = $(PAGES:%.sch=$(PRINTDIR)/%.pdf)
PRINTNAME = $(BOARDNAME).pdf

# Print schematics
.PHONY: print
print: $(PRINTDIR) \
       $(PRINTDIR)/$(PRINTNAME)

$(PRINTDIR)/$(PRINTNAME) : $(PDFPAGES)
	pdftk $^ cat output $@

# PDF
$(PRINTDIR)/%.pdf : $(PRINTDIR)/%.ps
	@echo
	@echo 'Converting $< to PDF...'
	ps2pdf $< $@

# Postscript
$(PRINTDIR)/%.ps : %.sch
	@echo
	@echo 'Converting $< to postscript...'
	gschem -p -o $@ -s $(PRINTSCRIPT) $<


# The output directory
$(PRINTDIR):
	mkdir -p $(PRINTDIR)

# The layout directory
$(LAYOUTDIR):
	mkdir -p $(LAYOUTDIR)

# Edit schematics
.PHONY: edit
edit:
	gschem $(PAGES) &

