DEFINES	+= CMBVERIFY_DLL QT_THREAD_SUPPORT
TEMPLATE	= lib
TARGET    = cmbverify
CONFIG += qt dll debug thread
QT += sql

QMAKE_LIBDIR +=  ./           \
        	     $(ADEHOME)/lib \
	             $(ADEHOME)/bin 
	            
LIBS +=	-lprotocol -lcomobject -lqtexdb -lalgorithm -lsystemsetdlg -lreport

DESTDIR = $(ADEHOME)\tmp\cmbverify
#MOC_DIR = $(ADEHOME)/tmp/cmbverify/moc
OBJECTS_DIR = $(ADEHOME)/tmp/cmbverify/obj
UI_DIR = $(ADEHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(ADEHOME_INC)/include	\
									 $$(ADEHOME_INC)/include/qextserial

HEADERS	+= $$(ADEHOME_INC)/include/cmbverify.h \
			$$(ADEHOME_INC)/include/cmbparam.h 
	
SOURCES	+= cmbverify.cpp  \
			cmbparam.cpp

					 
FORMS	+= cmbverify.ui\
			cmbparam.ui
     
RESOURCES += cmbverify.qrc     
         
win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(ADEHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(ADEHOME)\dll \
                  & copy .\language\cmbverify_zh.qm $(ADEHOME)\uif\i18n\zh \
                  & copy .\language\cmbverify_en.qm $(ADEHOME)\uif\i18n\en 

}

TRANSLATIONS =  \
		language/cmbverify_zh.ts language/cmbverify_en.ts
		
