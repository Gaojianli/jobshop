#include "../../include/jobshop.h"
int calculateTime(int n, int *_gene)
{
    int i, j;
    int *jobDone = (int *)calloc(MAX_NUM, sizeof(int));

    int ret = 0;

    memset(gapNum, 0, sizeof(gapNum));
    memset(lastTime, 0, sizeof(lastTime));
    memset(start, 0, sizeof(start));
    memset(end, 0, sizeof(end));
    memset(last, 0, sizeof(last));

    for (i = 0; i < n; i++)
    {
        int num = jobDone[_gene[i]];
        jobDone[_gene[i]]++;
        int tim = insertOne(_gene[i], num);
        if (tim > ret)
            ret = tim;
    }
    free(jobDone);
    return ret;
}


gene sBest(int flag)
{
    gene temp;
    switch (flag)
    {
    case 0:
    {
        temp = pop[0];
        for (int i = 1; i < parents; i++)
            if (pop[i].time < temp.time)
                temp = pop[i];
        return temp;
    }
    case 1:
    {
        temp = pop[parents];
        for (int i = parents; i < all_num; i++)
            if (pop[i].time < temp.time)
                temp = pop[i];
        return temp;
    }
    }
}

void selectFunc()
{
    gene bestPar = sBest(0), bestChi = sBest(1);
    if (bestPar.time < bestChi.time)
    {
        if (parents < all_num)
        {
            int choice, flag = 1;
            for (;;)
            {
                unsigned long long r = rand() * rand();
                choice = r % all_num;
                if (choice >= parents)
                {
                    pop[choice] = bestPar;
                    break;
                }
            }
        }
    }
}

void cal_p()
{
    double base = 0;
    for (int i = 0; i < all_num; i++)
        base += pop[i].fitness;
    base = base / all_num * DIE_RATIO;
    for (int i = 0; i < all_num; i++)
        pop[i].live_p = pop[i].fitness / base;
}