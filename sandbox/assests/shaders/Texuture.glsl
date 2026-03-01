#type vertex
#version 330 core


layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec4 a_Color;
layout(location = 3) in float a_TexIndex;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Position;
out vec2 v_TexCoord;
out vec4 v_Color;
out float v_TexIndex;

void main()
{
   v_Position = a_Position;
   v_TexCoord = a_TexCoord;
   v_Color = a_Color;  
   v_TexIndex = a_TexIndex;
   gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

 layout( location = 0) out vec4 color;

 in vec3 v_Position;
 in vec2 v_TexCoord;
 in vec4 v_Color;
 in float v_TexIndex;

 uniform vec4 u_Color;
 
 uniform sampler2D u_Texture[32];
 uniform float u_TilingFactor;

  void main()
  {
      color = texture(u_Texture[int(v_TexIndex)], v_TexCoord * u_TilingFactor) * u_Color * v_Color;
  }

