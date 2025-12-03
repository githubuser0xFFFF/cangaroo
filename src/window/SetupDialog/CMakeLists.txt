# SetupDialog module
set(SETUP_DIALOG_SOURCES
    SetupDialog.cpp
    SetupDialogTreeModel.cpp
    SetupDialogTreeItem.cpp
    SelectCanInterfacesDialog.cpp
)

set(SETUP_DIALOG_HEADERS
    SetupDialog.h
    SetupDialogTreeModel.h
    SetupDialogTreeItem.h
    SelectCanInterfacesDialog.h
)

set(SETUP_DIALOG_FORMS
    SetupDialog.ui
    SelectCanInterfacesDialog.ui
)

add_library(cangaroo_setup_dialog STATIC ${SETUP_DIALOG_SOURCES} ${SETUP_DIALOG_HEADERS} ${SETUP_DIALOG_FORMS})

target_include_directories(cangaroo_setup_dialog PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
    ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(cangaroo_setup_dialog cangaroo_core cangaroo_driver Qt6::Core Qt6::Widgets)