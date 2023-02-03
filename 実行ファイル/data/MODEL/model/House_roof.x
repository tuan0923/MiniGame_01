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
 7;
 480.27263;4.21277;-500.47917;,
 -0.55794;344.21211;-19.64554;,
 480.27248;4.21277;461.18639;,
 -0.55794;344.21211;-19.64554;,
 -481.39039;4.21277;461.18639;,
 -481.39039;4.21277;461.18639;,
 480.27263;4.21277;-500.47917;;
 
 4;
 3;0,1,2;,
 3;2,3,4;,
 3;1,2,5;,
 3;2,1,6;;
 
 MeshMaterialList {
  13;
  4;
  10,
  10,
  10,
  10;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\MiniGame\\������\\logHouse\\Tex\\Wood_Floor.jpg";
   }
  }
  Material {
   0.599200;0.599200;0.599200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.668000;0.668000;0.668000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.279200;0.417600;0.558400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.181480;0.271440;0.362960;;
  }
  Material {
   0.213600;0.213600;0.213600;1.000000;;
   6.000000;
   0.380000;0.380000;0.380000;;
   0.048060;0.048060;0.048060;;
  }
  Material {
   0.571200;0.432800;0.210400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.392700;0.297550;0.144650;;
  }
  Material {
   0.524000;0.376800;0.153600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.353700;0.254340;0.103680;;
  }
  Material {
   0.404800;0.664800;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.111320;0.182820;0.220000;;
  }
  Material {
   0.000000;0.684000;0.800000;1.000000;;
   5.000000;
   0.460000;0.460000;0.460000;;
   0.000000;0.649800;0.760000;;
  }
  Material {
   0.341600;0.357600;0.357600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.004270;0.004470;0.004470;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.600000;0.600000;0.600000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\MiniGame\\������\\logHouse\\Tex\\Wood_Floor.jpg";
   }
  }
  Material {
   0.800000;0.574400;0.344800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.550000;0.394900;0.237050;;
   TextureFilename {
    "C:\\Users\\student\\Pictures\\Saved Pictures\\wood01.jpg";
   }
  }
  Material {
   0.800000;0.561600;0.320000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Pictures\\Saved Pictures\\wood01.jpg";
   }
  }
 }
 MeshNormals {
  6;
  0.577351;0.816496;0.000000;,
  0.316228;0.894427;0.316228;,
  0.000000;0.816497;0.577350;,
  -0.316228;-0.894427;-0.316228;,
  0.000000;-0.816497;-0.577350;,
  -0.577351;-0.816496;-0.000000;;
  4;
  3;0,1,1;,
  3;1,1,2;,
  3;3,3,4;,
  3;3,3,5;;
 }
 MeshTextureCoords {
  7;
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
