# YouTube Video Script - Displacement Mapped Grid

## Video Title
"Real-time Displacement Mapping with Animated Rainbow Waves in OpenGL"

## Video Length Target
3-5 minutes

---

## INTRO (15-30 seconds)

**[Show final result - animated rainbow concentric circles]**

"Hi! Today I'm showing my displacement-mapped grid project for Computer Graphics class. This is a flat plane that becomes a 3D surface using GPU shader programming, with animated rainbow colors flowing through concentric wave patterns."

---

## SECTION 1: What is Displacement Mapping? (30 seconds)

**[Show side-by-side: flat plane → displaced 3D surface]**

"Displacement mapping is a technique where we modify vertex positions in the vertex shader to create 3D geometry from flat surfaces. Unlike normal mapping which just fakes lighting, displacement mapping actually moves the vertices to create real geometry."

**[Point to wireframe view showing vertex movement]**

"Here you can see the vertices actually being moved up and down to create the wave pattern."

---

## SECTION 2: The Technical Implementation (60-90 seconds)

**[Show code snippets on screen]**

"The magic happens in two GLSL shaders:

**Vertex Shader:**
- Takes each vertex's UV coordinates
- Calculates distance from the center point
- Uses that distance to compute a height value
- Moves the vertex up or down in the Z direction

**Fragment Shader:**
- Uses the same distance calculation
- Converts it to a rainbow color using HSV color space
- Adds time to create the animation
- Applies Blinn-Phong lighting for realistic shading"

**[Show the key code sections briefly]**

```glsl
// Distance from center creates concentric pattern
vec2 toCenter = UV - vec2(0.5, 0.5);
float dist = length(toCenter);

// Displace vertex height
displacedPosition.z += height * 2.0;

// Animate colors over time
float hue = dist * 5.0 + Time * 0.1;
```

---

## SECTION 3: Key Features (45 seconds)

**[Show each feature as you mention it]**

"This project includes several cool features:

1. **Procedural Generation** - The pattern is generated mathematically in real-time, no textures needed

2. **Real-time Animation** - The rainbow colors cycle continuously at 60 FPS

3. **Custom Shader Class** - I created a GLSLShaderDisplacement class to manage the shader

4. **Smooth Lighting** - Blinn-Phong lighting model shows off the 3D geometry

5. **Concentric Waves** - Five color rings flow outward from the center"

---

## SECTION 4: Customization (30 seconds)

**[Show parameter changes in real-time]**

"The effect is easily customizable by changing just a few numbers:

- Number of rings: 3, 5, or 10 concentric circles
- Animation speed: slower or faster color cycling  
- Displacement height: subtle ripples or tall waves
- Color saturation: pastel or vibrant"

**[Demo: show 3 rings, then 10 rings, then change animation speed]**

---

## SECTION 5: Technical Details (30 seconds)

**[Show Visual Studio / project structure]**

"Built using:
- AftrBurner Engine (OpenGL 4.3)
- C++ for scene management
- GLSL for vertex and fragment shaders
- 400x400 vertex grid (160,000 vertices)
- Runs at 60 FPS"

**[Show file structure briefly]**

---

## CONCLUSION (15-30 seconds)

**[Return to showing the animated effect]**

"This project demonstrates displacement mapping, procedural generation, shader programming, and real-time animation. The result is a hypnotic flowing rainbow wave that's all generated on the GPU."

**[Zoom out to show full scene with plane, skybox, etc]**

"Thanks for watching! Code and documentation available in the description."

---

## OPTIONAL B-ROLL FOOTAGE

- Wireframe view showing vertex displacement
- Side view showing 3D height
- Top-down view showing concentric pattern
- Close-up of color transitions
- Code editor showing shader files
- Visual Studio compilation
- Parameter tweaking demonstrations

---

## VIDEO RECORDING TIPS

### Software Needed
- **OBS Studio** (free) - for screen recording
- **Audacity** (free) - for audio recording/cleanup
- **DaVinci Resolve** (free) - for video editing
- OR just use **Windows Game Bar** (Win+G) for simple capture

### Recording Setup
1. **Set resolution to 1920x1080**
2. **Record at 60 FPS** to show smooth animation
3. **Enable audio** for voice narration
4. **Use Push-to-Talk** if recording live commentary

### What to Record
1. **Full-screen running application** (3-4 different angles/zoom levels)
2. **Code sections** in Visual Studio (zoom in so text is readable)
3. **File structure** in Explorer
4. **Wireframe mode** if available (shows displacement geometry)

### Editing Tips
- Add **text overlays** for key points
- Use **slow motion** (50% speed) when showing code
- Add **arrows/circles** to highlight important parts
- Include **background music** (copyright-free) at low volume
- Add **chapter markers** for each section

### Audio Tips
- Record in a **quiet room**
- Use a **decent microphone** (or phone headset)
- Speak **clearly and at moderate pace**
- Record **script separately** if nervous (easier to edit)
- Remove **"um"s and long pauses** in editing

---

## YOUTUBE DESCRIPTION TEMPLATE

```
Real-time Displacement Mapping with Animated Rainbow Waves

A computer graphics project demonstrating GPU-accelerated displacement mapping 
with procedurally-generated animated patterns. Built using OpenGL 4.3 and GLSL 
shaders in the AftrBurner Engine.

⭐ Key Features:
• Real-time vertex displacement on GPU
• Procedural concentric wave generation
• Animated rainbow color cycling
• Blinn-Phong lighting model
• 60 FPS performance with 160k vertices

🛠️ Technologies:
• C++ / OpenGL 4.3
• GLSL (Vertex & Fragment Shaders)
• AftrBurner Engine
• Visual Studio 2022

📚 Project Documentation:
[Link to GitHub or documentation]

🎓 Course: Computer Graphics - Fall 2025
Ohio University

#OpenGL #ComputerGraphics #GLSL #DisplacementMapping #ShaderProgramming 
#GameDev #GraphicsProgramming
```

---

## YOUTUBE THUMBNAIL IDEAS

1. **Split screen**: Flat plane | 3D displaced surface
2. **Close-up**: Rainbow concentric circles with "DISPLACEMENT MAPPING" text
3. **Before/After**: Gray flat grid → Colorful waves
4. **Code + Result**: Shader code on left, rendered output on right
5. **Action shot**: Mid-animation with motion blur effect

### Thumbnail Text Options
- "GPU DISPLACEMENT MAPPING"
- "VERTEX SHADERS IN ACTION"  
- "PROCEDURAL WAVES"
- "REAL-TIME 3D"
- "160K VERTICES • 60 FPS"

---

## BACKUP SCRIPT (If Nervous)

Just record yourself saying:

"This is my displacement mapping project. [pause] 

It takes a flat plane and turns it into a 3D surface using vertex shaders. [pause]

The rainbow colors animate in real-time based on distance from the center. [pause]

Everything runs at 60 frames per second on the GPU. [pause]

The pattern is generated procedurally - no textures required."

**Then add text overlays in editing to explain technical details!**
