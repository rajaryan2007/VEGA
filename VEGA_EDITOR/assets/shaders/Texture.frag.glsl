#version 450
layout(column_major) uniform;
layout(column_major) buffer;

#line 22 0
layout(binding = 1)
uniform sampler2D  u_Texture_0[32];


#line 90 1
struct GlobalParams_0
{
    mat4x4 u_ViewProjection_0;
    mat4x4 u_Transform_0;
    vec4 u_Color_0;
};


#line 90
layout(binding = 0)
layout(std140) uniform block_GlobalParams_0
{
    mat4x4 u_ViewProjection_0;
    mat4x4 u_Transform_0;
    vec4 u_Color_0;
}globalParams_0;

#line 1213 2
layout(location = 0)
out vec4 entryPointParam_fragmentMain_color_0;


#line 1213
layout(location = 1)
out int entryPointParam_fragmentMain_color2_0;


#line 1213
layout(location = 0)
in vec2 input_v_TexCoord_0;


#line 1213
layout(location = 1)
in vec4 input_v_Color_0;


#line 1213
flat layout(location = 2)
in float input_v_TexIndex_0;


#line 1213
layout(location = 3)
in float input_v_TilingFactor_0;


#line 1213
flat layout(location = 4)
in int input_v_EntityID_0;


#line 37 0
struct FragmentOutput_0
{
    vec4 color_0;
    int color2_0;
};

void main()
{

#line 44
    FragmentOutput_0 output_0;

#line 51
    output_0.color_0 = (texture((u_Texture_0[int(input_v_TexIndex_0)]), (input_v_TexCoord_0 * input_v_TilingFactor_0))) * globalParams_0.u_Color_0 * input_v_Color_0;
    output_0.color2_0 = input_v_EntityID_0;

    FragmentOutput_0 _S1 = output_0;

#line 54
    entryPointParam_fragmentMain_color_0 = output_0.color_0;

#line 54
    entryPointParam_fragmentMain_color2_0 = _S1.color2_0;

#line 54
    return;
}

