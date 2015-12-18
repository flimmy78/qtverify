TEMPLATE = app
TARGET   = pseudo
DEFINES += PSEUDO_DLL
CONFIG += qt warn_on debug

INCLUDEPATH	 +=  ./ \
				$$(ADEHOME_INC)/include  \
                $$(ADEHOME_INC)/include/qextserial

QMAKE_LIBDIR += \
              $$(ADEHOME)/lib \
              $$(ADEHOME)/bin

LIBS	+= -lqtexdb -lalgorithm -llibxl -lqexcel

HEADERS += pseudo.h

SOURCES	+= main.cpp \
		   pseudo.cpp

FORMS	+= pseudo.ui

MOC_DIR = $(ADEHOME)/tmp/pseudo/moc
OBJECTS_DIR = $(ADEHOME)/tmp/pseudo/obj
UI_DIR = $(ADEHOME_INC)/include

win32:debug{
	CONFIG += console
}

win32{
DEFINES += WIN32 _AFXDLL
DEFINES -= _USRDLL
DESTDIR = $(ADEHOME)\tmp\pseudo\obj
}

win32{
	MY_DEST_EXE_VAR = $${DESTDIR} $${TARGET}.exe
	MY_DEST_EXE = $$join( MY_DEST_EXE_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_EXE} $$(ADEHOME)\bin
}