# CMake generated Testfile for 
# Source directory: /Users/dev.daniil.bakushkin/github-classroom/itmo-mse-cpp/cpp23-ha-3-matrices-daniliambo
# Build directory: /Users/dev.daniil.bakushkin/github-classroom/itmo-mse-cpp/cpp23-ha-3-matrices-daniliambo/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(matrices_test "/bin/bash" "/Users/dev.daniil.bakushkin/github-classroom/itmo-mse-cpp/cpp23-ha-3-matrices-daniliambo/test/smoke_test.sh" "/Users/dev.daniil.bakushkin/github-classroom/itmo-mse-cpp/cpp23-ha-3-matrices-daniliambo/build/src/matrices")
set_tests_properties(matrices_test PROPERTIES  WORKING_DIRECTORY "/Users/dev.daniil.bakushkin/github-classroom/itmo-mse-cpp/cpp23-ha-3-matrices-daniliambo/build/test" _BACKTRACE_TRIPLES "/Users/dev.daniil.bakushkin/github-classroom/itmo-mse-cpp/cpp23-ha-3-matrices-daniliambo/CMakeLists.txt;28;add_test;/Users/dev.daniil.bakushkin/github-classroom/itmo-mse-cpp/cpp23-ha-3-matrices-daniliambo/CMakeLists.txt;0;")
subdirs("src")
