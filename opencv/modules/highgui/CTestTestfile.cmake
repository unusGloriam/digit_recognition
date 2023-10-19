# CMake generated Testfile for 
# Source directory: D:/Downloads/scoped_dir13072_1330966658/opencv/sources/modules/highgui
# Build directory: D:/Downloads/scoped_dir13072_1330966658/opencv/build-sources/modules/highgui
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_highgui "D:/Downloads/scoped_dir13072_1330966658/opencv/build-sources/bin/opencv_test_highgui.exe" "--gtest_output=xml:opencv_test_highgui.xml")
set_tests_properties(opencv_test_highgui PROPERTIES  LABELS "Main;opencv_highgui;Accuracy" WORKING_DIRECTORY "D:/Downloads/scoped_dir13072_1330966658/opencv/build-sources/test-reports/accuracy" _BACKTRACE_TRIPLES "D:/Downloads/scoped_dir13072_1330966658/opencv/sources/cmake/OpenCVUtils.cmake;1763;add_test;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/cmake/OpenCVModule.cmake;1375;ocv_add_test_from_target;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/modules/highgui/CMakeLists.txt;309;ocv_add_accuracy_tests;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/modules/highgui/CMakeLists.txt;0;")
