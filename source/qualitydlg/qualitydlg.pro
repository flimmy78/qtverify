
TEMPLATE	= lib
TARGET    = qualitydlg
CONFIG += qt dll debug

DEFINES	+= QUALITYDLG_DLL

QMAKE_LIBDIR +=  ./           \
        	     $(RUNHOME)/lib \
	             $(RUNHOME)/bin \

DESTDIR = $(RUNHOME)\tmp\qualitydlg\obj
MOC_DIR = $(RUNHOME)/tmp/qualitydlg/moc
OBJECTS_DIR = $(RUNHOME)/tmp/qualitydlg/obj
UI_DIR = $(RUNHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(RUNHOME_INC)/include \

HEADERS	+= $$(RUNHOME_INC)/include/qualitydlg_global.h \
           $$(RUNHOME_INC)/include/qualitydlg.h  
	
SOURCES	+= source/qualitydlg.cpp  
					 
FORMS	+= ui/qualitydlg.ui
         
win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(RUNHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(RUNHOME)\dll
}

TRANSLATIONS =  \
		language/qualitydlg_zh.ts language/qualitydlg_en.ts language/qualitydlg_es.ts
		
