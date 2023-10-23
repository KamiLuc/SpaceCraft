vec4 calculateLightByDirection(Light light, vec3 direction, float diffuseIntensity)
{
	vec4 ambientColor = vec4(light.color, 1.0f) * light.ambientIntensity;
	
	float diffuseFactor = max(dot(normalize(normal), normalize(direction)), 0.0f);
	vec4 diffuseColor = vec4(light.color, 1.0f) * diffuseIntensity * diffuseFactor;
	
	vec4 specularColor = vec4(0, 0, 0, 0);
	
	if(diffuseFactor > 0.0f)
	{
		vec3 fragToCamera = normalize(cameraPosition - fragPos);
		vec3 reflectedVertex = normalize(reflect(direction, normalize(normal)));
		
		float specularFactor = dot(fragToCamera, reflectedVertex);
		if(specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColor = vec4(light.color * material.specularIntensity * specularFactor, 1.0f);
		}
	}
	
	return (ambientColor + diffuseColor + specularColor);
};

vec4 calculatePointLights()
{
	vec4 totalColor = vec4(0, 0, 0, 0);

	for (int i = 0; i < pointLightCount; ++i)
	{
		vec3 direction = fragPos - pointLights[i].position;
		float distance = length(direction);
		direction = normalize(direction);

		vec4 color = calculateLightByDirection(pointLights[i].base, direction, pointLights[i].diffuseIntensity);
		float attenuation = pointLights[i].exponent * distance * distance + pointLights[i].linear * distance + pointLights[i].constant;

		totalColor += (color / attenuation);
	}

	return totalColor;
};

vec4 calculateOmnipresentLight()
{
	vec4 color = vec4(0, 0, 0, 0);
	return color + vec4(omnipresentLight.color, 1) * omnipresentLight.ambientIntensity;
}
