#include <iostream>
#include <vector>
#include <map>

using namespace std;

//class Polynomial {
//public:
//    Polynomial() = default;
//
//    explicit Polynomial(const size_t quantity_polynomials) // сделать защиту от отрицательных чисел
//        : quantity_polynomials_(quantity_polynomials)
//    {
//        cout << "number_polynomials = " << quantity_polynomials << endl;
//    }
//
//    explicit Polynomial(const size_t quantity_polynomials, const double alpha)
//        : quantity_polynomials_(quantity_polynomials)
//        , alpha_(alpha)
//    {
//        cout << "number_polynomials = " << quantity_polynomials << endl;
//        cout << "alpha_ = " << alpha_ << endl;
//    }
//
//    void SetQuantityPolynomials(const size_t quantity_polynomials) {
//        this->quantity_polynomials_ = quantity_polynomials;
//    }
//
//    vector<int32_t> GetPolynom(const size_t number_polynomial) {
//        return Laguerre_polynomials_.at(number_polynomial);
//    }
//
//    map<size_t, vector<int32_t>> GetAllPolynomials() {
//        return Laguerre_polynomials_;
//    }
//
//private:
//    double alpha_ = 0; // параметр масштаба
//    size_t quantity_polynomials_ = 2;
//    map<size_t, map<int32_t, double>> Laguerre_polynomials_ = { {0, {1}}, {1, {1 , -1}} };
//};

void AssertImpl(bool value, const string& expr_str, const string& file, const string& func, unsigned line,
    const string& hint = ""s) {
    if (!value) {
        cerr << file << "("s << line << "): "s << func << ": "s;
        cerr << "ASSERT("s << expr_str << ") failed."s;
        if (!hint.empty()) {
            cerr << " Hint: "s << hint;
        }
        cerr << endl;
        abort();
    }
}

#define ASSERT(expr) AssertImpl(!!(expr), #expr, __FILE__, __FUNCTION__, __LINE__, ""s)
#define ASSERT_HINT(expr, hint) AssertImpl(!!(expr), #expr, __FILE__, __FUNCTION__, __LINE__, (hint))

void PrintAllPolynomials(const vector<map<int32_t, double>>& all_polynom) {
    for (const map<int32_t, double>& polynom : all_polynom) {
        for (const auto& [exp, coef] : polynom) {
            if (exp == 0) {
                cout << coef;
            } else {
                if (coef > 0) {
                    cout << "+"s << coef << "x^"s << exp;
                } else {
                    cout << coef << "x^"s << exp;
                }
            }
        }
        cout << endl;
    }
}

void SynthesisLaguerrePolynomials(vector<map<int32_t, double>>& all_polynom) {
    for (size_t i = 2; i < all_polynom.size(); ++i) {
        map<int32_t, double> tmp_polynom = { {0, 2 * i - 1}, {1, 1} };
        // написать перегрузку оператора умножения для полиномов
        all_polynom[i] = ((tmp_polynom * all_polynom[i - 1]) - ((i - 1) * all_polynom[i - 2])) / i;
    }
}

int main()
{
    const double alpha = 0; // параметр масштаба
    const size_t min_quantity_polynomials = 2; // минимально допустимое число полиномов Лагерра
    const size_t quantity_polynomials = 2;
    ASSERT_HINT(quantity_polynomials >= min_quantity_polynomials, "Incorrect number of polynomials. Their number should not be less than 2."s);
    vector<map<int32_t, double>> Laguerre_polynomials(quantity_polynomials); // все полиномы Лагерра
    Laguerre_polynomials[0] = { {0,1} };
    Laguerre_polynomials[1] = { {0,1}, {1,-1} };
    PrintAllPolynomials(Laguerre_polynomials);
    SynthesisLaguerrePolynomials(Laguerre_polynomials);
    return 0;
}