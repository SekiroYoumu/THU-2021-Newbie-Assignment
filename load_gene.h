#pragma once
typedef struct gene_information
{
	char ID[15];
	char name[100];
	char type[20];
	char seq[50000];
	int a,t,c,g,l;
}gene;
gene load_gene(const char *p)
{
	int c=0;
	char ch;
	gene load;
	FILE *fp;
	if (p==NULL)
	{
		printf("请输入需要读取的基因文件名或路径:");
		scanf("%s", p);
	}
	printf("正在读取：%s\n\n", p);
	if((fp=fopen(p,"r"))==NULL)
	{
		printf("错误：该文件无法被读取！\n");
		exit(1); 
	}
	fscanf(fp,">%[^,],%[^,],%[^\n]",load.ID,load.name,load.type);
	ch=upper(fgetc(fp));
	load.a = 0; load.t = 0; load.g = 0; load.c = 0;
	while(ch!=EOF)
	{
		switch (ch)
		{
		case'A':load.a++; load.seq[c] = ch; c++; break;
		case'T':load.t++; load.seq[c] = ch; c++; break;
		case'C':load.c++; load.seq[c] = ch; c++; break;
		case'G':load.g++; load.seq[c] = ch; c++; break;
		default:break;
		}
		ch = upper(fgetc(fp));
	}
	load.seq[c] = '\0'; load.l = c;
	fclose(fp);
	char filename[100];
	sprintf(filename, "md %s", load.ID);
	system(filename);
	sprintf(filename, "%s\\stats-%s.txt",load.ID,load.name);
	fp = fopen(filename, "w");
	fprintf(fp, "A=%d,T=%d,G=%d,C=%d,sum=%d",load.a,load.t,load.g,load.c,load.l);
	fprintf(stdout, "A=%d,T=%d,G=%d,C=%d,sum=%d\n\n", load.a, load.t, load.g, load.c, load.l);
	printf("基因文件读取成功！统计信息已被保存在%s中。\n\n",filename);
	printf("Gene source check:\nID:%s\nName:%s\nType:%s\n\n", load.ID, load.name, load.type);
	fclose(fp);
	return load;
}

