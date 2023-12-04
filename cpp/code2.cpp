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

    vector<long long> base(N - 1), array(N);

    while(true)
    {
        for(long long i = 0; i < N - 1; ++i)
        {
            //0以上S以下のランダムな整数を等確率で生成
            base[i] = uid(mt);
        }
        base.push_back(0);
        base.push_back(S);

        //乱数列をソート
        sort(base.begin(), base.end());

        //隣り合う要素の差をとる
        long long bmin = S;
        for(long long i = 0; i < N; ++i)
        {
            array[i] = base[i + 1] - base[i];
            bmin = min(bmin, array[i]);
        }

        if(bmin >= 4)
        {
            break;
        }
    }

    //出力
    for(long long i = 0; i < N; ++i)
    {
        cout << array[i] << " ";
    }
    cout << endl;

    return 0;
}