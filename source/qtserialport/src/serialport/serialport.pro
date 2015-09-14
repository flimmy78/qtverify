QT = core

QMAKE_DOCS = $$PWD/doc/qtserialport.qdocconf
include($$PWD/serialport-lib.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(QtSerialPort$$QT_LIBINFIX)
include($$PWD/qt4support/install-helper.pri)
CONFIG += module create_prl
mac:QMAKE_FRAMEWORK_BUNDLE_NAME = $$TARGET

PRECOMPILED_HEADER =

DESTDIR = $(ADEHOME)\tmp\qserialport
#MOC_DIR = $(ADEHOME)/tmp/qserialport/moc
OBJECTS_DIR = $(ADEHOME)/tmp/qserialport/obj

win32{
	MY_DEST_LIB_VAR = $${DESTDIR} $${TARGET}.lib
	MY_DEST_LIB = $$join( MY_DEST_LIB_VAR, "\\" )
	MY_DEST_DLL_VAR = $${DESTDIR} $${TARGET}.dll
	MY_DEST_DLL = $$join( MY_DEST_DLL_VAR, "\\" )

	QMAKE_POST_LINK = copy $${MY_DEST_LIB} $$(ADEHOME)\lib \
                  & copy $${MY_DEST_DLL} $$(ADEHOME)\dll \
}