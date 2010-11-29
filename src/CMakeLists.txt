include(${QT_USE_FILE})

include_directories(${QRENCODE_INCLUDE_DIR})
link_libraries (${QRENCODE_LIBRARY})

SUBDIRS(encoder)

# ----------------
# Plasmoid
# ----------------
find_package(KDE4 REQUIRED)
include(KDE4Defaults)
 
add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(
   ${CMAKE_SOURCE_DIR}
   ${CMAKE_BINARY_DIR}
   ${KDE4_INCLUDES}
   )
 
# We add our source code here
set(qrgenplasmoid_SRCS QRGenPlasmoid.cpp ui/QRGenConfigDialog.cpp ui/QRCodeWidget.cpp)
 
kde4_add_plugin(qrgenapplet ${qrgenplasmoid_SRCS})
target_link_libraries(qrgenapplet 
                      ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS} ${QT_LIBRARIES} encoder)
 
install(TARGETS qrgenapplet
        DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES qrgenplasmoid.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})

install(FILES qrgenplasmoid.png
        DESTINATION ${KDE4_ICON_INSTALL_DIR})
