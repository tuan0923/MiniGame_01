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
 16;
 -50.26357;0.34919;-12.80106;,
 -50.59346;8.83626;-8.99438;,
 -0.08675;9.04721;-8.99438;,
 0.24312;0.56006;-12.80106;,
 -50.73006;12.35172;0.19574;,
 -0.22351;12.56269;0.19574;,
 -50.59346;8.83626;9.38588;,
 -0.08675;9.04721;9.38588;,
 -50.26357;0.34919;13.19256;,
 0.24312;0.56006;13.19256;,
 -49.93357;-8.13791;9.38587;,
 0.57302;-7.92689;9.38587;,
 -49.79687;-11.65351;0.19574;,
 0.70958;-11.44264;0.19574;,
 -49.93357;-8.13791;-8.99438;,
 0.57302;-7.92689;-8.99438;;
 
 20;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,0,3,15;,
 3;12,1,0;,
 3;12,4,1;,
 3;12,6,4;,
 3;12,8,6;,
 3;12,10,8;,
 3;12,0,14;,
 3;13,15,3;,
 3;13,9,11;,
 3;13,7,9;,
 3;13,3,2;,
 3;13,2,5;,
 3;13,5,7;;
 
 MeshMaterialList {
  4;
  20;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
  24;
  0.004177;-0.999991;-0.000000;,
  0.000000;-0.000002;-1.000000;,
  -0.003035;0.726676;-0.686974;,
  -0.004177;0.999991;-0.000000;,
  -0.003035;0.726676;0.686973;,
  0.000000;-0.000002;1.000000;,
  0.003035;-0.726671;0.686979;,
  0.003035;-0.726671;-0.686979;,
  -0.999245;-0.038847;0.000000;,
  -0.999245;-0.038845;0.000008;,
  -0.999245;-0.038849;0.000005;,
  -0.999245;-0.038845;0.000000;,
  -0.999245;-0.038845;-0.000008;,
  -0.999245;-0.038849;-0.000005;,
  -0.999245;-0.038853;-0.000001;,
  -0.999245;-0.038853;0.000001;,
  0.999245;0.038842;0.000000;,
  0.999245;0.038849;0.000014;,
  0.999245;0.038843;0.000008;,
  0.999245;0.038843;-0.000008;,
  0.999245;0.038849;-0.000014;,
  0.999246;0.038839;-0.000007;,
  0.999246;0.038839;0.000007;,
  0.999245;0.038841;0.000000;;
  20;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,0,0,6;,
  4;0,7,7,0;,
  4;7,1,1,7;,
  3;8,9,10;,
  3;8,11,9;,
  3;8,12,11;,
  3;8,13,12;,
  3;8,14,13;,
  3;8,10,15;,
  3;16,17,18;,
  3;16,19,20;,
  3;16,21,19;,
  3;16,18,22;,
  3;16,22,23;,
  3;16,23,21;;
 }
}
