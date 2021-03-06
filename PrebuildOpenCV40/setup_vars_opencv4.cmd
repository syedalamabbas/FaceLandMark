@ECHO OFF
SETLOCAL EnableDelayedExpansion

SET "SCRIPT_DIR=%~dp0"

IF NOT DEFINED OPENCV_QUIET ( ECHO Setting vars for OpenCV 4.0.0-pre )
SET "PATH=!SCRIPT_DIR!\x64/vc15/bin;%PATH%"

IF NOT DEFINED OPENCV_SKIP_PYTHON (
  SET "PYTHONPATH_OPENCV=!SCRIPT_DIR!\python_loader"
  IF NOT DEFINED OPENCV_QUIET ( ECHO Append PYTHONPATH: !PYTHONPATH_OPENCV! )
  SET "PYTHONPATH=!PYTHONPATH_OPENCV!;%PYTHONPATH%"
)

IF NOT [%1] == [] (
  %*
  EXIT /B !errorlevel!
)
