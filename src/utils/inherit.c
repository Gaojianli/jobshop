/*
@file:inherit.c 
@author:Group All
@version:1.3.1
@date:17/5/18
@description:
    The implement of the inheritance, including cross of the gene and mutation
*/

#include "../../include/jobshop.h"

// Cross the gene with the number of "which" using self-bred
gene crossOnce(int which)
{
    int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
    int y[4];
    while (!(a1 != a2 && a1 != b1 && a1 != b2 && a2 != b1 && a2 != b2 && b1 != b2))
    {
        unsigned long long r = rand() * rand();
        a1 = r % length;
        r = rand() * rand();
        a2 = r % length;
        r = rand() * rand();
        b1 = r % length;
        r = rand() * rand();
        b2 = r % length;
    }
    y[0] = a1, y[1] = a2, y[2] = b1, y[3] = b2;
    qsort(y, 4, sizeof(int), cmp);
    a1 = y[0], a2 = y[1], b1 = y[2], b2 = y[3];
    int newBorn[length + 2];
    int i;
    for (i = 0; i < a1; i++)
        newBorn[i] = pop[which].sequence[i];
    for (; i < a1 + b2 - b1 + 1; i++)
        newBorn[i] = pop[which].sequence[i - a1 + b1];
    for (; i < a1 - a2 + b2; i++)
        newBorn[i] = pop[which].sequence[i - (a1 + b2 - b1 + 1) + a2 + 1];
    for (; i < b2 + 1; i++)
        newBorn[i] = pop[which].sequence[i - (a1 - a2 + b2) + a1];
    for (; i < length; i++)
        newBorn[i] = pop[which].sequence[i];
    gene x = pop[which];
    for (int i = 0; i < length; i++)
        x.sequence[i] = newBorn[i];
    x.caled = 0;
    return x;
}

// Select genes randomly and cross them with the total amount of all_num / GER_MUL
void cross()
{
    int randNum;
    int crossed[2000];
    memset(crossed, 0, sizeof(crossed));
    for (int i = 0; i < all_num / GER_MUL; i++)
    {
        unsigned long long r = rand() * rand();
        randNum = r % all_num;
        if (crossed[randNum] == false)
        {
            pop[all_num] = crossOnce(randNum);
            crossed[randNum] = true;
            all_num++;
        }
    }
    for (int i = 0; i < all_num; i++)
    {
        if (pop[i].caled)
            continue;
        pop[i].time = calculateTime(length, pop[i].sequence);
        pop[i].caled = 1;
        pop[i].fitness = 1 / (double)(pop[i].time + 1);
    }
}

// Proceed the mutation operation on the gene with the number "num"
void mutate(int num)
{
    int a1 = 0, a2 = 0, a3 = 0;
    while (!((a1 != a2) && (a2 != a3) && (a3 != a1)))
    {
        unsigned long long r = rand() * rand();
        a1 = r % length;
        r = rand() * rand();
        a2 = r % length;
        r = rand() * rand();
        a3 = r % length;
    }

    // Generating 
    gene x[6];
    x[0] = x[1] = x[2] = x[3] = x[4] = x[5] = pop[num];
    x[1].sequence[a2] = pop[num].sequence[a3], x[1].sequence[a3] = pop[num].sequence[a2];
    x[2].sequence[a1] = pop[num].sequence[a2], x[2].sequence[a2] = pop[num].sequence[a1];
    x[3].sequence[a1] = pop[num].sequence[a2], x[3].sequence[a2] = pop[num].sequence[a3], x[3].sequence[a3] = pop[num].sequence[a1];
    x[4].sequence[a1] = pop[num].sequence[a3], x[4].sequence[a2] = pop[num].sequence[a1], x[4].sequence[a3] = pop[num].sequence[a2];
    x[5].sequence[a1] = pop[num].sequence[a3], x[5].sequence[a2] = pop[num].sequence[a2], x[5].sequence[a3] = pop[num].sequence[a1];
    int k = 0, min_time = pop[num].time;
#pragma omp parallel for
    for (int i = 1; i <= 5; i++)
    {
        x[i].time = calculateTime(length, x[i].sequence);
        if (min_time > x[i].time)
        {
            k = i;
            min_time = x[i].time;
        }
    }
    x[k].caled = 1;
    x[k].fitness = 1 / (double)(x[k].time + 1);
    pop[num] = x[k];
}

void generate()
{
    for (int i = 0; i < GAP; i++)
    {
        cross();
        selectFunc();
        int n = all_num / MUT_MUL;
        for (int j = 0; j < n; j++)
        {
            unsigned long long r = rand() * rand();
            int num = rand() % all_num;
            mutate(num);
        }
        cal_p();
        x_all = all_num;
        die();
        replace();
        parents = all_num;
    }
}


