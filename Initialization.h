#pragma once
void encrypt(char* pw)
{
	for (; *pw != '\0'; pw++)
	{
		if (*pw < 127) *pw = *pw + 1;
		else
		{
			printf("密码中含有非法字符！");
			return;
		}
	}
}//用ASCII码+1（除del）的方法完成密码的加密（写入时）
void decrypt(char* pw)
{
	for (; *pw != '\0'; pw++)
	{
		*pw = *pw - 1;
	}
	return;
}//用ASCII码+1（除del）的方法完成密码的解密（读取时）
void initialize()//初始化函数
{
	int i;
	system("color 0F");
	file_print("loading_screen.dat");//初始化界面，从文件中打印即可
	FILE* fp;
	printf("\n警告：该程序尚在施工中，请全程佩戴安全帽游览哦:)\n");
	/*Part 1.读取基因序列索引花名册*/
	fp = fopen("GeneRoster.dat", "r+b");
	if (fp == NULL)
	{
		fp = fopen("GeneRoster.dat", "wb");
		fwrite(&sum_roster, sizeof(int), 1, fp);
		rewind(fp);
	}//若无基因索引则重新创建
	fread(&sum_roster, sizeof(int), 1, fp);//基因序列总数被置于文件首
	roster = (index *)malloc(sizeof(index)*(sum_roster + 1));//读取后根据总数为基因索引分配空间
	if (roster == NULL) perror("Error:");
	for (i = 1; i <= sum_roster; i++)
	{
		fread(&roster[i], sizeof(index), 1, fp);//逐个读取基因序列索引
		roster[i].id = i;
	}
	printf("———————————————————————————————————————————————————\n");
	printf("****在库序列索引加载完毕……****\n****当前在库序列：%d条***********",sum_roster); 
	fclose(fp);
	/*Part 2.读取用户列表*/
	fp = fopen("UserInformation.dat", "r+b");
	if (fp == NULL)
	{
		fp = fopen("UserInformation.dat", "wb");
		fwrite(&sum_user, sizeof(int), 1, fp);
		encrypt(admin.password);
		fwrite(&admin, sizeof(user), 1, fp);//初次加载时输入管理员账户
		decrypt(admin.password);
		rewind(fp);
	}//若无用户列表则重新创建
	fread(&sum_user, sizeof(int), 1, fp);//用户列表总数被置于文件首
	userlist = (user*)malloc(sizeof(user) * (sum_user + 1));//读取后根据总数为用户分配空间
	for (i = 0; i <= sum_user; i++)
	{
		fread(&userlist[i], sizeof(user), 1, fp);//读取用户列表
		userlist[i].user_id = i;
		decrypt(userlist[i].password);
	}
	printf("\n****在库用户列表加载完毕……****\n****当前已注册用户：%d名********",sum_user); //加载现有用户列表
	printf("\n>-初始化完成！快进来，找个位置随便坐。-<\n");
	printf("———————————————————————————————————————————————————\n");
	fclose(fp);
	/*Part 3.登录或注册界面*/
	char step;
	back:
	do
	{
		printf("请登录或注册。\n输入1进行登录。若您是新用户，请输入2进行注册。\n输入3将作为低权限的访客模式进入程序。\n请选择：");
		step = getchar();
		rewind(stdin); //VS2019中fflush(stdin)已失效，故采取该方法清空缓冲区
	}while(step!=49&&step!=50 && step != 51);
	int flag = 0;
	switch (step)
	{
	case 49:flag = login(); break;
	case 50:flag = registration(); break;//具体功能见函数部分注释
	case 51:flag = 1; printf("注意：您将以低权限的访客模式使用该程序，某些功能可能受限哦。\n"); current_user = guest;  break;
	default:flag = 0; break;
	}
	if (flag == 0) goto back;//flag—用户验证是否通过，flag==1时允许进入主界面
	wait();//等待后清屏
}
