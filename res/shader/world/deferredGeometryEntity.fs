#version 330 core

layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gSpecular;

in vec3  fragPos;
in vec4  colorData;
in float useTex;
in vec3  normal;

uniform sampler2D tex;

void main() {
    if (useTex > 0.5) {
        vec4 spec = texture(tex, colorData.xy);
        if (spec.a < 0.1) discard;
        gSpecular = spec;
    }
    else {
        if (colorData.a < 0.1) discard;
        gSpecular = colorData;
    }
    gPosition = vec4(fragPos, 1);
    gNormal = vec4(normalize(normal), 1);
}