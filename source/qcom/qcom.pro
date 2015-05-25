#if QT_VERSION >= 0x050000
QT += core gui widgets
#else
QT += core gui
#endif

TARGET = qcom
TEMPLATE = app
CONFIG  += qt warn_on debug console

INCLUDEPATH += $$(ADEHOME_INC)/include/qextserial

SOURCES += main.cpp\
        mainwindow.cpp \
        aboutdialog.cpp \
        $$(ADEHOME_INC)/include/qextserial/qextserialport.cpp

HEADERS += mainwindow.h \
        aboutdialog.h \
        $$(ADEHOME_INC)/include/qextserial/qextserialport_global.h \
        $$(ADEHOME_INC)/include/qextserial/qextserialport.h

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
DESTDIR = $(ADEHOME)\tmp\qcom\obj
}

#MOC_DIR = $(ADEHOME)/tmp/qcom/moc
OBJECTS_DIR = $(ADEHOME)/tmp/qcom/obj
#UI_DIR = $(ADEHOME)/tmp/qcom/ui

TRANSLATIONS += ./language/qcom_en.ts ./language/qcom_zh.ts

win32{
	MY_DEST_EXE_VAR = $${DESTDIR} $${TARGET}.exe
	MY_DEST_EXE = $$join( MY_DEST_EXE_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_EXE} $(ADEHOME)\bin	\
                  & copy .\language\qcom_zh.qm $(ADEHOME)\uif\i18n\zh	\
                  & copy .\language\qcom_en.qm $(ADEHOME)\uif\i18n\en
}
