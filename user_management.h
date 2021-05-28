#pragma once
#include "Initialization.h"

int login()//登录函数，成功返回1，失败返回0。
{
	int i,n;
	bool flag = 0;
	char tmp_name[100];//暂存用户输入的账号以备比较
	char tmp_pw[17];//暂存用户输入的密码以备比较
	char tmp_auth[10];//暂存用户输入的确认码以备比较
	printf("———————————————————————————————————————————————————\n");
	printf("\n登录(要返回上级菜单，请直接键入exit)\n");
	do {
		printf("请输入机构名：");
		scanf("%s", tmp_name);//输入账号
		rewind(stdin);
		if (strcmp(tmp_name, "exit") == 0) return 0;//输入exit退出该函数，返回上级选择界面，返回0代表登录失败，后同
		for (i = 0; i <= sum_user; i++)
		{
			if (strcmp(tmp_name, userlist[i].user_name) == 0)
			{
				flag = 1;
				n = i;
				break;
			}
		}//从用户列表库中比对账号是否存在，若存在记住其序号
		switch (flag)
		{
		case 0: printf("该机构名不存在或尚未注册！请检查输入是否正确。若当前机构未注册，请输入exit，注册新账号。\n");  break;
		case 1: break;//flag==1时代表用户存在，进入输入密码部分，否则
		}
	} while (flag == 0);
	do{
		printf("请输入密码(小于16位)：");
		scanf("%s", tmp_pw); rewind(stdin);//输入密码
		if (strcmp(tmp_pw, "exit") == 0) return 0;//exit退出函数返回上一级选择
		flag = 0;
		if (strcmp(userlist[n].password, tmp_pw) == 0) flag = 1;//根据序号判断密码正确性
		if (flag == 0) printf("密码错误！请重新输入。\n");
	} while (flag==0);
	current_user = userlist[n];//验证通过后，当前用户即为该序号用户
	if ((current_user.privilege) <= UNAUTHED) strcpy(tmp_auth, "没有");
	else strcpy(tmp_auth, "有");
	printf("登录成功！您当前的账号为：%s\n该机构%s提交基因的权限，详情请咨询管理员。\n", current_user.user_name,tmp_auth);//输出用户的权限
	return 1;//返回1代表登录成功
}

int registration()//注册函数，成功返回1，失败返回0。
{
	int i,auth;
	bool flag = 1;
	char tmp_name[100]; //暂存账户
	char tmp_pw[40]; //暂存密码，为防止越界空间定略大
	char tmp_pwre[17]; //检验密码输入前后是否一致
	printf("———————————————————————————————————————————————————\n");
	printf("注册(要返回上级菜单，请直接键入exit)\n");
	printf("请输入机构名（包含字母，符号，数字等，不包含空格！）：");
	scanf("%s", tmp_name); rewind(stdin);
	for (i = 0; i <= sum_user; i++)
	{
		if (strcmp(tmp_name, userlist[i].user_name) == 0)
		{
			flag = 0;
			break;
		}
	}//逐个验证当前帐号是否已经被注册
	if (flag == 0) {
		printf("当前账号已被注册，请直接登录！");
		return 0;
	}
	if (strcmp(tmp_name, "exit") == 0) return 0;
	Redo:
	printf("请输入不超过16位的密码（包含字母，符号，数字等，不包含空格！）：");
	scanf("%s", tmp_pw); rewind(stdin);
	if (strcmp(tmp_pw, "exit") == 0) return 0;
	if (strlen(tmp_pw) > 16)
	{
		printf("密码超出长度！请重新输入。\n");
		goto Redo;
	}//检查密码是否超出长度，若超出长度要求其重新输入。
	printf("请再次输入密码：");
	scanf("%s", tmp_pwre); rewind(stdin);
	if (strcmp(tmp_pwre,tmp_pw)!=0)
	{
		printf("两次输入密码不一致！请重新输入。\n");
		goto Redo;
	}
	printf("\n若您的机构已取得基因测序的相关许可，请与管理员联系获取一个解锁提交序列权限验证的确认码。\n如果您拥有权限验证的确认码的话，请输入确认码：");
	scanf("%s", tmp_pw); fflush(stdin);//用户输入确认码以验证资质
	if (strcmp(tmp_pw, "exit") == 0) return 0;
	if (strcmp(tmp_pw, auth_key) == 0)
	{
		printf("验证成功！该账号拥有提交基因数据的权限。\n");
		auth = AUTHED;//意味着有导入序列权限；
	}
	else {
		printf("验证失败！该账号只拥有查看已提交基因数据的权限。\n若您拥有相关资质或许可，请联系管理员取得确认码后在主菜单“账户管理”子菜单中重新验证。\n");
		auth = UNAUTHED;//代表只有查看权限；（P.S.:管理员权限赋值为2(ROOT),见struct_definition.h）
	}
	printf("注册成功！请登录账号。\n");
	sum_user++;
	if (userlist == NULL) exit(2);
	userlist = (user*)realloc(userlist, sizeof(user) * (sum_user + 1));//注册成功后，重新分配用户列表内存以增加新用户
	userlist[sum_user].user_id = sum_user;
	strcpy(userlist[sum_user].user_name, tmp_name);
	strcpy(userlist[sum_user].password, tmp_pwre);
	userlist[sum_user].privilege= auth;
	FILE* fp;
	fp = fopen("UserInformation.dat", "r+");
	if (fp == NULL)
	{
		perror("Error:");
		return -1;
	}
	fseek(fp, 0L, 2);
	fwrite(&userlist[sum_user], sizeof(user), 1, fp);//将新用户信息输入用户花名册文件
	rewind(fp);
	fwrite(&sum_user, sizeof(int), 1, fp);//更新位于文件开头的用户数量
	fclose(fp);
	if (login() == 1) return 1;
	else return 0;
}
/*以下为共用命令，命令操作取决于当前用户等级*/
void password_change() //修改密码
{
	int id,i;
	char tmp_pw[40];
	char tmp_pwre[17];
	if (current_user.privilege <= 1) id = current_user.user_id;//一般用户只能修改本账号密码
	else if (current_user.privilege == 2)//管理员允许修改所有账户的密码
	{
		printf("欢迎你，管理员！\n请输入需要修改密码的账户编号：");
		scanf("%d", &id);
		if (id < 0 || id > sum_user) return;
	}
	else printf("Wrong Data Detected\n"); return;
	Redo:
	printf("(要返回上级菜单，请直接键入exit)\n请输入不超过16位的新密码：");
	scanf("%s", tmp_pw); fflush(stdin);
	if (strcmp(tmp_pw, "exit") == 0) return;
	if (strlen(tmp_pw) > 16)
	{
		printf("密码超出长度！请重新输入。\n");
		goto Redo;
	}
	printf("请再次输入新密码：");//新密码确认
	scanf("%s", tmp_pwre); fflush(stdin);
	if (strcmp(tmp_pwre, "exit") == 0) return;
	if (strcmp(tmp_pwre, tmp_pw) != 0)
	{
		printf("两次输入密码不一致！请重新输入。\n");
		goto Redo;
	}
	/*更改密码后，重新录入用户信息(采用全部覆盖的方式进行)*/
	strcpy(userlist[id].password, tmp_pwre);
	FILE* fp = fopen("UserInformation.dat", "w");
	if (fp == NULL)
	{
		perror("Error:");
		return;
	}
	fwrite(&sum_user, sizeof(int), 1, fp);
	for (i = 0; i <= sum_user; i++)
	{
		fwrite(&userlist[i], sizeof(user), 1, fp);
	}
	fclose(fp);
	printf("密码修改成功！注意，您可能需要重新启动系统以使更改生效。\n");
	return;
}
void auth_change() //修改账户权限
{
	int id,i;
	int new_auth;
	int tmp_pw[40];
	int flag = 0;//flag代表权限是否修改过，若flag==1修改过则后续花名册文件需重新写入
	if (current_user.privilege == 1)//AUTHED账户无需重复验证
	{
		printf("您的账户已经拥有提交基因的权限，无需重复验证！");
		return;
	}
	if (current_user.privilege == 2)//若为管理员调用该函数，则允许修改所有账户的权限
	{
		printf("欢迎你，管理员！\n请输入需要修改权限的账户编号(输入越界数字返回)：");
		scanf("%d", &id); rewind(stdin);
		if (id < 0 || id > sum_user) return;
		printf("请输入需要修改的新权限（0代表无权提交，1代表有权提交）：");
		scanf("%d", &new_auth); rewind(stdin);
		if (new_auth == 0 || new_auth == 1)
		{
			userlist[id].privilege = new_auth;
			flag = 1;
		}
		else
		{
			printf("Wrong input!");
			return;
		}
	}
	if (current_user.privilege == 0)//UNAUTHED账户可以提交确认码获得验证
	{
		id = current_user.user_id;
		printf("\n(要返回上级菜单，请直接键入exit)\n若您的机构已取得基因测序的相关许可，请与管理员联系获取一个解锁提交序列权限验证的确认码。\n如果您拥有权限验证的确认码的话，请输入确认码：");
		scanf("%s", tmp_pw); rewind(stdin);
		if (strcmp(tmp_pw, "exit") == 0) return 0;
		if (strcmp(tmp_pw, auth_key) == 0)
		{
			printf("验证成功！该账号现在起拥有提交基因数据的权限。\n");
			flag = 1;
			new_auth = AUTHED;//意味着有导入序列权限；
			userlist[id].privilege = new_auth;
			current_user.privilege = AUTHED;
		}
		else {
			printf("验证失败！该账号仍然只拥有查看已提交基因数据的权限。\n");
			new_auth = UNAUTHED;//代表只有查看权限；（P.S.:管理员权限赋值为2(ROOT)）
		}
	}
	if(flag==1)
	{
		FILE* fp = fopen("UserInformation.dat", "w");//若确实发生修改，则写入文件（采用全部重新写入的方式）
		if (fp == NULL)
		{
			perror("Error:");
			return;
		}
		fwrite(&sum_user, sizeof(int), 1, fp);
		for (i = 0; i <= sum_user; i++)
		{
			fwrite(&userlist[i], sizeof(user), 1, fp);
		}
		fclose(fp);
		printf("权限修改成功！注意，您可能需要重新启动系统以使更改生效。\n");
	}
	return;
}
/*以下为管理员命令*/
void print_userlist()//打印当前所有在库账户的信息
{
	if (current_user.privilege != 2)
	{
		printf("您没有使用该命令的权限:(\n");
		return;
	}
	int i;
	printf("\n当前在库账户个数：%d\n", sum_user);
	printf("Num  User Name                      Password         Privilege\n");
	for (i = 1; i <= sum_user; i++)
	{
		printf("%04d %-30s %-16s %d\n", userlist[i].user_id, userlist[i].user_name, userlist[i].password, userlist[i].privilege);
	}
}
void user_delete()//删除某一账户
{
	if (current_user.privilege != 2)
	{
		printf("您没有使用该命令的权限:(\n");
		return;
	}
	int id = -1;
	int i;
	char confirm;
	print_userlist();
	printf("请输入要删除的账户编号：");
	scanf("%d", &id); rewind(stdin);
	printf("确定要删除吗？输入Y以确定，其他字符取消。"); 
	scanf("%c", &confirm); rewind(stdin);
	if (id <= 0 || id > sum_user || confirm != 'Y') return;
	for (i = id; i < sum_user; i++)
	{
		userlist[i] = userlist[i + 1];
	}//删除用户的信息
	sum_user--;
	userlist = (user*)realloc(userlist, sizeof(user) * (sum_user + 1));//为删除后的用户列表重新分配内存
	FILE* fp = fopen("UserInformation.dat", "w");//将更改写入花名册文件
	if (fp == NULL)
	{
		perror("Error:");
		return;
	}
	fwrite(&sum_user, sizeof(int), 1, fp);
	for (i = 0; i <= sum_user; i++)
	{
		if (i >= id) userlist[i].user_id--;
		fwrite(&userlist[i], sizeof(user), 1, fp);
	}
	fclose(fp);
	printf("成功删除！\n");
}