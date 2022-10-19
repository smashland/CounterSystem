QT += quick texttospeech charts serialport network multimedia core xml

CONFIG += c++11

TARGET = CounterSystem

SDK_CONFIG *= Map Gis proto qrcode
include($$PWD/SoftSDK.pri)
DEFINES += QAPPLICATION_CLASS=QApplication

win32{
 RC_FILE = CounterSys_Version.rc

 DESTDIR = $${PWD}/../Bin
}else{
  VERSION = 2.0.0
}

SOURCES += \
        Src/API-CRCheck.cpp \
        Src/AppGlobal.cpp \
        Src/ConfigInfo.cpp \
        Src/Connection/Connection.cpp \
        Src/Connection/ConnectionManager.cpp \
        Src/Connection/SerialConnection.cpp \
        Src/Connection/WifiConnection.cpp \
        Src/DataManager/Config.pb.cc \
        Src/DataManager/DataManager.cpp \
        Src/DataManager/GlobalData.cpp \
        Src/DataManager/GroupStatus.cpp \
        Src/DataManager/MyListModel.cpp \
        Src/DataManager/PersonAllInfo.cpp \
        Src/DataManager/PersonInfo.pb.cc \
        Src/DataManager/PersonStatus.cpp \
        Src/DataManager/TypeDefine.pb.cc \
        Src/DataManager/ini_file.cpp \
        Src/ErrorReport.cpp \
        Src/Export/ExportResult.cpp \
        Src/Export/WordProcessingMerger.cpp \
        Src/JudgeValid/Blur.cpp \
        Src/JudgeValid/GetMachineInfo.cpp \
        Src/JudgeValid/HardDriveSerialNumber.cpp \
        Src/JudgeValid/JudgeLicense.cpp \
        Src/JudgeValid/MyRectageItem.cpp \
        Src/Map/ContrlMapPerson.cpp \
        Src/Map/PlaceNodeInfo.cpp \
        Src/Notice/NoticeManager.cpp \
        Src/Notice/PlayMp3.cpp \
        Src/Notice/ShowNotice.cpp \
        Src/Notice/SpeakText.cpp \
        Src/ParseData/DealDataManager.cpp \
        Src/ParseData/MyParse/MyEventInfo.cpp \
        Src/ParseData/MyParse/MyQueryEquipment.cpp \
        Src/ParseData/MyParse/MySetQuipment.cpp \
        Src/ParseData/MyParseData.cpp \
        Src/ParseData/ParseData.cpp \
        Src/SceInfo/SceInfo.cpp \
        Src/SceInfo/SceManager.cpp \
        Src/SceInfo/ScePersonInfo.cpp \
        Src/Settings/CSetEarth.cpp \
        Src/Settings/EarthManager.cpp \
        Src/Settings/GlobalSettings.cpp \
        Src/TimeServer/TimeServer.cpp \
        Src/XmlNode/TestXml.cpp \
        Src/md5.cpp \
        main.cpp

RESOURCES += qml.qrc

TRANSLATIONS += \
    CounterSystem_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Src/API-CRCheck.h \
    Src/AppGlobal.h \
    Src/CommonTypeDefine.h \
    Src/ConfigInfo.h \
    Src/Connection/Connection.h \
    Src/Connection/ConnectionManager.h \
    Src/Connection/SerialConnection.h \
    Src/Connection/WifiConnection.h \
    Src/DataManager/Config.pb.h \
    Src/DataManager/DataManager.h \
    Src/DataManager/GlobalData.h \
    Src/DataManager/GroupStatus.h \
    Src/DataManager/IDataManagerObserver.h \
    Src/DataManager/MyListModel.h \
    Src/DataManager/PersonAllInfo.h \
    Src/DataManager/PersonInfo.pb.h \
    Src/DataManager/PersonStatus.h \
    Src/DataManager/TypeDefine.pb.h \
    Src/DataManager/ini_file.h \
    Src/ErrorReport.h \
    Src/Export/ExportResult.h \
    Src/Export/WordProcessingMerger.h \
    Src/Export/dfw.h \
    Src/JudgeValid/Blur.h \
    Src/JudgeValid/GetMachineInfo.h \
    Src/JudgeValid/HardDriveSerialNumber.h \
    Src/JudgeValid/JudgeLicense.h \
    Src/JudgeValid/MyRectageItem.h \
    Src/Map/ContrlMapPerson.h \
    Src/Map/PlaceNodeInfo.h \
    Src/Notice/NoticeManager.h \
    Src/Notice/PlayMp3.h \
    Src/Notice/ShowNotice.h \
    Src/Notice/SpeakText.h \
    Src/ParseData/DealDataManager.h \
    Src/ParseData/MyParse/MyEventInfo.h \
    Src/ParseData/MyParse/MyParsetype.h \
    Src/ParseData/MyParse/MyQueryEquipment.h \
    Src/ParseData/MyParse/MySetQuipment.h \
    Src/ParseData/MyParseData.h \
    Src/ParseData/ParseData.h \
    Src/SceInfo/SceInfo.h \
    Src/SceInfo/SceManager.h \
    Src/SceInfo/ScePersonInfo.h \
    Src/Settings/CSetEarth.h \
    Src/Settings/EarthManager.h \
    Src/Settings/GlobalSettings.h \
    Src/TimeServer/ITimeObserver.h \
    Src/TimeServer/TimeServer.h \
    Src/XmlNode/TestXml.h \
    Src/md5.h

FORMS += \
    Src/Notice/ShowNotice.ui
