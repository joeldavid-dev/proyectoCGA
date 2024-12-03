#version 330 core

struct Light {
    vec3 ambient;
};

in vec3 our_uv;
out vec4 color;

uniform Light light;
uniform samplerCube skybox;
uniform float lowerLimit = 0.0;
uniform float upperLimit = 0.04;
uniform vec3 fogColor;

void main()
{
    vec4 colorText = texture(skybox, our_uv);
    vec4 ambientExtend = vec4(light.ambient, 1.0f);
    color = texture(skybox, our_uv) * ambientExtend;

    float factor = (our_uv.y - lowerLimit) / (upperLimit - lowerLimit);
    factor = clamp(factor,0.0 ,0.5);
    color = mix(vec4(fogColor, 1.0), color, factor);
}
