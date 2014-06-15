TEMPLATE = app

QT += qml quick widgets network sensors multimedia

SOURCES += main.cpp \
    imageclient.cpp \
    imageprovider.cpp \
    connectorclass.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    imageclient.h \
    imageprovider.h \
    connectorclass.h

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml
