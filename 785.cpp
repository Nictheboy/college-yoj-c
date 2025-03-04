#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
using ll = long long;

struct Point
{
    int x, y;
};

bool cmpX(const Point &a, const Point &b)
{
    return a.x < b.x;
}

bool cmpY(const Point &a, const Point &b)
{
    return a.y < b.y;
}

ll dist(const Point &a, const Point &b)
{
    ll dx = (ll)a.x - b.x;
    ll dy = (ll)a.y - b.y;
    return dx * dx + dy * dy;
}

const ll INF = 1LL << 60;

ll closestPair(vector<Point> &points, int left, int right)
{
    if (right - left <= 1)
        return INF; // 没有两点
    if (right - left == 2)
        return dist(points[left], points[left + 1]);

    int mid = (left + right) / 2;
    ll d = min(closestPair(points, left, mid), closestPair(points, mid, right));

    // 构造横跨分界线的带状区域
    vector<Point> strip;
    int midx = points[mid].x;
    for (int i = left; i < right; i++)
    {
        ll dx = (ll)points[i].x - midx;
        if (dx * dx < d)
            strip.push_back(points[i]);
    }

    // 按 y 坐标排序
    sort(strip.begin(), strip.end(), cmpY);

    // 枚举带状区域内的点对
    int sz = strip.size();
    for (int i = 0; i < sz; i++)
    {
        for (int j = i + 1; j < sz && (ll)(strip[j].y - strip[i].y) * (strip[j].y - strip[i].y) < d; j++)
        {
            d = min(d, dist(strip[i], strip[j]));
        }
    }
    return d;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; i++)
    {
        cin >> points[i].x >> points[i].y;
    }

    // 按 x 坐标排序
    sort(points.begin(), points.end(), cmpX);
    ll ans = closestPair(points, 0, n);
    cout << ans;
    return 0;
}
