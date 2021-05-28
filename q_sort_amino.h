#pragma once
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