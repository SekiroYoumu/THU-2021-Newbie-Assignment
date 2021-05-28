#pragma once
int SES(int id1,int id2,int t) 
//t=0代表用户调用SES，则输出SES文件；t=1代表用户调用求最相近基因组函数，不输出SES文件。
{
	gene t1 = load_from_base(id1, 1);
	gene t2 = load_from_base(id2, 1);//读取基因详细信息
	if (id1 > sum_roster || id1 <= 0 || id2 > sum_roster || id2 <= 0) return 10000000;//若输入出错则返回一个大数，防止影响“最大相似度”函数的计算
	int x, x1, x2, y;
	int n_cut = 0, n_plug = 0, sum = 0;//n_cut切割总数 n_plug插入总数 sum操作总数
	seq_len lcs_len;//定义“含长度的序列”结构体，同时从LCS函数接受长度和LCS序列，具体实现见LCS函数
	lcs_len = LCS(id1, id2, 1);
	if(t==0) printf("\n------SES正在计算中……------\n");
	char* lcs = lcs_len.seq;
	int l = lcs_len.l;
	int* num = (int*)malloc(l * sizeof(int)); //构造num数组，填入LCS对应t1.seq的位置编号，形成一一对应，以确定后续插入操作的位置
	char filename[233];
	FILE* fp=NULL;
	if (t == 0)
	{
		sprintf(filename, "genebase\\%s\\SES-%s & %s.txt", t1.ID, t1.name, t2.name);
		fp = fopen(filename, "w");
	}
	
	for (y = 0, x = 0, x1 = 0; x1 < t1.l;) //完成t1.seq-lcs的过程，并即时输出操作
	{
		if (lcs[x] == t1.seq[x1])
		{
			num[x] = x1+1;
			x++; x1++; y++;
		}
		else
		{
			n_cut++;
			if(fp!=NULL) fprintf(fp, "%d；切除%c\n", x1+1, t1.seq[x1]);
			x1++;
		}
	}
	for (y = 0, x = 0, x2 = 0; x2 < t2.l;)//完成t2.seq-lcs的过程，并即时输出操作
	{
		if (lcs[x] == t2.seq[x2])
		{
			x++; x2++; y++;
		}
		else
		{
			n_plug++;
			if (fp != NULL) fprintf(fp, "%d；插入%c\n", num[x], t2.seq[x2]);
			x2++;
		}
	}
	sum = n_cut + n_plug;
	if(fp!=NULL) rewind(fp);
	if (t == 0)
	{
		fprintf(fp, "最短操作次数：%d；\n", sum);
		printf("成功：最少操作次数检测完毕！结果已被保存在%s中，请查看。\n\n", filename);
		fclose(fp);
	}
	free(lcs); lcs = NULL;
	free(num); num = NULL;//释放临时开辟的lcs与num空间
	return sum;
}
int max_similarity(int id) //若id<=0则代表由用户未指定基因，需重新输入
{
	if (id <= 0)
	{
		printf("请输入需作样本的基因组编号：");
		scanf("%d", &id);
	}
	if (id < 0 || id > sum_roster)
	{
		printf("输入错误！请重新检查输入。\n");
		return -1;
	}
	int max_id=-1;//最大相似度基因的序号
	int min_SES=10000000;//先定义大数，防止干扰后续结果（VS不允许局部变量不初始化TAT）
	int i=0;
	int tmp = -1;//暂存SES大小
	printf("正在计算中……\n");
	for (i = 1; i <= sum_roster; i++)
	{
		if (i == id) continue;
		tmp=SES(id,i,1); //获得编号为i的序列和样本序列的SES大小
		if (tmp <= min_SES)
		{
			max_id = i;
			min_SES = tmp;
		}//如果当前SES大小比min_SES大，则替换
	}
	printf("与%s最相近的病毒基因名称为%s\n其ID为%s，系统内编号为%06d\n二者的SES次数最小，为%d。\n",roster[id].name,roster[max_id].name, roster[max_id].ID, roster[max_id].id,min_SES);
	return max_id;
}