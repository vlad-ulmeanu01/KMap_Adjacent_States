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

const int maxn = 16, max_pos = 5;
int tab[4][4];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

int bpop (int x) {
  return __builtin_popcount(x);
}

int gray (int x) { ///x=0/1/2/3
  if (x < 2) return x;
  return 2 + ((x-2)^1);
}

int norm (int x) {
  if (x >= 4) x -= 4;
  if (x < 0) x += 4;
  return x;
}

void fill_tab (vi &ord) {
  for (int i = 0; i < maxn; i++)
    tab[gray(i/4)][gray(i%4)] = ord[i];
}

void delu (set<pii> &s2, int x, int y) {
  if (x > y) swap(x, y);
  auto it = s2.find(pii(x, y));
  if (it != s2.end()) s2.erase(it);
}

int run_tab (set<pii> &s1) {
  set<pii> s2 = s1;
  int i, j, z;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (z = 0; z < 4; z++) delu(s2, tab[i][j], tab[norm(i+dx[z])][norm(j+dy[z])]);
  return sz(s2);
}

vector<vi> d[(1<<maxn)+5];

int main () {
  ifstream cfg ("cfg.txt");
  int n, m; cfg >> n >> m; ///noduri, muchii
  int i, j, z, a, b;
  set<pii> s1;
  for (i = 0; i < m; i++) {
    cfg >> a >> b; ///muchiile pe care as vrea sa le am
    if (a > b) swap(a, b);
    s1.insert(pii(a, b));
  }
  cfg.close();
  vi ord(maxn, -1);
  d[0].pb(ord);
  int conf, conn;
  for (conf = 1; conf < (1<<n); conf++) {
    if (conf % 160 == 0) cerr << conf << '\n';
    for (i = 0; i < n; i++)
      if (conf & (1<<i)) {
        conn = (conf ^ (1<<i));
        for (vi v: d[conn]) {
          for (j = 0; j < maxn; j++) {
            if (v[j] == -1) {
              v[j] = i;
              fill_tab(v);
              int scor = run_tab(s1);
              v.pb(scor); ///pun pe ultima pozitie "scor" temporar ca sa pot sa sortez ulterior
              d[conf].pb(v);
              v.pop_back();
              v[j] = -1;
            }
          }
        }
      }
    sort(all(d[conf]), [](vi &a, vi &b) { return a.back() < b.back(); });
    if (sz(d[conf]) > max_pos) d[conf].resize(max_pos);
    for (vi &v: d[conf]) v.pop_back(); ///scot pozitia cu scorul.
  }
  fill_tab(d[(1<<n)-1][0]);
  for (i = 0; i < 4; i++, cout << '\n')
    for (j = 0; j < 4; j++) cout << tab[i][j] << ' ';
  cout << "muchii ramase: " << run_tab(s1) << '\n';
  return 0;
}
