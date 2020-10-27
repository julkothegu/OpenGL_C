#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

const float offset = 1.0/400;

uniform sampler2D screenTexture;

void main()
{ 

    vec2 offsets[9] = vec2[](
            vec2(-offset,  offset), // top-left
            vec2( 0.0f,    offset), // top-center
            vec2( offset,  offset), // top-right
            vec2(-offset,  0.0f),   // center-left
            vec2( 0.0f,    0.0f),   // center-center
            vec2( offset,  0.0f),   // center-right
            vec2(-offset, -offset), // bottom-left
            vec2( 0.0f,   -offset), // bottom-center
            vec2( offset, -offset)  // bottom-right    
    );

    float kernel[9] = float[]
    (
        1, 1, 1, 
        1, -8, 1,
        1, 1, 1
    );

    vec3 samples[9];
    for (int i = 0; i < 9; i++)
    {
        samples[i] = vec3(texture(screenTexture, TexCoords + offsets[i]));
	}

    vec3 col = vec3(0.0);
    for (int j = 0; j < 9; j++)
    {
        col += samples[j] * kernel[j];
	}

    FragColor = texture(screenTexture, TexCoords);
}