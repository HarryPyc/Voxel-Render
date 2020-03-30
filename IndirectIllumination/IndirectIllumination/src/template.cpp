#include <windows.h>

#include <GL/glew.h>

#include <GL/freeglut.h>

#include <GL/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <InitShader.h>
#include <LoadMesh.h>
#include <LoadTexture.h>
#include <imgui_impl_glut.h>
#include <VideoMux.h>
#include <DebugCallback.h>

//names of the shader files to load
static const std::string vertex_shader("shader/template_vs.glsl");
static const std::string fragment_shader("shader/template_fs.glsl");

GLuint shader_program = -1;
GLuint texture_id = -1; //Texture map for fish

//names of the mesh and texture files to load
static const std::string mesh_name = "model/Amago0.obj";
static const std::string texture_name = "texture/AmagoT.bmp";

MeshData mesh_data;
float time_sec = 0.0f;
float angle = 0.0f;
bool recording = false;

//Draw the user interface using ImGui
void draw_gui()
{
   ImGui_ImplGlut_NewFrame();

   const int filename_len = 256;
   static char video_filename[filename_len] = "capture.mp4";

   ImGui::InputText("Video filename", video_filename, filename_len);
   ImGui::SameLine();
   if (recording == false)
   {
      if (ImGui::Button("Start Recording"))
      {
         const int w = glutGet(GLUT_WINDOW_WIDTH);
         const int h = glutGet(GLUT_WINDOW_HEIGHT);
         recording = true;
         start_encoding(video_filename, w, h); //Uses ffmpeg
      }
      
   }
   else
   {
      if (ImGui::Button("Stop Recording"))
      {
         recording = false;
         finish_encoding(); //Uses ffmpeg
      }
   }

   //create a slider to change the angle variables
   ImGui::SliderFloat("View angle", &angle, -3.141592f, +3.141592f);

   ImGui::Image((void*)texture_id, ImVec2(128,128));


   ImGui::Render();
 }

// glut display callback function.
// This function gets called every time the scene gets redisplayed 
void display()
{
   //clear the screen
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glUseProgram(shader_program);

   const int w = glutGet(GLUT_WINDOW_WIDTH);
   const int h = glutGet(GLUT_WINDOW_HEIGHT);
   const float aspect_ratio = float(w) / float(h);

   glm::mat4 M = glm::rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f))*glm::scale(glm::vec3(mesh_data.mScaleFactor));
   glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 1.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
   glm::mat4 P = glm::perspective(3.141592f / 4.0f, aspect_ratio, 0.1f, 100.0f);

   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, texture_id);
   int tex_loc = glGetUniformLocation(shader_program, "diffuse_color");
   if (tex_loc != -1)
   {
      glUniform1i(tex_loc, 0); // we bound our texture to texture unit 0
   }

   int PVM_loc = glGetUniformLocation(shader_program, "PVM");
   if (PVM_loc != -1)
   {
      glm::mat4 PVM = P*V*M;
      glUniformMatrix4fv(PVM_loc, 1, false, glm::value_ptr(PVM));
   }

   glBindVertexArray(mesh_data.mVao);
   mesh_data.DrawMesh();
         
   draw_gui();

   if (recording == true)
   {
      glFinish();

      glReadBuffer(GL_BACK);
      read_frame_to_encode(&rgb, &pixels, w, h);
      encode_frame(rgb);
   }

   glutSwapBuffers();
}

// glut idle callback.
//This function gets called between frames
void idle()
{
	glutPostRedisplay();

   const int time_ms = glutGet(GLUT_ELAPSED_TIME);
   time_sec = 0.001f*time_ms;
}

void reload_shader()
{
   GLuint new_shader = InitShader(vertex_shader.c_str(), fragment_shader.c_str());

   if(new_shader == -1) // loading failed
   {
      glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
   }
   else
   {
      glClearColor(0.35f, 0.35f, 0.35f, 0.0f);

      if(shader_program != -1)
      {
         glDeleteProgram(shader_program);
      }
      shader_program = new_shader;
      
   }
}

// Display info about the OpenGL implementation provided by the graphics driver.
// Your version should be > 4.0 for CGT 521 
void printGlInfo()
{
   std::cout << "Vendor: "       << glGetString(GL_VENDOR)                    << std::endl;
   std::cout << "Renderer: "     << glGetString(GL_RENDERER)                  << std::endl;
   std::cout << "Version: "      << glGetString(GL_VERSION)                   << std::endl;
   std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION)  << std::endl;
}

void initOpenGl()
{
   //Initialize glew so that new OpenGL function names can be used

   glewInit();
   RegisterCallback();
   glEnable(GL_DEPTH_TEST);

   reload_shader();

   //Load a mesh and a texture
   mesh_data = LoadMesh(mesh_name); //Helper function: Uses Open Asset Import library.
   texture_id = LoadTexture(texture_name.c_str()); //Helper function: Uses FreeImage library
}

// glut callbacks need to send keyboard and mouse events to imgui
void keyboard(unsigned char key, int x, int y)
{
   ImGui_ImplGlut_KeyCallback(key);
   std::cout << "key : " << key << ", x: " << x << ", y: " << y << std::endl;

   switch(key)
   {
      case 'r':
      case 'R':
         reload_shader();     
      break;
   }
}

void keyboard_up(unsigned char key, int x, int y)
{
   ImGui_ImplGlut_KeyUpCallback(key);
}

void special_up(int key, int x, int y)
{
   ImGui_ImplGlut_SpecialUpCallback(key);
}

void passive(int x, int y)
{
   ImGui_ImplGlut_PassiveMouseMotionCallback(x,y);
}

void special(int key, int x, int y)
{
   ImGui_ImplGlut_SpecialCallback(key);
}

void motion(int x, int y)
{
   ImGui_ImplGlut_MouseMotionCallback(x, y);
}

void mouse(int button, int state, int x, int y)
{
   ImGui_ImplGlut_MouseButtonCallback(button, state);
}


int main (int argc, char **argv)
{
#if _DEBUG
	glutInitContextFlags(GLUT_DEBUG);
#endif
	glutInitContextVersion(4, 3);
   //Configure initial window state using freeglut
   glutInit(&argc, argv); 
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
   glutInitWindowPosition (5, 5);
   glutInitWindowSize (1280, 720);
   int win = glutCreateWindow ("CGT 521 Template");

   printGlInfo();

   //Register callback functions with glut. 
   glutDisplayFunc(display); 
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(special);
   glutKeyboardUpFunc(keyboard_up);
   glutSpecialUpFunc(special_up);
   glutMouseFunc(mouse);
   glutMotionFunc(motion);
   glutPassiveMotionFunc(motion);

   glutIdleFunc(idle);

   initOpenGl();
   ImGui_ImplGlut_Init(); // initialize the imgui system

   //Enter the glut event loop.
   glutMainLoop();
   glutDestroyWindow(win);
   return 0;		
}


