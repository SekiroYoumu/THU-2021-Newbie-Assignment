#pragma once
int search()
{
	int t=0;//选择关键字类型
	int i = 0;//循环变量
	int n = 0;//结果数组的变量
	int m = 0;//二级筛选选择的id
	bool flag = 0;//是否找到的flag
	int result = 0;//最终选定的结果
	char* now;//指向查找对象的指针
	char target[51];//关键字
	char* needle;      //构建指针以备大小写转换
	char now_buf[200];//构建缓冲区以备大小写转换
	printf("———————————————————————————————————————————————————\n");
	printf("                                 ****关键字查找****\n———————————————————————————————————————————————————\n                      >--- 输入1按照序列名称查找；输入2按照来源类型查找；---<\n\n                      >--- 输入3按照采集地点查找；输入4按照测序机构查找；---<\n\n                      >--- 输入5按照测序技术查找。输入6按照序列通用ID查找。-<\n\n                      >--- 输入其他数字返回上级菜单。---<\n");
	printf("———————————————————————————————————————————————————\n");
	printf("\n请选择：");
	scanf("%d", &t);
	rewind(stdin);
	if (t > 6 || t <= 0) return -1;
	int* result_id = (int*)malloc(sizeof(int) * (sum_roster));//根据序列条目总数开辟数组暂存搜索结果，共后续进一步筛选
	printf("请输入您需要查找的关键字(不长于50字符)：");
	scanf("%s", target);
	rewind(stdin);
	needle = strlower(target);//将target中的字符全部转换为小写，后文统一以小写形式查找
	for (i=1;i<=sum_roster;i++)
	{
		switch (t)//根据所选关键字决定查找对象指针的指向
		{
		case 1:now = &roster[i].name; break;
		case 2:now = &roster[i].source; break;
		case 3:now = &roster[i].locale; break;
		case 4:now = &roster[i].ins; break;
		case 5:now = &roster[i].tech; break;
		case 6:now = &roster[i].ID; break;
		default:printf("Error！"); return NULL;
		}
		strcpy(now_buf, now);
		now = strlower(now_buf);//将now指向的字符串字符导入now_buf中后再对now_buf转换为小写后查找，避免影响原数据
		if (strstr(now, needle) != NULL)
		{
			result_id[n] = roster[i].id;
			printf("找到第%d条数据，系统内编号为：%06d，名称为：%s\n", n+1 , roster[i].id,roster[i].name);
			n++;
			if (n > 1) flag = 1;
		}
	}
	if (flag == 1)
	{
		printf("您需要上述第几条序列信息？请输入本次搜索的序号，若均不需要，请输入0，选择将会被重置：");
		scanf("%d",&m);
		rewind(stdin);
		if (m == 0) return 0;
		result = result_id[m - 1];
	}
	else result = result_id[0];
	return result;
}