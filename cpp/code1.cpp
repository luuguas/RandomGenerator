#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;

int main(void)
{
    long long N, S;
    cin >> N >> S;

    random_device rd;
    mt19937_64 mt(rd());

    uniform_int_distribution<long long> uid(0, S);

    vector<long long> array(N - 1), diff(N);

    for(long long i = 0; i < N - 1; ++i)
    {
        //0以上S以下のランダムな整数を等確率で生成
        array[i] = uid(mt);
    }
    array.push_back(0);
    array.push_back(S);

    //乱数列をソート
    sort(array.begin(), array.end());

    //隣り合う要素の差をとる
    for(long long i = 0; i < N; ++i)
    {
        diff[i] = array[i + 1] - array[i];
    }

    //出力
    for(long long i = 0; i < N; ++i)
    {
        cout << diff[i] << " ";
    }
    cout << endl;

    return 0;
}