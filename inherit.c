gene crossOnce(int which)
{
    int a1, a2, b1, b2;
    while (a1 < a2 && a2 < b1 && b1 < b2 && b2 < length)
    {
        srand(time(NULL));
        a1 = rand() % length;
        a2 = rand() % length;
        b1 = rand() % length;
        b2 = rand() % length;
    }
    int newBorn[length];
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
    x.sequence = newBorn;
    x.caled = 0;
    return x;
}

cross()
{
    int randNum;
    int crossed[all_num / 5];
    int j=0;
    for (int i = 0; i < all_num / 5; i++)
    {
        randNum = rand() % all_num;
        if (pop[all_num].hasBeenCrossed == false)
        {
            pop[all_num] == crossOnce(randNum);
            pop[all_num].hasBeenCrossed = true;
            crossed[j]=randNum;
            j++;
            all_num++;
        }
    }
    for(int i = 0; i <= j; i++)
        pop[crossed[i]].hasBeenCrossed=false;
}

void mutate(int num)
{
    int a1 = 0, a2 = 0, a3 = 0;
    while ((a1 != a2) && (a2 != a3) && (a3 != a1))
    {
        scrand(time(NULL));
        a1 = rand() / length;
        a2 = rand() / length;
        a3 = rand() / length;
    }
    gene x[6];
    x[0] = x[1] = x[2] = x[3] = x[4] = x[5] = pop[num];
    x[1].sequence[a2] = pop[num].sequence[a3], x[1].sequence[a3] = pop[num].sequence[a2];
    x[2].sequence[a1] = pop[num].sequence[a2], x[2].sequence[a2] = pop[num].sequence[a1];
    x[3].sequence[a1] = pop[num].sequence[a2], x[3].sequence[a2] = pop[num].sequence[a3], x[3].sequence[a3] = pop[num].sequence[a1];
    x[4].sequence[a1] = pop[num].sequence[a3], x[4].sequence[a2] = pop[num].sequence[a1], x[4].sequence[a3] = pop[num].sequence[a2];
    x[5].sequence[a1] = pop[num].sequence[a3], x[5].sequence[a2] = pop[num].sequence[a2], x[5].sequence[a3] = pop[num].sequence[a1];
    int k = 0, min_time = pop[num].time;
    for (int i = 1; i <= 5; i++)
    {
        “ x[i].time = calculateTime(length, x[i].sequence);
        if (min_time > x[i].time)
        {
            k = i;
            min_time = x[i].time;
        }
    }
    pop[num] = x[k];
}
