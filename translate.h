#pragma once
typedef struct amino_acid
{
	char name[4];
	int n;
}amino;
void q_sort_amino(amino* l, amino* r)
{
	if (l >= r) return;
	amino* i = l, * j = r;
	amino x = *i;
	while (i < j)
	{
		while ((i < j) && (x.n <= (*j).n)) j--;
		if (i < j)
		{
			(*i).n = (*j).n;
			strcpy((*i).name, (*j).name);
			i++;
		}
		while ((i < j) && ((*i).n <= x.n)) i++;
		if (i < j)
		{
			(*j).n = (*i).n;
			strcpy((*j).name, (*i).name);
		}
		*i = x;
		q_sort_amino(l, i - 1);
		q_sort_amino(i + 1, r);
	}
}
char* transcribe(gene load)
{
	int i,j;
	char* RNA=NULL;
	RNA = (char*)malloc((load.l+2) * sizeof(char));
	if (RNA == NULL)
	{
		printf("Error:Unsuccessful memory allocation for +RNA sequences!\n");
		return NULL;
	}
	RNA[0] = load.l;
	for (i = 1,j = 0; i <= load.l; i++,j++)
	{
		switch (load.seq[j])
		{
		case'A':RNA[i] = 'U'; break;
		case'T':RNA[i] = 'A'; break;
		case'G':RNA[i] = 'C'; break;
		case'C':RNA[i] = 'G'; break;
		}
	}
	RNA[i] = '\0';
	printf("+RNA序列已成功获取。\n\n");
	return RNA;
}

int translate(gene load)
{
	int i, n = 0;
	int flag = 0;
	char* RNA = NULL;
	RNA = transcribe(load);
	int Ala = 0, Cys = 0, Asp = 0, Glu = 0, Phe = 0, Gly = 0, His = 0, Ile = 0, Lys = 0, Leu = 0, Met = 0, Asn = 0, Pro = 0, Gln = 0, Arg = 0, Ser = 0, Thr = 0, Val = 0, Trp = 0, Tyr = 0;
	char filename[100];
	sprintf(filename, "%s\\Peptides-%s.txt",load.ID,load.name);
	FILE *fp=fopen(filename, "w");
	fprintf(fp, "Peptide Chain List");
	for (i = 1; i < load.l + 1; i++)
	{
		if (((RNA[i] == 'A') || (RNA[i] == 'G')) && (RNA[i + 1] == 'U') && (RNA[i + 2] == 'G')) //Check Starter
		{
			n++;
			fprintf(fp, "\n>Peptide-No.%d; Start at %d\n", n, i);
			do
			{
				flag = 0;
				switch (RNA[i])
				{
				case 'U':
					switch (RNA[i + 1])
					{
					case 'U':
						switch (RNA[i + 2])
						{
						case 'U':
						case 'C':Phe++; fprintf(fp,"Phe"); break;
						case 'A':
						case 'G':Leu++; fprintf(fp, "Leu"); break;
						}
						break;
					case 'C': Ser++; fprintf(fp, "Ser"); break;
					case 'A':
						switch (RNA[i + 2])
						{
						case 'U':
						case 'C':Tyr++; fprintf(fp, "Tyr"); break;
						case 'A':
						case 'G':flag = 1; fprintf(fp, "\nEnd at %d\n",i); break;
						}
						break;
					case 'G':
						switch (RNA[i + 2])
						{
						case 'U':
						case 'C':Cys++; fprintf(fp, "Cys"); break;
						case 'A':flag = 1; fprintf(fp, "\nEnd at %d\n", i);  break;
						case 'G':Trp++; fprintf(fp, "Trp"); break;
						}
						break;
					}
					break;
				case 'C':
					switch (RNA[i + 1])
					{
					case 'U':Leu++; fprintf(fp, "Leu"); break;
					case 'C':Pro++; fprintf(fp, "Pro"); break;
					case 'A':
						switch (RNA[i + 2])
						{
						case 'U':
						case 'C':His++; fprintf(fp, "His"); break;
						case 'A':
						case 'G':Gln++; fprintf(fp, "Gln"); break;
						}
						break;
					case 'G':Arg++; fprintf(fp, "Arg"); break;
					}
					break;
				case 'A':
					switch (RNA[i + 1])
					{
					case 'U':
						switch (RNA[i + 2])
						{
						case 'U':
						case 'C':
						case 'A':Ile++; fprintf(fp, "Ile"); break;
						case 'G':Met++; fprintf(fp, "Met"); break;
						}
						break;
					case 'C':Thr++; fprintf(fp, "Thr"); break;
					case 'A':
						switch (RNA[i + 2])
						{
						case 'U':
						case 'C':Asn++; fprintf(fp, "Asn"); break;
						case 'A':
						case 'G':Lys++; fprintf(fp, "Lys"); break;
						}
						break;
					case 'G':
						switch (RNA[i + 2])
						{
						case 'U':
						case 'C':Ser++; fprintf(fp, "Ser"); break;
						case 'A':
						case 'G':Arg++; fprintf(fp, "Arg"); break;
						}
						break;
					}
					break;
				case 'G':
					switch (RNA[i + 1])
					{
					case 'U':
						switch (RNA[i + 2])
						{
						case 'U':
						case 'C':
						case 'A':Val++; fprintf(fp, "Val"); break;
						case 'G':Val++; fprintf(fp, "Val"); break;
						}
						break;
					case 'C':Ala++; fprintf(fp, "Ala"); break;
					case 'A':
						switch (RNA[i + 2])
						{
						case 'U':
						case 'C':Asp++; fprintf(fp, "Asp"); break;
						case 'A':
						case 'G':Glu++; fprintf(fp, "Glu"); break;
						}
						break;
					case 'G':Gly++; fprintf(fp, "Gly"); break;
					}
					break;
				default: printf("错误：检测到错误碱基，请检查读取序列是否正确。"); return -1; break;
				}
				i = i + 3;
			} while (flag == 0);
			i = i - 1;
		}
	}
	fprintf(fp, "\n\n\nSource +RNA:\n%s\n", &RNA[1]);
	amino a[20] = {
		{"Ala",Ala},
		{"Cys",Cys},
		{"Asp",Asp},
		{"Glu",Glu},
		{"Phe",Phe},
		{"Gly",Gly},
		{"His",His},
		{"Ile",Ile},
		{"Lys",Lys},
		{"Leu",Leu},
		{"Met",Met},
		{"Asn",Asn},
		{"Pro",Pro},
		{"Gln",Gln},
		{"Arg",Arg},
		{"Ser",Ser},
		{"Thr",Thr},
		{"Val",Val},
		{"Trp",Trp},
		{"Tyr",Tyr},
	};
	q_sort_amino(&a[0],&a[19]);
	fprintf(fp, "\nAmino Acids Statistics:\n");
	for (i = 19; i >= 0; i--)
	{
		fprintf(fp, "\nName:%s;Count:%d\n", a[i].name, a[i].n);
	}
	fclose(fp);
	printf("翻译成功！各肽链情况，整体氨基酸统计数据与+RNA数据已保存至%s，请查看。\n\n",filename);
}