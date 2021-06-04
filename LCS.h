#pragma once
/*计算最长公共子序列的长度与序列本身；可供用户直接调用，或作为SES与相似度检查的前置函数*/
seq_len LCS(int id1, int id2,int t)
//t=0代表用户调用SES或LCS，则输出LCS文件；t=1代表用户调用求最相近基因组函数，不输出LCS文件。
{
	gene t1 = load_from_base(id1, 1);
	gene t2 = load_from_base(id2, 1);
	if(t==0) printf("\n------LCS获取中，请稍候片刻……------\n");
	int y,x,i,sum;
	int n[2] = {t1.l,t2.l};
	int** p = NULL;
	char* lcs = NULL;
	bool flag=0;
	/*Part.1 LCS的动态规划算法需要开辟一个(n[0]+1)*(n[1]+1)大小的空间*/
	/*P.S.:实测在长度如此之长的情况下会占用大量内存（3.5G）左右，并需要一定的计算时间*/
	/*为尽可能减少内存使用，计划采用二级指针+动态数组的方式开辟这种空间*/
	p = (int**)malloc((n[0]+1) * sizeof(int*));//第一级指针的内存空间开辟
	if (p == NULL) 	
	{
		printf("Error:Unsuccessful memory allocation for P[x] sequences!\n可能是当前空余内存空间太小……\n");
		return null_seq;
	}
	for (x = 0; x < (n[0] + 1); x++)
	{
		p[x]= (int*)malloc((n[1]+1) * sizeof(int));//第二级指针的内存空间开辟
		if (p[x] == NULL)
		{
			printf("Error:Unsuccessful memory allocation for P[x][y] sequences!\n可能是当前空余内存空间太小……\n");
			return null_seq;
		}
		p[x][0] = 0;
	}
	for (y = 0; y < (n[1] + 1); y++) p[0][y] = 0; //初始化DP问题中的0行0列
	for (x = 1; x < (n[0] + 1); x++) //行遍历
	{
		for (y = 1; y < (n[1] + 1); y++) //列遍历
		{
			flag = (t1.seq[x-1]==t2.seq[y-1]);
			switch (flag)
			{
			case 1:p[x][y] = p[x - 1][y - 1] + 1; break;
			case 0:p[x][y] = max(p[x][y - 1], p[x - 1][y]); break; //根据长度的递归表达式确定下一级长度
			}
		}
	}
	x--; y--;
	i = p[x][y];
	sum = p[x][y];
	lcs = (char*)malloc(i+1 * sizeof(char));//开辟lcs的存储空间
	if (lcs == NULL)
	{
		printf("Error:Unsuccessful memory allocation for lcs sequences!\n");
		return null_seq;
	}
	lcs[i] = '\0'; i--;//先加上字符串终止符
	while (x >= 1 && y >= 1 && i >= 0)
	{
		if (t1.seq[x-1] == t2.seq[y-1])
		{
			lcs[i] = t1.seq[x-1];
			i--;
			x--; y--;
		}
		else if (p[x - 1][y] >= p[x][y - 1])
		{
			x--;
		}
		else if (p[x - 1][y] < p[x][y - 1])
		{
			y--;
		}
	}//通过递推公式的定义反向寻找LCS字符串本身
	for (x = 0; x < n[0] + 1; x++)
	{
		free(p[x]);
		p[x] = NULL;
	}
	free(p); p = NULL; //尽早释放p二级指针占用的空间，P.S.lcs需要返回后续函数使用，故无法释放
	if (t == 0)
	{
		char filename[233];
		sprintf(filename, "genebase\\%s\\LCS-%s & %s.txt", t1.ID, t1.name, t2.name);
		FILE* fp = fopen(filename, "w");
		fprintf(fp, "Longest Common Sequence for %s & %s\n", t1.name, t2.name);
		fprintf(fp, "Sum:%d\n", sum);
		fprintf(fp, "Sequence:\n%s", lcs);
		fclose(fp);
		printf("成功：成功获得最长公共子序列数据，已保存至%s中，请查看。\n\n", filename);
	}
	seq_len lcs_len = { lcs,sum };
	return lcs_len;//以长度+序列的结构体形式返回
}