#pragma once
        /*工具函数库*/
//（一）数据处理
// (1)归并排序
int* merge(int a[], int b[])
{
    int* pa, * pb, * m, n;
    m = (int*)malloc((a[0] + b[0] + 1) * sizeof(int));
    if (m == NULL)
    {
        perror("Error:");
        return NULL;
    }
    m[0] = a[0] + b[0];
    pa = a + 1; pb = b + 1;
    int n1 = 1, n2 = 1;
    for (n = 1; n <= (a[0] + b[0]); n++)
    {
        if ((*pa < *pb && n1 <= a[0]) || n2 > b[0])
        {
            m[n] = *pa;
            pa++;
            n1++;
        }
        else if ((*pa >= *pb && n2 <= b[0]) || n1 > a[0])
        {
            m[n] = *pb;
            pb++;
            n2++;
        }
    }
    free(a); a = NULL;
    free(b); b = NULL;
    return m;
}
int* divide(int r[])
{
    if (r[0] == 1) return r;
    int a, b, i;
    a = r[0] / 2; b = r[0] - a;
    int* pa; pa = (int*)malloc((a + 1) * sizeof(int));
    int* pb; pb = (int*)malloc((b + 1) * sizeof(int));
    pa[0] = a;
    pb[0] = b;
    if (r[0] > 1)
    {
        for (i = 1; i <= r[0]; i++)
        {
            if (i <= a) pa[i] = r[i];
            if (i > a)  pb[i - a] = r[i];
        }
    }
    free(r); r = NULL;
    if (a > 1) pa = divide(pa);
    if (b > 1) pb = divide(pb);
    return merge(pa, pb);
}
int* merge_sort(int r[], char d[][10]) //记得r[0]是长度！
{
    int* pr;
    pr = divide(r);
    return pr;
}
//(2)值的比较
int maxinum(int a, int b)
{
    return (a > b) ? a : b;
}
int mininum(int a, int b)
{
    return (a < b) ? a : b;
}
//(二)函数功能相关
//（1）文件操作
//      i.文件链接
void file_connect(FILE* s, FILE* t) //s:source t:target
{
    rewind(s); fseek(t, 0L, SEEK_END);
    char tmp;
    tmp = fgetc(s);
    while (tmp != EOF)
    {
        fputc(tmp, t);
        tmp = fgetc(s);
    }
    rewind(s);
    rewind(t);
}
//       ii.文件打印到屏幕
void file_print(char *p)
{
    FILE* fp = fopen(p, "r");
    char buf = fgetc(fp);
    while (buf != EOF)
    {
        putchar(buf);
        buf = fgetc(fp);
    }
    fclose(fp);
}
//(2)等待后清屏函数
void wait()
{
    system("pause");
    system("cls");
    rewind(stdin);
}
//(3)获取当前本地日期并以date结构体类型返回
void get_time(date* today)
{
    struct tm* p;
    time_t t;
    t = time(NULL);
    p = localtime(&t);
    (*today).y = (*p).tm_year+1900;
    (*today).m = (*p).tm_mon+1;
    (*today).d = (*p).tm_mday;
}
//(4)从完整DNA序列信息中提取所需的索引信息
void indexualize(gene* load,index* get)
{
    (*get).id = (*load).id;
    strcpy((*get).ID, (*load).ID);
    strcpy((*get).ins, (*load).ins);
    strcpy((*get).locale, (*load).locale);
    strcpy((*get).name, (*load).name);
    strcpy((*get).source, (*load).source);
    strcpy((*get).tech, (*load).tech);
    strcpy((*get).type, (*load).type);
}
//(5)屏幕输出所有在库的基因序列
void print_roster()
{
    int i;
    printf("———————————————————————————————————————————————————\n");
    printf("当前在库序列个数：%d\n", sum_roster);
    printf("———————————————————————————————————————————————————\n");
    printf("Num    ID              Definition\n");
    for (i = 1; i <= sum_roster; i++)
    {
        printf("%06d %-15s %-100s\n", roster[i].id, roster[i].ID, roster[i].name);
    }
    printf("———————————————————————————————————————————————————\n");
}
//（三）字符串处理
// (1)大小写转换
char lower(char a)
{
    if (a >= 'A' && a <= 'Z') return a + 32;
    else return a;
}
char upper(char a)
{
    if (a >= 'a' && a <= 'z') return (char)(a - 32);
    else return a;
}
//（2）将字符串中字母全部变为小写
char* strlower(char* str)
{
    char* origin = str;
    for (; *str != '\0'; str++)
        *str = lower(*str);
    return origin;
}