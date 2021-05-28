#pragma once
void cut_check(gene load)
{
	int i,j,k,n=0;
	char tmp_f[9];
	char tmp_m[6];
	char tmp_b[7];
	char filename[100];
	sprintf(filename, "%s\\Tag-%s.txt",load.ID,load.name);
	FILE* fp = fopen(filename, "w");
	for (i = 0; i < load.l-11; i++)
	{
		if (load.seq[i] == 'A' && load.seq[i + 1] == 'C')
		{
			i = i + 7;
			if (load.seq[i] == 'C' && load.seq[i + 1] == 'T' && load.seq[i + 2] == 'C' && load.seq[i + 3] == 'C')
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
					tmp_f[k] = load.seq[j];
				}
				tmp_f[k] = '\0';
				j = i + 4;
				for (k = 0; k < 6; k++,j++)
				{
					tmp_b[k] = load.seq[j];
				}
				tmp_b[k] = '\0';
				fprintf(fp, ">Tag-%d\n", n);
				fprintf(fp, "%sAC%sCTCC%s\n", tmp_f, tmp_m, tmp_b);
			}
			i = i - 7;
		}
	}
	fclose(fp);
	printf("检测到%d个限制酶切割位点，已保存至%s中。\n\n",n,filename);
}