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
 32;
 -10.80711;-0.55528;-2.82261;,
 -15.14703;-0.52018;7.84747;,
 -6.54550;22.41775;1.57576;,
 -2.20558;12.67014;-9.09434;,
 5.06831;18.13934;10.20804;,
 9.40823;8.39173;-0.46205;,
 -3.53322;-0.53136;16.47977;,
 5.22604;-0.52634;5.80967;,
 -15.14703;-0.52018;7.84747;,
 -10.80711;-0.55528;-2.82261;,
 -3.53322;-0.53136;16.47977;,
 5.06831;18.13934;10.20804;,
 5.22604;-0.52634;5.80967;,
 9.40823;8.39173;-0.46205;,
 10.04327;0.04252;5.26103;,
 -0.96624;0.04252;-9.10724;,
 12.45144;0.04252;-9.80665;,
 15.58742;0.04252;-3.07099;,
 10.04327;0.04252;5.26103;,
 15.58742;0.04252;-3.07099;,
 9.09352;15.78192;-0.59795;,
 -0.96624;0.04252;-9.10724;,
 10.04327;0.04252;5.26103;,
 -0.69853;10.51965;-12.01377;,
 -16.05468;-0.01780;-8.04351;,
 -10.99915;8.67917;-4.86266;,
 -1.69607;-0.00191;-16.54691;,
 -0.69853;10.51965;-12.01377;,
 -2.66183;0.26392;-5.95027;,
 -16.05468;-0.01780;-8.04351;,
 -1.69607;-0.00191;-16.54691;,
 -1.69607;-0.00191;-16.54691;;
 
 17;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;1,10,11,2;,
 4;12,0,3,13;,
 4;14,15,16,17;,
 3;18,19,20;,
 3;19,16,20;,
 3;16,21,20;,
 3;21,22,20;,
 3;23,24,25;,
 3;26,27,28;,
 3;27,25,28;,
 3;25,29,28;,
 3;29,30,28;,
 3;31,24,23;;
 
 MeshMaterialList {
  1;
  17;
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
   0.558431;0.558431;0.558431;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\UV\\Stone.jpg";
   }
  }
 }
 MeshNormals {
  21;
  -0.851368;0.246578;-0.463002;,
  0.570023;0.708751;-0.415627;,
  0.831102;-0.120887;0.542821;,
  0.000000;-1.000000;-0.000000;,
  0.925701;0.368570;0.085052;,
  0.986619;-0.133727;0.093273;,
  -0.509135;0.470388;-0.720775;,
  -0.540930;0.547846;-0.638169;,
  0.196593;-0.897507;-0.394757;,
  -0.000176;-0.999999;0.001259;,
  -0.482163;0.431773;0.762293;,
  0.352854;-0.610081;-0.709433;,
  0.806439;0.248414;0.536606;,
  0.829679;0.403011;-0.386282;,
  -0.045163;0.497280;-0.866414;,
  -0.781418;0.175733;0.598752;,
  0.482318;0.375569;0.791402;,
  0.190293;0.061902;0.979774;,
  -0.143435;-0.265330;0.953429;,
  0.016865;-0.999504;0.026610;,
  -0.470297;0.386423;-0.793409;;
  17;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;8,9,9,8;,
  4;10,10,10,10;,
  4;8,8,11,11;,
  4;3,3,3,3;,
  3;12,4,4;,
  3;4,13,4;,
  3;14,14,14;,
  3;15,15,15;,
  3;6,6,7;,
  3;5,5,5;,
  3;16,17,17;,
  3;17,18,17;,
  3;19,19,19;,
  3;20,6,6;;
 }
 MeshTextureCoords {
  32;
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.500000;0.000000;,
  0.750000;0.250000;,
  0.500000;0.500000;,
  0.250000;0.250000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;1.000000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.250000;0.250000;,
  0.750000;0.250000;,
  0.500000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;1.000000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.500000;0.000000;;
 }
}
