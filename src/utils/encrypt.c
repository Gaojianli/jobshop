#include "../../include/jobshop.h"
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
void encrypt_main()
{
#pragma omp parallel for
    for (int i = 0; i < ENCRYPT_NUM; i++)
        encrypt_one(i);
    x_all = all_num = parents = ENCRYPT_NUM;
}

