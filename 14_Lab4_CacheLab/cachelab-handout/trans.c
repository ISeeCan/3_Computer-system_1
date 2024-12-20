
/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])       //最终提交的版本
{
    int temp0, temp1, temp2, temp3, temp4, temp5, temp6, temp7; //临时变量
    if(M==32)
    {
        for (int m = 0; m < 32; m += 8)         //划分为横条
        {
            for (int n = 0; n < 32; n += 8)     //在横条基础上划分为小块
            {
                if (m == n)                         //是对角线上的（块矩阵）
                {
                    for (int i = m; i < m + 8; ++i)     //展开以避免冲突
                    {
                        temp0 = A[i][n];
                        temp1 = A[i][n + 1];
                        temp2 = A[i][n + 2];
                        temp3 = A[i][n + 3];
                        temp4 = A[i][n + 4];
                        temp5 = A[i][n + 5];
                        temp6 = A[i][n + 6];
                        temp7 = A[i][n + 7];

                        B[i][n] = temp0;
                        B[i][n + 1] = temp1;
                        B[i][n + 2] = temp2;
                        B[i][n + 3] = temp3;
                        B[i][n + 4] = temp4;
                        B[i][n + 5] = temp5;
                        B[i][n + 6] = temp6;
                        B[i][n + 7] = temp7;
                    }
                    for (int i = m; i < m + 8; ++i)     //对角线块的每行
                    {
                        for (int j = n + (i - m + 1); j < n + 8; ++j)   //从每行之于对角线
                        {                                                    //上的元素开始
                            if (i != j)
                            {
                                temp0 = B[i][j];
                                B[i][j] = B[j][i];
                                B[j][i] = temp0;
                            }
                        }
                    }
                }
                else            //不是对角线上的——直接处理
                {
                    for (int i = m; i < m + 8; ++i)
                    {
                        for (int j = n; j < n + 8; ++j)
                        {
                            B[j][i] = A[i][j];
                        }
                    }
                }
            }
        }
    }
    else if(M==64)
    {
        for (int m = 0; m < 64; m += 8)
        {
            for (int n = m; n < 64; n += 8)
            {
                if (m != n)
                {
                    for (int i = n; i < n + 4; ++i)
                    {
                        N = i - n;

                        temp0 = A[i][m];
                        temp1 = A[i][m + 1];
                        temp2 = A[i][m + 2];
                        temp3 = A[i][m + 3];

                        temp4 = A[i][m + 4];
                        temp5 = A[i][m + 5];
                        temp6 = A[i][m + 6];
                        temp7 = A[i][m + 7];

                        B[m + 4][n + N] = temp4;
                        B[m + 5][n + N] = temp5;
                        B[m + 6][n + N] = temp6;
                        B[m + 7][n + N] = temp7;

                        B[m + 4][n + 4 + N] = temp0;
                        B[m + 5][n + 4 + N] = temp1;
                        B[m + 6][n + 4 + N] = temp2;
                        B[m + 7][n + 4 + N] = temp3;
                    }

                    for (int i = m + 4; i < m + 8; ++i)
                    {
                        N = i - (m + 4);

                        temp0 = A[n + 4][m + 4 + N];
                        temp1 = A[n + 5][m + 4 + N];
                        temp2 = A[n + 6][m + 4 + N];
                        temp3 = A[n + 7][m + 4 + N];

                        temp4 = B[m + 4 + N][n + 4];
                        temp5 = B[m + 4 + N][n + 5];
                        temp6 = B[m + 4 + N][n + 6];
                        temp7 = B[m + 4 + N][n + 7];

                        B[m + 4 + N][n + 4] = temp0;
                        B[m + 4 + N][n + 5] = temp1;
                        B[m + 4 + N][n + 6] = temp2;
                        B[m + 4 + N][n + 7] = temp3;

                        B[m + N][n] = temp4;
                        B[m + N][n + 1] = temp5;
                        B[m + N][n + 2] = temp6;
                        B[m + N][n + 3] = temp7;
                    }

                    for (int i = m; i < m + 4; ++i)
                    {
                        temp0 = A[n + 4][i];
                        temp1 = A[n + 5][i];
                        temp2 = A[n + 6][i];
                        temp3 = A[n + 7][i];

                        B[i][n + 4] = temp0;
                        B[i][n + 5] = temp1;
                        B[i][n + 6] = temp2;
                        B[i][n + 7] = temp3;
                    }
                    ///////////////////////////////////////////////////////////////////////////////////
                    for (int i = m + 4; i < m + 8; ++i)
                    {
                        M = i - (m + 4);

                        temp0 = A[i][n];
                        temp1 = A[i][n + 1];
                        temp2 = A[i][n + 2];
                        temp3 = A[i][n + 3];

                        temp4 = A[i][n + 4];
                        temp5 = A[i][n + 5];
                        temp6 = A[i][n + 6];
                        temp7 = A[i][n + 7];

                        B[n][m + M] = temp4;
                        B[n + 1][m + M] = temp5;
                        B[n + 2][m + M] = temp6;
                        B[n + 3][m + M] = temp7;

                        B[n][m + 4 + M] = temp0;
                        B[n + 1][m + 4 + M] = temp1;
                        B[n + 2][m + 4 + M] = temp2;
                        B[n + 3][m + 4 + M] = temp3;
                    }

                    for (int i = n; i < n + 4; ++i)
                    {
                        temp0 = A[m][i];
                        temp1 = A[m + 1][i];
                        temp2 = A[m + 2][i];
                        temp3 = A[m + 3][i];

                        temp4 = B[i][m];
                        temp5 = B[i][m + 1];
                        temp6 = B[i][m + 2];
                        temp7 = B[i][m + 3];

                        B[i][m] = temp0;
                        B[i][m + 1] = temp1;
                        B[i][m + 2] = temp2;
                        B[i][m + 3] = temp3;

                        B[i + 4][m + 4] = temp4;
                        B[i + 4][m + 5] = temp5;
                        B[i + 4][m + 6] = temp6;
                        B[i + 4][m + 7] = temp7;
                    }

                    for (int i = m; i < m + 4; ++i)
                    {
                        M = i - m;

                        temp0 = A[i][n + 4];
                        temp1 = A[i][n + 5];
                        temp2 = A[i][n + 6];
                        temp3 = A[i][n + 7];

                        B[n + 4][m + M] = temp0;
                        B[n + 5][m + M] = temp1;
                        B[n + 6][m + M] = temp2;
                        B[n + 7][m + M] = temp3;
                    }
                }
                //*******************************************************************************//
                else
                {
                    if (m != 56 && n != 56)
                    {
                        for (int i = m; i < m + 4; ++i)
                        {
                            M = i - m;

                            temp0 = A[i][n];
                            temp1 = A[i][n + 1];
                            temp2 = A[i][n + 2];
                            temp3 = A[i][n + 3];

                            temp4 = A[i][n + 4];
                            temp5 = A[i][n + 5];
                            temp6 = A[i][n + 6];
                            temp7 = A[i][n + 7];

                            B[m + 4][n + 8 + M] = temp0;
                            B[m + 5][n + 8 + M] = temp1;
                            B[m + 6][n + 8 + M] = temp2;
                            B[m + 7][n + 8 + M] = temp3;

                            B[m + 4][n + 12 + M] = temp4;
                            B[m + 5][n + 12 + M] = temp5;
                            B[m + 6][n + 12 + M] = temp6;
                            B[m + 7][n + 12 + M] = temp7;
                        }
// -----------------------------------------------------------------------
                        for (int i = m + 4; i < m + 8; ++i)
                        {
                            temp0 = A[i][n];
                            temp1 = A[i][n + 1];
                            temp2 = A[i][n + 2];
                            temp3 = A[i][n + 3];
                            temp4 = A[i][n + 4];
                            temp5 = A[i][n + 5];
                            temp6 = A[i][n + 6];
                            temp7 = A[i][n + 7];

                            B[i][n] = temp0;
                            B[i][n + 1] = temp1;
                            B[i][n + 2] = temp2;
                            B[i][n + 3] = temp3;
                            B[i][n + 4] = temp4;
                            B[i][n + 5] = temp5;
                            B[i][n + 6] = temp6;
                            B[i][n + 7] = temp7;
                        }

                        for (int i = m + 4; i < m + 8; ++i)
                        {
                            M = i - (m + 4);
                            for (int j = n + M; j < n + 4; ++j)
                            {
                                N = j - n;

                                temp0 = B[i][j];
                                B[i][j] = B[m + 4 + N][n + M];
                                B[m + 4 + N][n + M] = temp0;
                            }
                        }

                        for (int i = m + 4; i < m + 8; ++i)
                        {
                            M = i - (m + 4);
                            for (int j = n + 4 + M; j < n + 8; ++j)
                            {
                                N = j - (n + 4);
                                
                                temp0 = B[i][j];
                                B[i][j] = B[m + 4 + N][n + 4 + M];
                                B[m + 4 + N][n + 4 + M] = temp0;
                            }
                        }
// -------------------------------------------------------------------------------
                        for (int i = m + 4; i < m + 8; ++i)
                        {
                            temp0 = B[i][n];
                            temp1 = B[i][n + 1];
                            temp2 = B[i][n + 2];
                            temp3 = B[i][n + 3];

                            temp4 = B[i][n + 12];
                            temp5 = B[i][n + 13];
                            temp6 = B[i][n + 14];
                            temp7 = B[i][n + 15];

                            B[i][n] = temp4;
                            B[i][n + 1] = temp5;
                            B[i][n + 2] = temp6;
                            B[i][n + 3] = temp7;

                            B[i][n + 12] = temp0;
                            B[i][n + 13] = temp1;
                            B[i][n + 14] = temp2;
                            B[i][n + 15] = temp3;
                        }

                        for (int i = m; i < m + 4; ++i)
                            for (int j = n; j < n + 8; ++j)
                                B[i][j] = B[i + 4][j + 8];
                    }
                    else
                    {
                        for (int i = m; i < m + 4; ++i)
                        {
                            temp0 = A[i][n];
                            temp1 = A[i][n + 1];
                            temp2 = A[i][n + 2];
                            temp3 = A[i][n + 3];
                            temp4 = A[i][n + 4];
                            temp5 = A[i][n + 5];
                            temp6 = A[i][n + 6];
                            temp7 = A[i][n + 7];

                            B[i][n] = temp0;
                            B[i][n + 1] = temp1;
                            B[i][n + 2] = temp2;
                            B[i][n + 3] = temp3;
                            B[i][n + 4] = temp4;
                            B[i][n + 5] = temp5;
                            B[i][n + 6] = temp6;
                            B[i][n + 7] = temp7;
                        }

                        for (int i = m; i < m + 4; ++i)
                        {
                            for (int j = n + (i - m); j < n + 4; ++j)
                            {
                                if (i != j)
                                {
                                    temp0 = B[i][j];
                                    B[i][j] = B[j][i];
                                    B[j][i] = temp0;
                                }
                            }
                        }

                        for (int i = m; i < m + 4; ++i)
                        {
                            M = i - m;
                            for (int j = n + 4 + M; j < n + 8; ++j)
                            {
                                N = j - (n + 4);

                                temp0 = B[i][j];
                                B[i][j] = B[m + N][n + 4 + M];
                                B[m + N][n + 4 + M] = temp0;
                            }
                        }

                        for (int i = m + 4; i < m + 8; ++i)
                        {
                            temp0 = A[i][n];
                            temp1 = A[i][n + 1];
                            temp2 = A[i][n + 2];
                            temp3 = A[i][n + 3];
                            temp4 = A[i][n + 4];
                            temp5 = A[i][n + 5];
                            temp6 = A[i][n + 6];
                            temp7 = A[i][n + 7];

                            B[i][n] = temp0;
                            B[i][n + 1] = temp1;
                            B[i][n + 2] = temp2;
                            B[i][n + 3] = temp3;
                            B[i][n + 4] = temp4;
                            B[i][n + 5] = temp5;
                            B[i][n + 6] = temp6;
                            B[i][n + 7] = temp7;
                        }

                        for (int i = m + 4; i < m + 8; ++i)
                        {
                            for (int j = n + 4 + i - (m + 4); j < n + 8; ++j)
                            {
                                if (i != j)
                                {
                                    temp0 = B[i][j];
                                    B[i][j] = B[j][i];
                                    B[j][i] = temp0;
                                }
                            }
                        }

                        for (int i = m + 4; i < m + 8; ++i)
                        {
                            M = i - (m + 4);
                            for (int j = n + M; j < n + 4; ++j)
                            {
                                N = j - n;

                                temp0 = B[i][j];
                                B[i][j] = B[m + 4 + N][n + M];
                                B[m + 4 + N][n + M] = temp0;
                            }
                        }

                        for (int i = m + 4; i < m + 8; ++i)
                        {
                            temp0 = B[i][n];
                            temp1 = B[i][n + 1];
                            temp2 = B[i][n + 2];
                            temp3 = B[i][n + 3];

                            temp4 = B[i - 4][n + 4];
                            temp5 = B[i - 4][n + 5];
                            temp6 = B[i - 4][n + 6];
                            temp7 = B[i - 4][n + 7];

                            B[i - 4][n + 4] = temp0;
                            B[i - 4][n + 5] = temp1;
                            B[i - 4][n + 6] = temp2;
                            B[i - 4][n + 7] = temp3;

                            B[i][n] = temp4;
                            B[i][n + 1] = temp5;
                            B[i][n + 2] = temp6;
                            B[i][n + 3] = temp7;
                        }
                    }
                }
            }
        }
    }
    else
    {
        int n = 8 * (N / 8);
        int m = 8 * (M / 8);
        for (int i = 0; i < n; i += 8) 
        {
            for (int j = 0; j < m; j += 8) 
            {
                for (int ii = i; ii < i + 8; ++ii) 
                {
                    temp0 = A[ii][j];
                    temp1 = A[ii][j + 1];
                    temp2 = A[ii][j + 2];
                    temp3 = A[ii][j + 3];
                    temp4 = A[ii][j + 4];
                    temp5 = A[ii][j + 5];
                    temp6 = A[ii][j + 6];
                    temp7 = A[ii][j + 7];

                    B[j][ii] = temp0;
                    B[j + 1][ii] = temp1;
                    B[j + 2][ii] = temp2;
                    B[j + 3][ii] = temp3;
                    B[j + 4][ii] = temp4;
                    B[j + 5][ii] = temp5;
                    B[j + 6][ii] = temp6;
                    B[j + 7][ii] = temp7;
                }
            }
        }

        // 处理剩余部分
        for (int i = 0; i < n; i++) 
        {
            for (int j = m; j < M; j++) 
            {
                B[j][i] = A[i][j];
            }
        }
        for (int i = n; i < N; i++) 
        {
            for (int j = 0; j < M; j++) 
            {
                B[j][i] = A[i][j];
            }
        }
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])      //一个示例
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

void transpose_draft(int M, int N, int A[N][M], int B[M][N])   //我自己构造的草稿函数
{
    int temp0, temp1, temp2, temp3, temp4, temp5, temp6, temp7; //临时变量
    if(M==32)
    {
        for (int m = 0; m < 32; m += 8)         //划分为横条
        {
            for (int n = 0; n < 32; n += 8)     //在横条基础上划分为小块
            {
                if (m == n)                         //是对角线上的（块矩阵）
                {
                    for (int i = m; i < m + 8; ++i)     //展开以避免冲突
                    {
                        temp0 = A[i][n];
                        temp1 = A[i][n + 1];
                        temp2 = A[i][n + 2];
                        temp3 = A[i][n + 3];
                        temp4 = A[i][n + 4];
                        temp5 = A[i][n + 5];
                        temp6 = A[i][n + 6];
                        temp7 = A[i][n + 7];

                        B[i][n] = temp0;
                        B[i][n + 1] = temp1;
                        B[i][n + 2] = temp2;
                        B[i][n + 3] = temp3;
                        B[i][n + 4] = temp4;
                        B[i][n + 5] = temp5;
                        B[i][n + 6] = temp6;
                        B[i][n + 7] = temp7;
                    }
                    for (int i = m; i < m + 8; ++i)     //对角线块的每行
                    {
                        for (int j = n + (i - m + 1); j < n + 8; ++j)   //从每行之于对角线
                        {                                                    //上的元素开始
                            if (i != j)
                            {
                                temp0 = B[i][j];
                                B[i][j] = B[j][i];
                                B[j][i] = temp0;
                            }
                        }
                    }
                }
                else            //不是对角线上的——直接处理
                {
                    for (int i = m; i < m + 8; ++i)
                    {
                        for (int j = n; j < n + 8; ++j)
                        {
                            B[j][i] = A[i][j];
                        }
                    }
                }
            }
        }
    }
    else if(M==64)
    {
        for (int m = 0; m < 64; m += 8)
        {
            for (int n = m; n < 64; n += 8)
            {
                if (m != n)
                {
                    for (int i = n; i < n + 4; ++i)
                    {
                        N = i - n;

                        temp0 = A[i][m];
                        temp1 = A[i][m + 1];
                        temp2 = A[i][m + 2];
                        temp3 = A[i][m + 3];

                        temp4 = A[i][m + 4];
                        temp5 = A[i][m + 5];
                        temp6 = A[i][m + 6];
                        temp7 = A[i][m + 7];

                        B[m + 4][n + N] = temp4;
                        B[m + 5][n + N] = temp5;
                        B[m + 6][n + N] = temp6;
                        B[m + 7][n + N] = temp7;

                        B[m + 4][n + 4 + N] = temp0;
                        B[m + 5][n + 4 + N] = temp1;
                        B[m + 6][n + 4 + N] = temp2;
                        B[m + 7][n + 4 + N] = temp3;
                    }

                    for (int i = m + 4; i < m + 8; ++i)
                    {
                        N = i - (m + 4);

                        temp0 = A[n + 4][m + 4 + N];
                        temp1 = A[n + 5][m + 4 + N];
                        temp2 = A[n + 6][m + 4 + N];
                        temp3 = A[n + 7][m + 4 + N];

                        temp4 = B[m + 4 + N][n + 4];
                        temp5 = B[m + 4 + N][n + 5];
                        temp6 = B[m + 4 + N][n + 6];
                        temp7 = B[m + 4 + N][n + 7];

                        B[m + 4 + N][n + 4] = temp0;
                        B[m + 4 + N][n + 5] = temp1;
                        B[m + 4 + N][n + 6] = temp2;
                        B[m + 4 + N][n + 7] = temp3;

                        B[m + N][n] = temp4;
                        B[m + N][n + 1] = temp5;
                        B[m + N][n + 2] = temp6;
                        B[m + N][n + 3] = temp7;
                    }

                    for (int i = m; i < m + 4; ++i)
                    {
                        temp0 = A[n + 4][i];
                        temp1 = A[n + 5][i];
                        temp2 = A[n + 6][i];
                        temp3 = A[n + 7][i];

                        B[i][n + 4] = temp0;
                        B[i][n + 5] = temp1;
                        B[i][n + 6] = temp2;
                        B[i][n + 7] = temp3;
                    }
                    ///////////////////////////////////////////////////////////////////////////////////
                    for (int i = m + 4; i < m + 8; ++i)
                    {
                        M = i - (m + 4);

                        temp0 = A[i][n];
                        temp1 = A[i][n + 1];
                        temp2 = A[i][n + 2];
                        temp3 = A[i][n + 3];

                        temp4 = A[i][n + 4];
                        temp5 = A[i][n + 5];
                        temp6 = A[i][n + 6];
                        temp7 = A[i][n + 7];

                        B[n][m + M] = temp4;
                        B[n + 1][m + M] = temp5;
                        B[n + 2][m + M] = temp6;
                        B[n + 3][m + M] = temp7;

                        B[n][m + 4 + M] = temp0;
                        B[n + 1][m + 4 + M] = temp1;
                        B[n + 2][m + 4 + M] = temp2;
                        B[n + 3][m + 4 + M] = temp3;
                    }

                    for (int i = n; i < n + 4; ++i)
                    {
                        temp0 = A[m][i];
                        temp1 = A[m + 1][i];
                        temp2 = A[m + 2][i];
                        temp3 = A[m + 3][i];

                        temp4 = B[i][m];
                        temp5 = B[i][m + 1];
                        temp6 = B[i][m + 2];
                        temp7 = B[i][m + 3];

                        B[i][m] = temp0;
                        B[i][m + 1] = temp1;
                        B[i][m + 2] = temp2;
                        B[i][m + 3] = temp3;

                        B[i + 4][m + 4] = temp4;
                        B[i + 4][m + 5] = temp5;
                        B[i + 4][m + 6] = temp6;
                        B[i + 4][m + 7] = temp7;
                    }

                    for (int i = m; i < m + 4; ++i)
                    {
                        M = i - m;

                        temp0 = A[i][n + 4];
                        temp1 = A[i][n + 5];
                        temp2 = A[i][n + 6];
                        temp3 = A[i][n + 7];

                        B[n + 4][m + M] = temp0;
                        B[n + 5][m + M] = temp1;
                        B[n + 6][m + M] = temp2;
                        B[n + 7][m + M] = temp3;
                    }
                }
                //*******************************************************************************//
                else
                {
                    if (m != 56 && n != 56)
                    {
                        for (int i = m; i < m + 4; ++i)
                        {
                            M = i - m;

                            temp0 = A[i][n];
                            temp1 = A[i][n + 1];
                            temp2 = A[i][n + 2];
                            temp3 = A[i][n + 3];

                            temp4 = A[i][n + 4];
                            temp5 = A[i][n + 5];
                            temp6 = A[i][n + 6];
                            temp7 = A[i][n + 7];

                            B[m + 4][n + 8 + M] = temp0;
                            B[m + 5][n + 8 + M] = temp1;
                            B[m + 6][n + 8 + M] = temp2;
                            B[m + 7][n + 8 + M] = temp3;

                            B[m + 4][n + 12 + M] = temp4;
                            B[m + 5][n + 12 + M] = temp5;
                            B[m + 6][n + 12 + M] = temp6;
                            B[m + 7][n + 12 + M] = temp7;
                        }
// -----------------------------------------------------------------------
                        for (int i = m + 4; i < m + 8; ++i)
                        {
                            temp0 = A[i][n];
                            temp1 = A[i][n + 1];
                            temp2 = A[i][n + 2];
                            temp3 = A[i][n + 3];
                            temp4 = A[i][n + 4];
                            temp5 = A[i][n + 5];
                            temp6 = A[i][n + 6];
                            temp7 = A[i][n + 7];

                            B[i][n] = temp0;
                            B[i][n + 1] = temp1;
                            B[i][n + 2] = temp2;
                            B[i][n + 3] = temp3;
                            B[i][n + 4] = temp4;
                            B[i][n + 5] = temp5;
                            B[i][n + 6] = temp6;
                            B[i][n + 7] = temp7;
                        }

                        for (int i = m + 4; i < m + 8; ++i)
                        {
                            M = i - (m + 4);
                            for (int j = n + M; j < n + 4; ++j)
                            {
                                N = j - n;

                                temp0 = B[i][j];
                                B[i][j] = B[m + 4 + N][n + M];
                                B[m + 4 + N][n + M] = temp0;
                            }
                        }

                        for (int i = m + 4; i < m + 8; ++i)
                        {
                            M = i - (m + 4);
                            for (int j = n + 4 + M; j < n + 8; ++j)
                            {
                                N = j - (n + 4);
                                
                                temp0 = B[i][j];
                                B[i][j] = B[m + 4 + N][n + 4 + M];
                                B[m + 4 + N][n + 4 + M] = temp0;
                            }
                        }
// -------------------------------------------------------------------------------
                        for (int i = m + 4; i < m + 8; ++i)
                        {
                            temp0 = B[i][n];
                            temp1 = B[i][n + 1];
                            temp2 = B[i][n + 2];
                            temp3 = B[i][n + 3];

                            temp4 = B[i][n + 12];
                            temp5 = B[i][n + 13];
                            temp6 = B[i][n + 14];
                            temp7 = B[i][n + 15];

                            B[i][n] = temp4;
                            B[i][n + 1] = temp5;
                            B[i][n + 2] = temp6;
                            B[i][n + 3] = temp7;

                            B[i][n + 12] = temp0;
                            B[i][n + 13] = temp1;
                            B[i][n + 14] = temp2;
                            B[i][n + 15] = temp3;
                        }

                        for (int i = m; i < m + 4; ++i)
                            for (int j = n; j < n + 8; ++j)
                                B[i][j] = B[i + 4][j + 8];
                    }
                    else
                    {
                        for (int i = m; i < m + 4; ++i)
                        {
                            temp0 = A[i][n];
                            temp1 = A[i][n + 1];
                            temp2 = A[i][n + 2];
                            temp3 = A[i][n + 3];
                            temp4 = A[i][n + 4];
                            temp5 = A[i][n + 5];
                            temp6 = A[i][n + 6];
                            temp7 = A[i][n + 7];

                            B[i][n] = temp0;
                            B[i][n + 1] = temp1;
                            B[i][n + 2] = temp2;
                            B[i][n + 3] = temp3;
                            B[i][n + 4] = temp4;
                            B[i][n + 5] = temp5;
                            B[i][n + 6] = temp6;
                            B[i][n + 7] = temp7;
                        }

                        for (int i = m; i < m + 4; ++i)
                        {
                            for (int j = n + (i - m); j < n + 4; ++j)
                            {
                                if (i != j)
                                {
                                    temp0 = B[i][j];
                                    B[i][j] = B[j][i];
                                    B[j][i] = temp0;
                                }
                            }
                        }

                        for (int i = m; i < m + 4; ++i)
                        {
                            M = i - m;
                            for (int j = n + 4 + M; j < n + 8; ++j)
                            {
                                N = j - (n + 4);

                                temp0 = B[i][j];
                                B[i][j] = B[m + N][n + 4 + M];
                                B[m + N][n + 4 + M] = temp0;
                            }
                        }

                        for (int i = m + 4; i < m + 8; ++i)
                        {
                            temp0 = A[i][n];
                            temp1 = A[i][n + 1];
                            temp2 = A[i][n + 2];
                            temp3 = A[i][n + 3];
                            temp4 = A[i][n + 4];
                            temp5 = A[i][n + 5];
                            temp6 = A[i][n + 6];
                            temp7 = A[i][n + 7];

                            B[i][n] = temp0;
                            B[i][n + 1] = temp1;
                            B[i][n + 2] = temp2;
                            B[i][n + 3] = temp3;
                            B[i][n + 4] = temp4;
                            B[i][n + 5] = temp5;
                            B[i][n + 6] = temp6;
                            B[i][n + 7] = temp7;
                        }

                        for (int i = m + 4; i < m + 8; ++i)
                        {
                            for (int j = n + 4 + i - (m + 4); j < n + 8; ++j)
                            {
                                if (i != j)
                                {
                                    temp0 = B[i][j];
                                    B[i][j] = B[j][i];
                                    B[j][i] = temp0;
                                }
                            }
                        }

                        for (int i = m + 4; i < m + 8; ++i)
                        {
                            M = i - (m + 4);
                            for (int j = n + M; j < n + 4; ++j)
                            {
                                N = j - n;

                                temp0 = B[i][j];
                                B[i][j] = B[m + 4 + N][n + M];
                                B[m + 4 + N][n + M] = temp0;
                            }
                        }

                        for (int i = m + 4; i < m + 8; ++i)
                        {
                            temp0 = B[i][n];
                            temp1 = B[i][n + 1];
                            temp2 = B[i][n + 2];
                            temp3 = B[i][n + 3];

                            temp4 = B[i - 4][n + 4];
                            temp5 = B[i - 4][n + 5];
                            temp6 = B[i - 4][n + 6];
                            temp7 = B[i - 4][n + 7];

                            B[i - 4][n + 4] = temp0;
                            B[i - 4][n + 5] = temp1;
                            B[i - 4][n + 6] = temp2;
                            B[i - 4][n + 7] = temp3;

                            B[i][n] = temp4;
                            B[i][n + 1] = temp5;
                            B[i][n + 2] = temp6;
                            B[i][n + 3] = temp7;
                        }
                    }
                }
            }
        }
    }
    else
    {
        int n = 8 * (N / 8);
        int m = 8 * (M / 8);
        for (int i = 0; i < n; i += 8) 
        {
            for (int j = 0; j < m; j += 8) 
            {
                for (int ii = i; ii < i + 8; ++ii) 
                {
                    temp0 = A[ii][j];
                    temp1 = A[ii][j + 1];
                    temp2 = A[ii][j + 2];
                    temp3 = A[ii][j + 3];
                    temp4 = A[ii][j + 4];
                    temp5 = A[ii][j + 5];
                    temp6 = A[ii][j + 6];
                    temp7 = A[ii][j + 7];

                    B[j][ii] = temp0;
                    B[j + 1][ii] = temp1;
                    B[j + 2][ii] = temp2;
                    B[j + 3][ii] = temp3;
                    B[j + 4][ii] = temp4;
                    B[j + 5][ii] = temp5;
                    B[j + 6][ii] = temp6;
                    B[j + 7][ii] = temp7;
                }
            }
        }

        // 处理剩余部分
        for (int i = 0; i < n; i++) 
        {
            for (int j = m; j < M; j++) 
            {
                B[j][i] = A[i][j];
            }
        }
        for (int i = n; i < N; i++) 
        {
            for (int j = 0; j < M; j++) 
            {
                B[j][i] = A[i][j];
            }
        }
    }
}
