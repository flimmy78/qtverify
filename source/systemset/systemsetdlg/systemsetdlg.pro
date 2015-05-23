DEFINES	+= SYSTEMSETDLG_DLL
TEMPLATE	= lib
QT         += xml sql
TARGET    = systemsetdlg
CONFIG += qt dll debug

DEFINES	+= SYSTEMSETDLG_DLL

QMAKE_LIBDIR +=  ./           \
        	     $(RUNHOME)/lib \
	             $(RUNHOME)/bin
	             
LIBS += -lQt3Supportd4 -lQt3Support4 -lqtexdb -lalgorithm	           

DESTDIR = $(RUNHOME)\tmp\systemset\systemsetdlg\obj
#MOC_DIR = $(RUNHOME)/tmp/systemset/systemsetdlg/moc
OBJECTS_DIR = $(RUNHOME)/tmp/systemset/systemsetdlg/obj
UI_DIR = $(RUNHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(RUNHOME_INC)/include \
									 $$(RUNHOME_INC)/include/qextserial


HEADERS	+= $$(RUNHOME_INC)/include/qextserial/qextserialport_global.h  \
        	 $$(RUNHOME_INC)/include/qextserial/qextserialport.h \
					 $$(RUNHOME_INC)/include/systemsetdlg_global.h   \
					 $$(RUNHOME_INC)/include/setcomDlg.h   \
		   		 $$(RUNHOME_INC)/include/setportfrm.h  \
		   		 $$(RUNHOME_INC)/include/readcomconfig.h \
           $$(RUNHOME_INC)/include/stdmtrparaset.h \
           $$(RUNHOME_INC)/include/stdmtrcoecorrect.h \
           $$(RUNHOME_INC)/include/parasetdlg.h \
		   $$(RUNHOME_INC)/include/stdplasensor.h \
		   $$(RUNHOME_INC)/include/chkplasensor.h 

	
SOURCES	+= $$(RUNHOME_INC)/include/qextserial/qextserialport.cpp \
					 source/setcomDlg.cpp \
			     source/setportfrm.cpp \
			     source/readcomconfig.cpp \
      		 source/stdmtrparaset.cpp \
      		 source/stdmtrcoecorrect.cpp \
      		 source/parasetdlg.cpp \
			 source/stdplasensor.cpp \
			 source/chkplasensor.cpp 
			 

win32 {
     SOURCES += $$(RUNHOME_INC)/include/qextserial/qextserialport_win.cpp
}

unix {
     SOURCES += $$(RUNHOME_INC)/include/qextserial/qextserialport_unix.cpp
}
					 
FORMS	+= ui/setcomDlg.ui  \
		     ui/setportfrm.ui \
         ui/stdmtrparaset.ui \
         ui/stdmtrcoecorrect.ui \
         ui/parasetdlg.ui \
		 ui/stdplasensor.ui \
		 ui/chkplasensor.ui


win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(RUNHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(RUNHOME)\dll \
                  & copy .\language\systemsetdlg_zh.qm $(RUNHOME)\uif\i18n\zh	\
                  & copy .\language\systemsetdlg_en.qm $(RUNHOME)\uif\i18n\en
}

TRANSLATIONS =  \
		language/systemsetdlg_zh.ts language/systemsetdlg_en.ts
		
