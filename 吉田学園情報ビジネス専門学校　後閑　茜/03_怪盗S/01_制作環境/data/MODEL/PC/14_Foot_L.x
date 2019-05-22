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
 76;
 -0.00591;-0.04017;-0.88291;,
 -0.01104;-0.14611;-1.26051;,
 0.21111;-0.13776;-1.01633;,
 0.11431;-0.03566;-0.75076;,
 0.30532;-0.08903;-0.42681;,
 0.16530;-0.00928;-0.43172;,
 0.21660;-0.02449;0.20534;,
 0.11718;0.02351;-0.11267;,
 -0.00427;-0.00626;0.24775;,
 -0.00175;0.04587;0.04499;,
 -0.22552;0.00411;0.20534;,
 -0.12209;0.03899;-0.11267;,
 -0.31992;-0.04858;-0.42681;,
 -0.17308;0.01261;-0.43172;,
 -0.23100;-0.10917;-1.01633;,
 -0.12496;-0.02018;-0.75076;,
 -0.01104;-0.14611;-1.26051;,
 -0.00591;-0.04017;-0.88291;,
 -0.00942;-0.25458;-1.43871;,
 0.27295;-0.26437;-1.18971;,
 0.39605;-0.20069;-0.41946;,
 0.27939;-0.13143;0.24407;,
 -0.00926;-0.10935;0.28078;,
 -0.29825;-0.09407;0.24407;,
 -0.42087;-0.14785;-0.41946;,
 -0.30469;-0.22701;-1.18971;,
 -0.00942;-0.25458;-1.43871;,
 -0.02314;-0.39590;-1.45931;,
 0.29044;-0.39620;-1.24450;,
 0.42368;-0.32728;-0.41080;,
 0.29721;-0.25636;0.26376;,
 -0.01525;-0.23300;0.29756;,
 -0.32803;-0.21591;0.26376;,
 -0.46055;-0.27008;-0.41080;,
 -0.33480;-0.35576;-1.24450;,
 -0.02314;-0.39590;-1.45931;,
 -0.02910;-0.51886;-1.43505;,
 0.26090;-0.51319;-1.17238;,
 0.38400;-0.44951;-0.40213;,
 0.26734;-0.38025;0.26140;,
 -0.02133;-0.35850;0.29438;,
 -0.31030;-0.34288;0.26140;,
 -0.43292;-0.39667;-0.40213;,
 -0.31674;-0.47582;-1.17238;,
 -0.02910;-0.51886;-1.43505;,
 -0.03329;-0.60541;-1.22834;,
 0.18884;-0.59751;-0.98431;,
 0.28305;-0.54878;-0.39479;,
 0.19438;-0.48396;0.23735;,
 -0.02654;-0.46601;0.27977;,
 -0.24782;-0.45535;0.23735;,
 -0.34219;-0.50833;-0.39479;,
 -0.25327;-0.56891;-0.98431;,
 -0.03329;-0.60541;-1.22834;,
 -0.03117;-0.52882;-0.38984;,
 -0.03329;-0.60541;-1.22834;,
 -0.03329;-0.60541;-1.22834;,
 -0.24782;-0.45535;0.23735;,
 0.19438;-0.48396;0.23735;,
 0.02396;0.16247;-0.44938;,
 -0.00591;-0.04017;-0.88291;,
 0.11431;-0.03566;-0.75076;,
 0.08895;0.12650;-0.40817;,
 -0.01603;0.16505;-0.44938;,
 0.00564;0.19828;-0.29594;,
 0.11572;0.10299;-0.27591;,
 0.03977;0.13179;-0.06619;,
 -0.04982;0.13759;-0.06619;,
 -0.11120;0.11767;-0.27591;,
 -0.10979;0.12204;-0.40817;,
 0.16530;-0.00928;-0.43172;,
 0.11718;0.02351;-0.11267;,
 -0.00175;0.04587;0.04499;,
 -0.12209;0.03899;-0.11267;,
 -0.17308;0.01261;-0.43172;,
 -0.12496;-0.02018;-0.75076;;
 
 72;
 4;3,2,1,0;,
 4;5,4,2,3;,
 4;7,6,4,5;,
 4;9,8,6,7;,
 4;11,10,8,9;,
 4;13,12,10,11;,
 4;15,14,12,13;,
 4;17,16,14,15;,
 4;2,19,18,1;,
 4;4,20,19,2;,
 4;6,21,20,4;,
 4;8,22,21,6;,
 4;10,23,22,8;,
 4;12,24,23,10;,
 4;14,25,24,12;,
 4;16,26,25,14;,
 4;19,28,27,18;,
 4;20,29,28,19;,
 4;21,30,29,20;,
 4;22,31,30,21;,
 4;23,32,31,22;,
 4;24,33,32,23;,
 4;25,34,33,24;,
 4;26,35,34,25;,
 4;28,37,36,27;,
 4;29,38,37,28;,
 4;30,39,38,29;,
 4;31,40,39,30;,
 4;32,41,40,31;,
 4;33,42,41,32;,
 4;34,43,42,33;,
 4;35,44,43,34;,
 4;37,46,45,36;,
 4;38,47,46,37;,
 4;39,48,47,38;,
 4;40,49,48,39;,
 4;41,50,49,40;,
 4;42,51,50,41;,
 4;43,52,51,42;,
 4;44,53,52,43;,
 3;46,47,54;,
 3;46,54,55;,
 3;54,52,56;,
 3;51,52,54;,
 3;51,54,57;,
 3;54,49,57;,
 3;48,49,54;,
 3;54,47,58;,
 3;61,60,59;,
 3;59,62,61;,
 3;59,60,63;,
 3;62,59,64;,
 3;65,62,64;,
 3;66,65,64;,
 3;67,66,64;,
 3;68,67,64;,
 3;69,68,64;,
 3;63,69,64;,
 3;59,63,64;,
 3;70,61,62;,
 3;62,65,70;,
 3;71,70,65;,
 3;65,66,71;,
 3;72,71,66;,
 3;66,67,72;,
 3;73,72,67;,
 3;67,68,73;,
 3;74,73,68;,
 3;68,69,74;,
 3;75,74,69;,
 3;69,63,75;,
 3;60,75,63;;
 
 MeshMaterialList {
  12;
  72;
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11;;
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
   0.090980;0.090980;0.090980;1.000000;;
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
  75;
  0.278698;0.960269;-0.014484;,
  0.058956;0.927217;-0.369854;,
  0.541526;0.796095;-0.270151;,
  0.771612;0.632667;-0.065938;,
  0.725088;0.649302;0.229464;,
  0.060849;0.944313;0.323375;,
  -0.614346;0.779007;0.125409;,
  -0.723412;0.688745;-0.048011;,
  -0.454846;0.846608;-0.276351;,
  0.058245;0.923218;-0.379837;,
  0.504511;0.821288;-0.266374;,
  0.657926;0.749836;-0.069856;,
  0.525092;0.847927;0.072788;,
  0.063374;0.985354;0.158306;,
  -0.419406;0.904823;0.073439;,
  -0.566149;0.821245;-0.070932;,
  -0.401595;0.874318;-0.272560;,
  0.044532;0.656038;-0.753413;,
  0.757225;0.495836;-0.425154;,
  0.910956;0.411330;-0.031078;,
  0.910959;0.396150;0.114973;,
  0.016788;0.260852;0.965233;,
  -0.118519;0.265175;0.956888;,
  -0.863028;0.504166;-0.031596;,
  -0.691844;0.578272;-0.432382;,
  0.616013;-0.075708;-0.784090;,
  0.862076;-0.072715;-0.501536;,
  0.998706;-0.048391;0.015620;,
  0.982604;-0.035789;0.182233;,
  0.004001;0.062033;0.998066;,
  -0.109751;0.067163;0.991687;,
  -0.998615;0.050270;0.015505;,
  -0.863802;0.020766;-0.503404;,
  0.184761;-0.823551;-0.536309;,
  0.702365;-0.627042;-0.336902;,
  0.862734;-0.502807;0.053620;,
  0.862912;-0.465583;0.196509;,
  -0.007743;-0.120304;0.992707;,
  -0.135778;-0.113055;0.984268;,
  -0.910528;-0.410041;0.052958;,
  -0.768096;-0.546875;-0.333101;,
  -0.062943;-0.990823;-0.119613;,
  0.245555;-0.968077;-0.050290;,
  0.364082;-0.927215;0.087848;,
  0.225408;-0.964722;0.136028;,
  -0.013378;-0.207886;0.978061;,
  -0.158642;-0.198522;0.967172;,
  -0.472419;-0.877077;0.086922;,
  -0.363159;-0.930438;-0.048996;,
  -0.064290;-0.993639;0.092457;,
  0.349625;0.884418;-0.309140;,
  0.717524;0.681865;-0.142197;,
  0.815435;0.573083;0.081495;,
  0.530232;0.746319;0.402321;,
  -0.473175;0.783047;0.403662;,
  -0.773233;0.628045;0.087583;,
  -0.670165;0.732116;-0.122007;,
  -0.240980;0.919263;-0.311263;,
  0.175117;0.351492;0.919667;,
  0.151792;0.251730;0.955820;,
  0.023368;0.363401;0.931340;,
  -0.128926;0.366840;0.921307;,
  -0.864687;0.488672;0.116255;,
  0.117701;0.056095;0.991464;,
  -0.981376;0.061016;0.182151;,
  -0.615735;0.000315;-0.787953;,
  0.120414;-0.125566;0.984751;,
  -0.906907;-0.373912;0.194189;,
  -0.615597;-0.304759;-0.726748;,
  0.132172;-0.212821;0.968110;,
  -0.342508;-0.929844;0.134454;,
  -0.064281;-0.993529;0.093638;,
  -0.560949;0.826169;0.052737;,
  0.776889;0.323535;0.540157;,
  -0.766367;0.291974;0.572217;;
  72;
  4;2,10,9,1;,
  4;3,11,10,2;,
  4;4,12,11,3;,
  4;5,13,12,4;,
  4;6,14,13,5;,
  4;7,15,14,6;,
  4;8,16,15,7;,
  4;1,9,16,8;,
  4;10,18,17,9;,
  4;11,19,18,10;,
  4;12,20,19,11;,
  4;60,21,59,58;,
  4;61,22,21,60;,
  4;15,23,62,14;,
  4;16,24,23,15;,
  4;9,17,24,16;,
  4;18,26,25,17;,
  4;19,27,26,18;,
  4;20,28,27,19;,
  4;21,29,63,59;,
  4;22,30,29,21;,
  4;23,31,64,62;,
  4;24,32,31,23;,
  4;17,65,32,24;,
  4;26,34,33,25;,
  4;27,35,34,26;,
  4;28,36,35,27;,
  4;29,37,66,63;,
  4;30,38,37,29;,
  4;31,39,67,64;,
  4;32,40,39,31;,
  4;65,68,40,32;,
  4;34,42,41,33;,
  4;35,43,42,34;,
  4;36,44,43,35;,
  4;37,45,69,66;,
  4;38,46,45,37;,
  4;39,47,70,67;,
  4;40,48,47,39;,
  4;33,41,48,40;,
  3;42,43,49;,
  3;42,49,41;,
  3;49,48,41;,
  3;47,48,49;,
  3;47,49,70;,
  3;49,71,70;,
  3;44,71,49;,
  3;49,43,44;,
  3;2,1,50;,
  3;50,51,2;,
  3;50,1,57;,
  3;51,50,0;,
  3;52,51,0;,
  3;53,52,0;,
  3;54,53,0;,
  3;55,54,72;,
  3;56,55,72;,
  3;57,56,0;,
  3;50,57,0;,
  3;3,2,51;,
  3;51,52,3;,
  3;4,3,52;,
  3;52,53,4;,
  3;73,4,53;,
  3;53,54,5;,
  3;74,74,54;,
  3;54,55,6;,
  3;7,6,55;,
  3;55,56,7;,
  3;8,7,56;,
  3;56,57,8;,
  3;1,8,57;;
 }
 MeshTextureCoords {
  76;
  0.000000;0.125000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.125000;0.125000;,
  0.250000;0.250000;,
  0.250000;0.125000;,
  0.375000;0.250000;,
  0.375000;0.125000;,
  0.500000;0.250000;,
  0.500000;0.125000;,
  0.625000;0.250000;,
  0.625000;0.125000;,
  0.750000;0.250000;,
  0.750000;0.125000;,
  0.875000;0.250000;,
  0.875000;0.125000;,
  1.000000;0.250000;,
  1.000000;0.125000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.000000;0.000000;,
  0.000000;0.375000;,
  0.000000;0.187500;,
  0.312500;0.375000;,
  0.187500;0.375000;,
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
