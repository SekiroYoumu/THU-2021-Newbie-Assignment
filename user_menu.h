#pragma once
void admin_menu();
void gene_lookup_menu();
void account_menu();
void search_menu(int);
date today;
void main_menu() //���˵���ͨ�����˵������Ӳ˵�
{
	char move=0;
	char tmp_auth[10];
	get_time(&today);
	if ((current_user.privilege) <= UNAUTHED) strcpy(tmp_auth, "û��");
	else strcpy(tmp_auth, "��");
Back_1:			//���Ӳ˵�����ʱ������ʾ���˵�
	system("cls");
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("****��ӭ������%s����ǰ�ʺ�%s�ύ�����Ȩ�ޡ�������%d��%d��%d�ա����������˵�:)****\n", current_user.user_name, tmp_auth, today.y, today.m, today.d);
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("                      > ---����1��ʾ��ǰ�ڿ������б�--- <\n\n");
	printf("                      > ---����2�������в�����ѡ�����- <\n\n");
	printf("                      > ---����3�������ж�ȡ��ͳ�ƽ���- <\n\n"); //���ֹ��ܷÿͽ���
	printf("                      > ---����4���뵱ǰ�ʺŹ������--- <\n\n"); //�ÿͽ���
	printf("                      > ---����5�����»��������ύ����- <\n\n"); //�ÿ���δ��֤�˻�����
	printf("                      > ---����6�������Ա��������----- <\n\n"); //������Ա����
	printf("                      > ---���������ַ��˳�������------ <\n");
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("��ѡ��");
	rewind(stdin);//VS2015���޷�ʹ��fflush(stdin);����CSDN��ѯ��������Ծ���ʹ�øú���
	scanf("%c", &move);
	switch (move) //����ѡ����������Լ��û�Ȩ��ɸѡ
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
			printf("��������ǰΪ�ÿ�ģʽ����ע���ʹ�á�\n\n");
			system("pause");
			rewind(stdin);
			goto Back_1;
		}
		account_menu(); system("pause"); rewind(stdin); goto Back_1; break;
	case 53:
		if (current_user.privilege < 1)
		{
			printf("��������ǰ���˻�û���ύ�����Ȩ�ޡ���������ϵ����Ա��\n\n");
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
			printf("��������ǰ���˻����ǹ���ԱŶ��\n\n");
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
	default:printf("\n****��л����ʹ�ã���Գ����������κ����ʣ���΢����ϵ�����ߣ�SekiroYoumu��****\n****Ը�������޿��ѣ�����սʤ���飬���������ѹء����ף�����彡�����ټ���****\n\n"); system("pause"); exit(0); break;
	}
	return;
}
void admin_menu() //����Ա�˵�
{
	char move;
Back_2:
	printf("��ӭ�㣬����Ա��\n");
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("                      > ---����1��ʾ�ڿ��û������б�--- <\n\n");
	printf("                      > ---����2�����޸��˻��������--- <\n\n");
	printf("                      > ---����3�����޸��û�Ȩ�޽���--- <\n\n");
	printf("                      > ---����4����ɾ���û��˺Ž���--- <\n\n");
	printf("                      > ---����5����ɾ��������Ŀ����--- <\n\n");
	printf("                      > ---���������ַ�������һ���˵�--- <\n");
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("��ѡ��");
	rewind(stdin); //VS2019��fflush(stdin)��ʧЧ���ʲ�ȡ�÷�����ջ�����
	scanf("%c", &move);
	switch (move)
	{
	case 49:print_userlist(); system("pause"); rewind(stdin); goto Back_2; break;//��ӡ�û��б���Ϣ
	case 50:password_change(); system("pause"); rewind(stdin); goto Back_2; break;//�޸��û�����
	case 51:auth_change(); system("pause"); rewind(stdin); goto Back_2; break;//�޸��û�Ȩ��
	case 52:user_delete(); system("pause"); rewind(stdin); goto Back_2; break;//ɾ��
	case 53:gene_delete(); system("pause"); rewind(stdin); goto Back_2; break;//ɾ��������Ϣ��Ŀ������ѡ�������������֣�
	default: rewind(stdin); return; break;
	}
}
void search_menu(int target) //������Ҳ˵�
//target==1����ѡȡcurrent_id��target==2����LCS,SES����ǰ���øú���������ѡȡ��һ������ȽϵĻ���
{
	char move;
	int tmp_id;
Back_5:
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("                          ****������ѡ���������****\n");
	if (target == 1)
	{
		if (current_id > 0 && current_id <= sum_roster)
			printf("\n> ����ǰѡ���Ļ���Ϊ��%s <\n", roster[current_id].name);
		else printf("                           ע�⣬����ǰ��δѡ������\n");
	}
	if (target == 2)
	{
		if (compare_id > 0 && compare_id <= sum_roster)
			printf("\n> ����ǰѡ���ıȽϻ���Ϊ��%s <\n", roster[compare_id].name);
		else printf("                           ע�⣬����ǰ��δѡ���Ƚϻ���\n");
	}
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("                      > ---����1���ڿ�����б���ѡȡ����--- <\n\n");
	printf("                      > ---����2�Ի��������йؼ��ּ���--- <\n\n");
	printf("                      > ---���������ַ�������һ��ѡ��------ <\n");
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("��ѡ��");
	rewind(stdin);
	scanf("%c", &move);
	switch (move)
	{
	case 49:
		print_roster();
		printf("\n������Ŀ��DNA���е�ϵͳ��ţ��������num��������0�����ϼ��˵���");
		scanf("%d", &tmp_id); fflush(stdin);//ͨ�����յ�ǰ�ڿ�����ѡȡ����
		if(tmp_id==0) goto Back_5;
		if (tmp_id > sum_roster || tmp_id <= 0)
		{
			printf("����Խ�磡����������롣\n");
			tmp_id = 0;
		}
		break;
	case 50:tmp_id = search(); break; //ͨ�����ҹؼ���ѡȡ���򣬾����search����
	default:rewind(stdin); return; break;
	}
	if (target == 1) current_id = tmp_id;
	if (target == 2) compare_id = tmp_id;
	rewind(stdin);	 //VS2019��fflush(stdin)��ʧЧ���ʲ�ȡ�÷�����ջ�����
	return;
}
void gene_lookup_menu() //�����������˵�
{
	char move;
Back_4:
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("                      ****�Ե�ǰ�������н��в鿴�����****\n");
	/*��ʾ��ǰ�Ƿ�ѡ����������ѡ�������ٽ��к�����������δѡȡ������ѡȡ��������������޷���*/
	if (current_id > 0 && current_id <= sum_roster)
		printf(">����ǰѡ���Ļ���Ϊ��%s <\n", roster[current_id].name);
	else printf("                      > ����ǰ��δѡ������<\n");
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("                      > ---����1��ȡ��ǰ����������Ϣ-------------------- <\n\n");
	printf("                      > ---����2(����)ѡ�����������Ϣ-------------------- <\n\n");
	printf("                      > ---����3�Ե�ǰ���н�������øλ����------------ <\n\n");
	printf("                      > ---����4�Ե�ǰ���н��з���---------------------- <\n\n");
	printf("                      > ---����5�Ե�ǰ��������һָ�����н���LCS���----- <\n\n");
	printf("                      > ---����6�Ե�ǰ��������һָ�����н���SES���----- <\n\n");
	printf("                      > ---����7�����뵱ǰѡ����������������ڿ�����---- <\n\n");
	printf("                      > ---���������ַ�������һ���˵�------ <\n");
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("��ѡ��");
	rewind(stdin);
	scanf("%c", &move);
	if (current_user.privilege < 0 && (move >= 50 && move <= 55))
	{
		printf("��������ǰΪ�ÿ�ģʽ����ע���ʹ���������ܡ�\n\n");
		system("pause");
		rewind(stdin);
		goto Back_4;
	}
	if ((current_id <= 0 || current_id > sum_roster) && (move >= 51 && move <= 55))
	{
		printf("> ����ǰ��δѡ�������޷�ִ������������<\n"); //��δѡȡ�������޷�ִ�в���
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
	case 50:search_menu(1); system("pause"); goto Back_4; break; //����ѡȡ����
	case 51:cut_check(current_id); system("pause"); goto Back_4; break;//����ø���
	case 52:translate(current_id); system("pause"); goto Back_4; break;//ת¼-����
	case 53:search_menu(2); LCS(current_id, compare_id, 0);  break;//LCS����
	case 54:search_menu(2); SES(current_id, compare_id, 0); system("pause"); break;//SES����
	case 55:max_similarity(current_id); system("pause"); break;//������ƶȼ��㣨���Ϲ��ܾ����������
	default:return; break;
	}
}
void account_menu()//һ���û����˺Ź������
{
	char move;
Back_3:
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("                                 ****�˺Ź���****\n");
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("                      > ---����1�����޸ĵ�ǰ�˻��������------ <\n\n");
	printf("                      > ---����2���뵱ǰ�û�Ȩ����֤����------ <\n\n");
	printf("                      > ---���������ַ�������һ���˵�------ <\n");
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("��ѡ��");
	rewind(stdin);
	scanf("%c", &move);
	switch (move)
	{
	case 49:password_change(); system("pause"); goto Back_3; break;//�޸�����
	case 50:auth_change(); system("pause"); goto Back_3; break;//���û������֤��󣬿ɽ���������֤
	default: return; break;//VS2019��fflush(stdin)��ʧЧ���ʲ�ȡ�÷�����ջ�����
	}
}
