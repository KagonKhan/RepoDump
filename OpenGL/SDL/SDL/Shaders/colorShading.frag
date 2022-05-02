#version 130

in vec4 fragmentColor;
in vec2 fragmentPosition;
in vec2 fragmentUV;



out vec4 color;




uniform float time;
uniform sampler2D mySampler;


void main(){	


	vec4 textureColor = texture(mySampler, fragmentUV);

	time;


	color = textureColor * fragmentColor;

	color = vec4(
				fragmentColor.r * (cos(fragmentPosition.x * 4.f + time) + 1.f) / 2.f,
				fragmentColor.g * (cos(fragmentPosition.y * 8.f + time) + 1.f) / 2.f,
				fragmentColor.b * (cos(fragmentPosition.x * 1.5f+ time) + 1.f) / 2.f,
				fragmentColor.a
			) * textureColor;
}



/*fragmentColor +	vec4(
		(cos(time) + 1.0)		* 0.5,
		(cos(time + 2.0) + 1.0) * 0.5,
		(sin(time + 1.0) + 1.0) * 0.5,
		 0.0
	); 
	
*/