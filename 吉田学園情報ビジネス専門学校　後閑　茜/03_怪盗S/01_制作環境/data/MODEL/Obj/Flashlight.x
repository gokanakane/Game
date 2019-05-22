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
 149;
 -0.00483;7.62480;-0.96409;,
 0.68855;7.62480;-0.68855;,
 0.51559;1.19733;-0.51559;,
 0.00000;1.19733;-0.72915;,
 0.97375;7.62480;0.00000;,
 0.72915;1.19733;0.00000;,
 0.68855;7.62480;0.68855;,
 0.51559;1.19733;0.51559;,
 -0.00483;7.62480;0.96409;,
 -0.00000;1.19733;0.72915;,
 -0.68655;7.62480;0.68171;,
 -0.51559;1.19733;0.51559;,
 -0.96892;7.62480;-0.00000;,
 -0.72915;1.19733;-0.00000;,
 -0.68655;7.62480;-0.68171;,
 -0.51559;1.19733;-0.51559;,
 -0.00483;7.62480;-0.96409;,
 0.00000;1.19733;-0.72915;,
 0.26414;0.44853;-0.26743;,
 -0.00067;0.44853;-0.38756;,
 -0.00067;0.44853;-0.00054;,
 0.37592;0.44853;0.00044;,
 -0.00067;0.44853;-0.00054;,
 0.27134;0.44853;0.27409;,
 -0.00067;0.44853;-0.00054;,
 -0.00136;0.44853;0.38937;,
 -0.00067;0.44853;-0.00054;,
 -0.27638;0.44853;0.27545;,
 -0.00067;0.44853;-0.00054;,
 -0.39031;0.44853;0.00042;,
 -0.00067;0.44853;-0.00054;,
 -0.27638;0.44853;-0.27461;,
 -0.00067;0.44853;-0.00054;,
 -0.00067;0.44853;-0.38756;,
 -0.00067;0.44853;-0.00054;,
 -0.01451;9.35502;-2.25085;,
 1.60433;9.35502;-1.60755;,
 2.27019;9.35502;0.00000;,
 1.60433;9.35502;1.60755;,
 -0.01451;9.35502;2.25085;,
 -1.60610;9.35502;1.59159;,
 -2.26536;9.35502;-0.00000;,
 -1.60610;9.35502;-1.59159;,
 -0.01451;9.35502;-2.25085;,
 -0.01036;9.37819;-1.79008;,
 1.25748;9.37819;-1.28625;,
 1.77897;9.37819;-0.02725;,
 1.25748;9.37819;1.23176;,
 -0.01036;9.37819;1.73558;,
 -1.25687;9.37819;1.21926;,
 -1.77319;9.37819;-0.02725;,
 -1.25687;9.37819;-1.27376;,
 -0.01036;9.37819;-1.79008;,
 -0.00384;7.63686;-0.92184;,
 0.63956;7.63686;-0.66616;,
 -0.00384;7.63686;-0.02725;,
 0.90421;7.63686;-0.02725;,
 -0.00384;7.63686;-0.02725;,
 0.63956;7.63686;0.61167;,
 -0.00384;7.63686;-0.02725;,
 -0.00384;7.63686;0.86735;,
 -0.00384;7.63686;-0.02725;,
 -0.63641;7.63686;0.60533;,
 -0.00384;7.63686;-0.02725;,
 -0.89843;7.63686;-0.02725;,
 -0.00384;7.63686;-0.02725;,
 -0.63641;7.63686;-0.65982;,
 -0.00384;7.63686;-0.02725;,
 -0.00384;7.63686;-0.92184;,
 -0.00384;7.63686;-0.02725;,
 0.00000;8.50884;-0.05425;,
 0.23377;8.44308;-0.28802;,
 0.00000;8.44308;-0.38485;,
 0.00000;8.50884;-0.05425;,
 0.33060;8.44308;-0.05425;,
 0.00000;8.50884;-0.05425;,
 0.23377;8.44308;0.17952;,
 0.00000;8.50884;-0.05425;,
 -0.00000;8.44308;0.27635;,
 0.00000;8.50884;-0.05425;,
 -0.23377;8.44308;0.17952;,
 0.00000;8.50884;-0.05425;,
 -0.33060;8.44308;-0.05425;,
 0.00000;8.50884;-0.05425;,
 -0.23377;8.44308;-0.28802;,
 0.00000;8.50884;-0.05425;,
 0.00000;8.44308;-0.38485;,
 0.43195;8.25581;-0.48620;,
 0.00000;8.25581;-0.66512;,
 0.61087;8.25581;-0.05425;,
 0.43195;8.25581;0.37770;,
 -0.00000;8.25581;0.55662;,
 -0.43195;8.25581;0.37770;,
 -0.61087;8.25581;-0.05425;,
 -0.43195;8.25581;-0.48620;,
 0.00000;8.25581;-0.66512;,
 0.56437;7.97554;-0.61862;,
 0.00000;7.97554;-0.85239;,
 0.79814;7.97554;-0.05425;,
 0.56437;7.97554;0.51012;,
 -0.00000;7.97554;0.74389;,
 -0.56437;7.97554;0.51012;,
 -0.79814;7.97554;-0.05425;,
 -0.56437;7.97554;-0.61862;,
 0.00000;7.97554;-0.85239;,
 0.61087;7.64494;-0.66512;,
 0.00000;7.64494;-0.91815;,
 0.86390;7.64494;-0.05425;,
 0.61087;7.64494;0.55662;,
 -0.00000;7.64494;0.80965;,
 -0.61087;7.64494;0.55662;,
 -0.86390;7.64494;-0.05425;,
 -0.61087;7.64494;-0.66512;,
 0.00000;7.64494;-0.91815;,
 0.56437;7.31434;-0.61862;,
 0.00000;7.31434;-0.85239;,
 0.79814;7.31434;-0.05425;,
 0.56437;7.31434;0.51012;,
 -0.00000;7.31434;0.74389;,
 -0.56437;7.31434;0.51012;,
 -0.79814;7.31434;-0.05425;,
 -0.56437;7.31434;-0.61862;,
 0.00000;7.31434;-0.85239;,
 0.43195;7.03407;-0.48620;,
 0.00000;7.03407;-0.66512;,
 0.61087;7.03407;-0.05425;,
 0.43195;7.03407;0.37770;,
 -0.00000;7.03407;0.55662;,
 -0.43195;7.03407;0.37770;,
 -0.61087;7.03407;-0.05425;,
 -0.43195;7.03407;-0.48620;,
 0.00000;7.03407;-0.66512;,
 0.23377;6.84680;-0.28802;,
 0.00000;6.84680;-0.38485;,
 0.33060;6.84680;-0.05425;,
 0.23377;6.84680;0.17952;,
 -0.00000;6.84680;0.27635;,
 -0.23377;6.84680;0.17952;,
 -0.33060;6.84680;-0.05425;,
 -0.23377;6.84680;-0.28802;,
 0.00000;6.84680;-0.38485;,
 0.00000;6.78104;-0.05425;,
 0.00000;6.78104;-0.05425;,
 0.00000;6.78104;-0.05425;,
 0.00000;6.78104;-0.05425;,
 0.00000;6.78104;-0.05425;,
 0.00000;6.78104;-0.05425;,
 0.00000;6.78104;-0.05425;,
 0.00000;6.78104;-0.05425;;
 
 120;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;18,19,3,2;,
 3;20,19,18;,
 4;21,18,2,5;,
 3;22,18,21;,
 4;23,21,5,7;,
 3;24,21,23;,
 4;25,23,7,9;,
 3;26,23,25;,
 4;27,25,9,11;,
 3;28,25,27;,
 4;29,27,11,13;,
 3;30,27,29;,
 4;31,29,13,15;,
 3;32,29,31;,
 4;33,31,15,17;,
 3;34,31,33;,
 4;35,36,1,0;,
 4;36,37,4,1;,
 4;37,38,6,4;,
 4;38,39,8,6;,
 4;39,40,10,8;,
 4;40,41,12,10;,
 4;41,42,14,12;,
 4;42,43,16,14;,
 4;44,45,36,35;,
 4;45,46,37,36;,
 4;46,47,38,37;,
 4;47,48,39,38;,
 4;48,49,40,39;,
 4;49,50,41,40;,
 4;50,51,42,41;,
 4;51,52,43,42;,
 4;53,54,45,44;,
 3;55,54,53;,
 4;54,56,46,45;,
 3;57,56,54;,
 4;56,58,47,46;,
 3;59,58,56;,
 4;58,60,48,47;,
 3;61,60,58;,
 4;60,62,49,48;,
 3;63,62,60;,
 4;62,64,50,49;,
 3;65,64,62;,
 4;64,66,51,50;,
 3;67,66,64;,
 4;66,68,52,51;,
 3;69,68,66;,
 3;70,71,72;,
 3;73,74,71;,
 3;75,76,74;,
 3;77,78,76;,
 3;79,80,78;,
 3;81,82,80;,
 3;83,84,82;,
 3;85,86,84;,
 4;72,71,87,88;,
 4;71,74,89,87;,
 4;74,76,90,89;,
 4;76,78,91,90;,
 4;78,80,92,91;,
 4;80,82,93,92;,
 4;82,84,94,93;,
 4;84,86,95,94;,
 4;88,87,96,97;,
 4;87,89,98,96;,
 4;89,90,99,98;,
 4;90,91,100,99;,
 4;91,92,101,100;,
 4;92,93,102,101;,
 4;93,94,103,102;,
 4;94,95,104,103;,
 4;97,96,105,106;,
 4;96,98,107,105;,
 4;98,99,108,107;,
 4;99,100,109,108;,
 4;100,101,110,109;,
 4;101,102,111,110;,
 4;102,103,112,111;,
 4;103,104,113,112;,
 4;106,105,114,115;,
 4;105,107,116,114;,
 4;107,108,117,116;,
 4;108,109,118,117;,
 4;109,110,119,118;,
 4;110,111,120,119;,
 4;111,112,121,120;,
 4;112,113,122,121;,
 4;115,114,123,124;,
 4;114,116,125,123;,
 4;116,117,126,125;,
 4;117,118,127,126;,
 4;118,119,128,127;,
 4;119,120,129,128;,
 4;120,121,130,129;,
 4;121,122,131,130;,
 4;124,123,132,133;,
 4;123,125,134,132;,
 4;125,126,135,134;,
 4;126,127,136,135;,
 4;127,128,137,136;,
 4;128,129,138,137;,
 4;129,130,139,138;,
 4;130,131,140,139;,
 3;133,132,141;,
 3;132,134,142;,
 3;134,135,143;,
 3;135,136,144;,
 3;136,137,145;,
 3;137,138,146;,
 3;138,139,147;,
 3;139,140,148;;
 
 MeshMaterialList {
  2;
  120;
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
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.467451;0.467451;0.467451;1.000000;;
   18.000000;
   0.090000;0.090000;0.090000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.771765;0.800000;0.000000;0.410000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.964706;1.000000;0.000000;;
  }
 }
 MeshNormals {
  108;
  -0.004934;-0.335750;-0.941938;,
  0.661938;-0.337836;-0.669108;,
  0.941161;-0.337958;0.000000;,
  0.661925;-0.337889;0.669094;,
  -0.004935;-0.335803;0.941919;,
  -0.665656;-0.336996;0.665834;,
  -0.941286;-0.337611;0.000000;,
  -0.665656;-0.336996;-0.665834;,
  0.002066;-0.233575;-0.972337;,
  0.688036;-0.237089;-0.685854;,
  0.971360;-0.237589;-0.003389;,
  0.688625;-0.234920;0.686009;,
  -0.001104;-0.231025;0.972947;,
  -0.688131;-0.230205;0.688100;,
  -0.973130;-0.230257;0.000015;,
  -0.687758;-0.230672;-0.688316;,
  0.007612;-0.419451;-0.907746;,
  0.645109;-0.423712;-0.635848;,
  0.905326;-0.424666;-0.006592;,
  0.646600;-0.420515;0.636455;,
  0.001420;-0.414319;0.910131;,
  -0.644219;-0.412368;0.644154;,
  -0.911062;-0.412270;0.000029;,
  -0.643349;-0.413289;-0.644434;,
  0.000000;-1.000000;-0.000000;,
  -0.005783;-0.596771;-0.802391;,
  0.561451;-0.599911;-0.569981;,
  0.800272;-0.599637;0.000000;,
  0.561451;-0.599911;0.569981;,
  -0.005784;-0.596771;0.802391;,
  -0.566157;-0.598797;0.566488;,
  -0.800272;-0.599637;0.000000;,
  -0.566157;-0.598797;-0.566488;,
  -0.000348;0.998739;-0.050209;,
  0.034119;0.998798;-0.035182;,
  0.047132;0.998889;-0.000447;,
  0.031979;0.998974;0.032067;,
  -0.000318;0.998991;0.044911;,
  -0.032254;0.998970;0.031902;,
  -0.047042;0.998893;-0.000446;,
  -0.034420;0.998795;-0.034979;,
  0.000000;1.000000;0.000000;,
  0.006457;0.446225;0.894897;,
  -0.627079;0.449152;0.636423;,
  -0.893584;0.448896;-0.000000;,
  -0.627079;0.449152;-0.636423;,
  0.006457;0.446225;-0.894897;,
  0.632036;0.448112;-0.632239;,
  0.893584;0.448896;-0.000000;,
  0.632037;0.448112;0.632239;,
  -0.000000;1.000000;0.000000;,
  0.000000;0.924735;-0.380611;,
  0.269133;0.924735;-0.269133;,
  0.380611;0.924735;-0.000000;,
  0.269133;0.924735;0.269133;,
  -0.000000;0.924735;0.380611;,
  -0.269133;0.924735;0.269133;,
  -0.380611;0.924735;-0.000000;,
  -0.269133;0.924735;-0.269133;,
  0.000000;0.709231;-0.704976;,
  0.498493;0.709231;-0.498493;,
  0.704976;0.709231;0.000000;,
  0.498493;0.709231;0.498493;,
  -0.000000;0.709231;0.704976;,
  -0.498493;0.709231;0.498493;,
  -0.704976;0.709231;-0.000000;,
  -0.498493;0.709231;-0.498493;,
  -0.000000;0.384551;-0.923104;,
  0.652733;0.384551;-0.652733;,
  0.923104;0.384551;0.000000;,
  0.652733;0.384551;0.652733;,
  -0.000000;0.384551;0.923104;,
  -0.652733;0.384551;0.652733;,
  -0.923104;0.384551;0.000000;,
  -0.652733;0.384551;-0.652733;,
  -0.000000;0.000000;-1.000000;,
  0.707107;-0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;-0.000000;0.707107;,
  -0.000000;0.000000;1.000000;,
  -0.707107;-0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  -0.000000;-0.384551;-0.923104;,
  0.652733;-0.384551;-0.652733;,
  0.923104;-0.384551;0.000000;,
  0.652733;-0.384551;0.652733;,
  -0.000000;-0.384551;0.923104;,
  -0.652733;-0.384551;0.652733;,
  -0.923104;-0.384551;0.000000;,
  -0.652733;-0.384551;-0.652733;,
  0.000000;-0.709232;-0.704975;,
  0.498493;-0.709232;-0.498493;,
  0.704975;-0.709232;0.000000;,
  0.498493;-0.709232;0.498493;,
  -0.000000;-0.709232;0.704975;,
  -0.498493;-0.709232;0.498493;,
  -0.704975;-0.709232;-0.000000;,
  -0.498493;-0.709232;-0.498493;,
  0.000000;-0.924735;-0.380611;,
  0.269133;-0.924735;-0.269133;,
  0.380611;-0.924735;0.000000;,
  0.269133;-0.924735;0.269133;,
  -0.000000;-0.924735;0.380611;,
  -0.269133;-0.924735;0.269133;,
  -0.380611;-0.924735;-0.000000;,
  -0.269133;-0.924735;-0.269133;,
  0.000000;-1.000000;-0.000000;;
  120;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,0,8,15;,
  4;17,16,8,9;,
  3;24,24,24;,
  4;18,17,9,10;,
  3;24,24,24;,
  4;19,18,10,11;,
  3;24,24,24;,
  4;20,19,11,12;,
  3;24,24,24;,
  4;21,20,12,13;,
  3;24,24,24;,
  4;22,21,13,14;,
  3;24,24,24;,
  4;23,22,14,15;,
  3;24,24,24;,
  4;16,23,15,8;,
  3;24,24,24;,
  4;25,26,1,0;,
  4;26,27,2,1;,
  4;27,28,3,2;,
  4;28,29,4,3;,
  4;29,30,5,4;,
  4;30,31,6,5;,
  4;31,32,7,6;,
  4;32,25,0,7;,
  4;33,34,34,33;,
  4;34,35,35,34;,
  4;35,36,36,35;,
  4;36,37,37,36;,
  4;37,38,38,37;,
  4;38,39,39,38;,
  4;39,40,40,39;,
  4;40,33,33,40;,
  4;42,43,43,42;,
  3;41,41,41;,
  4;43,44,44,43;,
  3;41,41,41;,
  4;44,45,45,44;,
  3;41,41,41;,
  4;45,46,46,45;,
  3;41,41,41;,
  4;46,47,47,46;,
  3;41,41,41;,
  4;47,48,48,47;,
  3;41,41,41;,
  4;48,49,49,48;,
  3;41,41,41;,
  4;49,42,42,49;,
  3;41,41,41;,
  3;50,52,51;,
  3;50,53,52;,
  3;50,54,53;,
  3;50,55,54;,
  3;50,56,55;,
  3;50,57,56;,
  3;50,58,57;,
  3;50,51,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,57,65,64;,
  4;57,58,66,65;,
  4;58,51,59,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,65,73,72;,
  4;65,66,74,73;,
  4;66,59,67,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,73,81,80;,
  4;73,74,82,81;,
  4;74,67,75,82;,
  4;75,76,84,83;,
  4;76,77,85,84;,
  4;77,78,86,85;,
  4;78,79,87,86;,
  4;79,80,88,87;,
  4;80,81,89,88;,
  4;81,82,90,89;,
  4;82,75,83,90;,
  4;83,84,92,91;,
  4;84,85,93,92;,
  4;85,86,94,93;,
  4;86,87,95,94;,
  4;87,88,96,95;,
  4;88,89,97,96;,
  4;89,90,98,97;,
  4;90,83,91,98;,
  4;91,92,100,99;,
  4;92,93,101,100;,
  4;93,94,102,101;,
  4;94,95,103,102;,
  4;95,96,104,103;,
  4;96,97,105,104;,
  4;97,98,106,105;,
  4;98,91,99,106;,
  3;99,100,107;,
  3;100,101,107;,
  3;101,102,107;,
  3;102,103,107;,
  3;103,104,107;,
  3;104,105,107;,
  3;105,106,107;,
  3;106,99,107;;
 }
 MeshTextureCoords {
  149;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.062500;1.000000;,
  0.250000;1.000000;,
  0.187500;1.000000;,
  0.375000;1.000000;,
  0.312500;1.000000;,
  0.500000;1.000000;,
  0.437500;1.000000;,
  0.625000;1.000000;,
  0.562500;1.000000;,
  0.750000;1.000000;,
  0.687500;1.000000;,
  0.875000;1.000000;,
  0.812500;1.000000;,
  1.000000;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.250000;0.000000;,
  0.375000;0.000000;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.750000;0.000000;,
  0.875000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.250000;0.000000;,
  0.375000;0.000000;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.750000;0.000000;,
  0.875000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.062500;0.000000;,
  0.250000;0.000000;,
  0.187500;0.000000;,
  0.375000;0.000000;,
  0.312500;0.000000;,
  0.500000;0.000000;,
  0.437500;0.000000;,
  0.625000;0.000000;,
  0.562500;0.000000;,
  0.750000;0.000000;,
  0.687500;0.000000;,
  0.875000;0.000000;,
  0.812500;0.000000;,
  1.000000;0.000000;,
  0.937500;0.000000;,
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
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
