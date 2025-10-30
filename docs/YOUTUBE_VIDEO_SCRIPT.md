# Ocean Displacement Mapping - YouTube Video Script

## Video Title
"Real-Time Ocean Waves with OpenGL Displacement Mapping | Computer Graphics Project"

## Video Description
Demonstrating texture-based displacement mapping to create animated ocean waves in real-time using OpenGL and GLSL shaders. This project showcases vertex shader displacement, dynamic normal calculation, and procedural animation.

Source code: https://github.com/davindillon38/displacement-mapping-opengl

---

## Script

### Introduction (0:00 - 0:20)
**[Show ocean waves animating]**

"Hi! I'm Davin, and today I'm presenting my displacement mapping project for Computer Graphics. This demo shows a real-time animated ocean surface created entirely on the GPU using OpenGL vertex shaders."

**[Quick rotation around the ocean]**

### Technical Overview (0:20 - 1:00)
**[Split screen: code + visual result]**

"The core technique here is displacement mapping - where we modify vertex positions in the vertex shader based on a height texture. Instead of just coloring pixels differently, we're actually moving the geometry."

**[Highlight vertex shader code]**

"I'm using a seamless cloud texture as a noise source. The shader samples this texture at two different frequencies - a larger scale for the main wave patterns, and a smaller scale for surface detail."

**[Show texture side by side with result]**

"By scrolling the texture coordinates over time in different directions, we get this organic rolling wave motion."

### Live Controls Demo (1:00 - 1:40)
**[Show GUI controls on screen]**

"The system has three main parameters you can adjust in real-time:"

**[Adjust Height slider]**

"Height controls the wave amplitude - how tall the peaks are and how deep the valleys go."

**[Reset, then adjust Frequency slider]**

"Frequency changes the wave density - higher values give you more, tighter waves, while lower values create broader swells."

**[Reset, then adjust Speed slider]**

"And Speed controls how fast the waves animate. You can make them gentle and slow, or turn them into a stormy sea."

**[Show combination of parameters]**

"You can combine these to create different ocean conditions - from calm water to choppy seas."

### Technical Deep Dive (1:40 - 2:30)
**[Show vertex shader code close-up]**

"Let me walk through the key technical details. In the vertex shader, I sample the cloud texture at the world position of each vertex."

**[Highlight specific code sections as you explain]**

"I'm actually doing two texture samples at different scales - this gives us both large wave patterns and fine surface detail. The heights from both samples are combined and then amplified and centered around zero."

**[Show normal calculation]**

"For proper lighting, I calculate normals by sampling the height at neighboring points and using finite differences to compute the tangent vectors. This ensures the lighting responds correctly to the wave shape."

**[Show fragment shader]**

"In the fragment shader, I apply a simple blue gradient based on height - darker blue in the valleys, lighter blue at the peaks. The Blinn-Phong lighting model adds realistic shading with an overhead directional light."

### Visual Results (2:30 - 2:50)
**[Cinematic camera movements showing the ocean]**

"The result is a convincing ocean surface with smooth, rolling waves. The lighting properly follows the wave geometry, creating highlights on peaks and shadows in troughs."

**[Close-up of wave detail]**

"The dual-layer sampling creates nice surface variation - you get both the large wave forms and the smaller ripples."

### Performance (2:50 - 3:10)
**[Show FPS counter if visible]**

"Performance-wise, this runs at 60 FPS easily, even on integrated graphics. By doing all the heavy computation in the vertex shader rather than per-pixel, and using a single texture lookup, it's very efficient."

**[Show wire frame overlay briefly]**

"The grid mesh has about 40,000 vertices, and each one is being displaced every frame based on the animated texture samples."

### Conclusion (3:10 - 3:30)
**[Final beauty shot of ocean]**

"This project demonstrates several key graphics techniques: displacement mapping, procedural animation, dynamic normal calculation, and shader-based real-time rendering."

**[Show GitHub link on screen]**

"The full source code, including the GLSL shaders and C++ setup, is available on my GitHub. Link in the description."

**[Fade out with waves]**

"Thanks for watching! If you have questions about the implementation, feel free to leave a comment."

---

## B-Roll Suggestions
- Close-up shots of individual wave peaks
- Camera flying low over the water surface
- Wireframe overlay showing vertex displacement
- Side-by-side comparison with flat plane
- Texture visualization alongside result
- Parameter adjustment montage

## On-Screen Graphics
- Title card with project name
- Code snippets at relevant moments
- Parameter labels when adjusting sliders
- GitHub repository link
- Performance metrics (FPS, vertex count)

## Video Length
Target: 3-3.5 minutes

## Music Suggestions
- Calm, oceanic ambient music
- Low volume to not overpower narration
- Fade out during technical sections

## Technical Setup
- 1920x1080 resolution
- 60 FPS recording
- Screen capture with OBS
- Voiceover recorded separately for clarity