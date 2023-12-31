#include <iostream>
#include <fstream>

#include <vector>
#include <algorithm>
#include <random>

using namespace std;

random_device rd;
mt19937_64 mt(rd());

vector<long long> Query(long long N, long long l, long long r)
{
    vector<long long> array(N);
    uniform_int_distribution<long long> uid(l, r);

    for(long long i = 0; i < N; ++i)
    {
        array[i] = uid(mt);
    }

    return array;
}

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
    long long N, l, r;
    cin >> N >> l >> r;
    
    vector<long long> a = Query(N, l, r);
    for(long long i = 0; i < N; ++i)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    bool ret = OutputToCsv("data1.csv", a, N, l, r);
    cout << (ret ? "Success" : "Fail") << endl;

    return 0;
}