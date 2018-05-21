#include "../../include/jobshop.h"
void input_console()
{
    /*scanf("%d%d", &jobNum, &macNum);
    int i, j;
    for (i = 0; i < jobNum; i++)
        jobs[i].n = macNum;
    for (i = 0; i < jobNum; i++)
    {
        for (j = 0; j < macNum; j++)
        {
            scanf("%d", &jobs[i].time[j]);
        }
    }
    for (i = 0; i < jobNum; i++)
    {
        for (j = 0; j < macNum; j++)
        {
            scanf("%d", &jobs[i].mac[j]);
        }
    }
    return;*/
    scanf("%d%d", &jobNum, &macNum);
    for (int i = 0; i < jobNum; i++)
    {
        jobs[i].n = macNum;
        for (int j = 0; j < macNum; j++)
        {
            scanf("%d%d", &jobs[i].mac[j], &jobs[i].time[j]);
            jobs[i].mac[j]++;
        }
    }
}

void input_file(const char *filepath)
{
    FILE *fp = fopen(filepath, "r");
    fscanf(fp, "%d%d", &jobNum, &macNum);
    for (int i = 0; i < jobNum; i++)
    {
        jobs[i].n = macNum;
        for (int j = 0; j < macNum; j++)
        {
            fscanf(fp, "%d%d", &jobs[i].mac[j], &jobs[i].time[j]);
            jobs[i].mac[j]++;
        }
    }
}