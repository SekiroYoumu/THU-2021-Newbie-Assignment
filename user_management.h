#pragma once
#include "Initialization.h"

int login()//��¼�������ɹ�����1��ʧ�ܷ���0��
{
	int i,n;
	bool flag = 0;
	char tmp_name[100];//�ݴ��û�������˺��Ա��Ƚ�
	char tmp_pw[17];//�ݴ��û�����������Ա��Ƚ�
	char tmp_auth[10];//�ݴ��û������ȷ�����Ա��Ƚ�
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("\n��¼(Ҫ�����ϼ��˵�����ֱ�Ӽ���exit)\n");
	do {
		printf("�������������");
		scanf("%s", tmp_name);//�����˺�
		rewind(stdin);
		if (strcmp(tmp_name, "exit") == 0) return 0;//����exit�˳��ú����������ϼ�ѡ����棬����0�����¼ʧ�ܣ���ͬ
		for (i = 0; i <= sum_user; i++)
		{
			if (strcmp(tmp_name, userlist[i].user_name) == 0)
			{
				flag = 1;
				n = i;
				break;
			}
		}//���û��б���бȶ��˺��Ƿ���ڣ������ڼ�ס�����
		switch (flag)
		{
		case 0: printf("�û����������ڻ���δע�ᣡ���������Ƿ���ȷ������ǰ����δע�ᣬ������exit��ע�����˺š�\n");  break;
		case 1: break;//flag==1ʱ�����û����ڣ������������벿�֣�����
		}
	} while (flag == 0);
	do{
		printf("����������(С��16λ)��");
		scanf("%s", tmp_pw); rewind(stdin);//��������
		if (strcmp(tmp_pw, "exit") == 0) return 0;//exit�˳�����������һ��ѡ��
		flag = 0;
		if (strcmp(userlist[n].password, tmp_pw) == 0) flag = 1;//��������ж�������ȷ��
		if (flag == 0) printf("����������������롣\n");
	} while (flag==0);
	current_user = userlist[n];//��֤ͨ���󣬵�ǰ�û���Ϊ������û�
	if ((current_user.privilege) <= UNAUTHED) strcpy(tmp_auth, "û��");
	else strcpy(tmp_auth, "��");
	printf("��¼�ɹ�������ǰ���˺�Ϊ��%s\n�û���%s�ύ�����Ȩ�ޣ���������ѯ����Ա��\n", current_user.user_name,tmp_auth);//����û���Ȩ��
	return 1;//����1�����¼�ɹ�
}

int registration()//ע�ắ�����ɹ�����1��ʧ�ܷ���0��
{
	int i,auth;
	bool flag = 1;
	char tmp_name[100]; //�ݴ��˻�
	char tmp_pw[40]; //�ݴ����룬Ϊ��ֹԽ��ռ䶨�Դ�
	char tmp_pwre[17]; //������������ǰ���Ƿ�һ��
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("ע��(Ҫ�����ϼ��˵�����ֱ�Ӽ���exit)\n");
	printf("�������������������ĸ�����ţ����ֵȣ��������ո񣡣���");
	scanf("%s", tmp_name); rewind(stdin);
	for (i = 0; i <= sum_user; i++)
	{
		if (strcmp(tmp_name, userlist[i].user_name) == 0)
		{
			flag = 0;
			break;
		}
	}//�����֤��ǰ�ʺ��Ƿ��Ѿ���ע��
	if (flag == 0) {
		printf("��ǰ�˺��ѱ�ע�ᣬ��ֱ�ӵ�¼��");
		return 0;
	}
	if (strcmp(tmp_name, "exit") == 0) return 0;
	Redo:
	printf("�����벻����16λ�����루������ĸ�����ţ����ֵȣ��������ո񣡣���");
	scanf("%s", tmp_pw); rewind(stdin);
	if (strcmp(tmp_pw, "exit") == 0) return 0;
	if (strlen(tmp_pw) > 16)
	{
		printf("���볬�����ȣ����������롣\n");
		goto Redo;
	}//��������Ƿ񳬳����ȣ�����������Ҫ�����������롣
	printf("���ٴ��������룺");
	scanf("%s", tmp_pwre); rewind(stdin);
	if (strcmp(tmp_pwre,tmp_pw)!=0)
	{
		printf("�����������벻һ�£����������롣\n");
		goto Redo;
	}
	printf("\n�����Ļ�����ȡ�û������������ɣ��������Ա��ϵ��ȡһ�������ύ����Ȩ����֤��ȷ���롣\n�����ӵ��Ȩ����֤��ȷ����Ļ���������ȷ���룺");
	scanf("%s", tmp_pw); fflush(stdin);//�û�����ȷ��������֤����
	if (strcmp(tmp_pw, "exit") == 0) return 0;
	if (strcmp(tmp_pw, auth_key) == 0)
	{
		printf("��֤�ɹ������˺�ӵ���ύ�������ݵ�Ȩ�ޡ�\n");
		auth = AUTHED;//��ζ���е�������Ȩ�ޣ�
	}
	else {
		printf("��֤ʧ�ܣ����˺�ֻӵ�в鿴���ύ�������ݵ�Ȩ�ޡ�\n����ӵ��������ʻ���ɣ�����ϵ����Աȡ��ȷ����������˵����˻������Ӳ˵���������֤��\n");
		auth = UNAUTHED;//����ֻ�в鿴Ȩ�ޣ���P.S.:����ԱȨ�޸�ֵΪ2(ROOT),��struct_definition.h��
	}
	printf("ע��ɹ������¼�˺š�\n");
	sum_user++;
	if (userlist == NULL) exit(2);
	userlist = (user*)realloc(userlist, sizeof(user) * (sum_user + 1));//ע��ɹ������·����û��б��ڴ����������û�
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
	fwrite(&userlist[sum_user], sizeof(user), 1, fp);//�����û���Ϣ�����û��������ļ�
	rewind(fp);
	fwrite(&sum_user, sizeof(int), 1, fp);//����λ���ļ���ͷ���û�����
	fclose(fp);
	if (login() == 1) return 1;
	else return 0;
}
/*����Ϊ��������������ȡ���ڵ�ǰ�û��ȼ�*/
void password_change() //�޸�����
{
	int id,i;
	char tmp_pw[40];
	char tmp_pwre[17];
	if (current_user.privilege <= 1) id = current_user.user_id;//һ���û�ֻ���޸ı��˺�����
	else if (current_user.privilege == 2)//����Ա�����޸������˻�������
	{
		printf("��ӭ�㣬����Ա��\n��������Ҫ�޸�������˻���ţ�");
		scanf("%d", &id);
		if (id < 0 || id > sum_user) return;
	}
	else printf("Wrong Data Detected\n"); return;
	Redo:
	printf("(Ҫ�����ϼ��˵�����ֱ�Ӽ���exit)\n�����벻����16λ�������룺");
	scanf("%s", tmp_pw); fflush(stdin);
	if (strcmp(tmp_pw, "exit") == 0) return;
	if (strlen(tmp_pw) > 16)
	{
		printf("���볬�����ȣ����������롣\n");
		goto Redo;
	}
	printf("���ٴ����������룺");//������ȷ��
	scanf("%s", tmp_pwre); fflush(stdin);
	if (strcmp(tmp_pwre, "exit") == 0) return;
	if (strcmp(tmp_pwre, tmp_pw) != 0)
	{
		printf("�����������벻һ�£����������롣\n");
		goto Redo;
	}
	/*�������������¼���û���Ϣ(����ȫ�����ǵķ�ʽ����)*/
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
	printf("�����޸ĳɹ���ע�⣬��������Ҫ��������ϵͳ��ʹ������Ч��\n");
	return;
}
void auth_change() //�޸��˻�Ȩ��
{
	int id,i;
	int new_auth;
	int tmp_pw[40];
	int flag = 0;//flag����Ȩ���Ƿ��޸Ĺ�����flag==1�޸Ĺ�������������ļ�������д��
	if (current_user.privilege == 1)//AUTHED�˻������ظ���֤
	{
		printf("�����˻��Ѿ�ӵ���ύ�����Ȩ�ޣ������ظ���֤��");
		return;
	}
	if (current_user.privilege == 2)//��Ϊ����Ա���øú������������޸������˻���Ȩ��
	{
		printf("��ӭ�㣬����Ա��\n��������Ҫ�޸�Ȩ�޵��˻����(����Խ�����ַ���)��");
		scanf("%d", &id); rewind(stdin);
		if (id < 0 || id > sum_user) return;
		printf("��������Ҫ�޸ĵ���Ȩ�ޣ�0������Ȩ�ύ��1������Ȩ�ύ����");
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
	if (current_user.privilege == 0)//UNAUTHED�˻������ύȷ��������֤
	{
		id = current_user.user_id;
		printf("\n(Ҫ�����ϼ��˵�����ֱ�Ӽ���exit)\n�����Ļ�����ȡ�û������������ɣ��������Ա��ϵ��ȡһ�������ύ����Ȩ����֤��ȷ���롣\n�����ӵ��Ȩ����֤��ȷ����Ļ���������ȷ���룺");
		scanf("%s", tmp_pw); rewind(stdin);
		if (strcmp(tmp_pw, "exit") == 0) return 0;
		if (strcmp(tmp_pw, auth_key) == 0)
		{
			printf("��֤�ɹ������˺�������ӵ���ύ�������ݵ�Ȩ�ޡ�\n");
			flag = 1;
			new_auth = AUTHED;//��ζ���е�������Ȩ�ޣ�
			userlist[id].privilege = new_auth;
			current_user.privilege = AUTHED;
		}
		else {
			printf("��֤ʧ�ܣ����˺���Ȼֻӵ�в鿴���ύ�������ݵ�Ȩ�ޡ�\n");
			new_auth = UNAUTHED;//����ֻ�в鿴Ȩ�ޣ���P.S.:����ԱȨ�޸�ֵΪ2(ROOT)��
		}
	}
	if(flag==1)
	{
		FILE* fp = fopen("UserInformation.dat", "w");//��ȷʵ�����޸ģ���д���ļ�������ȫ������д��ķ�ʽ��
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
		printf("Ȩ���޸ĳɹ���ע�⣬��������Ҫ��������ϵͳ��ʹ������Ч��\n");
	}
	return;
}
/*����Ϊ����Ա����*/
void print_userlist()//��ӡ��ǰ�����ڿ��˻�����Ϣ
{
	if (current_user.privilege != 2)
	{
		printf("��û��ʹ�ø������Ȩ��:(\n");
		return;
	}
	int i;
	printf("\n��ǰ�ڿ��˻�������%d\n", sum_user);
	printf("Num  User Name                      Password         Privilege\n");
	for (i = 1; i <= sum_user; i++)
	{
		printf("%04d %-30s %-16s %d\n", userlist[i].user_id, userlist[i].user_name, userlist[i].password, userlist[i].privilege);
	}
}
void user_delete()//ɾ��ĳһ�˻�
{
	if (current_user.privilege != 2)
	{
		printf("��û��ʹ�ø������Ȩ��:(\n");
		return;
	}
	int id = -1;
	int i;
	char confirm;
	print_userlist();
	printf("������Ҫɾ�����˻���ţ�");
	scanf("%d", &id); rewind(stdin);
	printf("ȷ��Ҫɾ��������Y��ȷ���������ַ�ȡ����"); 
	scanf("%c", &confirm); rewind(stdin);
	if (id <= 0 || id > sum_user || confirm != 'Y') return;
	for (i = id; i < sum_user; i++)
	{
		userlist[i] = userlist[i + 1];
	}//ɾ���û�����Ϣ
	sum_user--;
	userlist = (user*)realloc(userlist, sizeof(user) * (sum_user + 1));//Ϊɾ������û��б����·����ڴ�
	FILE* fp = fopen("UserInformation.dat", "w");//������д�뻨�����ļ�
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
	printf("�ɹ�ɾ����\n");
}