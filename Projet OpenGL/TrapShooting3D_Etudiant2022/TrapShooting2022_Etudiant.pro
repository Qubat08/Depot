CONFIG *=  app

siteDptInfo {
    myDIR = $$PWD/..
}
else:configCISS {
    myDIR = R:/Stephanie
}
else {
    myDIR = D:/Steph/Lib
}

libName = QGLShaderViewer



TARGET = TrapShooting_Etudiant
DESTDIR = ./


# ---- Config Qt
# ------------------------
QT     += core gui widgets
QT     += opengl xml
CONFIG += console


DEPENDPATH += . src/glm
OBJECTS_DIR = ./obj
MOC_DIR     = ./obj
UI_DIR      = ./obj


INCLUDEPATH           += $$PWD/src


# --- sources
    SOURCES += \
        src/Viewer.cc \
        src/main.cpp \


    HEADERS += \
        src/Viewer.h \


    SOURCES +=  src/BallTarget.cc
    HEADERS +=  src/BallTarget.h


#    SOURCES +=  src/ART/ArtTracker.cc
#    HEADERS +=  src/ART/ArtTracker.h



# --- DTRACK
DTRACKSDK_PATH = $$PWD/../SDK
INCLUDEPATH += $${DTRACKSDK_PATH}

SOURCES += \
    $${DTRACKSDK_PATH}/DTrack/DTrackNet.cpp \
    $${DTRACKSDK_PATH}/DTrack/DTrackParse.cpp \
    $${DTRACKSDK_PATH}/DTrack/DTrackParser.cpp \
    $${DTRACKSDK_PATH}/DTrack/DTrackSDK.cpp \

HEADERS += \
    $${DTRACKSDK_PATH}/DTrack/DTrackDataTypes.h \
    $${DTRACKSDK_PATH}/DTrack/DTrackNet.h \
    $${DTRACKSDK_PATH}/DTrack/DTrackParse.hpp \
    $${DTRACKSDK_PATH}/DTrack/DTrackParser.hpp \
    $${DTRACKSDK_PATH}/DTrack/DTrackSDK.hpp \



# --- Ajout des Lib
# -----------------------
  # --- libQGLShaderViewer
        libTrapShootingPATH = $$PWD/libTrapShooting

message ( libTrapShootingPATH  ->   $${libTrapShootingPATH} )
        INCLUDEPATH *= $${libTrapShootingPATH}/include
        LIBS        += -L$${libTrapShootingPATH}/lib  -lTrapShooting2019_DLL


  # --- libQGLShaderViewer
        QGLShaderViewerPATH = $$PWD/../libQGLShaderViewer
        INCLUDEPATH *= $${QGLShaderViewerPATH}/include
        INCLUDEPATH *= $${QGLShaderViewerPATH}/include/Material
        INCLUDEPATH *= $${QGLShaderViewerPATH}/include/Effect

        message( QGLShaderViewerPATH  -> $${QGLShaderViewerPATH} )
        DEFINES += APP_QGLShaderViewerLibPath=\"\\\"$${QGLShaderViewerPATH}\\\"\"
        LIBS    += -L$${QGLShaderViewerPATH}/lib  -lQGLShaderViewer


  # --- OpenGL Glu
    LIBS += -lopengl32 -lglu32



  # --- Socket
win32 {
  DEFINES += "_WIN32_WINNT=0x0600"
  LIBS += -lws2_32
}
