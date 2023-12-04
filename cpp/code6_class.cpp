//総和が一定の乱数列を生成するクラス
#include <random>
#include <vector>
#include <cmath>
template <typename idxT, typename randT>
class RandomIntegerSequenceWithConstantSum
{
private:
    idxT _retry_max = 10;
    double _k = 6.0;

    std::random_device rd;
    std::mt19937_64 mt;

public:
    explicit RandomIntegerSequenceWithConstantSum(void) : mt(rd()) {}
    explicit RandomIntegerSequenceWithConstantSum(idxT retry_max) : RandomIntegerSequenceWithConstantSum(retry_max, 6.0) {}
    explicit RandomIntegerSequenceWithConstantSum(double k) : RandomIntegerSequenceWithConstantSum((idxT)10, k) {}
    explicit RandomIntegerSequenceWithConstantSum(idxT retry_max, double k) : _retry_max(std::max(retry_max, (idxT)0)), _k(std::max(k, 1.0)), mt(rd()) {}

    std::vector<randT> query(idxT N, randT S, randT L, randT R)
    {
        if(S / N < L || R < S / N)
            return std::vector<randT>(0);

        randT l_min = std::max(L, 2 * S / N - R), r_max = std::min(2 * S / N - L, R);
        double E_inv = _k * std::sqrt(N);
        randT gap = std::min((randT)((r_max - l_min) / E_inv), (r_max - l_min) / 2);
        randT l = l_min + gap, r = r_max - gap;

        std::uniform_int_distribution<randT> uid(l, r);

        std::vector<randT> array(N);

        idxT retry = 0;
        for(; retry <= _retry_max; ++retry)
        {
            randT sum = 0;
            for(idxT i = 0; i < N; ++i)
            {
                array[i] = uid(mt);
                sum += array[i];
            }

            randT err = sum - S;
            bool fail = false;
            for(idxT i = 0; i < N; ++i)
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

            std::vector<idxT> fisher;
            if(err > 0)
            {
                for(idxT i = 0; i < N; ++i)
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

            idxT fisher_size = fisher.size();
            if(std::abs(err) > (randT)fisher_size)
                continue;

            idxT idx;
            for(idxT upper = fisher_size - 1; err > 0; --err, --upper)
            {
                std::uniform_int_distribution<idxT> choose(0, upper);
                idx = choose(mt);
                array[fisher[idx]] -= 1;
                fisher[idx] = fisher[upper];
            }
            for(idxT upper = fisher_size - 1; err < 0; ++err, --upper)
            {
                std::uniform_int_distribution<idxT> choose(0, upper);
                idx = choose(mt);
                array[fisher[idx]] += 1;
                fisher[idx] = fisher[upper];
            }

            break;
        }

        if(retry > _retry_max)
            return std::vector<randT>(0);

        return array;
    }
};

/*
template <typename idxT, typename randT>
class RandomIntegerSequenceWithConstantSum
{
    //生成のやり直し回数および比例定数を指定して初期化
    //指定しない場合、やり直し回数のデフォルトは10回、比例定数のデフォルトは10.0
    explicit RandomIntegerSequenceWithConstantSum(void);
    explicit RandomIntegerSequenceWithConstantSum(idxT retry_max);
    explicit RandomIntegerSequenceWithConstantSum(double k);
    explicit RandomIntegerSequenceWithConstantSum(idxT retry_max, double k);

    //総和がSとなるL以上R以下の乱数N個を要素に持つ配列を生成して返す
    //生成に失敗した場合は空の配列を返す
    std::vector<randT> query(idxT N, randT S, randT L, randT R);
};
*/

#include <iostream>
using namespace std;
int main(void)
{
    long long N, S, L, R;
    cin >> N >> S >> L >> R;

    RandomIntegerSequenceWithConstantSum<long long, long long> generator;
    vector<long long> array = generator.query(N, S, L, R);

    if(array.size() == 0)
    {
        cout << "Failed to generate sequence." << endl;
        return 0;
    }

    long long sum = 0;
    for(long long i = 0; i < N; ++i)
    {
        cout << array[i] << " ";
        sum += array[i];
    }
    cout << endl;
    cout << sum << endl;

    return 0;
}