int main()
{
    input();
    init();
    generate();
    output();
}

void init()
{
    memset(pop, 0, sizeof(pop));
    encrypt_main();
    cal_len();
    for(int i = 0; i < all_num; i++)
    {
        pop[num].time = calculateTime(length, pop[num].sequence);
        pop[num].fitness = 1 / (double)time;
    }
}

void cal_len()
{
    int len = 0;
    for(int i = 0; i < jobNum; i++) len += jobs[i].n;
    length = len;
}

void generate()
{
    for(int i = 0; i < 100; i++)
    {
        cross();
        select();
        int n = all_num / 5;
        for(int j = 0; j < n; i++)
        {
            scrand(time(NULL));
            int num = rand() / all_num;
            mutate(num);
        }
        cal_p();
        die();
    }
}
