TEMPLATE = lib
CONFIG += dll debug
TARGET = usermanagedlg

QT += sql

DEPENDPATH += .
INCLUDEPATH  	+=    ./      \
									 include \ 
									 $$(ADEHOME_INC)/include
									 
DEFINES	+= USERMANAGEDLG_DLL

QMAKE_LIBDIR +=  ./             \
        	  		 $(ADEHOME)/lib \
	          		 $(ADEHOME)/bin 
	          		 
LIBS += -lqtexdb	          		 

UI_DIR = $(ADEHOME_INC)/include

# Input
HEADERS += $$(ADEHOME_INC)/include/usermanagedlg.h
SOURCES += usermanagedlg.cpp
FORMS += usermanagedlg.ui

win32{
DEFINES += WIN32 _AFXDLL
DEFINES -= _USRDLL
DESTDIR = $(ADEHOME)\tmp\usermanagedlg\obj
}

win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $(ADEHOME)\lib \
                  & copy $${MY_DEST_DLL} $(ADEHOME)\dll \
                  & copy .\language\usermanagedlg_zh.qm $(ADEHOME)\uif\i18n\zh \
                  & copy .\language\usermanagedlg_en.qm $(ADEHOME)\uif\i18n\en 
}

TRANSLATIONS =  \
		language/usermanagedlg_zh.ts language/usermanagedlg_en.ts
