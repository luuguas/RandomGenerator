#include <iostream>
#include <random>
#include <vector>
using namespace std;

int main(void)
{
    long long N, S, L, R;
    cin >> N >> S >> L >> R;

    random_device rd;
    mt19937_64 mt(rd());

    //平均
    long long ave = S / N;
    if(ave < L || R < ave)
    {
        //平均が範囲外の場合は生成不可能
        cout << "The average is out of range." << endl;
        return 0;
    }

    //乱数の生成範囲を決める
    long long l = max(L, 2 * ave - R), r = min(2 * ave - L, R);

    uniform_int_distribution<long long> uid(l, r);

    vector<long long> array(N);
    
    long long sum = 0;
    for(long long i = 0; i < N; ++i)
    {
        array[i] = uid(mt);
        sum += array[i];
    }

    //誤差を修正する
    long long err = sum - S;
    for(long long i = 0; i < N; ++i)
    {
        array[i] -= err / N;
    }
    err -= err / N * N;
    
    //微調整(N個の乱数から重複のないように選ぶ(Fisher-Yates shuffle))
    vector<long long> fisher(N);
    for(long long i = 0; i < N; ++i)
    {
        fisher[i] = i;
    }

    long long idx;
    for(long long upper = N - 1; err > 0; --err, --upper)
    {
        uniform_int_distribution<long long> choose(0, upper);
        idx = choose(mt);
        array[fisher[idx]] -= 1;
        fisher[idx] = fisher[upper];
    }
    for(long long upper = N - 1; err < 0; ++err, --upper)
    {
        uniform_int_distribution<long long> choose(0, upper);
        idx = choose(mt);
        array[fisher[idx]] += 1;
        fisher[idx] = fisher[upper];
    }

    //数列とその和を出力
    sum = 0;
    for(long long i = 0; i < N; ++i)
    {
        cout << array[i] << " ";
        sum += array[i];
    }
    cout << endl;
    cout << sum << endl;

    return 0;
}