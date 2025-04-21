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

	stream<matrix_t> mid0;
#pragma HLS STREAM variable=mid0 depth=10

	feeder(A, feedin);
	PE(0, feedin, result0, mid0);
	PE_last(mid0, result1);

	collector(
		result0,
		result1,
	       	L);

	return 0;
}
