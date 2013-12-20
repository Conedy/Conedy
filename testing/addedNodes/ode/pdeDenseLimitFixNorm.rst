

DGL of pdeDenseLimitFixNorm
------------------------------------------

::


	double phase;

	double phaseminus;

	double xlast = 1 -x[0] - x[1] - x[2] - x[3] - x[4] - x[5] - x[6] - x[7] - x[8] - x[9] - x[10] - x[11] - x[12] - x[13] - x[14] - x[15] - x[16] - x[17] - x[18] - x[19] - x[20] - x[21] - x[22] - x[23] - x[24] - x[25] - x[26] - x[27] - x[28] - x[29] - x[30] - x[31] - x[32] - x[33] - x[34] - x[35] - x[36] - x[37] - x[38] - x[39] - x[40] - x[41] - x[42] - x[43] - x[44] - x[45] - x[46] - x[47] - x[48] - x[49] - x[50] - x[51] - x[52] - x[53] - x[54] - x[55] - x[56] - x[57] - x[58] - x[59] - x[60] - x[61] - x[62] - x[63] - x[64] - x[65] - x[66] - x[67] - x[68] - x[69] - x[70] - x[71] - x[72] - x[73] - x[74] - x[75] - x[76] - x[77] - x[78] - x[79] - x[80] - x[81] - x[82] - x[83] - x[84] - x[85] - x[86] - x[87] - x[88] - x[89] - x[90] - x[91] - x[92] - x[93] - x[94] - x[95] - x[96] - x[97] - x[98];

	double rate =xlast * 100 / ( 1 - ( a() + b()) * xlast * 100);

	double xminus1 = xlast * ( 1 + (a() * 0.0   + b()) * rate) / (  1 + b() * rate);

	phase =  ((double)0) / 100;

	phaseminus =  ((double)99) / 100;

	dxdt[0]=- ( ( 1 + ( a() * phase + b() ) * rate ) * x [ 0]  -( 1 + ( a() * phaseminus + b() ) * rate ) * xminus1) *100;

	phase =  ((double)1) / 100;

	phaseminus =  ((double)0) / 100;

	dxdt[1]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 1]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 0]) *100;

	phase =  ((double)2) / 100;

	phaseminus =  ((double)1) / 100;

	dxdt[2]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 2]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 1]) *100;

	phase =  ((double)3) / 100;

	phaseminus =  ((double)2) / 100;

	dxdt[3]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 3]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 2]) *100;

	phase =  ((double)4) / 100;

	phaseminus =  ((double)3) / 100;

	dxdt[4]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 4]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 3]) *100;

	phase =  ((double)5) / 100;

	phaseminus =  ((double)4) / 100;

	dxdt[5]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 5]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 4]) *100;

	phase =  ((double)6) / 100;

	phaseminus =  ((double)5) / 100;

	dxdt[6]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 6]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 5]) *100;

	phase =  ((double)7) / 100;

	phaseminus =  ((double)6) / 100;

	dxdt[7]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 7]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 6]) *100;

	phase =  ((double)8) / 100;

	phaseminus =  ((double)7) / 100;

	dxdt[8]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 8]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 7]) *100;

	phase =  ((double)9) / 100;

	phaseminus =  ((double)8) / 100;

	dxdt[9]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 9]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 8]) *100;

	phase =  ((double)10) / 100;

	phaseminus =  ((double)9) / 100;

	dxdt[10]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 10]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 9]) *100;

	phase =  ((double)11) / 100;

	phaseminus =  ((double)10) / 100;

	dxdt[11]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 11]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 10]) *100;

	phase =  ((double)12) / 100;

	phaseminus =  ((double)11) / 100;

	dxdt[12]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 12]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 11]) *100;

	phase =  ((double)13) / 100;

	phaseminus =  ((double)12) / 100;

	dxdt[13]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 13]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 12]) *100;

	phase =  ((double)14) / 100;

	phaseminus =  ((double)13) / 100;

	dxdt[14]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 14]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 13]) *100;

	phase =  ((double)15) / 100;

	phaseminus =  ((double)14) / 100;

	dxdt[15]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 15]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 14]) *100;

	phase =  ((double)16) / 100;

	phaseminus =  ((double)15) / 100;

	dxdt[16]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 16]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 15]) *100;

	phase =  ((double)17) / 100;

	phaseminus =  ((double)16) / 100;

	dxdt[17]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 17]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 16]) *100;

	phase =  ((double)18) / 100;

	phaseminus =  ((double)17) / 100;

	dxdt[18]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 18]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 17]) *100;

	phase =  ((double)19) / 100;

	phaseminus =  ((double)18) / 100;

	dxdt[19]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 19]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 18]) *100;

	phase =  ((double)20) / 100;

	phaseminus =  ((double)19) / 100;

	dxdt[20]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 20]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 19]) *100;

	phase =  ((double)21) / 100;

	phaseminus =  ((double)20) / 100;

	dxdt[21]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 21]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 20]) *100;

	phase =  ((double)22) / 100;

	phaseminus =  ((double)21) / 100;

	dxdt[22]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 22]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 21]) *100;

	phase =  ((double)23) / 100;

	phaseminus =  ((double)22) / 100;

	dxdt[23]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 23]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 22]) *100;

	phase =  ((double)24) / 100;

	phaseminus =  ((double)23) / 100;

	dxdt[24]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 24]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 23]) *100;

	phase =  ((double)25) / 100;

	phaseminus =  ((double)24) / 100;

	dxdt[25]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 25]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 24]) *100;

	phase =  ((double)26) / 100;

	phaseminus =  ((double)25) / 100;

	dxdt[26]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 26]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 25]) *100;

	phase =  ((double)27) / 100;

	phaseminus =  ((double)26) / 100;

	dxdt[27]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 27]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 26]) *100;

	phase =  ((double)28) / 100;

	phaseminus =  ((double)27) / 100;

	dxdt[28]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 28]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 27]) *100;

	phase =  ((double)29) / 100;

	phaseminus =  ((double)28) / 100;

	dxdt[29]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 29]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 28]) *100;

	phase =  ((double)30) / 100;

	phaseminus =  ((double)29) / 100;

	dxdt[30]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 30]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 29]) *100;

	phase =  ((double)31) / 100;

	phaseminus =  ((double)30) / 100;

	dxdt[31]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 31]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 30]) *100;

	phase =  ((double)32) / 100;

	phaseminus =  ((double)31) / 100;

	dxdt[32]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 32]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 31]) *100;

	phase =  ((double)33) / 100;

	phaseminus =  ((double)32) / 100;

	dxdt[33]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 33]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 32]) *100;

	phase =  ((double)34) / 100;

	phaseminus =  ((double)33) / 100;

	dxdt[34]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 34]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 33]) *100;

	phase =  ((double)35) / 100;

	phaseminus =  ((double)34) / 100;

	dxdt[35]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 35]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 34]) *100;

	phase =  ((double)36) / 100;

	phaseminus =  ((double)35) / 100;

	dxdt[36]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 36]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 35]) *100;

	phase =  ((double)37) / 100;

	phaseminus =  ((double)36) / 100;

	dxdt[37]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 37]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 36]) *100;

	phase =  ((double)38) / 100;

	phaseminus =  ((double)37) / 100;

	dxdt[38]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 38]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 37]) *100;

	phase =  ((double)39) / 100;

	phaseminus =  ((double)38) / 100;

	dxdt[39]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 39]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 38]) *100;

	phase =  ((double)40) / 100;

	phaseminus =  ((double)39) / 100;

	dxdt[40]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 40]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 39]) *100;

	phase =  ((double)41) / 100;

	phaseminus =  ((double)40) / 100;

	dxdt[41]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 41]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 40]) *100;

	phase =  ((double)42) / 100;

	phaseminus =  ((double)41) / 100;

	dxdt[42]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 42]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 41]) *100;

	phase =  ((double)43) / 100;

	phaseminus =  ((double)42) / 100;

	dxdt[43]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 43]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 42]) *100;

	phase =  ((double)44) / 100;

	phaseminus =  ((double)43) / 100;

	dxdt[44]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 44]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 43]) *100;

	phase =  ((double)45) / 100;

	phaseminus =  ((double)44) / 100;

	dxdt[45]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 45]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 44]) *100;

	phase =  ((double)46) / 100;

	phaseminus =  ((double)45) / 100;

	dxdt[46]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 46]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 45]) *100;

	phase =  ((double)47) / 100;

	phaseminus =  ((double)46) / 100;

	dxdt[47]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 47]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 46]) *100;

	phase =  ((double)48) / 100;

	phaseminus =  ((double)47) / 100;

	dxdt[48]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 48]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 47]) *100;

	phase =  ((double)49) / 100;

	phaseminus =  ((double)48) / 100;

	dxdt[49]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 49]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 48]) *100;

	phase =  ((double)50) / 100;

	phaseminus =  ((double)49) / 100;

	dxdt[50]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 50]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 49]) *100;

	phase =  ((double)51) / 100;

	phaseminus =  ((double)50) / 100;

	dxdt[51]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 51]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 50]) *100;

	phase =  ((double)52) / 100;

	phaseminus =  ((double)51) / 100;

	dxdt[52]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 52]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 51]) *100;

	phase =  ((double)53) / 100;

	phaseminus =  ((double)52) / 100;

	dxdt[53]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 53]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 52]) *100;

	phase =  ((double)54) / 100;

	phaseminus =  ((double)53) / 100;

	dxdt[54]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 54]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 53]) *100;

	phase =  ((double)55) / 100;

	phaseminus =  ((double)54) / 100;

	dxdt[55]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 55]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 54]) *100;

	phase =  ((double)56) / 100;

	phaseminus =  ((double)55) / 100;

	dxdt[56]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 56]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 55]) *100;

	phase =  ((double)57) / 100;

	phaseminus =  ((double)56) / 100;

	dxdt[57]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 57]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 56]) *100;

	phase =  ((double)58) / 100;

	phaseminus =  ((double)57) / 100;

	dxdt[58]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 58]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 57]) *100;

	phase =  ((double)59) / 100;

	phaseminus =  ((double)58) / 100;

	dxdt[59]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 59]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 58]) *100;

	phase =  ((double)60) / 100;

	phaseminus =  ((double)59) / 100;

	dxdt[60]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 60]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 59]) *100;

	phase =  ((double)61) / 100;

	phaseminus =  ((double)60) / 100;

	dxdt[61]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 61]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 60]) *100;

	phase =  ((double)62) / 100;

	phaseminus =  ((double)61) / 100;

	dxdt[62]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 62]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 61]) *100;

	phase =  ((double)63) / 100;

	phaseminus =  ((double)62) / 100;

	dxdt[63]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 63]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 62]) *100;

	phase =  ((double)64) / 100;

	phaseminus =  ((double)63) / 100;

	dxdt[64]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 64]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 63]) *100;

	phase =  ((double)65) / 100;

	phaseminus =  ((double)64) / 100;

	dxdt[65]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 65]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 64]) *100;

	phase =  ((double)66) / 100;

	phaseminus =  ((double)65) / 100;

	dxdt[66]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 66]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 65]) *100;

	phase =  ((double)67) / 100;

	phaseminus =  ((double)66) / 100;

	dxdt[67]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 67]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 66]) *100;

	phase =  ((double)68) / 100;

	phaseminus =  ((double)67) / 100;

	dxdt[68]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 68]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 67]) *100;

	phase =  ((double)69) / 100;

	phaseminus =  ((double)68) / 100;

	dxdt[69]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 69]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 68]) *100;

	phase =  ((double)70) / 100;

	phaseminus =  ((double)69) / 100;

	dxdt[70]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 70]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 69]) *100;

	phase =  ((double)71) / 100;

	phaseminus =  ((double)70) / 100;

	dxdt[71]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 71]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 70]) *100;

	phase =  ((double)72) / 100;

	phaseminus =  ((double)71) / 100;

	dxdt[72]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 72]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 71]) *100;

	phase =  ((double)73) / 100;

	phaseminus =  ((double)72) / 100;

	dxdt[73]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 73]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 72]) *100;

	phase =  ((double)74) / 100;

	phaseminus =  ((double)73) / 100;

	dxdt[74]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 74]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 73]) *100;

	phase =  ((double)75) / 100;

	phaseminus =  ((double)74) / 100;

	dxdt[75]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 75]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 74]) *100;

	phase =  ((double)76) / 100;

	phaseminus =  ((double)75) / 100;

	dxdt[76]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 76]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 75]) *100;

	phase =  ((double)77) / 100;

	phaseminus =  ((double)76) / 100;

	dxdt[77]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 77]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 76]) *100;

	phase =  ((double)78) / 100;

	phaseminus =  ((double)77) / 100;

	dxdt[78]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 78]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 77]) *100;

	phase =  ((double)79) / 100;

	phaseminus =  ((double)78) / 100;

	dxdt[79]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 79]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 78]) *100;

	phase =  ((double)80) / 100;

	phaseminus =  ((double)79) / 100;

	dxdt[80]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 80]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 79]) *100;

	phase =  ((double)81) / 100;

	phaseminus =  ((double)80) / 100;

	dxdt[81]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 81]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 80]) *100;

	phase =  ((double)82) / 100;

	phaseminus =  ((double)81) / 100;

	dxdt[82]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 82]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 81]) *100;

	phase =  ((double)83) / 100;

	phaseminus =  ((double)82) / 100;

	dxdt[83]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 83]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 82]) *100;

	phase =  ((double)84) / 100;

	phaseminus =  ((double)83) / 100;

	dxdt[84]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 84]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 83]) *100;

	phase =  ((double)85) / 100;

	phaseminus =  ((double)84) / 100;

	dxdt[85]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 85]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 84]) *100;

	phase =  ((double)86) / 100;

	phaseminus =  ((double)85) / 100;

	dxdt[86]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 86]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 85]) *100;

	phase =  ((double)87) / 100;

	phaseminus =  ((double)86) / 100;

	dxdt[87]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 87]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 86]) *100;

	phase =  ((double)88) / 100;

	phaseminus =  ((double)87) / 100;

	dxdt[88]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 88]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 87]) *100;

	phase =  ((double)89) / 100;

	phaseminus =  ((double)88) / 100;

	dxdt[89]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 89]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 88]) *100;

	phase =  ((double)90) / 100;

	phaseminus =  ((double)89) / 100;

	dxdt[90]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 90]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 89]) *100;

	phase =  ((double)91) / 100;

	phaseminus =  ((double)90) / 100;

	dxdt[91]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 91]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 90]) *100;

	phase =  ((double)92) / 100;

	phaseminus =  ((double)91) / 100;

	dxdt[92]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 92]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 91]) *100;

	phase =  ((double)93) / 100;

	phaseminus =  ((double)92) / 100;

	dxdt[93]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 93]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 92]) *100;

	phase =  ((double)94) / 100;

	phaseminus =  ((double)93) / 100;

	dxdt[94]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 94]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 93]) *100;

	phase =  ((double)95) / 100;

	phaseminus =  ((double)94) / 100;

	dxdt[95]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 95]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 94]) *100;

	phase =  ((double)96) / 100;

	phaseminus =  ((double)95) / 100;

	dxdt[96]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 96]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 95]) *100;

	phase =  ((double)97) / 100;

	phaseminus =  ((double)96) / 100;

	dxdt[97]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 97]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 96]) *100;

	phase =  ((double)98) / 100;

	phaseminus =  ((double)97) / 100;

	dxdt[98]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 98]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 97]) *100;

	phase =  ((double)99) / 100;

	phaseminus =  ((double)98) / 100;

	dxdt[99]= -( ( 1 + ( a() * phase + b() ) * rate ) * x [ 99]  -( 1 + ( a() * phaseminus + b() ) * rate ) * x [ 98]) *100;

Parameter of pdeDenseLimitFixNorm
-----------------------------------------



- pdeDenseLimitFixNorm_a 		 =  0.0100000000000000; 
- pdeDenseLimitFixNorm_b 		 =  0.0200000000000000; 

