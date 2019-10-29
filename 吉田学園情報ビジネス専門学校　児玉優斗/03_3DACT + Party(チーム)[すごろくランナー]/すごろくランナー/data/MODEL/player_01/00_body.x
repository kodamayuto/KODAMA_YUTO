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
 79;
 4.38487;15.23115;-0.00033;,
 3.09868;15.23115;3.10482;,
 5.69968;-0.00209;5.70583;,
 8.06325;-0.00209;-0.00033;,
 -0.00648;15.24195;4.39102;,
 -0.00648;-0.00209;8.06939;,
 -3.11163;15.23115;3.10482;,
 -5.71264;-0.00209;5.70582;,
 -4.39783;15.23115;-0.00033;,
 -8.07621;-0.00209;-0.00033;,
 -3.11163;15.23115;-3.10549;,
 -5.71264;-0.00209;-5.70649;,
 -0.00648;14.65790;-4.39168;,
 -0.00648;-0.00209;-8.07006;,
 3.09867;15.23115;-3.10549;,
 5.69968;-0.00209;-5.70649;,
 4.38487;15.23115;-0.00033;,
 8.06325;-0.00209;-0.00033;,
 -0.00648;14.65790;-0.00033;,
 -0.00648;14.65790;-0.00033;,
 -0.00648;14.65790;-0.00033;,
 -0.00648;14.65790;-0.00033;,
 -0.00648;14.65790;-0.00033;,
 -0.00648;14.65790;-0.00033;,
 -0.00648;14.65790;-0.00033;,
 -0.00648;14.65790;-0.00033;,
 -0.00648;-0.00209;-0.00033;,
 -0.00648;-0.00209;-0.00033;,
 -0.00648;-0.00209;-0.00033;,
 -0.00648;-0.00209;-0.00033;,
 -0.00648;-0.00209;-0.00033;,
 -0.00648;-0.00209;-0.00033;,
 -0.00648;-0.00209;-0.00033;,
 -0.00648;-0.00209;-0.00033;,
 -4.70118;13.99454;-0.00033;,
 -3.32953;14.11958;3.58805;,
 -5.32863;12.76288;-3.58872;,
 0.04244;14.06035;4.91566;,
 -2.44486;13.80581;-5.54935;,
 5.50120;12.72062;-3.36530;,
 2.38521;13.97932;-4.70466;,
 3.35396;14.09273;3.62206;,
 4.74378;14.12309;-0.00396;,
 4.74378;14.12309;-0.00396;,
 5.50120;12.72062;-3.36530;,
 1.26837;14.15221;-4.51165;,
 0.90097;14.12567;-4.55370;,
 0.86881;-0.11323;-8.18916;,
 1.23621;-0.08666;-8.34560;,
 0.00952;14.11469;-4.48201;,
 -0.02264;-0.12419;-8.11747;,
 -0.88378;14.12573;-4.53705;,
 -0.91594;-0.11315;-8.17251;,
 -1.25565;14.22463;-4.50133;,
 -1.28782;-0.08654;-8.32205;,
 -0.88825;14.35510;-4.44605;,
 -0.92042;-0.05997;-8.47848;,
 0.00320;14.66326;-4.34571;,
 -0.02897;-0.04901;-8.55017;,
 0.89650;14.40020;-4.40976;,
 0.86433;-0.06006;-8.49514;,
 1.26837;14.15221;-4.51165;,
 1.23621;-0.08666;-8.34560;,
 0.00636;14.15228;-4.51310;,
 0.00636;14.15228;-4.51310;,
 0.00636;14.15228;-4.51310;,
 0.00636;14.15228;-4.51310;,
 0.00636;14.15228;-4.51310;,
 0.00636;14.15228;-4.51310;,
 0.00636;14.15228;-4.51310;,
 0.00636;14.15228;-4.51310;,
 -0.02580;-0.08661;-8.33383;,
 -0.02580;-0.08661;-8.33383;,
 -0.02580;-0.08661;-8.33383;,
 -0.02580;-0.08661;-8.33383;,
 -0.02580;-0.08661;-8.33383;,
 -0.02580;-0.08661;-8.33383;,
 -0.02580;-0.08661;-8.33383;,
 -0.02580;-0.08661;-8.33383;;
 
 56;
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
 3;26,3,2;,
 3;27,2,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;,
 4;6,8,34,35;,
 4;8,10,36,34;,
 4;6,35,37,4;,
 4;12,38,36,10;,
 4;14,39,40,12;,
 4;0,1,41,42;,
 4;1,4,37,41;,
 4;16,43,44,14;,
 4;45,46,47,48;,
 4;46,49,50,47;,
 4;49,51,52,50;,
 4;51,53,54,52;,
 4;53,55,56,54;,
 4;55,57,58,56;,
 4;57,59,60,58;,
 4;59,61,62,60;,
 3;63,46,45;,
 3;64,49,46;,
 3;65,51,49;,
 3;66,53,51;,
 3;67,55,53;,
 3;68,57,55;,
 3;69,59,57;,
 3;70,61,59;,
 3;71,48,47;,
 3;72,47,50;,
 3;73,50,52;,
 3;74,52,54;,
 3;75,54,56;,
 3;76,56,58;,
 3;77,58,60;,
 3;78,60,62;;
 
 MeshMaterialList {
  10;
  56;
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
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  8,
  8,
  8,
  8,
  8,
  8,
  9,
  8;;
  Material {
   0.583770;0.406290;0.317550;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.080520;0.056040;0.043800;;
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
   0.699480;0.289710;0.160080;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.096480;0.039960;0.022080;;
  }
  Material {
   0.699480;0.474150;0.321030;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.096480;0.065400;0.044280;;
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
   0.457176;0.317294;0.249059;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.063059;0.043765;0.034353;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  65;
  0.000000;0.999446;-0.033284;,
  0.940832;0.337880;0.025919;,
  0.673693;0.317862;0.667159;,
  -0.001006;0.338973;0.940796;,
  -0.679580;0.299029;0.669890;,
  -0.949207;0.313444;0.027551;,
  -0.675062;0.464278;-0.573356;,
  -0.001765;0.528020;-0.849230;,
  0.661010;0.442834;-0.605775;,
  0.972062;0.234724;-0.000000;,
  0.687480;0.234685;0.687236;,
  -0.000003;0.234678;0.972073;,
  -0.687484;0.234652;0.687244;,
  -0.972062;0.234724;0.000000;,
  -0.680593;0.236887;-0.693310;,
  0.000000;0.235604;-0.971849;,
  0.680593;0.236887;-0.693310;,
  0.000000;-1.000000;-0.000000;,
  -0.001982;0.437867;0.899038;,
  -0.668582;0.362216;0.649460;,
  -0.919990;0.388163;0.054295;,
  -0.626309;0.657443;-0.418934;,
  -0.331968;0.772606;-0.541181;,
  0.609447;0.623039;-0.490303;,
  0.325679;0.668506;-0.668605;,
  0.899058;0.434852;0.050986;,
  0.654886;0.398504;0.642121;,
  -0.008595;-0.444848;0.895565;,
  0.054675;-0.520193;0.852297;,
  0.084274;-0.477051;0.874826;,
  0.009050;0.219277;0.975621;,
  -0.081466;-0.067184;0.994409;,
  -0.068921;-0.332783;0.940481;,
  -0.105850;0.266752;-0.957935;,
  0.001800;0.272708;-0.962095;,
  0.094595;0.268361;-0.958663;,
  0.156834;-0.251141;0.955160;,
  0.118854;-0.249129;0.961150;,
  0.009055;-0.247392;0.968873;,
  -0.121697;-0.247989;0.961088;,
  -0.180331;-0.248340;0.951740;,
  -0.001644;-0.985239;-0.171178;,
  -0.090314;0.991585;-0.092744;,
  -0.129442;0.991587;0.000000;,
  0.000000;0.991271;-0.131838;,
  0.090314;0.991586;-0.092745;,
  0.129442;0.991587;-0.000000;,
  0.155510;0.987471;0.026789;,
  0.000000;1.000000;0.000000;,
  -0.155510;0.987471;0.026789;,
  -0.177483;0.260094;-0.949132;,
  0.151616;0.262766;-0.952873;,
  0.007077;0.637604;0.770332;,
  0.053835;0.639026;0.767299;,
  -0.005685;-0.336392;0.941705;,
  -0.011464;-0.311352;0.950225;,
  -0.012338;-0.346658;0.937910;,
  -0.001636;-0.985239;-0.171178;,
  -0.001641;-0.985246;-0.171135;,
  -0.001640;-0.985252;-0.171104;,
  -0.001643;-0.985243;-0.171156;,
  -0.001653;-0.985232;-0.171217;,
  -0.001654;-0.985232;-0.171220;,
  -0.001648;-0.985233;-0.171213;,
  -0.001638;-0.985235;-0.171201;;
  56;
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  3;0,42,43;,
  3;0,44,42;,
  3;0,45,44;,
  3;0,46,45;,
  3;0,47,46;,
  3;0,48,47;,
  3;0,49,48;,
  3;0,43,49;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  4;4,5,20,19;,
  4;5,6,21,20;,
  4;4,19,18,3;,
  4;7,22,21,6;,
  4;8,23,24,7;,
  4;1,2,26,25;,
  4;2,3,18,26;,
  4;1,25,23,8;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;50,33,33,50;,
  4;33,34,34,33;,
  4;34,35,35,34;,
  4;35,51,51,35;,
  3;27,29,28;,
  3;52,30,53;,
  3;52,31,30;,
  3;27,32,31;,
  3;27,54,32;,
  3;27,55,54;,
  3;27,56,55;,
  3;27,28,56;,
  3;41,57,58;,
  3;41,58,59;,
  3;41,59,60;,
  3;41,60,61;,
  3;41,61,62;,
  3;41,62,63;,
  3;41,63,64;,
  3;41,64,57;;
 }
 MeshTextureCoords {
  79;
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
  0.500000;0.000000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.250000;0.000000;,
  0.750000;0.000000;,
  0.875000;0.000000;,
  0.750000;0.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.972250;0.000000;,
  0.937500;0.000000;,
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
  0.937500;1.000000;;
 }
}
