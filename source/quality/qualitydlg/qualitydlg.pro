
TEMPLATE	= lib
TARGET    = qualitydlg
CONFIG += qt dll debug qtestlib

DEFINES	+= QUALITYDLG_DLL

QMAKE_LIBDIR +=  ./           \
        	     $(RUNHOME)/lib \
	             $(RUNHOME)/bin 
	            
LIBS +=	-lQt3Supportd4 -lQt3Support4 -lprotocol -lcomsetdlg

DESTDIR = $(RUNHOME)\tmp\quality\qualitydlg\obj
#MOC_DIR = $(RUNHOME)/tmp/quality/qualitydlg/moc
OBJECTS_DIR = $(RUNHOME)/tmp/quality/qualitydlg/obj
UI_DIR = $(RUNHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(RUNHOME_INC)/include \
									 $$(RUNHOME_INC)/include/qextserial

HEADERS	+= $$(RUNHOME_INC)/include/qualitydlg_global.h \
           $$(RUNHOME_INC)/include/qualitydlg.h \
           $$(RUNHOME_INC)/include/parasetdlg.h \ 
        	 $$(RUNHOME_INC)/include/qextserial/qextserialport_global.h  \
        	 $$(RUNHOME_INC)/include/qextserial/qextserialport.h	\
        	 $$(RUNHOME_INC)/include/comthread.h
	
SOURCES	+= source/qualitydlg.cpp  \
					 source/parasetdlg.cpp  \
	         $$(RUNHOME_INC)/include/qextserial/qextserialport.cpp \
	         source/comthread.cpp

win32 {
     SOURCES += $$(RUNHOME_INC)/include/qextserial/qextserialport_win.cpp
}

unix {
     SOURCES += $$(RUNHOME_INC)/include/qextserial/qextserialport_unix.cpp
}

					 
FORMS	+= ui/qualitydlg.ui \
         ui/parasetdlg.ui
     
RESOURCES += qualitydlg.qrc     
         
win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(RUNHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(RUNHOME)\dll
}

TRANSLATIONS =  \
		language/qualitydlg_zh.ts language/qualitydlg_en.ts
		
