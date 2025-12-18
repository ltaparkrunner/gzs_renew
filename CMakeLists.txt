cmake_minimum_required(VERSION 3.14)

project(gaz_mixer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick Charts Network Test SerialPort Window)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick Charts Network Test SerialPort QmlModels)
message("QT_VERSION_MAJOR= ${QT_VERSION_MAJOR}" )

#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Charts Network Test SerialPort Window)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Charts Network Test SerialPort QmlModels)
set(src_dir "src/")
set(inc_dir "inc/")

set_property(SOURCE ${src_dir}tableModel.cpp PROPERTY SKIP_AUTOMOC ON)
if(QT_VERSION_MAJOR EQUAL 6)
    set(PROJECT_SOURCES
        ${src_dir}main.cpp
        ${src_dir}master.cpp
        ${src_dir}wfiles.cpp
#        ${src_dir}calcMixture.cpp
#        ${src_dir}coefftable.cpp
        ${src_dir}combotable.cpp
        ${src_dir}calibrtable.cpp
        ${src_dir}simpletable.cpp
#        ${src_dir}max_flow_rate.cpp
        ${src_dir}params.cpp
        ${src_dir}tableModel.cpp
        ${src_dir}monitoring.cpp
        ${src_dir}serial.cpp
        ${src_dir}i87000_lnx.cpp
        ${src_dir}station.cpp
        qml/qml.qrc
        ${inc_dir}main.h
        ${inc_dir}master.h
        ${inc_dir}wfiles.h
#        ${inc_dir}calcMixture.h
#        ${inc_dir}coefftable.h
        ${inc_dir}combotable.h
        ${inc_dir}calibrtable.h
        ${inc_dir}simpletable.h
#        ${inc_dir}max_flow_rate.h
        ${inc_dir}params.h
        ${inc_dir}monitoring.h
        ${inc_dir}serial.h
        ${inc_dir}i87000_lnx.h
        ${inc_dir}station.h
    )
elseif(QT_VERSION_MAJOR EQUAL 5)
    set(PROJECT_SOURCES
        ${src_dir}main.cpp
        ${src_dir}master.cpp
        ${src_dir}wfiles.cpp
#        ${src_dir}calcMixture.cpp
#        ${src_dir}coefftable.cpp
        ${src_dir}combotable.cpp
        ${src_dir}calibrtable.cpp
        ${src_dir}simpletable.cpp
#        ${src_dir}max_flow_rate.cpp
        ${src_dir}params.cpp
        ${src_dir}tableModel.cpp
        ${src_dir}monitoring.cpp
#        ${src_dir}mycppobject.cpp
        ${src_dir}serial.cpp
        ${src_dir}i87000_lnx.cpp
        ${src_dir}station.cpp
        qml/qml_5.qrc
        ${inc_dir}main.h
        ${inc_dir}master.h
        ${inc_dir}wfiles.h
#        ${inc_dir}calcMixture.h
#        ${inc_dir}coefftable.h
        ${inc_dir}combotable.h
        ${inc_dir}calibrtable.h
        ${inc_dir}simpletable.h
#        ${inc_dir}max_flow_rate.h
        ${inc_dir}params.h
        ${inc_dir}mycppobject.h
        ${inc_dir}monitoring.h
        ${inc_dir}serial.h
        ${inc_dir}i87000_lnx.h
        ${inc_dir}station.h
    )
else()
    message(FATAL_ERROR "Unsupported Qt version")
endif()

#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic")
add_executable(gaz_mixer  ${PROJECT_SOURCES}
    inc/clibinc.h
    inc/auxil.h
#    inc/max_flow_rate.h
#    src/max_flow_rate.cpp
)
#    src/station.h src/station.cpp)

target_compile_definitions(gaz_mixer PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(gaz_mixer PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick
#    Qt${QT_VERSION_MAJOR}::Charts Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Test Qt${QT_VERSION_MAJOR}::SerialPort -Wl,-Bstatic)
    Qt${QT_VERSION_MAJOR}::Charts Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Test Qt${QT_VERSION_MAJOR}::SerialPort
    Qt${QT_VERSION_MAJOR}::QmlModels "libi7k_64.so")
target_link_directories(gaz_mixer PRIVATE "lib")
target_include_directories(gaz_mixer PUBLIC "inc" "lib/include")
#target_include_directories(gaz_mixer PUBLIC "lib/include")
#if(QT_VERSION_MAJOR EQUAL 6)
#    qt_import_qml_plugins(gaz_mixer)
#    qt_finalize_executable(gaz_mixer)
#endif()
