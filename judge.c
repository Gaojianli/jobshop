#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jobShop.h"

/*
struct job {
    int n;
    int time[MAX_NUM];
    int mac[MAX_NUM];
} jobs[MAX_NUM];

int jobNum;
int macNum;
*/

void calculateID(int **id, int *t) {
    int i, j;
    int cnt = 1;
    for (i = 0; i < jobNum; i++) {
        for (j = 0; j < jobs[i].n; j++) {
            id[i][j] = cnt;
            t[cnt] = jobs[i].time[j];
            cnt++;
        }
    }
    t[0] = 0;
}

int findPath(int **map, int *outDegree, int *maxTime, int *t, int u) {
    if (maxTime[u] != 0) return maxTime[u];
    maxTime[u] = t[u];
    int i;
    for (i = 0; i < outDegree[u]; i++) {
        int v = map[u][i];
        int suffix = findPath(map, outDegree, maxTime, t, v);
        if (maxTime[u] < suffix + t[u]) 
            maxTime[u] = suffix + t[u];
    } 
    return maxTime[u];
}

int calculateTime(int n, int *_gene) {
    int *outDegree = (int*)malloc(MAX_LEN * sizeof(int));
    int i, j;
    int **id = (int**)malloc(MAX_NUM * sizeof(int*));
    for (i = 0; i < MAX_NUM; i++) {
    	id[i] = (int*)malloc(MAX_NUM * sizeof(int));
	}
    int **map = (int**)malloc(MAX_LEN * sizeof(int*));
    for (i = 0; i < MAX_LEN; i++) {
    	map[i] = (int*)malloc(MAX_LEN * sizeof(int));
	}
    int *maxTime = (int*)malloc(MAX_LEN * sizeof(int));
    int *jobDone = (int*)malloc(MAX_NUM * sizeof(int));
    int *lastOpe = (int*)malloc(MAX_NUM * sizeof(int));
    int *t = (int*)malloc(MAX_LEN * MAX_LEN * sizeof(int));

    memset(jobDone, 0, sizeof(jobDone));
    memset(maxTime, 0, sizeof(maxTime));
    memset(outDegree, 0, sizeof(outDegree));
    memset(lastOpe, 0, sizeof(lastOpe));
    
    for (i = 0; i < MAX_NUM; i++) {
    	jobDone[i] = 0;
    	lastOpe[i] = 0;
    	for (j = 0; j < MAX_NUM; j++) {
    		id[i][j] = 0;
		}
	}
	
	for (i = 0; i < MAX_LEN; i++) {
		maxTime[i] = 0;
	}

    calculateID(id, t);

    for (i = 0; i < jobNum; i++) {
        map[0][i] = id[i][0];
        outDegree[0]++;
        for (j = 1; j < jobs[i].n; j++) {
            int num = outDegree[id[i][j - 1]];
            outDegree[id[i][j - 1]]++;
            map[id[i][j - 1]][num] = id[i][j];
        }
    }

    for (i = 0; i < n; i++) {
        int num = jobDone[_gene[i]];
        int mac_1 = jobs[_gene[i]].mac[num];
        jobDone[_gene[i]]++;
        if (lastOpe[mac_1] == 0) {
            lastOpe[mac_1] = id[_gene[i]][num];
            continue;
        }
        int out = outDegree[lastOpe[mac_1]];
        map[lastOpe[mac_1]][out] = id[_gene[i]][num];
        outDegree[lastOpe[mac_1]]++;
        lastOpe[mac_1] = id[_gene[i]][num];
    }

    findPath(map, outDegree, maxTime, t, 0);
    int res = maxTime;
	free(maxTime);
	free(jobDone);
	free(lastOpe);
	free(outdegree);
	for (i = 0; i < MAX_LEN) free(map[i]);
	free(map);
	for (i = 0; i < MAX_NUM; i++) free(id[i]);
	free(id);
    return maxTime[0];
}

/*
void input(struct job *jobs) {
    scanf("%d%d", &jobNum, &macNum);
    int i, j;
    
    for (i = 0; i < jobNum; i++) {
        jobs[i].n = 0;
    }
	getchar();
    char buf[100];
    for (i = 0; i < jobNum; i++) {
        gets(buf);
        j = 1;
        int id = i;
        int cnt = 0;
        int num = 0;
        while (buf[j] != '\0') {
            j += 2;
            jobs[id].n++;
            
            num = 0;
            while (buf[j] >= '0' && buf[j] <= '9') {
            	num = num * 10 + buf[j] - '0';
            	j++;
			}       	
            jobs[id].time[cnt] = num;
            
            j++;
            
            num = 0;
            while (buf[j] >= '0' && buf[j] <= '9') {
            	num = num * 10 + buf[j] - '0';
            	j++;
			} 
            jobs[id].mac[cnt] = num;
            cnt++;
            j++;
        }
    }
    gets(buf);
}
*/
/*
int main() {
	input(jobs);
	int _gene[7] = {1, 3, 1, 2, 2, 1, 3};
	int res = calculateTime(7, _gene);
	printf("%d\n", res);
	return 0;
}
*/
