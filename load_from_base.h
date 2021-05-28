#pragma once
/*从当前基因数据库中调取基因并以完整信息gene变量的的形式返回*/
gene load_from_base(int id, int t)
//t=0代表用户调用函数本身操作，则输出读取结果；t=1代表其他函数调用，不输出结果。
{
	char* p=NULL;
	if(t==0) printf("--------在库基因读取---------\n");
	if(id<=0) //若传入编号不合法，则从键盘读取
	{
		print_roster();
		printf("请输入目标DNA序列的系统编号（参照左侧num）：");
		scanf("%d",&id); fflush(stdin);
		current_id = id;
		
	}
	if (id <= 0 || id > sum_roster)//合法性检查
	{
		printf("输入越界！请检查输入是否正确。\n");
		return;
	}
	p = roster[id].ID;
	FILE* fp;
	gene test;
	char filename[300];
	sprintf(filename, "genebase\\%s\\SOURCEDATA",p);
	fp = fopen(filename, "rb");//打开基因数据文件
	if (fp == NULL)
	{
		printf("读取失败！请检查输入是否正确。\n");
		return;
	}
	fread(&test,sizeof(gene),1,fp);//读取结构体存放的基因数据
	fclose(fp);
	if (t == 0)
	{
		sprintf(filename, "genebase\\%s\\Information-%s.txt", p,test.name);
		printf("读取成功！请检查以下信息是否正确：\n");
		printf("———————————————————————————————————————————————————\n");
		fprintf(stdout, ">%s,%s,%s\n", test.ID, test.name, test.type);
		fprintf(stdout, "SOURCE:%s\n", test.source);
		fprintf(stdout, "LOCALE:%s\n", test.locale);
		fprintf(stdout, "INSTITUTION:%s\n", test.ins);
		fprintf(stdout, "SequencingTechnology:%s\n", test.tech);
		fprintf(stdout, "REMARK:\n%s\n", test.remark);
		fprintf(stdout, "SubmitTime:%d/%d/%d\n", test.submit.m, test.submit.d, test.submit.y);
		fprintf(stdout, "Stats:A=%d,T=%d,G=%d,C=%d\nLength:%d\n", test.a, test.t, test.g, test.c, test.l);
		printf("———————————————————————————————————————————————————\n");
		fprintf(stdout,"碱基序列等详细信息请打开\n%s查看。\n", filename);
		printf("———————————————————————————————————————————————————\n");
		//fprintf(stdout, "\nORIGIN\n%s", test.seq);最后决定命令行界面不显示碱基序列，没有意义
	}//显示所选基因的信息
	return test;
}