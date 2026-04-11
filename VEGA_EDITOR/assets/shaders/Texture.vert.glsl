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
layout(binding = 0)
layout(std140) uniform block_GlobalParams_0
{
    mat4x4 u_ViewProjection_0;
    mat4x4 u_Transform_0;
    vec4 u_Color_0;
}globalParams_0;

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

    output_0.location_0 = ((((((globalParams_0.u_ViewProjection_0) * (globalParams_0.u_Transform_0)))) * (vec4(input_a_Position_0, 1.0))));
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

