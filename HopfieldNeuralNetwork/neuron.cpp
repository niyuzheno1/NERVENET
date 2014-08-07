// neuron.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define N 10
class neuron{
public: int state;
		neuron()
		{
	     int r = rand()%2;
		 state = r?1:(-1);
		}
		bool changestate(double field)
		{
			bool res = false;
			if(field * double(state) < 0)
			{
				this->state = -this->state;
				res = true;
			}
			return res;
		}
};
int mp[N+2][N+2];
int n;
void changeinput(int i)
{
	int x = (i%n == 0 )? (i/n):((i/n)+1);
	int y = i - (x-1)*n;
	mp[x][y] ^= 1;
}
class neuralnetwork{
public:
	vector<neuron> neurons;
	int n,m;
	double e;
	int T[N+2][N+2];
	void calculateenergy()
	{
		double tempE = 0;
		for(int i = 1;i<=n;++i)
			 for(int j = 1;j<=n;++j)
				  if(i != j)
					   tempE += T[i][j] * neurons[i].state *  neurons[j].state;
	    e = -1*tempE/2;
	}
	neuralnetwork(int _n){
	  n = _n;
	  for(int i = 0;i<=n;++i)
	  {
		  neuron tmp;
		  tmp.state = 0;
		  neurons.push_back(tmp);
	  }
	  int m = 0;
	  for(int i = 1;i<=n;++i)
		   for(int j = 1;j<=n;++j)
			    T[i][j] = 0;
	}
	void addpattern(const vector<neuron> & pat){
	    for(int i = 1;i<=n;++i)
			 for(int j = 1;j<=n;++j)
			 {
				 if(i == j) T[i][j] = 0;
				 else T[i][j] += pat[i].state*pat[j].state;
			 }
		++m;
	}
	void run(vector<neuron> & initstate)
	{
		this->neurons = initstate;
		int k = 1;
		int h = 0;
		while(k != 0)
		{
			k = 0;
			for(int i = 1;i<=n;++i)
			{
				h = 0;
				for(int j = 1;j<=n;++j)
					 h += T[i][j] * neurons[j].state;
				if(neurons[i].changestate(h))
				{
				 ++k;
				 calculateenergy();
				 changeinput(i);
				}
			}
		}
		calculateenergy();
	}
};
neuralnetwork * global;
int _tmain(int argc, _TCHAR* argv[])
{
	n = 2;
	FILE* patfile = fopen("pat.txt","r");
    global = new neuralnetwork(n*n);
#define fr fscanf(patfile,
	int np = 0;
	fr "%d",&np);
	for(int i = 1;i<=np;++i)
	{
		vector<neuron> msg;msg.push_back(neuron());
		 for(int j = 1;j<=n;++j)
			  for(int k = 1;k<=n;++k)
			  {
				  int u = 0;
				  fr "%d",&u);
				  neuron now;
				  if(u == 1)
					  now.state = -1;
				  else 
					  now.state = 1;
				  msg.push_back(now);
			  }
		global->addpattern(msg);
	}
#undef fr
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
    int m;
	scanf("%d",&m);
	for(int i = 1;i<=m;++i)
	{
		vector<neuron> msg;msg.push_back(neuron());
		for(int j = 1;j<=n;++j)
			for(int k = 1;k<=n;++k)
			{
				scanf("%d",&mp[j][k]);
				neuron now;
				  if(mp[j][k] == 1)
					  now.state = -1;
				  else 
					  now.state = 1;
				  msg.push_back(now);
			}
		global->run(msg);
		for(int j = 1;j<=n;printf("\n"),++j)
			for(int k = 1;k<=n;++k)
				printf("%d ",mp[j][k]);
	}
	fclose(stdout);
	return 0;
}

