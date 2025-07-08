// g++ main1.cpp ./src/glad.c -I./include/ -o a.out -lSDL2 -ldl

#include <SDL2/SDL.h>
#include "include/glad/glad.h"
#include<vector>
#include <iostream>
#include<string>
#include<fstream>

int gScreenHeight = 480;
int gScreenWidth = 640;

SDL_Window *gGraphicsApplicationWindow = nullptr;
SDL_GLContext gOpenGlContext = nullptr;

GLuint gVertexArrayObject = 0;
GLuint gVertexBufferObject = 0;

// program object for our shaders // as a graphic pipleine .. hasving vertex shader and fragement shader
GLuint gGraphicsPipelineShaderProgram = 0;
bool gQuit = false;

std::string LoadShaderAsString(const std::string& filename){
    std::string result = "";

    std::string line = "";
    std::ifstream myFile(filename.c_str());

    if(myFile.is_open()){
        while(std::getline(myFile,line)){
            result += line + '\n';
        }
        myFile.close();
    }
    
    return result;
}

GLuint CompileShader(GLuint type , const std::string &source){

    GLuint shaderObject;

    if(type == GL_VERTEX_SHADER){
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
    }else if(type == GL_FRAGMENT_SHADER){
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    }

    const char* src = source.c_str();
    glShaderSource(shaderObject,1 ,&src, nullptr);
    glCompileShader(shaderObject);
    return shaderObject;
}

GLuint CreateShaderProgram(const std::string& vertexShaderSource , const std::string &fragmentShaderSource){
    GLuint programObject = glCreateProgram();

    GLuint myvertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint myFragmentShader = CompileShader(GL_FRAGMENT_SHADER,fragmentShaderSource);

    glAttachShader(programObject, myvertexShader);
    glAttachShader(programObject, myFragmentShader);
    glLinkProgram(programObject);

    // validate our porgram
    glValidateProgram(programObject);

    // glDetachShader , glDeleteShader
    return programObject;
}


void CreatedGraphicsPipeline(){

    std::string vertexShaderSource = LoadShaderAsString("./shaders/vert.glsl");
    std::string fragementShaderSource = LoadShaderAsString("./shaders/frag.glsl");
    gGraphicsPipelineShaderProgram = CreateShaderProgram(vertexShaderSource, fragementShaderSource);
}


void getOpenGLVersion()
{
    std::cout << "Vendor : " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "render : " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading language : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void VertexSpecification(){

    /// lives on gpu // triangle single
    // const std::vector<GLfloat> vertexData {
    //     // x, y ,z
    //     -0.8f,-0.8f,0.0,    // left vertex 1 
    //     1.0f, 0.0f,0.0f, // color
    //     0.8f,-0.8f,0.0f,    // right  vertex 2 
    //     0.0f,1.0f,0.0f, // color
    //     0.0f,0.8f,0.0f,  // top vertex 3
    //     0.0f,0.0f,1.0f // color
    // };

    // right angle triangle
    // const std::vector<GLfloat> vertexData {
    //     // x, y ,z
    //     -0.8f,-0.8f,0.0,    // left vertex 1 
    //     1.0f, 0.0f,0.0f, // color
    //     0.8f,-0.8f,0.0f,    // right  vertex 2 
    //     0.0f,1.0f,0.0f, // color
    //     -0.8f,0.8f,0.0f,  // top vertex 3
    //     0.0f,0.0f,1.0f // color
    // };

    // quarilateral
    const std::vector<GLfloat> vertexData {
        // triangle 1
        // x, y ,z
        -0.5f,-0.5f,0.0,    // left vertex 1 
        1.0f, 0.0f,0.0f, // color
        0.5f,-0.5f,0.0f,    // right  vertex 2 
        0.0f,1.0f,0.0f, // color
        -0.5f,0.5f,0.0f,  // top vertex 3
        0.0f,0.0f,1.0f, // color

        // traingle2
        0.5f,-0.5f,0.0,    // right vertex 1 
        0.0f, 1.0f,0.0f, // color
        0.5f,0.5f,0.0f,    // top-right  vertex 2 
        1.0f,0.0f,0.0f, // color
        -0.5f,0.5f,0.0f,  // top-left vertex 3
        0.0f,0.0f,1.0f // color
    }; 
// winding order is the direction that our vertices are laid out . can be counter clock wise or clockwise
    // there is also a concept to the winding order like in what order the vertices are wind like in clock wise or anti clock wise 
    // these determine the front face and back face .. front face is one visible to us
    // rule use is right handle finger rule .. thumb poiinting to y, index to x and middle finger to z .. z shows the face direction
    // also then use the right hand thummb riule .. thumb poitng to z direction or face direction adn finger curing diretion determine the winding order that is clockwise or anti-clockwise
    //  we start setting thing up on the gpu

    // also ther is glFrontFace function which can solve the winding order too 

    glGenVertexArrays(1,&gVertexArrayObject);
    glBindVertexArray(gVertexArrayObject);
    

    // start fgenerating out VBO
    glGenBuffers(1,&gVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(GL_FLOAT),vertexData.data(),GL_STATIC_DRAW);

     // to get to that data here 
     glEnableVertexAttribArray(0); // enable it
     // to use it 
     glVertexAttribPointer(0, 
                            3, // as x , y , z
                            GL_FLOAT, // wht type eof infomration we eworking with
                            GL_FALSE,   // normalise 
                            sizeof(GL_FLOAT)*6,  // stride is space between x, y, z and rbg
                            (void*)0
    ); // pointer for the offset
    
       
    glEnableVertexAttribArray(1); // enable it
     // to use it 
     glVertexAttribPointer(1, 
                            3, // as x , y , z
                            GL_FLOAT, // wht type eof infomration we eworking with
                            GL_FALSE,   // normalise 
                            sizeof(GL_FLOAT)*6,  // stride is space between x, y, z and rbg ..i.e one is 6  i.e x,y,x,r,g,b i.e 6
                            (GLvoid*)(sizeof(GL_FLOAT)*3)
    ); // pointer for the offset

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void InitialiseProgram()
{

// initliase sdl
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL2 could not be initialise video subsystem" << std::endl;
        exit(1);
    }

// set up some opengl attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // support latest ucntions
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // 24 bytes to get tprecison when dicrimainate in objec tor overlapiing

// created our window
    gGraphicsApplicationWindow = SDL_CreateWindow("opengl ", 0, 0, gScreenWidth, gScreenHeight, SDL_WINDOW_OPENGL);

    if (gGraphicsApplicationWindow == nullptr)
    {
        std::cout << "SDL Window was not able to be created " << std::endl;
        exit(1);
    }

// opengl context
    gOpenGlContext = SDL_GL_CreateContext(gGraphicsApplicationWindow);
    if (gOpenGlContext == nullptr)
    {
        std::cout << "Opengl Context not avialable\n";
        exit(1);
    }

    // include the glad library
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) // whic brings int he opengl funcits for us
    { // loading up a bunch of function pointers
        std::cout << "glad was not initialised" << std::endl;
        exit(1);
    }

    getOpenGLVersion();
}

void CleanUp()
{
    // delete opengl object
    glDeleteBuffers(1, &gVertexBufferObject);
    glDeleteVertexArrays(1, &gVertexArrayObject);

    // delete the graphics pipeine
    SDL_DestroyWindow(gGraphicsApplicationWindow);
    SDL_Quit();
}

void Input()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            std::cout << "GoodBye" << std::endl;
            gQuit = true;
        }
    }
}

void PreDraw()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0,0,gScreenWidth,gScreenHeight);
    glClearColor(1.1f,1.f,0.f,1.f);

    glClear(GL_DEPTH_BUFFER_BIT| GL_COLOR_BUFFER_BIT);
    glUseProgram(gGraphicsPipelineShaderProgram);   // using appropritate pipeline
}

void Draw()
{
    // after this piepline be activate

    glBindVertexArray(gVertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER,gVertexBufferObject);

    // glDrawArrays(GL_TRIANGLES, 0, 3);// for 3 vertices 
    // for quadritalralo vertices are now 6 cause if two triangle so 
    glDrawArrays(GL_TRIANGLES, 0, 6);

}

void MainLoop()
{
    while (!gQuit)
    {

        Input();

        PreDraw();

        Draw();

        // update the screen
        // the way double buffering work is when we drawing a graphic screen .. we draw to back as soon as we done .. we sent that information to the buffer .. and drawing somehting else on the back while fornt is displayed to user ..
        SDL_GL_SwapWindow(gGraphicsApplicationWindow);
    }
}

int main()
{
    InitialiseProgram();

// set up geometry
    VertexSpecification();
 
 // at minmal this mean s the vertex and fragment shader
    CreatedGraphicsPipeline();

    MainLoop();

    CleanUp();
    return 0;
}