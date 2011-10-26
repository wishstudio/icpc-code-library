#include <cstring>

struct graph
{
	static const int infi = 2147483647;
	static const int maxn = 200; // Max node count
	int ux[maxn], uy[maxn], slack[maxn], w[maxn][maxn];
	int nlink[maxn], n; // node count
	bool visx[maxn], visy[maxn];
	
	void init()
	{
		memset(ux, 0, sizeof ux);
		memset(uy, 0, sizeof uy);
		memset(nlink, 0, sizeof nlink);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (w[i][j] > ux[i])
					ux[i] = w[i][j];
	}
	
	bool dfs(int u)
	{
		int t;
		visx[u] = true;
		for (int i = 1; i <= n; i++)
		if (!visy[i])
		{
			t = ux[u] + uy[i] - w[u][i];
			if (t == 0)
			{
				visy[i] = true;
				if ((nlink[i] == 0) || (dfs(nlink[i])))
				{
					nlink[i] = u;
					return true;
				}
			}
			else if (t < slack[i])
				slack[i] = t;
		}
		return false;
	}
	
	void work()
	{
		int i, j;
		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= n; j++)
				slack[j] = infi;
			while (1)
			{
				memset(visx, 0, sizeof(visx));
				memset(visy, 0, sizeof(visy));
				if (dfs(i))
					break;
				int d = infi;
				for (j = 1; j <= n; j++)
					if ((!visy[j]) && (slack[j] < d))
						d = slack[j];
				for (j = 1; j <= n; j++)
				{
					if (visx[j])
						ux[j] -= d;
					if (visy[j])
						uy[j] += d;
					else
						slack[j] -= d;
				}
			}
		}
	}
	
	int getans()
	{
		int ans = 0;
		for (int i = 1; i <= n; i++)
			ans += w[nlink[i]][i];
		return ans;
	}
};