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
	PE_last(mid14, result15);

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
	       	L);

	return 0;
}
