# makefile for Boxcom's chassis

# The sticker file (no extension)
STICKER = budbox_back_sticker

# The fill color used for editing the sticker.  This must be set in
# inkscape.  This color will be replaced by another when making the
# final and proof outputs.
# 
# Remember to escape the # character.
STICKER_EDIT_FILL := \#dcdcdc

#------------------------- Done with configuration ---------------------

help:
	@echo "Makefile for Boxcom's chassis                             "
	@echo '                                                          '
	@echo 'Usage:                                                    '
	@echo '   make sticker              Make final backside sticker  '
	@echo '   make sticker_proof        Make sticker for printing    '
	@echo '   make clean                Clean up temporary files     '
	@echo '                                                          '


# Create the final sticker.  The final version will have an all black
# background with white text and lines.
.PHONY: sticker
sticker : $(STICKER).pdf
$(STICKER).pdf : $(STICKER).svg
	$(eval OUTTMP := $(shell mktemp temp.XXXXXX))
	$(eval INTMP := $(shell mktemp temp.XXXXXX))
	cat $< | sed -re 's/#000000/#ffffff/g' > $(OUTTMP).svg
	cp $(OUTTMP).svg $(INTMP).svg
	$(eval OUTTMP := $(shell mktemp temp.XXXXXX))	
	cat $(INTMP).svg | sed -re \
	  $(subst dummy,$(STICKER_EDIT_FILL),'s/dummy/#000000/g') \
	  > $(OUTTMP).svg
	inkscape --export-area-drawing --export-pdf=$@ $(OUTTMP).svg

# Make the sticker proof by translating all white colors to gray
.PHONY: sticker_proof
sticker_proof : $(STICKER)_proof.pdf
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



