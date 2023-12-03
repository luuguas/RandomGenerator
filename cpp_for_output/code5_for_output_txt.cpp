#include <iostream>
#include <random>
#include <vector>
#include <cmath>
using namespace std;

#include <string>
#include <fstream>

int main(void)
{
    fstream out;
    string fileName = "code5_result_2.txt";
    string filePath = "../txt/" + fileName;
    out.open(filePath, ios::out | ios::trunc);

    long long N, S, L, R;
    cin >> N >> S >> L >> R;

    const double k = 3.33; //比例定数
    const long long retry_max = 10;  //生成回数の最大値

    random_device rd;
    mt19937_64 mt(rd());

    //平均
    long long ave = S / N;
    if(ave < L || R < ave)
    {
        //平均が範囲外の場合は生成不可能
        out << "The average is out of range." << endl;
        out.close();
        return 0;
    }

    //乱数の生成範囲を決める
    long long l_min = max(L, 2 * ave - R), r_max = min(2 * ave - L, R);
    double E_inv = k * sqrt(N);
    long long gap = min((long long)((r_max - l_min) / E_inv), (r_max - l_min) / 2);
    long long l = l_min + gap, r = r_max - gap;

    uniform_int_distribution<long long> uid(l, r);

    vector<long long> array(N);

    long long retry = 0; //生成のやり直し回数
    for(; retry < retry_max; ++retry)
    {
        long long sum = 0;
        for(long long i = 0; i < N; ++i)
        {
            array[i] = uid(mt);
            sum += array[i];
        }

        //誤差を修正する
        long long err = sum - S;
        bool fail = false; //生成失敗判定
        for(long long i = 0; i < N; ++i)
        {
            array[i] -= err / N;
            if(array[i] < L || R < array[i])
            {
                fail = true;
                break;
            }
        }
        err -= err / N * N;
        if(fail)
            continue;

        //微調整(N個の乱数から重複のないように選ぶ(Fisher-Yates shuffle))
        vector<long long> fisher;
        if(err > 0)
        {
            for(long long i = 0; i < N; ++i)
            {
                if(L < array[i])
                    fisher.push_back(i);
            }
        }
        else if(err < 0)
        {
            for(long long i = 0; i < N; ++i)
            {
                if(array[i] < R)
                    fisher.push_back(i);
            }
        }

        long long fisher_size = fisher.size();
        //生成失敗判定
        if(abs(err) > fisher_size)
            continue;

        long long idx;
        for(long long upper = fisher_size - 1; err > 0; --err, --upper)
        {
            uniform_int_distribution<long long> choose(0, upper);
            idx = choose(mt);
            array[fisher[idx]] -= 1;
            fisher[idx] = fisher[upper];
        }
        for(long long upper = fisher_size - 1; err < 0; ++err, --upper)
        {
            uniform_int_distribution<long long> choose(0, upper);
            idx = choose(mt);
            array[fisher[idx]] += 1;
            fisher[idx] = fisher[upper];
        }

        break;
    }

    //retry_max回生成に失敗した場合
    if(retry == retry_max)
    {
        out << "Failed to generate sequence." << endl;
        out.close();
        return 0;
    }

    //数列とその和を出力
    long long sum = 0;
    for(long long i = 0; i < N; ++i)
    {
        out << array[i] << " ";
        sum += array[i];
    }
    out << endl;
    out << sum << endl;

    //生成のやり直し回数を出力
    out << "retry: " << retry << endl;

    out.close();
    return 0;
}