#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;

	float shininess;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
in vec3 FragPos;
in vec3 Normal;

out vec4 color;

in vec3 ourColor;
in vec2 TexCoord;


uniform vec3 viewPos;
uniform Material material;
uniform Light light;


uniform sampler2D ourTexture2;
uniform float mixValue;

void main() {

    color = mix( texture(material.diffuse, TexCoord), texture(ourTexture2, vec2( TexCoord.x, TexCoord.y)), mixValue);


	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diffusion = max(dot(norm, lightDir), 0.0);


	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);


	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
	vec3 diffuse = light.diffuse * diffusion * vec3(texture(material.diffuse, TexCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

	vec3 result = ambient + diffuse + specular;


	color = color * vec4(result, 1.0);
}

