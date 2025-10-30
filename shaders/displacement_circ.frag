#version 420
// Fragment Shader - Ocean Colors

in vec4 Color;
in vec3 VertexES;
in vec3 NormalES;
in vec2 TexCoord;
in vec4 ShadowCoord;
in flat int ShadowMapShadingState;
in float Height;
in vec2 WorldPos2D;

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

layout ( binding = 1 ) uniform sampler2D HeightMap;
uniform float Time = 0.0;
uniform float SpeedMultiplier = 1.0;
uniform float FrequencyMultiplier = 1.0;

layout ( location = 0 ) out vec4 FragColor;

void main()
{
    // Sample texture to match vertex shader - EXTREME VARIATION
    vec2 uv = WorldPos2D * (0.1 * FrequencyMultiplier) + vec2(Time * 0.005 * SpeedMultiplier, Time * 0.003 * SpeedMultiplier);
    float heightValue = texture(HeightMap, uv).r;
    vec2 uv2 = WorldPos2D * (0.25 * FrequencyMultiplier) - vec2(Time * 0.003 * SpeedMultiplier, Time * 0.004 * SpeedMultiplier);
    heightValue += texture(HeightMap, uv2).r * 0.7;
    heightValue = heightValue / 1.7;
    
    // DRAMATICALLY increase contrast for peaks and valleys
    heightValue = (heightValue - 0.5) * 4.0;  // Center around 0, moderate amplification
    
    // Simple blue gradient - dark valleys to mid-blue peaks
    vec3 darkBlue = vec3(0.0, 0.1, 0.3);    // Dark blue for valleys
    vec3 midBlue = vec3(0.2, 0.4, 0.7);     // Mid blue for peaks
    vec3 oceanColor = mix(darkBlue, midBlue, heightValue);
        
    // Blinn-Phong lighting
    vec3 n = normalize(NormalES);
    vec3 v = normalize(-VertexES);
    
    // Ambient lighting
    vec3 ambient = Lights.GlobalAmbient.rgb * Material.Ka.rgb * oceanColor * 0.5;
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);
    
    for (int i = 0; i < Lights.NumLights && i < 8; i++)
    {
        vec3 lightDir = normalize(Lights.PosEye[i].xyz - VertexES);
        vec3 h = normalize(v + lightDir);
        
        float diff = max(dot(n, lightDir), 0.0);
        diffuse += diff * Lights.Irgba[i].rgb * Material.Kd.rgb * oceanColor;
        
        float spec = pow(max(dot(n, h), 0.0), Material.SpecularCoeff);
        specular += spec * Lights.Irgba[i].rgb * Material.Ks.rgb;
    }
    
    vec3 finalColor = ambient + diffuse + specular;
    
    // Add minimum brightness
    float minBrightness = 0.3;
    finalColor = max(finalColor, oceanColor * minBrightness);
    
    FragColor = vec4(finalColor, 1.0);
}