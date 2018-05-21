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

void insert(int i, int j) {
    int mac = jobs[i].mac[j];
    int flag = 0;

    int startTime, endTime;
    int temp;
    int l, tm;
    tm = jobs[i].time[j];
    int k;
    for (k = 0; k < gapNum[mac]; k++) {
        if (flag) break;
        if (end[mac][k] - last[i] < tm) continue;
        if (end[mac][k] - start[mac][k] < tm) continue;
        flag = 1;

        for (l = 0; l < onum[mac]; l++) {
            if (blocks[mac][l].start >= end[mac][k]) break;
        }

        temp = l;

        for (l = onum[mac]; l > temp; l--) {
            blocks[mac][l].start = blocks[mac][l - 1].start;
            blocks[mac][l].end = blocks[mac][l - 1].end;
            blocks[mac][l].jobRec = blocks[mac][l - 1].jobRec;
            blocks[mac][l].opeRec = blocks[mac][l - 1].opeRec;
        }

        if (last[i] >= start[mac][k]) {
            startTime = last[i];
            blocks[mac][temp].start = last[i];
            blocks[mac][temp].end = last[i] + tm;
            blocks[mac][temp].jobRec = i;
            blocks[mac][temp].opeRec = j;
        }
        else {
            startTime = start[mac][k];
            blocks[mac][temp].start = startTime;
            blocks[mac][temp].end = startTime + tm;
            blocks[mac][temp].jobRec = i;
            blocks[mac][temp].opeRec = j;
        }
        temp = end[mac][k];
        end[mac][k] = startTime;
        endTime = tm + startTime;

        for (l = gapNum[mac]; l > k + 1; l--) {
            start[mac][l] = start[mac][l - 1];
            end[mac][l] = end[mac][l - 1];
        }
        start[mac][k + 1] = endTime;
        end[mac][k + 1] = temp;
        gapNum[mac]++; 
        onum[mac]++;
        last[i] = start[mac][k + 1];
    }
    if (!flag) {
        if (lastTime[mac] < last[i]) {
            blocks[mac][onum[mac]].start = last[i];
            blocks[mac][onum[mac]].end = last[i] + tm;
            blocks[mac][onum[mac]].jobRec = i;
            blocks[mac][onum[mac]].opeRec = j;
            onum[mac]++;
            end[mac][gapNum[mac]] = last[i];
            start[mac][gapNum[mac]] = lastTime[mac];
            lastTime[mac] = last[i] + tm;
            last[i] += tm;
            gapNum[mac]++;
            return;
        }
        blocks[mac][onum[mac]].start = lastTime[mac];
        blocks[mac][onum[mac]].end = lastTime[mac] + tm;
        blocks[mac][onum[mac]].jobRec = i;
        blocks[mac][onum[mac]].opeRec = j;
        onum[mac]++;
        lastTime[mac] += tm;
        last[i] = lastTime[mac];
    }
}
