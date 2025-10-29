#version 120

void main()
{
    // Simple pass-through - no displacement for testing
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
