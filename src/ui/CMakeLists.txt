SET( UI_SRCS
        QRGenConfigDialog.cpp
        )
SET( UI_HDRS
        QRGenConfigDialog.h
        )

QT4_WRAP_CPP(UI_MOC_SRCS ${UI_HDRS})
add_library(ui ${UI_MOC_SRCS})


