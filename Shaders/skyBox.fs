#version 330 core

struct Light {
    vec3 ambient;
};

in vec3 our_uv;
out vec4 color;

uniform Light light;
uniform samplerCube skybox;

void main()
{
    vec4 colorText = texture(skybox, our_uv);
    vec4 ambientExtend = vec4(light.ambient, 1.0f);
    color = texture(skybox, our_uv) * ambientExtend;
    //color = texture(skybox, our_uv); // linea original
}
