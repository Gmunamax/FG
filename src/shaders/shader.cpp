#include "FGengine/shaders/shader.hpp"

static std::string ReadFile(const char* path){
	std::ifstream reader(path);
	if(!reader.is_open()){
		std::cout << "Shader: file not found: " << path << std::endl;
	}

	std::string shadcode = "";
	std::string line;
	while(std::getline(reader,line)){
		shadcode+=(line+"\n");
	}

	reader.close();
	return shadcode;
}

static GLuint CompileObject(Shader::ObjectDescription description){
	GLuint object = glCreateShader(description.type);
	std::vector<std::string> sources;
	std::vector<const char*> csources;
	std::vector<GLint> lenghts;
	std::string source;
	for(GLsizei i = 0; i < description.filepathes.size(); i++){
		source = ReadFile( description.filepathes.at(i) );
		sources.push_back(source);
		csources.push_back(source.c_str());
		lenghts.push_back(source.length());
	}
	glShaderSource(object, description.filepathes.size(), csources.data(), lenghts.data());
	glCompileShader(object);
	return object;
}

void Shader::CheckForError(GLenum type, const char* errorheader){
	int sth;
	constexpr short logsize = 512;
	char log[logsize];
	glGetShaderiv(shaderid, type, &sth);
	if(!sth){
		glGetShaderInfoLog(shaderid, logsize, NULL, log);
		std::cout << errorheader << "\n" << log << std::endl;
	}
}

const char* Shader::compileerror = "Failed to compile shader";
const char* Shader::linkerror = "Failed to link shader";

std::vector<GLuint> Shader::CompileObjects(std::vector<Shader::ObjectDescription> descriptions){
	std::vector<GLuint> shaderparts;
	for(auto& e : descriptions){
		shaderparts.push_back( CompileObject(e) );
	}
	CheckForError(GL_COMPILE_STATUS, compileerror);
	return shaderparts;
}

void Shader::LinkShader(std::vector<GLuint> shaderparts){
	if(shaderid != 0)
		Delete();
	shaderid = glCreateProgram();
	for(GLuint& part : shaderparts){
		glAttachShader(shaderid, part);
	}
	glLinkProgram(shaderid);
	CheckForError(GL_LINK_STATUS, linkerror);
}

Shader nullshader;