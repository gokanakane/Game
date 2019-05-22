xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 70;
 0.31905;0.02839;-9.05013;,
 -5.43783;-3.56532;-6.46286;,
 -6.41235;-10.40028;-6.94812;,
 0.31905;-10.40028;-9.73635;,
 -8.62785;-5.05396;-0.21669;,
 -9.20058;-10.40028;-0.21669;,
 -5.43783;-3.56532;6.02949;,
 -6.41235;-10.40028;6.51471;,
 0.31905;0.02839;8.61675;,
 0.31905;-10.40028;9.30294;,
 6.07596;3.62211;6.02949;,
 7.05048;-10.40028;6.51471;,
 9.66867;5.11069;-0.21669;,
 9.83871;-10.40028;-0.21669;,
 6.07596;3.62211;-6.46286;,
 7.05048;-10.40028;-6.94812;,
 0.31905;0.02839;-9.05013;,
 0.31905;-10.40028;-9.73635;,
 -6.27939;-20.82876;-6.81513;,
 0.31905;-20.82876;-9.54831;,
 -9.01254;-20.82876;-0.21669;,
 -6.27939;-20.82876;6.38176;,
 0.31905;-20.82876;9.11490;,
 6.91752;-20.82876;6.38176;,
 9.65067;-20.82876;-0.21669;,
 6.91752;-20.82876;-6.81513;,
 0.31905;-20.82876;-9.54831;,
 -5.98974;-31.25732;-6.52551;,
 0.31905;-31.25732;-9.13869;,
 -8.60292;-31.25732;-0.21669;,
 -5.98974;-31.25732;6.09210;,
 0.31905;-31.25732;8.70528;,
 6.62787;-31.25732;6.09210;,
 9.24105;-31.25732;-0.21669;,
 6.62787;-31.25732;-6.52551;,
 0.31905;-31.25732;-9.13869;,
 -5.74296;-41.68589;-6.27872;,
 0.31905;-41.68589;-8.78970;,
 -8.25396;-41.68589;-0.21669;,
 -5.74296;-41.68589;5.84532;,
 0.31905;-41.68589;8.35632;,
 6.38109;-41.68589;5.84532;,
 8.89206;-41.68589;-0.21669;,
 6.38109;-41.68589;-6.27872;,
 0.31905;-41.68589;-8.78970;,
 -6.21390;-52.11454;-6.74964;,
 0.31905;-52.11454;-9.45567;,
 -8.91993;-52.11454;-0.21669;,
 -6.21390;-52.11454;6.31626;,
 0.31905;-52.11454;9.02229;,
 6.85200;-52.11454;6.31626;,
 9.55806;-52.11454;-0.21669;,
 6.85200;-52.11454;-6.74964;,
 0.31905;-52.11454;-9.45567;,
 0.31905;0.02839;-0.21669;,
 0.31905;0.02839;-0.21669;,
 0.31905;0.02839;-0.21669;,
 0.31905;0.02839;-0.21669;,
 0.31905;0.02839;-0.21669;,
 0.31905;0.02839;-0.21669;,
 0.31905;0.02839;-0.21669;,
 0.31905;0.02839;-0.21669;,
 0.31905;-52.11454;-0.21669;,
 0.31905;-52.11454;-0.21669;,
 0.31905;-52.11454;-0.21669;,
 0.31905;-52.11454;-0.21669;,
 0.31905;-52.11454;-0.21669;,
 0.31905;-52.11454;-0.21669;,
 0.31905;-52.11454;-0.21669;,
 0.31905;-52.11454;-0.21669;;
 
 56;
 4;3,2,1,0;,
 4;2,5,4,1;,
 4;5,7,6,4;,
 4;7,9,8,6;,
 4;9,11,10,8;,
 4;11,13,12,10;,
 4;13,15,14,12;,
 4;15,17,16,14;,
 4;19,18,2,3;,
 4;18,20,5,2;,
 4;20,21,7,5;,
 4;21,22,9,7;,
 4;22,23,11,9;,
 4;23,24,13,11;,
 4;24,25,15,13;,
 4;25,26,17,15;,
 4;28,27,18,19;,
 4;27,29,20,18;,
 4;29,30,21,20;,
 4;30,31,22,21;,
 4;31,32,23,22;,
 4;32,33,24,23;,
 4;33,34,25,24;,
 4;34,35,26,25;,
 4;37,36,27,28;,
 4;36,38,29,27;,
 4;38,39,30,29;,
 4;39,40,31,30;,
 4;40,41,32,31;,
 4;41,42,33,32;,
 4;42,43,34,33;,
 4;43,44,35,34;,
 4;46,45,36,37;,
 4;45,47,38,36;,
 4;47,48,39,38;,
 4;48,49,40,39;,
 4;49,50,41,40;,
 4;50,51,42,41;,
 4;51,52,43,42;,
 4;52,53,44,43;,
 3;0,1,54;,
 3;1,4,55;,
 3;4,6,56;,
 3;6,8,57;,
 3;8,10,58;,
 3;10,12,59;,
 3;12,14,60;,
 3;14,16,61;,
 3;45,46,62;,
 3;47,45,63;,
 3;48,47,64;,
 3;49,48,65;,
 3;50,49,66;,
 3;51,50,67;,
 3;52,51,68;,
 3;53,52,69;;
 
 MeshMaterialList {
  1;
  56;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.700000;0.480000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  56;
  -0.507842;0.861450;0.000000;,
  -0.016233;0.080956;-0.996585;,
  -0.704898;0.116190;-0.699727;,
  -0.814837;0.579690;0.000000;,
  -0.704898;0.116188;0.699728;,
  -0.016232;0.080953;0.996586;,
  0.681922;0.055009;0.729353;,
  0.998825;0.048467;0.000000;,
  0.681922;0.055011;-0.729353;,
  -0.008103;0.031355;-0.999475;,
  -0.707540;0.049578;-0.704932;,
  -0.998158;0.060671;0.000000;,
  -0.707539;0.049578;0.704933;,
  -0.008103;0.031355;0.999475;,
  0.694938;0.018739;0.718825;,
  0.999891;0.014736;0.000000;,
  0.694939;0.018739;-0.718825;,
  -0.000001;-0.028641;-0.999590;,
  -0.706818;-0.028641;-0.706816;,
  -0.999590;-0.028641;0.000000;,
  -0.706817;-0.028641;0.706817;,
  -0.000001;-0.028641;0.999590;,
  0.706816;-0.028641;0.706817;,
  0.999590;-0.028641;0.000000;,
  0.706817;-0.028641;-0.706816;,
  -0.000001;-0.036347;-0.999339;,
  -0.706640;-0.036347;-0.706639;,
  -0.999339;-0.036347;0.000001;,
  -0.706640;-0.036347;0.706640;,
  -0.000001;-0.036347;0.999339;,
  0.706639;-0.036347;0.706640;,
  0.999339;-0.036348;0.000001;,
  0.706640;-0.036347;-0.706639;,
  -0.000001;0.015165;-0.999885;,
  -0.707025;0.015166;-0.707026;,
  -0.999885;0.015166;0.000001;,
  -0.707025;0.015166;0.707026;,
  -0.000001;0.015166;0.999885;,
  0.707025;0.015166;0.707025;,
  0.999885;0.015166;0.000001;,
  0.707025;0.015165;-0.707026;,
  -0.000000;0.063730;-0.997967;,
  -0.705669;0.063731;-0.705670;,
  -0.997967;0.063732;0.000000;,
  -0.705669;0.063732;0.705669;,
  -0.000000;0.063732;0.997967;,
  0.705669;0.063731;0.705670;,
  0.997967;0.063732;0.000000;,
  0.705669;0.063730;-0.705670;,
  0.000000;-1.000000;0.000000;,
  -0.511722;0.858856;-0.022502;,
  -0.529538;0.848286;0.000000;,
  -0.511722;0.858856;0.022502;,
  -0.503549;0.863351;-0.032621;,
  -0.477585;0.878586;0.000000;,
  -0.503549;0.863351;0.032621;;
  56;
  4;9,10,2,1;,
  4;10,11,3,2;,
  4;11,12,4,3;,
  4;12,13,5,4;,
  4;13,14,6,5;,
  4;14,15,7,6;,
  4;15,16,8,7;,
  4;16,9,1,8;,
  4;17,18,10,9;,
  4;18,19,11,10;,
  4;19,20,12,11;,
  4;20,21,13,12;,
  4;21,22,14,13;,
  4;22,23,15,14;,
  4;23,24,16,15;,
  4;24,17,9,16;,
  4;25,26,18,17;,
  4;26,27,19,18;,
  4;27,28,20,19;,
  4;28,29,21,20;,
  4;29,30,22,21;,
  4;30,31,23,22;,
  4;31,32,24,23;,
  4;32,25,17,24;,
  4;33,34,26,25;,
  4;34,35,27,26;,
  4;35,36,28,27;,
  4;36,37,29,28;,
  4;37,38,30,29;,
  4;38,39,31,30;,
  4;39,40,32,31;,
  4;40,33,25,32;,
  4;41,42,34,33;,
  4;42,43,35,34;,
  4;43,44,36,35;,
  4;44,45,37,36;,
  4;45,46,38,37;,
  4;46,47,39,38;,
  4;47,48,40,39;,
  4;48,41,33,40;,
  3;51,50,0;,
  3;50,3,0;,
  3;3,52,0;,
  3;52,51,0;,
  3;51,53,0;,
  3;53,54,0;,
  3;54,55,0;,
  3;55,51,0;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;;
 }
 MeshTextureCoords {
  70;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;0.200000;,
  0.000000;0.200000;,
  0.250000;0.000000;,
  0.250000;0.200000;,
  0.375000;0.000000;,
  0.375000;0.200000;,
  0.500000;0.000000;,
  0.500000;0.200000;,
  0.625000;0.000000;,
  0.625000;0.200000;,
  0.750000;0.000000;,
  0.750000;0.200000;,
  0.875000;0.000000;,
  0.875000;0.200000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.125000;0.400000;,
  0.000000;0.400000;,
  0.250000;0.400000;,
  0.375000;0.400000;,
  0.500000;0.400000;,
  0.625000;0.400000;,
  0.750000;0.400000;,
  0.875000;0.400000;,
  1.000000;0.400000;,
  0.125000;0.600000;,
  0.000000;0.600000;,
  0.250000;0.600000;,
  0.375000;0.600000;,
  0.500000;0.600000;,
  0.625000;0.600000;,
  0.750000;0.600000;,
  0.875000;0.600000;,
  1.000000;0.600000;,
  0.125000;0.800000;,
  0.000000;0.800000;,
  0.250000;0.800000;,
  0.375000;0.800000;,
  0.500000;0.800000;,
  0.625000;0.800000;,
  0.750000;0.800000;,
  0.875000;0.800000;,
  1.000000;0.800000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
