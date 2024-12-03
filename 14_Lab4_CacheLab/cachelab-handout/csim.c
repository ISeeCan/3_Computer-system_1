

#include "cachelab.h"
//#include "cachelab.c"     //如果你要make，就把这个注释掉
#include <stdio.h>
#include <getopt.h>
//#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct
{
    int valid;
    int whichline;
    int lastvisittime;
} eachline;
typedef eachline* eachset;
typedef eachset* mycache;       //模仿多维数组的形式表达cache
// struct mycache
// { 
//     int linecount;
//     int setcount;
// };

unsigned hit=0,miss=0,evict=0;
int sbits=0, bbits=0;
int alls=0,alllines=0,eachslines=0,eachbsize=0;
int needhelp=0,needvisual=0;
char filePath[20] = {0};
mycache cache;

void helpme()           //用户说：这咋用啊
{
    printf("Hi there, this is help file:\n");
    printf("Usage: ./csim-ref [-hv] -s <s> -E <E> -b <b> -t <tracefile>\n");
    printf("• -h: Optional help flag that prints usage info\n");
    printf("• -v: Optional verbose flag that displays trace info\n");
    printf("• -s <s>: Number of set index bits (S = 2s\n");
    printf("is the number of sets)\n");
    printf("• -E <E>: Associativity (number of lines per set)\n");
    printf("• -b <b>: Number of block bits (B = 2b is the block size)\n");
    printf("• -t <tracefile>: Name of the valgrind trace to replay\n");
    exit(0);
}

void dealwithinput(int argc, char* const* argv)    //处理命令行输入
{
    int opt;
    while ((opt = getopt(argc, argv, "s:E:b:t:vh")) != -1) 
    {
        switch (opt) {
            case 's':
                sbits = atoi(optarg);
                alls = 1 << sbits;
                break;
            case 'E':
                eachslines = atoi(optarg);
                break;
            case 'b':
                bbits = atoi(optarg);
                eachbsize = 1 << bbits;
                break;
            case 't':
                strcpy(filePath, optarg);
                break;
            case 'v':
                needvisual = 1;
                break;
            case 'h':
                needhelp = 1;
                break;
        }
    }
    alllines =  eachslines;
    //printf("SS,EE,B %d,%d,%d",alls,alllines,bbits);

    if((!sbits || !alllines || !bbits || !filePath[1]) && needhelp == 0)
    {
        printf("Sorry, you have a wrong input format.(dealwithinput-ZeroError)\n");
        exit(1);
    }
    if(needhelp == 1)
    {
        helpme();
        exit(0);
    }
};

void newCache()         //初始化
{
    cache = (mycache)malloc(alls * sizeof(eachset));
    assert(cache);
    for (int i = 0; i < alls; ++i) {
        cache[i] = (eachset)malloc(alllines * sizeof(eachline));
        assert(cache[i]);
        memset(cache[i], 0, sizeof(eachline) * alllines);
    }
}

void deleteCache()      //析构
{
    for (int i = 0; i < alls; ++i) 
    {
        free(cache[i]);
    }
    free(cache);
}

void findanddo(long long where)        //寻找访问位置并进行操作
{
    int tag = where >> (bbits + sbits);
    unsigned long long mask = ((1ULL << 63) - 1) >> (63 - sbits);
    eachset cacheSet = cache[(where >> bbits) & mask];

    // 缓存击中
    for (int i = 0; i < alllines; ++i) 
    {
        if (cacheSet[i].valid && cacheSet[i].whichline == tag) 
        {
            hit++;
            cacheSet[i].lastvisittime = 0;
            if(needvisual == 1)
                printf(" hit");
            return;
        }
    }

    //未命中
    miss++;
    if(needvisual == 1)
        printf(" miss");
        // 有空位，直接写入
    for (int i = 0; i < alllines; ++i) 
    {
        //printf(" valid is [%d]",cacheSet[i].valid);
        if (!cacheSet[i].valid) 
        {
            cacheSet[i].valid = 1;
            cacheSet[i].whichline = tag;
            cacheSet[i].lastvisittime = 0;
            return;
        }
    }

    // 进行替换
    evict++;
    int evictIndex = 0;
    int maxTime = 0;
    for (int i = 0; i < alllines; ++i) 
    {
        if (cacheSet[i].lastvisittime > maxTime) 
        {
            maxTime = cacheSet[i].lastvisittime;
            evictIndex = i;
            if(needvisual == 1)
                printf(" eviction");
        }
    }

    cacheSet[evictIndex].whichline = tag;
    cacheSet[evictIndex].lastvisittime = 0;
}

void updatetime()       //整体更新时间
{
    for (int i = 0; i < alls; ++i) 
    {
        for (int j = 0; j < alllines; ++j) 
        {
            if (cache[i][j].valid) 
            {
                cache[i][j].lastvisittime++;
            }
        }
    }
}

void handling()         //根据文件进行模拟
{
    FILE* file = fopen(filePath,"r");
    assert(file);   //检查
    long long where;
    char what;
    int size;
    while (fscanf(file, " %c %I64x,%d", &what, &where, &size) > 0) 
    {
        if(needvisual == 1)
        {
            printf("%c %I64x,%d",what, where, size);
        }

        switch (what) 
        {
            case 'I':       //啥也不干
                continue;   
            case 'M':       //干两次    数据修改
                findanddo(where);
            case 'L':       //只干一次  数据加载
            case 'S':       //只干一次  数据存储
                findanddo(where);
                break;
        }
        updatetime();

        if(needvisual == 1)
            printf("\n");
    }
    fclose(file);
}



int main(int argc,char* argv[])
{
    dealwithinput(argc,argv);
    newCache();
    
    handling();
    printSummary(hit, miss, evict);
    deleteCache();

    return 0;
}
