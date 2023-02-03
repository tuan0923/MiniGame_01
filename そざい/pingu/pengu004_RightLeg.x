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
 288;
 -0.35677;-2.25615;-18.34513;,
 0.39471;-2.15296;-18.14203;,
 0.43440;-2.25190;-18.14571;,
 0.28199;-2.06469;-18.13687;,
 0.10724;-1.99577;-18.13075;,
 -0.11239;-1.95289;-18.12417;,
 -0.35539;-1.94031;-18.11789;,
 -0.59805;-1.95920;-18.11247;,
 -0.81656;-2.00777;-18.10848;,
 -0.98955;-2.08121;-18.10623;,
 -1.10004;-2.17238;-18.10600;,
 -1.13728;-2.27231;-18.10781;,
 -1.09758;-2.37125;-18.11147;,
 -0.98488;-2.45950;-18.11664;,
 -0.81013;-2.52844;-18.12278;,
 -0.59051;-2.57131;-18.12932;,
 -0.34748;-2.58389;-18.13561;,
 -0.10484;-2.56500;-18.14103;,
 0.11368;-2.51644;-18.14507;,
 0.28665;-2.44299;-18.14731;,
 0.39717;-2.35183;-18.14752;,
 1.12403;-2.06617;-17.51109;,
 1.20170;-2.25972;-17.51824;,
 0.90351;-1.89350;-17.50097;,
 0.56169;-1.75865;-17.48896;,
 0.13203;-1.67480;-17.47614;,
 -0.34339;-1.65018;-17.46385;,
 -0.81810;-1.68714;-17.45323;,
 -1.24553;-1.78212;-17.44535;,
 -1.58392;-1.92581;-17.44098;,
 -1.80015;-2.10415;-17.44055;,
 -1.87296;-2.29965;-17.44410;,
 -1.79531;-2.49321;-17.45126;,
 -1.57481;-2.66586;-17.46137;,
 -1.23297;-2.80072;-17.47339;,
 -0.80332;-2.88456;-17.48619;,
 -0.32788;-2.90920;-17.49851;,
 0.14679;-2.87222;-17.50911;,
 0.57423;-2.77724;-17.51699;,
 0.91261;-2.63355;-17.52137;,
 1.12884;-2.45523;-17.52180;,
 1.79933;-1.99956;-16.47981;,
 1.91154;-2.27928;-16.49018;,
 1.48067;-1.75006;-16.46521;,
 0.98669;-1.55519;-16.44781;,
 0.36575;-1.43403;-16.42933;,
 -0.32129;-1.39839;-16.41152;,
 -1.00725;-1.45187;-16.39622;,
 -1.62498;-1.58911;-16.38483;,
 -2.11399;-1.79674;-16.37851;,
 -2.42645;-2.05445;-16.37789;,
 -2.53173;-2.33699;-16.38302;,
 -2.41954;-2.61670;-16.39338;,
 -2.10084;-2.86620;-16.40798;,
 -1.60687;-3.06110;-16.42537;,
 -0.98593;-3.18225;-16.44386;,
 -0.29887;-3.21788;-16.46165;,
 0.38710;-3.16442;-16.47698;,
 1.00482;-3.02718;-16.48835;,
 1.49384;-2.81951;-16.49467;,
 1.80627;-2.56181;-16.49528;,
 2.39110;-1.95608;-15.09333;,
 2.53296;-2.30973;-15.10641;,
 1.98818;-1.64062;-15.07485;,
 1.36364;-1.39424;-15.05286;,
 0.57861;-1.24104;-15.02951;,
 -0.29006;-1.19602;-15.00699;,
 -1.15734;-1.26359;-14.98763;,
 -1.93835;-1.43712;-14.97322;,
 -2.55661;-1.69965;-14.96525;,
 -2.95162;-2.02548;-14.96446;,
 -3.08473;-2.38269;-14.97093;,
 -2.94287;-2.73632;-14.98404;,
 -2.53996;-3.05178;-15.00249;,
 -1.91541;-3.29818;-15.02449;,
 -1.13039;-3.45138;-15.04784;,
 -0.26171;-3.49638;-15.07035;,
 0.60559;-3.42883;-15.08974;,
 1.38657;-3.25528;-15.10412;,
 2.00486;-2.99275;-15.11210;,
 2.39986;-2.66693;-15.11288;,
 2.87345;-1.93760;-13.41219;,
 3.03878;-2.34972;-13.42746;,
 2.40391;-1.56999;-13.39069;,
 1.67610;-1.28286;-13.36505;,
 0.76125;-1.10432;-13.33781;,
 -0.25105;-1.05187;-13.31163;,
 -1.26175;-1.13060;-13.28903;,
 -2.17190;-1.33284;-13.27224;,
 -2.89239;-1.63878;-13.26295;,
 -3.35271;-2.01847;-13.26204;,
 -3.50782;-2.43476;-13.26958;,
 -3.34251;-2.84686;-13.28485;,
 -2.87296;-3.21448;-13.30636;,
 -2.14516;-3.50160;-13.33198;,
 -1.23031;-3.68015;-13.35924;,
 -0.21802;-3.73260;-13.38542;,
 0.79269;-3.65388;-13.40802;,
 1.70282;-3.45163;-13.42478;,
 2.42334;-3.14569;-13.43410;,
 2.88367;-2.76599;-13.43501;,
 3.22533;-1.94496;-11.50989;,
 3.40686;-2.39753;-11.52665;,
 2.70967;-1.54125;-11.48628;,
 1.91041;-1.22592;-11.45813;,
 0.90572;-1.02985;-11.42821;,
 -0.20597;-0.97224;-11.39944;,
 -1.31591;-1.05871;-11.37464;,
 -2.31540;-1.28080;-11.35623;,
 -3.10664;-1.61679;-11.34602;,
 -3.61218;-2.03377;-11.34499;,
 -3.78250;-2.49091;-11.35328;,
 -3.60096;-2.94347;-11.37005;,
 -3.08532;-3.34719;-11.39367;,
 -2.28606;-3.66251;-11.42181;,
 -1.28139;-3.85858;-11.45174;,
 -0.16968;-3.91619;-11.48049;,
 0.94024;-3.82972;-11.50531;,
 1.93976;-3.60763;-11.52371;,
 2.73100;-3.27164;-11.53393;,
 3.23654;-2.85466;-11.53494;,
 3.43130;-1.97778;-9.46956;,
 3.62114;-2.45106;-9.48710;,
 2.89209;-1.55563;-9.44489;,
 2.05630;-1.22590;-9.41546;,
 1.00571;-1.02088;-9.38415;,
 -0.15681;-0.96062;-9.35408;,
 -1.31744;-1.05105;-9.32812;,
 -2.36265;-1.28329;-9.30888;,
 -3.19004;-1.63463;-9.29822;,
 -3.71869;-2.07065;-9.29713;,
 -3.89678;-2.54870;-9.30582;,
 -3.70694;-3.02196;-9.32334;,
 -3.16776;-3.44412;-9.34805;,
 -2.33196;-3.77385;-9.37745;,
 -1.28139;-3.97887;-9.40876;,
 -0.11885;-4.03912;-9.43882;,
 1.04180;-3.94870;-9.46479;,
 2.08699;-3.71645;-9.48401;,
 2.91439;-3.36513;-9.49470;,
 3.44303;-2.92910;-9.49577;,
 3.48243;-2.03468;-7.38040;,
 3.67226;-2.50794;-7.39793;,
 2.94321;-1.61252;-7.35570;,
 2.10741;-1.28279;-7.32630;,
 1.05683;-1.07776;-7.29498;,
 -0.10568;-1.01751;-7.26492;,
 -1.26634;-1.10793;-7.23893;,
 -2.31152;-1.34019;-7.21973;,
 -3.13892;-1.69151;-7.20904;,
 -3.66754;-2.12755;-7.20797;,
 -3.84567;-2.60559;-7.21664;,
 -3.65583;-3.07886;-7.23419;,
 -3.11662;-3.50101;-7.25886;,
 -2.28083;-3.83074;-7.28828;,
 -1.23024;-4.03576;-7.31959;,
 -0.06773;-4.09601;-7.34966;,
 1.09291;-4.00559;-7.37561;,
 2.13811;-3.77334;-7.39486;,
 2.96551;-3.42201;-7.40552;,
 3.49415;-2.98600;-7.40660;,
 3.37644;-2.11316;-5.33368;,
 3.55799;-2.56574;-5.35047;,
 2.86078;-1.70946;-5.31011;,
 2.06151;-1.39414;-5.28196;,
 1.05685;-1.19806;-5.25200;,
 -0.05485;-1.14044;-5.22321;,
 -1.16478;-1.22692;-5.19844;,
 -2.16429;-1.44902;-5.18004;,
 -2.95553;-1.78500;-5.16983;,
 -3.46107;-2.20197;-5.16879;,
 -3.63139;-2.65913;-5.17709;,
 -3.44985;-3.11168;-5.19387;,
 -2.93420;-3.51540;-5.21746;,
 -2.13494;-3.83073;-5.24562;,
 -1.13026;-4.02679;-5.27553;,
 -0.01857;-4.08440;-5.30430;,
 1.09137;-3.99794;-5.32912;,
 2.09087;-3.77584;-5.34752;,
 2.88212;-3.43985;-5.35772;,
 3.38766;-3.02287;-5.35873;,
 3.11799;-2.20977;-3.41889;,
 3.28328;-2.62189;-3.43415;,
 2.64844;-1.84217;-3.39737;,
 1.92061;-1.55503;-3.37175;,
 1.00577;-1.37649;-3.34447;,
 -0.00653;-1.32403;-3.31830;,
 -1.01722;-1.40276;-3.29570;,
 -1.92737;-1.60501;-3.27895;,
 -2.64786;-1.91096;-3.26965;,
 -3.10818;-2.29064;-3.26872;,
 -3.26329;-2.70692;-3.27628;,
 -3.09799;-3.11904;-3.29155;,
 -2.62844;-3.48665;-3.31303;,
 -1.90063;-3.77378;-3.33866;,
 -0.98581;-3.95232;-3.36592;,
 0.02651;-4.00477;-3.39210;,
 1.03720;-3.92605;-3.41470;,
 1.94735;-3.72380;-3.43148;,
 2.66787;-3.41786;-3.44075;,
 3.12820;-3.03817;-3.44171;,
 2.71834;-2.32031;-1.71966;,
 2.86020;-2.67396;-1.73276;,
 2.31542;-2.00487;-1.70122;,
 1.69087;-1.75847;-1.67921;,
 0.90585;-1.60527;-1.65587;,
 0.03717;-1.56024;-1.63334;,
 -0.83012;-1.62781;-1.61398;,
 -1.61112;-1.80136;-1.59962;,
 -2.22940;-2.06391;-1.59161;,
 -2.62441;-2.38970;-1.59082;,
 -2.75751;-2.74693;-1.59730;,
 -2.61564;-3.10056;-1.61041;,
 -2.21273;-3.41602;-1.62886;,
 -1.58818;-3.66241;-1.65085;,
 -0.80315;-3.81561;-1.67422;,
 0.06552;-3.86063;-1.69672;,
 0.93281;-3.79307;-1.71608;,
 1.71381;-3.61952;-1.73048;,
 2.33207;-3.35698;-1.73846;,
 2.72709;-3.03116;-1.73923;,
 2.19500;-2.43995;-0.31030;,
 2.30720;-2.71966;-0.32064;,
 1.87629;-2.19044;-0.29569;,
 1.38234;-1.99554;-0.27831;,
 0.76142;-1.87439;-0.25983;,
 -1.22936;-2.02946;-0.21536;,
 -0.61163;-1.89223;-0.22673;,
 -1.71838;-2.23713;-0.20903;,
 -2.03082;-2.49483;-0.20840;,
 -2.13609;-2.77737;-0.21352;,
 -2.02388;-3.05708;-0.22388;,
 -1.70519;-3.30658;-0.23848;,
 -1.21123;-3.50146;-0.25587;,
 -0.59030;-3.62261;-0.27437;,
 0.09677;-3.65825;-0.29212;,
 0.78273;-3.60478;-0.30747;,
 1.40048;-3.46754;-0.31885;,
 1.88948;-3.25990;-0.32518;,
 2.20192;-3.00219;-0.32581;,
 1.56650;-2.56344;0.62437;,
 1.64416;-2.75699;0.61721;,
 1.34597;-2.39078;0.63448;,
 1.00415;-2.25593;0.64648;,
 0.57450;-2.17208;0.65931;,
 0.07435;-1.83877;-0.24204;,
 0.09907;-2.14743;0.67161;,
 -0.37565;-2.18442;0.68220;,
 -0.80309;-2.27940;0.69007;,
 -1.14146;-2.42309;0.69446;,
 -1.35769;-2.60142;0.69487;,
 -1.43051;-2.79692;0.69135;,
 -1.35287;-2.99048;0.68416;,
 -1.13237;-3.16314;0.67405;,
 -0.79053;-3.29799;0.66201;,
 -0.36086;-3.38184;0.64922;,
 0.11456;-3.40646;0.63693;,
 0.58924;-3.36950;0.62634;,
 1.01672;-3.27452;0.61843;,
 1.35511;-3.13083;0.61407;,
 1.57131;-2.95250;0.61365;,
 0.85460;-2.99359;0.87945;,
 0.89429;-3.09252;0.87576;,
 0.74188;-2.90531;0.88462;,
 0.56717;-2.83639;0.89073;,
 0.34753;-2.79353;0.89729;,
 0.10449;-2.78094;0.90357;,
 -0.13815;-2.79983;0.90901;,
 -0.35665;-2.84839;0.91304;,
 -0.52962;-2.92183;0.91525;,
 -0.64014;-3.01300;0.91548;,
 -0.67737;-3.11294;0.91367;,
 -0.63769;-2.90368;0.91001;,
 -0.52497;-2.99194;0.90484;,
 -0.35022;-3.06088;0.89867;,
 -0.13062;-3.10374;0.89213;,
 0.11243;-3.11635;0.88586;,
 0.35507;-3.09743;0.88044;,
 0.57357;-3.04888;0.87641;,
 0.74656;-2.97542;0.87420;,
 0.85706;-2.88426;0.87397;,
 0.11381;-3.10869;1.11311;,
 0.01880;0.69370;-1.18160;,
 1.03440;0.65058;-1.20768;,
 0.88998;0.38145;0.18836;,
 0.05598;0.41517;0.20969;,
 -0.99544;0.62421;-1.15871;,
 -0.77694;0.35980;0.22855;;
 
 306;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,9,8;,
 3;0,10,9;,
 3;0,11,10;,
 3;0,12,11;,
 3;0,13,12;,
 3;0,14,13;,
 3;0,15,14;,
 3;0,16,15;,
 3;0,17,16;,
 3;0,18,17;,
 3;0,19,18;,
 3;0,20,19;,
 3;0,2,20;,
 4;2,1,21,22;,
 4;1,3,23,21;,
 4;3,4,24,23;,
 4;4,5,25,24;,
 4;5,6,26,25;,
 4;6,7,27,26;,
 4;7,8,28,27;,
 4;8,9,29,28;,
 4;9,10,30,29;,
 4;10,11,31,30;,
 4;11,12,32,31;,
 4;12,13,33,32;,
 4;13,14,34,33;,
 4;14,15,35,34;,
 4;15,16,36,35;,
 4;16,17,37,36;,
 4;17,18,38,37;,
 4;18,19,39,38;,
 4;19,20,40,39;,
 4;20,2,22,40;,
 4;22,21,41,42;,
 4;21,23,43,41;,
 4;23,24,44,43;,
 4;24,25,45,44;,
 4;25,26,46,45;,
 4;26,27,47,46;,
 4;27,28,48,47;,
 4;28,29,49,48;,
 4;29,30,50,49;,
 4;30,31,51,50;,
 4;31,32,52,51;,
 4;32,33,53,52;,
 4;33,34,54,53;,
 4;34,35,55,54;,
 4;35,36,56,55;,
 4;36,37,57,56;,
 4;37,38,58,57;,
 4;38,39,59,58;,
 4;39,40,60,59;,
 4;40,22,42,60;,
 4;42,41,61,62;,
 4;41,43,63,61;,
 4;43,44,64,63;,
 4;44,45,65,64;,
 4;45,46,66,65;,
 4;46,47,67,66;,
 4;47,48,68,67;,
 4;48,49,69,68;,
 4;49,50,70,69;,
 4;50,51,71,70;,
 4;51,52,72,71;,
 4;52,53,73,72;,
 4;53,54,74,73;,
 4;54,55,75,74;,
 4;55,56,76,75;,
 4;56,57,77,76;,
 4;57,58,78,77;,
 4;58,59,79,78;,
 4;59,60,80,79;,
 4;60,42,62,80;,
 4;62,61,81,82;,
 4;61,63,83,81;,
 4;63,64,84,83;,
 4;64,65,85,84;,
 4;65,66,86,85;,
 4;66,67,87,86;,
 4;67,68,88,87;,
 4;68,69,89,88;,
 4;69,70,90,89;,
 4;70,71,91,90;,
 4;71,72,92,91;,
 4;72,73,93,92;,
 4;73,74,94,93;,
 4;74,75,95,94;,
 4;75,76,96,95;,
 4;76,77,97,96;,
 4;77,78,98,97;,
 4;78,79,99,98;,
 4;79,80,100,99;,
 4;80,62,82,100;,
 4;82,81,101,102;,
 4;81,83,103,101;,
 4;83,84,104,103;,
 4;84,85,105,104;,
 4;85,86,106,105;,
 4;86,87,107,106;,
 4;87,88,108,107;,
 4;88,89,109,108;,
 4;89,90,110,109;,
 4;90,91,111,110;,
 4;91,92,112,111;,
 4;92,93,113,112;,
 4;93,94,114,113;,
 4;94,95,115,114;,
 4;95,96,116,115;,
 4;96,97,117,116;,
 4;97,98,118,117;,
 4;98,99,119,118;,
 4;99,100,120,119;,
 4;100,82,102,120;,
 4;102,101,121,122;,
 4;101,103,123,121;,
 4;103,104,124,123;,
 4;104,105,125,124;,
 4;105,106,126,125;,
 4;106,107,127,126;,
 4;107,108,128,127;,
 4;108,109,129,128;,
 4;109,110,130,129;,
 4;110,111,131,130;,
 4;111,112,132,131;,
 4;112,113,133,132;,
 4;113,114,134,133;,
 4;114,115,135,134;,
 4;115,116,136,135;,
 4;116,117,137,136;,
 4;117,118,138,137;,
 4;118,119,139,138;,
 4;119,120,140,139;,
 4;120,102,122,140;,
 4;122,121,141,142;,
 4;121,123,143,141;,
 4;123,124,144,143;,
 4;124,125,145,144;,
 4;125,126,146,145;,
 4;126,127,147,146;,
 4;127,128,148,147;,
 4;128,129,149,148;,
 4;129,130,150,149;,
 4;130,131,151,150;,
 4;131,132,152,151;,
 4;132,133,153,152;,
 4;133,134,154,153;,
 4;134,135,155,154;,
 4;135,136,156,155;,
 4;136,137,157,156;,
 4;137,138,158,157;,
 4;138,139,159,158;,
 4;139,140,160,159;,
 4;140,122,142,160;,
 4;142,141,161,162;,
 4;141,143,163,161;,
 4;143,144,164,163;,
 4;144,145,165,164;,
 4;145,146,166,165;,
 4;146,147,167,166;,
 4;147,148,168,167;,
 4;148,149,169,168;,
 4;149,150,170,169;,
 4;150,151,171,170;,
 4;151,152,172,171;,
 4;152,153,173,172;,
 4;153,154,174,173;,
 4;154,155,175,174;,
 4;155,156,176,175;,
 4;156,157,177,176;,
 4;157,158,178,177;,
 4;158,159,179,178;,
 4;159,160,180,179;,
 4;160,142,162,180;,
 4;162,161,181,182;,
 4;161,163,183,181;,
 4;163,164,184,183;,
 4;164,165,185,184;,
 4;165,166,186,185;,
 4;166,167,187,186;,
 4;167,168,188,187;,
 4;168,169,189,188;,
 4;169,170,190,189;,
 4;170,171,191,190;,
 4;171,172,192,191;,
 4;172,173,193,192;,
 4;173,174,194,193;,
 4;174,175,195,194;,
 4;175,176,196,195;,
 4;176,177,197,196;,
 4;177,178,198,197;,
 4;178,179,199,198;,
 4;179,180,200,199;,
 4;180,162,182,200;,
 4;182,181,201,202;,
 4;181,183,203,201;,
 4;183,184,204,203;,
 4;184,185,205,204;,
 4;185,186,206,205;,
 4;186,187,207,206;,
 4;187,188,208,207;,
 4;188,189,209,208;,
 4;189,190,210,209;,
 4;190,191,211,210;,
 4;191,192,212,211;,
 4;192,193,213,212;,
 4;193,194,214,213;,
 4;194,195,215,214;,
 4;195,196,216,215;,
 4;196,197,217,216;,
 4;197,198,218,217;,
 4;198,199,219,218;,
 4;199,200,220,219;,
 4;200,182,202,220;,
 4;202,201,221,222;,
 4;201,203,223,221;,
 4;203,204,224,223;,
 4;204,205,225,224;,
 4;207,208,226,227;,
 4;208,209,228,226;,
 4;209,210,229,228;,
 4;210,211,230,229;,
 4;211,212,231,230;,
 4;212,213,232,231;,
 4;213,214,233,232;,
 4;214,215,234,233;,
 4;215,216,235,234;,
 4;216,217,236,235;,
 4;217,218,237,236;,
 4;218,219,238,237;,
 4;219,220,239,238;,
 4;220,202,222,239;,
 4;222,221,240,241;,
 4;221,223,242,240;,
 4;223,224,243,242;,
 4;224,225,244,243;,
 4;225,245,246,244;,
 4;245,227,247,246;,
 4;227,226,248,247;,
 4;226,228,249,248;,
 4;228,229,250,249;,
 4;229,230,251,250;,
 4;230,231,252,251;,
 4;231,232,253,252;,
 4;232,233,254,253;,
 4;233,234,255,254;,
 4;234,235,256,255;,
 4;235,236,257,256;,
 4;236,237,258,257;,
 4;237,238,259,258;,
 4;238,239,260,259;,
 4;239,222,241,260;,
 4;241,240,261,262;,
 4;240,242,263,261;,
 4;242,243,264,263;,
 4;243,244,265,264;,
 4;244,246,266,265;,
 4;246,247,267,266;,
 4;247,248,268,267;,
 4;248,249,269,268;,
 4;249,250,270,269;,
 4;250,251,271,270;,
 4;251,252,272,271;,
 4;252,253,273,272;,
 4;253,254,274,273;,
 4;254,255,275,274;,
 4;255,256,276,275;,
 4;256,257,277,276;,
 4;257,258,278,277;,
 4;258,259,279,278;,
 4;259,260,280,279;,
 4;260,241,262,280;,
 3;262,261,281;,
 3;261,263,281;,
 3;263,264,281;,
 3;264,265,281;,
 3;265,266,281;,
 3;266,267,281;,
 3;267,268,281;,
 3;268,269,281;,
 3;269,270,281;,
 3;270,271,281;,
 3;271,272,281;,
 3;272,273,281;,
 3;273,274,281;,
 3;274,275,281;,
 3;275,276,281;,
 3;276,277,281;,
 3;277,278,281;,
 3;278,279,281;,
 3;279,280,281;,
 3;280,262,281;,
 4;282,283,205,206;,
 4;284,285,245,225;,
 4;283,284,225,205;,
 4;283,282,285,284;,
 4;286,282,206,207;,
 4;287,286,207,227;,
 4;285,287,227,245;,
 4;282,286,287,285;;
 
 MeshMaterialList {
  4;
  306;
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
  3;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.480000;0.480000;0.480000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.034400;1.000000;;
   5.000000;
   0.630000;0.630000;0.630000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.320000;0.000000;1.000000;;
   5.000000;
   0.480000;0.480000;0.480000;;
   0.340000;0.136000;0.000000;;
  }
 }
 MeshNormals {
  299;
  -0.024448;0.027214;-0.999331;,
  0.446783;0.030188;-0.894133;,
  0.396806;0.352316;-0.847596;,
  0.291560;0.575152;-0.764326;,
  0.179288;0.699194;-0.692086;,
  0.074359;0.758990;-0.646843;,
  -0.025263;0.775934;-0.630308;,
  -0.125117;0.756393;-0.642040;,
  -0.230522;0.693869;-0.682206;,
  -0.342881;0.566909;-0.749031;,
  -0.446213;0.341301;-0.827290;,
  -0.489985;0.017908;-0.871547;,
  -0.438229;-0.306184;-0.845107;,
  -0.329306;-0.533131;-0.779313;,
  -0.213827;-0.660764;-0.719492;,
  -0.106912;-0.722759;-0.682781;,
  -0.006575;-0.740460;-0.672068;,
  0.092588;-0.720186;-0.687575;,
  0.195973;-0.655442;-0.729377;,
  0.305091;-0.524908;-0.794601;,
  0.404782;-0.295232;-0.865442;,
  0.734242;0.027756;-0.678320;,
  0.622004;0.507385;-0.596382;,
  0.420559;0.775403;-0.471042;,
  0.246347;0.890083;-0.383490;,
  0.105238;0.935815;-0.336415;,
  -0.020016;0.947201;-0.320015;,
  -0.145588;0.932557;-0.330365;,
  -0.287568;0.883151;-0.370607;,
  -0.462749;0.763943;-0.449726;,
  -0.662997;0.490669;-0.565402;,
  -0.766549;0.008193;-0.642134;,
  -0.651085;-0.475008;-0.591993;,
  -0.444110;-0.749187;-0.491412;,
  -0.265975;-0.868233;-0.418843;,
  -0.122807;-0.916265;-0.381283;,
  0.003096;-0.928358;-0.371673;,
  0.128027;-0.913007;-0.387335;,
  0.267932;-0.861295;-0.431722;,
  0.439192;-0.737735;-0.512696;,
  0.633905;-0.458333;-0.622974;,
  0.870911;0.024250;-0.490843;,
  0.716390;0.563809;-0.410981;,
  0.462869;0.833288;-0.302298;,
  0.265103;0.935284;-0.234446;,
  0.113861;0.973188;-0.199855;,
  -0.017279;0.982120;-0.187464;,
  -0.148584;0.969778;-0.193528;,
  -0.300282;0.927940;-0.220813;,
  -0.498362;0.820812;-0.279112;,
  -0.749756;0.544771;-0.375621;,
  -0.893888;0.001326;-0.448289;,
  -0.736370;-0.541565;-0.405544;,
  -0.478206;-0.816218;-0.324201;,
  -0.277493;-0.921493;-0.271749;,
  -0.124782;-0.961025;-0.246699;,
  0.006783;-0.970443;-0.241233;,
  0.137657;-0.957615;-0.253029;,
  0.287906;-0.914148;-0.285384;,
  0.483047;-0.803737;-0.347379;,
  0.729776;-0.522535;-0.440891;,
  0.936714;0.021159;-0.349455;,
  0.759199;0.586446;-0.282310;,
  0.480302;0.854456;-0.198030;,
  0.272688;0.950639;-0.148074;,
  0.117591;0.985428;-0.122901;,
  -0.015640;0.993431;-0.113360;,
  -0.148915;0.981966;-0.116476;,
  -0.304091;0.943148;-0.134168;,
  -0.511310;0.841573;-0.174121;,
  -0.786885;0.566372;-0.245021;,
  -0.952703;-0.003361;-0.303884;,
  -0.772871;-0.571230;-0.276346;,
  -0.490554;-0.843051;-0.220505;,
  -0.280872;-0.941538;-0.186058;,
  -0.124761;-0.977441;-0.170423;,
  0.008752;-0.985773;-0.167855;,
  0.141737;-0.973979;-0.176851;,
  0.295924;-0.934046;-0.199969;,
  0.501075;-0.830169;-0.244423;,
  0.773220;-0.551147;-0.313637;,
  0.970794;0.018549;-0.239198;,
  0.780878;0.596359;-0.185971;,
  0.488968;0.863436;-0.124054;,
  0.276602;0.956912;-0.088376;,
  0.119691;0.990321;-0.070272;,
  -0.014478;0.997919;-0.062837;,
  -0.148604;0.986836;-0.063802;,
  -0.305286;0.949354;-0.074343;,
  -0.516635;0.850369;-0.099805;,
  -0.804155;0.575766;-0.147747;,
  -0.981348;-0.006805;-0.192118;,
  -0.789831;-0.586393;-0.179748;,
  -0.495602;-0.856055;-0.146793;,
  -0.281866;-0.951055;-0.126673;,
  -0.124300;-0.985191;-0.118104;,
  0.010059;-0.993003;-0.117659;,
  0.143995;-0.981706;-0.124574;,
  0.300023;-0.943498;-0.140707;,
  0.510003;-0.842995;-0.171046;,
  0.795206;-0.565804;-0.217975;,
  0.988997;0.016237;-0.147043;,
  0.792472;0.600426;-0.107129;,
  0.493745;0.867166;-0.065113;,
  0.278926;0.959420;-0.041392;,
  0.121090;0.992216;-0.029052;,
  -0.013547;0.999636;-0.023321;,
  -0.148064;0.988720;-0.022563;,
  -0.305408;0.951830;-0.027301;,
  -0.518656;0.854014;-0.040699;,
  -0.812037;0.579579;-0.068440;,
  -0.995022;-0.009544;-0.099200;,
  -0.797563;-0.594758;-0.100776;,
  -0.497498;-0.862992;-0.087984;,
  -0.281891;-0.956118;-0.079843;,
  -0.123686;-0.989327;-0.077034;,
  0.011060;-0.996869;-0.078299;,
  0.145467;-0.985831;-0.083523;,
  0.302438;-0.948530;-0.093932;,
  0.514907;-0.849846;-0.112395;,
  0.806948;-0.573920;-0.139469;,
  0.997841;0.014064;-0.064155;,
  0.798288;0.601139;-0.036976;,
  0.496405;0.867988;-0.013348;,
  0.280416;0.959879;-0.000369;,
  0.122132;0.992490;0.006854;,
  -0.012719;0.999858;0.011079;,
  -0.147381;0.988990;0.013353;,
  -0.304931;0.952275;0.013747;,
  -0.518838;0.854800;0.011135;,
  -0.814481;0.580187;0.001915;,
  -0.999802;-0.011894;-0.015984;,
  -0.799944;-0.599296;-0.030565;,
  -0.497629;-0.866632;-0.036267;,
  -0.281374;-0.958810;-0.038875;,
  -0.122970;-0.991556;-0.041180;,
  0.011915;-0.998962;-0.043957;,
  0.146540;-0.988055;-0.047680;,
  0.303966;-0.951208;-0.052990;,
  0.517618;-0.853453;-0.060748;,
  0.812825;-0.578353;-0.069455;,
  0.999802;0.011884;0.015981;,
  0.799938;0.599304;0.030563;,
  0.497615;0.866639;0.036269;,
  0.281377;0.958809;0.038878;,
  0.122976;0.991555;0.041181;,
  -0.011914;0.998962;0.043957;,
  -0.146545;0.988054;0.047681;,
  -0.303970;0.951207;0.052993;,
  -0.517623;0.853449;0.060749;,
  -0.812826;0.578351;0.069454;,
  -0.997841;-0.014070;0.064153;,
  -0.798287;-0.601141;0.036975;,
  -0.496411;-0.867985;0.013348;,
  -0.280414;-0.959879;0.000368;,
  -0.122129;-0.992491;-0.006856;,
  0.012718;-0.999858;-0.011082;,
  0.147380;-0.988990;-0.013356;,
  0.304929;-0.952276;-0.013748;,
  0.518830;-0.854805;-0.011134;,
  0.814475;-0.580195;-0.001915;,
  0.995022;0.009532;0.099201;,
  0.797557;0.594767;0.100776;,
  0.497481;0.863002;0.087981;,
  0.281895;0.956117;0.079842;,
  0.123694;0.989326;0.077033;,
  -0.011059;0.996868;0.078300;,
  -0.145475;0.985830;0.083524;,
  -0.302443;0.948528;0.093932;,
  -0.514906;0.849847;0.112395;,
  -0.806947;0.573920;0.139469;,
  -0.988997;-0.016243;0.147044;,
  -0.792473;-0.600425;0.107130;,
  -0.493749;-0.867163;0.065112;,
  -0.278925;-0.959420;0.041391;,
  -0.121088;-0.992217;0.029051;,
  0.013544;-0.999636;0.023319;,
  0.148063;-0.988721;0.022561;,
  0.305407;-0.951831;0.027299;,
  0.518651;-0.854017;0.040697;,
  0.812035;-0.579582;0.068438;,
  0.981348;0.006798;0.192118;,
  0.789829;0.586396;0.179748;,
  0.495588;0.856064;0.146790;,
  0.281869;0.951054;0.126672;,
  0.124308;0.985190;0.118103;,
  -0.010058;0.993003;0.117658;,
  -0.144003;0.981705;0.124573;,
  -0.300033;0.943495;0.140706;,
  -0.509999;0.842998;0.171042;,
  -0.795204;0.565809;0.217969;,
  -0.970796;-0.018557;0.239190;,
  -0.780883;-0.596354;0.185967;,
  -0.488973;-0.863433;0.124053;,
  -0.276603;-0.956912;0.088374;,
  -0.119691;-0.990321;0.070269;,
  0.014473;-0.997919;0.062833;,
  0.148605;-0.986836;0.063800;,
  0.305289;-0.949353;0.074343;,
  0.516628;-0.850373;0.099806;,
  0.804156;-0.575763;0.147750;,
  0.952704;0.003355;0.303881;,
  0.772865;0.571239;0.276344;,
  0.490546;0.843056;0.220502;,
  0.280875;0.941537;0.186056;,
  0.147668;0.975654;0.162151;,
  -0.009504;0.990237;0.139071;,
  -0.164963;0.971592;0.169693;,
  -0.295930;0.934044;0.199968;,
  -0.501066;0.830178;0.244412;,
  -0.773218;0.551156;0.313625;,
  -0.936719;-0.021182;0.349442;,
  -0.759196;-0.586454;0.282300;,
  -0.480308;-0.854453;0.198028;,
  -0.272692;-0.950639;0.148072;,
  -0.117591;-0.985428;0.122897;,
  0.015633;-0.993431;0.113357;,
  0.148917;-0.981966;0.116471;,
  0.304102;-0.943145;0.134163;,
  0.511311;-0.841573;0.174117;,
  0.786880;-0.566379;0.245019;,
  0.879923;-0.002352;0.475110;,
  0.727017;0.534210;0.431354;,
  0.474605;0.808899;0.347034;,
  0.276364;0.915706;0.291729;,
  0.147433;0.946244;0.287899;,
  -0.004591;0.947350;0.320167;,
  -0.157919;0.942346;0.295035;,
  -0.285702;0.908512;0.304926;,
  -0.478288;0.796710;0.369452;,
  -0.719340;0.515615;0.465500;,
  -0.856130;-0.024884;0.516160;,
  -0.706649;-0.558445;0.434496;,
  -0.458763;-0.828050;0.322288;,
  -0.263335;-0.931392;0.251324;,
  -0.113032;-0.970057;0.214971;,
  0.017585;-0.979210;0.202086;,
  0.148397;-0.966626;0.208838;,
  0.299211;-0.923999;0.238116;,
  0.495004;-0.815513;0.299850;,
  0.740727;-0.539500;0.400329;,
  0.669176;0.025383;0.742670;,
  0.498456;0.345224;0.795212;,
  0.347039;0.559294;0.752831;,
  0.215037;0.659912;0.719913;,
  0.105670;0.703800;0.702494;,
  0.007531;0.715708;0.698359;,
  -0.090021;0.701811;0.706652;,
  -0.197559;0.655601;0.728806;,
  -0.325758;0.552028;0.767559;,
  -0.470469;0.334075;0.816733;,
  -0.635275;0.009171;0.772232;,
  -0.486863;-0.692870;0.531879;,
  -0.341600;-0.654927;0.674077;,
  -0.205077;-0.775794;0.596730;,
  -0.086008;-0.830535;0.550285;,
  0.023819;-0.845311;0.533744;,
  0.133850;-0.827098;0.545887;,
  0.253313;-0.768727;0.587274;,
  0.389689;-0.643977;0.658359;,
  0.583995;-0.477598;0.656391;,
  0.290248;0.080949;0.953522;,
  0.262100;0.161585;0.951417;,
  0.201408;0.295586;0.933844;,
  0.139025;0.381789;0.913734;,
  0.077014;0.429205;0.899918;,
  0.015839;0.444016;0.895879;,
  -0.044730;0.428172;0.902590;,
  -0.105098;0.379534;0.919189;,
  -0.164706;0.292128;0.942090;,
  -0.221847;0.156661;0.962414;,
  -0.248357;0.075053;0.965757;,
  -0.143949;-0.984361;-0.101553;,
  -0.276123;-0.564506;0.777874;,
  -0.200818;-0.770131;0.605450;,
  -0.093126;-0.873798;0.477288;,
  0.022118;-0.901118;0.433008;,
  0.138440;-0.869280;0.474539;,
  0.248580;-0.760955;0.599296;,
  0.325294;-0.552436;0.767462;,
  0.345467;-0.416688;0.840847;,
  0.019959;0.237952;0.971072;,
  -0.016064;0.196020;-0.980468;,
  -0.026196;0.195898;-0.980274;,
  -0.036325;0.195755;-0.979980;,
  0.016190;-0.196016;0.980467;,
  0.026178;-0.195896;0.980275;,
  -0.985633;-0.099887;0.136200;,
  -0.296846;-0.429072;0.853100;,
  0.159785;-0.980862;-0.111262;,
  0.244263;-0.063244;-0.967645;,
  -0.023362;-0.063903;-0.997683;,
  0.018039;-0.970231;0.241509;,
  -0.289292;-0.059927;-0.955363;,
  0.993313;-0.074182;0.088461;,
  0.045591;0.979873;0.194347;,
  -0.008012;0.980587;0.195921;,
  0.036163;-0.195757;0.979985;,
  -0.061591;0.978481;0.196932;;
  306;
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
  3;0,13,12;,
  3;0,14,13;,
  3;0,15,14;,
  3;0,16,15;,
  3;0,17,16;,
  3;0,18,17;,
  3;0,19,18;,
  3;0,20,19;,
  3;0,1,20;,
  4;1,2,22,21;,
  4;2,3,23,22;,
  4;3,4,24,23;,
  4;4,5,25,24;,
  4;5,6,26,25;,
  4;6,7,27,26;,
  4;7,8,28,27;,
  4;8,9,29,28;,
  4;9,10,30,29;,
  4;10,11,31,30;,
  4;11,12,32,31;,
  4;12,13,33,32;,
  4;13,14,34,33;,
  4;14,15,35,34;,
  4;15,16,36,35;,
  4;16,17,37,36;,
  4;17,18,38,37;,
  4;18,19,39,38;,
  4;19,20,40,39;,
  4;20,1,21,40;,
  4;21,22,42,41;,
  4;22,23,43,42;,
  4;23,24,44,43;,
  4;24,25,45,44;,
  4;25,26,46,45;,
  4;26,27,47,46;,
  4;27,28,48,47;,
  4;28,29,49,48;,
  4;29,30,50,49;,
  4;30,31,51,50;,
  4;31,32,52,51;,
  4;32,33,53,52;,
  4;33,34,54,53;,
  4;34,35,55,54;,
  4;35,36,56,55;,
  4;36,37,57,56;,
  4;37,38,58,57;,
  4;38,39,59,58;,
  4;39,40,60,59;,
  4;40,21,41,60;,
  4;41,42,62,61;,
  4;42,43,63,62;,
  4;43,44,64,63;,
  4;44,45,65,64;,
  4;45,46,66,65;,
  4;46,47,67,66;,
  4;47,48,68,67;,
  4;48,49,69,68;,
  4;49,50,70,69;,
  4;50,51,71,70;,
  4;51,52,72,71;,
  4;52,53,73,72;,
  4;53,54,74,73;,
  4;54,55,75,74;,
  4;55,56,76,75;,
  4;56,57,77,76;,
  4;57,58,78,77;,
  4;58,59,79,78;,
  4;59,60,80,79;,
  4;60,41,61,80;,
  4;61,62,82,81;,
  4;62,63,83,82;,
  4;63,64,84,83;,
  4;64,65,85,84;,
  4;65,66,86,85;,
  4;66,67,87,86;,
  4;67,68,88,87;,
  4;68,69,89,88;,
  4;69,70,90,89;,
  4;70,71,91,90;,
  4;71,72,92,91;,
  4;72,73,93,92;,
  4;73,74,94,93;,
  4;74,75,95,94;,
  4;75,76,96,95;,
  4;76,77,97,96;,
  4;77,78,98,97;,
  4;78,79,99,98;,
  4;79,80,100,99;,
  4;80,61,81,100;,
  4;81,82,102,101;,
  4;82,83,103,102;,
  4;83,84,104,103;,
  4;84,85,105,104;,
  4;85,86,106,105;,
  4;86,87,107,106;,
  4;87,88,108,107;,
  4;88,89,109,108;,
  4;89,90,110,109;,
  4;90,91,111,110;,
  4;91,92,112,111;,
  4;92,93,113,112;,
  4;93,94,114,113;,
  4;94,95,115,114;,
  4;95,96,116,115;,
  4;96,97,117,116;,
  4;97,98,118,117;,
  4;98,99,119,118;,
  4;99,100,120,119;,
  4;100,81,101,120;,
  4;101,102,122,121;,
  4;102,103,123,122;,
  4;103,104,124,123;,
  4;104,105,125,124;,
  4;105,106,126,125;,
  4;106,107,127,126;,
  4;107,108,128,127;,
  4;108,109,129,128;,
  4;109,110,130,129;,
  4;110,111,131,130;,
  4;111,112,132,131;,
  4;112,113,133,132;,
  4;113,114,134,133;,
  4;114,115,135,134;,
  4;115,116,136,135;,
  4;116,117,137,136;,
  4;117,118,138,137;,
  4;118,119,139,138;,
  4;119,120,140,139;,
  4;120,101,121,140;,
  4;121,122,142,141;,
  4;122,123,143,142;,
  4;123,124,144,143;,
  4;124,125,145,144;,
  4;125,126,146,145;,
  4;126,127,147,146;,
  4;127,128,148,147;,
  4;128,129,149,148;,
  4;129,130,150,149;,
  4;130,131,151,150;,
  4;131,132,152,151;,
  4;132,133,153,152;,
  4;133,134,154,153;,
  4;134,135,155,154;,
  4;135,136,156,155;,
  4;136,137,157,156;,
  4;137,138,158,157;,
  4;138,139,159,158;,
  4;139,140,160,159;,
  4;140,121,141,160;,
  4;141,142,162,161;,
  4;142,143,163,162;,
  4;143,144,164,163;,
  4;144,145,165,164;,
  4;145,146,166,165;,
  4;146,147,167,166;,
  4;147,148,168,167;,
  4;148,149,169,168;,
  4;149,150,170,169;,
  4;150,151,171,170;,
  4;151,152,172,171;,
  4;152,153,173,172;,
  4;153,154,174,173;,
  4;154,155,175,174;,
  4;155,156,176,175;,
  4;156,157,177,176;,
  4;157,158,178,177;,
  4;158,159,179,178;,
  4;159,160,180,179;,
  4;160,141,161,180;,
  4;161,162,182,181;,
  4;162,163,183,182;,
  4;163,164,184,183;,
  4;164,165,185,184;,
  4;165,166,186,185;,
  4;166,167,187,186;,
  4;167,168,188,187;,
  4;168,169,189,188;,
  4;169,170,190,189;,
  4;170,171,191,190;,
  4;171,172,192,191;,
  4;172,173,193,192;,
  4;173,174,194,193;,
  4;174,175,195,194;,
  4;175,176,196,195;,
  4;176,177,197,196;,
  4;177,178,198,197;,
  4;178,179,199,198;,
  4;179,180,200,199;,
  4;180,161,181,200;,
  4;181,182,202,201;,
  4;182,183,203,202;,
  4;183,184,204,203;,
  4;184,185,205,204;,
  4;185,186,206,205;,
  4;186,187,207,206;,
  4;187,188,208,207;,
  4;188,189,209,208;,
  4;189,190,210,209;,
  4;190,191,211,210;,
  4;191,192,212,211;,
  4;192,193,213,212;,
  4;193,194,214,213;,
  4;194,195,215,214;,
  4;195,196,216,215;,
  4;196,197,217,216;,
  4;197,198,218,217;,
  4;198,199,219,218;,
  4;199,200,220,219;,
  4;200,181,201,220;,
  4;201,202,222,221;,
  4;202,203,223,222;,
  4;203,204,224,223;,
  4;204,205,225,224;,
  4;207,208,228,227;,
  4;208,209,229,228;,
  4;209,210,230,229;,
  4;210,211,231,230;,
  4;211,212,232,231;,
  4;212,213,233,232;,
  4;213,214,234,233;,
  4;214,215,235,234;,
  4;215,216,236,235;,
  4;216,217,237,236;,
  4;217,218,238,237;,
  4;218,219,239,238;,
  4;219,220,240,239;,
  4;220,201,221,240;,
  4;221,222,242,241;,
  4;222,223,243,242;,
  4;223,224,244,243;,
  4;224,225,245,244;,
  4;225,226,246,245;,
  4;226,227,247,246;,
  4;227,228,248,247;,
  4;228,229,249,248;,
  4;229,230,250,249;,
  4;230,231,251,250;,
  4;231,232,252,251;,
  4;232,233,253,252;,
  4;233,234,254,253;,
  4;234,235,255,254;,
  4;235,236,256,255;,
  4;236,237,257,256;,
  4;237,238,258,257;,
  4;238,239,259,258;,
  4;239,240,260,259;,
  4;240,221,241,260;,
  4;241,242,262,261;,
  4;242,243,263,262;,
  4;243,244,264,263;,
  4;244,245,265,264;,
  4;245,246,266,265;,
  4;246,247,267,266;,
  4;247,248,268,267;,
  4;248,249,269,268;,
  4;249,250,270,269;,
  4;250,251,271,270;,
  4;272,252,272,272;,
  4;252,253,273,288;,
  4;253,254,274,273;,
  4;254,255,275,274;,
  4;255,256,276,275;,
  4;256,257,277,276;,
  4;257,258,278,277;,
  4;258,259,279,278;,
  4;259,260,280,279;,
  4;289,289,289,289;,
  3;261,262,281;,
  3;262,263,281;,
  3;263,264,281;,
  3;264,265,281;,
  3;265,266,281;,
  3;266,267,281;,
  3;267,268,281;,
  3;268,269,281;,
  3;269,270,281;,
  3;270,271,281;,
  3;290,290,291;,
  3;288,273,281;,
  3;273,274,292;,
  3;274,275,292;,
  3;275,276,292;,
  3;276,277,292;,
  3;277,278,292;,
  3;278,279,292;,
  3;279,280,281;,
  3;293,293,291;,
  4;283,282,282,283;,
  4;285,286,286,285;,
  4;294,294,294,294;,
  4;295,296,296,295;,
  4;284,283,283,284;,
  4;287,287,287,287;,
  4;286,297,297,286;,
  4;296,298,298,296;;
 }
}
