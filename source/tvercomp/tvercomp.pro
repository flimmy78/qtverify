DEFINES	+= TVERCOMP_DLL
TEMPLATE = lib
TARGET   = tvercomp
CONFIG += qt dll debug thread qtestlib
QT += sql

QMAKE_LIBDIR +=  ./           \
        	     $(RUNHOME)/lib \
	             $(RUNHOME)/bin 
	            
LIBS +=	-lQt3Supportd4 -lQt3Support4 -lprotocol -lsystemsetdlg -lcomobject -lqtexdb -lalgorithm -ltvercompparamDlg -lqtexdb

DESTDIR = $(RUNHOME)\tmp\tvercomp
#MOC_DIR = $(RUNHOME)/tmp/tvercomp/moc
OBJECTS_DIR = $(RUNHOME)/tmp/tvercomp/obj
UI_DIR = $(RUNHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(RUNHOME_INC)/include	\
									 $$(RUNHOME_INC)/include/qextserial

HEADERS	+= $$(RUNHOME_INC)/include/tvercomp.h 

SOURCES	+= tvercomp.cpp

FORMS	+= ui/tvercomp.ui \
     
RESOURCES += tvercomp.qrc     
         
win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(RUNHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(RUNHOME)\dll \
                  & copy .\language\tvercomp_zh.qm $(RUNHOME)\uif\i18n\zh \
                  & copy .\language\tvercomp_en.qm $(RUNHOME)\uif\i18n\en \

}

TRANSLATIONS =  \
		language/tvercomp_zh.ts language/tvercomp_en.ts \
		language/tvercomp_param_zh.ts language/tvercomp_param_en.ts \
		
