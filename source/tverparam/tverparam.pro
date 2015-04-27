DEFINES	+= TVERPARAM_DLL
TEMPLATE	= lib
TARGET    = tverparam
CONFIG += qt dll debug thread qtestlib
QT += sql


QMAKE_LIBDIR +=  ./           \
        	     $(RUNHOME)/lib \
	             $(RUNHOME)/bin 

LIBS +=	-lQt3Supportd4 -lQt3Support4 -lprotocol -lsystemsetdlg -lcomobject -lqtexdb -lalgorithm -ltverparamparamdlg

DESTDIR = $(RUNHOME)\tmp\tverparam
OBJECTS_DIR = $(RUNHOME)/tmp/tverparam/obj
UI_DIR = $(RUNHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(RUNHOME_INC)/include	\
									 $$(RUNHOME_INC)/include/qextserial

HEADERS	+= $$(RUNHOME_INC)/include/tverparam.h 

SOURCES	+= tverparam.cpp

FORMS	+= ui/tverparam.ui \

RESOURCES += tverparam.qrc     
         
win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(RUNHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(RUNHOME)\dll \
                  & copy .\language\tverparam_zh.qm $(RUNHOME)\uif\i18n\zh \
                  & copy .\language\tverparam_en.qm $(RUNHOME)\uif\i18n\en \

}

TRANSLATIONS =  \
		language/tverparam_zh.ts language/tverparam_en.ts \	
