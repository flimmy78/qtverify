
TEMPLATE	= lib
TARGET    = flowweight
CONFIG += qt dll debug thread qtestlib
QT += sql

DEFINES	+= FLOWWEIGHT_DLL QT_THREAD_SUPPORT

QMAKE_LIBDIR +=  ./           \
        	     $(RUNHOME)/lib \
	             $(RUNHOME)/bin 
	            
LIBS +=	-lQt3Supportd4 -lQt3Support4 -lprotocol -lsystemsetdlg -lcomobject -lqtexdb -lalgorithm	\
			  -ldatatestdlg

DESTDIR = $(RUNHOME)\tmp\flowweight
#MOC_DIR = $(RUNHOME)/tmp/flowweight/moc
OBJECTS_DIR = $(RUNHOME)/tmp/flowweight/obj
UI_DIR = $(RUNHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(RUNHOME_INC)/include	\
									 $$(RUNHOME_INC)/include/qextserial

HEADERS	+= $$(RUNHOME_INC)/include/flowweight.h 
	
SOURCES	+= flowweight.cpp  

					 
FORMS	+= flowweight.ui
     
RESOURCES += flowweight.qrc     
         
win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(RUNHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(RUNHOME)\dll \
                  & copy .\language\flowweight_zh.qm $(RUNHOME)\uif\i18n\zh \
                  & copy .\language\flowweight_en.qm $(RUNHOME)\uif\i18n\en 

}

TRANSLATIONS =  \
		language/flowweight_zh.ts language/flowweight_en.ts
		
