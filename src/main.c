/*
@file:main.c 
@author:Group All
@version:1.4
@date:21/5/18
@description:
    The main function, provide the interface to read arguments from console
*/
#include "../include/jobshop.h"
#include <getopt.h>

int main(int argc, char *argv[])
{
    int opt;
    int inputFlag = 0;
    bool fileFlag = false;
    char *sourcePath;
    bool configFile = false;
    bool outputFileFlag = false;
    char *outputPath;
    FILE *config;
    while ((opt = getopt(argc, argv, "f:C:g:m:i:p:d:c:ho:")) != -1)
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
        case 'o':
            outputFileFlag = true;
            outputPath = (char *)malloc(sizeof(char) * strlen(optarg));
            strcpy(outputPath, optarg);
            break;
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
    FILE *fPtr;
    if (outputFileFlag)
        fPtr = fopen(outputPath, "w");
    begin = clock();
    init();
    generate();
    gene finalSeq = out();
    if (outputFileFlag)
    {
        outputFile(length, finalSeq.sequence, fPtr);
    }
    else
    {
        output(length, finalSeq.sequence);
        printf("%d\n", finalSeq.time);
    }
    end = clock();
    cost = (double)(end - begin) / CLOCKS_PER_SEC;
    if (outputFileFlag)
    {
        fprintf(fPtr, "Time Used: %.3lf\r\n", cost);
        fprintf(fPtr, "Ended Time: %d\r\n", finalSeq.time);
        fclose(fPtr);
        printf("The result has been written to %s.\n", outputPath);
    }
    else{
        printf("Time Used: %lf\n", cost);
        printf("Ended Time: %d\n", finalSeq.time);
    }
    return 0;
}
