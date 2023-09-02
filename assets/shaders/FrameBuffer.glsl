#type vertex
#version 460 core
			
layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

void main()
{
	gl_Position = vec4(a_Position.x, a_Position.y, 0.0, 1.0);
	v_TexCoord = a_TexCoord;
}

#type fragment
#version 460 core
		
out vec4 color;
in vec2 v_TexCoord;

uniform sampler2D u_ScreenTexture;

void main()
{
	//inversion
	//vec4 test = vec4(vec3(1.0-texture(u_ScreenTexture, v_TexCoord)), 1.0);
	//color = test;

	//grayscale
	//vec4 test = texture(u_ScreenTexture, v_TexCoord);
	//float average = 0.2126 * test.r + 0.7152 * test.g + 0.0722 * test.b;
	//color = vec4(average, average, average, 1.0);

	//core
    /*
    const float offset = 1.0/300.0;
	vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // 左上
        vec2( 0.0f,    offset), // 正上
        vec2( offset,  offset), // 右上
        vec2(-offset,  0.0f),   // 左
        vec2( 0.0f,    0.0f),   // 中
        vec2( offset,  0.0f),   // 右
        vec2(-offset, -offset), // 左下
        vec2( 0.0f,   -offset), // 正下
        vec2( offset, -offset)  // 右下
    );
        //sharpen core
    //float kernel[9] = float[](
    //    -1, -1, -1,
    //    -1,  9, -1,
    //    -1, -1, -1
    //);
        //blur core
    //float kernel[9] = float[](
    //    1.0 / 16, 2.0 / 16, 1.0 / 16,
    //    2.0 / 16, 4.0 / 16, 2.0 / 16,
    //    1.0 / 16, 2.0 / 16, 1.0 / 16  
    //);
        //edge detection core
    float kernel[9] = float[](
        1,  1, 1,
        1, -8, 1,
        1,  1, 1
    );
    
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(u_ScreenTexture, v_TexCoord.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];
    
    color = vec4(col, 1.0);
    */
    float gamma = 2.2;
	color = texture(u_ScreenTexture, v_TexCoord);
    color.rgb = pow(color.rgb, vec3(1.0 / gamma));
    color = vec4(color.rgb, color.a);
}