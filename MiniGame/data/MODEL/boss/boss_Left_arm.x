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
 219;
 -8.06456;-0.23113;-10.35599;,
 -8.06456;-3.94514;-9.52328;,
 -11.40321;-4.94940;-10.09323;,
 -11.40321;-0.20720;-10.97291;,
 -8.06456;-7.09374;-7.15194;,
 -11.40321;-8.96964;-7.58817;,
 -8.06456;-9.19754;-3.60298;,
 -11.40321;-10.83376;-3.83906;,
 -8.06456;-9.93629;0.58330;,
 -11.40321;-11.37180;0.58330;,
 -8.06456;-9.19754;4.76959;,
 -11.40321;-10.83376;5.00568;,
 -8.06456;-7.09374;8.31855;,
 -11.40321;-8.96964;8.75479;,
 -8.06456;-3.94514;10.68989;,
 -11.40321;-4.94940;11.25985;,
 -8.06456;-0.23113;11.52260;,
 -11.40321;-0.20720;12.13953;,
 -8.06456;3.48289;10.68989;,
 -11.40321;4.53499;11.25985;,
 -8.06456;6.63149;8.31855;,
 -11.40321;8.55521;8.75479;,
 -8.06456;8.73528;4.76959;,
 -11.40321;11.24147;5.00568;,
 -8.06456;9.47404;0.58330;,
 -11.40321;12.18480;0.58330;,
 -8.06456;8.73528;-3.60298;,
 -11.40321;11.24147;-3.83906;,
 -8.06456;6.63149;-7.15194;,
 -11.40321;8.55521;-7.58817;,
 -8.06456;3.48288;-9.52328;,
 -11.40321;4.53498;-10.09323;,
 -8.06456;-0.23113;-10.35599;,
 -11.40321;-0.20720;-10.97291;,
 -14.74185;-5.10360;-9.07965;,
 -14.74185;-0.06889;-9.87580;,
 -14.74185;-9.37179;-6.81240;,
 -14.74185;-11.40156;-3.41922;,
 -14.74185;-11.99776;0.58330;,
 -14.74185;-11.40156;4.58583;,
 -14.74185;-9.37179;7.97901;,
 -14.74185;-5.10360;10.24626;,
 -14.74185;-0.06889;11.04241;,
 -14.74185;4.96580;10.24626;,
 -14.74185;9.23397;7.97901;,
 -14.74185;12.08596;4.58583;,
 -14.74185;13.08741;0.58330;,
 -14.74185;12.08596;-3.41922;,
 -14.74185;9.23397;-6.81240;,
 -14.74185;4.96575;-9.07965;,
 -14.74185;-0.06889;-9.87580;,
 -18.08051;-5.10360;-9.67564;,
 -18.08051;-0.06889;-10.52089;,
 -18.08051;-9.37179;-7.26855;,
 -18.08051;-11.40156;-3.66609;,
 -18.08051;-11.99776;0.58330;,
 -18.08051;-11.40156;4.83270;,
 -18.08051;-9.37179;8.43516;,
 -18.08051;-5.10360;10.84225;,
 -18.08051;-0.06889;11.68751;,
 -18.08051;4.96580;10.84225;,
 -18.08051;9.23397;8.43516;,
 -18.08051;12.08596;4.83270;,
 -18.08051;13.08741;0.58330;,
 -18.08051;12.08596;-3.66609;,
 -18.08051;9.23397;-7.26855;,
 -18.08051;4.96575;-9.67564;,
 -18.08051;-0.06889;-10.52089;,
 -21.41917;-4.92583;-9.67564;,
 -21.41917;-0.20720;-10.52089;,
 -21.41917;-8.92606;-7.26855;,
 -21.41917;-10.77678;-3.66609;,
 -21.41917;-11.31013;0.58330;,
 -21.41917;-10.77678;4.83270;,
 -21.41917;-8.92606;8.43516;,
 -21.41917;-4.92583;10.84225;,
 -21.41917;-0.20720;11.68751;,
 -21.41917;4.51141;10.84225;,
 -21.41917;8.51164;8.43516;,
 -21.41917;11.18458;4.83270;,
 -21.41917;12.12313;0.58330;,
 -21.41917;11.18458;-3.66609;,
 -21.41917;8.51164;-7.26855;,
 -21.41917;4.51138;-9.67564;,
 -21.41917;-0.20720;-10.52089;,
 -24.75781;-4.62281;-9.67564;,
 -24.75781;-0.20046;-10.52089;,
 -24.75781;-8.37197;-7.26855;,
 -24.75781;-10.05489;-3.66609;,
 -24.75781;-10.52928;0.58330;,
 -24.75781;-10.05489;4.83270;,
 -24.75781;-8.37197;8.43516;,
 -24.75781;-4.62281;10.84225;,
 -24.75781;-0.20046;11.68751;,
 -24.75781;4.22191;10.84225;,
 -24.75781;7.97101;8.43516;,
 -24.75781;10.47607;4.83270;,
 -24.75781;11.35577;0.58330;,
 -24.75781;10.47607;-3.66609;,
 -24.75781;7.97101;-7.26855;,
 -24.75781;4.22187;-9.67564;,
 -24.75781;-0.20046;-10.52089;,
 -28.09646;-4.36592;-9.07965;,
 -28.09646;-0.20046;-9.87580;,
 -28.09646;-7.89722;-6.81240;,
 -28.09646;-9.43461;-3.41922;,
 -28.09646;-9.85790;0.58330;,
 -28.09646;-9.43461;4.58583;,
 -28.09646;-7.89722;7.97901;,
 -28.09646;-4.36592;10.24626;,
 -28.09646;-0.20046;11.04241;,
 -28.09646;3.96494;10.24626;,
 -28.09646;7.49628;7.97901;,
 -28.09646;9.85587;4.58583;,
 -28.09646;10.68438;0.58330;,
 -28.09646;9.85587;-3.41922;,
 -28.09646;7.49628;-6.81240;,
 -28.09646;3.96494;-9.07965;,
 -28.09646;-0.20046;-9.87580;,
 -31.43510;-4.21375;-9.57380;,
 -31.43510;-0.23113;-10.41068;,
 -31.43510;-7.59003;-7.19062;,
 -31.43510;-9.02388;-3.62390;,
 -31.43510;-9.41082;0.58330;,
 -31.43510;-9.02388;4.79052;,
 -31.43510;-7.59003;8.35723;,
 -31.43510;-4.21375;10.74041;,
 -31.43510;-0.23113;11.57729;,
 -31.43510;3.75151;10.74041;,
 -31.43510;7.12780;8.35723;,
 -31.43510;9.38372;4.79052;,
 -31.43510;10.17600;0.58330;,
 -31.43510;9.38372;-3.62390;,
 -31.43510;7.12780;-7.19062;,
 -31.43510;3.75148;-9.57380;,
 -31.43510;-0.23113;-10.41068;,
 -34.77376;-3.96370;-9.52328;,
 -34.77376;-0.23113;-10.35599;,
 -34.77376;-7.12804;-7.15194;,
 -34.77376;-8.42025;-3.60298;,
 -34.77376;-8.75743;0.58330;,
 -34.77376;-8.42025;4.76959;,
 -34.77376;-7.12804;8.31855;,
 -34.77376;-3.96370;10.68989;,
 -34.77376;-0.23113;11.52260;,
 -34.77376;3.50146;10.68989;,
 -34.77376;6.66578;8.31855;,
 -34.77376;8.78015;4.76959;,
 -34.77376;9.52255;0.58330;,
 -34.77376;8.78015;-3.60298;,
 -34.77376;6.66578;-7.15194;,
 -34.77376;3.50146;-9.52328;,
 -34.77376;-0.23113;-10.35599;,
 -2.56977;-0.23113;-6.97980;,
 -2.56977;-3.18372;-6.40409;,
 3.71327;-0.23113;0.58330;,
 -2.56977;-5.68682;-4.76460;,
 3.71327;-0.23113;0.58330;,
 -2.56977;-7.35933;-2.31099;,
 3.71327;-0.23113;0.58330;,
 -2.56977;-7.94662;0.58330;,
 3.71327;-0.23113;0.58330;,
 -2.56977;-7.35933;3.47760;,
 3.71327;-0.23113;0.58330;,
 -2.56977;-5.68682;5.93122;,
 3.71327;-0.23113;0.58330;,
 -2.56977;-3.18372;7.57070;,
 3.71327;-0.23113;0.58330;,
 -2.56977;-0.23113;8.14641;,
 3.71327;-0.23113;0.58330;,
 -2.56977;2.72147;7.57070;,
 3.71327;-0.23113;0.58330;,
 -2.56977;5.22457;5.93122;,
 3.71327;-0.23113;0.58330;,
 -2.56977;6.89706;3.47760;,
 3.71327;-0.23113;0.58330;,
 -2.56977;7.48437;0.58330;,
 3.71327;-0.23113;0.58330;,
 -2.56977;6.89706;-2.31099;,
 3.71327;-0.23113;0.58330;,
 -2.56977;5.22457;-4.76460;,
 3.71327;-0.23113;0.58330;,
 -2.56977;2.72145;-6.40409;,
 3.71327;-0.23113;0.58330;,
 -2.56977;-0.23113;-6.97980;,
 3.71327;-0.23113;0.58330;,
 -40.61307;-3.38150;-6.79815;,
 -40.61307;-0.23113;-7.40632;,
 -47.84203;-0.23113;0.58330;,
 -40.61307;-6.05226;-5.06619;,
 -47.84203;-0.23113;0.58330;,
 -40.61307;-7.83682;-2.47421;,
 -47.84203;-0.23113;0.58330;,
 -40.61307;-8.05817;0.58330;,
 -47.84203;-0.23113;0.58330;,
 -40.61307;-7.83682;3.64083;,
 -47.84203;-0.23113;0.58330;,
 -40.61307;-6.05226;6.23281;,
 -47.84203;-0.23113;0.58330;,
 -40.61307;-3.38150;7.96476;,
 -47.84203;-0.23113;0.58330;,
 -40.61307;-0.23113;8.57294;,
 -47.84203;-0.23113;0.58330;,
 -40.61307;2.91922;7.96476;,
 -47.84203;-0.23113;0.58330;,
 -40.61307;5.59005;6.23281;,
 -47.84203;-0.23113;0.58330;,
 -40.61307;7.37452;3.64083;,
 -47.84203;-0.23113;0.58330;,
 -40.61307;8.00120;0.58330;,
 -47.84203;-0.23113;0.58330;,
 -40.61307;7.37452;-2.47421;,
 -47.84203;-0.23113;0.58330;,
 -40.61307;5.59005;-5.06619;,
 -47.84203;-0.23113;0.58330;,
 -40.61307;2.91922;-6.79815;,
 -47.84203;-0.23113;0.58330;,
 -40.61307;-0.23113;-7.40632;,
 -47.84203;-0.23113;0.58330;;
 
 192;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;3,2,34,35;,
 4;2,5,36,34;,
 4;5,7,37,36;,
 4;7,9,38,37;,
 4;9,11,39,38;,
 4;11,13,40,39;,
 4;13,15,41,40;,
 4;15,17,42,41;,
 4;17,19,43,42;,
 4;19,21,44,43;,
 4;21,23,45,44;,
 4;23,25,46,45;,
 4;25,27,47,46;,
 4;27,29,48,47;,
 4;29,31,49,48;,
 4;31,33,50,49;,
 4;35,34,51,52;,
 4;34,36,53,51;,
 4;36,37,54,53;,
 4;37,38,55,54;,
 4;38,39,56,55;,
 4;39,40,57,56;,
 4;40,41,58,57;,
 4;41,42,59,58;,
 4;42,43,60,59;,
 4;43,44,61,60;,
 4;44,45,62,61;,
 4;45,46,63,62;,
 4;46,47,64,63;,
 4;47,48,65,64;,
 4;48,49,66,65;,
 4;49,50,67,66;,
 4;52,51,68,69;,
 4;51,53,70,68;,
 4;53,54,71,70;,
 4;54,55,72,71;,
 4;55,56,73,72;,
 4;56,57,74,73;,
 4;57,58,75,74;,
 4;58,59,76,75;,
 4;59,60,77,76;,
 4;60,61,78,77;,
 4;61,62,79,78;,
 4;62,63,80,79;,
 4;63,64,81,80;,
 4;64,65,82,81;,
 4;65,66,83,82;,
 4;66,67,84,83;,
 4;69,68,85,86;,
 4;68,70,87,85;,
 4;70,71,88,87;,
 4;71,72,89,88;,
 4;72,73,90,89;,
 4;73,74,91,90;,
 4;74,75,92,91;,
 4;75,76,93,92;,
 4;76,77,94,93;,
 4;77,78,95,94;,
 4;78,79,96,95;,
 4;79,80,97,96;,
 4;80,81,98,97;,
 4;81,82,99,98;,
 4;82,83,100,99;,
 4;83,84,101,100;,
 4;86,85,102,103;,
 4;85,87,104,102;,
 4;87,88,105,104;,
 4;88,89,106,105;,
 4;89,90,107,106;,
 4;90,91,108,107;,
 4;91,92,109,108;,
 4;92,93,110,109;,
 4;93,94,111,110;,
 4;94,95,112,111;,
 4;95,96,113,112;,
 4;96,97,114,113;,
 4;97,98,115,114;,
 4;98,99,116,115;,
 4;99,100,117,116;,
 4;100,101,118,117;,
 4;103,102,119,120;,
 4;102,104,121,119;,
 4;104,105,122,121;,
 4;105,106,123,122;,
 4;106,107,124,123;,
 4;107,108,125,124;,
 4;108,109,126,125;,
 4;109,110,127,126;,
 4;110,111,128,127;,
 4;111,112,129,128;,
 4;112,113,130,129;,
 4;113,114,131,130;,
 4;114,115,132,131;,
 4;115,116,133,132;,
 4;116,117,134,133;,
 4;117,118,135,134;,
 4;120,119,136,137;,
 4;119,121,138,136;,
 4;121,122,139,138;,
 4;122,123,140,139;,
 4;123,124,141,140;,
 4;124,125,142,141;,
 4;125,126,143,142;,
 4;126,127,144,143;,
 4;127,128,145,144;,
 4;128,129,146,145;,
 4;129,130,147,146;,
 4;130,131,148,147;,
 4;131,132,149,148;,
 4;132,133,150,149;,
 4;133,134,151,150;,
 4;134,135,152,151;,
 4;153,154,1,0;,
 3;155,154,153;,
 4;154,156,4,1;,
 3;157,156,154;,
 4;156,158,6,4;,
 3;159,158,156;,
 4;158,160,8,6;,
 3;161,160,158;,
 4;160,162,10,8;,
 3;163,162,160;,
 4;162,164,12,10;,
 3;165,164,162;,
 4;164,166,14,12;,
 3;167,166,164;,
 4;166,168,16,14;,
 3;169,168,166;,
 4;168,170,18,16;,
 3;171,170,168;,
 4;170,172,20,18;,
 3;173,172,170;,
 4;172,174,22,20;,
 3;175,174,172;,
 4;174,176,24,22;,
 3;177,176,174;,
 4;176,178,26,24;,
 3;179,178,176;,
 4;178,180,28,26;,
 3;181,180,178;,
 4;180,182,30,28;,
 3;183,182,180;,
 4;182,184,32,30;,
 3;185,184,182;,
 4;186,187,137,136;,
 3;188,187,186;,
 4;189,186,136,138;,
 3;190,186,189;,
 4;191,189,138,139;,
 3;192,189,191;,
 4;193,191,139,140;,
 3;194,191,193;,
 4;195,193,140,141;,
 3;196,193,195;,
 4;197,195,141,142;,
 3;198,195,197;,
 4;199,197,142,143;,
 3;200,197,199;,
 4;201,199,143,144;,
 3;202,199,201;,
 4;203,201,144,145;,
 3;204,201,203;,
 4;205,203,145,146;,
 3;206,203,205;,
 4;207,205,146,147;,
 3;208,205,207;,
 4;209,207,147,148;,
 3;210,207,209;,
 4;211,209,148,149;,
 3;212,209,211;,
 4;213,211,149,150;,
 3;214,211,213;,
 4;215,213,150,151;,
 3;216,213,215;,
 4;217,215,151,152;,
 3;218,215,217;;
 
 MeshMaterialList {
  5;
  192;
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
  1,
  1,
  1;;
  Material {
   0.228800;0.295200;0.800000;1.000000;;
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
   0.323200;0.323200;0.323200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.780800;0.800000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.496000;0.031200;0.024800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.372000;0.023400;0.018600;;
  }
 }
 MeshNormals {
  178;
  0.365266;-0.000028;-0.930903;,
  0.386967;-0.363190;-0.847555;,
  0.420776;-0.664190;-0.617900;,
  0.407441;-0.858358;-0.311789;,
  0.384633;-0.923069;-0.000000;,
  0.407442;-0.858358;0.311789;,
  0.420776;-0.664189;0.617899;,
  0.386968;-0.363190;0.847555;,
  0.365268;-0.000028;0.930903;,
  0.389292;0.362718;0.846692;,
  0.437736;0.645105;0.626281;,
  0.475810;0.815740;0.328897;,
  0.488649;0.872480;-0.000000;,
  0.475810;0.815740;-0.328898;,
  0.437735;0.645104;-0.626282;,
  0.389291;0.362718;-0.846693;,
  -0.048937;0.000139;-0.998802;,
  0.013882;-0.364506;-0.931097;,
  0.173690;-0.716307;-0.675823;,
  0.279162;-0.911602;-0.301745;,
  0.297996;-0.954567;-0.000000;,
  0.279162;-0.911602;0.301745;,
  0.173690;-0.716307;0.675823;,
  0.013882;-0.364506;0.931097;,
  -0.048937;0.000139;0.998802;,
  0.029973;0.364344;0.930782;,
  0.208316;0.667487;0.714889;,
  0.376059;0.845324;0.379482;,
  0.440736;0.897637;-0.000000;,
  0.376059;0.845324;-0.379483;,
  0.208316;0.667486;-0.714890;,
  0.029971;0.364343;-0.930782;,
  -0.057868;0.000167;-0.998324;,
  -0.043481;-0.333392;-0.941785;,
  0.011674;-0.707760;-0.706357;,
  0.068194;-0.944915;-0.320132;,
  0.087256;-0.996186;-0.000000;,
  0.068193;-0.944915;0.320132;,
  0.011673;-0.707760;0.706357;,
  -0.043482;-0.333393;0.941785;,
  -0.057868;0.000167;0.998324;,
  -0.029985;0.333720;0.942195;,
  0.032288;0.648371;0.760640;,
  0.097795;0.894413;0.436419;,
  0.125833;0.992051;-0.000000;,
  0.097796;0.894413;-0.436419;,
  0.032289;0.648369;-0.760641;,
  -0.029985;0.333718;-0.942196;,
  0.087891;-0.000004;-0.996130;,
  0.068825;-0.333417;-0.940264;,
  0.000849;-0.708581;-0.705629;,
  -0.069831;-0.945559;-0.317872;,
  -0.094385;-0.995536;-0.000000;,
  -0.069831;-0.945559;0.317872;,
  0.000849;-0.708581;0.705629;,
  0.068825;-0.333417;0.940264;,
  0.087892;-0.000004;0.996130;,
  0.054745;0.333592;0.941127;,
  -0.019081;0.649867;0.759808;,
  -0.097571;0.895632;0.433962;,
  -0.131821;0.991274;-0.000000;,
  -0.097571;0.895632;-0.433963;,
  -0.019080;0.649866;-0.759810;,
  0.054745;0.333590;-0.941127;,
  -0.007955;-0.000004;-0.999968;,
  -0.031163;-0.351645;-0.935615;,
  -0.109765;-0.725000;-0.679946;,
  -0.182189;-0.939128;-0.291283;,
  -0.206218;-0.978506;-0.000000;,
  -0.182189;-0.939128;0.291282;,
  -0.109765;-0.725000;0.679946;,
  -0.031163;-0.351646;0.935614;,
  -0.007955;-0.000004;0.999968;,
  -0.044578;0.351370;0.935175;,
  -0.125515;0.666027;0.735292;,
  -0.207872;0.889317;0.407314;,
  -0.242490;0.970154;-0.000000;,
  -0.207872;0.889317;-0.407314;,
  -0.125515;0.666026;-0.735293;,
  -0.044577;0.351368;-0.935175;,
  -0.099227;0.000001;-0.995065;,
  -0.114897;-0.363439;-0.924506;,
  -0.159874;-0.737991;-0.655598;,
  -0.194931;-0.942958;-0.269875;,
  -0.206692;-0.978406;-0.000000;,
  -0.194931;-0.942958;0.269875;,
  -0.159874;-0.737991;0.655598;,
  -0.114897;-0.363440;0.924505;,
  -0.099228;0.000001;0.995065;,
  -0.114175;0.363477;0.924580;,
  -0.151656;0.680220;0.717148;,
  -0.190235;0.899597;0.393111;,
  -0.206469;0.978453;-0.000000;,
  -0.190235;0.899597;-0.393111;,
  -0.151655;0.680219;-0.717149;,
  -0.114174;0.363475;-0.924581;,
  -0.021727;0.000027;-0.999764;,
  -0.040909;-0.378024;-0.924891;,
  -0.097702;-0.759129;-0.643566;,
  -0.144770;-0.956049;-0.254975;,
  -0.159320;-0.987227;-0.000000;,
  -0.144769;-0.956049;0.254975;,
  -0.097702;-0.759129;0.643566;,
  -0.040909;-0.378024;0.924891;,
  -0.021728;0.000027;0.999764;,
  -0.044416;0.377978;0.924749;,
  -0.096498;0.698567;0.709008;,
  -0.147619;0.911542;0.383796;,
  -0.168448;0.985711;-0.000000;,
  -0.147619;0.911542;-0.383796;,
  -0.096498;0.698567;-0.709008;,
  -0.044415;0.377977;-0.924749;,
  0.062176;0.000026;-0.998065;,
  0.030752;-0.397065;-0.917275;,
  -0.057036;-0.780657;-0.622352;,
  -0.132454;-0.963019;-0.234627;,
  -0.155033;-0.987909;-0.000000;,
  -0.132454;-0.963019;0.234627;,
  -0.057035;-0.780657;0.622352;,
  0.030752;-0.397065;0.917275;,
  0.062176;0.000026;0.998065;,
  0.027242;0.397109;0.917367;,
  -0.053432;0.720710;0.691174;,
  -0.131359;0.921044;0.366636;,
  -0.162663;0.986682;-0.000000;,
  -0.131359;0.921045;-0.366636;,
  -0.053432;0.720710;-0.691175;,
  0.027242;0.397109;-0.917367;,
  -0.240105;0.000000;-0.970747;,
  -0.238183;-0.392035;-0.888582;,
  -0.220493;-0.756140;-0.616145;,
  -0.175076;-0.953873;-0.243876;,
  -0.151099;-0.988519;-0.000000;,
  -0.175076;-0.953873;0.243876;,
  -0.220492;-0.756140;0.616145;,
  -0.238183;-0.392035;0.888582;,
  -0.240105;-0.000000;0.970747;,
  -0.238184;0.392034;0.888582;,
  -0.232475;0.708470;0.666353;,
  -0.225459;0.907584;0.354204;,
  -0.222228;0.974995;-0.000000;,
  -0.225459;0.907584;-0.354204;,
  -0.232474;0.708470;-0.666353;,
  -0.238183;0.392034;-0.888582;,
  1.000000;0.000000;-0.000000;,
  0.652846;0.000000;-0.757491;,
  0.642892;-0.299163;-0.705118;,
  0.618245;-0.562090;-0.549389;,
  0.592894;-0.746309;-0.302490;,
  0.582241;-0.813016;-0.000000;,
  0.592894;-0.746309;0.302489;,
  0.618245;-0.562089;0.549389;,
  0.642892;-0.299163;0.705118;,
  0.652846;-0.000000;0.757490;,
  0.642892;0.299163;0.705118;,
  0.618246;0.562090;0.549388;,
  0.592894;0.746309;0.302490;,
  0.582242;0.813016;-0.000000;,
  0.592894;0.746308;-0.302491;,
  0.618246;0.562090;-0.549388;,
  0.642892;0.299163;-0.705118;,
  -0.604002;0.000000;-0.796983;,
  -0.593338;-0.312064;-0.742001;,
  -0.554472;-0.609193;-0.566961;,
  -0.493375;-0.831132;-0.256515;,
  -0.454133;-0.890934;-0.000000;,
  -0.493375;-0.831132;0.256515;,
  -0.554472;-0.609192;0.566961;,
  -0.593338;-0.312064;0.742001;,
  -0.604002;0.000000;0.796983;,
  -0.593338;0.312062;0.742002;,
  -0.567002;0.586501;0.578382;,
  -0.540016;0.779013;0.318623;,
  -0.528714;0.848800;-0.000000;,
  -0.540016;0.779013;-0.318623;,
  -0.567002;0.586501;-0.578382;,
  -0.593338;0.312062;-0.742002;,
  -0.999992;-0.004025;-0.000000;;
  192;
  4;0,1,17,16;,
  4;1,2,18,17;,
  4;2,3,19,18;,
  4;3,4,20,19;,
  4;4,5,21,20;,
  4;5,6,22,21;,
  4;6,7,23,22;,
  4;7,8,24,23;,
  4;8,9,25,24;,
  4;9,10,26,25;,
  4;10,11,27,26;,
  4;11,12,28,27;,
  4;12,13,29,28;,
  4;13,14,30,29;,
  4;14,15,31,30;,
  4;15,0,16,31;,
  4;16,17,33,32;,
  4;17,18,34,33;,
  4;18,19,35,34;,
  4;19,20,36,35;,
  4;20,21,37,36;,
  4;21,22,38,37;,
  4;22,23,39,38;,
  4;23,24,40,39;,
  4;24,25,41,40;,
  4;25,26,42,41;,
  4;26,27,43,42;,
  4;27,28,44,43;,
  4;28,29,45,44;,
  4;29,30,46,45;,
  4;30,31,47,46;,
  4;31,16,32,47;,
  4;32,33,49,48;,
  4;33,34,50,49;,
  4;34,35,51,50;,
  4;35,36,52,51;,
  4;36,37,53,52;,
  4;37,38,54,53;,
  4;38,39,55,54;,
  4;39,40,56,55;,
  4;40,41,57,56;,
  4;41,42,58,57;,
  4;42,43,59,58;,
  4;43,44,60,59;,
  4;44,45,61,60;,
  4;45,46,62,61;,
  4;46,47,63,62;,
  4;47,32,48,63;,
  4;48,49,65,64;,
  4;49,50,66,65;,
  4;50,51,67,66;,
  4;51,52,68,67;,
  4;52,53,69,68;,
  4;53,54,70,69;,
  4;54,55,71,70;,
  4;55,56,72,71;,
  4;56,57,73,72;,
  4;57,58,74,73;,
  4;58,59,75,74;,
  4;59,60,76,75;,
  4;60,61,77,76;,
  4;61,62,78,77;,
  4;62,63,79,78;,
  4;63,48,64,79;,
  4;64,65,81,80;,
  4;65,66,82,81;,
  4;66,67,83,82;,
  4;67,68,84,83;,
  4;68,69,85,84;,
  4;69,70,86,85;,
  4;70,71,87,86;,
  4;71,72,88,87;,
  4;72,73,89,88;,
  4;73,74,90,89;,
  4;74,75,91,90;,
  4;75,76,92,91;,
  4;76,77,93,92;,
  4;77,78,94,93;,
  4;78,79,95,94;,
  4;79,64,80,95;,
  4;80,81,97,96;,
  4;81,82,98,97;,
  4;82,83,99,98;,
  4;83,84,100,99;,
  4;84,85,101,100;,
  4;85,86,102,101;,
  4;86,87,103,102;,
  4;87,88,104,103;,
  4;88,89,105,104;,
  4;89,90,106,105;,
  4;90,91,107,106;,
  4;91,92,108,107;,
  4;92,93,109,108;,
  4;93,94,110,109;,
  4;94,95,111,110;,
  4;95,80,96,111;,
  4;96,97,113,112;,
  4;97,98,114,113;,
  4;98,99,115,114;,
  4;99,100,116,115;,
  4;100,101,117,116;,
  4;101,102,118,117;,
  4;102,103,119,118;,
  4;103,104,120,119;,
  4;104,105,121,120;,
  4;105,106,122,121;,
  4;106,107,123,122;,
  4;107,108,124,123;,
  4;108,109,125,124;,
  4;109,110,126,125;,
  4;110,111,127,126;,
  4;111,96,112,127;,
  4;112,113,129,128;,
  4;113,114,130,129;,
  4;114,115,131,130;,
  4;115,116,132,131;,
  4;116,117,133,132;,
  4;117,118,134,133;,
  4;118,119,135,134;,
  4;119,120,136,135;,
  4;120,121,137,136;,
  4;121,122,138,137;,
  4;122,123,139,138;,
  4;123,124,140,139;,
  4;124,125,141,140;,
  4;125,126,142,141;,
  4;126,127,143,142;,
  4;127,112,128,143;,
  4;145,146,1,0;,
  3;144,146,145;,
  4;146,147,2,1;,
  3;144,147,146;,
  4;147,148,3,2;,
  3;144,148,147;,
  4;148,149,4,3;,
  3;144,149,148;,
  4;149,150,5,4;,
  3;144,150,149;,
  4;150,151,6,5;,
  3;144,151,150;,
  4;151,152,7,6;,
  3;144,152,151;,
  4;152,153,8,7;,
  3;144,153,152;,
  4;153,154,9,8;,
  3;144,154,153;,
  4;154,155,10,9;,
  3;144,155,154;,
  4;155,156,11,10;,
  3;144,156,155;,
  4;156,157,12,11;,
  3;144,157,156;,
  4;157,158,13,12;,
  3;144,158,157;,
  4;158,159,14,13;,
  3;144,159,158;,
  4;159,160,15,14;,
  3;144,160,159;,
  4;160,145,0,15;,
  3;144,145,160;,
  4;162,161,128,129;,
  3;177,161,162;,
  4;163,162,129,130;,
  3;177,162,163;,
  4;164,163,130,131;,
  3;177,163,164;,
  4;165,164,131,132;,
  3;177,164,165;,
  4;166,165,132,133;,
  3;177,165,166;,
  4;167,166,133,134;,
  3;177,166,167;,
  4;168,167,134,135;,
  3;177,167,168;,
  4;169,168,135,136;,
  3;177,168,169;,
  4;170,169,136,137;,
  3;177,169,170;,
  4;171,170,137,138;,
  3;177,170,171;,
  4;172,171,138,139;,
  3;177,171,172;,
  4;173,172,139,140;,
  3;177,172,173;,
  4;174,173,140,141;,
  3;177,173,174;,
  4;175,174,141,142;,
  3;177,174,175;,
  4;176,175,142,143;,
  3;177,175,176;,
  4;161,176,143,128;,
  3;177,176,161;;
 }
 MeshTextureCoords {
  219;
  0.000000;0.000000;,
  0.062500;0.000000;,
  0.062500;0.125000;,
  0.000000;0.125000;,
  0.125000;0.000000;,
  0.125000;0.125000;,
  0.187500;0.000000;,
  0.187500;0.125000;,
  0.250000;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.312500;0.125000;,
  0.375000;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.437500;0.125000;,
  0.500000;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.562500;0.125000;,
  0.625000;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.687500;0.125000;,
  0.750000;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.812500;0.125000;,
  0.875000;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  0.937500;0.125000;,
  1.000000;0.000000;,
  1.000000;0.125000;,
  0.062500;0.250000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.187500;0.250000;,
  0.250000;0.250000;,
  0.312500;0.250000;,
  0.375000;0.250000;,
  0.437500;0.250000;,
  0.500000;0.250000;,
  0.562500;0.250000;,
  0.625000;0.250000;,
  0.687500;0.250000;,
  0.750000;0.250000;,
  0.812500;0.250000;,
  0.875000;0.250000;,
  0.937500;0.250000;,
  1.000000;0.250000;,
  0.062500;0.375000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.187500;0.375000;,
  0.250000;0.375000;,
  0.312500;0.375000;,
  0.375000;0.375000;,
  0.437500;0.375000;,
  0.500000;0.375000;,
  0.562500;0.375000;,
  0.625000;0.375000;,
  0.687500;0.375000;,
  0.750000;0.375000;,
  0.812500;0.375000;,
  0.875000;0.375000;,
  0.937500;0.375000;,
  1.000000;0.375000;,
  0.062500;0.500000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.187500;0.500000;,
  0.250000;0.500000;,
  0.312500;0.500000;,
  0.375000;0.500000;,
  0.437500;0.500000;,
  0.500000;0.500000;,
  0.562500;0.500000;,
  0.625000;0.500000;,
  0.687500;0.500000;,
  0.750000;0.500000;,
  0.812500;0.500000;,
  0.875000;0.500000;,
  0.937500;0.500000;,
  1.000000;0.500000;,
  0.062500;0.625000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.187500;0.625000;,
  0.250000;0.625000;,
  0.312500;0.625000;,
  0.375000;0.625000;,
  0.437500;0.625000;,
  0.500000;0.625000;,
  0.562500;0.625000;,
  0.625000;0.625000;,
  0.687500;0.625000;,
  0.750000;0.625000;,
  0.812500;0.625000;,
  0.875000;0.625000;,
  0.937500;0.625000;,
  1.000000;0.625000;,
  0.062500;0.750000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.187500;0.750000;,
  0.250000;0.750000;,
  0.312500;0.750000;,
  0.375000;0.750000;,
  0.437500;0.750000;,
  0.500000;0.750000;,
  0.562500;0.750000;,
  0.625000;0.750000;,
  0.687500;0.750000;,
  0.750000;0.750000;,
  0.812500;0.750000;,
  0.875000;0.750000;,
  0.937500;0.750000;,
  1.000000;0.750000;,
  0.062500;0.875000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.187500;0.875000;,
  0.250000;0.875000;,
  0.312500;0.875000;,
  0.375000;0.875000;,
  0.437500;0.875000;,
  0.500000;0.875000;,
  0.562500;0.875000;,
  0.625000;0.875000;,
  0.687500;0.875000;,
  0.750000;0.875000;,
  0.812500;0.875000;,
  0.875000;0.875000;,
  0.937500;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.187500;1.000000;,
  0.250000;1.000000;,
  0.312500;1.000000;,
  0.375000;1.000000;,
  0.437500;1.000000;,
  0.500000;1.000000;,
  0.562500;1.000000;,
  0.625000;1.000000;,
  0.687500;1.000000;,
  0.750000;1.000000;,
  0.812500;1.000000;,
  0.875000;1.000000;,
  0.937500;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.062500;0.000000;,
  0.031250;0.000000;,
  0.125000;0.000000;,
  0.093750;0.000000;,
  0.187500;0.000000;,
  0.156250;0.000000;,
  0.250000;0.000000;,
  0.218750;0.000000;,
  0.312500;0.000000;,
  0.281250;0.000000;,
  0.375000;0.000000;,
  0.343750;0.000000;,
  0.437500;0.000000;,
  0.406250;0.000000;,
  0.500000;0.000000;,
  0.468750;0.000000;,
  0.562500;0.000000;,
  0.531250;0.000000;,
  0.625000;0.000000;,
  0.593750;0.000000;,
  0.687500;0.000000;,
  0.656250;0.000000;,
  0.750000;0.000000;,
  0.718750;0.000000;,
  0.812500;0.000000;,
  0.781250;0.000000;,
  0.875000;0.000000;,
  0.843750;0.000000;,
  0.937500;0.000000;,
  0.906250;0.000000;,
  1.000000;0.000000;,
  0.968750;0.000000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.031250;1.000000;,
  0.125000;1.000000;,
  0.093750;1.000000;,
  0.187500;1.000000;,
  0.156250;1.000000;,
  0.250000;1.000000;,
  0.218750;1.000000;,
  0.312500;1.000000;,
  0.281250;1.000000;,
  0.375000;1.000000;,
  0.343750;1.000000;,
  0.437500;1.000000;,
  0.406250;1.000000;,
  0.500000;1.000000;,
  0.468750;1.000000;,
  0.562500;1.000000;,
  0.531250;1.000000;,
  0.625000;1.000000;,
  0.593750;1.000000;,
  0.687500;1.000000;,
  0.656250;1.000000;,
  0.750000;1.000000;,
  0.718750;1.000000;,
  0.812500;1.000000;,
  0.781250;1.000000;,
  0.875000;1.000000;,
  0.843750;1.000000;,
  0.937500;1.000000;,
  0.906250;1.000000;,
  1.000000;1.000000;,
  0.968750;1.000000;;
 }
}