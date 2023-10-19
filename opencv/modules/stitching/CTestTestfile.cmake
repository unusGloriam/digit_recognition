# CMake generated Testfile for 
# Source directory: D:/Downloads/scoped_dir13072_1330966658/opencv/sources/modules/stitching
# Build directory: D:/Downloads/scoped_dir13072_1330966658/opencv/build-sources/modules/stitching
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_stitching "D:/Downloads/scoped_dir13072_1330966658/opencv/build-sources/bin/opencv_test_stitching.exe" "--gtest_output=xml:opencv_test_stitching.xml")
set_tests_properties(opencv_test_stitching PROPERTIES  LABELS "Main;opencv_stitching;Accuracy" WORKING_DIRECTORY "D:/Downloads/scoped_dir13072_1330966658/opencv/build-sources/test-reports/accuracy" _BACKTRACE_TRIPLES "D:/Downloads/scoped_dir13072_1330966658/opencv/sources/cmake/OpenCVUtils.cmake;1763;add_test;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/cmake/OpenCVModule.cmake;1375;ocv_add_test_from_target;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/cmake/OpenCVModule.cmake;1133;ocv_add_accuracy_tests;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/modules/stitching/CMakeLists.txt;11;ocv_define_module;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/modules/stitching/CMakeLists.txt;0;")
add_test(opencv_perf_stitching "D:/Downloads/scoped_dir13072_1330966658/opencv/build-sources/bin/opencv_perf_stitching.exe" "--gtest_output=xml:opencv_perf_stitching.xml")
set_tests_properties(opencv_perf_stitching PROPERTIES  LABELS "Main;opencv_stitching;Performance" WORKING_DIRECTORY "D:/Downloads/scoped_dir13072_1330966658/opencv/build-sources/test-reports/performance" _BACKTRACE_TRIPLES "D:/Downloads/scoped_dir13072_1330966658/opencv/sources/cmake/OpenCVUtils.cmake;1763;add_test;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/cmake/OpenCVModule.cmake;1274;ocv_add_test_from_target;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/cmake/OpenCVModule.cmake;1134;ocv_add_perf_tests;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/modules/stitching/CMakeLists.txt;11;ocv_define_module;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/modules/stitching/CMakeLists.txt;0;")
add_test(opencv_sanity_stitching "D:/Downloads/scoped_dir13072_1330966658/opencv/build-sources/bin/opencv_perf_stitching.exe" "--gtest_output=xml:opencv_perf_stitching.xml" "--perf_min_samples=1" "--perf_force_samples=1" "--perf_verify_sanity")
set_tests_properties(opencv_sanity_stitching PROPERTIES  LABELS "Main;opencv_stitching;Sanity" WORKING_DIRECTORY "D:/Downloads/scoped_dir13072_1330966658/opencv/build-sources/test-reports/sanity" _BACKTRACE_TRIPLES "D:/Downloads/scoped_dir13072_1330966658/opencv/sources/cmake/OpenCVUtils.cmake;1763;add_test;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/cmake/OpenCVModule.cmake;1275;ocv_add_test_from_target;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/cmake/OpenCVModule.cmake;1134;ocv_add_perf_tests;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/modules/stitching/CMakeLists.txt;11;ocv_define_module;D:/Downloads/scoped_dir13072_1330966658/opencv/sources/modules/stitching/CMakeLists.txt;0;")
