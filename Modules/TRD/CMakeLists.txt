# ---- Library ----

add_library(O2QcTRD)

target_sources(O2QcTRD PRIVATE
              src/CalibReductorTRD.cxx 
              src/TrackletCountCheck.cxx
              src/PulsePositionCheck.cxx
              src/TrackingTask.cxx
              src/PulseHeightTrackMatch.cxx
              src/TrackletsTask.cxx
              src/PulseHeightCheck.cxx
              src/RawData.cxx
              src/RawDataCheck.cxx
              src/DigitsTask.cxx
              src/TRDTrending.cxx
              src/TrendingTaskConfigTRD.cxx
              src/PulseHeightPostProcessing.cxx
              src/TRDHelpers.cxx)

target_include_directories(
  O2QcTRD
  PUBLIC $<INSTALL_INTERFACE:include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(O2QcTRD PUBLIC O2QualityControl O2QcCommon)

install(TARGETS O2QcTRD
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

add_root_dictionary(O2QcTRD HEADERS
                    include/TRD/CalibReductorTRD.h
                    include/TRD/TrackletCountCheck.h
                    include/TRD/PulsePositionCheck.h
                    include/TRD/TrackingTask.h
                    include/TRD/PulseHeightTrackMatch.h
                    include/TRD/TrackletsTask.h
                    include/TRD/TRDHelpers.h
                    include/TRD/PulseHeightCheck.h
                    include/TRD/RawData.h
                    include/TRD/RawDataCheck.h
                    include/TRD/PulseHeightPostProcessing.h
                    include/TRD/DigitsTask.h
                    include/TRD/TRDTrending.h
                    include/TRD/TrendingTaskConfigTRD.h
                    LINKDEF include/TRD/LinkDef.h)

# ---- Test(s) ----

#set(TEST_SRCS test/testQcTRD.cxx) # uncomment to reenable the test which was empty

foreach(test ${TEST_SRCS})

  get_filename_component(test_name ${test} NAME)
  string(REGEX REPLACE ".cxx" "" test_name ${test_name})

  add_executable(${test_name} ${test})
  target_link_libraries(${test_name}
                        PRIVATE O2QcTRD Boost::unit_test_framework)

  add_test(NAME ${test_name} COMMAND ${test_name})
  set_property(TARGET ${test_name}
    PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

  set_tests_properties(${test_name} PROPERTIES TIMEOUT 20)
endforeach()


# ---- Install ----

install(TARGETS O2QcTRD ${EXE_NAMES}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/TRD
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/QualityControl")

# ---- Install config files ----

install(FILES TRDQC.json
              DESTINATION etc)
