
TEMPLATE	= lib
TARGET    = masterslaveset
CONFIG += qt dll debug

DEFINES	+= MASTERSLAVESET_DLL

QMAKE_LIBDIR +=  ./           \
        	     $(ADEHOME)/lib \
	             $(ADEHOME)/bin

LIBS += -lalgorithm

DESTDIR = $(ADEHOME)\tmp\masterslaveset\obj
#MOC_DIR = $(ADEHOME)/tmp/masterslaveset/moc
OBJECTS_DIR = $(ADEHOME)/tmp/masterslaveset/obj
UI_DIR = $(ADEHOME_INC)/include

INCLUDEPATH  	=    ./      \
					include  \ 
					$$(ADEHOME_INC)/include

HEADERS	+= $$(ADEHOME_INC)/include/masterslaveset.h
	
SOURCES	+= source/masterslaveset.cpp 

FORMS	+= ui/masterslaveset.ui

win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(ADEHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(ADEHOME)\dll \
                  & copy .\language\masterslaveset_zh.qm $(ADEHOME)\uif\i18n\zh \
                  & copy .\language\masterslaveset_en.qm $(ADEHOME)\uif\i18n\en 

}

TRANSLATIONS =  \
		language/masterslaveset_zh.ts language/masterslaveset_en.ts
		
