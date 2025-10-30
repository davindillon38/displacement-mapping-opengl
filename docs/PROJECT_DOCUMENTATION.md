# Ocean Displacement Mapping - Project Documentation

## Project Overview
This project implements real-time ocean wave simulation using GPU-based displacement mapping in OpenGL. The ocean surface is dynamically displaced in the vertex shader based on an animated cloud texture, creating realistic rolling wave motion.

## Technical Implementation

### Architecture
- **Engine**: AftrBurner Graphics Engine (C++ OpenGL wrapper)
- **Graphics API**: OpenGL 4.3 (Compatibility Profile)
- **Shader Language**: GLSL 4.20
- **Build System**: CMake + Visual Studio 2022

### Core Components

#### 1. Vertex Shader (`displacement_circ.vert`)
**Purpose**: Calculates displacement and normals for each vertex

**Key Features**:
- **Dual-Layer Texture Sampling**: Samples cloud texture at two different frequencies for detail
  - Layer 1: `worldPos2D * 0.1 * FrequencyMultiplier` (base waves)
  - Layer 2: `worldPos2D * 0.25 * FrequencyMultiplier` (detail waves)
- **Time-Based Animation**: Texture coordinates scroll over time to simulate wave motion
- **Height Amplification**: `(heightValue - 0.5) * 8.0` centers and amplifies displacement
- **3D Displacement**: Vertices displaced only in Z-axis (vertical)
- **Dynamic Normal Calculation**: Normals computed from height differences at neighboring points

**Algorithm**:
```glsl
// Sample texture at two scales
uv1 = worldPos * 0.1 * freq + time * speed
uv2 = worldPos * 0.25 * freq - time * speed
height = (tex(uv1) + tex(uv2) * 0.7) / 1.7

// Amplify and center around 0
height = (height - 0.5) * 8.0

// Displace vertex
vertex.z += height * DisplacementScale
```

#### 2. Fragment Shader (`displacement_circ.frag`)
**Purpose**: Applies color and lighting to the displaced surface

**Key Features**:
- **Ocean Color Gradient**: Interpolates between dark blue (valleys) and mid blue (peaks)
  - Dark Blue: `vec3(0.0, 0.1, 0.3)`
  - Mid Blue: `vec3(0.2, 0.4, 0.7)`
- **Blinn-Phong Lighting**: Ambient + diffuse + specular components
- **Height-Based Coloring**: Uses `Height` value from vertex shader
- **Minimum Brightness**: Ensures visibility even in shadows

#### 3. C++ Scene Setup (`GLViewdisplacement_grid.cpp`)
**Key Elements**:
- **Lighting**: Overhead directional light at position (0, 0, 200)
- **Ambient Light**: 0.3 for softer shadows
- **Texture Loading**: Cloud texture (`clouds_seemless.png`) loaded via ManagerTex
- **Grid Mesh**: Large flat grid mesh for displacement
- **Skybox**: Mountain skybox rotated for better sun positioning

#### 4. ImGui Controls (`AftrImGui_displacement_grid.cpp`)
**User Controls**:
- **Height Slider**: 0-50 range, controls `DisplacementScale` uniform
- **Frequency Slider**: 0.1-5.0 range, controls `FrequencyMultiplier` uniform
- **Speed Slider**: 0.1-5.0 range, controls `SpeedMultiplier` uniform

### Shader Uniforms

| Uniform | Type | Purpose |
|---------|------|---------|
| `DisplacementScale` | float | Wave height amplitude |
| `FrequencyMultiplier` | float | Wave density/pattern size |
| `SpeedMultiplier` | float | Animation speed |
| `Time` | float | Elapsed time for animation |
| `HeightMap` | sampler2D | Cloud texture for displacement |
| `ModelMat` | mat4 | Model transformation matrix |
| `MVPMat` | mat4 | Model-View-Projection matrix |

### Mathematical Details

#### Height Calculation
The height at any point is determined by:
```
h(x,y,t) = T₁(x*0.1*f + t*s) + 0.7*T₂(x*0.25*f - t*s)
height = ((h / 1.7) - 0.5) * 8.0
```
Where:
- T₁, T₂ = texture samples
- f = FrequencyMultiplier
- s = SpeedMultiplier  
- t = Time

#### Normal Calculation
Normals are computed using finite differences:
```
∂z/∂x ≈ (height(x+ε) - height(x)) / ε
∂z/∂y ≈ (height(y+ε) - height(y)) / ε
normal = normalize((-∂z/∂x, -∂z/∂y, 1))
```

## Performance Considerations

### Optimization Strategies
1. **Vertex Shader Computation**: All heavy math done per-vertex, not per-pixel
2. **Texture Caching**: Single texture loaded once and reused
3. **Efficient Normal Calculation**: Analytical calculation from height samples
4. **Single-Pass Rendering**: All effects in one draw call

### Performance Metrics
- **Target FPS**: 60
- **Typical Performance**: 60 FPS on Intel integrated graphics
- **Vertex Count**: ~40,000 vertices in grid mesh

## Assets
- **Texture**: `images/clouds_seemless.png` (seamless noise texture)
- **Skybox**: `sky_mountains+6.jpg`
- **Model**: Procedurally generated grid mesh

## Build Instructions

### Prerequisites
- Visual Studio 2022
- AftrBurner Engine installed
- CMake 3.15+

### Build Steps
1. Open project in Visual Studio 2022
2. Select x64 configuration
3. Build solution (F7)
4. Run `displacement_grid.exe`

### File Structure
```
displacement_mapping_hw/
├── shaders/
│   ├── displacement_circ.vert
│   └── displacement_circ.frag
├── src/
│   ├── GLViewdisplacement_grid.cpp
│   ├── AftrImGui_displacement_grid.cpp
│   └── GLSLShaderDisplacement.cpp
├── images/
│   └── clouds_seemless.png
└── docs/
    ├── PROJECT_DOCUMENTATION.md
    └── YOUTUBE_VIDEO_SCRIPT.md
```

## Future Enhancements
- [ ] Add foam/whitecaps at wave peaks
- [ ] Implement Gerstner waves for more realistic motion
- [ ] Add reflection/refraction effects
- [ ] Caustics on ocean floor
- [ ] Multiple light sources (sun + moon)
- [ ] Weather effects (rain, storms)

## References
- OpenGL Superbible 7th Edition
- GPU Gems: Effective Water Simulation from Physical Models
- AftrBurner Engine Documentation

## Author
Davin Dillon  
Ohio University - CS 6250 Computer Graphics  
Fall 2025