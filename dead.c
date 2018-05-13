void select()
{
    if(all_num < 1000) return;
    gene bestPar = sBest(0), bestChi = sBest(1);
    if(bestPar.time < bestChi.time)
    {
        if(parents < all_num)
        {
            int choice;
            for(;;)
            {
                choice = rand() / all_num;
                if(choice >= parent) pop[choice] = pop[bestPar];
            }
        }
    }
}

gene sBest(int flag)
{
    gene temp;
    switch(flag)
        case 0:
        {
            temp = pop[0];
            for(int i = 1; i < parents; i++) if(pop[i].time < temp.time)
                temp = pop[i];
            return temp;
        }
        case 1:
        {
            temp = pop[parents];
            for(int i = parents; i < all_num; i++) if(pop[i].time < temp.time)
                temp = pop[i];
            return temp;
        }
        default: return;
}
