

#version 330 core
uniform sampler2D tex;
in vec2 texCoord;
layout (location = 0) out vec4 colour;
void main(){
	/*if (texCoord.x > 0){
	colour = vec4(texCoord.x,0,0,1);
	}
	else{*/
	colour = texture(tex, texCoord);
	/*}*/
}