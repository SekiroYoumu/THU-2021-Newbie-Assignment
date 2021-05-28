#pragma once
void initialize()//��ʼ������
{
	int i;
	file_print("loading_screen.dat");//��ʼ�����棬���ļ��д�ӡ����
	FILE* fp;
	printf("\n���棺�ó�������ʩ���У���ȫ�������ȫñ����Ŷ:)\n");
	/*Part 1.��ȡ������������������*/
	fp = fopen("GeneRoster.dat", "r+");
	if (fp == NULL)
	{
		fp = fopen("GeneRoster.dat", "w");
		fwrite(&sum_roster, sizeof(int), 1, fp);
		rewind(fp);
	}//���޻������������´���
	fread(&sum_roster, sizeof(int), 1, fp);//�������������������ļ���
	roster = (index *)malloc(sizeof(index)*(sum_roster + 1));//��ȡ���������Ϊ������������ռ�
	if (roster == NULL) perror("Error:");
	for (i = 1; i <= sum_roster; i++)
	{
		fread(&roster[i], sizeof(index), 1, fp);//�����ȡ������������
	}
	printf("****�ڿ���������������ϡ���****\n****��ǰ�ڿ����У�%d��***********",sum_roster); 
	fclose(fp);
	/*Part 2.��ȡ�û��б�*/
	fp = fopen("UserInformation.dat", "r+");
	if (fp == NULL)
	{
		fp = fopen("UserInformation.dat", "w");
		fwrite(&sum_user, sizeof(int), 1, fp);
		fwrite(&admin, sizeof(user), 1, fp);//���μ���ʱ�������Ա�˻�
		rewind(fp);
	}//�����û��б������´���
	fread(&sum_user, sizeof(int), 1, fp);//�û��б������������ļ���
	userlist = (user*)malloc(sizeof(user) * (sum_user + 1));//��ȡ���������Ϊ�û�����ռ�
	for (i = 0; i <= sum_user; i++)
	{
		fread(&userlist[i], sizeof(user), 1, fp);//��ȡ�û��б�
	}
	printf("\n****�ڿ��û��б������ϡ���****\n****��ǰ��ע���û���%d��********",sum_user); //���������û��б�
	printf("\n>-��ʼ����ɣ���������Ҹ�λ���������-<\n");
	printf("������������������������������������������������������������������������������������������������������\n");
	fclose(fp);
	/*Part 3.��¼��ע�����*/
	char step;
	back:
	do
	{
		printf("���¼��ע�ᡣ\n����1���е�¼�����������û���������2����ע�ᡣ\n����3����Ϊ��Ȩ�޵ķÿ�ģʽ�������\n��ѡ��");
		step = getchar();
		rewind(stdin); //VS2019��fflush(stdin)��ʧЧ���ʲ�ȡ�÷�����ջ�����
	}while(step!=49&&step!=50 && step != 51);
	int flag = 0;
	switch (step)
	{
	case 49:flag = login(); break;
	case 50:flag = registration(); break;//���幦�ܼ���������ע��
	case 51:flag = 1; printf("ע�⣺�����Ե�Ȩ�޵ķÿ�ģʽʹ�øó���ĳЩ���ܿ�������Ŷ��\n"); current_user = guest;  break;
	default:flag = 0; break;
	}
	if (flag == 0) goto back;//flag���û���֤�Ƿ�ͨ����flag==1ʱ�������������
	wait();//�ȴ�������
}
