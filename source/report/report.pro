DEFINES += REPORT_DLL
QT       += core
QT       -= gui
TEMPLATE = lib
TARGET = report
CONFIG += dll console debug

DEPENDPATH += .
INCLUDEPATH += ./		\
               $$(RUNHOME_INC)/include

HEADERS += \
	$$(RUNHOME_INC)/include/report.h

SOURCES += \
	report.cpp
	
QMAKE_LIBDIR +=  ./             \
        	  		 $(RUNHOME)/lib \
	          		 $(RUNHOME)/bin \
					 
win32{
DEFINES += WIN32 _AFXDLL
DEFINES -= _USRDLL
DESTDIR = $(RUNHOME)\tmp\report\obj
}

win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $(RUNHOME)\lib \
                  & copy $${MY_DEST_DLL} $(RUNHOME)\dll
}