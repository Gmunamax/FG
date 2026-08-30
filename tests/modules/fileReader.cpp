// FGengine - a free and open-source library for game development
// Copyright (C) 2025, 2026 Gmunamax <https://github.com/Gmunamax/FGengine>

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, see <https://www.gnu.org/licenses/>.
#include <boost/test/unit_test.hpp>
#include <fileReader.hpp>
#include <fstream>
#include <string>
#include <string_view>
#include <set>

void CreateFileWithContent(const char* path, std::string_view content){
	std::fstream stream{path, std::ios::out | std::ios::trunc};
	stream << content;
}

BOOST_AUTO_TEST_CASE(readFile){
	const std::string fileContent = "Hello world";
	constexpr const char* testFilePath = "/tmp/testFile.txt";
	CreateFileWithContent(testFilePath, fileContent);

	const std::string readedFile{FGengine::ReadFile(testFilePath)};

	const std::set<std::string> validResults {fileContent, fileContent+"\n"};
	BOOST_TEST(validResults.contains(readedFile));
}
