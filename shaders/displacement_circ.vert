#version 420
// Texture-based Ocean Displacement

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

layout ( binding = 1 ) uniform sampler2D HeightMap;
uniform float DisplacementScale = 20.0;
uniform float Time = 0.0;
uniform float SpeedMultiplier = 1.0;
uniform float FrequencyMultiplier = 1.0;

out vec4 Color;
out vec3 VertexES;
out vec3 NormalES;
out vec2 TexCoord;
out vec4 ShadowCoord;
out flat int ShadowMapShadingState;
out float Height;
out vec2 WorldPos2D;

// Gerstner wave function
vec3 gerstnerWave(vec2 pos, vec2 direction, float wavelength, float steepness, float speed) {
    float k = 2.0 * 3.14159 / wavelength;  // Wave number
    float c = sqrt(9.8 / k);  // Wave speed from gravity
    vec2 d = normalize(direction);
    float f = k * (dot(d, pos) - c * speed * Time);
    float a = steepness / k;
    
    return vec3(
        d.x * (a * cos(f)),  // X displacement
        d.y * (a * cos(f)),  // Y displacement  
        a * sin(f)           // Z displacement (height)
    );
}




void main()
{
    Color = VertexColor;
    TexCoord = ( TexMat0 * vec4( VertexTexCoord, 0, 1 ) ).st;
    
    // Get world position FIRST
    vec4 worldPos = ModelMat * vec4(VertexPosition, 1.0);
    vec2 worldPos2D = worldPos.xy;
    WorldPos2D = worldPos2D;
    
        // Sample cloud texture with animated scrolling - EXTREME VARIATION
    vec2 uv = worldPos2D * (0.1 * FrequencyMultiplier) + vec2(Time * 0.005 * SpeedMultiplier, Time * 0.003 * SpeedMultiplier);
    // Calculate Gerstner waves (3 different directions)
    vec3 wave1 = gerstnerWave(worldPos2D, vec2(1.0, 0.3), 10.0 / FrequencyMultiplier, 0.5, SpeedMultiplier);
    vec3 wave2 = gerstnerWave(worldPos2D, vec2(0.7, -0.8), 15.0 / FrequencyMultiplier, 0.3, SpeedMultiplier * 0.8);
    vec3 wave3 = gerstnerWave(worldPos2D, vec2(-0.5, 1.0), 8.0 / FrequencyMultiplier, 0.4, SpeedMultiplier * 1.2);

    // Sum all waves
    vec3 totalDisplacement = wave1 + wave2 + wave3;
    float heightValue = totalDisplacement.z;  // Just the vertical component for now
        // Combine texture detail + rolling waves
        float finalHeight = heightValue;

    // Pass to fragment shader
    Height = finalHeight;
        
    // Displace vertex in 3D (X, Y, AND Z!)
    vec3 displacedPosition = VertexPosition;
    displacedPosition.x += totalDisplacement.x * DisplacementScale;  // Horizontal displacement
    displacedPosition.y += totalDisplacement.y * DisplacementScale;  // Horizontal displacement
    displacedPosition.z += totalDisplacement.z * DisplacementScale;  // Vertical displacement

    // Recalculate normals using texture
    // Calculate Gerstner wave normals analytically
    vec3 normal = vec3(0.0, 0.0, 1.0);  // Start with up vector

    // Add contribution from each wave
    for(int i = 0; i < 3; i++) {
        vec2 dir;
        float wavelength, steepness, speed;
        
        if(i == 0) { dir = vec2(1.0, 0.3); wavelength = 10.0 / FrequencyMultiplier; steepness = 0.5; speed = SpeedMultiplier; }
        else if(i == 1) { dir = vec2(0.7, -0.8); wavelength = 15.0 / FrequencyMultiplier; steepness = 0.3; speed = SpeedMultiplier * 0.8; }
        else { dir = vec2(-0.5, 1.0); wavelength = 8.0 / FrequencyMultiplier; steepness = 0.4; speed = SpeedMultiplier * 1.2; }
        
        float k = 2.0 * 3.14159 / wavelength;
        float c = sqrt(9.8 / k);
        vec2 d = normalize(dir);
        float f = k * (dot(d, worldPos2D) - c * speed * Time);
        float a = steepness / k;
        
        // Wave normal contribution
        normal.x -= d.x * steepness * cos(f);
        normal.y -= d.y * steepness * cos(f);
        normal.z -= steepness * sin(f);
    }

    vec3 displacedNormal = normalize(normal);
    // Transform for rendering
    NormalES = ( Cam.View * ModelMat * vec4( displacedNormal, 0 ) ).xyz;
    VertexES = ( Cam.View * ModelMat * vec4( displacedPosition, 1 ) ).xyz;
    
    ShadowCoord = Cam.Shadow * ModelMat * vec4( displacedPosition, 1 );
    ShadowMapShadingState = Cam.ShadowMapShadingState;
    
    gl_Position = MVPMat * vec4( displacedPosition, 1.0 );
}