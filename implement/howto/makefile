# makefile for boxcom's howto

# The top-level latex file (without the .tex)
MAINFILE=howto

# Where to put generated output for submission
OUTPUTDIR=./output

# The base name of the user commands index file
USER_CMDS_IDX=user_cmds_index

# The base name of the internal command index file
INTERNAL_CMDS_IDX=internal_cmds_index



#------------------------- Done with configuration ---------------------


help:
	@echo 'Makefile for the ec100 manual                                         '
	@echo '                                                                      '
	@echo 'Usage:                                                                '
	@echo '   make edit                        Edit the manual with emacs        '
	@echo '   make dvi                         Regenerate the dvi file           '
	@echo '   make preview                     Fire up xdvi to view the dvi file '
	@echo '   make howto                       Create the howto pdf in ./output  '
	@echo '   make comcheck                    Check included remote commands    '
	@echo '   make spell                       Check spelling                    '
	@echo '   make clean                       Clean up temporary files          '
	@echo '                                                                      '

.PHONY: edit
edit :
	emacs --geometry 120x40 \
              --visit $(MAINFILE).tex \
              --funcall visual-line-mode &

howto: $(OUTPUTDIR)\
	    $(OUTPUTDIR)/howto.pdf

$(OUTPUTDIR)/howto.pdf: $(OUTPUTDIR)\
			 $(MAINFILE).ps
	ps2pdf $(MAINFILE).ps
	mv $(MAINFILE).pdf $(OUTPUTDIR)/howto.pdf
	@echo "* howto.pdf output to "$(OUTPUTDIR)

pdf: $(MAINFILE).pdf
$(MAINFILE).pdf: $(MAINFILE).ps
	ps2pdf $(MAINFILE).ps

ps: $(MAINFILE).ps
$(MAINFILE).ps: $(MAINFILE).dvi
	dvips -t letter $(MAINFILE).dvi

.PHONY: preview
preview:
	xdvi $(MAINFILE).dvi &

# Make latex_manual.dvi a PHONY target so that latex can be run over and
# over to resove labels.
dvi: $(MAINFILE).dvi
.PHONY: $(MAINFILE).dvi
$(MAINFILE).dvi: 
	latex $(MAINFILE).tex


# The submission directory
$(OUTPUTDIR):
	mkdir -p $(OUTPUTDIR)




# Index ind files are just latex code made from individual idx files
usr_commands.ind: usr_commands.idx
	makeindex usr_commands.idx

# The SRS commands idx file has a cln extension
srs_commands.ind: srs_commands.cln
	makeindex srs_commands.cln

# The index entries for user commands
usr_commands.idx: $(wildcard ./commands/*.tex)\
				  usr_cmds.tex
	latex $(MAINFILE).tex

# LaTeX has a problem with index entries containing escaped characters
# when the entries occur inside macro arguments.  Need to remove all
# spaces in entries with escaped $ signs.
srs_commands.cln: srs_commands.idx
	cat srs_commands.idx | sed -e 's/ //' > srs_commands.cln

# The idx files are generated when the latex file is processed with the 
# multind.sty package included.
srs_commands.idx: $(wildcard ./commands/*.tex)
	latex $(MAINFILE).tex



# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Figure files ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# The big block diagram figure
./figs/full_block_diagram.eps: ./figs/full_block_diagram.fig
	fig2dev -L eps -m 1 $< $@

# The pulsed waveform construction parameter figure
./figs/pulse_params.eps: ./figs/pulse_params.fig
	# ------- Making the pulsed waveform construction figure ----------
	fig2dev -L eps -m 1 $< $@

# The arbitrary waveform construction parameter figure
./figs/arb_params.eps: ./figs/arb_params.fig
	# ----- Making the arbitrary waveform construction figure ---------
	fig2dev -L eps -m 1 $< $@

# The arbitrary waveform example figure
./figs/arb_example.eps: ./figs/arb_example.fig
	# ----- Making the arbitrary waveform construction figure ---------
	fig2dev -L eps -m 1 $< $@

# The ramp waveform construction parameter figure
./figs/ramp_params.eps: ./figs/ramp_params.fig
	# ----- Making the ramp waveform construction figure --------
	fig2dev -L eps -m 1 $< $@

# The current interrupt timing figure
./figs/interrupt_plot.eps: ./figs/interrupt_plot.fig
	# ---------- Making the current interrupt timing figure -----------
	fig2dev -L eps -m 1 $< $@

# The current interrupt synchronization timing figure
./figs/cisync_timing.eps: ./figs/cisync_timing.fig
	# ---------- Making the CI synchronization timing figure ----------
	fig2dev -L eps -m 1 $< $@

# The current interrupt example figure
./figs/ci_example.eps: ./figs/ci_example.fig
	fig2dev -L eps -m 1 $< $@

# The streaming data packet figure
./figs/datapacket.eps: ./figs/datapacket.fig
	# ---------------- Making the data packet figure ------------------
	fig2dev -L eps -m 1 $< $@

# The normal pulse example figure
./figs/npulse_example.eps: ./figs/npulse_example.fig
	# ------------ Making the normal pulse example figure -------------
	fig2dev -L eps -m 1 $< $@

# The CV example figure
./figs/cv_example.eps: ./figs/cv_example.fig
	fig2dev -L eps -m 1 $< $@

# The status bits figure.
# To convert gifs to eps, you must specifiy the image resolution.  You can
# determine this with:
# identify -verbose <image file>
# Then use this resolution in the density flag.
./raster/status_bits.eps: ./raster/status_bits.gif
	convert -density 72x72 $< $@

# The SRS logo
./raster/srs_logo.eps: ./raster/srs_logo.png
	convert $< $@

# ---- The "sideby" figures for documenting the front and rear panels -----

# IR compensation
./figs/ircomp_sideby.eps: ./figs/ircomp_sideby.fig
	fig2dev -L eps -m 1 $< $@

# Rear panel auxiliary input BNCs
./figs/aux_adc_sideby.eps: ./figs/aux_adc_sideby.fig
	fig2dev -L eps -m 1 $< $@





spell: spellcheck.sh
	cd scripts;./spellcheck.sh

spellcheck.sh: ./scripts/ec100_cmds.list\
			   ./scripts/ec100_jargon.list
	cd scripts;python spellgen.py

# comcheck -- report missing commands
comcheck:
	cd scripts;python comcheck.py

clean:
	rm -f *.aux
	# Clean up pages created by pdfpage.sh
	rm -f $(MAINFILE)_page*.pdf
	rm -f figs/*.eps
	rm -f figs/*.bak
	rm -f output/howto_page*

.PHONY: help clean dvi ps howto pdf comcheck spell
