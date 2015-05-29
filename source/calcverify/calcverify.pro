
TEMPLATE	= lib
TARGET    = calcverify
CONFIG += qt dll debug thread qtestlib
QT += sql

DEFINES	+= CALCVERIFY_DLL QT_THREAD_SUPPORT

QMAKE_LIBDIR +=  ./           \
        	     $(ADEHOME)/lib \
	             $(ADEHOME)/bin 
	            
LIBS +=	-lprotocol -lsystemsetdlg -lcomobject -lqtexdb -lalgorithms

DESTDIR = $(ADEHOME)\tmp\calcverify
#MOC_DIR = $(ADEHOME)/tmp/calcverify/moc
OBJECTS_DIR = $(ADEHOME)/tmp/calcverify/obj
UI_DIR = $(ADEHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(ADEHOME_INC)/include	\
									 $$(ADEHOME_INC)/include/qextserial

HEADERS	+= $$(ADEHOME_INC)/include/calcverify.h \
           $$(ADEHOME_INC)/include/calcpara.h 
	
SOURCES	+= calcverify.cpp \
           calcpara.cpp 

					 
FORMS	+= calcverify.ui \
         calcpara.ui
     
RESOURCES += calcverify.qrc     
         
win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(ADEHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(ADEHOME)\dll \
                  & copy .\language\calcverify_zh.qm $(ADEHOME)\uif\i18n\zh \
                  & copy .\language\calcverify_en.qm $(ADEHOME)\uif\i18n\en 

}

TRANSLATIONS =  \
		language/calcverify_zh.ts language/calcverify_en.ts
		
