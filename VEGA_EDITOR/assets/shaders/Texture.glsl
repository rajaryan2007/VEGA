#type vertex
#version 450
layout(column_major) uniform;
layout(column_major) buffer;

#line 13360 0
struct GlobalParams_0
{
    mat4x4 u_ViewProjection_0;
    mat4x4 u_Transform_0;
    vec4 u_Color_0;
};


#line 13360
uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform vec4 u_Color;

#line 1 1
layout(location = 0)
out vec2 entryPointParam_vertexMain_v_TexCoord_0;


#line 1
layout(location = 1)
out vec4 entryPointParam_vertexMain_v_Color_0;


#line 1
layout(location = 2)
out float entryPointParam_vertexMain_v_TexIndex_0;


#line 1
layout(location = 3)
out float entryPointParam_vertexMain_v_TilingFactor_0;


#line 1
layout(location = 4)
out int entryPointParam_vertexMain_v_EntityID_0;


#line 1
layout(location = 0)
in vec3 input_a_Position_0;


#line 1
layout(location = 1)
in vec2 input_a_TexCoord_0;


#line 1
layout(location = 2)
in vec4 input_a_Color_0;


#line 1
layout(location = 3)
in float input_a_TexIndex_0;


#line 1
layout(location = 4)
in float input_a_TilingFactor_0;


#line 1
layout(location = 5)
in int input_a_EntityID_0;


#line 10
struct VertexOutput_0
{
    vec4 location_0;
    vec2 v_TexCoord_0;
    vec4 v_Color_0;
    float v_TexIndex_0;
    float v_TilingFactor_0;
    int v_EntityID_0;
};


#line 25
void main()
{

#line 26
    VertexOutput_0 output_0;
    output_0.v_TexCoord_0 = input_a_TexCoord_0;
    output_0.v_Color_0 = input_a_Color_0;
    output_0.v_TexIndex_0 = input_a_TexIndex_0;
    output_0.v_TilingFactor_0 = input_a_TilingFactor_0;
    output_0.v_EntityID_0 = input_a_EntityID_0;

    output_0.location_0 = ((((((u_ViewProjection) * (u_Transform)))) * (vec4(input_a_Position_0, 1.0))));
    VertexOutput_0 _S1 = output_0;

#line 34
    gl_Position = output_0.location_0;

#line 34
    entryPointParam_vertexMain_v_TexCoord_0 = _S1.v_TexCoord_0;

#line 34
    entryPointParam_vertexMain_v_Color_0 = _S1.v_Color_0;

#line 34
    entryPointParam_vertexMain_v_TexIndex_0 = _S1.v_TexIndex_0;

#line 34
    entryPointParam_vertexMain_v_TilingFactor_0 = _S1.v_TilingFactor_0;

#line 34
    entryPointParam_vertexMain_v_EntityID_0 = _S1.v_EntityID_0;

#line 34
    return;
}


#type fragment
#version 450
layout(column_major) uniform;
layout(column_major) buffer;

#line 22 0
layout(binding = 1)
uniform sampler2D  u_Texture[32];


#line 90 1
struct GlobalParams_0
{
    mat4x4 u_ViewProjection_0;
    mat4x4 u_Transform_0;
    vec4 u_Color_0;
};


#line 90
uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform vec4 u_Color;

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
layout(location = 2)
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
    output_0.color_0 = (texture((u_Texture[int(input_v_TexIndex_0)]), (input_v_TexCoord_0 * input_v_TilingFactor_0))) * u_Color * input_v_Color_0;
    output_0.color2_0 = input_v_EntityID_0;

    FragmentOutput_0 _S1 = output_0;

#line 54
    entryPointParam_fragmentMain_color_0 = output_0.color_0;

#line 54
    entryPointParam_fragmentMain_color2_0 = _S1.color2_0;

#line 54
    return;
}


