PATH_BASE_PACK=../../xhajek48_xondri07_xrosin00_xrozsi06
PATH_BASE=..
PATH_DOC=$(PATH_BASE_PACK)/doc
PATH_INSTALL=$(PATH_BASE_PACK)/install
PATH_REPO=$(PATH_BASE_PACK)/repo
all:
	@cd "GUICalculator\bin\Debug\" & GUICalculator.exe
pack:
	@mkdir "$(PATH_BASE_PACK)"
	@mkdir "$(PATH_DOC)"
	@mkdir "$(PATH_INSTALL)"
	@mkdir "$(PATH_REPO)"

	@cd "$(PATH_REPO)" & @git clone https://github.com/HoundThe/IVS.git
 
	@xcopy "$(PATH_BASE)/documentation" "$(PATH_DOC)" /e /i /h

	@copy "GUICalculator\bin\Debug\calculator_install.exe" "$(PATH_INSTALL)"
	cd "$(PATH_BASE_PACK)\.." & zip -r "xhajek48_xondri07_xrosin00_xrozsi06" "xhajek48_xondri07_xrosin00_xrozsi06"
run:
	@cd "GUICalculator\bin\Debug\" & GUICalculator.exe
profile:
	@cd "StandDeviation\bin\Debug\" & StandDeviation.exe
doc: Doxyfile
	doxygen $<
help:
	cd ../ & uzivatelsky_manual.rtf
clean: