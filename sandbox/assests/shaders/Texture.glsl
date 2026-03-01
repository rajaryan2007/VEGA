#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec4 a_Color;
layout(location = 3) in float a_TexIndex;
layout(location = 4) in float a_TilingFactor;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TexCoord;
out vec4 v_Color;
out float v_TexIndex;
out float v_TilingFactor;

void main()
{
    v_TexCoord = a_TexCoord;
    v_Color = a_Color;
    v_TexIndex = a_TexIndex;
    v_TilingFactor = a_TilingFactor;
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_Color;
in float v_TexIndex;
in float v_TilingFactor;

uniform sampler2D u_Texture[32];
uniform vec4 u_Color;


void main()
{
    vec4 texColor = vec4(1.0);
    int index = int(v_TexIndex);
    float u_TilingFactor = v_TilingFactor;

    if(index == 0)
        texColor = texture(u_Texture[0], v_TexCoord * u_TilingFactor);
    else if(index == 1)
        texColor = texture(u_Texture[1], v_TexCoord * u_TilingFactor);
    else if(index == 2)
        texColor = texture(u_Texture[2], v_TexCoord * u_TilingFactor);
    else if(index == 3)
        texColor = texture(u_Texture[3], v_TexCoord * u_TilingFactor);
    else if(index == 4)
        texColor = texture(u_Texture[4], v_TexCoord * u_TilingFactor);
    else if(index == 5)
        texColor = texture(u_Texture[5], v_TexCoord * u_TilingFactor);
    else if(index == 6)
        texColor = texture(u_Texture[6], v_TexCoord * u_TilingFactor);
    else if(index == 7)
        texColor = texture(u_Texture[7], v_TexCoord * u_TilingFactor);
    else if(index == 8)
        texColor = texture(u_Texture[8], v_TexCoord * u_TilingFactor);
    else if(index == 9)
        texColor = texture(u_Texture[9], v_TexCoord * u_TilingFactor);
    else if(index == 10)
        texColor = texture(u_Texture[10], v_TexCoord * u_TilingFactor);
    else if(index == 11)
        texColor = texture(u_Texture[11], v_TexCoord * u_TilingFactor);
    else if(index == 12)
        texColor = texture(u_Texture[12], v_TexCoord * u_TilingFactor);
    else if(index == 13)
        texColor = texture(u_Texture[13], v_TexCoord * u_TilingFactor);
    else if(index == 14)
        texColor = texture(u_Texture[14], v_TexCoord * u_TilingFactor);
    else if(index == 15)
        texColor = texture(u_Texture[15], v_TexCoord * u_TilingFactor);
    else if(index == 16)
        texColor = texture(u_Texture[16], v_TexCoord * u_TilingFactor);
    else if(index == 17)
        texColor = texture(u_Texture[17], v_TexCoord * u_TilingFactor);
    else if(index == 18)
        texColor = texture(u_Texture[18], v_TexCoord * u_TilingFactor);
    else if(index == 19)
        texColor = texture(u_Texture[19], v_TexCoord * u_TilingFactor);
    else if(index == 20)
        texColor = texture(u_Texture[20], v_TexCoord * u_TilingFactor);
    else if(index == 21)
        texColor = texture(u_Texture[21], v_TexCoord * u_TilingFactor);
    else if(index == 22)
        texColor = texture(u_Texture[22], v_TexCoord * u_TilingFactor);
    else if(index == 23)
        texColor = texture(u_Texture[23], v_TexCoord * u_TilingFactor);
    else if(index == 24)
        texColor = texture(u_Texture[24], v_TexCoord * u_TilingFactor);
    else if(index == 25)
        texColor = texture(u_Texture[25], v_TexCoord * u_TilingFactor);
    else if(index == 26)
        texColor = texture(u_Texture[26], v_TexCoord * u_TilingFactor);
    else if(index == 27)
        texColor = texture(u_Texture[27], v_TexCoord * u_TilingFactor);
    else if(index == 28)
        texColor = texture(u_Texture[28], v_TexCoord * u_TilingFactor);
    else if(index == 29)
        texColor = texture(u_Texture[29], v_TexCoord * u_TilingFactor);
    else if(index == 30)
        texColor = texture(u_Texture[30], v_TexCoord * u_TilingFactor);
    else if(index == 31)
        texColor = texture(u_Texture[31], v_TexCoord * u_TilingFactor);

    color = texColor * u_Color * v_Color;
}