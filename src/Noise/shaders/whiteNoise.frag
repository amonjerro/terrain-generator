#version 460


out vec4 FragColor;

float random(vec2 st){
	return fract( sin( dot(st.xy, vec2(12.9898, 78.233)) ) * 43758.543123 );
}

void main(){
	float noiseValue = random(gl_FragCoord.xy);
	FragColor = vec4(noiseValue, noiseValue, noiseValue, 1.0);
}