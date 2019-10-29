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
 95;
 2.89641;-0.03458;0.02467;,
 2.04620;-0.03458;2.07725;,
 2.04620;-5.84018;2.07725;,
 2.89641;-5.84018;0.02467;,
 -0.00639;-0.03458;2.92747;,
 -0.00639;-5.84018;2.92747;,
 -2.05897;-0.03458;2.07725;,
 -2.05897;-5.84018;2.07725;,
 -2.90918;-0.03458;0.02467;,
 -2.90918;-5.84018;0.02467;,
 -2.05897;-0.03458;-2.02792;,
 -2.05897;-5.84018;-2.02792;,
 -0.00639;-0.03458;-2.87813;,
 -0.00639;-5.84018;-2.87813;,
 2.04620;-0.03458;-2.02792;,
 2.04620;-5.84018;-2.02792;,
 2.89641;-0.03458;0.02467;,
 2.89641;-5.84018;0.02467;,
 -0.00639;-0.03458;0.02467;,
 -0.00639;-0.03458;0.02467;,
 -0.00639;-0.03458;0.02467;,
 -0.00639;-0.03458;0.02467;,
 -0.00639;-0.03458;0.02467;,
 -0.00639;-0.03458;0.02467;,
 -0.00639;-0.03458;0.02467;,
 -0.00639;-0.03458;0.02467;,
 2.21671;-5.87788;2.24777;,
 3.13755;-5.87787;0.02467;,
 -0.00638;-5.87788;3.16860;,
 -2.22948;-5.87787;2.24777;,
 -3.15031;-5.87788;0.02467;,
 -2.22948;-5.87787;-2.19843;,
 -0.00638;-5.87788;-3.11926;,
 2.21671;-5.87788;-2.19843;,
 3.13755;-5.87787;0.02467;,
 2.21671;-7.50248;2.24776;,
 3.13755;-7.50248;0.02467;,
 -0.00638;-7.50248;0.02467;,
 -0.00638;-7.50248;3.16860;,
 -0.00638;-7.50248;0.02467;,
 -2.22948;-7.50248;2.24777;,
 -0.00638;-7.50248;0.02467;,
 -3.15031;-7.50248;0.02467;,
 -0.00638;-7.50248;0.02467;,
 -2.22948;-7.50248;-2.19843;,
 -0.00638;-7.50248;0.02467;,
 -0.00638;-7.50248;-3.11926;,
 -0.00638;-7.50248;0.02467;,
 2.21671;-7.50248;-2.19843;,
 -0.00638;-7.50248;0.02467;,
 3.13755;-7.50248;0.02467;,
 -0.00638;-7.50248;0.02467;,
 1.72431;-7.37034;0.02467;,
 1.22818;-7.37034;1.22242;,
 1.22818;-9.68928;1.22242;,
 1.72431;-9.68928;0.02467;,
 0.03043;-7.37034;1.71855;,
 0.03043;-9.68928;1.71855;,
 -1.16732;-7.37034;1.22242;,
 -1.16732;-9.68928;1.22242;,
 -1.66345;-7.37034;0.02467;,
 -1.66345;-9.68928;0.02467;,
 -1.16732;-7.37034;-1.17308;,
 -1.16732;-9.68928;-1.17308;,
 0.03043;-7.37034;-1.66921;,
 0.03043;-9.68928;-1.66921;,
 1.22818;-7.37034;-1.17308;,
 1.22818;-9.68928;-1.17308;,
 1.72431;-7.37034;0.02467;,
 1.72431;-9.68928;0.02467;,
 0.30268;-7.37034;0.02467;,
 0.30268;-7.37034;0.02467;,
 0.30268;-7.37034;0.02467;,
 0.30268;-7.37034;0.02467;,
 0.30268;-7.37034;0.02467;,
 0.30268;-7.37034;0.02467;,
 0.30268;-7.37034;0.02467;,
 0.30268;-7.37034;0.02467;,
 1.22818;-12.68928;1.22242;,
 1.72431;-12.68928;0.02467;,
 0.30268;-12.68928;0.02467;,
 0.03043;-12.68928;1.71855;,
 0.30268;-12.68928;0.02467;,
 -1.16732;-12.68928;1.22242;,
 0.30268;-12.68928;0.02467;,
 -1.66345;-12.68928;0.02467;,
 0.30268;-12.68928;0.02467;,
 -1.16732;-12.68928;-1.17308;,
 0.30268;-12.68928;0.02467;,
 0.03043;-12.68928;-1.66921;,
 0.30268;-12.68928;0.02467;,
 1.22818;-12.68928;-1.17308;,
 0.30268;-12.68928;0.02467;,
 1.72431;-12.68928;0.02467;,
 0.30268;-12.68928;0.02467;;
 
 72;
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
 4;26,27,3,2;,
 4;28,26,2,5;,
 4;29,28,5,7;,
 4;30,29,7,9;,
 4;31,30,9,11;,
 4;32,31,11,13;,
 4;33,32,13,15;,
 4;34,33,15,17;,
 4;35,36,27,26;,
 3;37,36,35;,
 4;38,35,26,28;,
 3;39,35,38;,
 4;40,38,28,29;,
 3;41,38,40;,
 4;42,40,29,30;,
 3;43,40,42;,
 4;44,42,30,31;,
 3;45,42,44;,
 4;46,44,31,32;,
 3;47,44,46;,
 4;48,46,32,33;,
 3;49,46,48;,
 4;50,48,33,34;,
 3;51,48,50;,
 4;52,53,54,55;,
 4;53,56,57,54;,
 4;56,58,59,57;,
 4;58,60,61,59;,
 4;60,62,63,61;,
 4;62,64,65,63;,
 4;64,66,67,65;,
 4;66,68,69,67;,
 3;70,53,52;,
 3;71,56,53;,
 3;72,58,56;,
 3;73,60,58;,
 3;74,62,60;,
 3;75,64,62;,
 3;76,66,64;,
 3;77,68,66;,
 4;78,79,55,54;,
 3;80,79,78;,
 4;81,78,54,57;,
 3;82,78,81;,
 4;83,81,57,59;,
 3;84,81,83;,
 4;85,83,59,61;,
 3;86,83,85;,
 4;87,85,61,63;,
 3;88,85,87;,
 4;89,87,63,65;,
 3;90,87,89;,
 4;91,89,65,67;,
 3;92,89,91;,
 4;93,91,67,69;,
 3;94,91,93;;
 
 MeshMaterialList {
  10;
  72;
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  6,
  2,
  6,
  2,
  6,
  2,
  6,
  2,
  6,
  2,
  6,
  2,
  6,
  2,
  6,
  2;;
  Material {
   0.699480;0.576810;0.348000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.096480;0.079560;0.048000;;
  }
  Material {
   0.107260;0.073160;0.000000;1.000000;;
   6.000000;
   0.090000;0.090000;0.090000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.680000;0.626960;0.466480;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.200000;0.184400;0.137200;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "�T����.jpg";
   }
  }
  Material {
   0.508080;0.419340;0.252300;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.070080;0.057840;0.034800;;
  }
  Material {
   0.378706;0.631176;0.610706;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.052235;0.087059;0.084235;;
  }
  Material {
   0.552000;0.552000;0.552000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.320760;0.000000;0.072900;1.000000;;
   7.000000;
   1.000000;1.000000;1.000000;;
   0.194040;0.000000;0.044100;;
  }
  Material {
   0.658471;0.781294;0.818824;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.090824;0.107765;0.112941;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  43;
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000001;,
  0.707108;0.000000;0.707106;,
  -0.000001;0.000000;1.000000;,
  -0.707108;0.000000;0.707105;,
  -1.000000;0.000000;0.000001;,
  -0.707107;0.000000;-0.707106;,
  -0.000001;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  0.154445;0.988001;-0.000001;,
  0.109213;0.988000;0.109220;,
  0.000005;0.988000;0.154456;,
  -0.109210;0.988001;0.109210;,
  -0.154449;0.988001;-0.000000;,
  -0.109212;0.988001;-0.109213;,
  0.000004;0.987999;-0.154460;,
  0.109214;0.987999;-0.109222;,
  1.000000;-0.000001;0.000000;,
  0.707106;-0.000002;0.707107;,
  0.000002;-0.000002;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000001;0.000000;-1.000000;,
  0.707106;0.000000;-0.707108;,
  0.000000;-1.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;-0.000000;,
  -0.000000;0.000000;1.000000;,
  -1.000000;0.000000;-0.000000;,
  -0.707107;0.000000;-0.707107;,
  -0.000000;0.000000;-1.000000;,
  1.000000;0.000000;-0.000000;,
  -0.000000;0.000000;1.000000;,
  -1.000000;0.000000;-0.000000;,
  -0.000000;0.000000;-1.000000;;
  72;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;10,9,9,10;,
  4;11,10,10,11;,
  4;12,11,11,12;,
  4;13,12,12,13;,
  4;14,13,13,14;,
  4;15,14,14,15;,
  4;16,15,15,16;,
  4;9,16,16,9;,
  4;18,17,17,18;,
  3;25,25,25;,
  4;19,18,18,19;,
  3;25,25,25;,
  4;20,19,19,20;,
  3;25,25,25;,
  4;21,20,20,21;,
  3;25,25,25;,
  4;22,21,21,22;,
  3;25,25,25;,
  4;23,22,22,23;,
  3;25,25,25;,
  4;24,23,23,24;,
  3;25,25,25;,
  4;17,24,24,17;,
  3;25,25,25;,
  4;26,27,27,34;,
  4;27,28,35,27;,
  4;28,29,29,35;,
  4;29,30,36,29;,
  4;30,31,37,36;,
  4;31,32,38,37;,
  4;32,33,33,38;,
  4;33,26,34,33;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;27,39,34,27;,
  3;25,25,25;,
  4;40,27,27,35;,
  3;25,25,25;,
  4;29,40,35,29;,
  3;25,25,25;,
  4;41,29,29,36;,
  3;25,25,25;,
  4;37,41,36,37;,
  3;25,25,25;,
  4;42,37,37,38;,
  3;25,25,25;,
  4;33,42,38,33;,
  3;25,25,25;,
  4;39,33,33,34;,
  3;25,25,25;;
 }
 MeshTextureCoords {
  95;
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
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  1.000000;1.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.062500;1.000000;,
  0.250000;1.000000;,
  0.187500;1.000000;,
  0.375000;1.000000;,
  0.312500;1.000000;,
  0.500000;1.000000;,
  0.437500;1.000000;,
  0.625000;1.000000;,
  0.562500;1.000000;,
  0.750000;1.000000;,
  0.687500;1.000000;,
  0.875000;1.000000;,
  0.812500;1.000000;,
  1.000000;1.000000;,
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
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.062500;1.000000;,
  0.250000;1.000000;,
  0.187500;1.000000;,
  0.375000;1.000000;,
  0.312500;1.000000;,
  0.500000;1.000000;,
  0.437500;1.000000;,
  0.625000;1.000000;,
  0.562500;1.000000;,
  0.750000;1.000000;,
  0.687500;1.000000;,
  0.875000;1.000000;,
  0.812500;1.000000;,
  1.000000;1.000000;,
  0.937500;1.000000;;
 }
}
