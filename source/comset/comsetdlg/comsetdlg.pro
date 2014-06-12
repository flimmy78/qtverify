
TEMPLATE	= lib
TARGET    = comsetdlg
CONFIG += qt dll debug

DEFINES	+= COMSETDLG_DLL

QMAKE_LIBDIR +=  ./           \
        	     $(RUNHOME)/lib \
	             $(RUNHOME)/bin \

DESTDIR = $(RUNHOME)\tmp\comset\comsetdlg\obj
MOC_DIR = $(RUNHOME)/tmp/comset/comsetdlg/moc
OBJECTS_DIR = $(RUNHOME)/tmp/comset/comsetdlg/obj
UI_DIR = $(RUNHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(RUNHOME_INC)/include \
									 $$(RUNHOME_INC)/include/qextsp

HEADERS	+= $(RUNHOME_INC)/include/comsetdlg_global.h \
           $(RUNHOME_INC)/include/comsetdlg.h   \
           $(RUNHOME_INC)/include/qextsp/qextserialbase.h  \
           $(RUNHOME_INC)/include/qextsp/qextserialport.h  \
           $(RUNHOME_INC)/include/qextsp/win_qextserialport.h
	
SOURCES	+= source/comsetdlg.cpp   \
           $(RUNHOME_INC)/include/qextsp/qextserialbase.cpp  \
           $(RUNHOME_INC)/include/qextsp/qextserialport.cpp  \
           $(RUNHOME_INC)/include/qextsp/win_qextserialport.cpp 
					 
FORMS	+= ui/comsetdlg.ui \
         
win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(RUNHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(RUNHOME)\dll
}

TRANSLATIONS =  \
		language/comsetdlg_zh.ts language/comsetdlg_en.ts
		
