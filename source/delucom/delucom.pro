CONFIG  += serialport
CONFIG  += qt warn_on debug
TARGET = delucom
TEMPLATE = app

INCLUDEPATH += $$(ADEHOME_INC)/include/qextserial\
				$$(ADEHOME_INC)/include
				
SOURCES += main.cpp\
        mainwindow.cpp \
        aboutdialog.cpp \
        $$(ADEHOME_INC)/include/qextserial/qextserialport.cpp

HEADERS += mainwindow.h \
        aboutdialog.h \
        $$(ADEHOME_INC)/include/qextserial/qextserialport_global.h \
        $$(ADEHOME_INC)/include/qextserial/qextserialport.h

QMAKE_LIBDIR +=  ./           \
		 $(ADEHOME)/lib \
		 $(ADEHOME)/bin

LIBS += -lalgorithm

win32:debug{
	CONFIG += console
}

win32 {
     SOURCES += $$(ADEHOME_INC)/include/qextserial/qextserialport_win.cpp
}

unix {
     SOURCES += $$(ADEHOME_INC)/include/qextserial/qextserialport_unix.cpp
}

FORMS += mainwindow.ui \
         aboutdialog.ui

RESOURCES += images.qrc
    
RC_FILE += myico.rc

OTHER_FILES += myico.rc

win32{
DEFINES += WIN32 _AFXDLL
DEFINES -= _USRDLL
DESTDIR = $(ADEHOME)\tmp\delucom\obj
}

#MOC_DIR = $(ADEHOME)/tmp/delucom/moc
OBJECTS_DIR = $(ADEHOME)/tmp/delucom/obj
#UI_DIR = $(ADEHOME)/tmp/delucom/ui

TRANSLATIONS += ./language/delucom_en.ts ./language/delucom_zh.ts

win32{
	MY_DEST_EXE_VAR = $${DESTDIR} $${TARGET}.exe
	MY_DEST_EXE = $$join( MY_DEST_EXE_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_EXE} $(ADEHOME)\bin	\
                  & copy .\language\delucom_zh.qm $(ADEHOME)\uif\i18n\zh	\
                  & copy .\language\delucom_en.qm $(ADEHOME)\uif\i18n\en
}
