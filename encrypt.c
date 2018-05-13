#pragma execution_character_set("utf-8")
void encrypt_main()
{
    for(int i = 0; i < 100; i++) encrypt_one(i);
}

void encrypt_one(int num)
{
    pop[num].caled = 0;
    pop[num].alive = 1;
    int jobN[jobNum + 2], gene_len = 0;
    memset(jobN, 0, sizeof(jobN));
    for(int i = 0; i < jobNum; i++) jobN[i] = jobs[i].n;
    while(!isZero(jobN, jobNum))
    {
        scrand(time(NULL));
        int temp = rand() % jobNum;
        if(jobN[temp] != 0)
        {
            pop[num].sequence[gene_len++] = temp;
            jobN[temp]--;
        }
    }
    return;
}

int isZero(int *cha, int len)
{
    int flag = 1;
    for(int i = 0; i < len; i++) if(cha[i] != 0) return 0;
    return 1;
}

