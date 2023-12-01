#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;

int main(void)
{
    long long N, S, L, R;
    long long Q; //クエリ数
    cin >> N >> S >> L >> R >> Q;

    random_device rd;
    mt19937_64 mt(rd());

    long long cnt = 0;
    for(long long q = 0; q < Q; ++q)
    {
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
        
        //微調整(N個の乱数からランダムに選ぶ)
        uniform_int_distribution<long long> choose(0, N - 1);
        for(; err > 0; --err)
        {
            array[choose(mt)] -= 1;
        }
        for(; err < 0; ++err)
        {
            array[choose(mt)] += 1;
        }
    
        sort(array.begin(), array.end());
    
        if(L <= array[0] && array[N - 1] <= R)
        {
            ++cnt;
        }
    }

    cout.setf(ios::fixed);
    cout.precision(5);
    cout << (double)cnt / Q * 100.0 << "%\n";

    return 0;
}