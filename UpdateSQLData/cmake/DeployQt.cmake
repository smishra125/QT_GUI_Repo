set(ENV{PATH} "${QT_BIN_DIR};${COMPILER_BIN_DIR};$ENV{PATH}")

execute_process(
    COMMAND "${WINDEPLOYQT_EXECUTABLE}"
        --qtpaths "${QT_BIN_DIR}/qtpaths.exe"
        "${TARGET_EXECUTABLE}"
    RESULT_VARIABLE WINDEPLOYQT_RESULT
)

if(NOT WINDEPLOYQT_RESULT EQUAL 0)
    message(FATAL_ERROR "windeployqt failed with exit code ${WINDEPLOYQT_RESULT}")
endif()
