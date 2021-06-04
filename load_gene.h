#pragma once
/*格式化读取置于根目录的DNA序列文件并入库*/
int load_gene(const char *p, int method)
	/*m=0（FORMATTED）时代表格式化读入，基因组文件需按照标准格式进行编写；
	m=1（MANUAL）代表手动读入，基因组文件只需包括序列本身，其他内容从键盘读入*/
{
	if (current_user.privilege < 1)
	{
		printf("您所在的机构的当前帐号没有提交基因数据的权限，详情请联系管理员。\n");
		system("pause");
		return -1;
	}
	int i = 0, j = 0, c = 0;//循环变量
	char ch;
	gene load;
	FILE *fp;
	char filename[200];//后续创建文件夹与文件时的缓冲区
	char buf[300];//基因信息的首行会先写入该缓冲区，替换非法字符，以防影响非法创建
	printf("———————————————————————————————————————————————————\n");
	printf("                                 ---------基因入库----------\n");
	printf("———————————————————————————————————————————————————\n");
	if (p==NULL) //若传输空指针则代表要从键盘读取
	{
		printf("若您需要采用格式化读入（按照说明文档中格式编辑好基因文件），请输入0；\n若您需要采用手动读入（确保基因文件只含有碱基序列），请输入1。\n如果您希望返回上级菜单，请输入其他数字。\n");
		printf("———————————————————————————————————————————————————\n请选择：");
		scanf("%d",&method); rewind(stdin);
		if (method < 0 || method > 1) return -1;
		printf("请输入需要读取的基因文件名(确保其已置于根目录！)或路径。输入exit退出:");
		scanf("%s", filename); rewind(stdin);
		if (strcmp(filename, "exit") == 0) return -1;
		p = filename;
	}
	printf("\n------------正在读取：%s------------\n", p);
	if((fp=fopen(p,"r"))==NULL)
	{
		printf("错误：该文件无法被读取！\n");
		return -1;
	}
	if (method == FORMATTED)
	{
		int flag=0;//以第一行为标准，验证格式化文件格式是否正确(只做大体验证）
		fgets(buf, 299, fp);//这一行设计文件与文件夹创建，故不能有Windows系统不兼容的字符！！,会在说明文档中提出，否则会被自动替换成"_"
		if (buf[0] != '>')
		{
			printf("基因文件格式不正确！请根据说明书中的格式进行调整后再行上传。注意：若该基因文件仅包含碱基序列，请选择“非格式化上传”。\n\n");
			return -1;
		}
		for (i = 1; buf[i] != '\n'; i++)
		{
			if (buf[i] == ',') flag = 1; //若检测到逗号则说明格式大概率没问题
			for (j = 0; not_allowed[j] != '\0'; j++)
			{
				if (buf[i] == not_allowed[j])
				{
					buf[i] = '_';
					printf("存在不兼容的字符！已自动替换为'_'\n");
					break;
				}
			}
		}
		if (flag==0)
		{
			printf("基因文件格式不正确！请根据说明书中的格式进行调整后再行上传。\n注意：若该基因文件仅包含碱基序列，请选择“非格式化上传”。\n");
			return -1;
		}//验证格式正确性
		sscanf(buf, ">%[^,],%[^,],%[^\n]\n", load.ID, load.name, load.type); 
		fscanf(fp, "SOURCE:%[^\n]\n", load.source);
		fscanf(fp, "LOCALE:%[^\n]\n", load.locale);
		fscanf(fp, "INSTITUTION:%[^\n]\n", load.ins);
		fscanf(fp, "SequencingTechnology:%[^\n]\n", load.tech);
		fscanf(fp, "REMARK:\n%[^\n]\n", load.remark);//格式化读取基因信息（除序列外）
	}
	if (method == MANUAL)
	{
		printf("请输入序列的通用ID：");
		fscanf(stdin, "%s", load.ID); rewind(stdin);
		printf("请输入序列的名称：");
		fscanf(stdin, "%s", load.name); rewind(stdin);
		printf("请输入序列的类型：");
		fscanf(stdin, "%s", load.type); rewind(stdin);
		printf("请输入序列的来源：");
		fscanf(stdin, "%s", load.source); rewind(stdin);
		printf("请输入序列的采集地点：");
		fscanf(stdin, "%s", load.locale); rewind(stdin);
		printf("请输入序列的测序机构：");
		fscanf(stdin, "%s", load.ins); rewind(stdin);
		printf("请输入序列的测序技术：");
		fscanf(stdin, "%s", load.tech); rewind(stdin);
		printf("请输入序列的其他相关信息与备注：");
		fscanf(stdin, "%s", load.remark); rewind(stdin);
	}//非格式化导入时，基因各类信息从键盘输入
	get_time(&load.submit);//获得提交基因时的本地时间
	for (i = 1; i <= sum_roster; i++)
	{
		if (strcmp(load.ID, roster[i].ID) == 0)
		{
			printf("错误：该基因组已在库中！\n");
			return -1;
		}
	}//检查是否重复提交
	/*读取DNA序列本体*/
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
		default:break;//忽略其他所有字符
		}
		ch = upper(fgetc(fp));
	}
	load.seq[c] = '\0'; load.l = c;
	fclose(fp);
	sprintf(filename, "md genebase\\%s", load.ID);
	system(filename);
	sprintf(filename, "genebase\\%s\\stats-%s.txt",load.ID,load.name);
	fp = fopen(filename, "w");
	fprintf(fp, "A=%d,T=%d,G=%d,C=%d,sum=%d",load.a,load.t,load.g,load.c,load.l);
	printf("成功：基因文件读取成功！统计信息已被保存在%s中。\n请核对以下基因信息是否正确：\n",filename);
	printf("———————————————————————————————————————————————————\n");
	printf("Gene source check:\nID:%s\nName:%s\nType:%s\n", load.ID, load.name, load.type);
	fprintf(stdout, "Statistics:A=%d,T=%d,G=%d,C=%d,sum=%d\n", load.a, load.t, load.g, load.c, load.l);
	printf("———————————————————————————————————————————————————\n");
	fclose(fp);
	/*花名册编号*/
	sum_roster++;
	load.id = sum_roster;
	roster = (index*)realloc(roster,sizeof(index)*(sum_roster + 1) );
	indexualize(&load,&roster[load.id]);
	fp = fopen("GeneRoster.dat", "r+b");
	rewind(fp);
	fwrite(&sum_roster, sizeof(int), 1, fp);//在开头写新基因数量
	fseek(fp, 0L, 2);
	fwrite(&roster[load.id], sizeof(index), 1, fp);//在末尾写新基因信息
	fclose(fp);
	/*固定格式的DNA源文件入库*/
	sprintf(filename, "genebase\\%s\\Information-%s.txt", load.ID, load.name); 
	fp = fopen(filename, "wb");
	fprintf(fp, ">%s,%s,%s\n", load.ID, load.name, load.type);
	fprintf(fp, "SOURCE:%s\n",load.source);
	fprintf(fp, "LOCALE:%s\n", load.locale);
	fprintf(fp, "INSTITUTION:%s\n",load.ins);
	fprintf(fp, "SequencingTechnology:%s\n", load.tech);
	fprintf(fp, "REMARK:\n%s\n", load.remark);
	fprintf(fp,"SubmitTime:%d/%d/%d,id=%d\n", load.submit.m, load.submit.d, load.submit.y,load.id);
	fprintf(fp, "Stats:A=%d,T=%d,G=%d,C=%d\nLength:%d\n", load.a, load.t, load.g, load.c, load.l);
	fprintf(fp, "\nORIGIN\n%s", load.seq);
	fclose(fp);
	/*可供直接结构体读取的DNA源文件入库，采用结构体写入的形式*/
	sprintf(filename, "genebase\\%s\\SOURCEDATA", load.ID);
	fp = fopen(filename, "wb");
	fwrite(&load, sizeof(gene), 1, fp);
	fclose(fp);
	return load.id;
}
void gene_delete() //管理员命令:删除基因条目
{
	if (current_user.privilege != 2)
	{
		printf("您没有使用该命令的权限:(\n");
		return;
	}
	int id = -1;
	int i;
	print_roster();
	printf("请输入要删除的基因信息编号：");
	scanf("%d", &id); rewind(stdin);
	printf("确定要删除吗？"); system("pause");
	if (id <= 0 || id > sum_roster) return;
	char filename[200];
	sprintf(filename, "rd /s /q genebase\\%s", roster[id].ID);//通过命令行命令删除所选基因条目的数据文件夹
	system(filename);
	for (i = id; i < sum_roster; i++)
	{
		roster[i] = roster[i + 1];
	}//删除该基因的索引信息（采用覆盖的形式）
	sum_roster--;
	roster = (index*)realloc(roster, sizeof(index) * (sum_user + 1));//重新分配基因索引的内存空间
	FILE* fp = fopen("GeneRoster.dat", "wb");//重新写入花名册文件
	if (fp == NULL)
	{
		perror("Error:");
		return;
	}
	roster[1].id = 1;
	fwrite(&sum_roster, sizeof(int), 1, fp);
	for (i = 1; i <= sum_roster; i++)
	{
		if (i >= id) roster[i].id--;
		fwrite(&roster[i], sizeof(index), 1, fp);
	}
	fclose(fp);
	printf("成功删除！\n");
}
