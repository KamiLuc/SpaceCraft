struct Light
{
	vec3 color;
	float ambientIntensity;
};

struct PointLight
{
	Light base;
	vec3 position;
	float diffuseIntensity;
	float constant;
	float linear;
	float exponent;
};

struct Material
{
	float specularIntensity;
	float shininess;
};