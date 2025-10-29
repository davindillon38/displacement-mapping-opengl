#pragma once
#include "GLSLShaderDefaultGL32.h"

namespace Aftr { class GLSLShaderDisplacement; }


namespace Aftr
{

/**
 * Displacement mapping shader that inherits default lighting/material behavior
 * from GLSLShaderDefaultGL32 and adds vertex displacement via heightmap.
 */
class GLSLShaderDisplacement : public GLSLShaderDefaultGL32
{
protected:
   GLSLShaderDisplacement(GLSLShaderDataShared* dataShared);
   
public:
   static GLSLShaderDisplacement* New();
   virtual ~GLSLShaderDisplacement();
   
   // Custom uniforms for displacement
   GLSLUniform* displacementScale = nullptr;
   GLSLUniform* time = nullptr;  // For animation
};

} // namespace Aftr
