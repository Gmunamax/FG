#pragma once
#include <vector>
#include <string>
#include "shaderproperty.hpp"
#include <forward_list>

class Shader{

	class ShadersList{
		std::forward_list<Shader*> shaderslist;

		std::forward_list<Shader*>::iterator iteratorcarret;
		std::forward_list<Shader*>::iterator lastelementcarret;
		unsigned long lastelement = 0;

	public:
		void MoveForward(){
			iteratorcarret++;
		}

		void AddElement(Shader* element, unsigned long id){
			//Move carret to here and rewrite pointer to shader
			//Error if id > maxid (if not do it, we'll have to create elements with ids from maxid to id and delete them and this once this id becomes free)
		}
		void AddElementBack(Shader* element){
			//Maybe we'll store carret pointing to last element, so we'll copy it here, add new element to shaderslist and give it this new shader.
		}
		std::forward_list<Shader*>::const_reference GetAtCarret(){
			//Return element at iteratorcarret
		}
		
	};
	

	std::vector<Uniforms::UniformData*> uniforms;
	std::vector<Shader*> allshaders;

	GLuint shaderid;

	// forward list<Pair (id,pointer)>. 
	//Creating element:
	//If new id is not > max.id (id is free), pair points to special Shader object that means this id is free.
	//If new id IS > max.id (new id), adds new pair
	//Deleting element:
	//If id is last, deleting pair
	//If id is not last, pair will point to null-Shader.
	//Editing:
	//Just changing pointer
	//Access:
	//In Shader class it will be used to access all elements in loop. So, for(TemporaryPointer p : thisarray) { if(!p.Empty()){ p.DoSomething() } p.GoToPointer()}
	//For deleting/adding it's not neccesary to do max perfomance.

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

public:
	Uniforms::UniformData& GetUniformByName(const char* name){
		for(std::vector<Uniforms::UniformData*>::reference unif : uniforms){
			if(unif.GetName() == name){
				return unif;
			}
		}
	}

	static void SetUniformValueForAllByName(Uniforms::UniformData value){
		value.GetName()
	}
	
	void Update(){
		for(std::vector<Uniforms::UniformData*>::reference unif : uniforms){
			unif.Send();
		}
	}

	void Bind(){
		glUseProgram(shaderid);
	}

	Shader(){}
	~Shader(){}
};