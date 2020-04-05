#include "DebugCallback.h"
#include <iostream>


void RegisterCallback()
{
#if _DEBUG
   if (glDebugMessageCallback)
   {
      std::cout << "Register OpenGL debug callback " << std::endl;
      glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
      glDebugMessageCallback(openglCallbackFunction, nullptr);
      GLuint unusedIds = 0;
      glDebugMessageControl(GL_DONT_CARE,
         GL_DONT_CARE,
         GL_DONT_CARE,
         0,
         &unusedIds,
         true);
   }
   else
   {
      std::cout << "glDebugMessageCallback not available" << std::endl;
   }
#endif
}

void APIENTRY openglCallbackFunction(GLenum source,
   GLenum type,
   GLuint id,
   GLenum severity,
   GLsizei length,
   const GLchar* message,
   const void* userParam)
{

   using namespace std;

   cout << "---------------------opengl-callback-start------------" << endl;
   cout << "message: " << message << endl;
   cout << "type: ";
   switch (type) {
   case GL_DEBUG_TYPE_ERROR:
      cout << "ERROR";
      break;
   case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      cout << "DEPRECATED_BEHAVIOR";
      break;
   case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      cout << "UNDEFINED_BEHAVIOR";
      break;
   case GL_DEBUG_TYPE_PORTABILITY:
      cout << "PORTABILITY";
      break;
   case GL_DEBUG_TYPE_PERFORMANCE:
      cout << "PERFORMANCE";
      break;
   case GL_DEBUG_TYPE_OTHER:
      cout << "OTHER";
      break;
   }
   cout << endl;

   cout << "id: " << id << endl;
   cout << "severity: ";
   switch (severity) {
   case GL_DEBUG_SEVERITY_LOW:
      cout << "LOW";
      break;
   case GL_DEBUG_SEVERITY_MEDIUM:
      cout << "MEDIUM";
      break;
   case GL_DEBUG_SEVERITY_HIGH:
      cout << "HIGH";
      break;
   }
   cout << endl;
   cout << "---------------------opengl-callback-end--------------" << endl;
}
