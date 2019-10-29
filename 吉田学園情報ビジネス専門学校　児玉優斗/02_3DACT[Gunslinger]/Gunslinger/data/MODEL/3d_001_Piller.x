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
 192;
 0.00000;7.82757;0.00000;,
 2.70598;7.74285;-2.70598;,
 0.00000;7.74285;-3.82683;,
 0.00000;7.82757;0.00000;,
 3.82683;7.74285;0.00000;,
 0.00000;7.82757;0.00000;,
 2.70598;7.74285;2.70598;,
 0.00000;7.82757;0.00000;,
 -0.00000;7.74285;3.82683;,
 0.00000;7.82757;0.00000;,
 -2.70598;7.74285;2.70598;,
 0.00000;7.82757;0.00000;,
 -3.82683;7.74285;-0.00000;,
 0.00000;7.82757;0.00000;,
 -2.70598;7.74285;-2.70598;,
 0.00000;7.82757;0.00000;,
 0.00000;7.74285;-3.82683;,
 5.00000;7.07107;-5.00000;,
 0.00000;7.07107;-7.07107;,
 7.07107;7.07107;0.00000;,
 5.00000;7.07107;5.00000;,
 -0.00000;7.07107;7.07107;,
 -5.00000;7.07107;5.00000;,
 -7.07107;7.07107;-0.00000;,
 -5.00000;7.07107;-5.00000;,
 0.00000;7.07107;-7.07107;,
 6.53281;3.82683;-6.53281;,
 0.00000;3.82683;-9.23879;,
 9.23879;3.82683;0.00000;,
 6.53281;3.82683;6.53281;,
 -0.00000;3.82683;9.23879;,
 -6.53282;3.82683;6.53281;,
 -9.23879;3.82683;-0.00000;,
 -6.53282;3.82683;-6.53281;,
 0.00000;3.82683;-9.23879;,
 7.07107;-0.00000;-7.07107;,
 0.00000;-0.00000;-10.00000;,
 10.00000;-0.00000;0.00000;,
 7.07107;-0.00000;7.07107;,
 -0.00000;-0.00000;10.00000;,
 -7.07107;-0.00000;7.07107;,
 -10.00000;-0.00000;-0.00000;,
 -7.07107;-0.00000;-7.07107;,
 0.00000;-0.00000;-10.00000;,
 6.53281;-0.12029;-6.53281;,
 0.00000;-0.12029;-9.23879;,
 9.23879;-0.12029;0.00000;,
 6.53281;-0.12029;6.53281;,
 -0.00000;-0.12029;9.23879;,
 -6.53282;-0.12029;6.53281;,
 -9.23879;-0.12029;-0.00000;,
 -6.53282;-0.12029;-6.53281;,
 0.00000;-0.12029;-9.23879;,
 5.00000;-0.14154;-5.00000;,
 0.00000;-0.14154;-7.07107;,
 7.07107;-0.14154;0.00000;,
 5.00000;-0.14154;5.00000;,
 -0.00000;-0.14154;7.07107;,
 -5.00000;-0.14154;5.00000;,
 -7.07107;-0.14154;-0.00000;,
 -5.00000;-0.14154;-5.00000;,
 0.00000;-0.14154;-7.07107;,
 2.70598;0.67002;-2.70598;,
 0.00000;0.67002;-3.82683;,
 3.82683;0.67002;0.00000;,
 2.70598;0.67002;2.70598;,
 -0.00000;0.67002;3.82683;,
 -2.70598;0.67002;2.70598;,
 -3.82683;0.67002;-0.00000;,
 -2.70598;0.67002;-2.70598;,
 0.00000;0.67002;-3.82683;,
 0.00000;1.13073;0.00000;,
 0.00000;1.13073;0.00000;,
 0.00000;1.13073;0.00000;,
 0.00000;1.13073;0.00000;,
 0.00000;1.13073;0.00000;,
 0.00000;1.13073;0.00000;,
 0.00000;1.13073;0.00000;,
 0.00000;1.13073;0.00000;,
 0.00000;75.79300;-3.80000;,
 2.68701;75.79300;-2.68701;,
 2.68701;5.79300;-2.68701;,
 0.00000;5.79300;-3.80000;,
 3.80000;75.79300;0.00000;,
 3.80000;5.79300;0.00000;,
 2.68701;75.79300;2.68701;,
 2.68701;5.79300;2.68701;,
 -0.00000;75.79300;3.80000;,
 -0.00000;5.79300;3.80000;,
 -2.68701;75.79300;2.68701;,
 -2.68701;5.79300;2.68701;,
 -3.80000;75.79300;-0.00000;,
 -3.80000;5.79300;-0.00000;,
 -2.68701;75.79300;-2.68701;,
 -2.68701;5.79300;-2.68701;,
 0.00000;75.79300;-3.80000;,
 0.00000;5.79300;-3.80000;,
 0.00000;75.79300;0.00000;,
 0.00000;75.79300;0.00000;,
 0.00000;75.79300;0.00000;,
 0.00000;75.79300;0.00000;,
 0.00000;75.79300;0.00000;,
 0.00000;75.79300;0.00000;,
 0.00000;75.79300;0.00000;,
 0.00000;75.79300;0.00000;,
 0.00000;5.79300;0.00000;,
 0.00000;5.79300;0.00000;,
 0.00000;5.79300;0.00000;,
 0.00000;5.79300;0.00000;,
 0.00000;5.79300;0.00000;,
 0.00000;5.79300;0.00000;,
 0.00000;5.79300;0.00000;,
 0.00000;5.79300;0.00000;,
 0.00000;74.60255;-0.00000;,
 0.00000;74.68728;3.82683;,
 -2.70598;74.68728;2.70598;,
 0.00000;74.60255;-0.00000;,
 -3.82683;74.68728;-0.00000;,
 0.00000;74.60255;-0.00000;,
 -2.70598;74.68728;-2.70598;,
 0.00000;74.60255;-0.00000;,
 0.00000;74.68728;-3.82683;,
 0.00000;74.60255;-0.00000;,
 2.70598;74.68728;-2.70598;,
 0.00000;74.60255;-0.00000;,
 3.82683;74.68728;-0.00000;,
 0.00000;74.60255;-0.00000;,
 2.70598;74.68728;2.70598;,
 0.00000;74.60255;-0.00000;,
 0.00000;74.68728;3.82683;,
 0.00000;75.35906;7.07107;,
 -5.00000;75.35906;5.00000;,
 -7.07107;75.35906;-0.00000;,
 -5.00000;75.35906;-5.00000;,
 0.00000;75.35906;-7.07107;,
 5.00000;75.35906;-5.00000;,
 7.07107;75.35906;-0.00000;,
 5.00000;75.35906;5.00000;,
 0.00000;75.35906;7.07107;,
 0.00000;78.60329;9.23879;,
 -6.53281;78.60329;6.53281;,
 -9.23879;78.60329;-0.00000;,
 -6.53281;78.60329;-6.53281;,
 0.00000;78.60329;-9.23879;,
 6.53282;78.60329;-6.53281;,
 9.23879;78.60329;0.00000;,
 6.53282;78.60329;6.53281;,
 0.00000;78.60329;9.23879;,
 0.00000;82.43013;10.00000;,
 -7.07107;82.43013;7.07107;,
 -10.00000;82.43013;-0.00000;,
 -7.07107;82.43013;-7.07107;,
 0.00000;82.43013;-10.00000;,
 7.07107;82.43013;-7.07107;,
 10.00000;82.43013;0.00000;,
 7.07107;82.43013;7.07107;,
 0.00000;82.43013;10.00000;,
 0.00000;82.55042;9.23879;,
 -6.53281;82.55042;6.53281;,
 -9.23879;82.55042;-0.00000;,
 -6.53281;82.55042;-6.53281;,
 0.00000;82.55042;-9.23879;,
 6.53282;82.55042;-6.53281;,
 9.23879;82.55042;0.00000;,
 6.53282;82.55042;6.53281;,
 0.00000;82.55042;9.23879;,
 0.00000;82.57167;7.07107;,
 -5.00000;82.57167;5.00000;,
 -7.07107;82.57167;0.00000;,
 -5.00000;82.57167;-5.00000;,
 0.00000;82.57167;-7.07107;,
 5.00000;82.57167;-5.00000;,
 7.07107;82.57167;0.00000;,
 5.00000;82.57167;5.00000;,
 0.00000;82.57167;7.07107;,
 0.00000;81.76010;3.82684;,
 -2.70598;81.76010;2.70598;,
 -3.82683;81.76010;0.00000;,
 -2.70598;81.76010;-2.70598;,
 0.00000;81.76010;-3.82683;,
 2.70598;81.76010;-2.70598;,
 3.82683;81.76010;0.00000;,
 2.70598;81.76010;2.70598;,
 0.00000;81.76010;3.82684;,
 0.00000;81.29940;0.00000;,
 0.00000;81.29940;0.00000;,
 0.00000;81.29940;0.00000;,
 0.00000;81.29940;0.00000;,
 0.00000;81.29940;0.00000;,
 0.00000;81.29940;0.00000;,
 0.00000;81.29940;0.00000;,
 0.00000;81.29940;0.00000;;
 
 152;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;27,26,35,36;,
 4;26,28,37,35;,
 4;28,29,38,37;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;36,35,44,45;,
 4;35,37,46,44;,
 4;37,38,47,46;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;45,44,53,54;,
 4;44,46,55,53;,
 4;46,47,56,55;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;54,53,62,63;,
 4;53,55,64,62;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 3;63,62,71;,
 3;62,64,72;,
 3;64,65,73;,
 3;65,66,74;,
 3;66,67,75;,
 3;67,68,76;,
 3;68,69,77;,
 3;69,70,78;,
 4;79,80,81,82;,
 4;80,83,84,81;,
 4;83,85,86,84;,
 4;85,87,88,86;,
 4;87,89,90,88;,
 4;89,91,92,90;,
 4;91,93,94,92;,
 4;93,95,96,94;,
 3;97,80,79;,
 3;98,83,80;,
 3;99,85,83;,
 3;100,87,85;,
 3;101,89,87;,
 3;102,91,89;,
 3;103,93,91;,
 3;104,95,93;,
 3;105,82,81;,
 3;106,81,84;,
 3;107,84,86;,
 3;108,86,88;,
 3;109,88,90;,
 3;110,90,92;,
 3;111,92,94;,
 3;112,94,96;,
 3;113,114,115;,
 3;116,115,117;,
 3;118,117,119;,
 3;120,119,121;,
 3;122,121,123;,
 3;124,123,125;,
 3;126,125,127;,
 3;128,127,129;,
 4;114,130,131,115;,
 4;115,131,132,117;,
 4;117,132,133,119;,
 4;119,133,134,121;,
 4;121,134,135,123;,
 4;123,135,136,125;,
 4;125,136,137,127;,
 4;127,137,138,129;,
 4;130,139,140,131;,
 4;131,140,141,132;,
 4;132,141,142,133;,
 4;133,142,143,134;,
 4;134,143,144,135;,
 4;135,144,145,136;,
 4;136,145,146,137;,
 4;137,146,147,138;,
 4;139,148,149,140;,
 4;140,149,150,141;,
 4;141,150,151,142;,
 4;142,151,152,143;,
 4;143,152,153,144;,
 4;144,153,154,145;,
 4;145,154,155,146;,
 4;146,155,156,147;,
 4;148,157,158,149;,
 4;149,158,159,150;,
 4;150,159,160,151;,
 4;151,160,161,152;,
 4;152,161,162,153;,
 4;153,162,163,154;,
 4;154,163,164,155;,
 4;155,164,165,156;,
 4;157,166,167,158;,
 4;158,167,168,159;,
 4;159,168,169,160;,
 4;160,169,170,161;,
 4;161,170,171,162;,
 4;162,171,172,163;,
 4;163,172,173,164;,
 4;164,173,174,165;,
 4;166,175,176,167;,
 4;167,176,177,168;,
 4;168,177,178,169;,
 4;169,178,179,170;,
 4;170,179,180,171;,
 4;171,180,181,172;,
 4;172,181,182,173;,
 4;173,182,183,174;,
 3;175,184,176;,
 3;176,185,177;,
 3;177,186,178;,
 3;178,187,179;,
 3;179,188,180;,
 3;180,189,181;,
 3;181,190,182;,
 3;182,191,183;;
 
 MeshMaterialList {
  2;
  152;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.116078;0.116078;0.116078;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.448627;0.448627;0.448627;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  142;
  -0.000000;1.000000;0.000000;,
  -0.000000;0.993622;-0.112761;,
  0.079734;0.993622;-0.079734;,
  0.112761;0.993622;0.000000;,
  0.079734;0.993622;0.079734;,
  -0.000000;0.993622;0.112761;,
  -0.079734;0.993622;0.079734;,
  -0.112761;0.993622;0.000000;,
  -0.079734;0.993622;-0.079734;,
  -0.000000;0.835250;-0.549870;,
  0.388817;0.835250;-0.388817;,
  0.549870;0.835250;0.000000;,
  0.388817;0.835250;0.388817;,
  -0.000000;0.835250;0.549870;,
  -0.388817;0.835250;0.388817;,
  -0.549870;0.835250;0.000000;,
  -0.388817;0.835250;-0.388817;,
  -0.000000;0.384551;-0.923104;,
  0.652733;0.384551;-0.652733;,
  0.923104;0.384551;0.000000;,
  0.652733;0.384551;0.652733;,
  -0.000000;0.384551;0.923104;,
  -0.652733;0.384551;0.652733;,
  -0.923104;0.384551;0.000000;,
  -0.652733;0.384551;-0.652733;,
  -0.000000;0.195090;-0.980785;,
  0.693520;0.195090;-0.693520;,
  0.980785;0.195090;0.000000;,
  0.693520;0.195090;0.693520;,
  -0.000000;0.195090;0.980785;,
  -0.693520;0.195090;0.693520;,
  -0.980785;0.195090;0.000000;,
  -0.693520;0.195090;-0.693520;,
  -0.000000;-0.996542;-0.083094;,
  0.058756;-0.996542;-0.058756;,
  0.083094;-0.996542;0.000000;,
  0.058756;-0.996542;0.058756;,
  -0.000000;-0.996542;0.083094;,
  -0.058756;-0.996542;0.058756;,
  -0.083094;-0.996542;-0.000000;,
  -0.058756;-0.996542;-0.058756;,
  0.000000;-0.993124;0.117070;,
  -0.082781;-0.993124;0.082781;,
  -0.117070;-0.993124;-0.000000;,
  -0.082781;-0.993124;-0.082781;,
  0.000000;-0.993124;-0.117069;,
  0.082781;-0.993124;-0.082781;,
  0.117070;-0.993124;0.000000;,
  0.082781;-0.993124;0.082781;,
  0.000000;-0.983420;0.181341;,
  -0.128227;-0.983420;0.128227;,
  -0.181341;-0.983420;-0.000000;,
  -0.128227;-0.983420;-0.128227;,
  0.000000;-0.983420;-0.181341;,
  0.128227;-0.983420;-0.128227;,
  0.181341;-0.983420;0.000000;,
  0.128227;-0.983420;0.128227;,
  0.000000;-1.000000;0.000000;,
  -0.000000;-0.987743;-0.156086;,
  0.110369;-0.987743;-0.110369;,
  0.156086;-0.987743;0.000000;,
  0.110369;-0.987743;0.110369;,
  -0.000000;-0.987743;0.156086;,
  -0.110369;-0.987743;0.110369;,
  -0.156086;-0.987743;-0.000000;,
  -0.110369;-0.987743;-0.110369;,
  0.000000;1.000000;0.000000;,
  -0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  -0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.993622;0.112761;,
  -0.079734;-0.993622;0.079734;,
  -0.112761;-0.993622;0.000000;,
  -0.079734;-0.993622;-0.079734;,
  0.000000;-0.993622;-0.112761;,
  0.079734;-0.993622;-0.079734;,
  0.112761;-0.993622;0.000000;,
  0.079734;-0.993622;0.079734;,
  0.000000;-0.835250;0.549870;,
  -0.388817;-0.835250;0.388817;,
  -0.549870;-0.835250;-0.000000;,
  -0.388817;-0.835250;-0.388817;,
  0.000000;-0.835250;-0.549870;,
  0.388817;-0.835250;-0.388817;,
  0.549870;-0.835250;-0.000000;,
  0.388817;-0.835250;0.388817;,
  0.000000;-0.384551;0.923104;,
  -0.652733;-0.384551;0.652733;,
  -0.923104;-0.384551;-0.000000;,
  -0.652733;-0.384551;-0.652733;,
  0.000000;-0.384551;-0.923104;,
  0.652733;-0.384551;-0.652733;,
  0.923104;-0.384551;-0.000000;,
  0.652733;-0.384551;0.652733;,
  0.000000;-0.195090;0.980785;,
  -0.693520;-0.195090;0.693520;,
  -0.980785;-0.195090;0.000000;,
  -0.693520;-0.195090;-0.693520;,
  0.000000;-0.195090;-0.980785;,
  0.693520;-0.195090;-0.693520;,
  0.980785;-0.195090;-0.000000;,
  0.693520;-0.195090;0.693520;,
  0.000000;0.996542;0.083095;,
  -0.058757;0.996542;0.058757;,
  -0.083095;0.996542;-0.000000;,
  -0.058757;0.996542;-0.058757;,
  0.000000;0.996542;-0.083095;,
  0.058757;0.996542;-0.058757;,
  0.083095;0.996542;0.000000;,
  0.058757;0.996542;0.058757;,
  0.000000;0.993124;-0.117070;,
  0.082781;0.993124;-0.082781;,
  0.117070;0.993124;0.000000;,
  0.082781;0.993124;0.082781;,
  -0.000000;0.993124;0.117070;,
  -0.082781;0.993124;0.082781;,
  -0.117070;0.993124;-0.000000;,
  -0.082781;0.993124;-0.082781;,
  -0.000000;0.983420;-0.181341;,
  0.128228;0.983420;-0.128228;,
  0.181341;0.983420;0.000000;,
  0.128228;0.983420;0.128228;,
  -0.000000;0.983420;0.181341;,
  -0.128228;0.983420;0.128228;,
  -0.181341;0.983420;-0.000000;,
  -0.128228;0.983420;-0.128228;,
  -0.000000;1.000000;-0.000000;,
  0.000000;0.987743;0.156086;,
  -0.110370;0.987743;0.110370;,
  -0.156086;0.987743;-0.000000;,
  -0.110370;0.987743;-0.110370;,
  0.000000;0.987743;-0.156086;,
  0.110370;0.987743;-0.110370;,
  0.156086;0.987743;0.000000;,
  0.110370;0.987743;0.110370;;
  152;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;58,59,34,33;,
  4;59,60,35,34;,
  4;60,61,36,35;,
  4;61,62,37,36;,
  4;62,63,38,37;,
  4;63,64,39,38;,
  4;64,65,40,39;,
  4;65,58,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;,
  4;67,68,68,67;,
  4;68,69,69,68;,
  4;69,70,70,69;,
  4;70,71,71,70;,
  4;71,72,72,71;,
  4;72,73,73,72;,
  4;73,74,74,73;,
  4;74,67,67,74;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;75,75,75;,
  3;75,75,75;,
  3;75,75,75;,
  3;75,75,75;,
  3;75,75,75;,
  3;75,75,75;,
  3;75,75,75;,
  3;75,75,75;,
  3;76,77,78;,
  3;76,78,79;,
  3;76,79,80;,
  3;76,80,81;,
  3;76,81,82;,
  3;76,82,83;,
  3;76,83,84;,
  3;76,84,77;,
  4;77,85,86,78;,
  4;78,86,87,79;,
  4;79,87,88,80;,
  4;80,88,89,81;,
  4;81,89,90,82;,
  4;82,90,91,83;,
  4;83,91,92,84;,
  4;84,92,85,77;,
  4;85,93,94,86;,
  4;86,94,95,87;,
  4;87,95,96,88;,
  4;88,96,97,89;,
  4;89,97,98,90;,
  4;90,98,99,91;,
  4;91,99,100,92;,
  4;92,100,93,85;,
  4;93,101,102,94;,
  4;94,102,103,95;,
  4;95,103,104,96;,
  4;96,104,105,97;,
  4;97,105,106,98;,
  4;98,106,107,99;,
  4;99,107,108,100;,
  4;100,108,101,93;,
  4;134,109,110,135;,
  4;135,110,111,136;,
  4;136,111,112,137;,
  4;137,112,113,138;,
  4;138,113,114,139;,
  4;139,114,115,140;,
  4;140,115,116,141;,
  4;141,116,109,134;,
  4;109,117,118,110;,
  4;110,118,119,111;,
  4;111,119,120,112;,
  4;112,120,121,113;,
  4;113,121,122,114;,
  4;114,122,123,115;,
  4;115,123,124,116;,
  4;116,124,117,109;,
  4;117,125,126,118;,
  4;118,126,127,119;,
  4;119,127,128,120;,
  4;120,128,129,121;,
  4;121,129,130,122;,
  4;122,130,131,123;,
  4;123,131,132,124;,
  4;124,132,125,117;,
  3;125,133,126;,
  3;126,133,127;,
  3;127,133,128;,
  3;128,133,129;,
  3;129,133,130;,
  3;130,133,131;,
  3;131,133,132;,
  3;132,133,125;;
 }
 MeshTextureCoords {
  192;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
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
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.062500;0.000000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
