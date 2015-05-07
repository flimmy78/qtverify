DEFINES	+= TVERPARAMPARAMDLG_DLL
TEMPLATE	= lib
TARGET    = tverparamparamdlg
CONFIG += qt dll debug thread
QT += sql

QMAKE_LIBDIR +=  ./           \
        	     $(RUNHOME)/lib \
	             $(RUNHOME)/bin 

LIBS +=	-lQt3Supportd4 -lQt3Support4 -lqtexdb -lalgorithm

DESTDIR = $(RUNHOME)\tmp\tverparamparamdlg

OBJECTS_DIR = $(RUNHOME)/tmp/tverparamparamdlg/obj
UI_DIR = $(RUNHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(RUNHOME_INC)/include	\
									 $$(RUNHOME_INC)/include/qextserial

HEADERS	+= $$(RUNHOME_INC)/include/tverparamparamdlg.h

SOURCES	+= tverparamparamdlg.cpp

FORMS	+= ui/tverparam_param.ui

win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(RUNHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(RUNHOME)\dll \
				  & copy .\language\tverparam_param_zh.qm $(RUNHOME)\uif\i18n\zh \
                  & copy .\language\tverparam_param_en.qm $(RUNHOME)\uif\i18n\en 
}

TRANSLATIONS =  \
		language/tverparam_param_zh.ts language/tverparam_param_en.ts \
		
