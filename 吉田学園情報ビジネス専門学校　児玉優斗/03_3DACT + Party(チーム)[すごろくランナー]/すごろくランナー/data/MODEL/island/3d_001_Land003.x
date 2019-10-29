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
 193;
 0.00000;29.74762;0.00000;,
 22.64644;27.09296;-39.22476;,
 0.00000;27.09296;-45.29288;,
 0.00000;29.74762;0.00000;,
 39.22476;27.09296;-22.64644;,
 0.00000;29.74762;0.00000;,
 45.29288;27.09296;0.00000;,
 0.00000;29.74762;0.00000;,
 39.22476;27.09296;22.64644;,
 0.00000;29.74762;0.00000;,
 22.64644;27.09296;39.22476;,
 0.00000;29.74762;0.00000;,
 0.00000;27.09296;45.29288;,
 0.00000;29.74762;0.00000;,
 -22.64644;27.09296;39.22476;,
 0.00000;29.74762;0.00000;,
 -39.22476;27.09296;22.64644;,
 0.00000;29.74762;0.00000;,
 -45.29288;27.09296;0.00004;,
 0.00000;29.74762;0.00000;,
 -39.22476;27.09296;-22.64640;,
 0.00000;29.74762;0.00000;,
 -22.64648;27.09296;-39.22476;,
 0.00000;29.74762;0.00000;,
 0.00000;27.09296;-45.29288;,
 41.84516;19.53318;-72.47794;,
 0.00000;19.53318;-83.69032;,
 72.47794;19.53318;-41.84516;,
 83.69032;19.53318;0.00000;,
 72.47794;19.53318;41.84516;,
 41.84516;19.53318;75.03900;,
 0.00000;19.53318;86.25138;,
 -41.84514;19.53318;75.03900;,
 -72.47790;19.53318;41.84516;,
 -83.69032;19.53318;0.00004;,
 -72.47794;19.53318;-41.84510;,
 -41.84520;19.53318;-72.47790;,
 0.00000;19.53318;-83.69032;,
 54.67336;8.21916;-94.69696;,
 0.00000;8.21916;-109.34671;,
 94.69696;8.21916;-54.67334;,
 109.53168;8.21916;-0.69028;,
 94.51200;8.21916;55.36364;,
 54.67336;8.21916;97.25804;,
 0.00000;8.21916;111.90774;,
 -54.67330;8.21916;97.25804;,
 -94.69696;8.21916;54.67336;,
 -109.34671;8.21916;0.00004;,
 -94.69696;8.21916;-54.67326;,
 -54.67336;8.21916;-94.69688;,
 0.00000;8.21916;-109.34671;,
 59.17798;-5.12668;-102.49937;,
 0.00000;-5.12668;-118.35595;,
 102.49937;-5.12668;-59.17792;,
 118.35595;-5.12668;-0.00000;,
 102.49937;-5.12668;59.17798;,
 59.17798;-5.12668;105.06040;,
 0.00004;-5.12668;120.91702;,
 -59.17792;-5.12668;105.06040;,
 -102.49937;-5.12668;59.17798;,
 -118.35595;-5.12668;0.00006;,
 -102.49938;-5.12668;-59.17790;,
 -59.17800;-5.12668;-102.49928;,
 0.00000;-5.12668;-118.35595;,
 -0.68200;56.71136;-33.23622;,
 10.88390;56.71136;-30.74364;,
 16.81496;31.95264;-33.82952;,
 -0.68200;31.95264;-37.60030;,
 24.56106;56.71136;-24.72600;,
 37.50584;27.18312;-24.72600;,
 10.88390;56.71136;-18.70836;,
 16.81496;31.95264;-15.62250;,
 -0.68200;56.71136;-16.21578;,
 -0.68200;31.95264;-11.85170;,
 -12.24790;56.71136;-18.70836;,
 -18.17896;31.95264;-15.62250;,
 -25.92506;56.71136;-24.72600;,
 -38.86984;27.18312;-24.72600;,
 -12.24790;56.71136;-30.74364;,
 -18.17896;31.95264;-33.82952;,
 -0.68200;56.71136;-33.23622;,
 -0.68200;31.95264;-37.60030;,
 -0.68200;56.71136;-24.72600;,
 -0.68200;56.71136;-24.72600;,
 -0.68200;56.71136;-24.72600;,
 -0.68200;56.71136;-24.72600;,
 -0.68200;56.71136;-24.72600;,
 -0.68200;56.71136;-24.72600;,
 -0.68200;56.71136;-24.72600;,
 -0.68200;56.71136;-24.72600;,
 -0.68200;31.95264;-24.72600;,
 -0.68200;31.95264;-24.72600;,
 -0.68200;31.95264;-24.72600;,
 -0.68200;31.95264;-24.72600;,
 -0.68200;31.95264;-24.72600;,
 -0.68200;31.95264;-24.72600;,
 -0.68200;31.95264;-24.72600;,
 -0.68200;31.95264;-24.72600;,
 -0.68200;135.73803;-41.12600;,
 6.93946;135.73803;-39.24748;,
 6.93946;30.13802;-39.24748;,
 -0.68200;30.13802;-41.12600;,
 12.81494;135.73803;-34.04226;,
 12.81494;30.13802;-34.04226;,
 15.59842;135.73803;-26.70280;,
 15.59842;30.13802;-26.70280;,
 14.65226;135.73803;-18.91048;,
 14.65226;30.13802;-18.91048;,
 10.19322;135.73803;-12.45042;,
 10.19322;30.13802;-12.45042;,
 3.24278;135.73803;-8.80256;,
 3.24278;30.13802;-8.80256;,
 -4.60678;135.73803;-8.80256;,
 -4.60678;30.13802;-8.80256;,
 -11.55722;135.73803;-12.45042;,
 -11.55722;30.13802;-12.45042;,
 -16.01626;135.73803;-18.91048;,
 -16.01626;30.13802;-18.91048;,
 -16.96242;135.73803;-26.70280;,
 -16.96242;30.13802;-26.70280;,
 -14.17894;135.73803;-34.04226;,
 -14.17894;30.13802;-34.04226;,
 -8.30346;135.73803;-39.24748;,
 -8.30346;30.13802;-39.24748;,
 -0.68200;135.73803;-41.12600;,
 -0.68200;30.13802;-41.12600;,
 -0.68200;135.73803;-24.72600;,
 -0.68200;135.73803;-24.72600;,
 -0.68200;135.73803;-24.72600;,
 -0.68200;135.73803;-24.72600;,
 -0.68200;135.73803;-24.72600;,
 -0.68200;135.73803;-24.72600;,
 -0.68200;135.73803;-24.72600;,
 -0.68200;135.73803;-24.72600;,
 -0.68200;135.73803;-24.72600;,
 -0.68200;135.73803;-24.72600;,
 -0.68200;135.73803;-24.72600;,
 -0.68200;135.73803;-24.72600;,
 -0.68200;135.73803;-24.72600;,
 -0.68200;30.13802;-24.72600;,
 -0.68200;30.13802;-24.72600;,
 -0.68200;30.13802;-24.72600;,
 -0.68200;30.13802;-24.72600;,
 -0.68200;30.13802;-24.72600;,
 -0.68200;30.13802;-24.72600;,
 -0.68200;30.13802;-24.72600;,
 -0.68200;30.13802;-24.72600;,
 -0.68200;30.13802;-24.72600;,
 -0.68200;30.13802;-24.72600;,
 -0.68200;30.13802;-24.72600;,
 -0.68200;30.13802;-24.72600;,
 -0.68200;30.13802;-24.72600;,
 -0.68200;136.22454;-42.70222;,
 -0.68200;171.87954;-24.88706;,
 7.59712;136.22454;-40.66160;,
 -0.68200;171.87954;-24.88706;,
 13.97958;136.22454;-35.00722;,
 -0.68200;171.87954;-24.88706;,
 17.00326;136.22454;-27.03442;,
 -0.68200;171.87954;-24.88706;,
 15.97546;136.22454;-18.56970;,
 -0.68200;171.87954;-24.88706;,
 11.13164;136.22454;-11.55222;,
 -0.68200;171.87954;-24.88706;,
 3.58144;136.22454;-7.58958;,
 -0.68200;171.87954;-24.88706;,
 -4.94544;136.22454;-7.58958;,
 -0.68200;171.87954;-24.88706;,
 -12.49564;136.22454;-11.55222;,
 -0.68200;171.87954;-24.88706;,
 -17.33946;136.22454;-18.56970;,
 -0.68200;171.87954;-24.88706;,
 -18.36726;136.22454;-27.03442;,
 -0.68200;171.87954;-24.88706;,
 -15.34358;136.22454;-35.00722;,
 -0.68200;171.87954;-24.88706;,
 -8.96110;136.22454;-40.66160;,
 -0.68200;171.87954;-24.88706;,
 -0.68200;136.22454;-42.70222;,
 -0.68200;136.22454;-24.88706;,
 -0.68200;136.22454;-42.70222;,
 7.59712;136.22454;-40.66160;,
 13.97958;136.22454;-35.00722;,
 17.00326;136.22454;-27.03442;,
 15.97546;136.22454;-18.56970;,
 11.13164;136.22454;-11.55222;,
 3.58144;136.22454;-7.58958;,
 -4.94544;136.22454;-7.58958;,
 -12.49564;136.22454;-11.55222;,
 -17.33946;136.22454;-18.56970;,
 -18.36726;136.22454;-27.03442;,
 -15.34358;136.22454;-35.00722;,
 -8.96110;136.22454;-40.66160;;
 
 137;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,16;,
 3;19,20,18;,
 3;21,22,20;,
 3;23,24,22;,
 4;2,1,25,26;,
 4;1,4,27,25;,
 4;4,6,28,27;,
 4;6,8,29,28;,
 4;8,10,30,29;,
 4;10,12,31,30;,
 4;12,14,32,31;,
 4;14,16,33,32;,
 4;16,18,34,33;,
 4;18,20,35,34;,
 4;20,22,36,35;,
 4;22,24,37,36;,
 4;26,25,38,39;,
 4;25,27,40,38;,
 4;27,28,41,40;,
 4;28,29,42,41;,
 4;29,30,43,42;,
 4;30,31,44,43;,
 4;31,32,45,44;,
 4;32,33,46,45;,
 4;33,34,47,46;,
 4;34,35,48,47;,
 4;35,36,49,48;,
 4;36,37,50,49;,
 4;39,38,51,52;,
 4;38,40,53,51;,
 4;40,41,54,53;,
 4;41,42,55,54;,
 4;42,43,56,55;,
 4;43,44,57,56;,
 4;44,45,58,57;,
 4;45,46,59,58;,
 4;46,47,60,59;,
 4;47,48,61,60;,
 4;48,49,62,61;,
 4;49,50,63,62;,
 4;64,65,66,67;,
 4;65,68,69,66;,
 4;68,70,71,69;,
 4;70,72,73,71;,
 4;72,74,75,73;,
 4;74,76,77,75;,
 4;76,78,79,77;,
 4;78,80,81,79;,
 3;82,65,64;,
 3;83,68,65;,
 3;84,70,68;,
 3;85,72,70;,
 3;86,74,72;,
 3;87,76,74;,
 3;88,78,76;,
 3;89,80,78;,
 3;90,67,66;,
 3;91,66,69;,
 3;92,69,71;,
 3;93,71,73;,
 3;94,73,75;,
 3;95,75,77;,
 3;96,77,79;,
 3;97,79,81;,
 4;98,99,100,101;,
 4;99,102,103,100;,
 4;102,104,105,103;,
 4;104,106,107,105;,
 4;106,108,109,107;,
 4;108,110,111,109;,
 4;110,112,113,111;,
 4;112,114,115,113;,
 4;114,116,117,115;,
 4;116,118,119,117;,
 4;118,120,121,119;,
 4;120,122,123,121;,
 4;122,124,125,123;,
 3;126,99,98;,
 3;127,102,99;,
 3;128,104,102;,
 3;129,106,104;,
 3;130,108,106;,
 3;131,110,108;,
 3;132,112,110;,
 3;133,114,112;,
 3;134,116,114;,
 3;135,118,116;,
 3;136,120,118;,
 3;137,122,120;,
 3;138,124,122;,
 3;139,101,100;,
 3;140,100,103;,
 3;141,103,105;,
 3;142,105,107;,
 3;143,107,109;,
 3;144,109,111;,
 3;145,111,113;,
 3;146,113,115;,
 3;147,115,117;,
 3;148,117,119;,
 3;149,119,121;,
 3;150,121,123;,
 3;151,123,125;,
 3;152,153,154;,
 3;154,155,156;,
 3;156,157,158;,
 3;158,159,160;,
 3;160,161,162;,
 3;162,163,164;,
 3;164,165,166;,
 3;166,167,168;,
 3;168,169,170;,
 3;170,171,172;,
 3;172,173,174;,
 3;174,175,176;,
 3;176,177,178;,
 3;179,180,181;,
 3;179,181,182;,
 3;179,182,183;,
 3;179,183,184;,
 3;179,184,185;,
 3;179,185,186;,
 3;179,186,187;,
 3;179,187,188;,
 3;179,188,189;,
 3;179,189,190;,
 3;179,190,191;,
 3;179,191,192;,
 3;179,192,180;;
 
 MeshMaterialList {
  5;
  137;
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
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
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
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
  Material {
   0.047200;0.731200;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.724800;0.624000;0.357600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.269600;0.269600;0.269600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.088000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.094400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  101;
  -0.000000;1.000000;0.000000;,
  -0.000000;0.992019;-0.126092;,
  0.063046;0.992019;-0.109199;,
  0.109199;0.992019;-0.063046;,
  0.126092;0.992019;0.000000;,
  0.109281;0.992090;0.061760;,
  0.062341;0.992519;0.104976;,
  -0.000000;0.992749;0.120207;,
  -0.062341;0.992519;0.104976;,
  -0.109281;0.992090;0.061760;,
  -0.126092;0.992019;0.000000;,
  -0.109199;0.992019;-0.063046;,
  -0.063046;0.992019;-0.109199;,
  -0.000000;0.953962;-0.299926;,
  0.149963;0.953962;-0.259744;,
  0.258955;0.954157;-0.150088;,
  0.299148;0.954207;-0.000143;,
  0.261615;0.954111;0.145702;,
  0.151234;0.955637;0.252756;,
  -0.000000;0.955734;0.294233;,
  -0.151936;0.955462;0.252999;,
  -0.262316;0.953885;0.145924;,
  -0.299926;0.953963;0.000000;,
  -0.259744;0.953962;-0.149963;,
  -0.149963;0.953962;-0.259744;,
  -0.000000;0.768993;-0.639257;,
  0.319629;0.768993;-0.553613;,
  0.554326;0.767888;-0.321044;,
  0.640260;0.768157;-0.001171;,
  0.560312;0.766868;0.312993;,
  0.327504;0.769296;0.548566;,
  -0.000000;0.768993;0.639257;,
  -0.327496;0.770389;0.547035;,
  -0.559955;0.767718;0.311544;,
  -0.639257;0.768993;0.000000;,
  -0.553613;0.768993;-0.319628;,
  -0.319629;0.768993;-0.553612;,
  -0.000001;0.559511;-0.828823;,
  0.414411;0.559511;-0.717782;,
  0.719775;0.555511;-0.416331;,
  0.831289;0.555837;-0.001978;,
  0.725990;0.554400;0.406914;,
  0.425426;0.557172;0.713143;,
  -0.000000;0.559511;0.828823;,
  -0.424542;0.561064;0.710614;,
  -0.724778;0.557990;0.404158;,
  -0.828823;0.559511;0.000000;,
  -0.717781;0.559512;-0.414411;,
  -0.414411;0.559512;-0.717781;,
  0.000000;1.000000;0.000000;,
  0.000000;0.173588;-0.984818;,
  0.312189;0.184869;-0.931859;,
  0.412970;0.197684;-0.889031;,
  0.312189;0.184868;0.931859;,
  0.000000;0.173588;0.984818;,
  -0.312189;0.184868;0.931859;,
  -0.412969;0.197684;0.889032;,
  -0.312189;0.184869;-0.931859;,
  0.000000;-1.000000;0.000000;,
  0.412969;0.197684;0.889032;,
  -0.412970;0.197684;-0.889031;,
  0.000000;-1.000000;0.000000;,
  -0.060810;-0.991283;-0.116877;,
  -0.123933;-0.992291;0.000000;,
  -0.060810;-0.991283;0.116878;,
  0.060810;-0.991283;0.116878;,
  0.123933;-0.992291;0.000000;,
  0.060810;-0.991283;-0.116877;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.464723;0.000000;-0.885456;,
  0.822984;0.000000;-0.568064;,
  0.992709;0.000000;-0.120536;,
  0.935017;0.000000;0.354604;,
  0.663123;0.000000;0.748511;,
  0.239315;0.000000;0.970942;,
  -0.239315;0.000000;0.970942;,
  -0.663123;0.000000;0.748511;,
  -0.935017;0.000000;0.354604;,
  -0.992709;0.000000;-0.120536;,
  -0.822984;0.000000;-0.568064;,
  -0.464723;0.000000;-0.885456;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;0.446966;-0.894551;,
  0.415719;0.446966;-0.792085;,
  0.736202;0.446966;-0.508162;,
  0.888029;0.446966;-0.107826;,
  0.836420;0.446966;0.317212;,
  0.593197;0.446966;0.669581;,
  0.214080;0.446966;0.868557;,
  -0.214080;0.446966;0.868557;,
  -0.593197;0.446966;0.669581;,
  -0.836420;0.446966;0.317212;,
  -0.888029;0.446966;-0.107826;,
  -0.736201;0.446966;-0.508163;,
  -0.415719;0.446966;-0.792086;,
  0.716744;0.491445;-0.494732;,
  0.000000;-1.000000;-0.000000;,
  0.208422;0.491445;0.845602;,
  -0.864559;0.491445;-0.104976;,
  -0.215316;0.436482;-0.873569;;
  137;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,9,8;,
  3;0,10,9;,
  3;0,11,10;,
  3;0,12,11;,
  3;0,1,12;,
  4;1,2,14,13;,
  4;2,3,15,14;,
  4;3,4,16,15;,
  4;4,5,17,16;,
  4;5,6,18,17;,
  4;6,7,19,18;,
  4;7,8,20,19;,
  4;8,9,21,20;,
  4;9,10,22,21;,
  4;10,11,23,22;,
  4;11,12,24,23;,
  4;12,1,13,24;,
  4;13,14,26,25;,
  4;14,15,27,26;,
  4;15,16,28,27;,
  4;16,17,29,28;,
  4;17,18,30,29;,
  4;18,19,31,30;,
  4;19,20,32,31;,
  4;20,21,33,32;,
  4;21,22,34,33;,
  4;22,23,35,34;,
  4;23,24,36,35;,
  4;24,13,25,36;,
  4;25,26,38,37;,
  4;26,27,39,38;,
  4;27,28,40,39;,
  4;28,29,41,40;,
  4;29,30,42,41;,
  4;30,31,43,42;,
  4;31,32,44,43;,
  4;32,33,45,44;,
  4;33,34,46,45;,
  4;34,35,47,46;,
  4;35,36,48,47;,
  4;36,25,37,48;,
  4;50,51,51,50;,
  4;51,52,52,51;,
  4;59,53,53,59;,
  4;53,54,54,53;,
  4;54,55,55,54;,
  4;55,56,56,55;,
  4;60,57,57,60;,
  4;57,50,50,57;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;49,49,49;,
  3;58,61,62;,
  3;58,62,63;,
  3;58,63,64;,
  3;58,64,61;,
  3;58,61,65;,
  3;58,65,66;,
  3;58,66,67;,
  3;58,67,61;,
  4;69,70,70,69;,
  4;70,71,71,70;,
  4;71,72,72,71;,
  4;72,73,73,72;,
  4;73,74,74,73;,
  4;74,75,75,74;,
  4;75,76,76,75;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;79,80,80,79;,
  4;80,81,81,80;,
  4;81,69,69,81;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;68,68,68;,
  3;82,82,82;,
  3;82,82,82;,
  3;82,82,82;,
  3;82,82,82;,
  3;82,82,82;,
  3;82,82,82;,
  3;82,82,82;,
  3;82,82,82;,
  3;82,82,82;,
  3;82,82,82;,
  3;82,82,82;,
  3;82,82,82;,
  3;82,82,82;,
  3;83,96,84;,
  3;84,96,85;,
  3;85,96,86;,
  3;86,96,87;,
  3;87,98,88;,
  3;88,98,89;,
  3;89,98,90;,
  3;90,98,91;,
  3;91,99,92;,
  3;92,99,93;,
  3;93,99,94;,
  3;94,99,95;,
  3;95,100,83;,
  3;97,97,97;,
  3;97,97,97;,
  3;97,97,97;,
  3;97,97,97;,
  3;97,97,97;,
  3;97,97,97;,
  3;97,97,97;,
  3;97,97,97;,
  3;97,97,97;,
  3;97,97,97;,
  3;97,97,97;,
  3;97,97,97;,
  3;97,97,97;;
 }
 MeshTextureCoords {
  193;
  0.041670;0.000000;,
  0.083330;0.125000;,
  0.000000;0.125000;,
  0.125000;0.000000;,
  0.166670;0.125000;,
  0.208330;0.000000;,
  0.250000;0.125000;,
  0.291670;0.000000;,
  0.333330;0.125000;,
  0.375000;0.000000;,
  0.416670;0.125000;,
  0.458330;0.000000;,
  0.500000;0.125000;,
  0.541670;0.000000;,
  0.583330;0.125000;,
  0.625000;0.000000;,
  0.666670;0.125000;,
  0.708330;0.000000;,
  0.750000;0.125000;,
  0.791670;0.000000;,
  0.833330;0.125000;,
  0.875000;0.000000;,
  0.916670;0.125000;,
  0.958330;0.000000;,
  1.000000;0.125000;,
  0.083330;0.250000;,
  0.000000;0.250000;,
  0.166670;0.250000;,
  0.250000;0.250000;,
  0.333330;0.250000;,
  0.416670;0.250000;,
  0.500000;0.250000;,
  0.583330;0.250000;,
  0.666670;0.250000;,
  0.750000;0.250000;,
  0.833330;0.250000;,
  0.916670;0.250000;,
  1.000000;0.250000;,
  0.083330;0.375000;,
  0.000000;0.375000;,
  0.166670;0.375000;,
  0.250000;0.375000;,
  0.333330;0.375000;,
  0.416670;0.375000;,
  0.500000;0.375000;,
  0.583330;0.375000;,
  0.666670;0.375000;,
  0.750000;0.375000;,
  0.833330;0.375000;,
  0.916670;0.375000;,
  1.000000;0.375000;,
  0.083330;0.500000;,
  0.000000;0.500000;,
  0.166670;0.500000;,
  0.250000;0.500000;,
  0.333330;0.500000;,
  0.416670;0.500000;,
  0.500000;0.500000;,
  0.583330;0.500000;,
  0.666670;0.500000;,
  0.750000;0.500000;,
  0.833330;0.500000;,
  0.916670;0.500000;,
  1.000000;0.500000;,
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
  0.000000;0.000000;,
  0.076920;0.000000;,
  0.076920;1.000000;,
  0.000000;1.000000;,
  0.153850;0.000000;,
  0.153850;1.000000;,
  0.230770;0.000000;,
  0.230770;1.000000;,
  0.307690;0.000000;,
  0.307690;1.000000;,
  0.384620;0.000000;,
  0.384620;1.000000;,
  0.461540;0.000000;,
  0.461540;1.000000;,
  0.538460;0.000000;,
  0.538460;1.000000;,
  0.615380;0.000000;,
  0.615380;1.000000;,
  0.692310;0.000000;,
  0.692310;1.000000;,
  0.769230;0.000000;,
  0.769230;1.000000;,
  0.846150;0.000000;,
  0.846150;1.000000;,
  0.923080;0.000000;,
  0.923080;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.038460;0.000000;,
  0.115380;0.000000;,
  0.192310;0.000000;,
  0.269230;0.000000;,
  0.346150;0.000000;,
  0.423080;0.000000;,
  0.500000;0.000000;,
  0.576920;0.000000;,
  0.653850;0.000000;,
  0.730770;0.000000;,
  0.807690;0.000000;,
  0.884620;0.000000;,
  0.961540;0.000000;,
  0.038460;1.000000;,
  0.115380;1.000000;,
  0.192310;1.000000;,
  0.269230;1.000000;,
  0.346150;1.000000;,
  0.423080;1.000000;,
  0.500000;1.000000;,
  0.576920;1.000000;,
  0.653850;1.000000;,
  0.730770;1.000000;,
  0.807690;1.000000;,
  0.884620;1.000000;,
  0.961540;1.000000;,
  0.000000;1.000000;,
  0.038460;0.000000;,
  0.076920;1.000000;,
  0.076920;0.000000;,
  0.153850;1.000000;,
  0.115380;0.000000;,
  0.230770;1.000000;,
  0.153850;0.000000;,
  0.307690;1.000000;,
  0.192310;0.000000;,
  0.384620;1.000000;,
  0.230770;0.000000;,
  0.461540;1.000000;,
  0.269230;0.000000;,
  0.538460;1.000000;,
  0.307690;0.000000;,
  0.615380;1.000000;,
  0.346150;0.000000;,
  0.692310;1.000000;,
  0.384620;0.000000;,
  0.769230;1.000000;,
  0.423080;0.000000;,
  0.846150;1.000000;,
  0.461540;0.000000;,
  0.923080;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
