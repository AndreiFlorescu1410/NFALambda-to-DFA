#include <iostream>
#include <string.h>
#include <fstream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

void avanseaza(char a[255][255][3], int inchiderea[255][255], int stare_initiala, int stare_curenta, int n) //functie ce-mi genereaza inchiderea starilor
{
	inchiderea[stare_initiala][stare_curenta] = 1;
	int i, j;
	for (i = 0; i < n; i++)
	{
		j = 0;
		while (a[stare_curenta][i][j] != 'l')
		{
			j++;
			if (j > 2 || a[stare_curenta][i][j-1] == 0)
				break;
		}
		if (a[stare_curenta][i][j] == 'l' && inchiderea[stare_initiala][i] == 0)
			avanseaza(a, inchiderea, stare_initiala, i, n);
	}

}


int main()
{

	int n, m, inchiderea[255][255] = { {0} }, finale[255];
	char cuvant[255], a[255][255][3] = { {'0'} };
	int i, j, k, l, x, y, nr;
	char b;
	ifstream f("input.in");
	f >> n >> nr;
	for (i = 1; i <= nr; i++) //citire din fisier
	{
		f >> x >> y >> b;
		j = 0;
		while (a[x][y][j] != 0)
			j++;
		a[x][y][j] = b;
	}
	f >> m;
	for (i = 1; i <= m; i++)
		f >> finale[i];
	for (i = 0; i < n; i++)
		avanseaza(a, inchiderea, i, i, n);	//apelez functia pentru inchiderea starilor


	int a_temp[255][255] = { {0} };
	int count;								//variabila pentru cazul in care am tranzitie cu mai mult de o litera
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (inchiderea[i][j] == 1)		//daca se poate ajunge din starea 'i' in starea 'j' prin λ-tranzitii
			{								// λ*
				for (k = 0; k < n; k++)
				{
					count = 0;
					while (a[j][k][count] != 0)
					{
						if (a[j][k][count] == 'a')			//daca pot avansa cu 'a'
							for (l = 0; l < n; l++)
							{
								if (inchiderea[k][l] == 1)	//completez circuitul λ*aλ*
									a_temp[2 * i][l] = 1;
							}
						else if (a[j][k][count] == 'b')
							for (l = 0; l < n; l++)
							{
								if (inchiderea[k][l] == 1)
									a_temp[2 * i + 1][l] = 1;
							}
						count++;
					}

							
				}

			}
		}
	}
	
	queue<int> coada;
	coada.push(0);		//adaug starea q0 in coada
	int p, p1, p2, stare_curenta[255] = { 0 };
	int a_nou[255][255] = { {0} };
	vector<int> vizitat;
	vizitat.push_back(0);
	bool ok;
	int n1, p_temp; 
	//ofstream g("output.out");
	while (!coada.empty())	//cat timp mai sunt stari in coada
	{
		p = coada.front();
		p_temp = p;
		n1 = 0;
		int stare_curenta[255] = { 0 }, stari_a[255] = { 0 }, stari_b[255] = { 0 };
		if (p == 0)			//daca e starea q0
		{
			stare_curenta[0] = 1;
			n1++;
		}
		while (p)				//cat timp mai sunt stari de vizitat(de ex, la q0123, am 4 stari de vizitat)
		{
			stare_curenta[p % 10] = 1;
			p /= 10;
			n1++;
		}
		for (i = 0; i < n; i++)	//adaug intr-un vector, starile adiacente starii curente
		{
			if (stare_curenta[i] == 1)
			{
				p1 = 0;
				for (j = 0; j < n; j++)
				{
					if (a_temp[2 * i][j])
					{
						a_nou[2 * i][j] = a_temp[2 * i][j];
						stari_a[j] = a_temp[2 * i][j];
					}
				}
				for (j = 0; j < n; j++)
				{
					if (a_temp[2 * i + 1][j])
					{
						a_nou[2 * i + 1][j] = a_temp[2 * i + 1][j];
						stari_b[j] = a_temp[2 * i + 1][j];
					}
				}
			}
		}
		p1 = 0, p2 = 0;
		for (j = 0; j < n; j++)	//formez noua stare dintr-un vector de forma [1 1 0 0 1] in q014
		{
			if (stari_a[j])
			{
				p1 *= 10;
				p1 += j;
			}
			if (stari_b[j])
			{
				p2 *= 10;
				p2 += j;
			}
		}
		cout << p_temp << " " << p1 << " " << p2 << endl;	// afisez starea curenta, si starile adiacente
		//g << p_temp << " " << p1 << " " << p2 << endl;	// sau, in fisier
		ok = 1;
		for (k = 0; k < vizitat.size(); k++)	//verific daca starea pe care vreau s-o adaug exista deja
		{										//pentru tranzitii 'a'
			if (p1 == vizitat[k])
				ok = 0;
		}
		if (ok)
		{
			coada.push(p1);
			vizitat.push_back(p1);
		}
		ok = 1;

		for (k = 0; k < vizitat.size(); k++)	//pentru tranzitii 'b'
		{				
			if (p2 == vizitat[k])
				ok = 0;
		}
		if (ok)
		{
			coada.push(p2);
			vizitat.push_back(p2);
		}
		coada.pop();
	}
	return 0;
}
