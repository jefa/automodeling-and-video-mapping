#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex;
uniform vec2 texSize;
uniform vec3 color;

void main()
{
	vec2 coords = gl_TexCoord[0].st * texSize;
	gl_FragColor = vec4(color, 1.0) * texture2DRect(tex, coords);
}
