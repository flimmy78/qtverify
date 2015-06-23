TEMPLATE = lib
CONFIG += dll console debug
DEFINES += PROTOCOL_DLL
TARGET = protocol
DEPENDPATH += .
INCLUDEPATH += ./		\
               $$(ADEHOME_INC)/include

QMAKE_LIBDIR +=  ./             \
        	  		 $(ADEHOME)/lib \
	          		 $(ADEHOME)/bin \

LIBS += -lalgorithm
# Input
HEADERS += $$(ADEHOME_INC)/include/protocol.h

SOURCES += protocol.cpp


win32{
DEFINES += WIN32 _AFXDLL
DEFINES -= _USRDLL
DESTDIR = $(ADEHOME)\tmp\protocol\obj
}

win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $(ADEHOME)\lib \
                  & copy $${MY_DEST_DLL} $(ADEHOME)\dll
}
