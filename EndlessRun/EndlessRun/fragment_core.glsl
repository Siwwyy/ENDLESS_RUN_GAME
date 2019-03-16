#version 440

//struct Material
//{
//	vec3 ambient;
//	vec3 diffuse;
//	vec3 specular;
//	sampler2D diffuseTex;
//	sampler2D specularTex;
//};
//
//in vec3 vs_position;
//in vec3 vs_color;
//in vec2 vs_texcoord;
//in vec3 vs_normal;
//
//out vec4 fs_color;
//
////Uniforms
//uniform Material material;
//uniform vec3 lightPos0;
//uniform vec3 cameraPos;
//
////Functions
//vec3 calculateAmbient(Material material)
//{
//	return material.ambient;
//}
//
//vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0)
//{
//	vec3 posToLightDirVec = normalize(lightPos0 - vs_position);
//	float diffuse = clamp(dot(posToLightDirVec, vs_normal), 0, 1);
//	vec3 diffuseFinal = material.diffuse * diffuse;
//
//	return diffuseFinal;
//}
//
//vec3 calculateSpecular(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0, vec3 cameraPos)
//{
//	vec3 lightToPosDirVec = normalize(vs_position - lightPos0);
//	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
//	vec3 posToViewDirVec = normalize(cameraPos - vs_position);
//	float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 35);
//	vec3 specularFinal = material.specular * specularConstant * texture(material.specularTex, vs_texcoord).rgb;
//
//	return specularFinal;
//}
//
//void main()
//{
//	//fs_color = vec4(vs_color, 1.f);
//	//fs_color = texture(texture0, vs_texcoord) * texture(texture1, vs_texcoord) * vec4(vs_color, 1.f);
//
//	//Ambient light
//	vec3 ambientFinal = calculateAmbient(material);
//
//	//Diffuse light
//	vec3 diffuseFinal = calculateDiffuse(material, vs_position, vs_normal, lightPos0);
//
//	//Specular light
//	vec3 specularFinal = calculateSpecular(material, vs_position, vs_normal, lightPos0, cameraPos);
//
//	//Attenuation
//
//	//Final light
//	fs_color =
//		texture(material.diffuseTex, vs_texcoord)
//		* (vec4(ambientFinal, 1.f) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f));
//}

struct Material
{
	//data for modify the color
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;	//real color data
	sampler2D specularTex;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;


//UNIFORMS
uniform Material material;
//material.ambient;

uniform vec3 lightPos0;
uniform vec3 cameraPos;


//Functions
//return type, name, parameters
vec3 calculateAmbient(Material material)
{
	return material.ambient;
}

vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0)
{
	vec3 posToLightDirVec = normalize(lightPos0 - vs_position);
//	vec3 diffuseColor = vec3(1.f, 1.f, 1.f);
	float diffuse = clamp(dot(posToLightDirVec, vs_normal), 0, 1);
	vec3 diffuseFinal = material.diffuse * diffuse;

	return diffuseFinal;
}

vec3 calculateSpecular(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0, vec3 cameraPos)
{
	vec3 lightToPosDirVec = normalize(vs_position - lightPos0);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(cameraPos - vs_position);
	float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 30);
	vec3 specularFinal = material.specular * specularConstant;

	return specularFinal;
}

void main()
{
	//fs_color = vec4(vs_color, 1.f);
	//fs_color = texture(texture0, vs_texcoord)
	//fs_color = texture(texture1, vs_texcoord)
	//fs_color = texture(texture0, vs_texcoord)*vec4(vs_color, 1.f);	//rainbow color by multiplaying the color
	//fs_color = texture(texture1, vs_texcoord)*vec4(vs_color, 1.f);	//rainbow color by multiplaying the color
	//fs_color = (texture(texture0, vs_texcoord)+texture(texture1, vs_texcoord))*vec4(vs_color, 1.f);	//rainbow color by multiplaying the color and next image
	//fs_color = ((texture(texture0, vs_texcoord)*vec4(vs_color, 1.f))+texture(texture1, vs_texcoord));	//basic color without multiplaying the color and next image


	//int *wsk_a = &a;

	//foo(wsk_a);

	//Ambient light
	//vec3 ambientLight = material.ambient;
	vec3 ambientFinal= calculateAmbient(material);

	//Specular light
	//vec3 lightToPosDirVec = normalize(lightPos0 - vs_position);
	//vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
	//vec3 posToViewDirVec = normalize(vs_position - cameraPos);
	//float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 30);
	vec3 specularFinal = calculateSpecular(material, vs_position, vs_normal, lightPos0, cameraPos);

	//Attenuation

	//Diffuse light
	//vec3 posToLightDirVec = normalize(vs_position - lightPos0);
	//vec3 diffuseColor = vec3(1.f, 1.f, 1.f);
	//float diffuse = clamp(dot(posToLightDirVec, vs_normal),0,1);
	vec3 diffuseFinal = calculateDiffuse(material,vs_position,vs_normal,lightPos0);

	//fs_color = texture(material.diffuseTex, vs_texcoord) * vec4(vs_color, 1.f) * (vec4(ambientLight, 1.f) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f)); //ranbowish color
	fs_color = texture(material.diffuseTex, vs_texcoord) * vec4(vs_color, 1.f) * (vec4(ambientFinal, 1.f) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f));	//specular light
	//fs_color = texture(material.diffuseTex, vs_texcoord) * vec4(vs_color, 1.f) * (vec4(ambientFinal, 1.f) + vec4(diffuseFinal, 1.f));	//without specular
}