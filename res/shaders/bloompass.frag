#version 430
layout(location = 0) uniform sampler2D geoRender;
layout(location = 2) uniform sampler2D lightAlbedo;
in vec2 vUV;
in float deltaTime;
out vec4 outColor;
vec4 sum = vec4(0);
vec4 white = vec4(1,1,1,1);
void main()
{
	vec4 thres = vec4(0.5,0.5,0.5,0.5);

    vec4 albedo = texture(geoRender, vUV);
    vec4 la = texture(lightAlbedo, vUV);
    for(int i = -11; i < 11; i++)
	{
        for(int j = - 11; j < 11; j++)
		{
            vec2 offset = vec2(i,j) * 0.005;
            sum += texture2D(geoRender, vUV + offset);
        }

	}

	if(length(albedo) > length(thres))
	{
		outColor =  vec4(0,1,1,1);
    }
	else
	{
        outColor = ((sum / 529) + (albedo + la ));
    }
}