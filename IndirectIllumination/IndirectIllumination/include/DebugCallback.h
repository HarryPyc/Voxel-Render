#pragma once

#include <windows.h>
#include <GL/glew.h>


/*
OpenGL debug message callbacks are a more convenient and performant alternative to glGetError(...).
When you register a debug message callback the openglCallbackFunction() below will be automatically called
by OpenGL when errors or warnings are detected.

More details about this feature are at: https://blog.nobel-joergensen.com/2013/02/17/debugging-opengl-part-2-using-gldebugmessagecallback/
*/

//Follow the following steps to add the debug callback to your application:

/* 1. Create an OpenGL context with debuggin enabled when you are running a debug build of the application. Also, verify that 
you are creating a context that supports OpenGL 4.3 or higher. 
You can do this by adding these lines before glutInit(...) is called:

#if _DEBUG
glutInitContextFlags(GLUT_DEBUG);
#endif
glutInitContextVersion(4, 3);

*/

/* 2. Register the debug callback function when you are running a debug build.
You can do this by calling RegisterCallback(); after glewInit(). Be sure to include this header file.

*/
void RegisterCallback();

void APIENTRY openglCallbackFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);