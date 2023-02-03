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
 86;
 -90.00000;60.00000;30.00000;,
 -73.63638;60.00000;30.00000;,
 -73.63638;60.00000;18.00000;,
 -86.10264;54.13572;0.00000;,
 73.63638;60.00000;30.00000;,
 90.00000;60.00000;30.00000;,
 86.96400;54.00000;0.00000;,
 73.63638;60.00000;18.00000;,
 -73.63638;60.00000;-18.00000;,
 -73.63638;60.00000;-30.00000;,
 -90.00000;60.00000;-30.00000;,
 73.63638;60.00000;-18.00000;,
 90.00000;60.00000;-30.00000;,
 73.63638;60.00000;-30.00000;,
 -57.27270;60.00000;18.00000;,
 -52.30746;53.05350;1.26468;,
 -73.44360;53.05350;-2.09640;,
 -57.27270;60.00000;-18.00000;,
 57.27270;60.00000;-18.00000;,
 53.23662;53.05350;-2.09640;,
 40.90908;60.00000;-18.00000;,
 36.87300;53.05350;-2.09640;,
 24.54546;60.00000;-18.00000;,
 20.50938;53.05350;-2.09640;,
 8.18184;60.00000;-18.00000;,
 4.14576;53.05350;-2.09640;,
 -8.18184;60.00000;-18.00000;,
 -12.21792;53.05350;-2.09640;,
 -24.54546;60.00000;-18.00000;,
 -28.58154;53.05350;-2.09640;,
 -40.90908;60.00000;-18.00000;,
 -44.94516;53.05350;-2.09640;,
 -61.30878;53.05350;-2.09640;,
 -35.94384;53.05350;1.26468;,
 -40.90908;60.00000;18.00000;,
 -24.54546;60.00000;18.00000;,
 -19.58022;53.05350;1.26468;,
 -8.18184;60.00000;18.00000;,
 -3.21660;53.05350;1.26468;,
 8.18184;60.00000;18.00000;,
 13.14708;53.05350;1.26468;,
 24.54546;60.00000;18.00000;,
 29.51070;53.05350;1.26468;,
 40.90908;60.00000;18.00000;,
 45.87432;53.05350;1.26468;,
 57.27270;60.00000;18.00000;,
 62.23794;53.05350;1.26468;,
 74.22996;53.05350;1.26468;,
 -57.27270;0.00000;-30.00000;,
 -73.63638;0.00000;-18.00000;,
 -73.63638;0.00000;-30.00000;,
 -57.27270;0.00000;0.00000;,
 -40.90908;0.00000;-30.00000;,
 -40.90908;0.00000;0.00000;,
 -24.54546;0.00000;-30.00000;,
 -24.54546;0.00000;0.00000;,
 -8.18184;0.00000;-30.00000;,
 -8.18184;0.00000;0.00000;,
 8.18184;0.00000;-30.00000;,
 8.18184;0.00000;0.00000;,
 24.54546;0.00000;-30.00000;,
 24.54546;0.00000;0.00000;,
 40.90908;0.00000;-30.00000;,
 40.90908;0.00000;0.00000;,
 57.27270;0.00000;-30.00000;,
 57.27270;0.00000;0.00000;,
 73.63638;0.00000;-30.00000;,
 73.63638;0.00000;0.00000;,
 86.96443;0.00000;0.00000;,
 -86.10264;0.00000;0.00000;,
 -73.63638;0.00000;0.00000;,
 73.63638;0.00000;18.00000;,
 73.63638;0.00000;30.00000;,
 57.27270;0.00000;30.00000;,
 40.90908;0.00000;30.00000;,
 24.54546;0.00000;30.00000;,
 8.18184;0.00000;30.00000;,
 -8.18184;0.00000;30.00000;,
 -24.54546;0.00000;30.00000;,
 -40.90908;0.00000;30.00000;,
 -57.27270;0.00000;30.00000;,
 -73.63638;0.00000;30.00000;,
 -90.00000;0.00000;30.00000;,
 -90.00000;0.00000;-30.00000;,
 90.00000;0.00000;-30.00000;,
 90.00000;0.00000;30.00000;;
 
 80;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;3,8,9,10;,
 4;11,6,12,13;,
 3;2,14,15;,
 3;8,16,17;,
 3;18,19,11;,
 3;18,20,21;,
 3;20,22,23;,
 3;22,24,25;,
 3;24,26,27;,
 3;26,28,29;,
 3;28,30,31;,
 3;30,17,32;,
 3;33,14,34;,
 3;34,35,36;,
 3;35,37,38;,
 3;37,39,40;,
 3;39,41,42;,
 3;41,43,44;,
 3;43,45,46;,
 3;45,7,47;,
 4;48,17,16,49;,
 4;16,8,50,49;,
 4;32,17,48,51;,
 4;52,30,32,51;,
 4;31,30,52,53;,
 4;28,31,53,54;,
 4;26,29,55,56;,
 4;24,27,57,58;,
 4;22,25,59,60;,
 4;20,23,61,62;,
 4;18,21,63,64;,
 4;11,19,65,66;,
 4;29,28,54,55;,
 4;27,26,56,57;,
 4;25,24,58,59;,
 4;23,22,60,61;,
 4;21,20,62,63;,
 4;19,18,64,65;,
 4;6,11,67,68;,
 4;3,69,70,8;,
 4;71,47,7,72;,
 4;47,71,73,45;,
 4;45,73,65,46;,
 4;46,65,74,43;,
 4;44,43,74,63;,
 4;44,63,75,41;,
 4;41,75,61,42;,
 4;42,61,76,39;,
 4;40,39,76,59;,
 4;40,59,77,37;,
 4;37,77,57,38;,
 4;38,57,78,35;,
 4;35,78,55,36;,
 4;36,55,79,34;,
 4;34,79,53,33;,
 4;33,53,80,14;,
 4;14,80,51,15;,
 4;15,51,81,2;,
 4;2,70,69,3;,
 4;67,7,6,68;,
 4;11,13,66,67;,
 3;71,7,67;,
 3;70,49,8;,
 4;2,1,81,70;,
 4;3,69,82,0;,
 4;3,10,83,69;,
 4;81,82,69,70;,
 4;83,50,70,69;,
 4;12,6,68,84;,
 4;6,5,85,68;,
 4;84,68,67,66;,
 4;68,85,72,67;,
 4;81,50,66,72;,
 4;72,66,50,81;,
 4;0,82,85,5;,
 4;4,7,2,1;,
 4;10,12,84,83;,
 4;9,8,11,13;;
 
 MeshMaterialList {
  1;
  80;
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
   0.000000;1.000000;0.941000;0.500000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.000000;0.250000;0.235250;;
  }
 }
 MeshNormals {
  74;
  -0.077183;0.991446;0.105250;,
  -0.038674;0.997859;0.052738;,
  0.038670;0.997860;0.052731;,
  -0.991667;0.000000;0.128830;,
  -0.999982;0.000000;0.006061;,
  0.660087;-0.180024;0.729299;,
  0.775398;-0.033507;0.630583;,
  0.775398;-0.033507;0.630583;,
  0.775397;-0.033507;0.630584;,
  0.775398;-0.033507;0.630583;,
  0.775397;-0.033507;0.630585;,
  0.077174;0.991448;0.105237;,
  0.077605;0.996984;0.000000;,
  0.994919;0.000004;0.100679;,
  -0.420909;0.103884;0.901135;,
  0.077174;0.991448;-0.105237;,
  0.038670;0.997860;-0.052731;,
  -0.038674;0.997859;-0.052738;,
  0.994919;0.000004;-0.100679;,
  0.999843;0.000000;0.017726;,
  -0.659627;-0.179899;-0.729746;,
  -0.775832;-0.029459;-0.630252;,
  -0.775832;-0.029459;-0.630252;,
  -0.775832;-0.029459;-0.630252;,
  -0.775831;-0.029459;-0.630253;,
  -0.775832;-0.029459;-0.630252;,
  -0.775832;-0.029459;-0.630252;,
  -0.775831;-0.029459;-0.630253;,
  -0.077183;0.991446;-0.105250;,
  -0.077614;0.996983;0.000000;,
  -0.991667;0.000000;-0.128830;,
  0.436362;0.100484;0.894143;,
  -0.026104;0.985905;-0.165256;,
  0.000000;0.923596;-0.383367;,
  0.026101;0.985906;-0.165252;,
  0.000000;0.923596;-0.383367;,
  0.000000;0.923596;-0.383366;,
  0.000000;0.923596;-0.383367;,
  0.000000;0.923596;-0.383366;,
  0.000000;0.916397;0.400271;,
  0.000000;0.916397;0.400271;,
  0.000000;0.916397;0.400271;,
  -0.026142;0.984886;0.171220;,
  0.000000;0.916397;0.400271;,
  0.026139;0.984887;0.171216;,
  -0.921414;-0.023339;-0.387881;,
  -0.921414;-0.023338;-0.387880;,
  0.917445;-0.028023;0.396874;,
  0.917445;-0.028023;0.396874;,
  0.917445;-0.028023;0.396874;,
  0.917445;-0.028023;0.396874;,
  0.917445;-0.028023;0.396874;,
  0.917445;-0.028023;0.396874;,
  0.911067;-0.098799;0.400244;,
  -0.993306;-0.015352;-0.114487;,
  -0.921414;-0.023339;-0.387880;,
  -0.921414;-0.023339;-0.387880;,
  -0.993306;-0.015352;-0.114487;,
  -0.921414;-0.023339;-0.387881;,
  -0.921414;-0.023339;-0.387880;,
  -0.921414;-0.023339;-0.387880;,
  -0.910941;-0.098743;-0.400545;,
  0.990842;-0.020443;0.133467;,
  0.990842;-0.020443;0.133467;,
  0.990842;-0.020443;0.133467;,
  0.436362;0.100484;-0.894143;,
  -0.420909;0.103884;-0.901135;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  1.000000;0.000004;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.000000;-1.000000;;
  80;
  4;28,17,32,29;,
  4;16,15,12,34;,
  4;29,42,1,0;,
  4;44,12,11,2;,
  3;32,33,35;,
  3;42,39,43;,
  3;43,39,44;,
  3;43,43,40;,
  3;43,41,39;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,43,39;,
  3;43,43,40;,
  3;36,33,33;,
  3;33,33,37;,
  3;33,33,37;,
  3;33,33,38;,
  3;33,33,37;,
  3;33,33,37;,
  3;33,33,36;,
  3;33,34,35;,
  4;5,5,5,53;,
  4;4,4,4,4;,
  4;54,54,54,45;,
  4;6,6,6,51;,
  4;54,54,54,46;,
  4;7,7,50,7;,
  4;7,7,47,7;,
  4;8,8,48,8;,
  4;9,9,49,9;,
  4;7,7,50,7;,
  4;6,6,51,6;,
  4;10,10,52,10;,
  4;54,54,54,55;,
  4;54,54,54,56;,
  4;57,57,57,58;,
  4;54,54,54,59;,
  4;54,54,54,55;,
  4;54,54,54,60;,
  4;14,14,14,14;,
  4;31,31,31,31;,
  4;19,19,19,19;,
  4;20,61,20,20;,
  4;62,62,52,62;,
  4;21,60,21,21;,
  4;62,62,62,51;,
  4;22,55,22,22;,
  4;63,63,50,63;,
  4;23,59,23,23;,
  4;64,64,64,49;,
  4;24,58,24,24;,
  4;64,64,48,64;,
  4;25,56,25,25;,
  4;62,62,47,62;,
  4;22,55,22,22;,
  4;63,63,50,63;,
  4;26,46,26,26;,
  4;62,62,51,62;,
  4;27,45,27,27;,
  4;65,65,65,65;,
  4;66,66,66,66;,
  4;67,67,67,67;,
  3;61,67,67;,
  3;68,53,68;,
  4;68,68,68,68;,
  4;67,67,30,30;,
  4;67,3,3,67;,
  4;69,69,69,69;,
  4;69,69,69,69;,
  4;13,70,70,13;,
  4;70,18,18,70;,
  4;69,69,69,69;,
  4;69,69,69,69;,
  4;69,69,69,69;,
  4;71,71,71,71;,
  4;72,72,72,72;,
  4;16,34,32,17;,
  4;73,73,73,73;,
  4;1,42,44,2;;
 }
}