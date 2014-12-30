
TEMPLATE	= lib
TARGET    = masterslaveset
CONFIG += qt dll debug

DEFINES	+= MASTERSLAVESET_DLL

QMAKE_LIBDIR +=  ./           \
        	     $(RUNHOME)/lib \
	             $(RUNHOME)/bin

LIBS += -lQt3Supportd4 -lalgorithm

DESTDIR = $(RUNHOME)\tmp\masterslaveset\obj
#MOC_DIR = $(RUNHOME)/tmp/masterslaveset/moc
OBJECTS_DIR = $(RUNHOME)/tmp/masterslaveset/obj
UI_DIR = $(RUNHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(RUNHOME_INC)/include

HEADERS	+= $$(RUNHOME_INC)/include/masterslaveset.h
	
SOURCES	+= source/masterslaveset.cpp 

FORMS	+= ui/masterslaveset.ui

win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(RUNHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(RUNHOME)\dll \
                  & copy .\language\masterslaveset_zh.qm $(RUNHOME)\uif\i18n\zh \
                  & copy .\language\masterslaveset_en.qm $(RUNHOME)\uif\i18n\en 

}

TRANSLATIONS =  \
		language/masterslaveset_zh.ts language/masterslaveset_en.ts
		
