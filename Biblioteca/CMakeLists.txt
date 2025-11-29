cmake_minimum_required(VERSION 3.16)

project(Biblioteca VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Biblioteca
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Models/material.h Models/material.cpp


        Models/libro.h Models/libro.cpp
        Models/tesis.h Models/tesis.cpp
        Models/revista.h Models/revista.cpp
        Models/usuario.h Models/usuario.cpp
        Views/MaterialesView.h Views/MaterialesView.cpp Views/MaterialesView.ui
        Views/UsuariosView.h Views/UsuariosView.cpp Views/UsuariosView.ui
        Views/mainwindow.h Views/mainwindow.cpp Views/mainwindow.ui

        Controllers/MaterialController.h Controllers/MaterialController.cpp
        Controllers/UsuarioController.h Controllers/UsuarioController.cpp
        Models/BaseDatos.h Models/BaseDatos.cpp
        Models/UsuarioDAO.h Models/UsuarioDAO.cpp
        Models/MaterialDAO.h Models/MaterialDAO.cpp
        Models/LibroDAO.h Models/LibroDAO.cpp

        Models/TesisDAO.h Models/TesisDAO.cpp
        Models/RevistaDAO.h Models/RevistaDAO.cpp


        Views/UsuarioForm.h Views/UsuarioForm.cpp Views/UsuarioForm.ui
        Views/MaterialesForm.h Views/MaterialesForm.cpp Views/MaterialesForm.ui
        Models/MaterialFactory.h Models/MaterialFactory.cpp
        Models/Prestamo.h Models/Prestamo.cpp
        Models/PrestamoDAO.h Models/PrestamoDAO.cpp
        Controllers/PrestamoController.h Controllers/PrestamoController.cpp
        Views/PrestamosView.h Views/PrestamosView.cpp Views/PrestamosView.ui
        Views/PrestamoForm.h Views/PrestamoForm.cpp Views/PrestamoForm.ui
        Models/Repositorio.h
        Controllers/BibliotecaFacade.h
        Controllers/BibliotecaFacade.cpp
        Iconos/Iconos.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Biblioteca APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Biblioteca SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Biblioteca
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Biblioteca PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Biblioteca)
endif()
set_target_properties(Biblioteca PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Biblioteca
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Biblioteca)
endif()
