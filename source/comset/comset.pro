TEMPLATE	= app
TARGET    = comset

CONFIG += qt warn_on debug
RC_FILE = comset.rc

INCLUDEPATH	 +=  $$(RUNHOME_INC)/include  \
								 $$(RUNHOME_INC)/include/qextserial

QMAKE_LIBDIR += \
              $$(RUNHOME)/lib \
              $$(RUNHOME)/bin
           
LIBS	+= -lcomsetdlg -lmasterslaveset

SOURCES	+= main.cpp

win32:debug{
	CONFIG += console
}

win32{
DEFINES += WIN32 _AFXDLL
DEFINES -= _USRDLL
DESTDIR = $(RUNHOME)\tmp\comset\obj
}

MOC_DIR = $(RUNHOME)/tmp/comset/moc
OBJECTS_DIR = $(RUNHOME)/tmp/comset/obj
UI_DIR = $(RUNHOME)/tmp/comset/ui


win32{
	MY_DEST_EXE_VAR = $${DESTDIR} $${TARGET}.exe
	MY_DEST_EXE = $$join( MY_DEST_EXE_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_EXE} $$(RUNHOME)\bin
}


