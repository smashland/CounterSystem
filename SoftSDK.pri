# Attention Debug   version always suffix with a d,
#           Release version always not.
# For example
# CONFIG(debug, debug|release){
#         LIBS += -losgd
#}else{
#         LIBS += -losg
#}
#
#Attention DLLDESTDIR only useful in windows
#          This will only copy exe or dll to DLLDESTDIR
include($$PWD/Path.pri)
include($$PWD/Src/SingleApplication/singleapplication.pri)
QMAKE_CXXFLAGS += /utf-8
QMAKE_CXXFLAGS += /wd"4100"
QMAKE_CXXFLAGS += /MP
LIBS *= -L$$PWD -lDocxFactory
contains(SDK_CONFIG,Map){

# include file
    INCLUDEPATH *=$${NEWGL3PATH}/include
    INCLUDEPATH *= $${PWD}/../../Gitee/Map/Inc
    LIBS *= -L$${PWD}/../../Gitee/Map/Lib

   CONFIG (debug, debug|release){
       LIBS *= -lSceneCored -lExternShaped
   }else{
       LIBS *= -lSceneCore -lExternShape
   }
}

contains(SDK_CONFIG,Gis){
   INCLUDEPATH *= $${PWD}/../../Gitee/VersionMath/Inc
   INCLUDEPATH *= $${PWD}/../../Gitee/VersionMath/Inc/Math
   LIBS *= -L$${PWD}/../../Gitee/VersionMath/Lib

   CONFIG (debug, debug|release){
       LIBS *= -lGisMathD
   }else{
       LIBS *= -lGisMath
   }
}

contains(SDK_CONFIG,proto){
LIBS *= -L$${NEWGL3PATH}/lib
    CONFIG (debug, debug|release){
       LIBS *= -llibprotobufd
    }else{
       LIBS *= -llibprotobuf
    }
}

contains(SDK_CONFIG,qrcode){
LIBS *= -L$${NEWGL3PATH}/lib
    CONFIG (debug, debug|release){
       LIBS *= -lqrencoded
    }else{
       LIBS *= -lqrencode
    }
}
# This can suffix a d by itself,if is a debug version
CONFIG(debug, debug|release) {
  TARGET = $$join(TARGET,,,d)
}
