#include <iostream>
#include <fstream>
#include <filesystem>

#include <vector>
#include <algorithm>
#include <random>

using namespace std;
using ll = long long;

random_device rd;
mt19937_64 mt(rd());

vector<ll> Query(ll N, ll l, ll r)
{
    vector<ll> array(N);
    uniform_int_distribution<ll> uid(l, r);

    for(ll i = 0; i < N; ++i)
    {
        array[i] = uid(mt);
    }

    return array;
}

bool OutputToCsv(string fileName, const vector<ll>& array, ll N, ll L, ll R)
{
    fstream out;
    string filePath = "../csv/" + fileName;
    out.open(filePath, ios::out | ios::trunc);

    if(!out.is_open())
        return false;

    out << N << "," << L << "," << R << endl;
    for(ll i = 0; i < N - 1; ++i)
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
    ll N, l, r;
    cin >> N >> l >> r;
    
    vector<ll> a = Query(N, l, r);
    for(ll i = 0; i < N; ++i)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    bool ret = OutputToCsv("data1.csv", a, N, l, r);
    cout << (ret ? "Success" : "Fail") << endl;

    return 0;
}