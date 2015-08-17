
TEMPLATE	= lib
TARGET    = flowweight
CONFIG += qt dll debug thread
QT += sql

DEFINES	+= FLOWWEIGHT_DLL QT_THREAD_SUPPORT

QMAKE_LIBDIR +=  ./           \
        	     $(ADEHOME)/lib \
	             $(ADEHOME)/bin 
	            
LIBS += -lprotocol -lsystemsetdlg -lcomobject -lqtexdb -lalgorithm -lreport

DESTDIR = $(ADEHOME)\tmp\flowweight
#MOC_DIR = $(ADEHOME)/tmp/flowweight/moc
OBJECTS_DIR = $(ADEHOME)/tmp/flowweight/obj
UI_DIR = $(ADEHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(ADEHOME_INC)/include	\
									 $$(ADEHOME_INC)/include/qextserial

HEADERS	+= $$(ADEHOME_INC)/include/flowweight.h 
	
SOURCES	+= flowweight.cpp  

					 
FORMS	+= flowweight.ui
     
RESOURCES += flowweight.qrc     
         
win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(ADEHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(ADEHOME)\dll \
                  & copy .\language\flowweight_zh.qm $(ADEHOME)\uif\i18n\zh \
                  & copy .\language\flowweight_en.qm $(ADEHOME)\uif\i18n\en 

}

TRANSLATIONS =  \
		language/flowweight_zh.ts language/flowweight_en.ts
		
