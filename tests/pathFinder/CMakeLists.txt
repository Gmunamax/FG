add_executable(pathFinderTests)

target_link_libraries(pathFinderTests PRIVATE Boost::unit_test_framework shared pathFinder)
target_compile_definitions(pathFinderTests PRIVATE BOOST_DYN_LINK)

target_sources(pathFinderTests PRIVATE
	main.cpp
)
