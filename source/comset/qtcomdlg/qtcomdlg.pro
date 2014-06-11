
TEMPLATE	= lib
TARGET    = qtcomdlg
CONFIG += qt dll debug

DEFINES	+= QTCOMDLG_DLL

QMAKE_LIBDIR +=  ./           \
        	     $(RUNHOME)/lib \
	             $(RUNHOME)/bin \

DESTDIR = $(RUNHOME)\tmp\qtcom\qtcomdlg\obj
MOC_DIR = $(RUNHOME)/tmp/qtcom/qtcomdlg/moc
OBJECTS_DIR = $(RUNHOME)/tmp/qtcom/qtcomdlg/obj
UI_DIR = $(RUNHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(RUNHOME_INC)/include \

HEADERS	+= $(RUNHOME_INC)/include/qtcomdlg_global.h \
           $(RUNHOME_INC)/include/serialportset.h   \
           $(RUNHOME_INC)/include/qextserialbase.h  \
           $(RUNHOME_INC)/include/qextserialport.h  \
           $(RUNHOME_INC)/include/win_qextserialport.h
	
SOURCES	+= source/serialportset.cpp   \
           source/qextserialbase.cpp  \
           source/qextserialport.cpp  \
           source/win_qextserialport.cpp 
					 
FORMS	+= ui/serialportset.ui \
         
win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(RUNHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(RUNHOME)\dll
}

TRANSLATIONS =  \
		language/qtcomdlg_zh.ts language/qtcomdlg_en.ts language/qtcomdlg_es.ts
		
