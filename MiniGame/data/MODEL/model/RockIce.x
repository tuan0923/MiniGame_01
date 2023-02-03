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
 50;
 0.00000;17.75016;0.00000;,
 -3.03234;17.26998;2.79288;,
 1.43532;16.95342;4.46262;,
 -4.50000;17.36496;-1.50000;,
 4.50000;16.08462;1.50000;,
 1.81716;16.48776;-2.60310;,
 -1.50000;16.43688;-4.50000;,
 -2.09583;15.00000;-5.68440;,
 -5.32497;14.70240;-5.14896;,
 2.01498;15.00000;-5.63676;,
 5.97246;10.08111;-6.55272;,
 1.50000;12.00000;-7.50000;,
 4.42239;14.55663;-4.54371;,
 7.19094;13.50000;-0.75000;,
 7.50000;4.31250;-3.75000;,
 7.50000;12.00000;-4.50000;,
 5.92239;14.42622;3.40593;,
 6.60234;10.74879;5.11698;,
 4.43910;13.57206;6.47295;,
 1.37091;14.73807;6.93792;,
 1.04484;9.87441;8.48385;,
 -3.06468;14.97243;6.31773;,
 -6.15654;9.53514;7.23456;,
 -1.50000;12.00000;7.50000;,
 -5.87910;14.90625;4.10427;,
 -6.62259;14.22918;1.94097;,
 -8.65026;4.15281;-5.09346;,
 -7.50000;12.00000;4.50000;,
 -6.60510;15.00000;-3.00000;,
 6.00000;5.49999;7.50000;,
 -9.65538;6.17181;4.11144;,
 -1.50000;10.50000;-7.88079;,
 1.50000;9.00000;-7.50000;,
 4.50000;6.00000;-7.50000;,
 7.50000;9.00000;1.50000;,
 7.50000;6.00000;4.50000;,
 -1.95516;8.37441;8.48385;,
 -4.50000;6.00000;8.75052;,
 -5.19282;2.78139;7.85727;,
 -3.75000;2.25000;-7.50000;,
 4.50000;3.00000;-7.50000;,
 -8.53356;-0.06747;-0.18600;,
 -3.83652;0.24126;5.16324;,
 1.04484;5.37441;8.48385;,
 7.10523;0.51855;1.46310;,
 3.75000;0.00000;5.25000;,
 1.50000;3.00000;7.50000;,
 -1.95516;5.37441;9.06651;,
 4.82100;0.00000;-1.62900;,
 3.00000;0.00000;-4.50000;;
 
 96;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,5;,
 3;0,5,6;,
 3;7,8,6;,
 3;9,10,11;,
 3;9,5,12;,
 3;13,14,15;,
 3;13,12,5;,
 3;16,17,13;,
 3;16,4,18;,
 3;19,20,18;,
 3;19,18,2;,
 3;21,22,23;,
 3;21,1,24;,
 3;25,26,27;,
 3;25,24,1;,
 3;28,3,8;,
 3;10,15,14;,
 3;17,18,29;,
 3;22,27,30;,
 3;31,11,32;,
 3;10,32,11;,
 3;10,9,12;,
 3;10,14,33;,
 3;14,13,34;,
 3;17,34,13;,
 3;17,16,18;,
 3;17,29,35;,
 3;20,29,18;,
 3;20,23,36;,
 3;22,36,23;,
 3;22,21,24;,
 3;22,30,37;,
 3;26,30,27;,
 3;26,28,8;,
 3;38,37,30;,
 3;26,31,39;,
 3;39,31,32;,
 3;10,33,32;,
 3;39,32,33;,
 3;39,33,40;,
 3;26,25,28;,
 3;41,42,38;,
 3;30,41,38;,
 3;30,26,41;,
 3;8,7,31;,
 3;31,26,8;,
 3;29,20,43;,
 3;44,35,29;,
 3;35,44,14;,
 3;29,45,44;,
 3;43,46,29;,
 3;45,46,38;,
 3;38,42,45;,
 3;11,31,7;,
 3;11,7,9;,
 3;36,43,20;,
 3;47,43,36;,
 3;43,47,46;,
 3;46,47,38;,
 3;47,37,38;,
 3;24,27,22;,
 3;27,24,25;,
 3;1,3,25;,
 3;25,3,28;,
 3;0,6,3;,
 3;3,6,8;,
 3;4,2,18;,
 3;2,4,0;,
 3;4,13,5;,
 3;13,4,16;,
 3;35,34,17;,
 3;12,13,15;,
 3;12,15,10;,
 3;6,9,7;,
 3;9,6,5;,
 3;19,21,23;,
 3;20,19,23;,
 3;21,19,2;,
 3;21,2,1;,
 3;37,47,36;,
 3;37,36,22;,
 3;44,45,48;,
 3;46,45,29;,
 3;40,33,14;,
 3;49,39,40;,
 3;14,34,35;,
 3;40,14,49;,
 3;48,49,14;,
 3;41,45,42;,
 3;48,14,44;,
 3;45,41,48;,
 3;41,49,48;,
 3;41,26,39;,
 3;41,39,49;;
 
 MeshMaterialList {
  1;
  96;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.000000;1.000000;1.000000;0.500000;;
   5.000000;
   0.500000;0.500000;0.500000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  51;
  -0.442801;0.544522;-0.712336;,
  -0.090464;0.539580;-0.837060;,
  0.241319;0.670086;-0.701962;,
  -0.883503;0.071226;-0.462978;,
  -0.166341;0.171406;-0.971057;,
  0.127119;0.291971;-0.947942;,
  0.485955;0.217651;-0.846449;,
  0.118613;0.019149;-0.992756;,
  0.370551;0.010300;-0.928755;,
  -0.152244;-0.378671;-0.912924;,
  0.457910;-0.413012;-0.787235;,
  0.491300;0.721754;-0.487540;,
  0.870398;0.491798;-0.023293;,
  0.754680;0.574250;0.317325;,
  0.831734;0.344664;-0.435230;,
  0.918892;-0.229823;-0.320653;,
  0.901645;0.221408;0.371503;,
  0.993189;0.090981;0.072784;,
  0.976921;-0.018823;0.212769;,
  0.899114;-0.410532;0.151847;,
  0.182701;-0.852616;0.489558;,
  0.526033;0.508060;0.682029;,
  0.069039;0.493112;0.867222;,
  -0.261929;0.595816;0.759208;,
  0.092399;0.178851;0.979528;,
  -0.152182;0.289955;0.944864;,
  -0.476785;0.295426;0.827888;,
  0.578359;-0.148643;0.802126;,
  -0.070768;0.210192;0.975095;,
  0.154433;-0.103518;0.982565;,
  0.037640;-0.143820;0.988888;,
  -0.377915;0.045774;0.924708;,
  0.150361;-0.442698;0.883974;,
  -0.313572;-0.521050;0.793838;,
  -0.192408;-0.879426;0.435418;,
  -0.657752;0.619905;0.427878;,
  -0.846372;0.528450;0.066298;,
  -0.843222;0.489285;-0.222658;,
  -0.888962;0.386197;0.246167;,
  -0.900702;-0.008455;0.434355;,
  -0.347898;0.899194;0.265362;,
  0.190080;0.879257;0.436779;,
  0.139110;0.986734;-0.083696;,
  0.513656;0.853838;0.084367;,
  -0.429229;0.890070;-0.153419;,
  0.369613;0.882039;-0.292220;,
  -0.006391;0.847832;-0.530227;,
  -0.441373;-0.897322;0.001898;,
  0.336931;-0.925361;-0.173740;,
  0.284696;-0.870228;-0.402059;,
  0.184210;-0.982468;0.028680;;
  96;
  3;42,40,41;,
  3;42,44,40;,
  3;42,43,45;,
  3;42,45,46;,
  3;1,0,46;,
  3;2,6,5;,
  3;2,45,11;,
  3;12,15,14;,
  3;12,11,45;,
  3;13,16,12;,
  3;13,43,21;,
  3;22,24,21;,
  3;22,21,41;,
  3;23,26,25;,
  3;23,40,35;,
  3;36,3,38;,
  3;36,35,40;,
  3;37,44,0;,
  3;6,14,15;,
  3;16,21,27;,
  3;26,38,39;,
  3;4,5,7;,
  3;6,7,5;,
  3;6,2,11;,
  3;6,15,8;,
  3;15,12,17;,
  3;16,17,12;,
  3;16,13,21;,
  3;16,27,18;,
  3;24,27,21;,
  3;24,25,28;,
  3;26,28,25;,
  3;26,23,35;,
  3;26,39,31;,
  3;3,39,38;,
  3;3,37,0;,
  3;33,31,39;,
  3;3,4,9;,
  3;9,4,7;,
  3;6,8,7;,
  3;9,7,8;,
  3;9,8,10;,
  3;3,36,37;,
  3;47,34,33;,
  3;39,47,33;,
  3;39,3,47;,
  3;0,1,4;,
  3;4,3,0;,
  3;27,24,29;,
  3;19,18,27;,
  3;18,19,15;,
  3;27,20,19;,
  3;29,32,27;,
  3;20,32,33;,
  3;33,34,20;,
  3;5,4,1;,
  3;5,1,2;,
  3;28,29,24;,
  3;30,29,28;,
  3;29,30,32;,
  3;32,30,33;,
  3;30,31,33;,
  3;35,38,26;,
  3;38,35,36;,
  3;40,44,36;,
  3;36,44,37;,
  3;42,46,44;,
  3;44,46,0;,
  3;43,41,21;,
  3;41,43,42;,
  3;43,12,45;,
  3;12,43,13;,
  3;18,17,16;,
  3;11,12,14;,
  3;11,14,6;,
  3;46,2,1;,
  3;2,46,45;,
  3;22,23,25;,
  3;24,22,25;,
  3;23,22,41;,
  3;23,41,40;,
  3;31,30,28;,
  3;31,28,26;,
  3;50,20,48;,
  3;32,20,27;,
  3;10,8,15;,
  3;49,9,10;,
  3;15,17,18;,
  3;10,15,49;,
  3;48,49,15;,
  3;47,20,34;,
  3;48,15,19;,
  3;20,47,48;,
  3;47,49,48;,
  3;47,3,9;,
  3;47,9,49;;
 }
}