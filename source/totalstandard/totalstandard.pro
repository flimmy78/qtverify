
TEMPLATE	= lib
TARGET    = totalstandard
CONFIG += qt dll debug thread qtestlib
QT += sql

DEFINES	+= TOTALSTANDARD_DLL QT_THREAD_SUPPORT

QMAKE_LIBDIR +=  ./           \
        	     $(RUNHOME)/lib \
	             $(RUNHOME)/bin 
	            
LIBS +=	-lQt3Supportd4 -lQt3Support4 -lprotocol -lcomsetdlg -lcomobject -lqtexdb -lalgorithm	\
			  -ldatatestdlg

DESTDIR = $(RUNHOME)\tmp\totalstandard
#MOC_DIR = $(RUNHOME)/tmp/totalstandard/moc
OBJECTS_DIR = $(RUNHOME)/tmp/totalstandard/obj
UI_DIR = $(RUNHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(RUNHOME_INC)/include	\
									 $$(RUNHOME_INC)/include/qextserial

HEADERS	+= $$(RUNHOME_INC)/include/totalstandard.h 
	
SOURCES	+= totalstandard.cpp  

					 
FORMS	+= totalstandard.ui
     
RESOURCES += totalstandard.qrc     
         
win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(RUNHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(RUNHOME)\dll \
                  & copy .\language\totalstandard_zh.qm $(RUNHOME)\uif\i18n\zh \
                  & copy .\language\totalstandard_en.qm $(RUNHOME)\uif\i18n\en 

}

TRANSLATIONS =  \
		language/totalstandard_zh.ts language/totalstandard_en.ts
		
