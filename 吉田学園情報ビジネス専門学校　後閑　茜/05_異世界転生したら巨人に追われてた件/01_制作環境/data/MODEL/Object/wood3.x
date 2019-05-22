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
 132;
 -0.44435;132.43726;-26.99174;,
 12.48499;132.50864;-20.42127;,
 8.94420;106.32754;-20.23783;,
 -3.98515;106.25611;-26.80826;,
 17.84051;132.68107;-4.55892;,
 14.29971;106.49973;-4.37545;,
 12.48499;132.85329;11.30354;,
 8.94420;106.67223;11.48696;,
 -0.44435;132.92492;17.87397;,
 -3.98515;106.74363;18.05740;,
 -13.37368;132.85329;11.30354;,
 -16.91451;106.67223;11.48696;,
 -18.72918;132.68107;-4.55892;,
 -22.27004;106.49973;-4.37545;,
 -13.37368;132.50864;-20.42127;,
 -16.91451;106.32754;-20.23783;,
 -0.44435;132.43726;-26.99174;,
 -3.98515;106.25611;-26.80826;,
 6.41628;81.43977;-23.24259;,
 -6.51307;81.86790;-29.80424;,
 11.77178;80.40574;-7.40131;,
 6.41628;79.37175;8.43996;,
 -6.51307;78.94363;15.00165;,
 -19.44245;79.37175;8.43996;,
 -24.44107;80.40574;-7.40131;,
 -19.44245;81.43977;-23.24259;,
 -6.51307;81.86790;-29.80424;,
 8.43903;55.29331;-27.23217;,
 -4.49031;55.72154;-30.90451;,
 13.79456;54.25939;-8.50161;,
 8.43903;53.22532;7.33969;,
 -4.49031;52.79711;13.90134;,
 -17.41968;53.22532;5.46204;,
 -22.77518;54.25939;-8.50161;,
 -17.41968;55.29331;-24.34286;,
 -4.49031;55.72154;-30.90451;,
 9.95878;28.00531;-22.16404;,
 -2.97056;28.00531;-28.73476;,
 15.31431;28.00531;-6.30103;,
 9.95878;28.00531;9.56196;,
 -2.97056;28.00531;16.13264;,
 -15.89993;27.07915;6.23944;,
 -21.25543;28.11299;-9.60181;,
 -15.89993;29.14712;-25.44314;,
 -2.97056;28.00531;-28.73476;,
 14.01150;1.82290;-23.17094;,
 1.89505;1.82290;-32.81406;,
 19.22784;1.82290;-6.30103;,
 14.08486;1.82290;9.56196;,
 -2.97056;1.82290;22.79980;,
 -15.89993;1.82290;14.18854;,
 -27.78999;1.82290;-6.30103;,
 -20.78313;1.82290;-24.62543;,
 1.89505;1.82290;-32.81406;,
 -2.97056;1.82290;-6.30103;,
 -2.97056;1.82290;-6.30103;,
 -2.97056;1.82290;-6.30103;,
 -2.97056;1.82290;-6.30103;,
 -2.97056;1.82290;-6.30103;,
 -2.97056;1.82290;-6.30103;,
 -2.97056;1.82290;-6.30103;,
 -2.97056;1.82290;-6.30103;,
 -0.72184;258.13868;-21.51261;,
 -4.90879;256.69695;25.96634;,
 42.90521;248.48599;-2.63220;,
 0.74807;122.79457;-75.59417;,
 56.27152;122.79457;-54.22408;,
 0.61412;105.68237;-2.63222;,
 85.42179;140.06673;-2.63221;,
 0.61412;105.68237;-2.63222;,
 56.27152;122.79457;48.95967;,
 0.61412;105.68237;-2.63222;,
 0.74806;122.79457;70.32974;,
 0.61412;105.68237;-2.63222;,
 -57.87983;140.06673;58.07372;,
 0.61412;105.68237;-2.63222;,
 -77.74512;122.65488;-1.13493;,
 0.61412;105.68237;-2.63222;,
 -53.81033;122.65488;-54.82693;,
 0.61412;105.68237;-2.63222;,
 0.74807;122.79457;-75.59417;,
 0.61412;105.68237;-2.63222;,
 -0.72184;258.13868;-21.51261;,
 39.40076;240.27505;-50.51677;,
 0.37181;227.98648;-80.73134;,
 39.40076;240.27505;45.25238;,
 42.90521;248.48599;-2.63220;,
 -4.90879;256.69695;25.96634;,
 0.37181;227.98648;75.46690;,
 -4.90879;256.69695;25.96634;,
 -38.65715;240.27505;45.25238;,
 -0.72184;258.13868;-21.51261;,
 -63.28386;227.98648;-2.63220;,
 -0.72184;258.13868;-21.51261;,
 -38.65715;240.27505;-50.51677;,
 -0.72184;258.13868;-21.51261;,
 0.37181;227.98648;-80.73134;,
 53.46637;201.20251;-67.77390;,
 0.37181;227.98648;-80.73134;,
 75.45892;201.20251;-2.63220;,
 53.46637;201.20251;62.50945;,
 -52.72272;201.20251;62.50945;,
 0.37181;227.98648;75.46690;,
 -52.72272;201.20251;-67.77389;,
 -63.28386;227.98648;-2.63220;,
 1.28951;172.02298;-99.88710;,
 1.28951;172.02298;94.62254;,
 53.46637;201.20251;62.50945;,
 -82.76910;174.00580;-5.21591;,
 -52.72272;201.20251;62.50945;,
 0.37181;227.98648;-80.73134;,
 1.28951;172.02298;-99.88710;,
 -52.72272;201.20251;-67.77389;,
 53.46637;201.20251;-67.77390;,
 65.39860;157.33887;-72.45218;,
 1.28951;172.02298;-99.88710;,
 75.45892;201.20251;-2.63220;,
 85.42179;140.06673;-2.63221;,
 65.39860;157.33887;67.18776;,
 1.28951;172.02298;94.62254;,
 -57.87983;140.06673;58.07372;,
 -60.98422;157.33887;-72.45218;,
 -82.76910;174.00580;-5.21591;,
 1.28951;172.02298;-99.88710;,
 56.27152;122.79457;-54.22408;,
 0.74807;122.79457;-75.59417;,
 56.27152;122.79457;48.95967;,
 0.74806;122.79457;70.32974;,
 -77.74512;122.65488;-1.13493;,
 -57.87983;140.06673;58.07372;,
 -53.81033;122.65488;-54.82693;,
 0.74807;122.79457;-75.59417;;
 
 104;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;3,2,18,19;,
 4;2,5,20,18;,
 4;5,7,21,20;,
 4;7,9,22,21;,
 4;9,11,23,22;,
 4;11,13,24,23;,
 4;13,15,25,24;,
 4;15,17,26,25;,
 4;19,18,27,28;,
 4;18,20,29,27;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;25,26,35,34;,
 4;28,27,36,37;,
 4;27,29,38,36;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;34,35,44,43;,
 4;37,36,45,46;,
 4;36,38,47,45;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;43,44,53,52;,
 3;54,46,45;,
 3;55,45,47;,
 3;56,47,48;,
 3;57,48,49;,
 3;58,49,50;,
 3;59,50,51;,
 3;60,51,52;,
 3;61,52,53;,
 3;62,63,64;,
 3;65,66,67;,
 3;66,68,69;,
 3;68,70,71;,
 3;70,72,73;,
 3;72,74,75;,
 3;74,76,77;,
 3;76,78,79;,
 3;78,80,81;,
 3;82,83,84;,
 3;64,83,82;,
 3;63,85,86;,
 3;87,88,85;,
 3;89,90,88;,
 3;91,92,90;,
 3;91,90,89;,
 3;93,94,92;,
 3;95,96,94;,
 3;83,97,98;,
 3;86,99,97;,
 3;86,97,83;,
 3;85,100,99;,
 3;85,99,86;,
 3;88,100,85;,
 3;90,101,102;,
 3;92,101,90;,
 3;94,103,104;,
 3;96,103,94;,
 3;97,105,98;,
 3;102,106,107;,
 3;101,106,102;,
 3;104,108,109;,
 3;103,108,104;,
 3;110,111,112;,
 3;113,114,115;,
 3;116,117,114;,
 3;116,114,113;,
 3;116,107,118;,
 3;116,118,117;,
 3;107,119,118;,
 3;109,120,119;,
 3;108,120,109;,
 3;112,121,122;,
 3;112,123,121;,
 3;114,124,125;,
 3;114,125,115;,
 3;117,124,114;,
 3;117,118,126;,
 3;118,119,127;,
 3;118,127,126;,
 3;120,127,119;,
 3;122,128,129;,
 3;122,121,130;,
 3;122,130,128;,
 3;121,123,131;,
 3;121,131,130;;
 
 MeshMaterialList {
  3;
  104;
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
  1;;
  Material {
   0.599200;0.464000;0.207200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game105\\Desktop\\フィールドアスレチック・クローン改\\リポジトリ改\\フィールドアスレチック\\稲井フォルダ\\Date\\TEXTURE\\Object\\Wood.jpg";
   }
  }
  Material {
   0.172800;0.668000;0.138400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game105\\Desktop\\フィールドアスレチック・クローン改\\リポジトリ改\\フィールドアスレチック\\稲井フォルダ\\Date\\TEXTURE\\Object\\tree.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  85;
  0.000107;-0.007021;-0.999975;,
  0.751773;-0.106232;-0.650808;,
  0.990979;-0.134012;0.001403;,
  0.751404;-0.097049;0.652667;,
  -0.000107;0.007021;0.999975;,
  -0.751774;0.106232;0.650808;,
  -0.990979;0.134014;-0.001405;,
  -0.751404;0.097049;-0.652667;,
  0.001040;0.057011;-0.998373;,
  0.755013;-0.051590;-0.653678;,
  0.993397;-0.114722;-0.001023;,
  0.751074;-0.119752;0.649267;,
  -0.000835;-0.051605;0.998667;,
  -0.756764;0.050851;0.651707;,
  -0.993700;0.112068;0.000977;,
  -0.752600;0.123310;-0.646829;,
  -0.023101;0.093707;-0.995332;,
  0.744547;0.062093;-0.664676;,
  0.999962;-0.005461;0.006850;,
  0.755141;-0.056056;0.653161;,
  -0.014258;-0.086273;0.996170;,
  -0.765365;-0.055982;0.641158;,
  -0.999970;0.006651;0.004079;,
  -0.758517;0.061185;-0.648774;,
  -0.021864;-0.004695;-0.999750;,
  0.733355;0.037712;-0.678799;,
  0.997573;0.068023;0.014838;,
  0.753188;0.066591;0.654426;,
  -0.051219;0.003118;0.998682;,
  -0.783937;-0.064292;0.617502;,
  -0.997886;-0.064728;0.005748;,
  -0.738768;-0.036072;-0.672994;,
  0.067628;0.022501;-0.997457;,
  0.762395;0.064725;-0.643867;,
  0.994627;0.103204;0.008063;,
  0.765626;0.132108;0.629575;,
  0.489900;0.133254;0.861534;,
  -0.780445;0.102891;0.616700;,
  -0.996716;0.076755;0.025825;,
  -0.704024;0.039010;-0.709104;,
  0.132786;0.122306;-0.983570;,
  0.781389;0.170607;-0.600270;,
  0.988036;0.154182;0.003495;,
  0.778636;0.161158;0.606427;,
  0.529441;0.159799;0.833160;,
  -0.751951;0.224993;0.619636;,
  -0.977378;0.206700;0.044813;,
  -0.683824;0.123469;-0.719125;,
  0.000000;-1.000000;-0.000000;,
  -0.578438;0.119397;0.806941;,
  -0.572006;0.223875;0.789106;,
  0.600166;0.799045;-0.036438;,
  0.001492;0.965977;0.258624;,
  -0.126911;0.978818;-0.160651;,
  0.480197;0.764328;-0.430363;,
  0.547130;0.727673;0.413693;,
  -0.002509;0.611242;0.791440;,
  -0.502969;0.792054;0.345938;,
  -0.793325;0.608797;-0.000946;,
  -0.494545;0.758964;-0.423555;,
  0.000373;0.626547;-0.779383;,
  0.700426;0.404765;-0.587851;,
  0.931492;0.362800;0.026422;,
  0.643503;0.370473;0.669816;,
  -0.721868;0.285352;0.630461;,
  -0.697411;0.350823;-0.624933;,
  -0.023221;-0.010301;0.999677;,
  -0.997047;0.065188;-0.040588;,
  -0.002266;0.026088;-0.999657;,
  0.728095;-0.135765;-0.671897;,
  0.677128;-0.735865;0.000000;,
  0.728095;-0.135765;0.671897;,
  -0.291622;-0.812099;0.505423;,
  -0.661387;-0.190376;-0.725482;,
  0.465061;-0.805563;-0.367132;,
  0.465061;-0.805563;0.367132;,
  0.010963;-0.738143;0.674555;,
  -0.207812;-0.970334;0.123554;,
  -0.221122;-0.882180;-0.415769;,
  -0.001344;-0.704714;-0.709491;,
  0.015261;-0.999420;0.030441;,
  0.986980;0.160841;0.000000;,
  -0.833221;-0.012001;0.552809;,
  -0.994258;-0.100250;-0.037439;,
  -0.923820;-0.214884;-0.316829;;
  104;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,0,8,15;,
  4;8,9,17,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,8,16,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,16,24,31;,
  4;24,25,33,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,49;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,24,32,39;,
  4;32,33,41,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;49,37,45,50;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,32,40,47;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;53,52,51;,
  3;79,74,80;,
  3;74,70,80;,
  3;70,75,80;,
  3;75,76,80;,
  3;76,72,80;,
  3;72,77,80;,
  3;77,78,80;,
  3;78,79,80;,
  3;53,54,60;,
  3;51,54,53;,
  3;52,55,51;,
  3;52,56,55;,
  3;52,57,56;,
  3;53,58,57;,
  3;53,57,52;,
  3;53,59,58;,
  3;53,60,59;,
  3;54,61,60;,
  3;51,62,61;,
  3;51,61,54;,
  3;55,63,62;,
  3;55,62,51;,
  3;56,63,55;,
  3;57,64,56;,
  3;58,64,57;,
  3;59,65,58;,
  3;60,65,59;,
  3;61,68,60;,
  3;56,66,63;,
  3;64,66,56;,
  3;58,67,64;,
  3;65,67,58;,
  3;60,68,65;,
  3;61,69,68;,
  3;62,81,69;,
  3;62,69,61;,
  3;62,63,71;,
  3;62,71,81;,
  3;63,66,71;,
  3;64,82,66;,
  3;67,82,64;,
  3;65,73,67;,
  3;65,68,73;,
  3;69,74,79;,
  3;69,79,68;,
  3;70,74,69;,
  3;70,71,75;,
  3;71,66,76;,
  3;71,76,75;,
  3;72,76,66;,
  3;67,83,82;,
  3;67,73,84;,
  3;67,84,83;,
  3;73,68,79;,
  3;73,79,78;;
 }
 MeshTextureCoords {
  132;
  0.000000;0.285710;,
  0.125000;0.285710;,
  0.125000;0.428570;,
  0.000000;0.428570;,
  0.250000;0.285710;,
  0.250000;0.428570;,
  0.375000;0.285710;,
  0.375000;0.428570;,
  0.500000;0.285710;,
  0.500000;0.428570;,
  0.625000;0.285710;,
  0.625000;0.428570;,
  0.750000;0.285710;,
  0.750000;0.428570;,
  0.875000;0.285710;,
  0.875000;0.428570;,
  1.000000;0.285710;,
  1.000000;0.428570;,
  0.125000;0.571430;,
  0.000000;0.571430;,
  0.250000;0.571430;,
  0.375000;0.571430;,
  0.500000;0.571430;,
  0.625000;0.571430;,
  0.750000;0.571430;,
  0.875000;0.571430;,
  1.000000;0.571430;,
  0.125000;0.714290;,
  0.000000;0.714290;,
  0.250000;0.714290;,
  0.375000;0.714290;,
  0.500000;0.714290;,
  0.625000;0.714290;,
  0.750000;0.714290;,
  0.875000;0.714290;,
  1.000000;0.714290;,
  0.125000;0.857140;,
  0.000000;0.857140;,
  0.250000;0.857140;,
  0.375000;0.857140;,
  0.500000;0.857140;,
  0.625000;0.857140;,
  0.750000;0.857140;,
  0.875000;0.857140;,
  1.000000;0.857140;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  1.000000;1.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.250000;0.125000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.062500;1.000000;,
  0.250000;0.875000;,
  0.187500;1.000000;,
  0.375000;0.875000;,
  0.312500;1.000000;,
  0.500000;0.875000;,
  0.437500;1.000000;,
  0.625000;0.875000;,
  0.562500;1.000000;,
  0.750000;0.875000;,
  0.687500;1.000000;,
  0.875000;0.875000;,
  0.812500;1.000000;,
  1.000000;0.875000;,
  0.937500;1.000000;,
  0.125000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.375000;0.250000;,
  0.250000;0.250000;,
  0.500000;0.125000;,
  0.500000;0.250000;,
  0.625000;0.125000;,
  0.625000;0.250000;,
  0.750000;0.125000;,
  0.750000;0.250000;,
  0.875000;0.125000;,
  0.875000;0.250000;,
  1.000000;0.125000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.625000;0.375000;,
  0.500000;0.375000;,
  0.875000;0.375000;,
  0.750000;0.375000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.375000;0.500000;,
  0.750000;0.500000;,
  0.625000;0.500000;,
  1.000000;0.375000;,
  1.000000;0.500000;,
  0.875000;0.500000;,
  0.125000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.500000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.875000;0.625000;,
  0.750000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  0.625000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;;
 }
}
