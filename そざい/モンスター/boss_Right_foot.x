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
 -11.91056;0.45164;-12.06910;,
 11.80165;0.53447;-11.99999;,
 11.96472;-9.64613;-14.02855;,
 4.37744;-9.89585;-14.60360;,
 12.05113;0.26587;12.00191;,
 -11.99059;0.81248;11.91835;,
 -12.15088;-18.64586;11.91136;,
 11.32243;-18.76631;11.94011;,
 -11.26774;-9.87959;-12.84602;,
 -5.22518;-10.01688;-13.93969;,
 9.17484;-18.98138;-37.26354;,
 4.37484;-19.64780;-10.30600;,
 -10.02517;-18.98138;-37.05759;,
 -5.22518;-19.64780;-10.09367;,
 -0.42516;-18.98138;-37.52521;;
 
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
  31;
  -0.070917;0.138624;-0.987803;,
  -0.999246;-0.024137;-0.030398;,
  -0.123444;0.097627;-0.987538;,
  -0.021271;0.633549;-0.773410;,
  -0.002386;-0.001730;0.999996;,
  0.981771;-0.070489;-0.176512;,
  -0.981215;-0.077578;-0.176631;,
  0.034868;0.218608;-0.975190;,
  0.018399;0.647871;-0.761528;,
  -0.998837;-0.021412;-0.043212;,
  0.981526;-0.077376;-0.174983;,
  0.981139;-0.188684;-0.041999;,
  -0.999485;-0.026858;-0.017578;,
  0.009623;0.999952;-0.002051;,
  0.997458;-0.069931;-0.013698;,
  0.993378;-0.113856;-0.015417;,
  -0.002306;0.928001;-0.372571;,
  0.130105;-0.991499;-0.001345;,
  0.062622;-0.997837;0.019982;,
  0.031415;-0.999389;0.015353;,
  -0.048548;-0.998391;0.029292;,
  -0.982377;-0.069319;-0.173582;,
  -0.047012;-0.998867;0.007379;,
  -0.036741;0.931620;-0.361572;,
  -0.039744;0.933054;-0.357533;,
  -0.000539;-0.999703;-0.024381;,
  -0.042747;0.934463;-0.353484;,
  -0.141136;-0.989990;0.000657;,
  0.999949;-0.010129;0.000538;,
  0.999785;0.018045;-0.010190;,
  -0.176364;0.062898;-0.982313;;
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
  3;23,24,3;,
  3;25,19,22;,
  3;26,26,24;,
  3;27,22,20;,
  3;28,15,14;,
  3;14,29,28;,
  3;0,2,30;;
 }
}
