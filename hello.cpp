#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
void dd(vector<int> &v, vector<int> &w, int l, int r,int *k,int *id)
{

}
int main()
{
	vector<int> v(100);
	for(int i = 1 ; i <= 100 ; i++)
	{
		v[100-i] = i;
	}
	vector<int> w = v;
	sort(w.begin(),w.end());
	int l = (100/3);
	int r = (200/3);
	int k = 0;
	int id = 0;
	dd(v,w,l,r, &k, &id);
	cout<<k<<endl;
}
50
