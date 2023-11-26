#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;

#include <string>
#include <fstream>
bool OutputToCsv(string fileName, const vector<long long>& base, const vector<long long>& array, long long N, long long S)
{
    fstream out;
    string filePath = "../csv/" + fileName;
    out.open(filePath, ios::out | ios::trunc);

    if(!out.is_open())
        return false;

    out << N << "," << S << endl;

    for(long long i = 0; i < N; ++i)
    {
        out << base[i] << ",";
    }
    out << base[N];
    out << endl;

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
    long long N, S;
    cin >> N >> S;

    random_device rd;
    mt19937_64 mt(rd());

    uniform_int_distribution<long long> uid(0, S);

    vector<long long> base(N - 1), array(N);

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
    for(long long i = 0; i < N; ++i)
    {
        array[i] = base[i + 1] - base[i];
    }

    //出力
    for(long long i = 0; i < N; ++i)
    {
        cout << array[i] << " ";
    }
    cout << endl;

    OutputToCsv("data2.csv", base, array, N, S);

    return 0;
}