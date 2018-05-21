#include "../../include/jobshop.h"
void die()
{
    if (all_num <= MAX_POP)
        return;
    while (all_num > MAX_POP)
    {
        unsigned long long r = rand() * rand();
        int x = r % all_num;
        int px = 10000 * pop[x].live_p;
        r = rand() * rand();
        int y = r % 10000;
        if (y > px)
        {
            pop[x].alive = 0;
            all_num--;
        }
    }
}
void replace()
{
    int fron = 0, rear = x_all - 1;
    while (fron < rear)
    {
        while (fron < rear && pop[fron].alive == 1)
            fron++;
        while (fron < rear && pop[rear].alive == 0)
            rear--;
        pop[fron] = pop[rear];
        pop[rear].alive = 0;
    }
}
