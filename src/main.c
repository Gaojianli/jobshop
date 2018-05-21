#include "../include/jobshop.h"
#include <getopt.h>
int main(int argc, char *argv[])
{
    int opt;
    int inputFlag = 0;
    bool fileFlag = false;
    char *sourcePath;
    bool configFile = false;
    FILE *config;
    while ((opt = getopt(argc, argv, "f:C:g:m:i:p:d:c:h")) != -1)
    {
        switch (opt)
        {
        case 'f':
            fileFlag = true;
            sourcePath = (char *)calloc(sizeof(char), strlen(optarg));
            strcpy(sourcePath, optarg);
            break;
        case 'C':
            config = fopen(optarg, "r");
            fscanf(config, "%d%lf%d%d%lf%lf", &GAP, &GER_MUL, &ENCRYPT_NUM, &MAX_POP, &DIE_RATIO, &MUT_MUL);
            fclose(config);
            configFile = true;
            break;
        case 'g':
            if (configFile)
            {
                printf("Config file detected, ignore the option \"- %c\"", opt);
                break;
            }
            sscanf(optarg, "%d", &GAP);
            inputFlag++;
            break;
        case 'm':
            if (configFile)
            {
                printf("Config file detected, ignore the option \"- %c\"", opt);
                break;
            }
            sscanf(optarg, "%lf", &GER_MUL);
            inputFlag++;
            break;
        case 'i':
            if (configFile)
            {
                printf("Config file detected, ignore the option \"- %c\"", opt);
                break;
            }
            sscanf(optarg, "%d", &ENCRYPT_NUM);
            inputFlag++;
            break;
        case 'p':
            if (configFile)
            {
                printf("Config file detected, ignore the option \"- %c\"", opt);
                break;
            }
            sscanf(optarg, "%d", &MAX_POP);
            inputFlag++;
            break;
        case 'd':
            if (configFile)
            {
                printf("Config file detected, ignore the option \"- %c\"", opt);
                break;
            }
            sscanf(optarg, "%lf", &DIE_RATIO);
            inputFlag++;
            break;
        case 'c':
            if (configFile)
            {
                printf("Config file detected, ignore the option \"- %c\"", opt);
                break;
            }
            sscanf(optarg, "%lf", &MUT_MUL);
            inputFlag++;
            break;
        case 'h':
            if (configFile)
            {
                printf("Config file detected, ignore the option \"- %c\"", opt);
                break;
            }
            printUsage();
            exit(0);
        default:
            printUsage();
            exit(-1);
            break;
        }
    }
    if (!configFile)
    {
        if (inputFlag == 6)
            if (fileFlag)
                input_file(sourcePath);
            else
                input_console();
        else
        {
            printf("Missing argument!\n");
            printUsage();
            exit(-1);
        }
    }
    else
    {
        if (fileFlag)
            input_file(sourcePath);
        else
            input_console();
    }
    double cost;
    clock_t begin, end;
    begin = clock();
    init();
    generate();
    output(length, out().sequence);
    printf("%d\n", out().time);
    end = clock();
    cost = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%lf\n", cost);
    return 0;
}
