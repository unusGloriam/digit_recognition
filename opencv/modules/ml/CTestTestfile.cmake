# CMake generated Testfile for 
# Source directory: D:/Downloads/scoped_dir13072_1330966658/opencv/sources/modules/ml
# Build directory: D:/Downloads/scoped_dir13072_1330966658/opencv/build-sources/modules/ml
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_ml "D:/Downloads/scoped_dir13072_1330966658/opencv/build-sources/bin/opencv_test_ml.exe" "--gtest_output=xml:opencv_test_ml.xml")
set_tests_properties(opencv_test_ml PROPERTIES  LABELS "Main;opencv_ml;Accuracy" WORKING_DIRECTORY "D:/Downloads/scoped_dir13072_1330966658/opencv/build-sources/test-reports/accuracy" _BACKTRACE_TRIPLES "D:/Downloads/scoped_dir13072_1330966658/opencv/sources/cmake/OpenCVUtils.cmake;1763;add_test;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/cmake/OpenCVModule.cmake;1375;ocv_add_test_from_target;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/cmake/OpenCVModule.cmake;1133;ocv_add_accuracy_tests;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/modules/ml/CMakeLists.txt;2;ocv_define_module;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/modules/ml/CMakeLists.txt;0;")