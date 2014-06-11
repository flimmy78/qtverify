TEMPLATE	= app
TARGET    = qtcom

CONFIG += qt warn_on debug
RC_FILE = qtcom.rc

INCLUDEPATH	 +=  $$(RUNHOME_INC)/include  \

QMAKE_LIBDIR += \
              $$(RUNHOME)/lib \
              $$(RUNHOME)/bin
           
LIBS	+= -lqtcomdlg

SOURCES	+= main.cpp

win32:debug{
	CONFIG += console
}

win32{
DEFINES += WIN32 _AFXDLL
DEFINES -= _USRDLL
DESTDIR = $(RUNHOME)\tmp\qtcom\obj
}

MOC_DIR = $(RUNHOME)/tmp/qtcom/moc
OBJECTS_DIR = $(RUNHOME)/tmp/qtcom/obj
UI_DIR = $(RUNHOME)/tmp/qtcom/ui


win32{
	MY_DEST_EXE_VAR = $${DESTDIR} $${TARGET}.exe
	MY_DEST_EXE = $$join( MY_DEST_EXE_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_EXE} $$(RUNHOME)\bin
}


