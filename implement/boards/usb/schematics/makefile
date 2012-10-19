# Makefile for usb board schematics

# The name of the board
BOARDNAME = usb_board

# Schematic pages in the order you'd like them arranged in the pdf output
PAGES = contents.sch \
	usbio.sch \
	power.sch

# The Guile script to run in order to print schematics
PRINTSCRIPT = print.scm

# The directory for printed schematics
PRINTDIR = ./printable

#------------------------- Done with configuration ---------------------



help:
	@echo 'Makefile for USB board schematics                                     '
	@echo '                                                                      '
	@echo 'Usage:                                                                '
	@echo '   make print           Print schematic pages to PDF                  '
	@echo '                                                                      '

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

