#version 330

in vec3 vVertex;

out vec4 FragColor;

void main() {
    FragColor = vec4(vVertex, 1.0f);
}
