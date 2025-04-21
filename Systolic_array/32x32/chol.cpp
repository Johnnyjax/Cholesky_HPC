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
	PE_last(mid30, result31);

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
	       	L);

	return 0;
}
