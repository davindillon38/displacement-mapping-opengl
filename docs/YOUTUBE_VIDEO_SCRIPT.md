# Ocean Displacement Mapping - YouTube Video Script

## Video Title
"Real-Time Ocean Waves with OpenGL Displacement Mapping | Computer Graphics Project"

## Video Description
Demonstrating texture-based displacement mapping to create animated ocean waves in real-time using OpenGL and GLSL shaders. This project showcases vertex shader displacement, dynamic normal calculation, and procedural animation.

Source code: https://github.com/davindillon38/displacement-mapping-opengl

---

Script
[Screen shows launching the application]
"Hello and welcome to my channel. For my first video, I'd like to show you this project I just finished for my graduate course in advanced graphics. I'm launching it now."
"Alright, so This is an animated ocean surface I built in OpenGL."
"The assignment was to do displacement mapping - basically moving vertices around to create 3D shapes. But when I started playing with it, I felt like it could do a good job of mimicking ocean waves."
"So I've got these controls here - speed is pretty self-explanatory - faster or slower wave motion."
"Frequency controls how many waves you get - more choppy or more smooth and rolling."
"The height slider makes the waves taller or flatter. See how that changes the amplitude?"

"What's actually happening under the hood is pretty interesting. I'm using something called Gerstner waves - it's this mathematical function that ocean researchers came up with to simulate realistic wave motion."
"Unlike just moving vertices straight up and down, Gerstner waves make the water move in these circular patterns, which is how real ocean waves actually work. that's what makes this nice rolling effect."
"The cool part is this is all happening in real-time on the GPU. The vertex shader is calculating the wave positions for every single vertex, every frame. And I'm using multiple waves going in different directions, which creates this natural-looking randomness."
"You can make it calm like this, or crank it up and get something more stormy."
"So yeah - I started with a displacement mapping assignment, and ended up with an ocean simulator. The code's on my GitHub (davindillon38) if anyone wants to check it out."
"Thanks for watching!"
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
