#define _CRT_SECURE_NO_WARNINGS
typedef int bool;
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "toolspack.h"
#include "load_gene.h"
#include "cut_check.h"
#include "translate.h"
#include "LCS.h"
int main()
{
    printf("警告！该程序尚在施工中，请佩戴安全帽:)\n\n");
    const char* p=NULL;
    gene covid;
    p = "genomic.txt";
    covid = load_gene(p);
    cut_check(covid);
    translate(covid);
    
    p = "SARS.txt";
    gene SARS;
    SARS = load_gene(p);
    cut_check(SARS);
    translate(SARS);
    p = "test1.txt";
    gene test1, test2;
    test1 = load_gene(p);
    p = "test2.txt";
    test2 = load_gene(p);
    LCS(covid, SARS);
    system("pause");
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
