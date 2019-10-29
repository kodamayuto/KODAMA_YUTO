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
 84;
 -50.21195;26.70326;-1.73210;,
 44.59514;26.70326;-1.73210;,
 44.59514;20.19199;-1.73210;,
 -50.21195;20.19199;-1.73210;,
 44.59514;26.70326;-1.73210;,
 44.59514;26.70326;1.77600;,
 44.59514;20.19199;1.77600;,
 44.59514;20.19199;-1.73210;,
 44.59514;26.70326;1.77600;,
 -50.21195;26.70326;1.77600;,
 -50.21195;20.19199;1.77600;,
 44.59514;20.19199;1.77600;,
 -50.21195;26.70326;1.77600;,
 -50.21195;26.70326;-1.73210;,
 -50.21195;20.19199;-1.73210;,
 -50.21195;20.19199;1.77600;,
 44.59514;26.70326;-1.73210;,
 -50.21195;26.70326;-1.73210;,
 -50.21195;20.19199;-1.73210;,
 44.59514;20.19199;-1.73210;,
 -43.23787;19.95079;-1.73210;,
 51.56917;19.95079;-1.73210;,
 51.56917;13.43950;-1.73210;,
 -43.23787;13.43950;-1.73210;,
 51.56917;19.95079;-1.73210;,
 51.56917;19.95079;1.77600;,
 51.56917;13.43950;1.77600;,
 51.56917;13.43950;-1.73210;,
 51.56917;19.95079;1.77600;,
 -43.23787;19.95079;1.77600;,
 -43.23787;13.43950;1.77600;,
 51.56917;13.43950;1.77600;,
 -43.23787;19.95079;1.77600;,
 -43.23787;19.95079;-1.73210;,
 -43.23787;13.43950;-1.73210;,
 -43.23787;13.43950;1.77600;,
 51.56917;19.95079;-1.73210;,
 -43.23787;19.95079;-1.73210;,
 -43.23787;13.43950;-1.73210;,
 51.56917;13.43950;-1.73210;,
 -51.14186;13.25367;-1.73210;,
 43.66523;13.25367;-1.73210;,
 43.66523;6.74240;-1.73210;,
 -51.14186;6.74240;-1.73210;,
 43.66523;13.25367;-1.73210;,
 43.66523;13.25367;1.77600;,
 43.66523;6.74240;1.77600;,
 43.66523;6.74240;-1.73210;,
 43.66523;13.25367;1.77600;,
 -51.14186;13.25367;1.77600;,
 -51.14186;6.74240;1.77600;,
 43.66523;6.74240;1.77600;,
 -51.14186;13.25367;1.77600;,
 -51.14186;13.25367;-1.73210;,
 -51.14186;6.74240;-1.73210;,
 -51.14186;6.74240;1.77600;,
 43.66523;13.25367;-1.73210;,
 -51.14186;13.25367;-1.73210;,
 -51.14186;6.74240;-1.73210;,
 43.66523;6.74240;-1.73210;,
 -46.49247;6.55656;-1.73210;,
 48.31468;6.55656;-1.73210;,
 48.31468;0.04529;-1.73210;,
 -46.49247;0.04529;-1.73210;,
 48.31468;6.55656;-1.73210;,
 48.31468;6.55656;1.77600;,
 48.31468;0.04529;1.77600;,
 48.31468;0.04529;-1.73210;,
 48.31468;6.55656;1.77600;,
 -46.49247;6.55656;1.77600;,
 -46.49247;0.04529;1.77600;,
 48.31468;0.04529;1.77600;,
 -46.49247;6.55656;1.77600;,
 -46.49247;6.55656;-1.73210;,
 -46.49247;0.04529;-1.73210;,
 -46.49247;0.04529;1.77600;,
 48.31468;6.55656;-1.73210;,
 -46.49247;6.55656;-1.73210;,
 -46.49247;0.04529;-1.73210;,
 48.31468;0.04529;-1.73210;,
 -39.79186;25.46684;-1.80145;,
 38.99090;28.22424;-1.80145;,
 39.92047;1.66415;-1.80145;,
 -38.86225;-1.09321;-1.80145;;
 
 25;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;52,45,56,57;,
 4;58,59,46,55;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;72,65,76,77;,
 4;78,79,66,75;,
 4;80,81,82,83;;
 
 MeshMaterialList {
  2;
  25;
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
  1;;
  Material {
   0.643200;0.530400;0.320000;1.000000;;
   5.000000;
   0.150000;0.150000;0.150000;;
   0.096480;0.079560;0.048000;;
   TextureFilename {
    "data/TEXTURE/wood.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/GAMEOVER001.png";
   }
  }
 }
 MeshNormals {
  25;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;;
  25;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;;
 }
 MeshTextureCoords {
  84;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}
