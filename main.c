#define _CRT_SECURE_NO_WARNINGS
typedef int bool;
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "struct_definition.h"
#include "toolspack.h"
#include "user_management.h"
#include "Initialization.h"
#include "load_gene.h"
#include "load_from_base.h"
#include "cut_check.h"
#include "translate.h"
#include "LCS.h"
#include "SES.h"
#include "search_from_roster.h"
#include "user_menu.h"
int main()
{   
    system("mode con cols=128 lines=45"); //初始化界面大小为长128，宽45！
    initialize(); //程序初始化
    main_menu();  //加载菜单
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

/*版本更新日志*/
// 21.5.21 v0.50 主要算法函数完工。
// 21.5.26 v0.90 账号管理系统完工并通过测试。
// 21.5.27 v1.00 函数接口完工，将所有函数的接口修改成整型数“唯一id”。
// 21.5.27 v1.10 完整的平台架构建成。
// 21.5.27 v1.20 修复了基因名中包含“\”或“/”等Windows创建文件不支持的符号导致的bug。根据现实基因信息加长乐基因信息结构体的存储空间。第一次Release。
// 21.5.28 v1.30 大幅优化界面显示效果与内容，解决未清空缓冲区导致的菜单选择出错问题。增加了几个菜单的返回上级菜单方式。增加了进入程序时可选的低权限访客模式。
// 21.5.28 v1.31 添加了第一部分的代码注释。添加了程序图标（by Sirius_Neo，特此致谢)。
// 21.5.28 v1.32 全部代码注释初步加注完成。做了一些可能无法被察觉的优化与修复。第二次Release与小范围测试（炸酒馆）。
// 21.5.29 v1.33 源代码一度因未知原因丢失，后通过回滚找回。将工程上传了Github。修改了主菜单界面的按钮顺序。添加了格式化上传基因文件时的格式验证。


/*以下为调试期的调试代码，已无法重新启用，若需启用请根据现有参数传递格式进行修改*/
/*  //printf("\nChoose your language: \n1、中国语\n2、Simplified Chinese\n3、简体中文\n");
    gene covid;
    p = "genomic.txt";
    covid = load_gene(p,0);  
    cut_check(covid);
    translate(covid); //COVID-19 data loaded and tested
    p = "SARS.txt";
    gene SARS;
    SARS = load_gene(p,0);
    cut_check(SARS);
    translate(SARS);//SARS data loaded and tested
    
    //SES(covid, SARS,0);
    p = "test1.txt";
    gene test1, test2;
    test1 = load_gene(p,0);
    p = "test2.txt";
    test2 = load_gene(p,0); //selfmade test data loaded
    
    SES(test1, test2,0);
    max_similarity(3);
    load_from_base(1,0);
    //search();
    load_gene(NULL, 0);
    load_from_base(0,0);
     password_change();
    auth_change();
        load_gene("1 (1).txt", 0);
    load_gene("1 (2).txt", 0);
    load_gene("1 (3).txt", 0);
    load_gene("1 (4).txt", 0);
    load_gene("1 (5).txt", 0);
    load_gene("1 (6).txt", 0);
    load_gene("1 (7).txt", 0);
    load_gene("1 (8).txt", 0);
    load_gene("1 (9).txt", 0);
    load_gene("1 (10).txt", 0);*/