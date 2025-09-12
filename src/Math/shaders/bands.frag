#version 460 core
#define PI 3.14159265358979

uniform float waveScale;

out vec4 FragColor;


vec3 calculateWindDirection(vec2 pos){
	float east = 0.5*sin(waveScale*pos.y)+1;
	float west = 0.5*cos(waveScale*pos.y+(0.5*PI))+1;
	float rVal = 0.5*(east-west+1);
	float bVal = 0.5*(west-east+1);

	return vec3(rVal,0, bVal);
}

void main(){
	vec2 pos = gl_FragCoord.xy;
	FragColor = vec4(calculateWindDirection(pos), 1);
}

