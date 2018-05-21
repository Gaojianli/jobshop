#include <omp.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#define MAX_NUM 25
#define MAX_LEN 600
int GAP, ENCRYPT_NUM, MAX_POP;
double GER_MUL, DIE_RATIO, MUT_MUL;

struct job
{
    int n;
    int time[MAX_NUM];
    int mac[MAX_NUM];
} jobs[MAX_NUM];

typedef struct gene
{
    int sequence[MAX_LEN];
    double fitness;
    double live_p;
    int caled;
    int alive;
    int time;
    int haveBeenCrossed;
}gene;

struct block
{
    int start;
    int end;
    int jobRec;
    int opeRec;
} blocks[MAX_NUM][MAX_NUM];

gene pop[3000];

int jobNum, macNum, all_num, parents, length, x_all;

int gapNum[MAX_NUM], lastTime[MAX_NUM], start[MAX_NUM][MAX_NUM], end[MAX_NUM][MAX_NUM], last[MAX_NUM];

int onum[MAX_NUM];
int ostart[MAX_NUM][MAX_NUM];
int oend[MAX_NUM][MAX_NUM];
int jobDone[MAX_NUM];
#include "utils.h"
#include "input.h"
#include "encrypt.h"
#include "inherit.h"
#include "judge.h"
#include "dead.h"