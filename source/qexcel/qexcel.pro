DEFINES += QEXCEL_DLL
QT       += core
QT       -= gui
TEMPLATE = lib
TARGET = qexcel
CONFIG += qaxcontainer
CONFIG += dll console debug

DEPENDPATH += .
INCLUDEPATH += ./		\
               $$(ADEHOME_INC)/include

HEADERS += \
	$$(ADEHOME_INC)/include/qexcel.h

SOURCES += \
	qexcel.cpp
	
QMAKE_LIBDIR +=  ./             \
        	  		 $(ADEHOME)/lib \
	          		 $(ADEHOME)/bin \
					 
win32{
DEFINES += WIN32 _AFXDLL
DEFINES -= _USRDLL
DESTDIR = $(ADEHOME)\tmp\qexcel\obj
}

win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $(ADEHOME)\lib \
                  & copy $${MY_DEST_DLL} $(ADEHOME)\dll
}