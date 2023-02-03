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
 15;
 -11.99065;-0.19993;-11.90252;,
 11.97415;-0.18384;-11.83218;,
 9.90613;-9.41598;-15.76154;,
 4.15153;-10.15498;-16.38128;,
 11.83288;0.25134;11.86792;,
 -11.95578;0.29905;11.87160;,
 -11.95547;-18.86872;11.77697;,
 11.92398;-18.56016;12.20819;,
 -10.83661;-10.24530;-16.83971;,
 -5.44848;-10.54158;-15.67268;,
 8.95154;-19.20443;-38.99641;,
 4.15153;-19.87085;-12.03900;,
 -10.24849;-19.20443;-38.79046;,
 -5.44848;-19.87085;-11.82666;,
 -0.64847;-19.20443;-39.25807;;
 
 22;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;5,0,8,6;,
 4;5,4,1,0;,
 3;0,3,9;,
 3;10,2,7;,
 3;10,11,3;,
 3;10,3,2;,
 3;10,7,11;,
 3;7,6,11;,
 3;12,6,8;,
 3;12,9,13;,
 3;14,3,11;,
 3;14,13,9;,
 3;6,13,11;,
 3;14,9,3;,
 3;14,11,13;,
 3;12,8,9;,
 3;12,13,6;,
 3;4,7,2;,
 3;2,1,4;,
 3;0,9,8;;
 
 MeshMaterialList {
  4;
  22;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
 }
 MeshNormals {
  30;
  0.052815;0.385023;-0.921395;,
  -0.999397;-0.012091;-0.032556;,
  0.054266;0.713050;-0.699010;,
  -0.053771;0.697300;-0.714760;,
  -0.008901;0.006576;0.999939;,
  0.981599;-0.072779;-0.176540;,
  -0.981103;-0.078948;-0.176646;,
  0.026410;0.397702;-0.917134;,
  -0.027165;0.711183;-0.702482;,
  -0.999277;0.017331;-0.033847;,
  0.981459;-0.078209;-0.174992;,
  0.997433;0.041405;-0.058422;,
  -0.998650;-0.041504;-0.031238;,
  0.000696;0.999806;-0.019665;,
  0.997414;-0.059658;-0.040076;,
  0.997656;0.022482;-0.064625;,
  -0.076741;0.919966;-0.384413;,
  0.156056;-0.987743;0.003369;,
  0.084270;-0.996082;0.026830;,
  0.042227;-0.998946;0.017998;,
  -0.044633;-0.998504;0.031570;,
  -0.982211;-0.071571;-0.173608;,
  -0.048821;-0.998785;0.006659;,
  -0.063792;0.932501;-0.355488;,
  -0.000539;-0.999703;-0.024381;,
  0.131027;0.919094;-0.371615;,
  0.182923;0.729168;-0.659434;,
  -0.146459;-0.989215;0.001623;,
  0.993422;-0.110322;-0.030676;,
  0.974863;-0.222584;0.009898;;
  22;
  4;0,7,8,3;,
  4;4,4,4,4;,
  4;12,12,1,1;,
  4;13,13,13,13;,
  3;0,3,2;,
  3;11,14,15;,
  3;6,6,6;,
  3;16,3,8;,
  3;17,18,19;,
  3;18,20,19;,
  3;9,1,1;,
  3;5,5,5;,
  3;10,10,10;,
  3;21,21,21;,
  3;20,22,19;,
  3;23,2,3;,
  3;24,19,22;,
  3;25,26,2;,
  3;27,22,20;,
  3;28,15,14;,
  3;14,29,28;,
  3;0,2,26;;
 }
}
