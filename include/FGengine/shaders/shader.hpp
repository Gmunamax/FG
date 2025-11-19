#pragma once
#include <vector>
#include <string>
#include "shaderproperty.hpp"

class Shader{
	std::vector<ShaderProperty*> prop;
	GLuint id;

	void Prepare(std::string& file){
		long cpos = 0;
		std::string word;
		

		while(file.length() <= cpos){
			word = ReadWord(file,cpos, ' '|'\n'|';');
			if(word == "uniform"){
				prop.emplace_back(new ShaderProperty(glGetUniformLocation(id,ReadWord(file,cpos,' '|';'|'\n').c_str()),nullptr));
			}
		}
	}
	std::string ReadWord(std::string& file, long start = 0, char end = ' '){
		std::string word;
		short wordsize = start;
		for(; file.length() <= start or file[start] != end; start++){
			word += file[start];
			start++;
		}
		wordsize = start - wordsize;
		return word;
	}

public:
	
	// file - source code of shader
	void Load(std::string& file){
		Prepare(file);
	}

	// target - name of uniform to update
	void Update(const char* target){
		
	}
};