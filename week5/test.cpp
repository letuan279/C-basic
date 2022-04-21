#include <iostream>

using namespace std;

int solve(int *arr, int l, int r)
{
    if (l > r)
        return 0;

    int Min = arr[l];
    int Min_pos = l;
    for (int i = l + 1; i <= r; ++i)
    {
        if (Min > arr[i])
        {
            Min = arr[i];
            Min_pos = i;
        }
    }

    for (int i = l; i <= r; ++i)
    {
        arr[i] -= Min;
    }

    int ans = min(solve(arr, l, Min_pos - 1) + solve(arr, Min_pos + 1, r) + Min, r - l + 1);

    return ans;
}

int main()
{
    int n;
    cin >> n;
    int a[n];

    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

    cout << solve(a, 0, n - 1);

    return 0;
}