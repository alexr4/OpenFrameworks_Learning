#version 120
#extension GL_ARB_texture_rectangle: enable
#define PI (3.141592653558979323846)
#define TWO_PI (2*PI)

uniform int ksector = 10;
uniform float kangleRad = 0.0;
uniform vec2 kcenter = vec2(1280.0, 720.0) / 2.0;
uniform vec2 screenCenter = vec2(1280.0, 720.0) / 2.0;
uniform sampler2DRect inputTexture;

void main()
{
	vec2 texCoord = gl_TexCoord[0].xy;
	vec2 v = texCoord - screenCenter;
	float r = length(v);
	float a = atan(v.x, v.y);

	float A = TWO_PI / float(ksector);
	a = mod(a, A);
	if(a > A/2.0)
	{
		a = A - a;
	}
	a -= kangleRad;

	vec2 u = vec2(cos(a), sin(a)) * r;
	u += kcenter;

	gl_FragColor = texture2DRect(inputTexture, u);
}