#version 420
// Test Vertex Shader - Simple UV wrapping

layout ( location = 0 ) in vec3 VertexPosition;
layout ( location = 1 ) in vec3 VertexNormal;
layout ( location = 2 ) in vec2 VertexTexCoord;
layout ( location = 3 ) in vec4 VertexColor;

uniform mat4 ModelMat;
uniform mat4 NormalMat;
uniform mat4 TexMat0;
uniform mat4 MVPMat;

layout ( binding = 0, std140 ) uniform CameraTransforms
{
   mat4 View;
   mat4 Projection;
   mat4 Shadow;
   int ShadowMapShadingState;
} Cam;

// Heightmap for displacement
layout ( binding = 1 ) uniform sampler2D HeightMap;
uniform float DisplacementScale = 2.0;
uniform float Time = 0.0;

out vec4 Color;
out vec3 VertexES;
out vec3 NormalES;
out vec2 TexCoord;
out vec4 ShadowCoord;
out flat int ShadowMapShadingState;
out float Height;

void main()
{
    Color = VertexColor;
    
    // Wrap UVs to 0-1 range (fixes tiling/quadrant issues)
    vec2 animatedUV = fract(VertexTexCoord);
    
    TexCoord = ( TexMat0 * vec4( animatedUV, 0, 1 ) ).st;
    
    // Sample heightmap
    float height = texture(HeightMap, animatedUV).r;
    Height = height;
    
    // Displace vertex upward based on height
    vec3 displacedPosition = VertexPosition;
    displacedPosition.z += height * DisplacementScale;
    
    // Transform displaced position and normals
    NormalES = ( Cam.View * ModelMat * vec4( VertexNormal, 0 ) ).xyz;
    VertexES = ( Cam.View * ModelMat * vec4( displacedPosition, 1 ) ).xyz;
    
    ShadowCoord = Cam.Shadow * ModelMat * vec4( displacedPosition, 1 );
    ShadowMapShadingState = Cam.ShadowMapShadingState;
    
    // Final clip-space position
    gl_Position = MVPMat * vec4( displacedPosition, 1.0 );
}
