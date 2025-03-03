QT = core network concurrent

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# 定义输出目录变量
PLATFORM_FOLDER =  # 初始化为空
win32:PLATFORM_FOLDER = windows_x86
win32:contains(QMAKE_HOST.arch, x86_64):PLATFORM_FOLDER = windows_x64
unix:!macx:PLATFORM_FOLDER = ubuntu

# 检查 PLATFORM_FOLDER 是否正确设置
isEmpty(PLATFORM_FOLDER) {
    error("Platform detection failed! Please check platform conditions.")
}
# 定义最终输出目录
CONFIG(debug,debug|release)
{
    OUTDIR = $$PWD/../bin/$$PLATFORM_FOLDER/Debug
}
CONFIG(release,debug|release){
    OUTDIR = $$PWD/../bin/$$PLATFORM_FOLDER/Release
}

# 设置可执行文件目录
DESTDIR = $$OUTDIR

INCLUDEPATH += \
    $$PWD/Api \
    $$PWD/Api/base \
    $$PWD/Http \
    $$PWD/Log \
    $$PWD/ThreadPool \
    $$PWD/Json

SOURCES += \
    $$PWD/Log/Logger.cpp \
    $$PWD/Api/base/api_service_base.cpp \
    $$PWD/Api/http_api_manager.cpp \
    $$PWD/Http/http_request_manager.cpp \
    $$PWD/Json/jsonoperate.cpp \
    main.cpp \
    $$PWD/Api/vote_service.cpp \
    $$PWD/Api/vote_service_handler.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    $$PWD/Log/Logger.h \
    $$PWD/Log/LoggerTemplate.h \
    ThreadPool.h \
    $$PWD/Api/base/api_response_handler.h \
    $$PWD/Api/base/api_service_base.h \
    $$PWD/Api/http_api_manager.h \
    $$PWD/Http/http_request_manager.h \
    $$PWD/Http/http_request_task.h \
    $$PWD/Json/jsonoperate.h \
    $$PWD/Api/vote_service.h \
    $$PWD/Api/vote_service_handler.h

# msvc >= 2017  编译器使用utf-8编码
msvc {
    greaterThan(QMAKE_MSC_VER, 1900){
        QMAKE_CFLAGS += /utf-8
        QMAKE_CXXFLAGS += /utf-8
    }
}
