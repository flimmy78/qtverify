TEMPLATE	= app
TARGET    = quality

CONFIG += qt warn_on debug
RC_FILE = quality.rc

INCLUDEPATH	 +=  ./qualitydlg/include     \
								 $$(RUNHOME_INC)/include  \
                 $$(RUNHOME_INC)/include/qextserial

QMAKE_LIBDIR += \
              $$(RUNHOME)/lib \
              $$(RUNHOME)/bin
           
LIBS	+= -lqualitydlg

SOURCES	+= main.cpp

win32:debug{
	CONFIG += console
}

win32{
DEFINES += WIN32 _AFXDLL
DEFINES -= _USRDLL
DESTDIR = $(RUNHOME)\tmp\quality\obj
}

MOC_DIR = $(RUNHOME)/tmp/quality/moc
OBJECTS_DIR = $(RUNHOME)/tmp/quality/obj
UI_DIR = $(RUNHOME)/tmp/quality/ui


win32{
	MY_DEST_EXE_VAR = $${DESTDIR} $${TARGET}.exe
	MY_DEST_EXE = $$join( MY_DEST_EXE_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_EXE} $$(RUNHOME)\bin
}


