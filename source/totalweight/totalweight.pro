
TEMPLATE	= lib
TARGET    = totalweight
CONFIG += qt dll debug thread qtestlib
QT += sql

DEFINES	+= TOTALWEIGHT_DLL QT_THREAD_SUPPORT

QMAKE_LIBDIR +=  ./           \
        	     $(ADEHOME)/lib \
	             $(ADEHOME)/bin 
	            
LIBS +=	-lprotocol -lsystemsetdlg -lcomobject -lqtexdb -lalgorithm -ldatatestdlg

DESTDIR = $(ADEHOME)\tmp\totalweight
#MOC_DIR = $(ADEHOME)/tmp/totalweight/moc
OBJECTS_DIR = $(ADEHOME)/tmp/totalweight/obj
UI_DIR = $(ADEHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(ADEHOME_INC)/include	\
									 $$(ADEHOME_INC)/include/qextserial

HEADERS	+= $$(ADEHOME_INC)/include/totalweight.h 
	
SOURCES	+= totalweight.cpp  

					 
FORMS	+= totalweight.ui
     
RESOURCES += totalweight.qrc     
         
win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(ADEHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(ADEHOME)\dll \
                  & copy .\language\totalweight_zh.qm $(ADEHOME)\uif\i18n\zh \
                  & copy .\language\totalweight_en.qm $(ADEHOME)\uif\i18n\en 

}

TRANSLATIONS =  \
		language/totalweight_zh.ts language/totalweight_en.ts
		
