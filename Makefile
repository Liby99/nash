DOC_TARGET = sample # Add file to be pdflatexed here
DOC_SOURCE_DIR = doc
DOC_OUTPUT_DIR = pdf
DOC_PDF = $(patsubst %, $(DOC_OUTPUT_DIR)/%.pdf, $(DOC_TARGET))

build:
	@ sh ./build.sh

doc: $(DOC_PDF)

$(DOC_OUTPUT_DIR)/%.pdf: $(DOC_SOURCE_DIR)/%.tex
	@ pdflatex $<
	@ mkdir -p $(DOC_OUTPUT_DIR)/
	@ mv $(*F).pdf $(DOC_OUTPUT_DIR)/$(*F).pdf

clean-build:
	@ rm -rf build/

clean-doc:
	@ rm *.aux *.log
	@ rm -rf $(DOC_OUTPUT_DIR)

clean: clean-build clean-doc
