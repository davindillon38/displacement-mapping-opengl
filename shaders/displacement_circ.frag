#version 420
// Test Fragment Shader - Radial gradient from UVs (ignores heightmap)

in vec4 Color;
in vec3 VertexES;
in vec3 NormalES;
in vec2 TexCoord;
in vec4 ShadowCoord;
in flat int ShadowMapShadingState;
in float Height;

struct MaterialInfo
{
   vec4 Ka;
   vec4 Kd;
   vec4 Ks;
   float SpecularCoeff;
};
uniform MaterialInfo Material;

layout ( binding = 1, std140 ) uniform LightInfo
{
   vec4 PosEye[8];
   vec4 Irgba[8];
   vec4 GlobalAmbient;
   int NumLights;
} Lights;

uniform float Time = 0.0;

layout ( location = 0 ) out vec4 FragColor;

layout ( binding = 0 ) uniform sampler2D Texture0;
layout ( binding = 1 ) uniform sampler2D HeightMap;

// HSV to RGB conversion
vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
    // TEST: Create radial concentric circles from UVs
    // This ignores the heightmap texture to test if UVs work
    
    vec2 center = vec2(0.5, 0.5);
    vec2 toCenter = TexCoord - center;
    float dist = length(toCenter);  // Distance from center (0 = center, ~0.7 = corner)
    
    // Create multiple rings - multiply dist to get more circles
    float hue = dist * 5.0 + Time * 0.1;  // 5.0 = number of color rings
    hue = fract(hue);  // Wrap to 0-1
    
    float saturation = 0.8;
    float value = 0.9;
    
    vec3 rainbowColor = hsv2rgb(vec3(hue, saturation, value));
    
    // Simple lighting (Blinn-Phong)
    vec3 n = normalize(NormalES);
    vec3 v = normalize(-VertexES);
    
    vec3 ambient = Lights.GlobalAmbient.rgb * Material.Ka.rgb;
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);
    
    for (int i = 0; i < Lights.NumLights && i < 8; i++)
    {
        vec3 lightDir = normalize(Lights.PosEye[i].xyz - VertexES);
        vec3 h = normalize(v + lightDir);
        
        float diff = max(dot(n, lightDir), 0.0);
        diffuse += diff * Lights.Irgba[i].rgb * Material.Kd.rgb * rainbowColor;
        
        float spec = pow(max(dot(n, h), 0.0), Material.SpecularCoeff);
        specular += spec * Lights.Irgba[i].rgb * Material.Ks.rgb;
    }
    
    vec3 finalColor = ambient + diffuse + specular;
    FragColor = vec4(finalColor, 1.0);
}
