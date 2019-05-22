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
 79;
 -1.63258;1.09077;0.00037;,
 -2.84165;0.85432;-0.54448;,
 -1.61453;0.92973;-0.61718;,
 -1.63258;1.09077;0.00037;,
 -3.74223;0.79952;-0.32542;,
 -1.63258;1.09077;0.00037;,
 -4.07427;0.77934;-0.01904;,
 -1.63258;1.09077;0.00037;,
 -3.74853;0.79928;0.29254;,
 -1.63258;1.09077;0.00037;,
 -2.85253;0.85391;0.52584;,
 -1.63258;1.09077;0.00037;,
 -1.62706;0.92924;0.61827;,
 -3.70144;0.35733;-0.94327;,
 -1.57451;0.48685;-1.06984;,
 -5.26136;0.26240;-0.56384;,
 -5.83630;0.22750;-0.03317;,
 -5.27225;0.26199;0.50647;,
 -3.72025;0.35659;0.91057;,
 -1.59622;0.48601;1.07082;,
 -5.78279;-0.37658;-0.65099;,
 -3.98157;-0.26695;-1.08917;,
 -6.44673;-0.41690;-0.03827;,
 -5.79532;-0.37707;0.58490;,
 -4.00328;-0.26782;1.05149;,
 -1.55067;-0.11839;1.23655;,
 -1.52635;-0.11776;-1.23587;,
 -3.60701;-0.85131;-0.94302;,
 -1.48082;-0.72206;-1.06911;,
 -5.16689;-0.94625;-0.56357;,
 -5.74184;-0.98114;-0.03293;,
 -5.17776;-0.94668;0.50677;,
 -3.62582;-0.85205;0.91087;,
 -2.67804;-1.23919;-0.54402;,
 -1.45089;-1.16389;-0.61672;,
 -3.57868;-1.29399;-0.32496;,
 -3.91064;-1.31415;-0.01858;,
 -3.58490;-1.29423;0.29300;,
 -2.68889;-1.23960;0.52632;,
 -1.44446;-1.32665;0.00102;,
 -1.44446;-1.32665;0.00102;,
 -1.44446;-1.32665;0.00102;,
 -1.44446;-1.32665;0.00102;,
 -1.44446;-1.32665;0.00102;,
 -1.46342;-1.16440;0.61870;,
 -1.44446;-1.32665;0.00102;,
 -1.49834;-0.84658;1.09211;,
 -3.69118;0.36524;-1.28334;,
 -1.58319;0.48954;-1.32643;,
 -1.52526;-0.12201;-1.42651;,
 -3.99047;-0.25871;-1.36369;,
 -4.18618;0.27671;-1.20094;,
 -4.42862;-0.22866;-1.26602;,
 -4.19466;0.27031;-0.91216;,
 -4.42156;-0.23537;-1.03033;,
 -1.61453;0.92973;-0.61718;,
 -1.57451;0.48685;-1.06984;,
 -0.78130;0.49563;-0.54044;,
 -0.63736;0.14252;-0.69261;,
 -0.93559;0.74146;-0.20834;,
 0.02133;0.00564;0.01146;,
 -0.93892;0.74093;0.21857;,
 -0.79019;0.49461;0.55211;,
 -0.64925;0.14192;0.70564;,
 -0.59532;-0.26270;0.70111;,
 -0.66536;-0.62506;0.54389;,
 -0.77862;-0.85039;0.21523;,
 -0.77526;-0.85068;-0.20367;,
 -0.67494;-0.59432;-0.53293;,
 -0.60191;-0.23148;-0.68936;,
 -1.59622;0.48601;1.07082;,
 -1.62706;0.92924;0.61827;,
 -1.55067;-0.11839;1.23655;,
 -1.52635;-0.11776;-1.23587;,
 -1.48082;-0.72206;-1.06911;,
 -1.45089;-1.16389;-0.61672;,
 -1.44446;-1.32665;0.00102;,
 -1.46342;-1.16440;0.61870;,
 -1.63258;1.09077;0.00037;;
 
 79;
 3;2,1,0;,
 3;1,4,3;,
 3;4,6,5;,
 3;6,8,7;,
 3;8,10,9;,
 3;10,12,11;,
 4;14,13,1,2;,
 4;13,15,4,1;,
 4;15,16,6,4;,
 4;16,17,8,6;,
 4;17,18,10,8;,
 4;18,19,12,10;,
 4;21,20,15,13;,
 4;20,22,16,15;,
 4;22,23,17,16;,
 4;23,24,18,17;,
 4;24,25,19,18;,
 4;28,27,21,26;,
 4;27,29,20,21;,
 4;29,30,22,20;,
 4;30,31,23,22;,
 4;31,32,24,23;,
 4;34,33,27,28;,
 4;33,35,29,27;,
 4;35,36,30,29;,
 4;36,37,31,30;,
 4;37,38,32,31;,
 3;39,33,34;,
 3;40,35,33;,
 3;41,36,35;,
 3;42,37,36;,
 3;43,38,37;,
 3;45,44,38;,
 4;44,46,32,38;,
 4;46,25,24,32;,
 4;13,14,48,47;,
 4;26,21,50,49;,
 4;14,26,49,48;,
 4;49,50,47,48;,
 4;47,50,52,51;,
 4;13,47,51,53;,
 4;50,21,54,52;,
 4;54,53,51,52;,
 3;57,56,55;,
 3;56,57,58;,
 3;59,57,55;,
 3;57,59,60;,
 3;59,61,60;,
 3;61,62,60;,
 3;62,63,60;,
 3;63,64,60;,
 3;64,65,60;,
 3;65,66,60;,
 3;66,67,60;,
 3;67,68,60;,
 3;68,69,60;,
 3;69,58,60;,
 3;58,57,60;,
 3;71,70,62;,
 3;63,62,70;,
 3;71,62,61;,
 3;63,70,72;,
 3;64,63,72;,
 3;73,56,58;,
 3;73,58,69;,
 3;69,74,73;,
 3;74,69,68;,
 3;68,75,74;,
 3;75,68,67;,
 3;67,76,75;,
 3;76,67,66;,
 3;66,77,76;,
 3;77,66,65;,
 3;65,46,77;,
 3;46,65,64;,
 3;64,72,46;,
 3;61,78,71;,
 3;78,61,59;,
 3;78,59,55;;
 
 MeshMaterialList {
  14;
  79;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.483200;0.483200;0.483200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.552000;0.552000;0.552000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.664800;0.473600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.633600;0.360800;0.213600;1.000000;;
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
   0.345000;0.086000;0.063000;1.000000;;
   24.000000;
   0.400000;0.400000;0.400000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.091200;0.091200;0.091200;1.000000;;
   24.000000;
   0.520000;0.520000;0.520000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
        "data\\TEXTURE\\Player\\Eye.png";
   }
  }
  Material {
   0.263200;0.084800;0.009600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  65;
  0.069115;0.997608;0.001020;,
  0.229654;0.856632;-0.461997;,
  -0.117130;0.888010;-0.444656;,
  -0.181250;0.942934;-0.279326;,
  -0.212246;0.977215;-0.001758;,
  -0.185695;0.942921;0.276436;,
  -0.124215;0.887843;0.443063;,
  0.222423;0.855843;0.466970;,
  0.266693;0.711562;-0.650042;,
  -0.168527;0.857184;-0.486657;,
  -0.348895;0.696111;-0.627457;,
  -0.509418;0.860507;-0.004542;,
  -0.359177;0.696208;0.621519;,
  -0.167107;0.543274;0.822756;,
  0.235541;0.512048;0.826031;,
  0.367247;-0.041156;-0.929213;,
  -0.169785;-0.106059;-0.979757;,
  -0.452484;-0.033323;-0.891150;,
  -0.581794;0.555786;-0.593816;,
  -0.397024;0.194334;0.896998;,
  -0.165461;-0.003198;0.986211;,
  0.262524;0.044393;0.963904;,
  0.319172;-0.470118;-0.822872;,
  -0.086181;-0.561690;-0.822847;,
  -0.258774;-0.738264;-0.622898;,
  -0.309750;-0.926087;-0.215449;,
  -0.268839;-0.739223;0.617475;,
  -0.107306;-0.581517;0.806427;,
  0.349557;-0.813781;-0.464296;,
  -0.007938;-0.896169;-0.443642;,
  -0.064786;-0.958477;-0.277712;,
  -0.091072;-0.995844;-0.001299;,
  -0.069172;-0.958765;0.275653;,
  -0.018206;-0.910086;0.414018;,
  0.335659;-0.850489;0.404972;,
  0.200895;-0.979612;0.001593;,
  0.322430;-0.501685;0.802715;,
  -0.059053;0.998111;0.016933;,
  -0.116186;0.993080;0.017103;,
  0.057347;-0.998344;-0.004642;,
  -0.008732;-0.999838;-0.015767;,
  -0.609301;0.792782;0.015817;,
  -0.074771;-0.996840;-0.026820;,
  -0.198072;0.218076;-0.955620;,
  0.751937;0.644972;0.136388;,
  0.542298;0.662359;-0.516908;,
  0.534169;0.661048;0.526952;,
  0.575569;0.294154;0.763016;,
  0.589230;0.287215;-0.755192;,
  0.627258;-0.186454;-0.756163;,
  0.640740;-0.565202;-0.519614;,
  0.640690;-0.747565;-0.175111;,
  0.632938;-0.758318;0.156022;,
  0.648950;-0.599700;0.468213;,
  0.628039;-0.163870;0.760732;,
  0.510746;0.839898;0.183601;,
  0.513499;0.840370;-0.173484;,
  -0.592012;0.556160;0.583273;,
  -0.503232;-0.634191;-0.586992;,
  -0.513118;-0.635496;0.576936;,
  0.995742;0.091021;-0.014573;,
  -0.031342;0.150997;-0.988037;,
  -0.115188;0.185311;-0.975906;,
  -0.907183;0.420597;0.010823;,
  0.850872;-0.505648;-0.142609;;
  79;
  3;1,2,0;,
  3;2,3,0;,
  3;3,4,0;,
  3;4,5,0;,
  3;5,6,0;,
  3;6,7,0;,
  4;8,9,2,1;,
  4;9,10,3,2;,
  4;10,11,4,3;,
  4;11,12,5,4;,
  4;12,13,6,5;,
  4;13,14,7,6;,
  4;16,17,10,9;,
  4;17,18,11,10;,
  4;57,19,12,11;,
  4;19,20,13,12;,
  4;20,21,14,13;,
  4;22,23,16,15;,
  4;23,24,17,16;,
  4;24,25,58,17;,
  4;59,26,59,59;,
  4;26,27,20,19;,
  4;28,29,23,22;,
  4;29,30,24,23;,
  4;30,31,25,24;,
  4;31,32,26,25;,
  4;32,33,27,26;,
  3;35,29,28;,
  3;35,30,29;,
  3;35,31,30;,
  3;35,32,31;,
  3;35,33,32;,
  3;35,34,33;,
  4;34,36,27,33;,
  4;36,21,20,27;,
  4;9,8,37,38;,
  4;39,40,40,39;,
  4;60,60,60,60;,
  4;61,62,62,61;,
  4;62,62,43,43;,
  4;9,38,41,41;,
  4;40,40,42,42;,
  4;63,41,41,63;,
  3;45,8,1;,
  3;8,45,48;,
  3;56,45,1;,
  3;45,56,44;,
  3;56,55,44;,
  3;55,46,44;,
  3;46,47,44;,
  3;47,54,44;,
  3;54,53,64;,
  3;53,52,64;,
  3;52,51,64;,
  3;51,50,64;,
  3;50,49,64;,
  3;49,48,64;,
  3;48,45,44;,
  3;7,14,46;,
  3;47,46,14;,
  3;7,46,55;,
  3;47,14,21;,
  3;54,47,21;,
  3;15,8,48;,
  3;15,48,49;,
  3;49,22,15;,
  3;22,49,50;,
  3;50,28,22;,
  3;28,50,51;,
  3;51,35,28;,
  3;35,51,52;,
  3;52,34,35;,
  3;34,52,53;,
  3;53,36,34;,
  3;36,53,54;,
  3;54,21,36;,
  3;55,0,7;,
  3;0,55,56;,
  3;0,56,1;;
 }
 MeshTextureCoords {
  79;
  0.041670;0.000000;,
  0.083330;0.166670;,
  0.000000;0.166670;,
  0.125000;0.000000;,
  0.166670;0.166670;,
  0.208330;0.000000;,
  0.250000;0.166670;,
  0.291670;0.000000;,
  0.333330;0.166670;,
  0.375000;0.000000;,
  0.416670;0.166670;,
  0.458330;0.000000;,
  0.500000;0.166670;,
  0.083330;0.333330;,
  0.000000;0.333330;,
  0.166670;0.333330;,
  0.250000;0.333330;,
  0.333330;0.333330;,
  0.416670;0.333330;,
  0.500000;0.333330;,
  0.166670;0.500000;,
  0.083330;0.500000;,
  0.250000;0.500000;,
  0.333330;0.500000;,
  0.416670;0.500000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  0.083330;0.666670;,
  0.000000;0.666670;,
  0.166670;0.666670;,
  0.250000;0.666670;,
  0.333330;0.666670;,
  0.416670;0.666670;,
  0.083330;0.833330;,
  0.000000;0.833330;,
  0.166670;0.833330;,
  0.250000;0.833330;,
  0.333330;0.833330;,
  0.416670;0.833330;,
  0.041670;1.000000;,
  0.125000;1.000000;,
  0.208330;1.000000;,
  0.291670;1.000000;,
  0.375000;1.000000;,
  0.500000;0.833330;,
  0.458330;1.000000;,
  0.000000;0.000000;,
  0.083330;0.333330;,
  0.000000;0.333330;,
  0.000000;0.500000;,
  0.083330;0.500000;,
  0.083330;0.333330;,
  0.083330;0.500000;,
  0.083330;0.333330;,
  0.083330;0.500000;,
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
