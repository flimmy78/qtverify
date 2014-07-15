TEMPLATE = lib
CONFIG += dll console debug
TARGET = logindialog

QT += sql

DEPENDPATH += .
INCLUDEPATH  	+=    ./      \
									 include \ 
									 $$(RUNHOME_INC)/include
									 
DEFINES	+= LOGINDIALOG_DLL

QMAKE_LIBDIR +=  ./             \
        	  		 $(RUNHOME)/lib \
	          		 $(RUNHOME)/bin 
	          		 
LIBS += -lqtexdb	          		 

UI_DIR = $(RUNHOME_INC)/include

# Input
HEADERS += $$(RUNHOME_INC)/include/logindialog.h
SOURCES += logindialog.cpp
FORMS += logindialog.ui

win32{
DEFINES += WIN32 _AFXDLL
DEFINES -= _USRDLL
DESTDIR = $(RUNHOME)\tmp\logindialog\obj
}

win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $(RUNHOME)\lib \
                        & copy $${MY_DEST_DLL} $(RUNHOME)\dll
}
