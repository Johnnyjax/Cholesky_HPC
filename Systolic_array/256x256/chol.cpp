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
	stream<matrix_t> &feedout64,
	stream<matrix_t> &feedout65,
	stream<matrix_t> &feedout66,
	stream<matrix_t> &feedout67,
	stream<matrix_t> &feedout68,
	stream<matrix_t> &feedout69,
	stream<matrix_t> &feedout70,
	stream<matrix_t> &feedout71,
	stream<matrix_t> &feedout72,
	stream<matrix_t> &feedout73,
	stream<matrix_t> &feedout74,
	stream<matrix_t> &feedout75,
	stream<matrix_t> &feedout76,
	stream<matrix_t> &feedout77,
	stream<matrix_t> &feedout78,
	stream<matrix_t> &feedout79,
	stream<matrix_t> &feedout80,
	stream<matrix_t> &feedout81,
	stream<matrix_t> &feedout82,
	stream<matrix_t> &feedout83,
	stream<matrix_t> &feedout84,
	stream<matrix_t> &feedout85,
	stream<matrix_t> &feedout86,
	stream<matrix_t> &feedout87,
	stream<matrix_t> &feedout88,
	stream<matrix_t> &feedout89,
	stream<matrix_t> &feedout90,
	stream<matrix_t> &feedout91,
	stream<matrix_t> &feedout92,
	stream<matrix_t> &feedout93,
	stream<matrix_t> &feedout94,
	stream<matrix_t> &feedout95,
	stream<matrix_t> &feedout96,
	stream<matrix_t> &feedout97,
	stream<matrix_t> &feedout98,
	stream<matrix_t> &feedout99,
	stream<matrix_t> &feedout100,
	stream<matrix_t> &feedout101,
	stream<matrix_t> &feedout102,
	stream<matrix_t> &feedout103,
	stream<matrix_t> &feedout104,
	stream<matrix_t> &feedout105,
	stream<matrix_t> &feedout106,
	stream<matrix_t> &feedout107,
	stream<matrix_t> &feedout108,
	stream<matrix_t> &feedout109,
	stream<matrix_t> &feedout110,
	stream<matrix_t> &feedout111,
	stream<matrix_t> &feedout112,
	stream<matrix_t> &feedout113,
	stream<matrix_t> &feedout114,
	stream<matrix_t> &feedout115,
	stream<matrix_t> &feedout116,
	stream<matrix_t> &feedout117,
	stream<matrix_t> &feedout118,
	stream<matrix_t> &feedout119,
	stream<matrix_t> &feedout120,
	stream<matrix_t> &feedout121,
	stream<matrix_t> &feedout122,
	stream<matrix_t> &feedout123,
	stream<matrix_t> &feedout124,
	stream<matrix_t> &feedout125,
	stream<matrix_t> &feedout126,
	stream<matrix_t> &feedout127,
	stream<matrix_t> &feedout128,
	stream<matrix_t> &feedout129,
	stream<matrix_t> &feedout130,
	stream<matrix_t> &feedout131,
	stream<matrix_t> &feedout132,
	stream<matrix_t> &feedout133,
	stream<matrix_t> &feedout134,
	stream<matrix_t> &feedout135,
	stream<matrix_t> &feedout136,
	stream<matrix_t> &feedout137,
	stream<matrix_t> &feedout138,
	stream<matrix_t> &feedout139,
	stream<matrix_t> &feedout140,
	stream<matrix_t> &feedout141,
	stream<matrix_t> &feedout142,
	stream<matrix_t> &feedout143,
	stream<matrix_t> &feedout144,
	stream<matrix_t> &feedout145,
	stream<matrix_t> &feedout146,
	stream<matrix_t> &feedout147,
	stream<matrix_t> &feedout148,
	stream<matrix_t> &feedout149,
	stream<matrix_t> &feedout150,
	stream<matrix_t> &feedout151,
	stream<matrix_t> &feedout152,
	stream<matrix_t> &feedout153,
	stream<matrix_t> &feedout154,
	stream<matrix_t> &feedout155,
	stream<matrix_t> &feedout156,
	stream<matrix_t> &feedout157,
	stream<matrix_t> &feedout158,
	stream<matrix_t> &feedout159,
	stream<matrix_t> &feedout160,
	stream<matrix_t> &feedout161,
	stream<matrix_t> &feedout162,
	stream<matrix_t> &feedout163,
	stream<matrix_t> &feedout164,
	stream<matrix_t> &feedout165,
	stream<matrix_t> &feedout166,
	stream<matrix_t> &feedout167,
	stream<matrix_t> &feedout168,
	stream<matrix_t> &feedout169,
	stream<matrix_t> &feedout170,
	stream<matrix_t> &feedout171,
	stream<matrix_t> &feedout172,
	stream<matrix_t> &feedout173,
	stream<matrix_t> &feedout174,
	stream<matrix_t> &feedout175,
	stream<matrix_t> &feedout176,
	stream<matrix_t> &feedout177,
	stream<matrix_t> &feedout178,
	stream<matrix_t> &feedout179,
	stream<matrix_t> &feedout180,
	stream<matrix_t> &feedout181,
	stream<matrix_t> &feedout182,
	stream<matrix_t> &feedout183,
	stream<matrix_t> &feedout184,
	stream<matrix_t> &feedout185,
	stream<matrix_t> &feedout186,
	stream<matrix_t> &feedout187,
	stream<matrix_t> &feedout188,
	stream<matrix_t> &feedout189,
	stream<matrix_t> &feedout190,
	stream<matrix_t> &feedout191,
	stream<matrix_t> &feedout192,
	stream<matrix_t> &feedout193,
	stream<matrix_t> &feedout194,
	stream<matrix_t> &feedout195,
	stream<matrix_t> &feedout196,
	stream<matrix_t> &feedout197,
	stream<matrix_t> &feedout198,
	stream<matrix_t> &feedout199,
	stream<matrix_t> &feedout200,
	stream<matrix_t> &feedout201,
	stream<matrix_t> &feedout202,
	stream<matrix_t> &feedout203,
	stream<matrix_t> &feedout204,
	stream<matrix_t> &feedout205,
	stream<matrix_t> &feedout206,
	stream<matrix_t> &feedout207,
	stream<matrix_t> &feedout208,
	stream<matrix_t> &feedout209,
	stream<matrix_t> &feedout210,
	stream<matrix_t> &feedout211,
	stream<matrix_t> &feedout212,
	stream<matrix_t> &feedout213,
	stream<matrix_t> &feedout214,
	stream<matrix_t> &feedout215,
	stream<matrix_t> &feedout216,
	stream<matrix_t> &feedout217,
	stream<matrix_t> &feedout218,
	stream<matrix_t> &feedout219,
	stream<matrix_t> &feedout220,
	stream<matrix_t> &feedout221,
	stream<matrix_t> &feedout222,
	stream<matrix_t> &feedout223,
	stream<matrix_t> &feedout224,
	stream<matrix_t> &feedout225,
	stream<matrix_t> &feedout226,
	stream<matrix_t> &feedout227,
	stream<matrix_t> &feedout228,
	stream<matrix_t> &feedout229,
	stream<matrix_t> &feedout230,
	stream<matrix_t> &feedout231,
	stream<matrix_t> &feedout232,
	stream<matrix_t> &feedout233,
	stream<matrix_t> &feedout234,
	stream<matrix_t> &feedout235,
	stream<matrix_t> &feedout236,
	stream<matrix_t> &feedout237,
	stream<matrix_t> &feedout238,
	stream<matrix_t> &feedout239,
	stream<matrix_t> &feedout240,
	stream<matrix_t> &feedout241,
	stream<matrix_t> &feedout242,
	stream<matrix_t> &feedout243,
	stream<matrix_t> &feedout244,
	stream<matrix_t> &feedout245,
	stream<matrix_t> &feedout246,
	stream<matrix_t> &feedout247,
	stream<matrix_t> &feedout248,
	stream<matrix_t> &feedout249,
	stream<matrix_t> &feedout250,
	stream<matrix_t> &feedout251,
	stream<matrix_t> &feedout252,
	stream<matrix_t> &feedout253,
	stream<matrix_t> &feedout254,
	stream<matrix_t> &feedout255,
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

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 64)
			L[i][64] = feedout64.read();
		else
			L[i][64] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 65)
			L[i][65] = feedout65.read();
		else
			L[i][65] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 66)
			L[i][66] = feedout66.read();
		else
			L[i][66] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 67)
			L[i][67] = feedout67.read();
		else
			L[i][67] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 68)
			L[i][68] = feedout68.read();
		else
			L[i][68] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 69)
			L[i][69] = feedout69.read();
		else
			L[i][69] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 70)
			L[i][70] = feedout70.read();
		else
			L[i][70] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 71)
			L[i][71] = feedout71.read();
		else
			L[i][71] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 72)
			L[i][72] = feedout72.read();
		else
			L[i][72] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 73)
			L[i][73] = feedout73.read();
		else
			L[i][73] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 74)
			L[i][74] = feedout74.read();
		else
			L[i][74] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 75)
			L[i][75] = feedout75.read();
		else
			L[i][75] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 76)
			L[i][76] = feedout76.read();
		else
			L[i][76] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 77)
			L[i][77] = feedout77.read();
		else
			L[i][77] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 78)
			L[i][78] = feedout78.read();
		else
			L[i][78] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 79)
			L[i][79] = feedout79.read();
		else
			L[i][79] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 80)
			L[i][80] = feedout80.read();
		else
			L[i][80] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 81)
			L[i][81] = feedout81.read();
		else
			L[i][81] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 82)
			L[i][82] = feedout82.read();
		else
			L[i][82] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 83)
			L[i][83] = feedout83.read();
		else
			L[i][83] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 84)
			L[i][84] = feedout84.read();
		else
			L[i][84] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 85)
			L[i][85] = feedout85.read();
		else
			L[i][85] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 86)
			L[i][86] = feedout86.read();
		else
			L[i][86] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 87)
			L[i][87] = feedout87.read();
		else
			L[i][87] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 88)
			L[i][88] = feedout88.read();
		else
			L[i][88] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 89)
			L[i][89] = feedout89.read();
		else
			L[i][89] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 90)
			L[i][90] = feedout90.read();
		else
			L[i][90] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 91)
			L[i][91] = feedout91.read();
		else
			L[i][91] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 92)
			L[i][92] = feedout92.read();
		else
			L[i][92] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 93)
			L[i][93] = feedout93.read();
		else
			L[i][93] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 94)
			L[i][94] = feedout94.read();
		else
			L[i][94] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 95)
			L[i][95] = feedout95.read();
		else
			L[i][95] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 96)
			L[i][96] = feedout96.read();
		else
			L[i][96] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 97)
			L[i][97] = feedout97.read();
		else
			L[i][97] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 98)
			L[i][98] = feedout98.read();
		else
			L[i][98] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 99)
			L[i][99] = feedout99.read();
		else
			L[i][99] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 100)
			L[i][100] = feedout100.read();
		else
			L[i][100] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 101)
			L[i][101] = feedout101.read();
		else
			L[i][101] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 102)
			L[i][102] = feedout102.read();
		else
			L[i][102] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 103)
			L[i][103] = feedout103.read();
		else
			L[i][103] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 104)
			L[i][104] = feedout104.read();
		else
			L[i][104] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 105)
			L[i][105] = feedout105.read();
		else
			L[i][105] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 106)
			L[i][106] = feedout106.read();
		else
			L[i][106] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 107)
			L[i][107] = feedout107.read();
		else
			L[i][107] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 108)
			L[i][108] = feedout108.read();
		else
			L[i][108] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 109)
			L[i][109] = feedout109.read();
		else
			L[i][109] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 110)
			L[i][110] = feedout110.read();
		else
			L[i][110] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 111)
			L[i][111] = feedout111.read();
		else
			L[i][111] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 112)
			L[i][112] = feedout112.read();
		else
			L[i][112] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 113)
			L[i][113] = feedout113.read();
		else
			L[i][113] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 114)
			L[i][114] = feedout114.read();
		else
			L[i][114] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 115)
			L[i][115] = feedout115.read();
		else
			L[i][115] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 116)
			L[i][116] = feedout116.read();
		else
			L[i][116] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 117)
			L[i][117] = feedout117.read();
		else
			L[i][117] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 118)
			L[i][118] = feedout118.read();
		else
			L[i][118] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 119)
			L[i][119] = feedout119.read();
		else
			L[i][119] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 120)
			L[i][120] = feedout120.read();
		else
			L[i][120] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 121)
			L[i][121] = feedout121.read();
		else
			L[i][121] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 122)
			L[i][122] = feedout122.read();
		else
			L[i][122] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 123)
			L[i][123] = feedout123.read();
		else
			L[i][123] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 124)
			L[i][124] = feedout124.read();
		else
			L[i][124] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 125)
			L[i][125] = feedout125.read();
		else
			L[i][125] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 126)
			L[i][126] = feedout126.read();
		else
			L[i][126] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 127)
			L[i][127] = feedout127.read();
		else
			L[i][127] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 128)
			L[i][128] = feedout128.read();
		else
			L[i][128] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 129)
			L[i][129] = feedout129.read();
		else
			L[i][129] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 130)
			L[i][130] = feedout130.read();
		else
			L[i][130] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 131)
			L[i][131] = feedout131.read();
		else
			L[i][131] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 132)
			L[i][132] = feedout132.read();
		else
			L[i][132] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 133)
			L[i][133] = feedout133.read();
		else
			L[i][133] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 134)
			L[i][134] = feedout134.read();
		else
			L[i][134] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 135)
			L[i][135] = feedout135.read();
		else
			L[i][135] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 136)
			L[i][136] = feedout136.read();
		else
			L[i][136] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 137)
			L[i][137] = feedout137.read();
		else
			L[i][137] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 138)
			L[i][138] = feedout138.read();
		else
			L[i][138] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 139)
			L[i][139] = feedout139.read();
		else
			L[i][139] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 140)
			L[i][140] = feedout140.read();
		else
			L[i][140] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 141)
			L[i][141] = feedout141.read();
		else
			L[i][141] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 142)
			L[i][142] = feedout142.read();
		else
			L[i][142] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 143)
			L[i][143] = feedout143.read();
		else
			L[i][143] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 144)
			L[i][144] = feedout144.read();
		else
			L[i][144] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 145)
			L[i][145] = feedout145.read();
		else
			L[i][145] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 146)
			L[i][146] = feedout146.read();
		else
			L[i][146] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 147)
			L[i][147] = feedout147.read();
		else
			L[i][147] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 148)
			L[i][148] = feedout148.read();
		else
			L[i][148] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 149)
			L[i][149] = feedout149.read();
		else
			L[i][149] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 150)
			L[i][150] = feedout150.read();
		else
			L[i][150] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 151)
			L[i][151] = feedout151.read();
		else
			L[i][151] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 152)
			L[i][152] = feedout152.read();
		else
			L[i][152] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 153)
			L[i][153] = feedout153.read();
		else
			L[i][153] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 154)
			L[i][154] = feedout154.read();
		else
			L[i][154] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 155)
			L[i][155] = feedout155.read();
		else
			L[i][155] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 156)
			L[i][156] = feedout156.read();
		else
			L[i][156] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 157)
			L[i][157] = feedout157.read();
		else
			L[i][157] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 158)
			L[i][158] = feedout158.read();
		else
			L[i][158] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 159)
			L[i][159] = feedout159.read();
		else
			L[i][159] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 160)
			L[i][160] = feedout160.read();
		else
			L[i][160] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 161)
			L[i][161] = feedout161.read();
		else
			L[i][161] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 162)
			L[i][162] = feedout162.read();
		else
			L[i][162] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 163)
			L[i][163] = feedout163.read();
		else
			L[i][163] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 164)
			L[i][164] = feedout164.read();
		else
			L[i][164] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 165)
			L[i][165] = feedout165.read();
		else
			L[i][165] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 166)
			L[i][166] = feedout166.read();
		else
			L[i][166] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 167)
			L[i][167] = feedout167.read();
		else
			L[i][167] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 168)
			L[i][168] = feedout168.read();
		else
			L[i][168] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 169)
			L[i][169] = feedout169.read();
		else
			L[i][169] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 170)
			L[i][170] = feedout170.read();
		else
			L[i][170] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 171)
			L[i][171] = feedout171.read();
		else
			L[i][171] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 172)
			L[i][172] = feedout172.read();
		else
			L[i][172] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 173)
			L[i][173] = feedout173.read();
		else
			L[i][173] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 174)
			L[i][174] = feedout174.read();
		else
			L[i][174] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 175)
			L[i][175] = feedout175.read();
		else
			L[i][175] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 176)
			L[i][176] = feedout176.read();
		else
			L[i][176] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 177)
			L[i][177] = feedout177.read();
		else
			L[i][177] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 178)
			L[i][178] = feedout178.read();
		else
			L[i][178] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 179)
			L[i][179] = feedout179.read();
		else
			L[i][179] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 180)
			L[i][180] = feedout180.read();
		else
			L[i][180] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 181)
			L[i][181] = feedout181.read();
		else
			L[i][181] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 182)
			L[i][182] = feedout182.read();
		else
			L[i][182] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 183)
			L[i][183] = feedout183.read();
		else
			L[i][183] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 184)
			L[i][184] = feedout184.read();
		else
			L[i][184] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 185)
			L[i][185] = feedout185.read();
		else
			L[i][185] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 186)
			L[i][186] = feedout186.read();
		else
			L[i][186] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 187)
			L[i][187] = feedout187.read();
		else
			L[i][187] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 188)
			L[i][188] = feedout188.read();
		else
			L[i][188] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 189)
			L[i][189] = feedout189.read();
		else
			L[i][189] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 190)
			L[i][190] = feedout190.read();
		else
			L[i][190] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 191)
			L[i][191] = feedout191.read();
		else
			L[i][191] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 192)
			L[i][192] = feedout192.read();
		else
			L[i][192] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 193)
			L[i][193] = feedout193.read();
		else
			L[i][193] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 194)
			L[i][194] = feedout194.read();
		else
			L[i][194] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 195)
			L[i][195] = feedout195.read();
		else
			L[i][195] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 196)
			L[i][196] = feedout196.read();
		else
			L[i][196] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 197)
			L[i][197] = feedout197.read();
		else
			L[i][197] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 198)
			L[i][198] = feedout198.read();
		else
			L[i][198] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 199)
			L[i][199] = feedout199.read();
		else
			L[i][199] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 200)
			L[i][200] = feedout200.read();
		else
			L[i][200] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 201)
			L[i][201] = feedout201.read();
		else
			L[i][201] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 202)
			L[i][202] = feedout202.read();
		else
			L[i][202] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 203)
			L[i][203] = feedout203.read();
		else
			L[i][203] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 204)
			L[i][204] = feedout204.read();
		else
			L[i][204] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 205)
			L[i][205] = feedout205.read();
		else
			L[i][205] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 206)
			L[i][206] = feedout206.read();
		else
			L[i][206] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 207)
			L[i][207] = feedout207.read();
		else
			L[i][207] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 208)
			L[i][208] = feedout208.read();
		else
			L[i][208] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 209)
			L[i][209] = feedout209.read();
		else
			L[i][209] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 210)
			L[i][210] = feedout210.read();
		else
			L[i][210] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 211)
			L[i][211] = feedout211.read();
		else
			L[i][211] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 212)
			L[i][212] = feedout212.read();
		else
			L[i][212] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 213)
			L[i][213] = feedout213.read();
		else
			L[i][213] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 214)
			L[i][214] = feedout214.read();
		else
			L[i][214] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 215)
			L[i][215] = feedout215.read();
		else
			L[i][215] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 216)
			L[i][216] = feedout216.read();
		else
			L[i][216] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 217)
			L[i][217] = feedout217.read();
		else
			L[i][217] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 218)
			L[i][218] = feedout218.read();
		else
			L[i][218] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 219)
			L[i][219] = feedout219.read();
		else
			L[i][219] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 220)
			L[i][220] = feedout220.read();
		else
			L[i][220] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 221)
			L[i][221] = feedout221.read();
		else
			L[i][221] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 222)
			L[i][222] = feedout222.read();
		else
			L[i][222] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 223)
			L[i][223] = feedout223.read();
		else
			L[i][223] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 224)
			L[i][224] = feedout224.read();
		else
			L[i][224] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 225)
			L[i][225] = feedout225.read();
		else
			L[i][225] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 226)
			L[i][226] = feedout226.read();
		else
			L[i][226] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 227)
			L[i][227] = feedout227.read();
		else
			L[i][227] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 228)
			L[i][228] = feedout228.read();
		else
			L[i][228] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 229)
			L[i][229] = feedout229.read();
		else
			L[i][229] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 230)
			L[i][230] = feedout230.read();
		else
			L[i][230] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 231)
			L[i][231] = feedout231.read();
		else
			L[i][231] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 232)
			L[i][232] = feedout232.read();
		else
			L[i][232] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 233)
			L[i][233] = feedout233.read();
		else
			L[i][233] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 234)
			L[i][234] = feedout234.read();
		else
			L[i][234] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 235)
			L[i][235] = feedout235.read();
		else
			L[i][235] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 236)
			L[i][236] = feedout236.read();
		else
			L[i][236] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 237)
			L[i][237] = feedout237.read();
		else
			L[i][237] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 238)
			L[i][238] = feedout238.read();
		else
			L[i][238] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 239)
			L[i][239] = feedout239.read();
		else
			L[i][239] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 240)
			L[i][240] = feedout240.read();
		else
			L[i][240] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 241)
			L[i][241] = feedout241.read();
		else
			L[i][241] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 242)
			L[i][242] = feedout242.read();
		else
			L[i][242] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 243)
			L[i][243] = feedout243.read();
		else
			L[i][243] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 244)
			L[i][244] = feedout244.read();
		else
			L[i][244] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 245)
			L[i][245] = feedout245.read();
		else
			L[i][245] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 246)
			L[i][246] = feedout246.read();
		else
			L[i][246] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 247)
			L[i][247] = feedout247.read();
		else
			L[i][247] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 248)
			L[i][248] = feedout248.read();
		else
			L[i][248] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 249)
			L[i][249] = feedout249.read();
		else
			L[i][249] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 250)
			L[i][250] = feedout250.read();
		else
			L[i][250] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 251)
			L[i][251] = feedout251.read();
		else
			L[i][251] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 252)
			L[i][252] = feedout252.read();
		else
			L[i][252] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 253)
			L[i][253] = feedout253.read();
		else
			L[i][253] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 254)
			L[i][254] = feedout254.read();
		else
			L[i][254] = 0;
	}

	for(i = 0; i < matrix_size; i++)
	{
#pragma HLS pipeline II=1
		if(i >= 255)
			L[i][255] = feedout255.read();
		else
			L[i][255] = 0;
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
	stream<matrix_t> result64;
#pragma HLS STREAM variable=result64 depth=10
	stream<matrix_t> result65;
#pragma HLS STREAM variable=result65 depth=10
	stream<matrix_t> result66;
#pragma HLS STREAM variable=result66 depth=10
	stream<matrix_t> result67;
#pragma HLS STREAM variable=result67 depth=10
	stream<matrix_t> result68;
#pragma HLS STREAM variable=result68 depth=10
	stream<matrix_t> result69;
#pragma HLS STREAM variable=result69 depth=10
	stream<matrix_t> result70;
#pragma HLS STREAM variable=result70 depth=10
	stream<matrix_t> result71;
#pragma HLS STREAM variable=result71 depth=10
	stream<matrix_t> result72;
#pragma HLS STREAM variable=result72 depth=10
	stream<matrix_t> result73;
#pragma HLS STREAM variable=result73 depth=10
	stream<matrix_t> result74;
#pragma HLS STREAM variable=result74 depth=10
	stream<matrix_t> result75;
#pragma HLS STREAM variable=result75 depth=10
	stream<matrix_t> result76;
#pragma HLS STREAM variable=result76 depth=10
	stream<matrix_t> result77;
#pragma HLS STREAM variable=result77 depth=10
	stream<matrix_t> result78;
#pragma HLS STREAM variable=result78 depth=10
	stream<matrix_t> result79;
#pragma HLS STREAM variable=result79 depth=10
	stream<matrix_t> result80;
#pragma HLS STREAM variable=result80 depth=10
	stream<matrix_t> result81;
#pragma HLS STREAM variable=result81 depth=10
	stream<matrix_t> result82;
#pragma HLS STREAM variable=result82 depth=10
	stream<matrix_t> result83;
#pragma HLS STREAM variable=result83 depth=10
	stream<matrix_t> result84;
#pragma HLS STREAM variable=result84 depth=10
	stream<matrix_t> result85;
#pragma HLS STREAM variable=result85 depth=10
	stream<matrix_t> result86;
#pragma HLS STREAM variable=result86 depth=10
	stream<matrix_t> result87;
#pragma HLS STREAM variable=result87 depth=10
	stream<matrix_t> result88;
#pragma HLS STREAM variable=result88 depth=10
	stream<matrix_t> result89;
#pragma HLS STREAM variable=result89 depth=10
	stream<matrix_t> result90;
#pragma HLS STREAM variable=result90 depth=10
	stream<matrix_t> result91;
#pragma HLS STREAM variable=result91 depth=10
	stream<matrix_t> result92;
#pragma HLS STREAM variable=result92 depth=10
	stream<matrix_t> result93;
#pragma HLS STREAM variable=result93 depth=10
	stream<matrix_t> result94;
#pragma HLS STREAM variable=result94 depth=10
	stream<matrix_t> result95;
#pragma HLS STREAM variable=result95 depth=10
	stream<matrix_t> result96;
#pragma HLS STREAM variable=result96 depth=10
	stream<matrix_t> result97;
#pragma HLS STREAM variable=result97 depth=10
	stream<matrix_t> result98;
#pragma HLS STREAM variable=result98 depth=10
	stream<matrix_t> result99;
#pragma HLS STREAM variable=result99 depth=10
	stream<matrix_t> result100;
#pragma HLS STREAM variable=result100 depth=10
	stream<matrix_t> result101;
#pragma HLS STREAM variable=result101 depth=10
	stream<matrix_t> result102;
#pragma HLS STREAM variable=result102 depth=10
	stream<matrix_t> result103;
#pragma HLS STREAM variable=result103 depth=10
	stream<matrix_t> result104;
#pragma HLS STREAM variable=result104 depth=10
	stream<matrix_t> result105;
#pragma HLS STREAM variable=result105 depth=10
	stream<matrix_t> result106;
#pragma HLS STREAM variable=result106 depth=10
	stream<matrix_t> result107;
#pragma HLS STREAM variable=result107 depth=10
	stream<matrix_t> result108;
#pragma HLS STREAM variable=result108 depth=10
	stream<matrix_t> result109;
#pragma HLS STREAM variable=result109 depth=10
	stream<matrix_t> result110;
#pragma HLS STREAM variable=result110 depth=10
	stream<matrix_t> result111;
#pragma HLS STREAM variable=result111 depth=10
	stream<matrix_t> result112;
#pragma HLS STREAM variable=result112 depth=10
	stream<matrix_t> result113;
#pragma HLS STREAM variable=result113 depth=10
	stream<matrix_t> result114;
#pragma HLS STREAM variable=result114 depth=10
	stream<matrix_t> result115;
#pragma HLS STREAM variable=result115 depth=10
	stream<matrix_t> result116;
#pragma HLS STREAM variable=result116 depth=10
	stream<matrix_t> result117;
#pragma HLS STREAM variable=result117 depth=10
	stream<matrix_t> result118;
#pragma HLS STREAM variable=result118 depth=10
	stream<matrix_t> result119;
#pragma HLS STREAM variable=result119 depth=10
	stream<matrix_t> result120;
#pragma HLS STREAM variable=result120 depth=10
	stream<matrix_t> result121;
#pragma HLS STREAM variable=result121 depth=10
	stream<matrix_t> result122;
#pragma HLS STREAM variable=result122 depth=10
	stream<matrix_t> result123;
#pragma HLS STREAM variable=result123 depth=10
	stream<matrix_t> result124;
#pragma HLS STREAM variable=result124 depth=10
	stream<matrix_t> result125;
#pragma HLS STREAM variable=result125 depth=10
	stream<matrix_t> result126;
#pragma HLS STREAM variable=result126 depth=10
	stream<matrix_t> result127;
#pragma HLS STREAM variable=result127 depth=10
	stream<matrix_t> result128;
#pragma HLS STREAM variable=result128 depth=10
	stream<matrix_t> result129;
#pragma HLS STREAM variable=result129 depth=10
	stream<matrix_t> result130;
#pragma HLS STREAM variable=result130 depth=10
	stream<matrix_t> result131;
#pragma HLS STREAM variable=result131 depth=10
	stream<matrix_t> result132;
#pragma HLS STREAM variable=result132 depth=10
	stream<matrix_t> result133;
#pragma HLS STREAM variable=result133 depth=10
	stream<matrix_t> result134;
#pragma HLS STREAM variable=result134 depth=10
	stream<matrix_t> result135;
#pragma HLS STREAM variable=result135 depth=10
	stream<matrix_t> result136;
#pragma HLS STREAM variable=result136 depth=10
	stream<matrix_t> result137;
#pragma HLS STREAM variable=result137 depth=10
	stream<matrix_t> result138;
#pragma HLS STREAM variable=result138 depth=10
	stream<matrix_t> result139;
#pragma HLS STREAM variable=result139 depth=10
	stream<matrix_t> result140;
#pragma HLS STREAM variable=result140 depth=10
	stream<matrix_t> result141;
#pragma HLS STREAM variable=result141 depth=10
	stream<matrix_t> result142;
#pragma HLS STREAM variable=result142 depth=10
	stream<matrix_t> result143;
#pragma HLS STREAM variable=result143 depth=10
	stream<matrix_t> result144;
#pragma HLS STREAM variable=result144 depth=10
	stream<matrix_t> result145;
#pragma HLS STREAM variable=result145 depth=10
	stream<matrix_t> result146;
#pragma HLS STREAM variable=result146 depth=10
	stream<matrix_t> result147;
#pragma HLS STREAM variable=result147 depth=10
	stream<matrix_t> result148;
#pragma HLS STREAM variable=result148 depth=10
	stream<matrix_t> result149;
#pragma HLS STREAM variable=result149 depth=10
	stream<matrix_t> result150;
#pragma HLS STREAM variable=result150 depth=10
	stream<matrix_t> result151;
#pragma HLS STREAM variable=result151 depth=10
	stream<matrix_t> result152;
#pragma HLS STREAM variable=result152 depth=10
	stream<matrix_t> result153;
#pragma HLS STREAM variable=result153 depth=10
	stream<matrix_t> result154;
#pragma HLS STREAM variable=result154 depth=10
	stream<matrix_t> result155;
#pragma HLS STREAM variable=result155 depth=10
	stream<matrix_t> result156;
#pragma HLS STREAM variable=result156 depth=10
	stream<matrix_t> result157;
#pragma HLS STREAM variable=result157 depth=10
	stream<matrix_t> result158;
#pragma HLS STREAM variable=result158 depth=10
	stream<matrix_t> result159;
#pragma HLS STREAM variable=result159 depth=10
	stream<matrix_t> result160;
#pragma HLS STREAM variable=result160 depth=10
	stream<matrix_t> result161;
#pragma HLS STREAM variable=result161 depth=10
	stream<matrix_t> result162;
#pragma HLS STREAM variable=result162 depth=10
	stream<matrix_t> result163;
#pragma HLS STREAM variable=result163 depth=10
	stream<matrix_t> result164;
#pragma HLS STREAM variable=result164 depth=10
	stream<matrix_t> result165;
#pragma HLS STREAM variable=result165 depth=10
	stream<matrix_t> result166;
#pragma HLS STREAM variable=result166 depth=10
	stream<matrix_t> result167;
#pragma HLS STREAM variable=result167 depth=10
	stream<matrix_t> result168;
#pragma HLS STREAM variable=result168 depth=10
	stream<matrix_t> result169;
#pragma HLS STREAM variable=result169 depth=10
	stream<matrix_t> result170;
#pragma HLS STREAM variable=result170 depth=10
	stream<matrix_t> result171;
#pragma HLS STREAM variable=result171 depth=10
	stream<matrix_t> result172;
#pragma HLS STREAM variable=result172 depth=10
	stream<matrix_t> result173;
#pragma HLS STREAM variable=result173 depth=10
	stream<matrix_t> result174;
#pragma HLS STREAM variable=result174 depth=10
	stream<matrix_t> result175;
#pragma HLS STREAM variable=result175 depth=10
	stream<matrix_t> result176;
#pragma HLS STREAM variable=result176 depth=10
	stream<matrix_t> result177;
#pragma HLS STREAM variable=result177 depth=10
	stream<matrix_t> result178;
#pragma HLS STREAM variable=result178 depth=10
	stream<matrix_t> result179;
#pragma HLS STREAM variable=result179 depth=10
	stream<matrix_t> result180;
#pragma HLS STREAM variable=result180 depth=10
	stream<matrix_t> result181;
#pragma HLS STREAM variable=result181 depth=10
	stream<matrix_t> result182;
#pragma HLS STREAM variable=result182 depth=10
	stream<matrix_t> result183;
#pragma HLS STREAM variable=result183 depth=10
	stream<matrix_t> result184;
#pragma HLS STREAM variable=result184 depth=10
	stream<matrix_t> result185;
#pragma HLS STREAM variable=result185 depth=10
	stream<matrix_t> result186;
#pragma HLS STREAM variable=result186 depth=10
	stream<matrix_t> result187;
#pragma HLS STREAM variable=result187 depth=10
	stream<matrix_t> result188;
#pragma HLS STREAM variable=result188 depth=10
	stream<matrix_t> result189;
#pragma HLS STREAM variable=result189 depth=10
	stream<matrix_t> result190;
#pragma HLS STREAM variable=result190 depth=10
	stream<matrix_t> result191;
#pragma HLS STREAM variable=result191 depth=10
	stream<matrix_t> result192;
#pragma HLS STREAM variable=result192 depth=10
	stream<matrix_t> result193;
#pragma HLS STREAM variable=result193 depth=10
	stream<matrix_t> result194;
#pragma HLS STREAM variable=result194 depth=10
	stream<matrix_t> result195;
#pragma HLS STREAM variable=result195 depth=10
	stream<matrix_t> result196;
#pragma HLS STREAM variable=result196 depth=10
	stream<matrix_t> result197;
#pragma HLS STREAM variable=result197 depth=10
	stream<matrix_t> result198;
#pragma HLS STREAM variable=result198 depth=10
	stream<matrix_t> result199;
#pragma HLS STREAM variable=result199 depth=10
	stream<matrix_t> result200;
#pragma HLS STREAM variable=result200 depth=10
	stream<matrix_t> result201;
#pragma HLS STREAM variable=result201 depth=10
	stream<matrix_t> result202;
#pragma HLS STREAM variable=result202 depth=10
	stream<matrix_t> result203;
#pragma HLS STREAM variable=result203 depth=10
	stream<matrix_t> result204;
#pragma HLS STREAM variable=result204 depth=10
	stream<matrix_t> result205;
#pragma HLS STREAM variable=result205 depth=10
	stream<matrix_t> result206;
#pragma HLS STREAM variable=result206 depth=10
	stream<matrix_t> result207;
#pragma HLS STREAM variable=result207 depth=10
	stream<matrix_t> result208;
#pragma HLS STREAM variable=result208 depth=10
	stream<matrix_t> result209;
#pragma HLS STREAM variable=result209 depth=10
	stream<matrix_t> result210;
#pragma HLS STREAM variable=result210 depth=10
	stream<matrix_t> result211;
#pragma HLS STREAM variable=result211 depth=10
	stream<matrix_t> result212;
#pragma HLS STREAM variable=result212 depth=10
	stream<matrix_t> result213;
#pragma HLS STREAM variable=result213 depth=10
	stream<matrix_t> result214;
#pragma HLS STREAM variable=result214 depth=10
	stream<matrix_t> result215;
#pragma HLS STREAM variable=result215 depth=10
	stream<matrix_t> result216;
#pragma HLS STREAM variable=result216 depth=10
	stream<matrix_t> result217;
#pragma HLS STREAM variable=result217 depth=10
	stream<matrix_t> result218;
#pragma HLS STREAM variable=result218 depth=10
	stream<matrix_t> result219;
#pragma HLS STREAM variable=result219 depth=10
	stream<matrix_t> result220;
#pragma HLS STREAM variable=result220 depth=10
	stream<matrix_t> result221;
#pragma HLS STREAM variable=result221 depth=10
	stream<matrix_t> result222;
#pragma HLS STREAM variable=result222 depth=10
	stream<matrix_t> result223;
#pragma HLS STREAM variable=result223 depth=10
	stream<matrix_t> result224;
#pragma HLS STREAM variable=result224 depth=10
	stream<matrix_t> result225;
#pragma HLS STREAM variable=result225 depth=10
	stream<matrix_t> result226;
#pragma HLS STREAM variable=result226 depth=10
	stream<matrix_t> result227;
#pragma HLS STREAM variable=result227 depth=10
	stream<matrix_t> result228;
#pragma HLS STREAM variable=result228 depth=10
	stream<matrix_t> result229;
#pragma HLS STREAM variable=result229 depth=10
	stream<matrix_t> result230;
#pragma HLS STREAM variable=result230 depth=10
	stream<matrix_t> result231;
#pragma HLS STREAM variable=result231 depth=10
	stream<matrix_t> result232;
#pragma HLS STREAM variable=result232 depth=10
	stream<matrix_t> result233;
#pragma HLS STREAM variable=result233 depth=10
	stream<matrix_t> result234;
#pragma HLS STREAM variable=result234 depth=10
	stream<matrix_t> result235;
#pragma HLS STREAM variable=result235 depth=10
	stream<matrix_t> result236;
#pragma HLS STREAM variable=result236 depth=10
	stream<matrix_t> result237;
#pragma HLS STREAM variable=result237 depth=10
	stream<matrix_t> result238;
#pragma HLS STREAM variable=result238 depth=10
	stream<matrix_t> result239;
#pragma HLS STREAM variable=result239 depth=10
	stream<matrix_t> result240;
#pragma HLS STREAM variable=result240 depth=10
	stream<matrix_t> result241;
#pragma HLS STREAM variable=result241 depth=10
	stream<matrix_t> result242;
#pragma HLS STREAM variable=result242 depth=10
	stream<matrix_t> result243;
#pragma HLS STREAM variable=result243 depth=10
	stream<matrix_t> result244;
#pragma HLS STREAM variable=result244 depth=10
	stream<matrix_t> result245;
#pragma HLS STREAM variable=result245 depth=10
	stream<matrix_t> result246;
#pragma HLS STREAM variable=result246 depth=10
	stream<matrix_t> result247;
#pragma HLS STREAM variable=result247 depth=10
	stream<matrix_t> result248;
#pragma HLS STREAM variable=result248 depth=10
	stream<matrix_t> result249;
#pragma HLS STREAM variable=result249 depth=10
	stream<matrix_t> result250;
#pragma HLS STREAM variable=result250 depth=10
	stream<matrix_t> result251;
#pragma HLS STREAM variable=result251 depth=10
	stream<matrix_t> result252;
#pragma HLS STREAM variable=result252 depth=10
	stream<matrix_t> result253;
#pragma HLS STREAM variable=result253 depth=10
	stream<matrix_t> result254;
#pragma HLS STREAM variable=result254 depth=10
	stream<matrix_t> result255;
#pragma HLS STREAM variable=result255 depth=10

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
	stream<matrix_t> mid63;
#pragma HLS STREAM variable=mid63 depth=10
	stream<matrix_t> mid64;
#pragma HLS STREAM variable=mid64 depth=10
	stream<matrix_t> mid65;
#pragma HLS STREAM variable=mid65 depth=10
	stream<matrix_t> mid66;
#pragma HLS STREAM variable=mid66 depth=10
	stream<matrix_t> mid67;
#pragma HLS STREAM variable=mid67 depth=10
	stream<matrix_t> mid68;
#pragma HLS STREAM variable=mid68 depth=10
	stream<matrix_t> mid69;
#pragma HLS STREAM variable=mid69 depth=10
	stream<matrix_t> mid70;
#pragma HLS STREAM variable=mid70 depth=10
	stream<matrix_t> mid71;
#pragma HLS STREAM variable=mid71 depth=10
	stream<matrix_t> mid72;
#pragma HLS STREAM variable=mid72 depth=10
	stream<matrix_t> mid73;
#pragma HLS STREAM variable=mid73 depth=10
	stream<matrix_t> mid74;
#pragma HLS STREAM variable=mid74 depth=10
	stream<matrix_t> mid75;
#pragma HLS STREAM variable=mid75 depth=10
	stream<matrix_t> mid76;
#pragma HLS STREAM variable=mid76 depth=10
	stream<matrix_t> mid77;
#pragma HLS STREAM variable=mid77 depth=10
	stream<matrix_t> mid78;
#pragma HLS STREAM variable=mid78 depth=10
	stream<matrix_t> mid79;
#pragma HLS STREAM variable=mid79 depth=10
	stream<matrix_t> mid80;
#pragma HLS STREAM variable=mid80 depth=10
	stream<matrix_t> mid81;
#pragma HLS STREAM variable=mid81 depth=10
	stream<matrix_t> mid82;
#pragma HLS STREAM variable=mid82 depth=10
	stream<matrix_t> mid83;
#pragma HLS STREAM variable=mid83 depth=10
	stream<matrix_t> mid84;
#pragma HLS STREAM variable=mid84 depth=10
	stream<matrix_t> mid85;
#pragma HLS STREAM variable=mid85 depth=10
	stream<matrix_t> mid86;
#pragma HLS STREAM variable=mid86 depth=10
	stream<matrix_t> mid87;
#pragma HLS STREAM variable=mid87 depth=10
	stream<matrix_t> mid88;
#pragma HLS STREAM variable=mid88 depth=10
	stream<matrix_t> mid89;
#pragma HLS STREAM variable=mid89 depth=10
	stream<matrix_t> mid90;
#pragma HLS STREAM variable=mid90 depth=10
	stream<matrix_t> mid91;
#pragma HLS STREAM variable=mid91 depth=10
	stream<matrix_t> mid92;
#pragma HLS STREAM variable=mid92 depth=10
	stream<matrix_t> mid93;
#pragma HLS STREAM variable=mid93 depth=10
	stream<matrix_t> mid94;
#pragma HLS STREAM variable=mid94 depth=10
	stream<matrix_t> mid95;
#pragma HLS STREAM variable=mid95 depth=10
	stream<matrix_t> mid96;
#pragma HLS STREAM variable=mid96 depth=10
	stream<matrix_t> mid97;
#pragma HLS STREAM variable=mid97 depth=10
	stream<matrix_t> mid98;
#pragma HLS STREAM variable=mid98 depth=10
	stream<matrix_t> mid99;
#pragma HLS STREAM variable=mid99 depth=10
	stream<matrix_t> mid100;
#pragma HLS STREAM variable=mid100 depth=10
	stream<matrix_t> mid101;
#pragma HLS STREAM variable=mid101 depth=10
	stream<matrix_t> mid102;
#pragma HLS STREAM variable=mid102 depth=10
	stream<matrix_t> mid103;
#pragma HLS STREAM variable=mid103 depth=10
	stream<matrix_t> mid104;
#pragma HLS STREAM variable=mid104 depth=10
	stream<matrix_t> mid105;
#pragma HLS STREAM variable=mid105 depth=10
	stream<matrix_t> mid106;
#pragma HLS STREAM variable=mid106 depth=10
	stream<matrix_t> mid107;
#pragma HLS STREAM variable=mid107 depth=10
	stream<matrix_t> mid108;
#pragma HLS STREAM variable=mid108 depth=10
	stream<matrix_t> mid109;
#pragma HLS STREAM variable=mid109 depth=10
	stream<matrix_t> mid110;
#pragma HLS STREAM variable=mid110 depth=10
	stream<matrix_t> mid111;
#pragma HLS STREAM variable=mid111 depth=10
	stream<matrix_t> mid112;
#pragma HLS STREAM variable=mid112 depth=10
	stream<matrix_t> mid113;
#pragma HLS STREAM variable=mid113 depth=10
	stream<matrix_t> mid114;
#pragma HLS STREAM variable=mid114 depth=10
	stream<matrix_t> mid115;
#pragma HLS STREAM variable=mid115 depth=10
	stream<matrix_t> mid116;
#pragma HLS STREAM variable=mid116 depth=10
	stream<matrix_t> mid117;
#pragma HLS STREAM variable=mid117 depth=10
	stream<matrix_t> mid118;
#pragma HLS STREAM variable=mid118 depth=10
	stream<matrix_t> mid119;
#pragma HLS STREAM variable=mid119 depth=10
	stream<matrix_t> mid120;
#pragma HLS STREAM variable=mid120 depth=10
	stream<matrix_t> mid121;
#pragma HLS STREAM variable=mid121 depth=10
	stream<matrix_t> mid122;
#pragma HLS STREAM variable=mid122 depth=10
	stream<matrix_t> mid123;
#pragma HLS STREAM variable=mid123 depth=10
	stream<matrix_t> mid124;
#pragma HLS STREAM variable=mid124 depth=10
	stream<matrix_t> mid125;
#pragma HLS STREAM variable=mid125 depth=10
	stream<matrix_t> mid126;
#pragma HLS STREAM variable=mid126 depth=10
	stream<matrix_t> mid127;
#pragma HLS STREAM variable=mid127 depth=10
	stream<matrix_t> mid128;
#pragma HLS STREAM variable=mid128 depth=10
	stream<matrix_t> mid129;
#pragma HLS STREAM variable=mid129 depth=10
	stream<matrix_t> mid130;
#pragma HLS STREAM variable=mid130 depth=10
	stream<matrix_t> mid131;
#pragma HLS STREAM variable=mid131 depth=10
	stream<matrix_t> mid132;
#pragma HLS STREAM variable=mid132 depth=10
	stream<matrix_t> mid133;
#pragma HLS STREAM variable=mid133 depth=10
	stream<matrix_t> mid134;
#pragma HLS STREAM variable=mid134 depth=10
	stream<matrix_t> mid135;
#pragma HLS STREAM variable=mid135 depth=10
	stream<matrix_t> mid136;
#pragma HLS STREAM variable=mid136 depth=10
	stream<matrix_t> mid137;
#pragma HLS STREAM variable=mid137 depth=10
	stream<matrix_t> mid138;
#pragma HLS STREAM variable=mid138 depth=10
	stream<matrix_t> mid139;
#pragma HLS STREAM variable=mid139 depth=10
	stream<matrix_t> mid140;
#pragma HLS STREAM variable=mid140 depth=10
	stream<matrix_t> mid141;
#pragma HLS STREAM variable=mid141 depth=10
	stream<matrix_t> mid142;
#pragma HLS STREAM variable=mid142 depth=10
	stream<matrix_t> mid143;
#pragma HLS STREAM variable=mid143 depth=10
	stream<matrix_t> mid144;
#pragma HLS STREAM variable=mid144 depth=10
	stream<matrix_t> mid145;
#pragma HLS STREAM variable=mid145 depth=10
	stream<matrix_t> mid146;
#pragma HLS STREAM variable=mid146 depth=10
	stream<matrix_t> mid147;
#pragma HLS STREAM variable=mid147 depth=10
	stream<matrix_t> mid148;
#pragma HLS STREAM variable=mid148 depth=10
	stream<matrix_t> mid149;
#pragma HLS STREAM variable=mid149 depth=10
	stream<matrix_t> mid150;
#pragma HLS STREAM variable=mid150 depth=10
	stream<matrix_t> mid151;
#pragma HLS STREAM variable=mid151 depth=10
	stream<matrix_t> mid152;
#pragma HLS STREAM variable=mid152 depth=10
	stream<matrix_t> mid153;
#pragma HLS STREAM variable=mid153 depth=10
	stream<matrix_t> mid154;
#pragma HLS STREAM variable=mid154 depth=10
	stream<matrix_t> mid155;
#pragma HLS STREAM variable=mid155 depth=10
	stream<matrix_t> mid156;
#pragma HLS STREAM variable=mid156 depth=10
	stream<matrix_t> mid157;
#pragma HLS STREAM variable=mid157 depth=10
	stream<matrix_t> mid158;
#pragma HLS STREAM variable=mid158 depth=10
	stream<matrix_t> mid159;
#pragma HLS STREAM variable=mid159 depth=10
	stream<matrix_t> mid160;
#pragma HLS STREAM variable=mid160 depth=10
	stream<matrix_t> mid161;
#pragma HLS STREAM variable=mid161 depth=10
	stream<matrix_t> mid162;
#pragma HLS STREAM variable=mid162 depth=10
	stream<matrix_t> mid163;
#pragma HLS STREAM variable=mid163 depth=10
	stream<matrix_t> mid164;
#pragma HLS STREAM variable=mid164 depth=10
	stream<matrix_t> mid165;
#pragma HLS STREAM variable=mid165 depth=10
	stream<matrix_t> mid166;
#pragma HLS STREAM variable=mid166 depth=10
	stream<matrix_t> mid167;
#pragma HLS STREAM variable=mid167 depth=10
	stream<matrix_t> mid168;
#pragma HLS STREAM variable=mid168 depth=10
	stream<matrix_t> mid169;
#pragma HLS STREAM variable=mid169 depth=10
	stream<matrix_t> mid170;
#pragma HLS STREAM variable=mid170 depth=10
	stream<matrix_t> mid171;
#pragma HLS STREAM variable=mid171 depth=10
	stream<matrix_t> mid172;
#pragma HLS STREAM variable=mid172 depth=10
	stream<matrix_t> mid173;
#pragma HLS STREAM variable=mid173 depth=10
	stream<matrix_t> mid174;
#pragma HLS STREAM variable=mid174 depth=10
	stream<matrix_t> mid175;
#pragma HLS STREAM variable=mid175 depth=10
	stream<matrix_t> mid176;
#pragma HLS STREAM variable=mid176 depth=10
	stream<matrix_t> mid177;
#pragma HLS STREAM variable=mid177 depth=10
	stream<matrix_t> mid178;
#pragma HLS STREAM variable=mid178 depth=10
	stream<matrix_t> mid179;
#pragma HLS STREAM variable=mid179 depth=10
	stream<matrix_t> mid180;
#pragma HLS STREAM variable=mid180 depth=10
	stream<matrix_t> mid181;
#pragma HLS STREAM variable=mid181 depth=10
	stream<matrix_t> mid182;
#pragma HLS STREAM variable=mid182 depth=10
	stream<matrix_t> mid183;
#pragma HLS STREAM variable=mid183 depth=10
	stream<matrix_t> mid184;
#pragma HLS STREAM variable=mid184 depth=10
	stream<matrix_t> mid185;
#pragma HLS STREAM variable=mid185 depth=10
	stream<matrix_t> mid186;
#pragma HLS STREAM variable=mid186 depth=10
	stream<matrix_t> mid187;
#pragma HLS STREAM variable=mid187 depth=10
	stream<matrix_t> mid188;
#pragma HLS STREAM variable=mid188 depth=10
	stream<matrix_t> mid189;
#pragma HLS STREAM variable=mid189 depth=10
	stream<matrix_t> mid190;
#pragma HLS STREAM variable=mid190 depth=10
	stream<matrix_t> mid191;
#pragma HLS STREAM variable=mid191 depth=10
	stream<matrix_t> mid192;
#pragma HLS STREAM variable=mid192 depth=10
	stream<matrix_t> mid193;
#pragma HLS STREAM variable=mid193 depth=10
	stream<matrix_t> mid194;
#pragma HLS STREAM variable=mid194 depth=10
	stream<matrix_t> mid195;
#pragma HLS STREAM variable=mid195 depth=10
	stream<matrix_t> mid196;
#pragma HLS STREAM variable=mid196 depth=10
	stream<matrix_t> mid197;
#pragma HLS STREAM variable=mid197 depth=10
	stream<matrix_t> mid198;
#pragma HLS STREAM variable=mid198 depth=10
	stream<matrix_t> mid199;
#pragma HLS STREAM variable=mid199 depth=10
	stream<matrix_t> mid200;
#pragma HLS STREAM variable=mid200 depth=10
	stream<matrix_t> mid201;
#pragma HLS STREAM variable=mid201 depth=10
	stream<matrix_t> mid202;
#pragma HLS STREAM variable=mid202 depth=10
	stream<matrix_t> mid203;
#pragma HLS STREAM variable=mid203 depth=10
	stream<matrix_t> mid204;
#pragma HLS STREAM variable=mid204 depth=10
	stream<matrix_t> mid205;
#pragma HLS STREAM variable=mid205 depth=10
	stream<matrix_t> mid206;
#pragma HLS STREAM variable=mid206 depth=10
	stream<matrix_t> mid207;
#pragma HLS STREAM variable=mid207 depth=10
	stream<matrix_t> mid208;
#pragma HLS STREAM variable=mid208 depth=10
	stream<matrix_t> mid209;
#pragma HLS STREAM variable=mid209 depth=10
	stream<matrix_t> mid210;
#pragma HLS STREAM variable=mid210 depth=10
	stream<matrix_t> mid211;
#pragma HLS STREAM variable=mid211 depth=10
	stream<matrix_t> mid212;
#pragma HLS STREAM variable=mid212 depth=10
	stream<matrix_t> mid213;
#pragma HLS STREAM variable=mid213 depth=10
	stream<matrix_t> mid214;
#pragma HLS STREAM variable=mid214 depth=10
	stream<matrix_t> mid215;
#pragma HLS STREAM variable=mid215 depth=10
	stream<matrix_t> mid216;
#pragma HLS STREAM variable=mid216 depth=10
	stream<matrix_t> mid217;
#pragma HLS STREAM variable=mid217 depth=10
	stream<matrix_t> mid218;
#pragma HLS STREAM variable=mid218 depth=10
	stream<matrix_t> mid219;
#pragma HLS STREAM variable=mid219 depth=10
	stream<matrix_t> mid220;
#pragma HLS STREAM variable=mid220 depth=10
	stream<matrix_t> mid221;
#pragma HLS STREAM variable=mid221 depth=10
	stream<matrix_t> mid222;
#pragma HLS STREAM variable=mid222 depth=10
	stream<matrix_t> mid223;
#pragma HLS STREAM variable=mid223 depth=10
	stream<matrix_t> mid224;
#pragma HLS STREAM variable=mid224 depth=10
	stream<matrix_t> mid225;
#pragma HLS STREAM variable=mid225 depth=10
	stream<matrix_t> mid226;
#pragma HLS STREAM variable=mid226 depth=10
	stream<matrix_t> mid227;
#pragma HLS STREAM variable=mid227 depth=10
	stream<matrix_t> mid228;
#pragma HLS STREAM variable=mid228 depth=10
	stream<matrix_t> mid229;
#pragma HLS STREAM variable=mid229 depth=10
	stream<matrix_t> mid230;
#pragma HLS STREAM variable=mid230 depth=10
	stream<matrix_t> mid231;
#pragma HLS STREAM variable=mid231 depth=10
	stream<matrix_t> mid232;
#pragma HLS STREAM variable=mid232 depth=10
	stream<matrix_t> mid233;
#pragma HLS STREAM variable=mid233 depth=10
	stream<matrix_t> mid234;
#pragma HLS STREAM variable=mid234 depth=10
	stream<matrix_t> mid235;
#pragma HLS STREAM variable=mid235 depth=10
	stream<matrix_t> mid236;
#pragma HLS STREAM variable=mid236 depth=10
	stream<matrix_t> mid237;
#pragma HLS STREAM variable=mid237 depth=10
	stream<matrix_t> mid238;
#pragma HLS STREAM variable=mid238 depth=10
	stream<matrix_t> mid239;
#pragma HLS STREAM variable=mid239 depth=10
	stream<matrix_t> mid240;
#pragma HLS STREAM variable=mid240 depth=10
	stream<matrix_t> mid241;
#pragma HLS STREAM variable=mid241 depth=10
	stream<matrix_t> mid242;
#pragma HLS STREAM variable=mid242 depth=10
	stream<matrix_t> mid243;
#pragma HLS STREAM variable=mid243 depth=10
	stream<matrix_t> mid244;
#pragma HLS STREAM variable=mid244 depth=10
	stream<matrix_t> mid245;
#pragma HLS STREAM variable=mid245 depth=10
	stream<matrix_t> mid246;
#pragma HLS STREAM variable=mid246 depth=10
	stream<matrix_t> mid247;
#pragma HLS STREAM variable=mid247 depth=10
	stream<matrix_t> mid248;
#pragma HLS STREAM variable=mid248 depth=10
	stream<matrix_t> mid249;
#pragma HLS STREAM variable=mid249 depth=10
	stream<matrix_t> mid250;
#pragma HLS STREAM variable=mid250 depth=10
	stream<matrix_t> mid251;
#pragma HLS STREAM variable=mid251 depth=10
	stream<matrix_t> mid252;
#pragma HLS STREAM variable=mid252 depth=10
	stream<matrix_t> mid253;
#pragma HLS STREAM variable=mid253 depth=10
	stream<matrix_t> mid254;
#pragma HLS STREAM variable=mid254 depth=10

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
	PE(63, mid62, result63, mid63);
	PE(64, mid63, result64, mid64);
	PE(65, mid64, result65, mid65);
	PE(66, mid65, result66, mid66);
	PE(67, mid66, result67, mid67);
	PE(68, mid67, result68, mid68);
	PE(69, mid68, result69, mid69);
	PE(70, mid69, result70, mid70);
	PE(71, mid70, result71, mid71);
	PE(72, mid71, result72, mid72);
	PE(73, mid72, result73, mid73);
	PE(74, mid73, result74, mid74);
	PE(75, mid74, result75, mid75);
	PE(76, mid75, result76, mid76);
	PE(77, mid76, result77, mid77);
	PE(78, mid77, result78, mid78);
	PE(79, mid78, result79, mid79);
	PE(80, mid79, result80, mid80);
	PE(81, mid80, result81, mid81);
	PE(82, mid81, result82, mid82);
	PE(83, mid82, result83, mid83);
	PE(84, mid83, result84, mid84);
	PE(85, mid84, result85, mid85);
	PE(86, mid85, result86, mid86);
	PE(87, mid86, result87, mid87);
	PE(88, mid87, result88, mid88);
	PE(89, mid88, result89, mid89);
	PE(90, mid89, result90, mid90);
	PE(91, mid90, result91, mid91);
	PE(92, mid91, result92, mid92);
	PE(93, mid92, result93, mid93);
	PE(94, mid93, result94, mid94);
	PE(95, mid94, result95, mid95);
	PE(96, mid95, result96, mid96);
	PE(97, mid96, result97, mid97);
	PE(98, mid97, result98, mid98);
	PE(99, mid98, result99, mid99);
	PE(100, mid99, result100, mid100);
	PE(101, mid100, result101, mid101);
	PE(102, mid101, result102, mid102);
	PE(103, mid102, result103, mid103);
	PE(104, mid103, result104, mid104);
	PE(105, mid104, result105, mid105);
	PE(106, mid105, result106, mid106);
	PE(107, mid106, result107, mid107);
	PE(108, mid107, result108, mid108);
	PE(109, mid108, result109, mid109);
	PE(110, mid109, result110, mid110);
	PE(111, mid110, result111, mid111);
	PE(112, mid111, result112, mid112);
	PE(113, mid112, result113, mid113);
	PE(114, mid113, result114, mid114);
	PE(115, mid114, result115, mid115);
	PE(116, mid115, result116, mid116);
	PE(117, mid116, result117, mid117);
	PE(118, mid117, result118, mid118);
	PE(119, mid118, result119, mid119);
	PE(120, mid119, result120, mid120);
	PE(121, mid120, result121, mid121);
	PE(122, mid121, result122, mid122);
	PE(123, mid122, result123, mid123);
	PE(124, mid123, result124, mid124);
	PE(125, mid124, result125, mid125);
	PE(126, mid125, result126, mid126);
	PE(127, mid126, result127, mid127);
	PE(128, mid127, result128, mid128);
	PE(129, mid128, result129, mid129);
	PE(130, mid129, result130, mid130);
	PE(131, mid130, result131, mid131);
	PE(132, mid131, result132, mid132);
	PE(133, mid132, result133, mid133);
	PE(134, mid133, result134, mid134);
	PE(135, mid134, result135, mid135);
	PE(136, mid135, result136, mid136);
	PE(137, mid136, result137, mid137);
	PE(138, mid137, result138, mid138);
	PE(139, mid138, result139, mid139);
	PE(140, mid139, result140, mid140);
	PE(141, mid140, result141, mid141);
	PE(142, mid141, result142, mid142);
	PE(143, mid142, result143, mid143);
	PE(144, mid143, result144, mid144);
	PE(145, mid144, result145, mid145);
	PE(146, mid145, result146, mid146);
	PE(147, mid146, result147, mid147);
	PE(148, mid147, result148, mid148);
	PE(149, mid148, result149, mid149);
	PE(150, mid149, result150, mid150);
	PE(151, mid150, result151, mid151);
	PE(152, mid151, result152, mid152);
	PE(153, mid152, result153, mid153);
	PE(154, mid153, result154, mid154);
	PE(155, mid154, result155, mid155);
	PE(156, mid155, result156, mid156);
	PE(157, mid156, result157, mid157);
	PE(158, mid157, result158, mid158);
	PE(159, mid158, result159, mid159);
	PE(160, mid159, result160, mid160);
	PE(161, mid160, result161, mid161);
	PE(162, mid161, result162, mid162);
	PE(163, mid162, result163, mid163);
	PE(164, mid163, result164, mid164);
	PE(165, mid164, result165, mid165);
	PE(166, mid165, result166, mid166);
	PE(167, mid166, result167, mid167);
	PE(168, mid167, result168, mid168);
	PE(169, mid168, result169, mid169);
	PE(170, mid169, result170, mid170);
	PE(171, mid170, result171, mid171);
	PE(172, mid171, result172, mid172);
	PE(173, mid172, result173, mid173);
	PE(174, mid173, result174, mid174);
	PE(175, mid174, result175, mid175);
	PE(176, mid175, result176, mid176);
	PE(177, mid176, result177, mid177);
	PE(178, mid177, result178, mid178);
	PE(179, mid178, result179, mid179);
	PE(180, mid179, result180, mid180);
	PE(181, mid180, result181, mid181);
	PE(182, mid181, result182, mid182);
	PE(183, mid182, result183, mid183);
	PE(184, mid183, result184, mid184);
	PE(185, mid184, result185, mid185);
	PE(186, mid185, result186, mid186);
	PE(187, mid186, result187, mid187);
	PE(188, mid187, result188, mid188);
	PE(189, mid188, result189, mid189);
	PE(190, mid189, result190, mid190);
	PE(191, mid190, result191, mid191);
	PE(192, mid191, result192, mid192);
	PE(193, mid192, result193, mid193);
	PE(194, mid193, result194, mid194);
	PE(195, mid194, result195, mid195);
	PE(196, mid195, result196, mid196);
	PE(197, mid196, result197, mid197);
	PE(198, mid197, result198, mid198);
	PE(199, mid198, result199, mid199);
	PE(200, mid199, result200, mid200);
	PE(201, mid200, result201, mid201);
	PE(202, mid201, result202, mid202);
	PE(203, mid202, result203, mid203);
	PE(204, mid203, result204, mid204);
	PE(205, mid204, result205, mid205);
	PE(206, mid205, result206, mid206);
	PE(207, mid206, result207, mid207);
	PE(208, mid207, result208, mid208);
	PE(209, mid208, result209, mid209);
	PE(210, mid209, result210, mid210);
	PE(211, mid210, result211, mid211);
	PE(212, mid211, result212, mid212);
	PE(213, mid212, result213, mid213);
	PE(214, mid213, result214, mid214);
	PE(215, mid214, result215, mid215);
	PE(216, mid215, result216, mid216);
	PE(217, mid216, result217, mid217);
	PE(218, mid217, result218, mid218);
	PE(219, mid218, result219, mid219);
	PE(220, mid219, result220, mid220);
	PE(221, mid220, result221, mid221);
	PE(222, mid221, result222, mid222);
	PE(223, mid222, result223, mid223);
	PE(224, mid223, result224, mid224);
	PE(225, mid224, result225, mid225);
	PE(226, mid225, result226, mid226);
	PE(227, mid226, result227, mid227);
	PE(228, mid227, result228, mid228);
	PE(229, mid228, result229, mid229);
	PE(230, mid229, result230, mid230);
	PE(231, mid230, result231, mid231);
	PE(232, mid231, result232, mid232);
	PE(233, mid232, result233, mid233);
	PE(234, mid233, result234, mid234);
	PE(235, mid234, result235, mid235);
	PE(236, mid235, result236, mid236);
	PE(237, mid236, result237, mid237);
	PE(238, mid237, result238, mid238);
	PE(239, mid238, result239, mid239);
	PE(240, mid239, result240, mid240);
	PE(241, mid240, result241, mid241);
	PE(242, mid241, result242, mid242);
	PE(243, mid242, result243, mid243);
	PE(244, mid243, result244, mid244);
	PE(245, mid244, result245, mid245);
	PE(246, mid245, result246, mid246);
	PE(247, mid246, result247, mid247);
	PE(248, mid247, result248, mid248);
	PE(249, mid248, result249, mid249);
	PE(250, mid249, result250, mid250);
	PE(251, mid250, result251, mid251);
	PE(252, mid251, result252, mid252);
	PE(253, mid252, result253, mid253);
	PE(254, mid253, result254, mid254);
	PE_last(mid254, result255);

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
		result64,
		result65,
		result66,
		result67,
		result68,
		result69,
		result70,
		result71,
		result72,
		result73,
		result74,
		result75,
		result76,
		result77,
		result78,
		result79,
		result80,
		result81,
		result82,
		result83,
		result84,
		result85,
		result86,
		result87,
		result88,
		result89,
		result90,
		result91,
		result92,
		result93,
		result94,
		result95,
		result96,
		result97,
		result98,
		result99,
		result100,
		result101,
		result102,
		result103,
		result104,
		result105,
		result106,
		result107,
		result108,
		result109,
		result110,
		result111,
		result112,
		result113,
		result114,
		result115,
		result116,
		result117,
		result118,
		result119,
		result120,
		result121,
		result122,
		result123,
		result124,
		result125,
		result126,
		result127,
		result128,
		result129,
		result130,
		result131,
		result132,
		result133,
		result134,
		result135,
		result136,
		result137,
		result138,
		result139,
		result140,
		result141,
		result142,
		result143,
		result144,
		result145,
		result146,
		result147,
		result148,
		result149,
		result150,
		result151,
		result152,
		result153,
		result154,
		result155,
		result156,
		result157,
		result158,
		result159,
		result160,
		result161,
		result162,
		result163,
		result164,
		result165,
		result166,
		result167,
		result168,
		result169,
		result170,
		result171,
		result172,
		result173,
		result174,
		result175,
		result176,
		result177,
		result178,
		result179,
		result180,
		result181,
		result182,
		result183,
		result184,
		result185,
		result186,
		result187,
		result188,
		result189,
		result190,
		result191,
		result192,
		result193,
		result194,
		result195,
		result196,
		result197,
		result198,
		result199,
		result200,
		result201,
		result202,
		result203,
		result204,
		result205,
		result206,
		result207,
		result208,
		result209,
		result210,
		result211,
		result212,
		result213,
		result214,
		result215,
		result216,
		result217,
		result218,
		result219,
		result220,
		result221,
		result222,
		result223,
		result224,
		result225,
		result226,
		result227,
		result228,
		result229,
		result230,
		result231,
		result232,
		result233,
		result234,
		result235,
		result236,
		result237,
		result238,
		result239,
		result240,
		result241,
		result242,
		result243,
		result244,
		result245,
		result246,
		result247,
		result248,
		result249,
		result250,
		result251,
		result252,
		result253,
		result254,
		result255,
	       	L);

	return 0;
}
