#pragma once
char* LCS(gene t1, gene t2)
{
	int y,x;
	int n[2] = {t1.l,t2.l};
	int** p = NULL;
	bool flag=0;
	p = (int**)malloc((n[0]+2) * sizeof(int*));
	if (p == NULL) printf("Allocation Failed!");
	for (x = 0; x < (n[0] + 1); x++)
	{
		p[x]= (int*)malloc((n[1]+2) * sizeof(int));
		if (p[x] == NULL) printf("Allocation Failed!");
		p[x][0] = 0;
	}
	for (y = 0; y < (n[1] + 1); y++) p[0][y] = 0; //初始化DP问题中的0行0列
	for (x = 1; x < (n[0] + 1); x++) //行遍历
	{
		for (y = 1; y < (n[1] + 1); y++) //列遍历
		{
			flag = (t1.seq[x]==t2.seq[y]);
			switch (flag)
			{
			case 1:p[x][y] = p[x - 1][y - 1] + 1; break;
			case 0:p[x][y] = max(p[x][y - 1], p[x - 1][y]); break; //长度的递归表达式
			}
		}
	}
	printf("\n\n%d", p[x-1][y-1]);
	return NULL;
}