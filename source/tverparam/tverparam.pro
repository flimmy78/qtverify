DEFINES	+= TVERPARAM_DLL
TEMPLATE	= lib
TARGET    = tverparam
CONFIG += qt dll debug thread qtestlib
QT += sql


QMAKE_LIBDIR +=  ./           \
        	     $(ADEHOME)/lib \
	             $(ADEHOME)/bin 

LIBS +=	-lprotocol -lsystemsetdlg -lcomobject -lqtexdb -lalgorithm

DESTDIR = $(ADEHOME)\tmp\tverparam
OBJECTS_DIR = $(ADEHOME)/tmp/tverparam/obj
UI_DIR = $(ADEHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(ADEHOME_INC)/include	\
									 $$(ADEHOME_INC)/include/qextserial

HEADERS	+= $$(ADEHOME_INC)/include/tverparam.h \
           $$(ADEHOME_INC)/include/tverparamparamdlg.h

SOURCES	+= tverparam.cpp \
           tverparamparamdlg.cpp

FORMS	+= ui/tverparam.ui \
         ui/tverparam_param.ui

RESOURCES += tverparam.qrc     
         
win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(ADEHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(ADEHOME)\dll \
                  & copy .\language\tverparam_zh.qm $(ADEHOME)\uif\i18n\zh \
                  & copy .\language\tverparam_en.qm $(ADEHOME)\uif\i18n\en \

}

TRANSLATIONS =  \
		language/tverparam_zh.ts language/tverparam_en.ts \	
