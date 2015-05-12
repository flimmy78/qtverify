DEFINES	+= RESULTQUERYDLG_DLL
TEMPLATE	= lib
QT         += xml sql
TARGET    = resultquerydlg
CONFIG += qt dll debug

QMAKE_LIBDIR +=  ./           \
        	     $(RUNHOME)/lib \
	             $(RUNHOME)/bin

LIBS += -lQt3Supportd4 -lQt3Support4 -lqtexdb -lalgorithm -lreport	           

DESTDIR = $(RUNHOME)\tmp\resultquerydlg\obj
OBJECTS_DIR = $(RUNHOME)/tmp/resultquerydlg/obj
UI_DIR = $(RUNHOME_INC)/include

INCLUDEPATH  	=    ./      \
									 include \ 
									 $$(RUNHOME_INC)/include \

HEADERS	+= $$(RUNHOME_INC)/include/resultquery_globlal.h   \
		   $$(RUNHOME_INC)/include/flowweight_result.h   \
		   $$(RUNHOME_INC)/include/placompare_result.h  \
		   $$(RUNHOME_INC)/include/plaparam_result.h \

SOURCES	+= source/flowweight_result.cpp \
		   source/placompare_result.cpp \
		   source/plaparam_result.cpp \

FORMS	+= ui/flowresult.ui  \
		 ui/placompare_result.ui \
         ui/plaparam_result.ui \

win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(RUNHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(RUNHOME)\dll \
                  & copy .\language\resultquerydlg_zh.qm $(RUNHOME)\uif\i18n\zh	\
                  & copy .\language\resultquerydlg_en.qm $(RUNHOME)\uif\i18n\en
}

TRANSLATIONS =  \
		language/resultquerydlg_zh.ts language/resultquerydlg_en.ts
