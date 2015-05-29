TEMPLATE	= lib
TARGET    = tvercompparamdlg
CONFIG += qt dll debug thread qtestlib
QT += sql

DEFINES	+= TVERCOMPPARAMDLG_DLL

QMAKE_LIBDIR +=  ./           \
        	     $(ADEHOME)/lib \
	             $(ADEHOME)/bin 

LIBS +=	-lprotocol -lsystemsetdlg -lcomobject -lqtexdb -lalgorithm

DESTDIR = $(ADEHOME)\tmp\tvercompparamdlg
#MOC_DIR = $(ADEHOME)/tmp/tvercompparamdlg/moc
OBJECTS_DIR = $(ADEHOME)/tmp/tvercompparamdlg/obj
UI_DIR = $(ADEHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(ADEHOME_INC)/include	\
									 $$(ADEHOME_INC)/include/qextserial

HEADERS	+= $$(ADEHOME_INC)/include/tvercompparamdlg.h 

SOURCES	+= tvercompparamdlg.cpp

FORMS	+= ui/tvercomp_param.ui

#RESOURCES += tvercompparamdlg.qrc   

win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(ADEHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(ADEHOME)\dll \
				  & copy .\language\tvercomp_param_zh.qm $(ADEHOME)\uif\i18n\zh \
                  & copy .\language\tvercomp_param_en.qm $(ADEHOME)\uif\i18n\en 
}

TRANSLATIONS =  \
		language/tvercomp_param_zh.ts language/tvercomp_param_en.ts \
		
