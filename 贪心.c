#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEN 150  
#define MAX_NUM 25
#define inf 0x3f3f3f3f 

struct job {
    int n;
    int time[MAX_NUM];
    int mac[MAX_NUM];
} jobs[MAX_NUM];

struct block {
	int start;
	int end;
	int jobRec;
	int opeRec;
} blocks[MAX_NUM][MAX_NUM];

int jobNum;
int macNum;

void greed(int *sequence, int *result, int *gapNum, 
            int **start, int **end, int *lastTime, int *final) {
    int i, j, k;
    int maxTime = 0;

    for (i = 0; i < MAX_NUM; i++) {
    	gapNum[i] = 0;
    	lastTime[i] = 0;
    	for (j = 0; j < MAX_NUM; j++) {
    		start[i][j] = end[i][j] = 0;
		}
	} 

    for (i = 0; i < jobNum; i++) {
        int last = 0;
        int tm;
        int startTime, endTime;
        for (j = 0; j < jobs[sequence[i]].n; j++) {
            int mac = jobs[sequence[i]].mac[j];
            int flag = 0;
            tm = jobs[sequence[i]].time[j];
            for (k = 0; k < gapNum[mac]; k++) {
                if (flag) break;
                if (end[mac][k] - last < tm) continue;
                if (end[mac][k] - start[mac][k] < tm) continue;
                flag = 1;

                if (last >= start[mac][k]) startTime = last;
                else startTime = start[mac][k];
				int temp = end[mac][k];
                end[mac][k] = startTime;
                endTime = tm + startTime;

                int l;
                for (l = gapNum[mac]; l > k + 1; l--) {
                    start[mac][l] = start[mac][l - 1];
                    end[mac][l] = end[mac][l - 1];
                }
                start[mac][k + 1] = endTime;
				end[mac][k + 1] = temp;
                gapNum[mac]++; 
                last = start[mac][k + 1];
            }
            if (!flag) {
                if (lastTime[mac] < last) {
                    
                    end[mac][gapNum[mac]] = last;
                    start[mac][gapNum[mac]] = lastTime[mac];
                    lastTime[mac] = last + tm;
                    last += tm;
                    if (lastTime[mac] > maxTime) maxTime = lastTime[mac];
                    gapNum[mac]++;
                    continue;
                }
                lastTime[mac] += tm;
                last = lastTime[mac];
                if (lastTime[mac] > maxTime) maxTime = lastTime[mac];
            }
        }       
    } 
    if (maxTime < *result) {
    	*result = maxTime;
    	for (i = 0; i < jobNum; i++) final[i] = sequence[i];
	} 
}


int initSequence(int *sequence, int maxn) {
    int i; 
	for (i = maxn + 1; i < jobNum; i++) sequence[i] = i;
}

void perm(int *seq, int *result, int *occ, int cur, int maxn, int *gapNum, 
            int *lastTime, int **start, int **end, int *final) {
    if (cur == maxn) {
        initSequence(seq, maxn);
        greed(seq, result, gapNum, start, end, lastTime, final);
    }
    int i;
    for (i = 0; i < maxn; i++) {
        if (occ[i]) continue;
        seq[cur] = i;
        occ[i] = 1;
        perm(seq, result, occ, cur + 1, maxn, gapNum, lastTime, start, end, final);
        occ[i] = 0;
    }
}


int work(int *final) {
	int i;
    int *sequence = (int*)malloc(MAX_NUM * sizeof(int));
    int *gapNum = (int*)malloc(MAX_NUM * sizeof(int));
    int *lastTime = (int*)malloc((MAX_NUM + 1) * sizeof(int));
    int **start = (int**)malloc((MAX_NUM + 1) * sizeof(int*));
    for (i = 0; i <= MAX_NUM; i++) {
    	start[i] = (int*)malloc(MAX_NUM * sizeof(int));
	}
    int **end = (int**)malloc(MAX_NUM * sizeof(int*));
    for (i = 0; i <= MAX_NUM; i++) {
    	end[i] = (int*)malloc(MAX_NUM * sizeof(int));
	}
    int *occ = (int*)malloc(MAX_NUM * sizeof(int));
    int answer = inf;
    int *result = &answer;

    int maxn = 0;
    if (jobNum < 9) maxn = jobNum;
    else maxn = 9;

    perm(sequence, result, occ, 0, maxn, gapNum, lastTime, start, end, final);
    free(sequence);    
    for (i = 0; i < MAX_NUM; i++) {
    	free(start[i]);
    	free(end[i]);
	}
	free(start);
	free(end);
	free(occ);
	free(gapNum);
	free(lastTime);
    return answer;
}

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

void in(struct job *jobs) {
	scanf("%d%d", &jobNum, &macNum);
    int i, j;
    for (i = 0; i < jobNum; i++) jobs[i].n = macNum;
    for (i = 0; i < jobNum; i++) {
    	for (j = 0; j < macNum; j++) {
    		scanf("%d", &jobs[i].time[j]);
		}
	}
	for (i = 0; i < jobNum; i++) {
    	for (j = 0; j < macNum; j++) {
    		scanf("%d", &jobs[i].mac[j]);
		}
	}
	return;
}

void output(int *final) {
	int i, j, k;
    int *gapNum = (int*)malloc(MAX_NUM * sizeof(int));
    int *lastTime = (int*)malloc((MAX_NUM + 1) * sizeof(int));
    int **start = (int**)malloc((MAX_NUM + 1) * sizeof(int*));
    for (i = 0; i <= MAX_NUM; i++) {
    	start[i] = (int*)malloc(MAX_NUM * sizeof(int));
	}
    int **end = (int**)malloc(MAX_NUM * sizeof(int*));
    for (i = 0; i <= MAX_NUM; i++) {
    	end[i] = (int*)malloc(MAX_NUM * sizeof(int));
	}
	int **ostart = (int**)malloc(MAX_NUM * sizeof(int*));
	for (i = 0; i < MAX_NUM; i++) {
		ostart[i] = (int*)malloc(MAX_NUM * sizeof(int));
	}
	int **oend = (int**)malloc(MAX_NUM * sizeof(int*));
	for (i = 0; i < MAX_NUM; i++) {
		oend[i] = (int*)malloc(MAX_NUM * sizeof(int));
	}
	int *onum = (int*)malloc(MAX_NUM * sizeof(int));

	
	for (i = 0; i < MAX_NUM; i++) {
    	gapNum[i] = 0;
    	lastTime[i] = 0;
    	onum[i] = 0;
    	for (j = 0; j < MAX_NUM; j++) {
    		start[i][j] = end[i][j] = 0;
		}
	} 

    for (i = 0; i < jobNum; i++) {
        int last = 0;
        int tm;
        int startTime, endTime;
        int temp;
        int l;
        for (j = 0; j < jobs[final[i]].n; j++) {
            int mac = jobs[final[i]].mac[j];
            int flag = 0;
            tm = jobs[final[i]].time[j];
            for (k = 0; k < gapNum[mac]; k++) {
                if (flag) break;
                if (end[mac][k] - last < tm) continue;
                if (end[mac][k] - start[mac][k] < tm) continue;
                flag = 1;
				
				for (l = 0; l < onum[mac]; l++) {
					if (blocks[mac][l].start >= end[mac][k]) break;
				}
				
				temp = l;
				
				for (l = onum[mac]; l > temp; l--) {
					blocks[mac][l].start = blocks[mac][l - 1].start;
					blocks[mac][l].end = blocks[mac][l - 1].end;
                    blocks[mac][l].jobRec = blocks[mac][l - 1].jobRec;
                    blocks[mac][l].opeRec = blocks[mac][l - 1].opeRec;
				}
				
                if (last >= start[mac][k]) {
                	startTime = last;
                	blocks[mac][temp].start = last;
                	blocks[mac][temp].end = last + tm;
                    blocks[mac][temp].jobRec = final[i];
                    blocks[mac][temp].opeRec = j;
				}
                else {
                	startTime = start[mac][k];
                	blocks[mac][temp].start = startTime;
                	blocks[mac][temp].end = startTime + tm;
                    blocks[mac][temp].jobRec = final[i];
                    blocks[mac][temp].opeRec = j;

				}
				temp = end[mac][k];
                end[mac][k] = startTime;
                endTime = tm + startTime;

                
                for (l = gapNum[mac]; l > k + 1; l--) {
                    start[mac][l] = start[mac][l - 1];
                    end[mac][l] = end[mac][l - 1];
                }
                start[mac][k + 1] = endTime;
				end[mac][k + 1] = temp;
                gapNum[mac]++; 
                onum[mac]++;
                last = start[mac][k + 1];
            }
            if (!flag) {
                if (lastTime[mac] < last) {
                    blocks[mac][onum[mac]].start = last;
                    blocks[mac][onum[mac]].end = last + tm;
                    blocks[mac][onum[mac]].jobRec = final[i];
                    blocks[mac][onum[mac]].opeRec = j;
                    onum[mac]++;
                    end[mac][gapNum[mac]] = last;
                    start[mac][gapNum[mac]] = lastTime[mac];
                    lastTime[mac] = last + tm;
                    last += tm;
                    gapNum[mac]++;
                    continue;
                }

                blocks[mac][onum[mac]].start = lastTime[mac];
                blocks[mac][onum[mac]].end = lastTime[mac] + tm;
                blocks[mac][onum[mac]].jobRec = final[i];
                blocks[mac][onum[mac]].opeRec = j;
                onum[mac]++;
                lastTime[mac] += tm;
                last = lastTime[mac];
            }
        }       
    }
	for (i = 1; i <= macNum; i++) {
		printf("M%d", i);
		for (j = 0; j < onum[i]; j++) {
			if (blocks[i][j].start == blocks[i][j].end) continue;
			printf(" (%d,%d-%d,%d)", blocks[i][j].start, blocks[i][j].jobRec + 1, blocks[i][j].opeRec + 1, blocks[i][j].end);
		}
        printf("\n");
	}
}

int main() {
    in(jobs);
    clock_t start, finish;
    start = clock();
    int *final = (int*)malloc(MAX_NUM * sizeof(int));
    int out = work(final);
    int i;
    finish = clock();
	output(final);
	printf("End %d\n", out);
	printf("Running Time: %.2lf s", (double)(finish - start) / CLOCKS_PER_SEC);
    return 0;
}
