
TEMPLATE	= lib
TARGET    = datatestdlg
CONFIG += qt dll debug thread

DEFINES	+= DATATESTDLG_DLL QT_THREAD_SUPPORT

QMAKE_LIBDIR +=  ./           \
        	     $(ADEHOME)/lib \
	             $(ADEHOME)/bin 
	            
LIBS += -lsystemsetdlg -lprotocol -lcomobject -lalgorithm -lqtexdb

DESTDIR = $(ADEHOME)\tmp\datatest\datatestdlg\obj
#MOC_DIR = $(ADEHOME)/tmp/datatest/datatestdlg/moc
OBJECTS_DIR = $(ADEHOME)/tmp/datatest/datatestdlg/obj
UI_DIR = $(ADEHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(ADEHOME_INC)/include	\
									 $$(ADEHOME_INC)/include/qextserial

HEADERS	+= $$(ADEHOME_INC)/include/datatestdlg.h \
	
SOURCES	+= source/datatestdlg.cpp
			 
FORMS	+= ui/datatestdlg.ui
     
RESOURCES += datatestdlg.qrc     
         
win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(ADEHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(ADEHOME)\dll \
                  & copy .\language\datatestdlg_zh.qm $(ADEHOME)\uif\i18n\zh \
                  & copy .\language\datatestdlg_en.qm $(ADEHOME)\uif\i18n\en 
}

TRANSLATIONS =  \
		language/datatestdlg_zh.ts language/datatestdlg_en.ts
		
