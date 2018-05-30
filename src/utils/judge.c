/*
@file:judge.c 
@author:Group All
@version:1.2
@date:19/5/18
@description:
    The implement of the judgement, decide which item can live
*/
#include "../../include/jobshop.h"

int insertOne(int i, int j)
{
    int k;
    int startTime, endTime;
    int mac = jobs[i].mac[j];
    int flag = 0;
    int tm = jobs[i].time[j];
    for (k = 0; k < gapNum[mac]; k++)
    {
        if (flag)
            break;
        if (end[mac][k] - last[i] < tm)
            continue;
        if (end[mac][k] - start[mac][k] < tm)
            continue;
        flag = 1;

        if (last[i] >= start[mac][k])
            startTime = last[i];
        else
            startTime = start[mac][k];
        int temp = end[mac][k];
        end[mac][k] = startTime;
        endTime = tm + startTime;

        int l;
        for (l = gapNum[mac]; l > k + 1; l--)
        {
            start[mac][l] = start[mac][l - 1];
            end[mac][l] = end[mac][l - 1];
        }
        start[mac][k + 1] = endTime;
        end[mac][k + 1] = temp;
        gapNum[mac]++;
        last[i] = start[mac][k + 1];
    }
    if (!flag)
    {
        if (lastTime[mac] < last[i])
        {

            end[mac][gapNum[mac]] = last[i];
            start[mac][gapNum[mac]] = lastTime[mac];
            lastTime[mac] = last[i] + tm;
            last[i] += tm;
            gapNum[mac]++;
            return lastTime[mac];
        }
        lastTime[mac] += tm;
        last[i] = lastTime[mac];
    }
    return lastTime[mac];
}

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

    for (i = 0; i < n; i++) {
        int num = jobDone[_gene[i]];
        jobDone[_gene[i]]++;
        int tim = insertOne(_gene[i], num);
        if (tim > ret)
            ret = tim;
    }
    free(jobDone);
    return ret;
}


int sBest(int flag)
{
    int temp;
    switch (flag)
    {
    case 0:
    {
        temp = 0;
        for (int i = 1; i < parents; i++)
            if (pop[i].time < pop[temp].time)
                temp = i;
        return temp;
    }
    case 1:
    {
        temp = parents;
        for (int i = parents; i < all_num; i++)
            if (pop[i].time < pop[temp].time)
                temp = i;
        return temp;
    }
    }
}

void selectFunc()
{
    int bestPar = sBest(0), bestChi = sBest(1);
    if (pop[bestPar].time < pop[bestChi].time)
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
                    pop[choice] = pop[bestPar];
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