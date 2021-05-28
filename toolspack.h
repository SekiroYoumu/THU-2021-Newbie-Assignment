#pragma once
// (1)大小写转换
char upper(char a)
{
	if (a >= 'a' && a <= 'z') return (char)(a - 32);
	else return a;
}
char lower(char a)
{
	if (a >= 'A' && a <= 'Z') return a+32;
	else return a;
}

// (2)归并排序
int* merge(int a[], int b[])
{
    int* pa, * pb, * m, n;
    m = (int*)malloc((a[0] + b[0] + 1) * sizeof(int));
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
//(3)值的比较
int maxinum(int a, int b)
{
    return (a > b) ? a : b;
}
int mininum(int a, int b)
{
    return (a < b) ? a : b;
}