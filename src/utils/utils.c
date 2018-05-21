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
        printf("M%d", i);
        for (j = 0; j < onum[i]; j++)
        {
            if (blocks[i][j].start == blocks[i][j].end)
                continue;
            printf(" (%d,%d-%d,%d)", blocks[i][j].start, blocks[i][j].jobRec + 1, blocks[i][j].opeRec + 1, blocks[i][j].end);
        }
        printf("\n");
    }
}

void printUsage()
{
    printf("Usage:\n(optional)-f <data_filepath>\tread data from the file\n");
    printf("(optional)-C <config_file_path>\t read options from the config file\n");
    printf("OR:\n-g <int>\tthe gap of the population\n");
    printf("-m <double>\treproductive ratio,the number of units which can reproduce is <ALL>/<this_ratio>\n");
    printf("-i <int>\tthe number of initial population\n");
    printf("-p <int>\tthe max number of a population\n");
    printf("-d <double>\tdead ratio, in each generation,the new number of population is <number_of_old>*1/<this ratio>\n");
    printf("-c <double>\tmutational ratio, the number of mutational units is <ALL>/<this_ratio>\n");
    printf("-h\t\tshow this help\n");
}