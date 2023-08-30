#version 330

layout (location = 0) in vec3 vertex;

uniform mat4 mvp;

out vec3 vVertex;

void main ()
{
   // We add 0.5 to make the vertex values be within [0, 1]
   vVertex = vertex + 0.5;

   gl_Position = mvp*vec4(vertex, 1.0);
}
