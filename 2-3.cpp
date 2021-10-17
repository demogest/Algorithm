#include <bits/stdc++.h>
using namespace std;
int part(vector<int> &nums, int l, int r)
{ 
    int pivot = nums[l];
    int i = l + 1, j = r;
    while (true)
    {
        while (i <= j && nums[i] <= pivot)
            i++;
        while (i <= j && nums[j] >= pivot)
            j--;
        if (i > j)
            break;
        swap(nums[i], nums[j]);
    }
    swap(nums[j], nums[l]);
    return j;
}
void QuickSort(vector<int> &nums, int l, int r)
{
    if (l < r)
    {
        int mid = part(nums, l, r);
        QuickSort(nums, l, mid - 1);
        QuickSort(nums, mid + 1, r);
    }
}

int main(){
    vector<int> a;
    int n,k;
    for (int i=(cin>>n,0);i<n;i++)
        a.push_back((cin>>k,k));
    QuickSort(a,0,a.size()-1);
    for (auto it = a.begin();it!=a.end();it++)
        cout<<*it<<(*it == a[a.size()-1]?"\n":" ");
    return 0;
}
