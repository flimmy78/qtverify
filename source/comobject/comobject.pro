
TEMPLATE	= lib
TARGET    = comobject
CONFIG += qt dll debug qtestlib thread

DEFINES	+= COMOBJECT_DLL QT_THREAD_SUPPORT

QMAKE_LIBDIR +=  ./           \
        	     $(ADEHOME)/lib \
	             $(ADEHOME)/bin 
	            
LIBS +=	-lprotocol -lalgorithm

DESTDIR = $(ADEHOME)\tmp\comobject\obj
#MOC_DIR = $(ADEHOME)/tmp/comobject/moc
OBJECTS_DIR = $(ADEHOME)/tmp/comobject/obj

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(ADEHOME_INC)/include \
									 $$(ADEHOME_INC)/include/qextserial

HEADERS	+= $$(ADEHOME_INC)/include/comobject.h \
        	 $$(ADEHOME_INC)/include/qextserial/qextserialport_global.h  \
        	 $$(ADEHOME_INC)/include/qextserial/qextserialport.h	\
	
SOURCES	+= source/comobject.cpp  \
	         $$(ADEHOME_INC)/include/qextserial/qextserialport.cpp \

win32 {
     SOURCES += $$(ADEHOME_INC)/include/qextserial/qextserialport_win.cpp
}

unix {
     SOURCES += $$(ADEHOME_INC)/include/qextserial/qextserialport_unix.cpp
}

					          
win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(ADEHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(ADEHOME)\dll \
				  & copy .\language\comobject_zh.qm $(ADEHOME)\uif\i18n\zh \
                  & copy .\language\comobject_en.qm $(ADEHOME)\uif\i18n\en 
}

TRANSLATIONS =  \
		language/comobject_zh.ts language/comobject_en.ts
		
