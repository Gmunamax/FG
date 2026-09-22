add_executable(tests)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)
target_link_libraries(tests PRIVATE Boost::unit_test_framework engine)
target_compile_definitions(tests PRIVATE BOOST_DYN_LINK)
target_include_directories(tests PRIVATE ../../src)

target_sources(tests PRIVATE
	main.cpp
	officeGraph.cpp
)
