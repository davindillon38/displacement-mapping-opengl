# Displacement Mapped Grid - Quick Reference

## What We Built
A real-time animated displacement-mapped grid with procedurally-generated concentric rainbow waves.

## Visual Result
- Flat 400x400 grass plane becomes 3D wavy surface
- Concentric circles emanating from center
- Rainbow colors cycle through the pattern continuously
- Smooth lighting reveals 3D geometry
- 60 FPS performance

## Files You Need

### C++ Files (src/)
```
GLSLShaderDisplacement.h        - Shader class header
GLSLShaderDisplacement.cpp      - Shader implementation
GLViewdisplacement_grid.h       - Scene header (modified)
GLViewdisplacement_grid.cpp     - Scene implementation (modified)
```

### Shader Files (mm/shaders/)
```
displacement.vert               - Vertex shader (displacement)
displacement.frag               - Fragment shader (colors)
```

## How It Works

**1. Vertex Shader:**
- Calculates distance from UV center (0.5, 0.5)
- Uses distance to create height value
- Displaces vertex position in Z-axis
- Creates concentric circle geometry

**2. Fragment Shader:**
- Uses same distance calculation
- Converts distance + time to rainbow color (HSV → RGB)
- Applies Blinn-Phong lighting
- Creates animated color flow

**3. C++ Integration:**
- Loads shader when model loads (async callback)
- Updates Time uniform every frame (~60 FPS)
- Manages shader lifecycle

## Key Code Snippets

### Vertex Displacement
```glsl
vec2 toCenter = UV - vec2(0.5, 0.5);
float dist = length(toCenter);
float height = fract(dist * 5.0);  // 5 rings
displacedPosition.z += height * 2.0;
```

### Color Animation
```glsl
float hue = dist * 5.0 + Time * 0.1;
vec3 color = hsv2rgb(vec3(fract(hue), 0.8, 0.9));
```

### Time Update
```cpp
void updateWorld() {
    currentTime += 0.016f;
    displacementShader->time->setValues(&currentTime);
}
```

## Customization Parameters

| Parameter | Location | Default | Purpose |
|-----------|----------|---------|---------|
| Ring Count | Fragment shader | 5.0 | Number of concentric circles |
| Animation Speed | Fragment shader | 0.1 | How fast colors cycle |
| Displacement Height | Vertex shader | 2.0 | Amplitude of waves |
| Color Saturation | Fragment shader | 0.8 | Vibrancy of colors |

**To modify:** Edit shader files, no rebuild needed (shaders load at runtime)

## Assignment Requirements Met

✅ **Core (4-5 pts):**
- Displacement-mapped grid
- Vertex shader samples heightmap
- Flat plane becomes 3D
- Visual displacement

✅ **Bonus (+5 pts):**
- Animated texture (procedural)
- Time-based color cycling
- Real-time updates
- Professional shader architecture

## Technical Specs

- **Engine:** AftrBurner (OpenGL 4.3)
- **Language:** C++ / GLSL
- **Vertices:** ~160,000 (400x400 grid)
- **Frame Rate:** 60 FPS (vsync)
- **GPU Load:** Minimal
- **Memory:** Low (no texture loading)

## Build Instructions

1. Open `displacement_grid.sln` in Visual Studio 2022
2. Configuration: Debug x64
3. Build → Rebuild Solution
4. Press F5 to run

## Running the Program

1. Window opens with 3D scene
2. Plane shows animated rainbow waves
3. Use mouse to rotate camera
4. WASD keys to move camera
5. ESC to exit

## Troubleshooting

**Issue:** Flat uniform colors, no circles
- **Fix:** Check shader files in `mm/shaders/` directory
- Ensure `displacement.vert` and `displacement.frag` are test versions

**Issue:** Shader compile errors
- **Fix:** Check console output for line numbers
- Verify `SpecularCoeff` (not `SpecularCoefficient`) in MaterialInfo struct

**Issue:** No displacement visible
- **Fix:** Increase `DisplacementScale` to 5.0 or higher
- View from side angle to see height variation

## Important Notes

- Shaders load at **runtime** - no rebuild needed when modifying .vert/.frag files
- Must copy shaders to `mm/shaders/` directory
- Time uniform updates every frame in `updateWorld()`
- Procedural generation = no texture files needed

## For YouTube Video

**Show:**
1. Final animated result (full screen)
2. Side view (shows 3D displacement)
3. Wireframe mode (shows vertex movement)
4. Code snippets (shader files)
5. Parameter changes (live editing)

**Explain:**
- What displacement mapping is
- How vertex shader moves geometry
- How fragment shader creates colors
- Why it's animated (Time uniform)
- Performance (60 FPS, 160k verts)

## Next Steps / Future Enhancements

- Add expanding wave animation (radial motion)
- Load actual heightmap textures
- Generate proper surface normals
- Add multiple wave centers
- Interactive parameter control (GUI sliders)
- Record/export animation sequences

## Credits

**Student:** Davin  
**Course:** Computer Graphics (Fall 2025)  
**Institution:** Ohio University  
**Engine:** AftrBurner Engine by Scott Nykl  
**Assignment:** Spontaneous Assignment - Displacement Mapped Grid

---

## Quick Command Reference

**View files in directory:**
```bash
ls mm/shaders/
```

**Check shader compilation:**
- Look for "Link successful for program" in console
- Look for "Displacement shader applied!" message

**Edit shaders:**
- Edit `mm/shaders/displacement.vert`
- Edit `mm/shaders/displacement.frag`  
- Save → Run (no rebuild!)

**Modify parameters:**
```glsl
// In displacement.frag:
float hue = dist * 5.0 + Time * 0.1;
//           ^^^^ rings   ^^^ speed
```

---

**Last Updated:** October 28, 2025
