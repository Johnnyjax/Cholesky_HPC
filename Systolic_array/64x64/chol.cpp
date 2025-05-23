#include "chol.h"
#include <iostream>

using namespace std;

void feeder(matrix_t A[matrix_size][matrix_size],
	stream<matrix_t> &feedin)
	{
		ap_uint<iterator_bit> i, j;
		for(i = 0; i < matrix_size; i++)
		{
			for(j = 0; j < matrix_size; j++)
			{
#pragma pipeline II=1
				if(j >= i)
					feedin.write(A[j][i]);
			}
		}
	}

void PE(ap_uint<iterator_bit> id,
	stream<matrix_t> &readin,
	stream<matrix_t> &result,
	stream<matrix_t> &mid)
	{
		ap_uint<iterator_bit> i, j;
		int bound;
		matrix_t mid_L[matrix_size][matrix_size];
		matrix_t diag;

		//loop bound for MPS
		bound = (matrix_size - id) * (matrix_size - id - 1) / 2;

		//SQRT
		mid_L[id][id] = readin.read();
		mid_L[id][id] = hls::sqrt(mid_L[id][id]);
		result.write(mid_L[id][id]);

		//DIV
		diag = mid_L[id][id];
		loop_div: for(i = id + 1; i < matrix_size; i++)
		{
#pragma HLS pipeline II=1
			mid_L[i][id] = readin.read();
			mid_L[i][id] = mid_L[i][id] / diag;
			result.write(mid_L[i][id]);
		}

		//MPS
		loop1_mps: for(i = id + 1; i < matrix_size; i++)
			loop2_mps: for(j = id + 1; j < matrix_size; j++)
			{
#pragma HLS pipeline II=1
				if(j >= i)
				{
					mid_L[j][i] = readin.read();
					mid_L[j][i] = mid_L[j][i] - mid_L[j][id] * mid_L[i][id];
					mid.write(mid_L[j][i]);
				}
			}
	}


void PE_last(stream<matrix_t> &readin,
		stream<matrix_t> &result)
{
	matrix_t op;

	op = readin.read();
	result.write(hls::sqrt(op));
}

void collector(
	stream<matrix_t> &feedout0,
	stream<matrix_t> &feedout1,
	stream<matrix_t> &feedout2,
	stream<matrix_t> &feedout3,
	stream<matrix_t> &feedout4,
	stream<matrix_t> &feedout5,
	stream<matrix_t> &feedout6,
	stream<matrix_t> &feedout7,
	stream<matrix_t> &feedout8,
	stream<matrix_t> &feedout9,
	stream<matrix_t> &feedout10,
	stream<matrix_t> &feedout11,
	stream<matrix_t> &feedout12,
	stream<matrix_t> &feedout13,
	stream<matrix_t> &feedout14,
	stream<matrix_t> &feedout15,
	stream<matrix_t> &feedout16,
	stream<matrix_t> &feedout17,
	stream<matrix_t> &feedout18,
	stream<matrix_t> &feedout19,
	stream<matrix_t> &feedout20,
	stream<matrix_t> &feedout21,
	stream<matrix_t> &feedout22,
	stream<matrix_t> &feedout23,
	stream<matrix_t> &feedout24,
	stream<matrix_t> &feedout25,
	stream<matrix_t> &feedout26,
	stream<matrix_t> &feedout27,
	stream<matrix_t> &feedout28,
	stream<matrix_t> &feedout29,
	stream<matrix_t> &feedout30,
	stream<matrix_t> &feedout31,
	stream<matrix_t> &feedout32,
	stream<matrix_t> &feedout33,
	stream<matrix_t> &feedout34,
	stream<matrix_t> &feedout35,
	stream<matrix_t> &feedout36,
	stream<matrix_t> &feedout37,
	stream<matrix_t> &feedout38,
	stream<matrix_t> &feedout39,
	stream<matrix_t> &feedout40,
	stream<matrix_t> &feedout41,
	stream<matrix_t> &feedout42,
	stream<matrix_t> &feedout43,
	stream<matrix_t> &feedout44,
	stream<matrix_t> &feedout45,
	stream<matrix_t> &feedout46,
	stream<matrix_t> &feedout47,
	stream<matrix_t> &feedout48,
	stream<matrix_t> &feedout49,
	stream<matrix_t> &feedout50,
	stream<matrix_t> &feedout51,
	stream<matrix_t> &feedout52,
	stream<matrix_t> &feedout53,
	stream<matrix_t> &feedout54,
	stream<matrix_t> &feedout55,
	stream<matrix_t> &feedout56,
	stream<matrix_t> &feedout57,
	stream<matrix_t> &feedout58,
	stream<matrix_t> &feedout59,
	stream<matrix_t> &feedout60,
	stream<matrix_t> &feedout61,
	stream<matrix_t> &feedout62,
	stream<matrix_t> &feedout63,
	matrix_t L[matrix_size][matrix_size])
{
	ap_uint<iterator_bit> i;

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 0)
			L[i][0] = feedout0.read();
		else
			L[i][0] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 1)
			L[i][1] = feedout1.read();
		else
			L[i][1] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 2)
			L[i][2] = feedout2.read();
		else
			L[i][2] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 3)
			L[i][3] = feedout3.read();
		else
			L[i][3] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 4)
			L[i][4] = feedout4.read();
		else
			L[i][4] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 5)
			L[i][5] = feedout5.read();
		else
			L[i][5] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 6)
			L[i][6] = feedout6.read();
		else
			L[i][6] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 7)
			L[i][7] = feedout7.read();
		else
			L[i][7] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 8)
			L[i][8] = feedout8.read();
		else
			L[i][8] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 9)
			L[i][9] = feedout9.read();
		else
			L[i][9] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 10)
			L[i][10] = feedout10.read();
		else
			L[i][10] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 11)
			L[i][11] = feedout11.read();
		else
			L[i][11] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 12)
			L[i][12] = feedout12.read();
		else
			L[i][12] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 13)
			L[i][13] = feedout13.read();
		else
			L[i][13] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 14)
			L[i][14] = feedout14.read();
		else
			L[i][14] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 15)
			L[i][15] = feedout15.read();
		else
			L[i][15] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 16)
			L[i][16] = feedout16.read();
		else
			L[i][16] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 17)
			L[i][17] = feedout17.read();
		else
			L[i][17] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 18)
			L[i][18] = feedout18.read();
		else
			L[i][18] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 19)
			L[i][19] = feedout19.read();
		else
			L[i][19] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 20)
			L[i][20] = feedout20.read();
		else
			L[i][20] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 21)
			L[i][21] = feedout21.read();
		else
			L[i][21] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 22)
			L[i][22] = feedout22.read();
		else
			L[i][22] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 23)
			L[i][23] = feedout23.read();
		else
			L[i][23] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 24)
			L[i][24] = feedout24.read();
		else
			L[i][24] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 25)
			L[i][25] = feedout25.read();
		else
			L[i][25] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 26)
			L[i][26] = feedout26.read();
		else
			L[i][26] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 27)
			L[i][27] = feedout27.read();
		else
			L[i][27] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 28)
			L[i][28] = feedout28.read();
		else
			L[i][28] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 29)
			L[i][29] = feedout29.read();
		else
			L[i][29] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 30)
			L[i][30] = feedout30.read();
		else
			L[i][30] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 31)
			L[i][31] = feedout31.read();
		else
			L[i][31] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 32)
			L[i][32] = feedout32.read();
		else
			L[i][32] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 33)
			L[i][33] = feedout33.read();
		else
			L[i][33] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 34)
			L[i][34] = feedout34.read();
		else
			L[i][34] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 35)
			L[i][35] = feedout35.read();
		else
			L[i][35] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 36)
			L[i][36] = feedout36.read();
		else
			L[i][36] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 37)
			L[i][37] = feedout37.read();
		else
			L[i][37] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 38)
			L[i][38] = feedout38.read();
		else
			L[i][38] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 39)
			L[i][39] = feedout39.read();
		else
			L[i][39] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 40)
			L[i][40] = feedout40.read();
		else
			L[i][40] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 41)
			L[i][41] = feedout41.read();
		else
			L[i][41] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 42)
			L[i][42] = feedout42.read();
		else
			L[i][42] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 43)
			L[i][43] = feedout43.read();
		else
			L[i][43] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 44)
			L[i][44] = feedout44.read();
		else
			L[i][44] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 45)
			L[i][45] = feedout45.read();
		else
			L[i][45] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 46)
			L[i][46] = feedout46.read();
		else
			L[i][46] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 47)
			L[i][47] = feedout47.read();
		else
			L[i][47] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 48)
			L[i][48] = feedout48.read();
		else
			L[i][48] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 49)
			L[i][49] = feedout49.read();
		else
			L[i][49] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 50)
			L[i][50] = feedout50.read();
		else
			L[i][50] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 51)
			L[i][51] = feedout51.read();
		else
			L[i][51] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 52)
			L[i][52] = feedout52.read();
		else
			L[i][52] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 53)
			L[i][53] = feedout53.read();
		else
			L[i][53] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 54)
			L[i][54] = feedout54.read();
		else
			L[i][54] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 55)
			L[i][55] = feedout55.read();
		else
			L[i][55] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 56)
			L[i][56] = feedout56.read();
		else
			L[i][56] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 57)
			L[i][57] = feedout57.read();
		else
			L[i][57] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 58)
			L[i][58] = feedout58.read();
		else
			L[i][58] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 59)
			L[i][59] = feedout59.read();
		else
			L[i][59] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 60)
			L[i][60] = feedout60.read();
		else
			L[i][60] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 61)
			L[i][61] = feedout61.read();
		else
			L[i][61] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 62)
			L[i][62] = feedout62.read();
		else
			L[i][62] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 63)
			L[i][63] = feedout63.read();
		else
			L[i][63] = 0;
	}

}

int top(matrix_t A[matrix_size][matrix_size],
	matrix_t L[matrix_size][matrix_size])
{
#pragma HLS DATAFLOW
	stream<matrix_t> feedin;
#pragma HLS STREAM variable=feedin depth=5

	stream<matrix_t> result0;
#pragma HLS STREAM variable=result0 depth=10
	stream<matrix_t> result1;
#pragma HLS STREAM variable=result1 depth=10
	stream<matrix_t> result2;
#pragma HLS STREAM variable=result2 depth=10
	stream<matrix_t> result3;
#pragma HLS STREAM variable=result3 depth=10
	stream<matrix_t> result4;
#pragma HLS STREAM variable=result4 depth=10
	stream<matrix_t> result5;
#pragma HLS STREAM variable=result5 depth=10
	stream<matrix_t> result6;
#pragma HLS STREAM variable=result6 depth=10
	stream<matrix_t> result7;
#pragma HLS STREAM variable=result7 depth=10
	stream<matrix_t> result8;
#pragma HLS STREAM variable=result8 depth=10
	stream<matrix_t> result9;
#pragma HLS STREAM variable=result9 depth=10
	stream<matrix_t> result10;
#pragma HLS STREAM variable=result10 depth=10
	stream<matrix_t> result11;
#pragma HLS STREAM variable=result11 depth=10
	stream<matrix_t> result12;
#pragma HLS STREAM variable=result12 depth=10
	stream<matrix_t> result13;
#pragma HLS STREAM variable=result13 depth=10
	stream<matrix_t> result14;
#pragma HLS STREAM variable=result14 depth=10
	stream<matrix_t> result15;
#pragma HLS STREAM variable=result15 depth=10
	stream<matrix_t> result16;
#pragma HLS STREAM variable=result16 depth=10
	stream<matrix_t> result17;
#pragma HLS STREAM variable=result17 depth=10
	stream<matrix_t> result18;
#pragma HLS STREAM variable=result18 depth=10
	stream<matrix_t> result19;
#pragma HLS STREAM variable=result19 depth=10
	stream<matrix_t> result20;
#pragma HLS STREAM variable=result20 depth=10
	stream<matrix_t> result21;
#pragma HLS STREAM variable=result21 depth=10
	stream<matrix_t> result22;
#pragma HLS STREAM variable=result22 depth=10
	stream<matrix_t> result23;
#pragma HLS STREAM variable=result23 depth=10
	stream<matrix_t> result24;
#pragma HLS STREAM variable=result24 depth=10
	stream<matrix_t> result25;
#pragma HLS STREAM variable=result25 depth=10
	stream<matrix_t> result26;
#pragma HLS STREAM variable=result26 depth=10
	stream<matrix_t> result27;
#pragma HLS STREAM variable=result27 depth=10
	stream<matrix_t> result28;
#pragma HLS STREAM variable=result28 depth=10
	stream<matrix_t> result29;
#pragma HLS STREAM variable=result29 depth=10
	stream<matrix_t> result30;
#pragma HLS STREAM variable=result30 depth=10
	stream<matrix_t> result31;
#pragma HLS STREAM variable=result31 depth=10
	stream<matrix_t> result32;
#pragma HLS STREAM variable=result32 depth=10
	stream<matrix_t> result33;
#pragma HLS STREAM variable=result33 depth=10
	stream<matrix_t> result34;
#pragma HLS STREAM variable=result34 depth=10
	stream<matrix_t> result35;
#pragma HLS STREAM variable=result35 depth=10
	stream<matrix_t> result36;
#pragma HLS STREAM variable=result36 depth=10
	stream<matrix_t> result37;
#pragma HLS STREAM variable=result37 depth=10
	stream<matrix_t> result38;
#pragma HLS STREAM variable=result38 depth=10
	stream<matrix_t> result39;
#pragma HLS STREAM variable=result39 depth=10
	stream<matrix_t> result40;
#pragma HLS STREAM variable=result40 depth=10
	stream<matrix_t> result41;
#pragma HLS STREAM variable=result41 depth=10
	stream<matrix_t> result42;
#pragma HLS STREAM variable=result42 depth=10
	stream<matrix_t> result43;
#pragma HLS STREAM variable=result43 depth=10
	stream<matrix_t> result44;
#pragma HLS STREAM variable=result44 depth=10
	stream<matrix_t> result45;
#pragma HLS STREAM variable=result45 depth=10
	stream<matrix_t> result46;
#pragma HLS STREAM variable=result46 depth=10
	stream<matrix_t> result47;
#pragma HLS STREAM variable=result47 depth=10
	stream<matrix_t> result48;
#pragma HLS STREAM variable=result48 depth=10
	stream<matrix_t> result49;
#pragma HLS STREAM variable=result49 depth=10
	stream<matrix_t> result50;
#pragma HLS STREAM variable=result50 depth=10
	stream<matrix_t> result51;
#pragma HLS STREAM variable=result51 depth=10
	stream<matrix_t> result52;
#pragma HLS STREAM variable=result52 depth=10
	stream<matrix_t> result53;
#pragma HLS STREAM variable=result53 depth=10
	stream<matrix_t> result54;
#pragma HLS STREAM variable=result54 depth=10
	stream<matrix_t> result55;
#pragma HLS STREAM variable=result55 depth=10
	stream<matrix_t> result56;
#pragma HLS STREAM variable=result56 depth=10
	stream<matrix_t> result57;
#pragma HLS STREAM variable=result57 depth=10
	stream<matrix_t> result58;
#pragma HLS STREAM variable=result58 depth=10
	stream<matrix_t> result59;
#pragma HLS STREAM variable=result59 depth=10
	stream<matrix_t> result60;
#pragma HLS STREAM variable=result60 depth=10
	stream<matrix_t> result61;
#pragma HLS STREAM variable=result61 depth=10
	stream<matrix_t> result62;
#pragma HLS STREAM variable=result62 depth=10
	stream<matrix_t> result63;
#pragma HLS STREAM variable=result63 depth=10

	stream<matrix_t> mid0;
#pragma HLS STREAM variable=mid0 depth=10
	stream<matrix_t> mid1;
#pragma HLS STREAM variable=mid1 depth=10
	stream<matrix_t> mid2;
#pragma HLS STREAM variable=mid2 depth=10
	stream<matrix_t> mid3;
#pragma HLS STREAM variable=mid3 depth=10
	stream<matrix_t> mid4;
#pragma HLS STREAM variable=mid4 depth=10
	stream<matrix_t> mid5;
#pragma HLS STREAM variable=mid5 depth=10
	stream<matrix_t> mid6;
#pragma HLS STREAM variable=mid6 depth=10
	stream<matrix_t> mid7;
#pragma HLS STREAM variable=mid7 depth=10
	stream<matrix_t> mid8;
#pragma HLS STREAM variable=mid8 depth=10
	stream<matrix_t> mid9;
#pragma HLS STREAM variable=mid9 depth=10
	stream<matrix_t> mid10;
#pragma HLS STREAM variable=mid10 depth=10
	stream<matrix_t> mid11;
#pragma HLS STREAM variable=mid11 depth=10
	stream<matrix_t> mid12;
#pragma HLS STREAM variable=mid12 depth=10
	stream<matrix_t> mid13;
#pragma HLS STREAM variable=mid13 depth=10
	stream<matrix_t> mid14;
#pragma HLS STREAM variable=mid14 depth=10
	stream<matrix_t> mid15;
#pragma HLS STREAM variable=mid15 depth=10
	stream<matrix_t> mid16;
#pragma HLS STREAM variable=mid16 depth=10
	stream<matrix_t> mid17;
#pragma HLS STREAM variable=mid17 depth=10
	stream<matrix_t> mid18;
#pragma HLS STREAM variable=mid18 depth=10
	stream<matrix_t> mid19;
#pragma HLS STREAM variable=mid19 depth=10
	stream<matrix_t> mid20;
#pragma HLS STREAM variable=mid20 depth=10
	stream<matrix_t> mid21;
#pragma HLS STREAM variable=mid21 depth=10
	stream<matrix_t> mid22;
#pragma HLS STREAM variable=mid22 depth=10
	stream<matrix_t> mid23;
#pragma HLS STREAM variable=mid23 depth=10
	stream<matrix_t> mid24;
#pragma HLS STREAM variable=mid24 depth=10
	stream<matrix_t> mid25;
#pragma HLS STREAM variable=mid25 depth=10
	stream<matrix_t> mid26;
#pragma HLS STREAM variable=mid26 depth=10
	stream<matrix_t> mid27;
#pragma HLS STREAM variable=mid27 depth=10
	stream<matrix_t> mid28;
#pragma HLS STREAM variable=mid28 depth=10
	stream<matrix_t> mid29;
#pragma HLS STREAM variable=mid29 depth=10
	stream<matrix_t> mid30;
#pragma HLS STREAM variable=mid30 depth=10
	stream<matrix_t> mid31;
#pragma HLS STREAM variable=mid31 depth=10
	stream<matrix_t> mid32;
#pragma HLS STREAM variable=mid32 depth=10
	stream<matrix_t> mid33;
#pragma HLS STREAM variable=mid33 depth=10
	stream<matrix_t> mid34;
#pragma HLS STREAM variable=mid34 depth=10
	stream<matrix_t> mid35;
#pragma HLS STREAM variable=mid35 depth=10
	stream<matrix_t> mid36;
#pragma HLS STREAM variable=mid36 depth=10
	stream<matrix_t> mid37;
#pragma HLS STREAM variable=mid37 depth=10
	stream<matrix_t> mid38;
#pragma HLS STREAM variable=mid38 depth=10
	stream<matrix_t> mid39;
#pragma HLS STREAM variable=mid39 depth=10
	stream<matrix_t> mid40;
#pragma HLS STREAM variable=mid40 depth=10
	stream<matrix_t> mid41;
#pragma HLS STREAM variable=mid41 depth=10
	stream<matrix_t> mid42;
#pragma HLS STREAM variable=mid42 depth=10
	stream<matrix_t> mid43;
#pragma HLS STREAM variable=mid43 depth=10
	stream<matrix_t> mid44;
#pragma HLS STREAM variable=mid44 depth=10
	stream<matrix_t> mid45;
#pragma HLS STREAM variable=mid45 depth=10
	stream<matrix_t> mid46;
#pragma HLS STREAM variable=mid46 depth=10
	stream<matrix_t> mid47;
#pragma HLS STREAM variable=mid47 depth=10
	stream<matrix_t> mid48;
#pragma HLS STREAM variable=mid48 depth=10
	stream<matrix_t> mid49;
#pragma HLS STREAM variable=mid49 depth=10
	stream<matrix_t> mid50;
#pragma HLS STREAM variable=mid50 depth=10
	stream<matrix_t> mid51;
#pragma HLS STREAM variable=mid51 depth=10
	stream<matrix_t> mid52;
#pragma HLS STREAM variable=mid52 depth=10
	stream<matrix_t> mid53;
#pragma HLS STREAM variable=mid53 depth=10
	stream<matrix_t> mid54;
#pragma HLS STREAM variable=mid54 depth=10
	stream<matrix_t> mid55;
#pragma HLS STREAM variable=mid55 depth=10
	stream<matrix_t> mid56;
#pragma HLS STREAM variable=mid56 depth=10
	stream<matrix_t> mid57;
#pragma HLS STREAM variable=mid57 depth=10
	stream<matrix_t> mid58;
#pragma HLS STREAM variable=mid58 depth=10
	stream<matrix_t> mid59;
#pragma HLS STREAM variable=mid59 depth=10
	stream<matrix_t> mid60;
#pragma HLS STREAM variable=mid60 depth=10
	stream<matrix_t> mid61;
#pragma HLS STREAM variable=mid61 depth=10
	stream<matrix_t> mid62;
#pragma HLS STREAM variable=mid62 depth=10

	feeder(A, feedin);
	PE(0, feedin, result0, mid0);
	PE(1, mid0, result1, mid1);
	PE(2, mid1, result2, mid2);
	PE(3, mid2, result3, mid3);
	PE(4, mid3, result4, mid4);
	PE(5, mid4, result5, mid5);
	PE(6, mid5, result6, mid6);
	PE(7, mid6, result7, mid7);
	PE(8, mid7, result8, mid8);
	PE(9, mid8, result9, mid9);
	PE(10, mid9, result10, mid10);
	PE(11, mid10, result11, mid11);
	PE(12, mid11, result12, mid12);
	PE(13, mid12, result13, mid13);
	PE(14, mid13, result14, mid14);
	PE(15, mid14, result15, mid15);
	PE(16, mid15, result16, mid16);
	PE(17, mid16, result17, mid17);
	PE(18, mid17, result18, mid18);
	PE(19, mid18, result19, mid19);
	PE(20, mid19, result20, mid20);
	PE(21, mid20, result21, mid21);
	PE(22, mid21, result22, mid22);
	PE(23, mid22, result23, mid23);
	PE(24, mid23, result24, mid24);
	PE(25, mid24, result25, mid25);
	PE(26, mid25, result26, mid26);
	PE(27, mid26, result27, mid27);
	PE(28, mid27, result28, mid28);
	PE(29, mid28, result29, mid29);
	PE(30, mid29, result30, mid30);
	PE(31, mid30, result31, mid31);
	PE(32, mid31, result32, mid32);
	PE(33, mid32, result33, mid33);
	PE(34, mid33, result34, mid34);
	PE(35, mid34, result35, mid35);
	PE(36, mid35, result36, mid36);
	PE(37, mid36, result37, mid37);
	PE(38, mid37, result38, mid38);
	PE(39, mid38, result39, mid39);
	PE(40, mid39, result40, mid40);
	PE(41, mid40, result41, mid41);
	PE(42, mid41, result42, mid42);
	PE(43, mid42, result43, mid43);
	PE(44, mid43, result44, mid44);
	PE(45, mid44, result45, mid45);
	PE(46, mid45, result46, mid46);
	PE(47, mid46, result47, mid47);
	PE(48, mid47, result48, mid48);
	PE(49, mid48, result49, mid49);
	PE(50, mid49, result50, mid50);
	PE(51, mid50, result51, mid51);
	PE(52, mid51, result52, mid52);
	PE(53, mid52, result53, mid53);
	PE(54, mid53, result54, mid54);
	PE(55, mid54, result55, mid55);
	PE(56, mid55, result56, mid56);
	PE(57, mid56, result57, mid57);
	PE(58, mid57, result58, mid58);
	PE(59, mid58, result59, mid59);
	PE(60, mid59, result60, mid60);
	PE(61, mid60, result61, mid61);
	PE(62, mid61, result62, mid62);
	PE_last(mid62, result63);

	collector(
		result0,
		result1,
		result2,
		result3,
		result4,
		result5,
		result6,
		result7,
		result8,
		result9,
		result10,
		result11,
		result12,
		result13,
		result14,
		result15,
		result16,
		result17,
		result18,
		result19,
		result20,
		result21,
		result22,
		result23,
		result24,
		result25,
		result26,
		result27,
		result28,
		result29,
		result30,
		result31,
		result32,
		result33,
		result34,
		result35,
		result36,
		result37,
		result38,
		result39,
		result40,
		result41,
		result42,
		result43,
		result44,
		result45,
		result46,
		result47,
		result48,
		result49,
		result50,
		result51,
		result52,
		result53,
		result54,
		result55,
		result56,
		result57,
		result58,
		result59,
		result60,
		result61,
		result62,
		result63,
	       	L);

	return 0;
}
