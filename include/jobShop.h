#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <math.h>
#include "input.h"
#include "output.h"
#include "encrypt.h"
#include "inherit.h"
#include "judge.h"
#define MAX_NUM 25
#define MAX_LEN 255
#pragma once

static struct job {
    int n;
    int time[MAX_NUM];
    int mac[MAX_NUM];
} jobs[MAX_NUM];

struct gene {
    int sequence[MAX_LEN];
    double fitness;
    double live_p;
    int caled;
    int alive;
    int time;
};

static gene pop[2000];

static int jobNum, macNum, all_num, parents, length;
