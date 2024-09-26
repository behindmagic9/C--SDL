
#include <iostream>
#include "include/glad/glad.h"
#include<vector>
#include <SDL2/SDL.h>

int gScrneeHeight = 480;
int gScreenWidth = 680;
SDL_Window* gGraphicsApplicationWindow = nullptr;
SDL_GLContext gOpenGLContext = nullptr;

bool gQuit = false;


// vao
GLuint gVertexArrayObject = 0;

// vbo
GLuint gVertexBufferObject = 0;

// pogram object for our shaders
GLuint gGraphicsPipelineShaderProgram = 0;


const std::string gVertexShaderSource = 
	"#version 410 core\n"
	"in vec4 position;\n"
	"void main() \n"
	"{ \n"
	"	gl_Position = vec4(position.x,position.y,position.z,position.w);\n"
	"}\n";


const std::string gFragementShaderSource = 
	"#version 410 core\n"
	"out vec4 fragColor;\n"
	"void main() \n"
	"{ \n"
	"	fragColor = vec4(1.0f, 0.5f, 0.0f,1.0f);\n"
	"}\n";

GLuint CompilerShader(GLuint type , const std::string & source){
	GLuint shaderObject;
	if(type == GL_VERTEX_SHADER){
		shaderObject = glCreateShader(GL_VERTEX_SHADER);
	}else if(type == GL_FRAGMENT_SHADER){
		shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
	}

	

	const char* src = source.c_str();
	glShaderSource(shaderObject,1, &src, nullptr );
	glCompileShader(shaderObject);
	return shaderObject;
}

GLuint CreateShaderProgram(const std::string &vertexshadersource ,const std::string &fragmentshader ){
	GLuint programObject = glCreateProgram();
	GLuint myVertexShader = CompilerShader(GL_VERTEX_SHADER, vertexshadersource);
	GLuint myFragementShader = CompilerShader(GL_FRAGMENT_SHADER, fragmentshader);

	glAttachShader(programObject,myVertexShader);
	glAttachShader(programObject, myFragementShader);

	glLinkProgram(programObject);

	return programObject;


}

void CreateGraphicsPipeline(){
	gGraphicsPipelineShaderProgram = CreateShaderProgram(gVertexShaderSource,gFragementShaderSource);
}

void VertexSpecification(){
	const std::vector<GLfloat> vertexPosition{
		-0.8f,-0.8f,0.0f,	// vertex 1
		0.8f,-0.8f,0.0f,	// vertex 2
		0.0f,0.8f,0.0f	// vertex 3
	};

	// GLuint gVertexArrayObject = 0;
	glGenVertexArrays(1,&gVertexArrayObject);
	glBindVertexArray(gVertexArrayObject);

	glGenBuffers(1,&gVertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER,gVertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER,vertexPosition.size() * sizeof(float), vertexPosition.data() , GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
	// glBindVertexArray(0);
	// glDisableVertexAttribArray(0);
}

void GetOpenGLVersion(){
	std::cout << "Vendor : " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer : " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Shading Language : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void Initialise()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		std::cout << "SDL2 could not initialise video subsytem" << std::endl;
		exit(1);
	}
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);
	

	gGraphicsApplicationWindow = SDL_CreateWindow("Opengl window",0,0,gScreenWidth, gScrneeHeight, SDL_WINDOW_OPENGL);

	if(gGraphicsApplicationWindow == nullptr){
		std::cout << "SDL Window was not ble to be created" << std::endl;
		exit(1);
	}

	gOpenGLContext = SDL_GL_CreateContext(gGraphicsApplicationWindow);

	if(gOpenGLContext == nullptr){
		std::cout << "OpenGl context not avialable " << std::endl;
		exit(1);
	}

	if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
		std::cout << "Glad was not initialized " << std::endl;
		exit(1);
	}
	GetOpenGLVersion();
}

void Input(){
	SDL_Event e;
	while(SDL_PollEvent(&e)){
		if(e.type == SDL_QUIT){
			std::cout <<  "quit " << std::endl;
			gQuit = true;
		}
	}
}

void PreDraw(){
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glViewport(0,0,gScreenWidth, gScrneeHeight);
	glClearColor(1.0f,1.0f,0.0f,1.0f);

	glClear( GL_COLOR_BUFFER_BIT);
	glUseProgram(gGraphicsPipelineShaderProgram);
}

void Draw(){
	glBindVertexArray(gVertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER,gVertexBufferObject);
	glDrawArrays(GL_TRIANGLES, 0,3);
}

void MainLoop()
{
	while(!gQuit){
		Input();

		PreDraw();

		Draw();
		// update the screen 
		SDL_GL_SwapWindow(gGraphicsApplicationWindow);
	}
}

void CleanUp()
{
	SDL_DestroyWindow(gGraphicsApplicationWindow);
	SDL_Quit();
}

int main()
{
	Initialise();
	CreateGraphicsPipeline();
	VertexSpecification();
	MainLoop();
	CleanUp();
	return 0;
}
