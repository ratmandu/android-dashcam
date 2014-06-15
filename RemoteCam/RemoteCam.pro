TEMPLATE = app

QT += qml quick multimedia positioning network sensors

SOURCES += main.cpp \
    imagesource.cpp \
    qandroidmultimediautils.cpp \
    imageserver.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml

HEADERS += \
    imagesource.h \
    qandroidmultimediautils.h \
    imageserver.h
