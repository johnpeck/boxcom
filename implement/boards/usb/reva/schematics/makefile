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

# Path to footprints
FOOTDIR = ./jpeda/footprints

# The kit number
KITNUM = 15

# The kit quantity
KITQTY = 3

# Path to the file repository for the blog entry
BLOGPATH = /home/john/projects/johnpeck/revb/src/boxcom

#------------------------- Done with configuration ---------------------



help:
	@echo 'Makefile for USB board schematics                                       '
	@echo '                                                                        '
	@echo 'Usage:                                                                  '
	@echo '   make print           Print schematic pages to PDF                    '
	@echo '   make blog            Copy outputs to blog                            '
	@echo '   make edit            Open all schematic pages with gschem            '
	@echo '   make netlist         Extract netlist from schematics                 '
	@echo '   make kit             Run kitgen on the schematic pages               '
	@echo '   make buy             Run buygen on the filled kit                    '
	@echo '   make newbuy          Remove old buygen summary file, run buygen again'
	@echo '   make pcb             Run gsch2pcb on the board                       '
	@echo '                                                                        '


.PHONY: blog
blog: print
	cp $(PRINTDIR)/$(PRINTNAME) $(BLOGPATH)/usb_board_schematics.pdf


# Run gsch2pcb on the board's project file
.PHONY: pcb
pcb :   $(LAYOUTDIR) \
	$(LAYOUTDIR)/$(BOARDNAME).pcb

$(LAYOUTDIR)/$(BOARDNAME).pcb : $(BOARDNAME).pj \
                                $(FOOTDIR)/*.fp
	gsch2pcb $<


# Create project file for gsch2pcb
$(BOARDNAME).pj :
	@echo 'schematics '$(PAGES) > $@
	@echo 'output-name '$(LAYOUTDIR)/$(BOARDNAME) >> $@
	@echo 'elements-dir '$(FOOTDIR) >> $@


# Create netlist
.PHONY: netlist
netlist : $(LAYOUTDIR)/$(NETLIST)
$(LAYOUTDIR)/$(NETLIST) : $(LAYOUTDIR) \
                          $(PAGES)
	gnetlist -g PCB $(PAGES) -o $@

# Run kitgen
.PHONY: kit
kit : $(PAGES) \
      $(SCRIPTDIR)/kitconf.py
	python $(SCRIPTDIR)/kitgen.py $(PAGES)

.PHONY : $(SCRIPTDIR)/kitconf.py
$(SCRIPTDIR)/kitconf.py:
	@echo "# The configuration file for kitgen.py" > $@
	@echo "# The kit number" >> $@
	@echo "kitnum = "$(KITNUM) >> $@
	@echo "# How many boards to kit for" >> $@
	@echo "kitqty = "$(KITQTY) >> $@

# Run buygen after kit has been filled by hand.  If there are repeated
# vendors, run this target again after putting x's in the summary file
# next to vendors you want to disqualify.
.PHONY: buy
buy:
	python $(SCRIPTDIR)/buygen.py

# Disregard the summary file and run buygen again. This is useful when
# new vendors become qualified for parts.
.PHONY: newbuy
newbuy:
	rm -f kit$(KITNUM)/kit$(KITNUM)_summary.dat
	python $(SCRIPTDIR)/buygen.py



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

# Create PDF from postscript
$(PRINTDIR)/%.pdf : $(PRINTDIR)/%.ps
	@echo
	@echo 'Converting $< to PDF...'
	ps2pdf $< $@

# Create postscript schematic pages
$(PRINTDIR)/%.ps : %.sch
	@echo
	@echo 'Converting $< to postscript...'
	gschem -p -o $@ -s $(PRINTSCRIPT) $<


# The output directory for prints
$(PRINTDIR):
	mkdir -p $(PRINTDIR)

# The layout directory
$(LAYOUTDIR):
	mkdir -p $(LAYOUTDIR)

# Edit schematics
.PHONY: edit
edit:
	gschem $(PAGES) &

.PHONY: clean
clean :
	rm -f $(BOARDNAME).pj
