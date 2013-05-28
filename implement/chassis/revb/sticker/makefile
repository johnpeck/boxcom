# makefile for Boxcom's chassis

# The sticker file (no extension)
STICKER = sticker

# The output subdirectory
OUTPUTDIR = output

# The fill color used for editing the sticker.  This must be set in
# inkscape.  This color will be replaced by another when making the
# final and proof outputs.
# 
# Remember to escape the # character.
STICKER_EDIT_FILL := \#dcdcdc

#------------------------- Done with configuration ---------------------

help:
	@echo "Makefile for Boxcom's sticker                             "
	@echo '                                                          '
	@echo 'Usage:                                                    '
	@echo '   make edit                Edit the sticker with inkscape'
	@echo '   make submit              Make final backside sticker   '
	@echo '   make proof               Make sticker for printing     '
	@echo '   make clean               Clean up temporary files      '
	@echo '                                                          '


# Edit the sticker with inkscape
.PHONY : edit
edit :
	inkscape $(STICKER).svg &


# Create the final sticker.  The final version will have an all black
# background with white text and lines.
.PHONY: submit
submit : $(OUTPUTDIR) \
         $(OUTPUTDIR)/$(STICKER).pdf
$(OUTPUTDIR)/$(STICKER).pdf : $(STICKER).svg
	$(eval OUTTMP := $(shell mktemp temp.XXXXXX))
	$(eval INTMP := $(shell mktemp temp.XXXXXX))
	cat $< | sed -re 's/#000000/#ffffff/g' > $(OUTTMP).svg
	cp $(OUTTMP).svg $(INTMP).svg
	$(eval OUTTMP := $(shell mktemp temp.XXXXXX))	
	cat $(INTMP).svg | sed -re \
	  $(subst dummy,$(STICKER_EDIT_FILL),'s/dummy/#000000/g') \
	  > $(OUTTMP).svg
	inkscape --export-area-drawing --export-pdf=$@ $(OUTTMP).svg

$(OUTPUTDIR) :
	mkdir -p $(OUTPUTDIR)

# Make the sticker proof by translating all white colors to gray
.PHONY: proof
proof : $(STICKER)_proof.pdf
$(STICKER)_proof.pdf: $(STICKER).svg
	$(eval OUTTMP := $(shell mktemp temp.XXXXXX))
	# cat $(STICKER).svg | sed -re 's/#ffffff/#dcdcdc/g' > $(OUTTMP).svg
	cat $(STICKER).svg | sed -re \
	  $(subst dummy,$(STICKER_EDIT_FILL),'s/dummy/#dcdcdc/g') \
	  > $(OUTTMP).svg
	inkscape --export-pdf=$@ $(OUTTMP).svg

.PHONY: clean
clean:
	rm temp.*



