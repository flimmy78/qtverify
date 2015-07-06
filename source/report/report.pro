DEFINES += REPORT_DLL
QT       += core
QT       -= gui
QT		 += sql
TEMPLATE = lib
TARGET = report
CONFIG += dll debug

DEPENDPATH += .
INCLUDEPATH += ./		\
               $$(ADEHOME_INC)/include

HEADERS += \
	$$(ADEHOME_INC)/include/report.h

SOURCES += \
	report.cpp
	
QMAKE_LIBDIR +=  ./             \
        	  		 $(ADEHOME)/lib \
	          		 $(ADEHOME)/bin \
					 
LIBS += -lqexcel -llibxl -lqtexdb -lalgorithm
 					 
win32{
DEFINES += WIN32 _AFXDLL
DEFINES -= _USRDLL
DESTDIR = $(ADEHOME)\tmp\report\obj
}

win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $(ADEHOME)\lib \
                  & copy $${MY_DEST_DLL} $(ADEHOME)\dll
}