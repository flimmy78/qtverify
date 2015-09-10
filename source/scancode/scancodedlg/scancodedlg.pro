TEMPLATE	= lib
TARGET    = scancodedlg

CONFIG += qt dll debug thread
QT += sql

DEFINES	+= SCANCODEDLG_DLL QT_THREAD_SUPPORT

QMAKE_LIBDIR +=  ./           \
        	     $(ADEHOME)/lib \
	             $(ADEHOME)/bin 
	            
LIBS += -lprotocol -lsystemsetdlg -lcomobject -lqtexdb -lalgorithm

DESTDIR = $(ADEHOME)\tmp\scancodedlg
#MOC_DIR = $(ADEHOME)/tmp/scancodedlg/moc
OBJECTS_DIR = $(ADEHOME)/tmp/scancodedlg/obj
UI_DIR = $(ADEHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(ADEHOME_INC)/include	\
									 $$(ADEHOME_INC)/include/qextserial

HEADERS	+= $$(ADEHOME_INC)/include/scancodedlg.h 
	
SOURCES	+= scancodedlg.cpp  
			 
FORMS	+= scancodedlg.ui
     
RESOURCES += scancodedlg.qrc     
         
win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(ADEHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(ADEHOME)\dll \
                  & copy .\language\scancodedlg_zh.qm $(ADEHOME)\uif\i18n\zh \
                  & copy .\language\scancodedlg_en.qm $(ADEHOME)\uif\i18n\en 

}

TRANSLATIONS =  \
		language/scancodedlg_zh.ts language/scancodedlg_en.ts
		
