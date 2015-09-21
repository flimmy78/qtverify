
TEMPLATE	= lib
TARGET    = adjustratedlg
CONFIG += qt dll debug thread

DEFINES	+= ADJUSTRATEDLG_DLL QT_THREAD_SUPPORT

QMAKE_LIBDIR +=  ./           \
        	     $(ADEHOME)/lib \
	             $(ADEHOME)/bin 

LIBS += -lsystemsetdlg -lprotocol -lcomobject -lalgorithm -lqtexdb

DESTDIR = $$(ADEHOME)\tmp\adjustrate\adjustratedlg\obj
#MOC_DIR = $(ADEHOME)/tmp/adjustrate/adjustratedlg/moc
OBJECTS_DIR = $$(ADEHOME)/tmp/adjustrate/adjustratedlg/obj
UI_DIR = $$(ADEHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(ADEHOME_INC)/include	\
									 $$(ADEHOME_INC)/include/qextserial

HEADERS	+= $$(ADEHOME_INC)/include/adjustratedlg.h \
	
SOURCES	+= source/adjustratedlg.cpp

FORMS	+= ui/adjustratedlg.ui

RESOURCES += adjustratedlg.qrc     

win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(ADEHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(ADEHOME)\dll \
                  & copy .\language\adjustratedlg_zh.qm $(ADEHOME)\uif\i18n\zh \
                  & copy .\language\adjustratedlg_en.qm $(ADEHOME)\uif\i18n\en 
}

TRANSLATIONS =  \
		language/adjustratedlg_zh.ts language/adjustratedlg_en.ts
		
