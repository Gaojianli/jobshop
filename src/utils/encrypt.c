/*
@file:encrypt.c 
@author:Yibo Zhang
@version:1.0
@date:10/5/18
@description:
    The implement of the encode, convert sequence into code
*/

#include "../../include/jobshop.h"

// Create a legal gene sequence randomly
void encrypt_one(int num)
{
    pop[num].caled = 0;
    pop[num].alive = 1;
    pop[num].haveBeenCrossed = 0;
    int jobN[jobNum + 2], gene_len = 0;
    memset(jobN, 0, sizeof(jobN));
#pragma omp parallel for
    for (int i = 0; i < jobNum; i++)
        jobN[i] = jobs[i].n;
    while (!isZero(jobN, jobNum)) 
    {
        unsigned long long r = rand() * rand();
        int temp = r % jobNum;
        if (jobN[temp] != 0)
        {
            pop[num].sequence[gene_len++] = temp;
            jobN[temp]--;
        }
    }
    return;
}

// Generate the whole gene pool with the population of ENCRYPT_NUM
void encrypt_main()
{
    for (int i = 0; i < ENCRYPT_NUM; i++)
        encrypt_one(i);
    x_all = all_num = parents = ENCRYPT_NUM;
}

