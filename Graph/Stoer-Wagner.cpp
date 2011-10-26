#include <iostream>
#include <cstring>

using namespace std;

const int maxN = 400;
const int inf = 1 << 30;
bool Box[maxN], Deleted[maxN];
int w[maxN][maxN];
int MM[maxN];
int N, mS, mT, ans;

void st_mincut(int remain)
{
	int i, j, t;
	for (i = 0; i < N; i++)
		Box[i] = Deleted[i];
	memset(MM, 0, sizeof(MM));
	for (i = 0; i < remain - 1; i++)
	{
		t = -1;
		for (j = 0; j < N; j++)
			if (!Box[j] && (t == -1 || MM[t] < MM[j]))
				t = j;
		Box[t] = true;
		for (j = 0; j < N; j++)
			if (!Box[j])
				MM[j] += w[t][j];
	}
	mS = t;
	for (i = 0; i < N; i++)
		if (!Box[i])
		{
			mT = i;
			break;
		}
	if (MM[mT] < ans)
		ans = MM[mT];
}

void Contract(int S, int T)
{
	for (int i = 0; i < N; i++)
		if (!Deleted[i] && i != S && i != T)
			w[S][i] = w[i][S] += w[i][T];
	Deleted[T] = true;
}

int Stoer_Wagner()
{
	ans = inf;
	memset(Deleted, 0, sizeof(Deleted));
	for (int i = 0; i < N - 1; i++)
	{
		st_mincut(N - i);
		Contract(mS, mT);
	}
	return ans;
}