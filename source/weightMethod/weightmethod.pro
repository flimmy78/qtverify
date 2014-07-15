
TEMPLATE	= lib
TARGET    = weightmethod
CONFIG += qt dll debug thread qtestlib

DEFINES	+= WEIGHTMETHOD_DLL QT_THREAD_SUPPORT

QMAKE_LIBDIR +=  ./           \
        	     $(RUNHOME)/lib \
	             $(RUNHOME)/bin 
	            
LIBS +=	-lQt3Supportd4 -lQt3Support4 -lprotocol -lcomsetdlg -lcomobject -lqtexdb -lalgorithm

DESTDIR = $(RUNHOME)\tmp\weightmethod
#MOC_DIR = $(RUNHOME)/tmp/weightmethod/moc
OBJECTS_DIR = $(RUNHOME)/tmp/weightmethod/obj
UI_DIR = $(RUNHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(RUNHOME_INC)/include	\
									 $$(RUNHOME_INC)/include/qextserial

HEADERS	+= $$(RUNHOME_INC)/include/weightmethod.h 
	
SOURCES	+= weightmethod.cpp  

					 
FORMS	+= weightmethod.ui
     
RESOURCES += weightmethod.qrc     
         
win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(RUNHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(RUNHOME)\dll
}

TRANSLATIONS =  \
		language/weightmethod_zh.ts language/weightmethod_en.ts
		
