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
 304;
 34.33935;204.67552;-110.47649;,
 38.69353;193.25574;-108.62827;,
 -49.57141;193.25574;99.31101;,
 -53.92561;204.67552;97.46279;,
 49.20547;188.52552;-104.16614;,
 -39.05945;188.52552;103.77310;,
 59.71744;193.25574;-99.70403;,
 -28.54751;193.25574;108.23506;,
 64.07166;204.67552;-97.85581;,
 -24.19333;204.67552;110.08330;,
 59.71744;216.09529;-99.70403;,
 -28.54751;216.09529;108.23506;,
 49.20547;220.82552;-104.16614;,
 -39.05945;220.82552;103.77310;,
 38.69353;216.09529;-108.62827;,
 -49.57141;216.09529;99.31101;,
 34.33935;204.67552;-110.47649;,
 -53.92561;204.67552;97.46279;,
 49.20547;204.67552;-104.16614;,
 49.20547;204.67552;-104.16614;,
 49.20547;204.67552;-104.16614;,
 49.20547;204.67552;-104.16614;,
 49.20547;204.67552;-104.16614;,
 49.20547;204.67552;-104.16614;,
 49.20547;204.67552;-104.16614;,
 49.20547;204.67552;-104.16614;,
 -39.05945;204.67552;103.77310;,
 -39.05945;204.67552;103.77310;,
 -39.05945;204.67552;103.77310;,
 -39.05945;204.67552;103.77310;,
 -39.05945;204.67552;103.77310;,
 -39.05945;204.67552;103.77310;,
 -39.05945;204.67552;103.77310;,
 -39.05945;204.67552;103.77310;,
 48.42529;204.56778;-143.66121;,
 51.05128;193.14800;-137.74136;,
 38.70309;193.14800;-108.65069;,
 34.34886;204.56778;-110.49903;,
 60.05599;188.41778;-129.72847;,
 49.21504;188.41778;-104.18865;,
 72.07509;193.14800;-128.81724;,
 59.72700;193.14800;-99.72653;,
 78.15753;204.56778;-131.04048;,
 64.08120;204.56778;-97.87830;,
 75.60001;215.98755;-137.12151;,
 59.72700;215.98755;-99.72653;,
 65.08811;220.71778;-141.58364;,
 49.21504;220.71778;-104.18865;,
 54.57618;215.98755;-146.04568;,
 38.70309;215.98755;-108.65069;,
 48.42529;204.56778;-143.66121;,
 34.34886;204.56778;-110.49903;,
 63.29146;204.56778;-137.35088;,
 63.29146;204.56778;-137.35088;,
 63.29146;204.56778;-137.35088;,
 63.29146;204.56778;-137.35088;,
 63.29146;204.56778;-137.35088;,
 63.29146;204.56778;-137.35088;,
 63.29146;204.56778;-137.35088;,
 63.29146;204.56778;-137.35088;,
 -68.42307;204.84712;131.61636;,
 -65.60093;216.26690;137.07381;,
 -49.72766;216.26690;99.67911;,
 -54.08181;204.84712;97.83080;,
 -55.08892;220.99712;141.53589;,
 -39.21571;220.99712;104.14119;,
 -44.57696;216.26690;145.99785;,
 -28.70374;216.26690;108.60313;,
 -38.69069;204.84712;144.23682;,
 -24.34955;204.84712;110.45134;,
 -41.51415;193.42735;138.78238;,
 -28.70374;193.42735;108.60313;,
 -51.15184;188.69712;132.26077;,
 -39.21567;188.69712;104.14116;,
 -62.53807;193.42735;129.85833;,
 -49.72766;193.42735;99.67911;,
 -68.42307;204.84712;131.61636;,
 -54.08181;204.84712;97.83080;,
 -53.55689;204.84712;137.92659;,
 -53.55689;204.84712;137.92659;,
 -53.55689;204.84712;137.92659;,
 -53.55689;204.84712;137.92659;,
 -53.55689;204.84712;137.92659;,
 -53.55689;204.84712;137.92659;,
 -53.55689;204.84712;137.92659;,
 -53.55689;204.84712;137.92659;,
 24.58253;151.78886;-87.49077;,
 28.93671;140.36908;-85.64255;,
 -39.84695;140.36908;76.40166;,
 -44.20114;151.78886;74.55336;,
 39.44870;135.63886;-81.18050;,
 -29.33498;135.63886;80.86371;,
 49.96061;140.36908;-76.71833;,
 -18.82304;140.36908;85.32574;,
 54.31481;151.78886;-74.87019;,
 -14.46882;151.78886;87.17398;,
 49.96061;163.20863;-76.71833;,
 -18.82306;163.20863;85.32576;,
 39.44870;167.93886;-81.18050;,
 -29.33498;167.93886;80.86371;,
 28.93671;163.20863;-85.64255;,
 -39.84695;163.20863;76.40166;,
 24.58253;151.78886;-87.49077;,
 -44.20114;151.78886;74.55336;,
 39.44870;151.78886;-81.18050;,
 39.44870;151.78886;-81.18050;,
 39.44870;151.78886;-81.18050;,
 39.44870;151.78886;-81.18050;,
 39.44870;151.78886;-81.18050;,
 39.44870;151.78886;-81.18050;,
 39.44870;151.78886;-81.18050;,
 39.44870;151.78886;-81.18050;,
 -29.33498;151.78886;80.86371;,
 -29.33498;151.78886;80.86371;,
 -29.33498;151.78886;80.86371;,
 -29.33498;151.78886;80.86371;,
 -29.33498;151.78886;80.86371;,
 -29.33498;151.78886;80.86371;,
 -29.33498;151.78886;80.86371;,
 -29.33498;151.78886;80.86371;,
 35.55954;151.68112;-113.35112;,
 38.56692;140.26134;-108.32996;,
 28.94412;140.26134;-85.66001;,
 24.58995;151.68112;-87.50827;,
 47.90427;135.53112;-101.10066;,
 39.45609;135.53112;-81.19800;,
 59.59085;140.26134;-99.40576;,
 49.96806;140.26134;-76.73590;,
 65.29186;151.68112;-100.73042;,
 54.32228;151.68112;-74.88762;,
 62.33781;163.10089;-105.87722;,
 49.96806;163.10089;-76.73591;,
 51.82584;167.83112;-110.33933;,
 39.45609;167.83112;-81.19800;,
 41.31385;163.10089;-114.80142;,
 28.94412;163.10089;-85.66002;,
 35.55954;151.68112;-113.35112;,
 24.58995;151.68112;-87.50827;,
 50.42567;151.68112;-107.04072;,
 50.42567;151.68112;-107.04072;,
 50.42567;151.68112;-107.04072;,
 50.42567;151.68112;-107.04072;,
 50.42567;151.68112;-107.04072;,
 50.42567;151.68112;-107.04072;,
 50.42567;151.68112;-107.04072;,
 50.42567;151.68112;-107.04072;,
 -55.49873;151.96046;101.16883;,
 -52.33843;163.38024;105.82969;,
 -39.96869;163.38024;76.68843;,
 -44.32289;151.96046;74.84021;,
 -41.82648;168.11046;110.29177;,
 -29.45676;168.11046;81.15051;,
 -31.31454;163.38024;114.75376;,
 -18.94475;163.38024;85.61258;,
 -25.76648;151.96046;113.78921;,
 -14.59060;151.96046;87.46080;,
 -28.92773;140.54069;109.13089;,
 -18.94476;140.54069;85.61257;,
 -38.75839;135.81046;103.06380;,
 -29.45676;135.81046;81.15051;,
 -49.95164;140.54069;100.20684;,
 -39.96870;140.54069;76.68844;,
 -55.49873;151.96046;101.16883;,
 -44.32289;151.96046;74.84021;,
 -40.63258;151.96046;107.47918;,
 -40.63258;151.96046;107.47918;,
 -40.63258;151.96046;107.47918;,
 -40.63258;151.96046;107.47918;,
 -40.63258;151.96046;107.47918;,
 -40.63258;151.96046;107.47918;,
 -40.63258;151.96046;107.47918;,
 -40.63258;151.96046;107.47918;,
 9.39536;190.91800;-23.23981;,
 11.79835;190.91800;-28.90089;,
 11.79835;163.72801;-28.90089;,
 9.39536;163.72801;-23.23981;,
 11.79835;190.91800;-28.90089;,
 21.04943;190.91800;-24.97406;,
 21.04943;163.72801;-24.97406;,
 11.79835;163.72801;-28.90089;,
 21.04943;190.91800;-24.97406;,
 18.64643;190.91800;-19.31296;,
 18.64643;163.72801;-19.31296;,
 21.04943;163.72801;-24.97406;,
 18.64643;190.91800;-19.31296;,
 9.39536;190.91800;-23.23981;,
 9.39536;163.72801;-23.23981;,
 18.64643;163.72801;-19.31296;,
 11.79835;190.91800;-28.90089;,
 9.39536;190.91800;-23.23981;,
 9.39536;163.72801;-23.23981;,
 11.79835;163.72801;-28.90089;,
 -11.25320;190.91800;25.40517;,
 -8.85022;190.91800;19.74407;,
 -8.85022;163.72801;19.74407;,
 -11.25320;163.72801;25.40517;,
 -8.85022;190.91800;19.74407;,
 0.40086;190.91800;23.67092;,
 0.40086;163.72801;23.67092;,
 -8.85022;163.72801;19.74407;,
 0.40086;190.91800;23.67092;,
 -2.00213;190.91800;29.33201;,
 -2.00213;163.72801;29.33201;,
 0.40086;163.72801;23.67092;,
 -2.00213;190.91800;29.33201;,
 -11.25320;190.91800;25.40517;,
 -11.25320;163.72801;25.40517;,
 -2.00213;163.72801;29.33201;,
 -8.85022;190.91800;19.74407;,
 -11.25320;190.91800;25.40517;,
 -11.25320;163.72801;25.40517;,
 -8.85022;163.72801;19.74407;,
 11.55170;180.39800;-23.46656;,
 11.55170;174.24800;-23.46656;,
 -8.26560;174.24800;23.22010;,
 -8.26560;180.39800;23.22010;,
 11.55170;174.24800;-23.46656;,
 17.31162;174.24800;-21.02162;,
 -2.50569;174.24800;25.66503;,
 -8.26560;174.24800;23.22010;,
 17.31162;174.24800;-21.02162;,
 17.31162;180.39800;-21.02162;,
 -2.50569;180.39800;25.66503;,
 -2.50569;174.24800;25.66503;,
 17.31162;180.39800;-21.02162;,
 11.55170;180.39800;-23.46656;,
 -8.26560;180.39800;23.22010;,
 -2.50569;180.39800;25.66503;,
 11.55170;174.24800;-23.46656;,
 11.55170;180.39800;-23.46656;,
 -8.26560;180.39800;23.22010;,
 -8.26560;174.24800;23.22010;,
 3.69327;175.43817;-2.59352;,
 1.29027;175.43817;3.06758;,
 1.29027;195.39601;3.06758;,
 3.69327;195.39601;-2.59352;,
 1.29027;175.43817;3.06758;,
 5.35275;175.43817;4.79200;,
 5.35275;195.39601;4.79200;,
 1.29027;195.39601;3.06758;,
 5.35275;175.43817;4.79200;,
 7.75575;175.43817;-0.86910;,
 7.75575;195.39601;-0.86910;,
 5.35275;195.39601;4.79200;,
 7.75575;175.43817;-0.86910;,
 3.69327;175.43817;-2.59352;,
 3.69327;195.39601;-2.59352;,
 7.75575;195.39601;-0.86910;,
 1.29027;175.43817;3.06758;,
 3.69327;175.43817;-2.59352;,
 3.69327;195.39601;-2.59352;,
 1.29027;195.39601;3.06758;,
 21.65959;-0.51156;-80.60480;,
 21.55172;-0.51156;-68.24456;,
 21.55173;192.48419;-68.24456;,
 21.65962;192.48419;-80.60480;,
 30.21543;-0.51156;-59.42833;,
 30.21544;192.48419;-59.42834;,
 42.57565;-0.51156;-59.32044;,
 42.57566;192.48419;-59.32045;,
 51.39188;-0.51156;-67.98416;,
 51.39188;192.48419;-67.98417;,
 51.49976;-0.51156;-80.34434;,
 51.49977;192.48419;-80.34436;,
 42.83605;-0.51156;-89.16065;,
 42.83605;192.48419;-89.16067;,
 30.47585;-0.51156;-89.26849;,
 30.47585;192.48419;-89.26850;,
 21.65959;-0.51156;-80.60480;,
 21.65962;192.48419;-80.60480;,
 36.52575;192.48419;-74.29448;,
 36.52575;192.48419;-74.29448;,
 36.52575;192.48419;-74.29448;,
 36.52575;192.48419;-74.29448;,
 36.52575;192.48419;-74.29448;,
 36.52575;192.48419;-74.29448;,
 36.52575;192.48419;-74.29448;,
 36.52575;192.48419;-74.29448;,
 -40.61639;-0.51156;66.10825;,
 -40.72424;-0.51156;78.46845;,
 -40.72422;192.48419;78.46843;,
 -40.61638;192.48419;66.10825;,
 -32.06057;-0.51156;87.28474;,
 -32.06057;192.48419;87.28473;,
 -19.70036;-0.51156;87.39254;,
 -19.70036;192.48419;87.39252;,
 -10.88412;-0.51156;78.72884;,
 -10.88412;192.48419;78.72885;,
 -10.77623;-0.51156;66.36868;,
 -10.77624;192.48419;66.36867;,
 -19.43994;-0.51156;57.55242;,
 -19.43994;192.48419;57.55241;,
 -31.80012;-0.51156;57.44454;,
 -31.80013;192.48419;57.44453;,
 -40.61639;-0.51156;66.10825;,
 -40.61638;192.48419;66.10825;,
 -25.75024;192.48419;72.41859;,
 -25.75024;192.48419;72.41859;,
 -25.75024;192.48419;72.41859;,
 -25.75024;192.48419;72.41859;,
 -25.75024;192.48419;72.41859;,
 -25.75024;192.48419;72.41859;,
 -25.75024;192.48419;72.41859;,
 -25.75024;192.48419;72.41859;;
 
 168;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,1,0;,
 3;19,4,1;,
 3;20,6,4;,
 3;21,8,6;,
 3;22,10,8;,
 3;23,12,10;,
 3;24,14,12;,
 3;25,16,14;,
 3;26,3,2;,
 3;27,2,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;,
 4;34,35,36,37;,
 4;35,38,39,36;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 3;52,35,34;,
 3;53,38,35;,
 3;54,40,38;,
 3;55,42,40;,
 3;56,44,42;,
 3;57,46,44;,
 3;58,48,46;,
 3;59,50,48;,
 4;60,61,62,63;,
 4;61,64,65,62;,
 4;64,66,67,65;,
 4;66,68,69,67;,
 4;68,70,71,69;,
 4;70,72,73,71;,
 4;72,74,75,73;,
 4;74,76,77,75;,
 3;78,61,60;,
 3;79,64,61;,
 3;80,66,64;,
 3;81,68,66;,
 3;82,70,68;,
 3;83,72,70;,
 3;84,74,72;,
 3;85,76,74;,
 4;86,87,88,89;,
 4;87,90,91,88;,
 4;90,92,93,91;,
 4;92,94,95,93;,
 4;94,96,97,95;,
 4;96,98,99,97;,
 4;98,100,101,99;,
 4;100,102,103,101;,
 3;104,87,86;,
 3;105,90,87;,
 3;106,92,90;,
 3;107,94,92;,
 3;108,96,94;,
 3;109,98,96;,
 3;110,100,98;,
 3;111,102,100;,
 3;112,89,88;,
 3;113,88,91;,
 3;114,91,93;,
 3;115,93,95;,
 3;116,95,97;,
 3;117,97,99;,
 3;118,99,101;,
 3;119,101,103;,
 4;120,121,122,123;,
 4;121,124,125,122;,
 4;124,126,127,125;,
 4;126,128,129,127;,
 4;128,130,131,129;,
 4;130,132,133,131;,
 4;132,134,135,133;,
 4;134,136,137,135;,
 3;138,121,120;,
 3;139,124,121;,
 3;140,126,124;,
 3;141,128,126;,
 3;142,130,128;,
 3;143,132,130;,
 3;144,134,132;,
 3;145,136,134;,
 4;146,147,148,149;,
 4;147,150,151,148;,
 4;150,152,153,151;,
 4;152,154,155,153;,
 4;154,156,157,155;,
 4;156,158,159,157;,
 4;158,160,161,159;,
 4;160,162,163,161;,
 3;164,147,146;,
 3;165,150,147;,
 3;166,152,150;,
 3;167,154,152;,
 3;168,156,154;,
 3;169,158,156;,
 3;170,160,158;,
 3;171,162,160;,
 4;172,173,174,175;,
 4;176,177,178,179;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;184,177,188,189;,
 4;190,191,178,187;,
 4;192,193,194,195;,
 4;196,197,198,199;,
 4;200,201,202,203;,
 4;204,205,206,207;,
 4;204,197,208,209;,
 4;210,211,198,207;,
 4;212,213,214,215;,
 4;216,217,218,219;,
 4;220,221,222,223;,
 4;224,225,226,227;,
 4;224,217,228,229;,
 4;230,231,218,227;,
 4;232,233,234,235;,
 4;236,237,238,239;,
 4;240,241,242,243;,
 4;244,245,246,247;,
 4;244,237,248,249;,
 4;250,251,238,247;,
 4;252,253,254,255;,
 4;253,256,257,254;,
 4;256,258,259,257;,
 4;258,260,261,259;,
 4;260,262,263,261;,
 4;262,264,265,263;,
 4;264,266,267,265;,
 4;266,268,269,267;,
 3;270,255,254;,
 3;271,254,257;,
 3;272,257,259;,
 3;273,259,261;,
 3;274,261,263;,
 3;275,263,265;,
 3;276,265,267;,
 3;277,267,269;,
 4;278,279,280,281;,
 4;279,282,283,280;,
 4;282,284,285,283;,
 4;284,286,287,285;,
 4;286,288,289,287;,
 4;288,290,291,289;,
 4;290,292,293,291;,
 4;292,294,295,293;,
 3;296,281,280;,
 3;297,280,283;,
 3;298,283,285;,
 3;299,285,287;,
 3;300,287,289;,
 3;301,289,291;,
 3;302,291,293;,
 3;303,293,295;;
 
 MeshMaterialList {
  2;
  168;
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
   0.759216;0.065882;0.156863;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.138039;0.138039;0.138039;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  151;
  0.390734;0.000000;-0.920503;,
  -0.920505;0.000000;-0.390731;,
  -0.650896;-0.707106;-0.276289;,
  0.000000;-1.000000;0.000000;,
  0.650895;-0.707107;0.276289;,
  0.920505;0.000000;0.390731;,
  0.650895;0.707107;0.276289;,
  0.000000;1.000000;0.000000;,
  -0.650896;0.707106;-0.276289;,
  -0.390729;-0.000000;0.920506;,
  0.363455;-0.367092;-0.856238;,
  -0.920506;-0.000001;-0.390729;,
  -0.650894;-0.707108;-0.276287;,
  0.000000;-1.000000;-0.000000;,
  0.650896;-0.707107;0.276286;,
  0.920507;-0.000000;0.390727;,
  0.650896;0.707107;0.276286;,
  -0.000000;1.000000;-0.000000;,
  -0.650895;0.707108;-0.276286;,
  -0.371383;-0.310748;0.874935;,
  -0.920504;-0.000001;-0.390734;,
  -0.650894;0.707107;-0.276291;,
  0.000001;1.000000;0.000000;,
  0.650895;0.707106;0.276290;,
  0.920504;0.000000;0.390733;,
  0.650895;-0.707106;0.276290;,
  0.000001;-1.000000;0.000000;,
  -0.650894;-0.707107;-0.276291;,
  0.390733;0.000000;-0.920504;,
  -0.920505;0.000000;-0.390731;,
  -0.650895;-0.707107;-0.276289;,
  0.000000;-1.000000;0.000000;,
  0.650896;-0.707106;0.276289;,
  0.920505;0.000000;0.390731;,
  0.650895;0.707106;0.276289;,
  0.000000;1.000000;0.000000;,
  -0.650895;0.707107;-0.276289;,
  -0.390731;-0.000000;0.920505;,
  0.373407;-0.294487;-0.879685;,
  -0.920505;-0.000000;-0.390730;,
  -0.650896;-0.707107;-0.276288;,
  -0.000000;-1.000000;-0.000000;,
  0.650895;-0.707108;0.276288;,
  0.920505;0.000000;0.390731;,
  0.650894;0.707108;0.276288;,
  -0.000000;1.000000;0.000000;,
  -0.650896;0.707106;-0.276288;,
  -0.378615;-0.247056;0.891972;,
  -0.920505;-0.000001;-0.390731;,
  -0.650895;0.707106;-0.276289;,
  -0.000000;1.000000;0.000000;,
  0.650896;0.707105;0.276291;,
  0.920504;-0.000000;0.390734;,
  0.650896;-0.707105;0.276291;,
  -0.000001;-1.000000;-0.000000;,
  -0.650895;-0.707107;-0.276288;,
  -0.920505;0.000000;-0.390732;,
  0.390730;0.000000;-0.920505;,
  0.920504;0.000000;0.390732;,
  -0.920506;0.000000;-0.390729;,
  0.390731;0.000000;-0.920505;,
  0.920505;0.000000;0.390731;,
  -0.920505;0.000000;-0.390731;,
  0.000000;-1.000000;-0.000000;,
  0.920505;0.000000;0.390731;,
  -0.920505;0.000000;-0.390731;,
  -0.390731;0.000000;0.920505;,
  0.920505;0.000000;0.390732;,
  -0.920505;0.000000;-0.390732;,
  -0.927184;0.000000;0.374607;,
  -0.390731;0.000000;0.920505;,
  0.374607;0.000000;0.927184;,
  0.920505;-0.000000;0.390731;,
  0.927185;-0.000000;-0.374604;,
  0.390731;-0.000000;-0.920505;,
  -0.374607;-0.000000;-0.927184;,
  0.000000;1.000000;0.000000;,
  -0.920505;0.000000;-0.390730;,
  -0.927185;0.000000;0.374605;,
  -0.390731;0.000000;0.920505;,
  0.374609;0.000000;0.927183;,
  0.920504;-0.000000;0.390732;,
  0.927184;-0.000000;-0.374606;,
  0.390732;-0.000000;-0.920505;,
  -0.374606;-0.000000;-0.927184;,
  0.390736;0.000002;-0.920503;,
  0.390734;0.000000;-0.920504;,
  0.390736;0.000000;-0.920503;,
  0.390733;-0.000001;-0.920504;,
  0.390732;0.000000;-0.920505;,
  0.390733;0.000001;-0.920504;,
  0.390736;-0.000002;-0.920503;,
  -0.390731;0.000000;0.920505;,
  -0.390732;-0.000001;0.920504;,
  -0.390729;0.000000;0.920506;,
  -0.390725;-0.000001;0.920507;,
  -0.390726;0.000000;0.920507;,
  -0.390725;0.000001;0.920507;,
  -0.390732;0.000001;0.920504;,
  0.407175;-0.408494;-0.816910;,
  0.363412;-0.367356;-0.856143;,
  0.347693;-0.456256;-0.819109;,
  0.304793;-0.408493;-0.860369;,
  0.363418;-0.367355;-0.856141;,
  0.317003;-0.323770;-0.891450;,
  0.375798;-0.273840;-0.885318;,
  0.421053;-0.323769;-0.847283;,
  -0.329703;-0.280407;0.901481;,
  -0.369567;-0.324618;0.870657;,
  -0.379697;-0.235932;0.894520;,
  -0.419432;-0.280409;0.863393;,
  -0.369567;-0.324618;0.870657;,
  -0.383705;-0.340304;0.858465;,
  -0.365110;-0.356135;0.860153;,
  -0.350977;-0.340306;0.872357;,
  0.390729;0.000000;-0.920506;,
  0.390729;0.000000;-0.920506;,
  0.390735;0.000000;-0.920503;,
  0.390737;-0.000004;-0.920503;,
  0.390732;0.000000;-0.920504;,
  0.390737;0.000004;-0.920503;,
  0.390729;-0.000000;-0.920506;,
  -0.390733;0.000000;0.920504;,
  -0.390732;0.000001;0.920505;,
  -0.390730;0.000000;0.920505;,
  -0.390729;0.000000;0.920506;,
  -0.390729;-0.000001;0.920506;,
  -0.390730;-0.000001;0.920505;,
  -0.390731;0.000000;0.920505;,
  -0.390732;-0.000001;0.920505;,
  0.410119;-0.329893;-0.850278;,
  0.373446;-0.294183;-0.879770;,
  0.362841;-0.371046;-0.854793;,
  0.326751;-0.329893;-0.885666;,
  0.373440;-0.294184;-0.879772;,
  0.335881;-0.258069;-0.905861;,
  0.381456;-0.216619;-0.898648;,
  0.418303;-0.258069;-0.870875;,
  -0.345281;-0.222227;0.911809;,
  -0.377466;-0.258370;0.889249;,
  -0.383919;-0.185897;0.904460;,
  -0.416042;-0.222231;0.881772;,
  -0.377451;-0.258371;0.889255;,
  -0.389093;-0.271485;0.880286;,
  -0.374557;-0.284716;0.882408;,
  -0.362929;-0.271488;0.891390;,
  -0.390731;0.000000;0.920505;,
  -0.390731;0.000000;0.920505;,
  0.390731;0.000000;-0.920505;,
  -0.390730;0.000000;0.920505;,
  0.390731;0.000000;-0.920505;;
  168;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,85,86;,
  3;0,87,85;,
  3;0,88,87;,
  3;0,89,88;,
  3;0,90,89;,
  3;0,87,90;,
  3;0,91,87;,
  3;0,86,91;,
  3;9,92,93;,
  3;9,93,94;,
  3;9,94,95;,
  3;9,95,96;,
  3;9,96,97;,
  3;9,97,94;,
  3;9,94,98;,
  3;9,98,92;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,11,11,18;,
  3;10,99,100;,
  3;10,101,99;,
  3;10,102,101;,
  3;10,103,102;,
  3;10,104,103;,
  3;10,105,104;,
  3;10,106,105;,
  3;10,100,106;,
  4;20,21,21,20;,
  4;21,22,22,21;,
  4;22,23,23,22;,
  4;23,24,24,23;,
  4;24,25,25,24;,
  4;25,26,26,25;,
  4;26,27,27,26;,
  4;27,20,20,27;,
  3;19,107,108;,
  3;19,109,107;,
  3;19,110,109;,
  3;19,111,110;,
  3;19,112,111;,
  3;19,113,112;,
  3;19,114,113;,
  3;19,108,114;,
  4;29,30,30,29;,
  4;30,31,31,30;,
  4;31,32,32,31;,
  4;32,33,33,32;,
  4;33,34,34,33;,
  4;34,35,35,34;,
  4;35,36,36,35;,
  4;36,29,29,36;,
  3;28,115,116;,
  3;28,117,115;,
  3;28,118,117;,
  3;28,119,118;,
  3;28,120,119;,
  3;28,117,120;,
  3;28,121,117;,
  3;28,116,121;,
  3;37,122,123;,
  3;37,123,124;,
  3;37,124,125;,
  3;37,125,126;,
  3;37,126,127;,
  3;37,127,128;,
  3;37,128,129;,
  3;37,129,122;,
  4;39,40,40,39;,
  4;40,41,41,40;,
  4;41,42,42,41;,
  4;42,43,43,42;,
  4;43,44,44,43;,
  4;44,45,45,44;,
  4;45,46,46,45;,
  4;46,39,39,46;,
  3;38,130,131;,
  3;38,132,130;,
  3;38,133,132;,
  3;38,134,133;,
  3;38,135,134;,
  3;38,136,135;,
  3;38,137,136;,
  3;38,131,137;,
  4;48,49,49,48;,
  4;49,50,50,49;,
  4;50,51,51,50;,
  4;51,52,52,51;,
  4;52,53,53,52;,
  4;53,54,54,53;,
  4;54,55,55,54;,
  4;55,48,48,55;,
  3;47,138,139;,
  3;47,140,138;,
  3;47,141,140;,
  3;47,142,141;,
  3;47,143,142;,
  3;47,144,143;,
  3;47,145,144;,
  3;47,139,145;,
  4;56,56,56,56;,
  4;57,57,57,57;,
  4;58,58,58,58;,
  4;146,146,146,146;,
  4;76,76,76,76;,
  4;63,63,63,63;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;61,61,61,61;,
  4;147,147,147,147;,
  4;76,76,76,76;,
  4;63,63,63,63;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;76,76,76,76;,
  4;148,148,148,148;,
  4;149,149,149,149;,
  4;65,65,65,65;,
  4;66,66,66,66;,
  4;67,67,67,67;,
  4;150,150,150,150;,
  4;63,63,63,63;,
  4;76,76,76,76;,
  4;68,69,69,68;,
  4;69,70,70,69;,
  4;70,71,71,70;,
  4;71,72,72,71;,
  4;72,73,73,72;,
  4;73,74,74,73;,
  4;74,75,75,74;,
  4;75,68,68,75;,
  3;76,76,76;,
  3;76,76,76;,
  3;76,76,76;,
  3;76,76,76;,
  3;76,76,76;,
  3;76,76,76;,
  3;76,76,76;,
  3;76,76,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;79,80,80,79;,
  4;80,81,81,80;,
  4;81,82,82,81;,
  4;82,83,83,82;,
  4;83,84,84,83;,
  4;84,77,77,84;,
  3;76,76,76;,
  3;76,76,76;,
  3;76,76,76;,
  3;76,76,76;,
  3;76,76,76;,
  3;76,76,76;,
  3;76,76,76;,
  3;76,76,76;;
 }
 MeshTextureCoords {
  304;
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
  0.937500;1.000000;,
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
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
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
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
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
  0.937500;1.000000;,
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
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
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
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
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
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
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
