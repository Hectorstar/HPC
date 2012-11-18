#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

#define start_time clock_gettime(CLOCK_MONOTONIC, &start);
#define end_time clock_gettime(CLOCK_MONOTONIC, &finish);

struct timespec start, finish;

int main(int argc, char *argv[]){
        char filepath[100];
        int a_rows=atoi(argv[1]), a_cols=atoi(argv[2]), b_cols=atoi(argv[3]);
        sprintf(filepath, "../data/m2m/double_dataset/m%d_%d_to_m%d_%d.double", a_rows, a_cols, a_cols, b_cols);
        FILE* pfile = fopen(filepath, "r");
        double *v1, *v2_tmp, **res;

// set size
        fread((void*)(&a_rows), sizeof(int), 1, pfile);
        fread((void*)(&a_cols), sizeof(int), 1, pfile);
	fread((void*)(&b_cols), sizeof(int), 1, pfile);
// alloc
        v1 = (double*)malloc(a_rows* a_cols * sizeof(double));
        v2_tmp = (double*)malloc(a_cols* b_cols* sizeof(double));
        res = (double**)malloc(a_rows * sizeof(double*));

        int i, j, k;
		for(i=0; i<a_rows; i++){
			res[i] = (double*)malloc(b_cols * sizeof(double));
			memset(res[i], 0.0, b_cols * sizeof(double));	
		}

// read in data
        fread((void*)v1, sizeof(double), a_rows*a_cols, pfile);
        fread((void*)v2_tmp, sizeof(double), a_cols*b_cols, pfile);
	
// memset
//        memset(res, 0.0, a_rows * b_cols * sizeof(double));

		double *v2;
		v2 = (double*)malloc(a_cols * b_cols * sizeof(double));
		for(i=0; i<a_cols; i++)
			for(j=0; j<b_cols; j++)
				v2[j*a_cols + i] = v2_tmp[i*b_cols+j];

// set start
        start_time

// calculate
        for(i=0; i<a_rows; i++)
            for(j=0; j<b_cols; j++)
				for(k=0; k<a_cols; k++)
//	                        res[i*a_rows+j] += v1[i*a_rows+k] * v2_tmp[k*a_cols+j];
					res[i][j] += v1[i*a_cols+k] * v2[j*a_cols + k];

// set end
        end_time
        printf("%d %d %d %.16lf\n", a_rows, a_cols, b_cols, finish.tv_sec-start.tv_sec + (double)(finish.tv_nsec - start.tv_nsec) / 1000000000.0);

// print out
#ifdef DEBUG
        for(i=0; i<a_rows; i++)
                printf("%d %d %lf\n", a_rows, a_cols, res[i]);

        return 0;
#endif
}

