TEMPLATE = lib
CONFIG += qt thread dll debug
TARGET = readstdmeter
DEFINES += READSTDMETER_DLL

DEPENDPATH += .
INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(ADEHOME_INC)/include	\
									 $$(ADEHOME_INC)/include/qextserial

QMAKE_LIBDIR +=  ./             \
        	  		 $(ADEHOME)/lib \
	          		 $(ADEHOME)/bin \

LIBS += -lalgorithm -lcomobject -lsystemsetdlg

# Input
HEADERS += $$(ADEHOME_INC)/include/readstdmeter.h
SOURCES += readstdmeter.cpp

win32{
DEFINES += WIN32 _AFXDLL
DEFINES -= _USRDLL
DESTDIR = $(ADEHOME)\tmp\readstdmeter\obj
}

win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $(ADEHOME)\lib \
                  & copy $${MY_DEST_DLL} $(ADEHOME)\dll
}