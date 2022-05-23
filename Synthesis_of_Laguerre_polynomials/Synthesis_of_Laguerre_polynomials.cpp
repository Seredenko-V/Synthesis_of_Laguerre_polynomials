#include <iostream>
#include <vector>
#include <map>

using namespace std;

//class Polynomial {
//public:
//    Polynomial() = default;
//    
//private:
//    map<int32_t, double> polynomial_;
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

void PrintPolynomial(const map<int32_t, double>& polynom) {
    for (const auto& [exponent, coefficient] : polynom) {
        if (exponent == 0) {
            cout << coefficient;
        } else {
            if (coefficient > 0) {
                cout << "+"s << coefficient << "x^"s << exponent;
            }
            else {
                cout << coefficient << "x^"s << exponent;
            }
        }
    }
}

void PrintAllPolynomials(const vector<map<int32_t, double>>& all_polynom) {
    for (const map<int32_t, double>& polynom : all_polynom) {
        PrintPolynomial(polynom);
        cout << endl;
    }
}

map<int32_t, double> operator*(const map<int32_t, double>& first, const map<int32_t, double>& second) {
    map<int32_t, double> result;
    for (const auto& [exponent_first, coefficient_first] : first) {
        for (const auto& [exponent_second, coefficient_second] : second) {
            result[exponent_first + exponent_second] += coefficient_first * coefficient_second;
        }
    }
    return result;
}

template <typename Value> 
map<int32_t, double> operator*(Value value, const map<int32_t, double>& polynomial) {
    map<int32_t, double> result = polynomial;
    for (const auto& [exponent, coefficient] : result) {
        result[exponent] = coefficient * value;
    }
    return result;
}

map<int32_t, double> operator-(const map<int32_t, double>& first, const map<int32_t, double>& second) {
    map<int32_t, double> result = first;
    for (const auto& [exponent, coefficient] : second) {
        result[exponent] -= coefficient;
    }
    return result;
}

void SynthesisLaguerrePolynomials(vector<map<int32_t, double>>& all_polynom) {
    for (size_t i = 2; i < all_polynom.size(); ++i) {
        map<int32_t, double> tmp_polynom = { {0, 2 * i - 1}, {1, 1} };
        //all_polynom[i] = ((tmp_polynom * all_polynom[i - 1]) - ((i - 1) * all_polynom[i - 2])) / i;
    }
    map<int32_t, double> a = { {5,1}, {4,2}, {3,3}, {2,4}, {1,2} };
    map<int32_t, double> b = { {3,1}, {2,1}, {1,3}, {0,3} };
    map<int32_t, double> mult = b - a;
    PrintPolynomial(mult);
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