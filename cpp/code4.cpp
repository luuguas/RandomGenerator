#include <iostream>
#include <random>
#include <vector>
using namespace std;

int main(void)
{
    long long Q; //各条件における試行回数
    cin >> Q;

    //個数Nと生成幅RANGE=R-Lの条件を変えて調べる
    //総和S=0
    vector<long long> RANGE = {100, 1000, 10000, 100000};
    vector<long long> N = {10, 100, 1000, 10000};

    random_device rd;
    mt19937_64 mt(rd());

    vector<vector<double>> err(16, vector<double>(Q, 0.0));

    for(long long i = 0; i < 4; ++i)
    {
        long long range = RANGE[i];

        for(long long j = 0; j < 4; ++j)
        {
            long long n = N[j];

            for(long long q = 0; q < Q; ++q)
            {
                uniform_int_distribution<long long> uid(-range / 2, range / 2);

                vector<long long> array(n);

                long long sum = 0;
                for(long long i = 0; i < n; ++i)
                {
                    array[i] = uid(mt);
                    sum += array[i];
                }

                //誤差の絶対値を記録
                err[i * 4 + j][q] = (double)abs(sum) / n;
            }
        }
    }

    //誤差を出力
    cout.setf(ios::fixed);
    cout.precision(4);
    for(long long i = 0; i < 4; ++i)
    {
        long long range = RANGE[i];

        cout << "range: " << range << endl;
        for(long long j = 0; j < 4; ++j)
        {
            long long n = N[j];

            cout << " n: " << n << endl;
            cout << "  ";
            for(long long q = 0; q < Q; ++q)
            {
                cout << err[i * 4 + j][q] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}