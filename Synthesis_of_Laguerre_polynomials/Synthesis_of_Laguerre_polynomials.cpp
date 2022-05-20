#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Polynomial {
public:
    Polynomial() = default;

    explicit Polynomial(const size_t quantity_polynomials) // сделать защиту от отрицательных чисел
        : quantity_polynomials_(quantity_polynomials)
    {
        cout << "number_polynomials = " << quantity_polynomials << endl;
    }

    void SetQuantityPolynomials(const size_t quantity_polynomials) {
        this->quantity_polynomials_ = quantity_polynomials;
    }

    vector<int32_t> GetPolynom(const size_t number_polynomial) {
        return Laguerre_polynomials_.at(number_polynomial);
    }

    map<size_t, vector<int32_t>> GetAllPolynomials() {
        return Laguerre_polynomials_;
    }

private:
    size_t quantity_polynomials_ = 2;
    map<size_t, vector<int32_t>> Laguerre_polynomials_ = { {0, {1}}, {1, {1 , -1}} };
};

int main()
{
    Polynomial first(2);
    return 0;
}