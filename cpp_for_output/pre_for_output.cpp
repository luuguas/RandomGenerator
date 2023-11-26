#include <iostream>
#include <random>
#include <vector>
using namespace std;

#include <string>
#include <fstream>
bool OutputToCsv(string fileName, const vector<long long>& array, long long N, long long L, long long R)
{
    fstream out;
    string filePath = "../csv/" + fileName;
    out.open(filePath, ios::out | ios::trunc);

    if(!out.is_open())
        return false;

    out << N << "," << L << "," << R << endl;
    for(long long i = 0; i < N - 1; ++i)
    {
        out << array[i] << ",";
    }
    out << array[N - 1];
    out << endl;

    out.close();
    return true;
}


int main(void)
{
    long long N, L, R;
    cin >> N >> L >> R;

    //ランダムなシード値を使って乱数生成器を初期化
    random_device rd;
    mt19937_64 mt(rd());

    //生成する乱数の最小値L,最大値Rを指定して初期化
    uniform_int_distribution<long long> uid(L, R);

    vector<long long> array(N);
    
    for(long long i = 0; i < N; ++i)
    {
        //L以上R以下のランダムな整数を等確率で生成
        array[i] = uid(mt);
    }

    //乱数列を出力
    for(long long i = 0; i < N; ++i)
    {
        cout << array[i] << " ";
    }
    cout << endl;

    OutputToCsv("data11.csv", array, N, L, R);

    return 0;
}