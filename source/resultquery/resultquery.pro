DEFINES	+= RESULTQUERYDLG_DLL
TEMPLATE	= lib
QT         += xml sql
TARGET    = resultquerydlg
CONFIG += qt dll debug

QMAKE_LIBDIR +=  ./           \
        	     $(ADEHOME)/lib \
	             $(ADEHOME)/bin

LIBS += -lqtexdb -lalgorithm -lreport	           

DESTDIR = $(ADEHOME)\tmp\resultquerydlg\obj
OBJECTS_DIR = $(ADEHOME)/tmp/resultquerydlg/obj
UI_DIR = $(ADEHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 $$(ADEHOME_INC)/include

HEADERS	+= $$(ADEHOME_INC)/include/resultquery_globlal.h   \
		   $$(ADEHOME_INC)/include/flow_result.h   \
		   $$(ADEHOME_INC)/include/platinum_result.h  \
		   $$(ADEHOME_INC)/include/calculator_result.h \
		   $$(ADEHOME_INC)/include/cmb_result.h \
		   $$(ADEHOME_INC)/include/total_result.h \
		   $$(ADEHOME_INC)/include/water_result.h

SOURCES	+= source/flow_result.cpp \
		   source/platinum_result.cpp \
		   source/calculator_result.cpp \
		   source/cmb_result.cpp \
		   source/total_result.cpp \
		   source/water_result.cpp 

FORMS	+= ui/flowresult.ui  \
		 ui/platinum_result.ui \
		 ui/calculator_result.ui \
		 ui/cmb_result.ui \
		 ui/total_result.ui \
		 ui/water_result.ui

RESOURCES += resultquery.qrc

win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(ADEHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(ADEHOME)\dll \
                  & copy .\language\resultquerydlg_zh.qm $(ADEHOME)\uif\i18n\zh	\
                  & copy .\language\resultquerydlg_en.qm $(ADEHOME)\uif\i18n\en
}

TRANSLATIONS =  \
		language/resultquerydlg_zh.ts language/resultquerydlg_en.ts
