#version 420 core

layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gSpecular;

in vec2  texCoords;
in vec3  fragPos;
in vec3  normal;

uniform float time;

layout (binding = 0) uniform sampler2D tex;

void main() {
    vec4 spec = texture(tex, texCoords);
    if (spec.a < 0.1) discard;
    gSpecular = spec;

    gPosition = vec4(fragPos, 1);
    gNormal = vec4(normal, 1);
}