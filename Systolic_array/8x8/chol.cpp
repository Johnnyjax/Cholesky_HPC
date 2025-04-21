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

	feeder(A, feedin);
	PE(0, feedin, result0, mid0);
	PE(1, mid0, result1, mid1);
	PE(2, mid1, result2, mid2);
	PE(3, mid2, result3, mid3);
	PE(4, mid3, result4, mid4);
	PE(5, mid4, result5, mid5);
	PE(6, mid5, result6, mid6);
	PE_last(mid6, result7);

	collector(
		result0,
		result1,
		result2,
		result3,
		result4,
		result5,
		result6,
		result7,
	       	L);

	return 0;
}
