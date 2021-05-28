#pragma once
void admin_menu();
void gene_lookup_menu();
void account_menu();
void search_menu(int);
date today;
void main_menu() //主菜单，通过主菜单调用子菜单
{
	char move=0;
	char tmp_auth[10];
	get_time(&today);
	if ((current_user.privilege) <= UNAUTHED) strcpy(tmp_auth, "没有");
	else strcpy(tmp_auth, "有");
Back_1:			//从子菜单返回时重新显示主菜单
	system("cls");
	printf("———————————————————————————————————————————————————\n");
	printf("****欢迎回来，%s！当前帐号%s提交基因的权限。今天是%d年%d月%d日。这里是主菜单:)****\n", current_user.user_name, tmp_auth, today.y, today.m, today.d);
	printf("———————————————————————————————————————————————————\n");
	printf("                      > ---输入1显示当前在库序列列表--- <\n\n");
	printf("                      > ---输入2进入序列查找与选择界面- <\n\n");
	printf("                      > ---输入3进入序列读取与统计界面- <\n\n"); //部分功能访客禁用
	printf("                      > ---输入4进入当前帐号管理界面--- <\n\n"); //访客禁用
	printf("                      > ---输入5进入新基因序列提交界面- <\n\n"); //访客与未认证账户禁用
	printf("                      > ---输入6进入管理员操作界面----- <\n\n"); //仅管理员可用
	printf("                      > ---输入其他字符退出本程序------ <\n");
	printf("———————————————————————————————————————————————————\n");
	printf("请选择：");
	rewind(stdin);//VS2015后无法使用fflush(stdin);，经CSDN查询决定与测试决定使用该函数
	scanf("%c", &move);
	switch (move) //根据选择决定操作以及用户权限筛选
	{
	case 49:
		print_roster(); 
		system("pause");
		rewind(stdin);
		goto Back_1;
		break;
	case 50:search_menu(1); system("pause"); rewind(stdin); goto Back_1;break;
	case 51:gene_lookup_menu(); system("pause"); rewind(stdin); goto Back_1; break;
	case 52:
		if (current_user.privilege == -1) 
		{
			printf("错误：您当前为访客模式，请注册后使用。\n\n");
			system("pause");
			rewind(stdin);
			goto Back_1;
		}
		account_menu(); system("pause"); rewind(stdin); goto Back_1; break;
	case 53:
		if (current_user.privilege < 1)
		{
			printf("错误：您当前的账户没有提交基因的权限。详情请联系管理员。\n\n");
			system("pause");
			rewind(stdin);
			goto Back_1;
		}
		else
		{
			load_gene(NULL, 0);
			system("pause");
			rewind(stdin);
			goto Back_1;
		}
		break;
	case 54:
		if (current_user.privilege < 2)
		{
			printf("错误：您当前的账户并非管理员哦。\n\n");
			system("pause");
			rewind(stdin);
			goto Back_1;
		}
		else
		{
			admin_menu();
			rewind(stdin);
			goto Back_1;
		}
		break;
	default:printf("\n****感谢您的使用！如对程序内容有任何疑问，请微信联系开发者：SekiroYoumu。****\n****愿世间再无苦难，早日战胜疫情，共度世纪难关。最后祝您身体健康，再见！****\n\n"); system("pause"); exit(0); break;
	}
	return;
}
void admin_menu() //管理员菜单
{
	char move;
Back_2:
	printf("欢迎你，管理员！\n");
	printf("———————————————————————————————————————————————————\n");
	printf("                      > ---输入1显示在库用户序列列表--- <\n\n");
	printf("                      > ---输入2进入修改账户密码界面--- <\n\n");
	printf("                      > ---输入3进入修改用户权限界面--- <\n\n");
	printf("                      > ---输入4进入删除用户账号界面--- <\n\n");
	printf("                      > ---输入5进入删除序列条目界面--- <\n\n");
	printf("                      > ---输入其他字符返回上一级菜单--- <\n");
	printf("———————————————————————————————————————————————————\n");
	printf("请选择：");
	rewind(stdin); //VS2019中fflush(stdin)已失效，故采取该方法清空缓冲区
	scanf("%c", &move);
	switch (move)
	{
	case 49:print_userlist(); system("pause"); rewind(stdin); goto Back_2; break;//打印用户列表信息
	case 50:password_change(); system("pause"); rewind(stdin); goto Back_2; break;//修改用户密码
	case 51:auth_change(); system("pause"); rewind(stdin); goto Back_2; break;//修改用户权限
	case 52:user_delete(); system("pause"); rewind(stdin); goto Back_2; break;//删号
	case 53:gene_delete(); system("pause"); rewind(stdin); goto Back_2; break;//删除基因信息条目（以上选项具体见函数部分）
	default: rewind(stdin); return; break;
	}
}
void search_menu(int target) //基因查找菜单
//target==1代表选取current_id，target==2代表LCS,SES过程前调用该函数，代表选取另一个参与比较的基因
{
	char move;
	int tmp_id;
Back_5:
	printf("———————————————————————————————————————————————————\n");
	printf("                          ****检索并选择基因序列****\n");
	if (target == 1)
	{
		if (current_id > 0 && current_id <= sum_roster)
			printf("\n> 您当前选定的基因为：%s <\n", roster[current_id].name);
		else printf("                           注意，您当前尚未选定基因。\n");
	}
	if (target == 2)
	{
		if (compare_id > 0 && compare_id <= sum_roster)
			printf("\n> 您当前选定的比较基因为：%s <\n", roster[compare_id].name);
		else printf("                           注意，您当前尚未选定比较基因。\n");
	}
	printf("———————————————————————————————————————————————————\n");
	printf("                      > ---输入1从在库基因列表中选取基因--- <\n\n");
	printf("                      > ---输入2对基因组库进行关键字检索--- <\n\n");
	printf("                      > ---输入其他字符返回上一级选项------ <\n");
	printf("———————————————————————————————————————————————————\n");
	printf("请选择：");
	rewind(stdin);
	scanf("%c", &move);
	switch (move)
	{
	case 49:
		print_roster();
		printf("\n请输入目标DNA序列的系统编号（参照左侧num），输入0返回上级菜单：");
		scanf("%d", &tmp_id); fflush(stdin);//通过参照当前在库基因表选取基因
		if(tmp_id==0) goto Back_5;
		if (tmp_id > sum_roster || tmp_id <= 0)
		{
			printf("输入越界！请检查你的输入。\n");
			tmp_id = 0;
		}
		break;
	case 50:tmp_id = search(); break; //通过查找关键字选取基因，具体见search函数
	default:rewind(stdin); return; break;
	}
	if (target == 1) current_id = tmp_id;
	if (target == 2) compare_id = tmp_id;
	rewind(stdin);	 //VS2019中fflush(stdin)已失效，故采取该方法清空缓冲区
	return;
}
void gene_lookup_menu() //基因具体操作菜单
{
	char move;
Back_4:
	printf("———————————————————————————————————————————————————\n");
	printf("                      ****对当前基因序列进行查看与操作****\n");
	/*显示当前是否选定基因，需先选定基因再进行后续操作；若未选取需重新选取，否则后续操作无法打开*/
	if (current_id > 0 && current_id <= sum_roster)
		printf(">您当前选定的基因为：%s <\n", roster[current_id].name);
	else printf("                      > 您当前尚未选定基因。<\n");
	printf("———————————————————————————————————————————————————\n");
	printf("                      > ---输入1读取当前基因序列信息-------------------- <\n\n");
	printf("                      > ---输入2(重新)选择基因序列信息-------------------- <\n\n");
	printf("                      > ---输入3对当前序列进行限制酶位点检查------------ <\n\n");
	printf("                      > ---输入4对当前序列进行翻译---------------------- <\n\n");
	printf("                      > ---输入5对当前序列与另一指定序列进行LCS检查----- <\n\n");
	printf("                      > ---输入6对当前序列与另一指定序列进行SES检查----- <\n\n");
	printf("                      > ---输入7检索与当前选定基因序列最相近在库序列---- <\n\n");
	printf("                      > ---输入其他字符返回上一级菜单------ <\n");
	printf("———————————————————————————————————————————————————\n");
	printf("请选择：");
	rewind(stdin);
	scanf("%c", &move);
	if (current_user.privilege < 0 && (move >= 50 && move <= 55))
	{
		printf("错误：您当前为访客模式，请注册后使用上述功能。\n\n");
		system("pause");
		rewind(stdin);
		goto Back_4;
	}
	if ((current_id <= 0 || current_id > sum_roster) && (move >= 51 && move <= 55))
	{
		printf("> 您当前尚未选定基因，无法执行上述操作。<\n"); //若未选取基因则无法执行操作
		system("pause");
		goto Back_4;
	}
	switch (move)
	{
	case 49:
		load_from_base(current_id, 0);
		system("pause");
		goto Back_4;
		break;
	case 50:search_menu(1); system("pause"); goto Back_4; break; //重新选取基因
	case 51:cut_check(current_id); system("pause"); goto Back_4; break;//限制酶检查
	case 52:translate(current_id); system("pause"); goto Back_4; break;//转录-翻译
	case 53:search_menu(2); LCS(current_id, compare_id, 0);  break;//LCS计算
	case 54:search_menu(2); SES(current_id, compare_id, 0); system("pause"); break;//SES计算
	case 55:max_similarity(current_id); system("pause"); break;//最大相似度计算（以上功能具体见函数）
	default:return; break;
	}
}
void account_menu()//一般用户的账号管理界面
{
	char move;
Back_3:
	printf("———————————————————————————————————————————————————\n");
	printf("                                 ****账号管理****\n");
	printf("———————————————————————————————————————————————————\n");
	printf("                      > ---输入1进入修改当前账户密码界面------ <\n\n");
	printf("                      > ---输入2进入当前用户权限认证界面------ <\n\n");
	printf("                      > ---输入其他字符返回上一级菜单------ <\n");
	printf("———————————————————————————————————————————————————\n");
	printf("请选择：");
	rewind(stdin);
	scanf("%c", &move);
	switch (move)
	{
	case 49:password_change(); system("pause"); goto Back_3; break;//修改密码
	case 50:auth_change(); system("pause"); goto Back_3; break;//在用户获得验证码后，可进行重新验证
	default: return; break;//VS2019中fflush(stdin)已失效，故采取该方法清空缓冲区
	}
}
