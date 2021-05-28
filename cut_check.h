#pragma once
void cut_check(int id)
{
	gene load = load_from_base(id, 1);//根据id从库中加载基因序列的详细信息
	int i,j,k,n=0;
	char tmp_f[9];//f-front
	char tmp_m[6];//m-middle
	char tmp_b[7];//b-back————对位点附近序列的暂存
	char filename[200];
	printf("\n------正在检测%s的酶切位点……------\n",load.name);
	sprintf(filename, "genebase\\%s\\Tag-%s.txt",load.ID,load.name);
	FILE* fp = fopen(filename, "w");
	for (i = 0; i < load.l-11; i++)
	{
		if (load.seq[i] == 'A' && load.seq[i + 1] == 'C')
		{
			i = i + 7;
			if (load.seq[i] == 'C' && load.seq[i + 1] == 'T' && load.seq[i + 2] == 'C' && load.seq[i + 3] == 'C')
				//根据限制酶切割位点的检索
			{
				n++;
				j = i - 5;
				for (k = 0; k < 5; k++,j++)
				{
					tmp_m[k]= load.seq[j];
				}
				tmp_m[k] = '\0';
				j = i - 15;
				for (k = 0; k < 8; k++,j++)
				{
					tmp_f[k] = load.seq[j];//位点附近序列的暂存
				}
				tmp_f[k] = '\0';
				j = i + 4;
				for (k = 0; k < 6; k++,j++)
				{
					tmp_b[k] = load.seq[j];//位点附近序列的暂存
				}
				tmp_b[k] = '\0';
				fprintf(fp, ">Tag-%d\n", n);
				fprintf(fp, "%sAC%sCTCC%s\n", tmp_f, tmp_m, tmp_b);//写入Tag文件
			}
			i = i - 7;//返回继续检测
		}
	}
	fclose(fp);
	printf("成功：检测到%d个限制酶切割位点，已保存至%s中。\n\n",n,filename);
}