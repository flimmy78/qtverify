TEMPLATE	= app
TARGET    = systemset

CONFIG += qt warn_on debug
RC_FILE = systemset.rc

INCLUDEPATH	 +=  $$(RUNHOME_INC)/include  \
								 $$(RUNHOME_INC)/include/qextserial

QMAKE_LIBDIR += \
              $$(RUNHOME)/lib \
              $$(RUNHOME)/bin
           

LIBS	+= -lsystemsetdlg
SOURCES	+= main.cpp

win32:debug{
	CONFIG += console
}

win32{
DEFINES += WIN32 _AFXDLL
DEFINES -= _USRDLL
DESTDIR = $(RUNHOME)\tmp\systemset\obj
}

MOC_DIR = $(RUNHOME)/tmp/systemset/moc
OBJECTS_DIR = $(RUNHOME)/tmp/systemset/obj
UI_DIR = $(RUNHOME)/tmp/systemset/ui


win32{
	MY_DEST_EXE_VAR = $${DESTDIR} $${TARGET}.exe
	MY_DEST_EXE = $$join( MY_DEST_EXE_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_EXE} $$(RUNHOME)\bin
}


