#pragma once
#include <vector>
#include <string>
#include "shaderproperty.hpp"

class Shader{
	std::vector<Uniforms::UniformData> uniforms;
	std::vector<Shader*> allshaders;

	GLuint shaderid;

	class ShaderSourceReader{
		std::string* file;
		long cpos = 0;
		const static inline std::string stopcharacters{" \n\t:;{}()[]\\|/*+-=%#!~`.,<>\"'@$^&"};
	
	public:

		std::string ReadWord(){
			std::string word;

			for(; IsEOF() or IsAStopCharacter((*file)[cpos]); cpos++){
				word += (*file)[cpos];
				cpos++;
			}
			return word;
		}

	private:
		bool IsAStopCharacter(char character){
			return stopcharacters.find(character) != std::string::npos;
		}
	
	public:

		bool IsEOF(){
			return cpos <= file->length();
		}

	public:

		ShaderSourceReader(std::string* file){
			this->file = file;
		}
	};

public:
	
	void Load(std::string& file){
		ApplyUniforms(file);
	}

private:
	void ApplyUniforms(std::string& file){
		std::string word;
		ShaderSourceReader reader {&file};


		while( !reader.IsEOF() ){
			word = reader.ReadWord();
			if(word == "uniform"){
				const char* type = reader.ReadWord().c_str();
				const char* name = reader.ReadWord().c_str();
				AddNewUniform(name, type);
			}
		}
	}

	void AddNewUniform(const char* name, const char* type){
		if(type == "vec4"){
			uniforms.emplace_back(name, shaderid, (glm::vec4*)nullptr);
		}
		else if(type == "vec3"){
			uniforms.emplace_back(name, shaderid, (glm::vec3*)nullptr);
		}
		else if(type == "mat4"){
			uniforms.emplace_back(name, shaderid, (glm::mat4*)nullptr);
		}
		else if(type == "mat3"){
			uniforms.emplace_back(name, shaderid, (glm::mat3*)nullptr);
		}
	}

	Uniforms::UniformData& GetUniformByName(const char* name){
		for(std::vector<Uniforms::UniformData>::reference unif : uniforms){
			if(unif.GetName() == name){
				return unif;
			}
		}
	}

	static void SetUniformValueForAllByName(const char* name){
		
	}
	
	void Update(){
		for(std::vector<Uniforms::UniformData>::reference unif : uniforms){
			unif.Send();
		}
	}

	void Bind(){
		glUseProgram(shaderid);
	}

	Shader(){}
	~Shader(){}
};