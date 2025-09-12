#version 460 core

uniform int oct;
uniform float frequency;
uniform float amplitude;
uniform bool colorize;

out vec4 FragColor;
uniform float permutation[512];



float fade(float t) {
	return ((6 * t - 15) * t + 10) * t * t * t;
}

float lerp(float t, float mn, float mx) {
	return mn + t * (mx - mn);
}


vec2 getConstantVector(int val){
    int h = val % 4;
	if (h == 0) {
		return vec2(1, 1);
	}
	else if (h == 1) {
		return vec2(-1, 1);
	}
	else if (h == 2) {
		return vec2(-1, -1);
	}
	else {
		return vec2(1, -1);
	}
}


float calculatePerlinNoise(vec2 xy){
	ivec2 XY = ivec2(floor(xy));

	vec2 df = xy - XY;
	vec2 topRight = vec2( df.x - 1.0, df.y - 1.0 );
	vec2 topLeft = vec2( df.x, df.y - 1.0 );
	vec2 botRight = vec2( df.x - 1.0, df.y );
	vec2 botLeft = vec2( df.x, df.y );

	int valueTopRight = int(permutation[int(permutation[XY.x+1] + XY.y+1)]);
	int valueTopLeft = int(permutation[int(permutation[XY.x] + XY.y+1)]);
	int valueBottomRight = int(permutation[int(permutation[XY.x+1] + XY.y)]);
	int valueBottomLeft = int(permutation[int(permutation[XY.x] + XY.y)]);

	float dotTopRight = dot(topRight, getConstantVector(valueTopRight));
	float dotTopLeft = dot(topLeft, getConstantVector(valueTopLeft));
	float dotBottomRight = dot(botRight, getConstantVector(valueBottomRight));
	float dotBottomLeft = dot(botLeft, getConstantVector(valueBottomLeft));

	float u = fade(df.x);
	float v = fade(df.y);
	float returnable = lerp(u,
		lerp(v, dotBottomLeft, dotTopLeft),
		lerp(v, dotBottomRight, dotTopRight));

	return returnable;
}


vec3 noiseToColor(float noiseVal){
	if (noiseVal < 0.1){
		return vec3(0, 0, 0.2);
	} else if (noiseVal >= 0.1 && noiseVal < 0.2){
		return vec3(0, 0.23, 0.6);
	} else if (noiseVal >= 0.2 && noiseVal < 0.4){
		return vec3(0.1, 0.4, 0);
	}  else if (noiseVal >= 0.4 && noiseVal < 0.6){
		return vec3(0, 0.2, 0.05);
	} else if (noiseVal >= 0.6 && noiseVal < 0.8){
		return vec3(0.3, 0.3, 0.3);
	} else {
		return vec3(1,1,1);
	}

}

void main(){
	vec2 pos = gl_FragCoord.xy;
	float noiseValue = 0;
	float actingFrequency = frequency;
	float actingAmplitude = amplitude;
	for (int i = 0; i<oct; i++){
		float n = actingAmplitude * calculatePerlinNoise(pos * actingFrequency);
		noiseValue += n;

		actingFrequency *= 2.0;
		actingAmplitude *= 0.5;
	}
	noiseValue = (noiseValue+1)*0.5f;
	vec3 color;
	if (colorize){
		color = noiseToColor(noiseValue);
	} else {
		color = vec3(noiseValue);
	}
	
	FragColor = vec4(color, 1.0);
}