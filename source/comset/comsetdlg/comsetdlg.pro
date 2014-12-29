
TEMPLATE	= lib
QT         += xml
TARGET    = comsetdlg
CONFIG += qt dll debug

DEFINES	+= COMSETDLG_DLL

QMAKE_LIBDIR +=  ./           \
        	     $(RUNHOME)/lib \
	             $(RUNHOME)/bin \

DESTDIR = $(RUNHOME)\tmp\comset\comsetdlg\obj
#MOC_DIR = $(RUNHOME)/tmp/comset/comsetdlg/moc
OBJECTS_DIR = $(RUNHOME)/tmp/comset/comsetdlg/obj
UI_DIR = $(RUNHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(RUNHOME_INC)/include \
									 $$(RUNHOME_INC)/include/qextserial


HEADERS	+= $$(RUNHOME_INC)/include/setcomfrm.h   \
		   		 $$(RUNHOME_INC)/include/setportfrm.h  \
		   		 $$(RUNHOME_INC)/include/readcomconfig.h \
        	 $$(RUNHOME_INC)/include/qextserial/qextserialport_global.h  \
        	 $$(RUNHOME_INC)/include/qextserial/qextserialport.h
	
SOURCES	+= source/setcomfrm.cpp \
			     source/setportfrm.cpp \
			     source/readcomconfig.cpp \
	         $$(RUNHOME_INC)/include/qextserial/qextserialport.cpp

win32 {
     SOURCES += $$(RUNHOME_INC)/include/qextserial/qextserialport_win.cpp
}

unix {
     SOURCES += $$(RUNHOME_INC)/include/qextserial/qextserialport_unix.cpp
}
					 
FORMS	+= ui/setcomfrm.ui \
		     ui/setportfrm.ui \

win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(RUNHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(RUNHOME)\dll \
                  & copy .\language\comsetdlg_zh.qm $(RUNHOME)\uif\i18n\zh	\
                  & copy .\language\comsetdlg_en.qm $(RUNHOME)\uif\i18n\en
}

TRANSLATIONS =  \
		language/comsetdlg_zh.ts language/comsetdlg_en.ts
		
