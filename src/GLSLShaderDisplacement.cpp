#include "GLSLShaderDisplacement.h"
#include "ManagerShader.h"
#include "ManagerEnvironmentConfiguration.h"
#include "GLSLUniform.h"

using namespace Aftr;

GLSLShaderDisplacement::GLSLShaderDisplacement(GLSLShaderDataShared* dataShared)
   : GLSLShaderDefaultGL32(dataShared)
{
}

GLSLShaderDisplacement::~GLSLShaderDisplacement()
{
}

GLSLShaderDisplacement* GLSLShaderDisplacement::New()
{
   // Load shader files
   std::string vert = ManagerEnvironmentConfiguration::getLMM() + "/shaders/displacement_circ.vert";
   std::string frag = ManagerEnvironmentConfiguration::getLMM() + "/shaders/displacement_circ.frag";
   
   GLSLShaderDataShared* data = ManagerShader::loadShaderDataShared(vert, frag);
   if (data == nullptr)
      return nullptr;
   
   // Create the shader instance
   GLSLShaderDisplacement* ptr = new GLSLShaderDisplacement(data);
   
   // Create custom uniform for displacement scale
   ptr->displacementScale = new GLSLUniform("DisplacementScale", utFLOAT, data->getShaderHandle());
   float scale = 2.0f;  // Increased from 1.0 for more visible waves
   ptr->displacementScale->setValues(&scale);
   
   // Create time uniform for animation
   ptr->time = new GLSLUniform("Time", utFLOAT, data->getShaderHandle());
   float startTime = 0.0f;
   ptr->time->setValues(&startTime);
   
   return ptr;
}

