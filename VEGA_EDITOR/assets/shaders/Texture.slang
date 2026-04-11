struct VertexInput {
    [[vk::location(0)]] float3 a_Position : POSITION;
    [[vk::location(1)]] float2 a_TexCoord : TEXCOORD;
    [[vk::location(2)]] float4 a_Color : COLOR;
    [[vk::location(3)]] float a_TexIndex : TEXINDEX;
    [[vk::location(4)]] float a_TilingFactor : TILINGFACTOR;
    [[vk::location(5)]] int a_EntityID : ENTITYID;
};

struct VertexOutput {
    float4 location : SV_Position;
    [[vk::location(0)]] float2 v_TexCoord;
    [[vk::location(1)]] float4 v_Color;
    [[vk::location(2)]] float v_TexIndex;
    [[vk::location(3)]] float v_TilingFactor;
    [[vk::location(4)]] int v_EntityID; // In GLSL it generated 'flat in int', slang handles this if types are int.
};

uniform float4x4 u_ViewProjection;
uniform float4x4 u_Transform;
uniform float4 u_Color;
uniform Sampler2D u_Texture[32];

[shader("vertex")]
VertexOutput vertexMain(VertexInput input) {
    VertexOutput output;
    output.v_TexCoord = input.a_TexCoord;
    output.v_Color = input.a_Color;
    output.v_TexIndex = input.a_TexIndex;
    output.v_TilingFactor = input.a_TilingFactor;
    output.v_EntityID = input.a_EntityID;
    
    output.location = mul(float4(input.a_Position, 1.0), mul(u_Transform, u_ViewProjection));
    return output;
}

struct FragmentOutput {
    [[vk::location(0)]] float4 color : SV_Target0;
    [[vk::location(1)]] int color2 : SV_Target1;
};

[shader("fragment")]
FragmentOutput fragmentMain(VertexOutput input) {
    FragmentOutput output;
    float4 texColor = float4(1.0);
    int index = (int)input.v_TexIndex;

    // In Slang, dynamic indexing is natively supported and mapped to GLSL arrays.
    texColor = u_Texture[index].Sample(input.v_TexCoord * input.v_TilingFactor);
    
    output.color = texColor * u_Color * input.v_Color;
    output.color2 = input.v_EntityID;
    
    return output;
}
