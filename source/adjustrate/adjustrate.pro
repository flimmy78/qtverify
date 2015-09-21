TEMPLATE	= app
TARGET    = adjustrate

CONFIG += qt warn_on debug
RC_FILE = adjustrate.rc

INCLUDEPATH	 +=  ./adjustratedlg/include     \
								 $$(ADEHOME_INC)/include  \
                 $$(ADEHOME_INC)/include/qextserial

QMAKE_LIBDIR += \
              $$(ADEHOME)/lib \
              $$(ADEHOME)/bin
           
LIBS	+= -ladjustratedlg -lqtexdb

SOURCES	+= main.cpp

win32:debug{
	CONFIG += console
}

win32{
DEFINES += WIN32 _AFXDLL
DEFINES -= _USRDLL
DESTDIR = $(ADEHOME)\tmp\adjustrate\obj
}

MOC_DIR = $(ADEHOME)/tmp/adjustrate/moc
OBJECTS_DIR = $(ADEHOME)/tmp/adjustrate/obj
UI_DIR = $(ADEHOME)/tmp/adjustrate/ui

win32{
	MY_DEST_EXE_VAR = $${DESTDIR} $${TARGET}.exe
	MY_DEST_EXE = $$join( MY_DEST_EXE_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_EXE} $$(ADEHOME)\bin
}