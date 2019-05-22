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
 68;
 -1.48302;0.10890;-1.61082;,
 -1.44263;-0.48236;-1.66376;,
 0.00187;-0.95095;-2.30285;,
 -0.00006;0.01695;-2.26177;,
 -1.48302;0.10890;-1.61082;,
 -1.53963;0.09235;-0.92520;,
 -1.55155;-0.42239;-0.96057;,
 -1.53963;0.09235;-0.92520;,
 -1.53964;0.10352;-0.28255;,
 -1.53964;-0.51445;-0.13163;,
 -1.57953;-1.22683;-1.66376;,
 0.00200;-1.29617;-2.19256;,
 -1.90767;-1.12211;-0.85177;,
 -1.55959;-1.10168;0.00574;,
 -1.85398;-1.63751;-1.75405;,
 0.00200;-2.17505;-2.21156;,
 -1.94497;-1.67914;-0.82234;,
 -1.51949;-1.68129;-0.06930;,
 -0.36891;-2.35892;-1.57923;,
 0.00002;-2.40217;-1.96958;,
 -0.00146;0.17459;-0.28664;,
 0.00085;-0.45010;-0.16645;,
 -0.00063;-1.30242;0.20443;,
 0.01015;-1.54786;0.20522;,
 -1.18641;-2.37316;-0.66266;,
 -1.55598;-2.03180;0.01374;,
 0.00059;-1.88407;0.26090;,
 0.00238;-2.35382;-0.66587;,
 -0.00134;-2.59540;0.55259;,
 -1.29721;-2.70109;0.30543;,
 -0.25976;-3.30771;0.92426;,
 -1.53036;-3.61587;0.67710;,
 -0.76609;-4.17365;1.14999;,
 -2.02092;-4.74319;0.90283;,
 0.00006;0.01695;-2.26177;,
 -0.00187;-0.95095;-2.30285;,
 1.44263;-0.48236;-1.66376;,
 1.48302;0.10890;-1.61082;,
 1.55155;-0.42239;-0.96057;,
 1.53963;0.09235;-0.92520;,
 1.48302;0.10890;-1.61082;,
 1.53964;-0.51445;-0.13163;,
 1.53964;0.10352;-0.28255;,
 1.53963;0.09235;-0.92520;,
 -0.00200;-1.29617;-2.19256;,
 1.57953;-1.22683;-1.66376;,
 1.90767;-1.12211;-0.85177;,
 1.55959;-1.10168;0.00574;,
 -0.00200;-2.17505;-2.21156;,
 1.85398;-1.63751;-1.75405;,
 1.94497;-1.67914;-0.82234;,
 1.51949;-1.68129;-0.06930;,
 -0.00002;-2.40217;-1.96958;,
 0.36891;-2.35892;-1.57923;,
 -0.00085;-0.45010;-0.16645;,
 0.00146;0.17459;-0.28664;,
 0.00063;-1.30242;0.20443;,
 -0.01015;-1.54786;0.20522;,
 1.18641;-2.37316;-0.66266;,
 1.55598;-2.03180;0.01374;,
 -0.00059;-1.88407;0.26090;,
 -0.00238;-2.35382;-0.66587;,
 1.29721;-2.70109;0.30543;,
 0.00134;-2.59540;0.55259;,
 1.53036;-3.61587;0.67710;,
 0.25976;-3.30771;0.92426;,
 2.02092;-4.74319;0.90283;,
 0.76609;-4.17365;1.14999;;
 
 48;
 4;3,2,1,0;,
 4;1,6,5,4;,
 4;6,9,8,7;,
 4;2,11,10,1;,
 4;10,12,6,1;,
 4;12,13,9,6;,
 4;11,15,14,10;,
 4;14,16,12,10;,
 4;16,17,13,12;,
 4;15,19,18,14;,
 4;9,21,20,8;,
 4;13,22,21,9;,
 4;17,23,22,13;,
 4;18,24,16,14;,
 4;24,25,17,16;,
 4;25,26,23,17;,
 4;18,19,27,24;,
 4;24,27,26,25;,
 4;25,29,28,26;,
 4;29,31,30,28;,
 4;31,33,32,30;,
 4;26,28,29,25;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;37,36,35,34;,
 4;40,39,38,36;,
 4;43,42,41,38;,
 4;36,45,44,35;,
 4;36,38,46,45;,
 4;38,41,47,46;,
 4;45,49,48,44;,
 4;45,46,50,49;,
 4;46,47,51,50;,
 4;49,53,52,48;,
 4;42,55,54,41;,
 4;41,54,56,47;,
 4;47,56,57,51;,
 4;49,50,58,53;,
 4;50,51,59,58;,
 4;51,57,60,59;,
 4;58,61,52,53;,
 4;59,60,61,58;,
 4;60,63,62,59;,
 4;63,65,64,62;,
 4;65,67,66,64;,
 4;59,62,63,60;,
 4;62,64,65,63;,
 4;64,66,67,65;;
 
 MeshMaterialList {
  12;
  48;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.483200;0.483200;0.483200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game112\\Desktop\\�f��\\���f�����O\\bg_biceps_a_1.jpg";
   }
  }
  Material {
   0.552000;0.552000;0.552000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game112\\Desktop\\�f��\\���f�����O\\bg_biceps_a_2.jpg";
   }
  }
  Material {
   0.800000;0.664800;0.473600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.295200;0.295200;0.295200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.796800;0.169600;1.000000;;
   16.000000;
   0.300000;0.300000;0.300000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.031200;0.000000;1.000000;;
   19.000000;
   0.380000;0.380000;0.380000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.373600;0.373600;0.373600;1.000000;;
   5.000000;
   0.190000;0.190000;0.190000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.156800;0.072000;0.316800;1.000000;;
   5.000000;
   0.190000;0.190000;0.190000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.091200;0.091200;0.091200;1.000000;;
   24.000000;
   0.520000;0.520000;0.520000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  72;
  -0.396216;0.046474;-0.916981;,
  -0.377194;-0.032379;-0.925568;,
  -0.616043;0.078462;-0.783795;,
  -0.993270;-0.012767;-0.115113;,
  -0.988071;0.148018;-0.042491;,
  -0.999885;0.013394;0.007175;,
  -0.980448;0.158002;0.117294;,
  -0.298002;0.026934;-0.954185;,
  -0.699307;0.186883;-0.689960;,
  -0.971696;0.232846;0.039874;,
  -0.930804;0.144138;0.335898;,
  -0.233475;0.164263;-0.958388;,
  -0.983883;-0.004448;0.178756;,
  -0.625342;-0.057239;0.778249;,
  -0.286368;-0.922245;-0.259726;,
  -0.374387;-0.892786;-0.250534;,
  0.002966;0.213143;0.977017;,
  -0.011804;0.264128;0.964415;,
  -0.095169;0.124373;0.987661;,
  -0.172337;0.067780;0.982703;,
  -0.426908;-0.890648;0.156510;,
  -0.904121;-0.316345;0.287212;,
  -0.186811;0.279993;0.941651;,
  -0.008607;-0.970178;0.242240;,
  -0.214071;0.410526;0.886365;,
  -0.265201;0.409909;0.872722;,
  -0.293035;0.352104;0.888906;,
  0.396216;0.046474;-0.916981;,
  0.377194;-0.032379;-0.925568;,
  0.616043;0.078462;-0.783795;,
  0.993270;-0.012767;-0.115113;,
  0.988071;0.148018;-0.042491;,
  0.999885;0.013394;0.007175;,
  0.980448;0.158002;0.117294;,
  0.298002;0.026934;-0.954185;,
  0.699307;0.186883;-0.689960;,
  0.971696;0.232846;0.039874;,
  0.930804;0.144138;0.335898;,
  0.233475;0.164263;-0.958388;,
  0.983883;-0.004448;0.178756;,
  0.625342;-0.057239;0.778249;,
  0.286368;-0.922245;-0.259726;,
  0.374387;-0.892786;-0.250534;,
  -0.002966;0.213143;0.977017;,
  0.011804;0.264128;0.964415;,
  0.095169;0.124373;0.987661;,
  0.172337;0.067780;0.982703;,
  0.426908;-0.890648;0.156510;,
  0.904121;-0.316345;0.287212;,
  0.186811;0.279993;0.941651;,
  0.008607;-0.970178;0.242240;,
  0.214071;0.410526;0.886365;,
  0.265201;0.409909;0.872722;,
  0.293035;0.352104;0.888906;,
  -0.920046;0.318288;-0.228491;,
  -0.519772;-0.771301;-0.367330;,
  -0.499530;-0.708186;-0.498941;,
  -0.528727;-0.817668;-0.227742;,
  0.013914;-0.890930;0.453927;,
  0.190934;-0.353206;-0.915855;,
  0.214071;-0.410526;-0.886365;,
  0.265201;-0.409909;-0.872722;,
  0.293035;-0.352104;-0.888906;,
  0.920046;0.318288;-0.228491;,
  0.499530;-0.708186;-0.498941;,
  0.519772;-0.771301;-0.367330;,
  0.528727;-0.817668;-0.227742;,
  -0.013914;-0.890930;0.453927;,
  -0.190934;-0.353206;-0.915855;,
  -0.214071;-0.410526;-0.886365;,
  -0.265201;-0.409909;-0.872722;,
  -0.293035;-0.352104;-0.888906;;
  48;
  4;0,1,2,0;,
  4;3,4,3,3;,
  4;4,6,5,5;,
  4;1,7,8,2;,
  4;8,9,4,2;,
  4;9,10,6,4;,
  4;7,11,11,8;,
  4;54,12,9,8;,
  4;12,13,10,9;,
  4;56,14,15,55;,
  4;17,17,16,16;,
  4;18,18,17,17;,
  4;13,19,18,18;,
  4;15,20,57,55;,
  4;20,21,13,12;,
  4;22,22,19,13;,
  4;15,14,23,20;,
  4;20,23,58,58;,
  4;22,24,24,22;,
  4;24,25,25,24;,
  4;25,26,26,25;,
  4;59,60,60,59;,
  4;60,61,61,60;,
  4;61,62,62,61;,
  4;27,29,28,27;,
  4;30,30,31,30;,
  4;32,32,33,31;,
  4;29,35,34,28;,
  4;29,31,36,35;,
  4;31,33,37,36;,
  4;35,38,38,34;,
  4;35,36,39,63;,
  4;36,37,40,39;,
  4;65,42,41,64;,
  4;43,43,44,44;,
  4;44,44,45,45;,
  4;45,45,46,40;,
  4;65,66,47,42;,
  4;39,40,48,47;,
  4;40,46,49,49;,
  4;47,50,41,42;,
  4;67,67,50,47;,
  4;49,51,51,49;,
  4;51,52,52,51;,
  4;52,53,53,52;,
  4;68,69,69,68;,
  4;69,70,70,69;,
  4;70,71,71,70;;
 }
 MeshTextureCoords {
  68;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
