
TEMPLATE	= lib
TARGET    = comobject
CONFIG += qt dll debug qtestlib thread

DEFINES	+= COMOBJECT_DLL QT_THREAD_SUPPORT

QMAKE_LIBDIR +=  ./           \
        	     $(RUNHOME)/lib \
	             $(RUNHOME)/bin 
	            
LIBS +=	-lQt3Supportd4 -lQt3Support4 -lprotocol -lsystemsetdlg

DESTDIR = $(RUNHOME)\tmp\comobject\obj
#MOC_DIR = $(RUNHOME)/tmp/comobject/moc
OBJECTS_DIR = $(RUNHOME)/tmp/comobject/obj

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(RUNHOME_INC)/include \
									 $$(RUNHOME_INC)/include/qextserial

HEADERS	+= $$(RUNHOME_INC)/include/comobject.h \
        	 $$(RUNHOME_INC)/include/qextserial/qextserialport_global.h  \
        	 $$(RUNHOME_INC)/include/qextserial/qextserialport.h	\
	
SOURCES	+= source/comobject.cpp  \
	         $$(RUNHOME_INC)/include/qextserial/qextserialport.cpp \

win32 {
     SOURCES += $$(RUNHOME_INC)/include/qextserial/qextserialport_win.cpp
}

unix {
     SOURCES += $$(RUNHOME_INC)/include/qextserial/qextserialport_unix.cpp
}

					          
win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(RUNHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(RUNHOME)\dll
}

TRANSLATIONS =  \
		language/comobject_zh.ts language/comobject_en.ts
		
