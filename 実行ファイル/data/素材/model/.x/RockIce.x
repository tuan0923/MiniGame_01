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
 0.00000;5.91672;0.00000;,
 1.01078;5.75666;0.93096;,
 -0.47844;5.65114;1.48754;,
 1.50000;5.78832;-0.50000;,
 -1.50000;5.36154;0.50000;,
 -0.60572;5.49592;-0.86770;,
 0.50000;5.47896;-1.50000;,
 0.69861;5.00000;-1.89480;,
 1.77499;4.90080;-1.71632;,
 -0.67166;5.00000;-1.87892;,
 -1.99082;3.36037;-2.18424;,
 -0.50000;4.00000;-2.50000;,
 -1.47413;4.85221;-1.51457;,
 -2.39698;4.50000;-0.25000;,
 -2.50000;1.43750;-1.25000;,
 -2.50000;4.00000;-1.50000;,
 -1.97413;4.80874;1.13531;,
 -2.20078;3.58293;1.70566;,
 -1.47970;4.52402;2.15765;,
 -0.45697;4.91269;2.31264;,
 -0.34828;3.29147;2.82795;,
 1.02156;4.99081;2.10591;,
 2.05218;3.17838;2.41152;,
 0.50000;4.00000;2.50000;,
 1.95970;4.96875;1.36809;,
 2.20753;4.74306;0.64699;,
 2.88342;1.38427;-1.69782;,
 2.50000;4.00000;1.50000;,
 2.20170;5.00000;-1.00000;,
 -2.00000;1.83333;2.50000;,
 3.21846;2.05727;1.37048;,
 0.50000;3.50000;-2.62693;,
 -0.50000;3.00000;-2.50000;,
 -1.50000;2.00000;-2.50000;,
 -2.50000;3.00000;0.50000;,
 -2.50000;2.00000;1.50000;,
 0.65172;2.79147;2.82795;,
 1.50000;2.00000;2.91684;,
 1.73094;0.92713;2.61909;,
 1.25000;0.75000;-2.50000;,
 -1.50000;1.00000;-2.50000;,
 2.84452;-0.02249;-0.06200;,
 1.27884;0.08042;1.72108;,
 -0.34828;1.79147;2.82795;,
 -2.36841;0.17285;0.48770;,
 -1.25000;0.00000;1.75000;,
 -0.50000;1.00000;2.50000;,
 0.65172;1.79147;3.02217;,
 -1.60700;0.00000;-0.54300;,
 -1.00000;0.00000;-1.50000;;
 
 96;
 3;2,1,0;,
 3;1,3,0;,
 3;5,4,0;,
 3;6,5,0;,
 3;6,8,7;,
 3;11,10,9;,
 3;12,5,9;,
 3;15,14,13;,
 3;5,12,13;,
 3;13,17,16;,
 3;18,4,16;,
 3;18,20,19;,
 3;2,18,19;,
 3;23,22,21;,
 3;24,1,21;,
 3;27,26,25;,
 3;1,24,25;,
 3;8,3,28;,
 3;14,15,10;,
 3;29,18,17;,
 3;30,27,22;,
 3;32,11,31;,
 3;11,32,10;,
 3;12,9,10;,
 3;33,14,10;,
 3;34,13,14;,
 3;13,34,17;,
 3;18,16,17;,
 3;35,29,17;,
 3;18,29,20;,
 3;36,23,20;,
 3;23,36,22;,
 3;24,21,22;,
 3;37,30,22;,
 3;27,30,26;,
 3;8,28,26;,
 3;30,37,38;,
 3;39,31,26;,
 3;32,31,39;,
 3;32,33,10;,
 3;33,32,39;,
 3;40,33,39;,
 3;28,25,26;,
 3;38,42,41;,
 3;38,41,30;,
 3;41,26,30;,
 3;31,7,8;,
 3;8,26,31;,
 3;43,20,29;,
 3;29,35,44;,
 3;14,44,35;,
 3;44,45,29;,
 3;29,46,43;,
 3;38,46,45;,
 3;45,42,38;,
 3;7,31,11;,
 3;9,7,11;,
 3;20,43,36;,
 3;36,43,47;,
 3;46,47,43;,
 3;38,47,46;,
 3;38,37,47;,
 3;22,27,24;,
 3;25,24,27;,
 3;25,3,1;,
 3;28,3,25;,
 3;3,6,0;,
 3;8,6,3;,
 3;18,2,4;,
 3;0,4,2;,
 3;5,13,4;,
 3;16,4,13;,
 3;17,34,35;,
 3;15,13,12;,
 3;10,15,12;,
 3;7,9,6;,
 3;5,6,9;,
 3;23,21,19;,
 3;23,19,20;,
 3;2,19,21;,
 3;1,2,21;,
 3;36,47,37;,
 3;22,36,37;,
 3;48,45,44;,
 3;29,45,46;,
 3;14,33,40;,
 3;40,39,49;,
 3;35,34,14;,
 3;49,14,40;,
 3;14,49,48;,
 3;42,45,41;,
 3;44,14,48;,
 3;48,41,45;,
 3;48,49,41;,
 3;39,26,41;,
 3;49,39,41;;
 
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
}
