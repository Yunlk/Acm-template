# Acm-template

ACM / OI 算法竞赛 C++ 模板。

## 内容

### 宏定义

```cpp
#define ll long long int
#define T true
#define F false
#define MOD1 1000000007
#define MOD2 998244353
```

### 方向数组

```cpp
int dx[] = { 1,1,1,0,0,-1,-1,-1 };
int dy[] = { -1,0,1,-1,1,-1,0,1 };
```

八邻域，用于 `neighbor_sum` 和网格遍历。

### 结构体

```cpp
struct node { ll i; double d; string s; bool b; char c; };
```

### 大数加法

```cpp
string add(string a, string b);
// add("123", "456") → "579"
```

### 大数乘法

```cpp
string mul(string a, string b);
// mul("123", "456") → "56088"
```

### 快速幂

```cpp
ll qpow(ll a, ll b, ll mod);
// qpow(2, 10, MOD1) → 1024
```

### GCD / LCM

```cpp
ll gcd(ll a, ll b);   // gcd(12, 18) → 6
ll lcm(ll a, ll b);   // lcm(12, 18) → 36
```

### 八邻域计数

```cpp
// 有向（每对双向各算一次）
ll neighbor_sum(n, m, target, grid);

// 无向（每对只算一次）
ll neighbor_sum_undirected(n, m, target, grid);
```

### DFS 组合选择

```cpp
void dfs_pick(int pos, int n, int k, int cnt, int sum, int a[], int& ans);
// 从 n 个数中选 k 个，遍历所有组合
// 用法：int ans = 0; dfs_pick(0, n, k, 0, 0, a, ans);
```

## 编译

需要支持 `bits/stdc++.h` 的编译器（MinGW GCC 推荐）。

## License

MIT-这也有人用？
