// vertシェーダ内

//------RGB to HSV -------
float3 hsv = rgb2hsv(color);
//------------------------

float rad = radians(hsv.x*360.0);
v.vertex.x += cos(rad);
v.vertex.y += sin(rad);

//------------------------

v2f o;
o.vertex = UnityObjectToClipPos(v.vertex);
o.uv = TRANSFORM_TEX(v.uv, _MainTex);
UNITY_TRANSFER_FOG(o,o.vertex);
return o;
