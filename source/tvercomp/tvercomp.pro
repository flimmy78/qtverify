DEFINES	+= TVERCOMP_DLL
TEMPLATE = lib
TARGET   = tvercomp
CONFIG += qt dll debug thread
QT += sql

QMAKE_LIBDIR +=  ./           \
        	     $(ADEHOME)/lib \
	             $(ADEHOME)/bin 
	            
LIBS +=	-lprotocol -lsystemsetdlg -lcomobject -lqtexdb -lalgorithm -lqtexdb

DESTDIR = $(ADEHOME)\tmp\tvercomp
#MOC_DIR = $(ADEHOME)/tmp/tvercomp/moc
OBJECTS_DIR = $(ADEHOME)/tmp/tvercomp/obj
UI_DIR = $(ADEHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(ADEHOME_INC)/include	\
									 $$(ADEHOME_INC)/include/qextserial

HEADERS	+= $$(ADEHOME_INC)/include/tvercomp.h \
           $$(ADEHOME_INC)/include/tvercompparamdlg.h 

SOURCES	+= tvercomp.cpp \
           tvercompparamdlg.cpp     

FORMS	+= ui/tvercomp.ui \
         ui/tvercomp_param.ui
     
RESOURCES += tvercomp.qrc     
         
win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(ADEHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(ADEHOME)\dll \
                  & copy .\language\tvercomp_zh.qm $(ADEHOME)\uif\i18n\zh \
                  & copy .\language\tvercomp_en.qm $(ADEHOME)\uif\i18n\en \

}

TRANSLATIONS =  \
		language/tvercomp_zh.ts language/tvercomp_en.ts \
		
