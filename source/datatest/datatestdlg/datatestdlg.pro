
TEMPLATE	= lib
TARGET    = datatestdlg
CONFIG += qt dll debug qtestlib thread
QT += sql

DEFINES	+= DATATESTDLG_DLL QT_THREAD_SUPPORT

QMAKE_LIBDIR +=  ./           \
        	     $(RUNHOME)/lib \
	             $(RUNHOME)/bin 
	            
LIBS +=	-lQt3Supportd4 -lQt3Support4 -lprotocol -lcomsetdlg -lcomobject -lqtexdb -lalgorithm

DESTDIR = $(RUNHOME)\tmp\datatest\datatestdlg\obj
#MOC_DIR = $(RUNHOME)/tmp/datatest/datatestdlg/moc
OBJECTS_DIR = $(RUNHOME)/tmp/datatest/datatestdlg/obj
UI_DIR = $(RUNHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(RUNHOME_INC)/include	\
									 $$(RUNHOME_INC)/include/qextserial

HEADERS	+= $$(RUNHOME_INC)/include/datatestdlg_global.h \
		       $$(RUNHOME_INC)/include/parasetdlg_global.h \
           $$(RUNHOME_INC)/include/datatestdlg.h \
           $$(RUNHOME_INC)/include/parasetdlg.h \ 
	
SOURCES	+= source/datatestdlg.cpp  \
			source/parasetdlg.cpp  \

					 
FORMS	+= ui/datatestdlg.ui \
         ui/parasetdlg.ui
     
RESOURCES += datatestdlg.qrc     
         
win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(RUNHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(RUNHOME)\dll \
                  & copy .\language\datatestdlg_zh.qm $(RUNHOME)\uif\i18n
}

TRANSLATIONS =  \
		language/datatestdlg_zh.ts language/datatestdlg_en.ts
		
