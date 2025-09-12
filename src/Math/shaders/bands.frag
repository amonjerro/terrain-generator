#version 460 core
#define PI 3.14159265358979

uniform float waveScale;
uniform sampler2D noiseTex; 

out vec4 FragColor;

vec2 offsets[9] = vec2[](
	vec2(-1,-1), vec2(0,-1), vec2(1,-1),
	vec2(-1,0), vec2(0,0), vec2(1,0),
	vec2(-1,1), vec2(0,1), vec2(1,1)
);
float samples[9];

vec3 paintWindDirection(vec2 pos){
	float east = 0.5*sin(waveScale*pos.y)+1;
	float west = 0.5*cos(waveScale*pos.y+(0.5*PI))+1;
	float rVal = 0.5*(east-west+1);
	float bVal = 0.5*(west-east+1);

	return vec3(rVal,0, bVal);
}

float calculateXDirection(vec2 pos){
	return sin(waveScale*pos.y);
}

float invertNoise(float noiseVal){
	return -1*(noiseVal-1);
}

vec3 makeWindVector(float direction){
	float absVal = abs(direction);

	if (direction < 0){
		float remainingWindX = samples[3] - invertNoise(samples[4])*absVal;
		float yDirection = samples[0] < samples[6] ? 1 : -1;
		float zVal = yDirection == 1 ? samples[4] - samples[0] : samples[6] - samples[4];
		return vec3(remainingWindX, yDirection, zVal);
	} else {
		float remainingWindX = samples[5] - invertNoise(samples[4])*absVal;
		float yDirection = samples[2] < samples[8] ? 1 : -1;
		float zVal = yDirection == 1 ? samples[4] - samples[2] : samples[8] - samples[4];
		return vec3(remainingWindX, yDirection, zVal);
	}
}

void main(){
	vec2 pos = gl_FragCoord.xy;
	vec2 uv = pos / vec2(textureSize(noiseTex,0));
	vec2 texelSize = 1.0 / vec2(textureSize(noiseTex,0));
	for(int i = 0; i < 9; i++){
		vec2 coord = uv + offsets[i]*texelSize;
		samples[i] = texture(noiseTex, coord).r;
	}

	vec3 directionColor = paintWindDirection(pos);
	vec3 windVector =  makeWindVector(calculateXDirection(pos));
	//FragColor = vec4(windVectors(calculateWindDirection(pos)), 1);
	FragColor = vec4(windVector,1);
	//FragColor = vec4(vec3(samples[4]),1);
}

