# CMake generated Testfile for 
# Source directory: D:/Downloads/scoped_dir13072_1330966658/opencv/sources/modules/core
# Build directory: D:/Downloads/scoped_dir13072_1330966658/opencv/build-sources/modules/core
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_core "D:/Downloads/scoped_dir13072_1330966658/opencv/build-sources/bin/opencv_test_core.exe" "--gtest_output=xml:opencv_test_core.xml")
set_tests_properties(opencv_test_core PROPERTIES  LABELS "Main;opencv_core;Accuracy" WORKING_DIRECTORY "D:/Downloads/scoped_dir13072_1330966658/opencv/build-sources/test-reports/accuracy" _BACKTRACE_TRIPLES "D:/Downloads/scoped_dir13072_1330966658/opencv/sources/cmake/OpenCVUtils.cmake;1763;add_test;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/cmake/OpenCVModule.cmake;1375;ocv_add_test_from_target;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/modules/core/CMakeLists.txt;176;ocv_add_accuracy_tests;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/modules/core/CMakeLists.txt;0;")
add_test(opencv_perf_core "D:/Downloads/scoped_dir13072_1330966658/opencv/build-sources/bin/opencv_perf_core.exe" "--gtest_output=xml:opencv_perf_core.xml")
set_tests_properties(opencv_perf_core PROPERTIES  LABELS "Main;opencv_core;Performance" WORKING_DIRECTORY "D:/Downloads/scoped_dir13072_1330966658/opencv/build-sources/test-reports/performance" _BACKTRACE_TRIPLES "D:/Downloads/scoped_dir13072_1330966658/opencv/sources/cmake/OpenCVUtils.cmake;1763;add_test;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/cmake/OpenCVModule.cmake;1274;ocv_add_test_from_target;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/modules/core/CMakeLists.txt;177;ocv_add_perf_tests;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/modules/core/CMakeLists.txt;0;")
add_test(opencv_sanity_core "D:/Downloads/scoped_dir13072_1330966658/opencv/build-sources/bin/opencv_perf_core.exe" "--gtest_output=xml:opencv_perf_core.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
set_tests_properties(opencv_sanity_core PROPERTIES  LABELS "Main;opencv_core;Sanity" WORKING_DIRECTORY "D:/Downloads/scoped_dir13072_1330966658/opencv/build-sources/test-reports/sanity" _BACKTRACE_TRIPLES "D:/Downloads/scoped_dir13072_1330966658/opencv/sources/cmake/OpenCVUtils.cmake;1763;add_test;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/cmake/OpenCVModule.cmake;1275;ocv_add_test_from_target;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/modules/core/CMakeLists.txt;177;ocv_add_perf_tests;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/modules/core/CMakeLists.txt;0;")
