#version 330

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aNormals;
layout(location = 2) in vec2 aTexCoords;

out vec3 vColor;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;
uniform sampler2D uTexture;

// Sorties du shader
out vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
out vec3 vNormals_vs; // Position du sommet transformé dans l'espace View
out vec2 vTexCoords_vs; // Position du sommet transformé dans l'espace View

void main() {
	vPosition_vs = (uMVMatrix * vec4(aVertexPosition,1)).xyz;
	vNormals_vs=(uNormalMatrix*vec4(aNormals,0)).xyz;
	vTexCoords_vs=aTexCoords;
	gl_Position=uMVPMatrix*vec4(aVertexPosition,1);
}

//