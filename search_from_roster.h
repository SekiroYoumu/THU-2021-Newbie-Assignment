#pragma once
int search()
{
	int t=0;//ѡ��ؼ�������
	int i = 0;//ѭ������
	int n = 0;//�������ı���
	int m = 0;//����ɸѡѡ���id
	bool flag = 0;//�Ƿ��ҵ���flag
	int result = 0;//����ѡ���Ľ��
	char* now;//ָ����Ҷ����ָ��
	char target[51];//�ؼ���
	char* needle;      //����ָ���Ա���Сдת��
	char now_buf[200];//�����������Ա���Сдת��
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("                                 ****�ؼ��ֲ���****\n������������������������������������������������������������������������������������������������������\n                      >--- ����1�����������Ʋ��ң�����2������Դ���Ͳ��ң�---<\n\n                      >--- ����3���ղɼ��ص���ң�����4���ղ���������ң�---<\n\n                      >--- ����5���ղ��������ҡ�����6��������ͨ��ID���ҡ�-<\n\n                      >--- �����������ַ����ϼ��˵���---<\n");
	printf("������������������������������������������������������������������������������������������������������\n");
	printf("\n��ѡ��");
	scanf("%d", &t);
	rewind(stdin);
	if (t > 6 || t <= 0) return -1;
	int* result_id = (int*)malloc(sizeof(int) * (sum_roster));//����������Ŀ�������������ݴ������������������һ��ɸѡ
	printf("����������Ҫ���ҵĹؼ���(������50�ַ�)��");
	scanf("%s", target);
	rewind(stdin);
	needle = strlower(target);//��target�е��ַ�ȫ��ת��ΪСд������ͳһ��Сд��ʽ����
	for (i=1;i<=sum_roster;i++)
	{
		switch (t)//������ѡ�ؼ��־������Ҷ���ָ���ָ��
		{
		case 1:now = &roster[i].name; break;
		case 2:now = &roster[i].source; break;
		case 3:now = &roster[i].locale; break;
		case 4:now = &roster[i].ins; break;
		case 5:now = &roster[i].tech; break;
		case 6:now = &roster[i].ID; break;
		default:printf("Error��"); return NULL;
		}
		strcpy(now_buf, now);
		now = strlower(now_buf);//��nowָ����ַ����ַ�����now_buf�к��ٶ�now_bufת��ΪСд����ң�����Ӱ��ԭ����
		if (strstr(now, needle) != NULL)
		{
			result_id[n] = roster[i].id;
			printf("�ҵ���%d�����ݣ�ϵͳ�ڱ��Ϊ��%06d������Ϊ��%s\n", n+1 , roster[i].id,roster[i].name);
			n++;
			if (n > 1) flag = 1;
		}
	}
	if (flag == 1)
	{
		printf("����Ҫ�����ڼ���������Ϣ�������뱾����������ţ���������Ҫ��������0��ѡ�񽫻ᱻ���ã�");
		scanf("%d",&m);
		rewind(stdin);
		if (m == 0) return 0;
		result = result_id[m - 1];
	}
	else result = result_id[0];
	return result;
}