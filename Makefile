TEX_TARGET = sample # Add file to be pdflatexed here
TEX_SOURCE_DIR = doc/paper
TEX_OUTPUT_DIR = pdf
TEX_PDF = $(patsubst %, $(TEX_OUTPUT_DIR)/%.pdf, $(TEX_TARGET))

SRC_FILES = src/**/*.cpp src/**/*.h app/*.cpp app/**/*.cpp test/*.cpp test/**/*.cpp

all: build

build: FORCE
	sh ./script/build

format: format-lib format-app format-test

format-lib:
	find ./src/intern -name '*.cpp' | xargs -I '{}' clang-format -i '{}'
	find ./src/extern -name '*.h' | xargs -I '{}' clang-format -i '{}'
	
format-app:
	find ./app -name '*.cpp' | xargs -I '{}' clang-format -i '{}'
	
format-test:
	find ./test -name '*.cpp' | xargs -I '{}' clang-format -i '{}'

setup-pre-commit:
	cp ./script/pre-commit .git/hooks/pre-commit

remove-pre-commit:
	rm .git/hooks/pre-commit

doc: $(TEX_PDF)

$(TEX_OUTPUT_DIR)/%.pdf: $(TEX_SOURCE_DIR)/%.tex
	@ pdflatex $<
	@ mkdir -p $(TEX_OUTPUT_DIR)/
	@ mv $(*F).pdf $(TEX_OUTPUT_DIR)/$(*F).pdf

clean-build:
	@ rm -rf build/

clean-doc:
	@ rm *.aux *.log
	@ rm -rf $(TEX_OUTPUT_DIR)

clean: clean-build clean-doc

FORCE:
