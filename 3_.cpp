#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

int t, b, n;
int pre[100010], node_l[100010], node_r[100010];
int min_num[100010], max_num[100010], ans[100010];

int calc_imbalance()
{
    int minn = 0;
    int maxx = 1e9;
    while (minn < maxx)
    {
        int mid = (minn + maxx) / 2;
        int symbol = 0;
        for (int i = 1; i <= n; i++)
        {
            min_num[i] = node_l[i] - mid;
            max_num[i] = node_r[i] + mid;
        }
        for (int i = n; i >= 1; i--)
        {
            if ((node_r[i] < min_num[i]) || (node_l[i] > max_num[i]))
            {
                symbol = 1;
                break;
            }
            else if (min_num[i] > max_num[i])
            {
                symbol = 2;
                break;
            }
            else
            {
                min_num[pre[i]] = max(min_num[pre[i]], min_num[i]);
                max_num[pre[i]] = min(max_num[pre[i]], max_num[i]);
            }
        }
        if (symbol == 0)
            maxx = mid;
        else
            minn = mid + 1;
    }
    return (minn + maxx) / 2;
}

void calc_range(int mid)
{
    for (int i = 1; i <= n; i++)
    {
        min_num[i] = node_l[i] - mid;
        max_num[i] = node_r[i] + mid;
    }
    for (int i = n; i >= 1; i--)
    {
        min_num[pre[i]] = max(min_num[pre[i]], min_num[i]);
        max_num[pre[i]] = min(max_num[pre[i]], max_num[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        node_l[i] = max(node_l[i], min_num[i]);
        node_r[i] = min(node_r[i], max_num[i]);
    }
}

void calc_ans(int mid)
{
    ans[1] = node_l[1];
    min_num[1] = node_l[1] - mid;
    max_num[1] = node_l[1] + mid;
    for (int i = 2; i <= n; i++)
    {
        ans[i] = max(node_l[i], min_num[pre[i]]);
        max_num[i] = min(ans[i] + mid, max_num[pre[i]]);
        min_num[i] = max(ans[i] - mid, min_num[pre[i]]);
    }
}

int main()
{
    scanf("%d %d", &t, &b);
    while (t--)
    {
        scanf("%d", &n);
        for (int i = 2; i <= n; i++)
        {
            scanf("%d", &pre[i]);
        }
        for (int i = 1; i <= n; i++)
        {
            scanf("%d %d", &node_l[i], &node_r[i]);
        }

        int mid = calc_imbalance();
        cout << mid << endl;

        if (b)
        {
            calc_range(mid);
            memset(ans, 0, sizeof(ans));
            calc_ans(mid);

            for (int i = 1; i <= n; i++)
                printf("%d ", ans[i]);
            printf("\n");
        }
    }

    return 0;
}
