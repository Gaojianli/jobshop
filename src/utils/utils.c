/*
@file:utils.c 
@author:Group All
@version:1.3
@date:21/5/18
@description:
    Others, implements of utils
*/

#include "../../include/jobshop.h"
void init()
{
    srand(time(NULL));
    encrypt_main();
    cal_len();
    for (int i = 0; i < all_num; i++)
    {
        pop[i].time = calculateTime(length, pop[i].sequence);
        pop[i].caled = 1;
        pop[i].fitness = 1 / (double)(pop[i].time + 1);
    }
}

int isZero(int *cha, int len)
{
    int flag = 1;
    for (int i = 0; i < len; i++)
        if (cha[i] != 0)
            return 0;
    return 1;
}

int cmp(const void *a, const void *b)
{
    return *((int *)a) - *((int *)b);
}

void cal_len()
{
    int len = 0;
    for (int i = 0; i < jobNum; i++)
        len += jobs[i].n;
    length = len;
}

gene out()
{
    int min = 0x3F3F3F3F, k = 0;
    for (int i = 0; i < all_num; i++)
    {
        if (pop[i].time < min && pop[i].time != 0)
        {
            min = pop[i].time;
            k = i;
        }
        //for(int j = 0; j < length; j++) printf("%d%c", pop[i].sequence[j], j == length - 1 ? '\n' : ' ');
        //printf("%d\n", pop[i].time);
    }
    return pop[k];
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

void output(int n, int *seq)
{

    int i, j, k;
    for (i = 0; i < MAX_NUM; i++)
    {
        gapNum[i] = 0;
        lastTime[i] = 0;
        onum[i] = 0;
        jobDone[i] = 0;
        last[i] = 0;
        for (j = 0; j < MAX_NUM; j++)
        {
            start[i][j] = end[i][j] = 0;
            blocks[i][j].start = blocks[i][j].end = blocks[i][j].jobRec = blocks[i][j].opeRec = 0;
            oend[i][j] = ostart[i][j] = 0;
        }
    }

    for (i = 0; i < n; i++)
    {
        int num = jobDone[seq[i]];
        int mac_1 = jobs[seq[i]].mac[num];
        jobDone[seq[i]]++;
        insert(seq[i], num);
    }

    for (i = 1; i <= macNum; i++)
    {
        printf("M%d", i - 1);
        for (j = 0; j < onum[i]; j++)
        {
            if (blocks[i][j].start == blocks[i][j].end)
                continue;
            printf(" (%d,%d-%d,%d)", blocks[i][j].start, blocks[i][j].jobRec, blocks[i][j].opeRec, blocks[i][j].end);
        }
        printf("\n");
    }
}

void outputFile(int n, int *seq, FILE *fPtr)
{
    int i, j, k;

    for (i = 0; i < MAX_NUM; i++)
    {
        gapNum[i] = 0;
        lastTime[i] = 0;
        onum[i] = 0;
        jobDone[i] = 0;
        last[i] = 0;
        for (j = 0; j < MAX_NUM; j++)
        {
            start[i][j] = end[i][j] = 0;
            blocks[i][j].start = blocks[i][j].end = blocks[i][j].jobRec = blocks[i][j].opeRec = 0;
            oend[i][j] = ostart[i][j] = 0;
        }
    }

    for (i = 0; i < n; i++)
    {
        int num = jobDone[seq[i]];
        int mac_1 = jobs[seq[i]].mac[num];
        jobDone[seq[i]]++;
        insert(seq[i], num);
    }

    for (i = 1; i <= macNum; i++)
    {
        fprintf(fPtr, "M%d", i - 1);
        for (j = 0; j < onum[i]; j++)
        {
            if (blocks[i][j].start == blocks[i][j].end)
                continue;
            fprintf(fPtr, " (%d,%d-%d,%d)", blocks[i][j].start, blocks[i][j].jobRec, blocks[i][j].opeRec, blocks[i][j].end);
        }
        fprintf(fPtr, "\r\n");
    }
}



void printUsage()
{
    printf("Usage:\n(optional)-f <data_filepath>\tread data from the file\n");
    printf("(optional)-C <config_file_path>\tread options from the config file\n");
    printf("(optional)-o <output_file>\tprint the result into a file instead of console\n");
    printf("OR:\n-g <int>\tthe gap of the population\n");
    printf("-m <double>\treproductive ratio,the number of units which can reproduce is <ALL>/<this_ratio>\n");
    printf("-i <int>\tthe number of initial population\n");
    printf("-p <int>\tthe max number of a population\n");
    printf("-d <double>\tdead ratio, in each generation,the new number of population is <number_of_old>*1/<this ratio>\n");
    printf("-c <double>\tmutational ratio, the number of mutational units is <ALL>/<this_ratio>\n");
    printf("-h\t\tshow this help\n");
}