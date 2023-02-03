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
 37;
 0.07326;113.19838;-0.00572;,
 13.27280;108.54476;-12.75238;,
 0.07326;108.54476;-18.66811;,
 -13.12627;108.54476;-12.75238;,
 17.60554;104.75557;-16.93648;,
 0.07326;104.75557;-24.79404;,
 25.74230;104.75557;-0.00572;,
 -17.45903;104.75557;-16.93645;,
 -25.59577;104.75557;-0.00571;,
 24.20437;90.06677;-23.30888;,
 0.07326;90.06677;-34.12394;,
 35.40365;90.06677;-0.00572;,
 17.60554;104.75557;16.92503;,
 24.20437;90.06677;23.29743;,
 0.07326;104.75557;24.78259;,
 0.07327;90.06677;34.11245;,
 -17.45900;104.75557;16.92503;,
 -24.05784;90.06677;23.29745;,
 -35.25715;90.06677;-0.00571;,
 -24.05785;90.06677;-23.30888;,
 23.72773;16.11157;-22.84860;,
 0.07326;16.11157;-33.45005;,
 34.70580;16.11157;-0.00572;,
 23.72773;16.11157;22.83715;,
 0.07327;16.11157;33.43855;,
 -23.58120;16.11157;22.83718;,
 -34.55930;16.11157;-0.00571;,
 -23.58121;16.11157;-22.84859;,
 17.25924;1.71287;-16.60205;,
 0.07326;1.71287;-24.30443;,
 25.23528;1.71287;-0.00572;,
 17.25924;1.71287;16.59060;,
 0.07326;-4.81036;58.73431;,
 -17.11272;1.71287;16.59061;,
 -25.08875;1.71287;-0.00571;,
 -17.11272;1.71287;-16.60204;,
 0.07326;-2.27230;-0.00572;;
 
 42;
 3;0,1,2;,
 3;0,2,3;,
 4;2,1,4,5;,
 4;1,0,6,4;,
 4;0,3,7,8;,
 4;3,2,5,7;,
 4;5,4,9,10;,
 4;4,6,11,9;,
 4;6,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,8,18,17;,
 4;8,7,19,18;,
 4;7,5,10,19;,
 4;10,9,20,21;,
 4;9,11,22,20;,
 4;11,13,23,22;,
 4;13,15,24,23;,
 4;15,17,25,24;,
 4;17,18,26,25;,
 4;18,19,27,26;,
 4;19,10,21,27;,
 4;21,20,28,29;,
 4;20,22,30,28;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,25,33,32;,
 4;25,26,34,33;,
 4;26,27,35,34;,
 4;27,21,29,35;,
 3;0,8,16;,
 3;0,12,6;,
 3;0,14,12;,
 3;0,16,14;,
 3;36,31,32;,
 3;36,32,33;,
 3;36,28,30;,
 3;36,29,28;,
 3;36,35,29;,
 3;36,34,35;,
 3;36,30,31;,
 3;36,33,34;;
 
 MeshMaterialList {
  4;
  42;
  1,
  1,
  0,
  1,
  1,
  0,
  3,
  1,
  1,
  1,
  1,
  1,
  1,
  3,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
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
  41;
  -0.000000;0.922029;-0.387121;,
  0.254763;0.918685;-0.301850;,
  -0.000000;0.999683;0.025156;,
  -0.254763;0.918685;-0.301850;,
  -0.000000;0.714516;-0.699619;,
  0.474227;0.735092;-0.484508;,
  0.621393;0.783487;0.004282;,
  0.430417;0.786084;0.443636;,
  0.000000;0.792042;0.610467;,
  -0.430416;0.786085;0.443636;,
  -0.621393;0.783487;0.004282;,
  -0.474227;0.735092;-0.484508;,
  -0.000000;0.278301;-0.960494;,
  0.670691;0.273457;-0.689489;,
  0.958067;0.286545;-0.000000;,
  0.670691;0.273457;0.689489;,
  0.000000;0.278301;0.960494;,
  -0.670690;0.273457;0.689490;,
  -0.958067;0.286545;0.000000;,
  -0.670691;0.273457;-0.689489;,
  -0.000000;-0.286925;-0.957953;,
  0.668973;-0.281981;-0.687722;,
  0.955365;-0.295428;-0.000000;,
  0.743703;-0.145017;0.652592;,
  0.000000;-0.014353;0.999897;,
  -0.743702;-0.145017;0.652593;,
  -0.955365;-0.295429;0.000000;,
  -0.668973;-0.281981;-0.687722;,
  -0.000000;-0.842251;-0.539086;,
  0.381186;-0.836948;-0.392703;,
  0.528780;-0.848759;-0.000000;,
  0.771177;-0.275686;0.573832;,
  0.693479;-0.015124;0.720318;,
  -0.771177;-0.275686;0.573832;,
  -0.528780;-0.848759;0.000000;,
  -0.381186;-0.836948;-0.392703;,
  -0.000000;-0.998659;-0.051761;,
  -0.693479;-0.015123;0.720318;,
  0.210512;-0.977448;0.016717;,
  0.000000;-0.999068;-0.043168;,
  -0.210512;-0.977448;0.016717;;
  42;
  3;2,1,0;,
  3;2,0,3;,
  4;0,1,5,4;,
  4;1,2,6,5;,
  4;2,3,11,10;,
  4;3,0,4,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,9,17,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,4,12,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,17,25,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,12,20,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,25,33,37;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,20,28,35;,
  3;2,10,9;,
  3;2,7,6;,
  3;2,8,7;,
  3;2,9,8;,
  3;36,38,39;,
  3;36,39,40;,
  3;36,29,30;,
  3;36,28,29;,
  3;36,35,28;,
  3;36,34,35;,
  3;36,30,38;,
  3;36,40,34;;
 }
}
