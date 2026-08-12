# Acm-template

ACM / OI 算法竞赛 C++ 模板。边学边补，C++14 兼容。

## 常量

```
#define ll long long int
#define endl '\n'       // 换行不 flush，需刷新用 fflush(stdout)
#define MOD1 1000000007   // 1e9 + 7
#define MOD2 998244353    // NTT 友好质数
```

## 方向数组

```
dx[] = { 1, 1, 1, 0, 0, -1, -1, -1 }
dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 }
```

---

## 大数运算

**add(a, b)** — 高精度加法
**mul(a, b)** — 高精度乘法

模拟竖式，~10^1000 级别，无负数。

---

## 数值

### 快速幂 · qpow

```
qpow(a, b, mod)   // a^b % mod, O(log b)
```

二进制拆分指数。

### GCD / LCM

```
gcd(a, b)   lcm(a, b)
```

欧几里得算法。

### 模逆元 · modinv

```
modinv(a, mod)   // a^(mod-2) % mod，要求 mod 为质数
```

费马小定理。

### 组合数学

```
pre_fac(mod)           // O(N) 预处理阶乘 & 逆元阶乘
C(n, r, mod)           // 组合数 O(1)
A(n, r, mod)           // 排列数 O(1)
catalan(n, mod)        // 卡特兰数 O(1)
```

预处理：先费马算 `invfac[N-1]`，再倒推 `invfac[n] = invfac[n+1] * (n+1)`——避免每个都调费马，不然复杂度就真的费马了。

卡特兰数 C_n = binom(2n, n) / (n+1)。经典：括号匹配、BST 计数、出栈序列。

### 质数筛

```
init_sieve(n)          // 预处理 isp[]
is_prime(n)            // O(1) 查表
get_primes(n)          // 返回 [2, n] 质数列表
```

埃筛 O(n log log n)。

---

## KMP

```
kmp(s, p)   // 返回 p 在 s 中所有匹配位置
```

next[j] = 最长相等前后缀长度 - 1，失配跳回，i 不回退。O(n+m)。

---

## 前缀和

### 一维

```
prefix_sum(a)   // 返回 pre[0..n]，pre[0] = 0
```

区间和：`sum(l, r) = pre[r+1] - pre[l]`

### 二维

```
prefix_sum_2d(a)   // 返回 (n+1) × (m+1)，1 索引
```

查 (x1, y1) ~ (x2, y2)，0 索引：

`sum = pre[x2+1][y2+1] - pre[x1][y2+1] - pre[x2+1][y1] + pre[x1][y1]`

---

## DP

### 最大子段和

```
max_subarray(a)   // Kadane, O(n)
```

`cur = max(x, cur + x)`

### 01 背包

```
knapsack_01(w, v, n, W)   // 每件最多 1 次, O(nW)
```

容量 **倒序** `j = W -> w[i]`，`dp[j - w[i]]` 取旧值。

### 完全背包

```
knapsack_full(w, v, n, W)   // 每件无限次, O(nW)
```

容量 **正序** `j = w[i] -> W`，`dp[j - w[i]]` 可取新值。

| | 01 背包 | 完全背包 |
|---|---|---|
| 方向 | `j = W..w[i]` | `j = w[i]..W` |
| 顺序 | 倒序 | 正序 |

---

## 差分

### 一维

```
diff_add(d, l, r, v)   // d[l] += v, d[r+1] -= v
```

对 `d` 跑一次 `prefix_sum` 还原。

### 二维

```
diff2d_add(d, x1, y1, x2, y2, v)   // 四个角 O(1)
diff2d_recover(d, n, m)            // O(nm)
```

---

## 搜索

### 组合枚举

```
dfs_pick(pos, n, k, cnt, sum, a[], ans)   // n 选 k
```

### 八邻域

```
neighbor_sum(n, m, target, grid)
neighbor_sum_undirected(n, m, target, grid)
```

---

## 编译

```bash
g++ -std=c++14 -O2 codebook.cpp -o codebook
```

C++14 / GCC 9+ / 洛谷 / ICPC

## License

MIT
