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
    system("mode con cols=128 lines=45"); //初始化界面大小为长128，宽45
    initialize(); //程序初始化
    main_menu();  //加载菜单
    return 0;
}
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