add_executable(algorithmTests)
target_sources(algorithmTests PRIVATE
	main.cpp
)
target_link_libraries(algorithmTests PRIVATE Boost::unit_test_framework shared algorithm)
target_compile_definitions(algorithmTests PRIVATE BOOST_DYN_LINK)
