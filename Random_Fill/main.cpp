#include <bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pli pair<ll,int>
#define pil pair<int,ll>
#define fi first
#define se second
#define inf (INT_MAX/2-1)
#define infl (1LL<<60)
#define vi vector<int>
#define vl vector<ll>
#define pb push_back
#define sz(a) (int)(a).size()
#define all(a) begin(a),end(a)
#define y0 y5656
#define y1 y7878
#define aaa system("pause");
#define dbg(x) cerr<<(#x)<<": "<<(x)<<'\n',aaa
#define dbga(x,n) cerr<<(#x)<<"[]: ";for(int _=0;_<n;_++)cerr<<x[_]<<' ';cerr<<'\n',aaa
#define dbgs(x) cerr<<(#x)<<"[stl]: ";for(auto _:x)cerr<<_<<' ';cerr<<'\n',aaa
#define dbgp(x) cerr<<(#x)<<": "<<x.fi<<' '<<x.se<<'\n',aaa

using namespace std;

const int maxn = 16;
int tab[4][4];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

int gray (int x) { ///x=0/1/2/3
  if (x < 2) return x;
  return 2 + ((x-2)^1);
}

int main () {
  ifstream cfg ("cfg.txt");
  int t; cfg >> t; /// numar de teste
  int n, m; cfg >> n >> m; ///noduri, muchii
  int i, j, z, a, b;
  set<pii> s1, s2;
  for (i = 0; i < m; i++) {
    cfg >> a >> b; ///muchiile pe care as vrea sa le am
    if (a > b) swap(a, b);
    s1.insert(pii(a, b));
  }
  cfg.close();

  srand(time(NULL));
  vi ord(maxn, -1);
  for (i = 0; i < n; i++) ord[i] = i;
  auto fill_tab = [&] (vi &ord) {
    for (int i = 0; i < maxn; i++)
      tab[gray(i/4)][gray(i%4)] = ord[i];
  };
  auto delu = [&] (int x, int y) {
    if (x > y) swap(x, y);
    auto it = s2.find(pii(x, y));
    if (it != s2.end()) s2.erase(it);
  };
  auto norm = [&] (int x) {
    if (x >= 4) x -= 4;
    if (x < 0) x += 4;
    return x;
  };
  int best = m+1;
  while (t--) {
    random_shuffle(all(ord));
    fill_tab(ord);
    s2 = s1;
    for (i = 0; i < 4; i++)
      for (j = 0; j < 4; j++)
        for (z = 0; z < 4; z++) delu(tab[i][j], tab[norm(i+dx[z])][norm(j+dy[z])]);
    if (best > sz(s2)) {
      for (i = 0; i < 4; i++, cerr << '\n')
        for (j = 0; j < 4; j++) cerr << tab[i][j] << ' ';
      best = sz(s2);
      dbg(best);
    }
  }
  return 0;
}
