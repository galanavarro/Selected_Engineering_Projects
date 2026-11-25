cmake_minimum_required(VERSION 3.5)

project(ejemplo_opc_cliente VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(open62541 REQUIRED)

# ─── 1. PAQUETES AÑADIDOS PARA ROS2 (EJERCICIO 6) ───
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
# ───────────────────────────────────────────────────

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        worker.cpp worker.h
        definiciones.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ejemplo_opc_cliente
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(ejemplo_opc_cliente SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(ejemplo_opc_cliente
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# ─── 2. ENLACE DE LIBRERÍAS DE ROS2 MODIFICADO ───
target_link_libraries(ejemplo_opc_cliente PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    open62541::open62541
    rclcpp::rclcpp
    std_msgs::std_msgs__rosidl_typesupport_cpp
)
# ─────────────────────────────────────────────────

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ejemplo_opc_cliente)
endif()
set_target_properties(ejemplo_opc_cliente PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ejemplo_opc_cliente
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ejemplo_opc_cliente)
endif()
