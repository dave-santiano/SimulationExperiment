// #version 150
// uniform sampler2D src_tex_unit0; // 0
// uniform float vx_offset;

// // uniform float rt_w; // GeeXLab built-in
// // uniform float rt_h; // GeeXLab built-in

// uniform float pixel_w; // 15.0
// uniform float pixel_h; // 10.0

// void main()
// {
//   vec2 uv = gl_TexCoord[0].xy;
//   // vec2 uv = src_tex_unit0[0].xy;
//   vec3 tc = vec3(1.0, 0.0, 0.0);

//   float dx = pixel_w*(1./1920);
//   float dy = pixel_h*(1./1080);
//   vec2 coord = vec2(dx*floor(uv.x/dx),
//                     dy*floor(uv.y/dy));
//   tc = texture2D(src_tex_unit0, coord).rgb;


//   // else if (uv.x>=(vx_offset+0.005))
//   // {
//   //   tc = texture2D(src_tex_unit0, uv).rgb;
//   // }
//     gl_FragColor = vec4(tc, 1.0);
// }
#version 150
uniform sampler2D src_tex_unit0;
void main()
{
 float dx = 15.*(1./1920.);
 float dy = 10.*(1./1080.);
 vec2 coord = vec2(dx*floor(gl_TexCoord[0].x/dx),
                   dy*floor(gl_TexCoord[0].y/dy));
 gl_FragColor = texture2D(src_tex_unit0, coord);
}