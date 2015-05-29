DEFINES	+= TVERPARAMPARAMDLG_DLL
TEMPLATE	= lib
TARGET    = tverparamparamdlg
CONFIG += qt dll debug thread
QT += sql

QMAKE_LIBDIR +=  ./           \
        	     $(ADEHOME)/lib \
	             $(ADEHOME)/bin 

LIBS +=	-lqtexdb -lalgorithm

DESTDIR = $(ADEHOME)\tmp\tverparamparamdlg

OBJECTS_DIR = $(ADEHOME)/tmp/tverparamparamdlg/obj
UI_DIR = $(ADEHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(ADEHOME_INC)/include	\
									 $$(ADEHOME_INC)/include/qextserial

HEADERS	+= $$(ADEHOME_INC)/include/tverparamparamdlg.h

SOURCES	+= tverparamparamdlg.cpp

FORMS	+= ui/tverparam_param.ui

win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(ADEHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(ADEHOME)\dll \
				  & copy .\language\tverparam_param_zh.qm $(ADEHOME)\uif\i18n\zh \
                  & copy .\language\tverparam_param_en.qm $(ADEHOME)\uif\i18n\en 
}

TRANSLATIONS =  \
		language/tverparam_param_zh.ts language/tverparam_param_en.ts \
		
