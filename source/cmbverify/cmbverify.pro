
TEMPLATE	= lib
TARGET    = cmbverify
CONFIG += qt dll debug thread qtestlib
QT += sql

DEFINES	+= CMBVERIFY_DLL QT_THREAD_SUPPORT

QMAKE_LIBDIR +=  ./           \
        	     $(RUNHOME)/lib \
	             $(RUNHOME)/bin 
	            
LIBS +=	-lQt3Supportd4 -lQt3Support4 -lprotocol -lcomobject -lqtexdb -lalgorithm

DESTDIR = $(RUNHOME)\tmp\cmbverify
#MOC_DIR = $(RUNHOME)/tmp/cmbverify/moc
OBJECTS_DIR = $(RUNHOME)/tmp/cmbverify/obj
UI_DIR = $(RUNHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(RUNHOME_INC)/include	\
									 $$(RUNHOME_INC)/include/qextserial

HEADERS	+= $$(RUNHOME_INC)/include/cmbverify.h 
	
SOURCES	+= cmbverify.cpp  

					 
FORMS	+= cmbverify.ui
     
RESOURCES += cmbverify.qrc     
         
win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(RUNHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(RUNHOME)\dll \
                  & copy .\language\cmbverify_zh.qm $(RUNHOME)\uif\i18n\zh \
                  & copy .\language\cmbverify_en.qm $(RUNHOME)\uif\i18n\en 

}

TRANSLATIONS =  \
		language/cmbverify_zh.ts language/cmbverify_en.ts
		
