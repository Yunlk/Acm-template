#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define T true
#define F false
//现在的你没有刷新缓冲区！需要请fflush(stdout)；
#define endl '\n' 
#define MOD1 1000000007
#define MOD2 998244353
int dx[] = { 1,1,1,0,0,-1,-1,-1 };
int dy[] = { -1,0,1,-1,1,-1,0,1 };
const int MAX_M = 200005;

//抄来的计时器：tick() 打点，tock() 返回毫秒
auto _t0 = chrono::high_resolution_clock::now();
void tick() 
{ 
    _t0 = chrono::high_resolution_clock::now(); 
}
ll tock() 
{
    return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - _t0).count();
}
//结构体
struct node
{
    ll i;
    double d;
    string s;
    bool b;
    char c;
};
//大数运算
string add(string a, string b)
{
    int lena = a.size();
    int lenb = b.size();
    int len = max(lena, lenb);
    vector<int> A(lena);
    vector<int> B(lenb);
    for (int i = 0; i < lena; ++i)
        A[i] = a[lena - 1 - i] - '0';
    for (int i = 0; i < lenb; ++i)
        B[i] = b[lenb - 1 - i] - '0';
    vector<int> out(len + 1, 0);
    for (int i = 0; i < len; ++i)
    {
        if (i < lena)
            out[i] += A[i];
        if (i < lenb)
            out[i] += B[i];
        out[i + 1] += out[i] / 10;
        out[i] %= 10;
    }
    while (len > 0 && out[len] == 0)
        --len;
    string res;
    for (int i = len; i >= 0; --i)
        res += (char)(out[i] + '0');
    return res.empty() ? "0" : res;
}
string mul(string a, string b)
{
    int lena = a.size();
    int lenb = b.size();
    vector<int> A(lena);
    vector<int> B(lenb);
    for (int i = 0; i < lena; ++i)
        A[i] = a[lena - 1 - i] - '0';
    for (int i = 0; i < lenb; ++i)
        B[i] = b[lenb - 1 - i] - '0';
    vector<int> C(lena + lenb, 0);
    for (int i = 0; i < lena; ++i)
        for (int j = 0; j < lenb; ++j)
            C[i + j] += A[i] * B[j];

    for (int i = 0; i < (int)C.size() - 1; ++i)
    {
        C[i + 1] += C[i] / 10;
        C[i] %= 10;
    }

    int len = C.size();
    while (len > 1 && C[len - 1] == 0)
        --len;
    string res;
    for (int i = len - 1; i >= 0; --i)
        res += (char)(C[i] + '0');
    return res.empty() ? "0" : res;
}
//快速幂a^b%mod
ll qpow(ll a, ll b, ll mod)
{
    ll res = 1 % mod;
    while (b)
    {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
//GCD/LCM
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
//有向计数（每对双向各算一次）
ll neighbor_sum(ll n, ll m, ll target, int grid[][MAX_M])
{
    ll ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < 8; k++)
            {
                ll ni = i + dx[k], nj = j + dy[k];
                if (ni >= 0 && ni < n && nj >= 0 && nj < m && grid[ni][nj] == target)
                    ans++;
            }
    return ans;
}
//无向计数（每对只算一次）
ll neighbor_sum_undirected(ll n, ll m, ll target, int grid[][MAX_M])
{
    return neighbor_sum(n, m, target, grid) / 2;
}
//DFS
void dfs_pick(int pos, int n, int k, int cnt, int sum, int a[], int& ans)
{
    if (cnt == k)
    {
        //if (check(sum)) 
        //ans++;
        return;
    }
    if (pos == n) return;

    dfs_pick(pos + 1, n, k, cnt + 1, sum + a[pos], a, ans);
    dfs_pick(pos + 1, n, k, cnt, sum, a, ans);
}
//int ans = 0; dfs_pick(0, n, k, 0, 0, a, ans);
//组合数学
//模逆元
ll modinv(ll a, ll mod)
{
    return qpow(a, mod - 2, mod);
}
//组合数学初始化
ll fac[MAX_M], invfac[MAX_M];
void pre_fac(ll mod)
{
    fac[0] = 1;
    for (int i = 1; i < MAX_M; i++)
        fac[i] = fac[i - 1] * i % mod;
    invfac[MAX_M - 1] = modinv(fac[MAX_M - 1], mod);
    for (int i = MAX_M - 2; i >= 0; i--)
        invfac[i] = invfac[i + 1] * (i + 1) % mod;
}
//组合数 C(n, r) % mod
ll C(ll n, ll r, ll mod)
{
    if (r < 0 || r > n)
        return 0;
    return fac[n] * invfac[r] % mod * invfac[n - r] % mod;
}
//排列数 A(n, r) % mod
ll A(ll n, ll r, ll mod)
{
    if (r < 0 || r > n)
        return 0;
    return fac[n] * invfac[n - r] % mod;
}
//卡特兰数 Catalan(n) = C(2n, n) / (n + 1)
ll catalan(ll n, ll mod)
{
    return C(2 * n, n, mod) * modinv(n + 1, mod) % mod;
}
//wdf，is 埃筛！：返回 [2, n] 所有质数，同时可以直接 isp[x] 判质数
vector<ll> get_primes(ll n)
{
    vector<bool> isp(n + 1, true);
    vector<ll> primes;
    isp[0] = isp[1] = false;
    for (ll i = 2; i <= n; i++)
    {
        if (!isp[i])
            continue;
        primes.push_back(i);
        if (i * i > n)
            continue;
        for (ll j = i * i; j <= n; j += i)
            isp[j] = false;
    }
    return primes;
}
//提前筛好，之后 O(1) 查
vector<bool> _isp;
void init_sieve(ll n)
{
    _isp.assign(n + 1, true);
    _isp[0] = _isp[1] = false;
    for (ll i = 2; i <= n; i++)
    {
        if (!_isp[i])
            continue;
        if (i * i > n)
            continue;
        for (ll j = i * i; j <= n; j += i)
            _isp[j] = false;
    }
}
bool is_prime(ll n)
{
    return n >= 0 && n < (ll)_isp.size() ? _isp[n] : false;
}
//KMP：返回 p 在 s 中所有匹配的起始位置
vector<int> kmp(string& s, string& p)
{
    int n = s.size(), m = p.size();
    vector<int> nxt(m, -1), res;
    for (int i = 1, j = -1; i < m; i++)
    {
        while (j >= 0 && p[i] != p[j + 1])
            j = nxt[j];
        if (p[i] == p[j + 1])
            j++;
        nxt[i] = j;
    }
    for (int i = 0, j = -1; i < n; i++)
    {
        while (j >= 0 && s[i] != p[j + 1])
            j = nxt[j];
        if (s[i] == p[j + 1])
            j++;
        if (j == m - 1)
        {
            res.push_back(i - m + 1);
            j = nxt[j];
        }
    }
    return res;
}
//一维前缀和：sum(l, r) = pre[r + 1] - pre[l]
vector<ll> prefix_sum(vector<ll>& a)
{
    int n = a.size();
    vector<ll> pre(n + 1, 0);
    for (int i = 0; i < n; i++)
        pre[i + 1] = pre[i] + a[i];
    return pre;
}
//二维前缀和
vector<vector<ll>> prefix_sum_2d(vector<vector<ll>>& a)
{
    int n = a.size(), m = a[0].size();
    vector<vector<ll>> pre(n + 1, vector<ll>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + a[i - 1][j - 1];
    return pre;
}
//简单DP
//最大子段和
ll max_subarray(vector<ll>& a)
{
    ll cur = 0, ans = a[0];
    for (ll x : a)
    {
        cur = max(x, cur + x);
        ans = max(ans, cur);
    }
    return ans;
}
//01 背包：每个物品最多选一次，求最大价值
//w[i]重量, v[i]价值, n物品数, W容量
ll knapsack_01(vector<ll>& w, vector<ll>& v, int n, int W)
{
    vector<ll> dp(W + 1, 0);
    for (int i = 0; i < n; i++)
        for (int j = W; j >= w[i]; j--)       // 倒序
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    return dp[W];
}
//完全背包：每个物品无限个，求最大价值
ll knapsack_full(vector<ll>& w, vector<ll>& v, int n, int W)
{
    vector<ll> dp(W + 1, 0);
    for (int i = 0; i < n; i++)
        for (int j = w[i]; j <= W; j++)       // 正序
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    return dp[W];
}
//一些差分
//一维 要prefix_sum(vector<ll>& a)前缀和
void diff_add(vector<ll>& d, int l, int r, ll v) 
{ 
    d[l] += v; d[r + 1] -= v;
}
//二维
void diff2d_add(vector<vector<ll>>& d, int x1, int y1, int x2, int y2, ll v) 
{
    d[x1][y1] += v;
    d[x2 + 1][y1] -= v;
    d[x1][y2 + 1] -= v;
    d[x2 + 1][y2 + 1] += v;
}
void diff2d_recover(vector<vector<ll>>& d, int n, int m) 
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            d[i][j] += d[i - 1][j] + d[i][j - 1] - d[i - 1][j - 1];
}
int main()
{
    tick();
    ios::sync_with_stdio(F);
    cin.tie(0);
    cout.tie(0);
    //组合数学初始化
    //pre_fac(mod);
    //质数筛初始化
    //init_sieve(NEED);
    //is_prime(NEED);

        // === 大数 ===
    cout << add("999", "1") << endl;
    cout << add("123", "456") << endl;
    cout << mul("123", "456") << endl;

    // === 快速幂 ===
    cout << qpow(2, 10, MOD1) << endl;
    cout << qpow(3, 0, MOD1) << endl;

    // === GCD / LCM ===
    cout << gcd(12, 18) << " " << lcm(12, 18) << endl;

    // === 埃筛 ===
    init_sieve(30);
    for (int i = 2; i <= 30; i++)
        if (is_prime(i)) cout << i << " ";
    cout << endl;
    auto primes = get_primes(30);
    for (auto p : primes) cout << p << " ";
    cout << endl;

    // === KMP ===
    string s = "ababababc", p = "ababc";
    for (auto x : kmp(s, p)) cout << x << " ";
    cout << endl;
    string s2 = "aaa", p2 = "aa";
    for (auto x : kmp(s2, p2)) cout << x << " ";
    cout << endl;

    // === 前缀和 ===
    vector<ll> a = { 1,2,3,4,5 };
    auto pre = prefix_sum(a);
    cout << pre[5] - pre[1] << endl;  // sum[1..4] = 14

    // === 二维前缀和 ===
    vector<vector<ll>> b = { {1,2,3},{4,5,6},{7,8,9} };
    auto pre2 = prefix_sum_2d(b);
    cout << pre2[3][3] << endl;  // 45

    // === DP ===
    vector<ll> c = { -2,1,-3,4,-1,2,1,-5,4 };
    cout << max_subarray(c) << endl;  // 6

    vector<ll> w = { 2,3,4 }, v = { 3,4,5 };
    cout << knapsack_01(w, v, 3, 7) << endl;   // 9
    cout << knapsack_full(w, v, 3, 7) << endl; // 10

    // === 组合 ===
    pre_fac(MOD1);
    cout << C(5, 2, MOD1) << endl;      // 10
    cout << A(5, 2, MOD1) << endl;      // 20
    cout << catalan(3, MOD1) << endl;  // 5

    // === 差分 1D ===
    vector<ll> d1(7, 0);
    diff_add(d1, 1, 3, 5);
    auto r1 = prefix_sum(d1);
    cout << r1[2] << " " << r1[3] << " " << r1[4] << endl;  // 5 5 5

    // === 差分 2D ===
    vector<vector<ll>> d2(6, vector<ll>(6, 0));
    diff2d_add(d2, 1, 1, 3, 3, 1);
    diff2d_add(d2, 2, 2, 4, 4, 1);
    diff2d_recover(d2, 5, 5);
    cout << d2[1][1] << " " << d2[2][2] << " " << d2[4][4] << endl;  // 1 2 1

    // === DFS ===
    int arr[] = { 1,2,3,4,5 }, ans = 0;
    dfs_pick(0, 5, 3, 0, 0, arr, ans);

    // === 计时器 ===
    cerr << tock() << " ms" << endl;
}