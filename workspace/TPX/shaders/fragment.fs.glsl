#version 330

in vec3 vPosition_vs;
in vec3 vNormals_vs;
in vec2 vTexCoords_vs;

uniform sampler2D uTexture;
uniform vec3 uColor;

out vec4 fFragColor;

void main()
{
	fFragColor = texture(uTexture, vTexCoords_vs);
}


