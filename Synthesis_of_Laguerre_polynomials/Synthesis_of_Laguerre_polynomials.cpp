#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

typedef map<int32_t, double> Polynomial;

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

void PrintPolynomial(const Polynomial& polynom) {
    for (const auto& [exponent, coefficient] : polynom) {
        if (exponent == 0) {
            cout << coefficient;
        }
        else {
            if (coefficient > 0) {
                cout << "+"s << coefficient << "x^"s << exponent;
            }
            else {
                cout << coefficient << "x^"s << exponent;
            }
        }
    }
}

// Запись в .txt файл коэффициентов сгенерированных полиномов Лагерра
void WriteAllPolynomialsToTxt(const vector<Polynomial>& all_polynom) {
    ofstream Laguerre_polynomials;
    Laguerre_polynomials.open("Laguerre_polynomials.txt"s);
    for (const Polynomial& polynom : all_polynom) {
        vector<double> polynom_to_txt(all_polynom.size(), 0);
        for (const auto& [exponent, coefficient] : polynom) {
            polynom_to_txt[exponent] = coefficient;
        }
        reverse(polynom_to_txt.begin(), polynom_to_txt.end()); // т.к. в map от меньшего к большему
        bool flag = true;
        for (const double& coefficient_polynom : polynom_to_txt) {
            if (flag) {
                Laguerre_polynomials << coefficient_polynom;
                flag = false;
            } else {
                Laguerre_polynomials << ", "s << coefficient_polynom;
            }
        }
        Laguerre_polynomials << endl;
    }
    Laguerre_polynomials.close();
}

void PrintAllPolynomials(const vector<Polynomial>& all_polynom) {
    for (const Polynomial& polynom : all_polynom) {
        PrintPolynomial(polynom);
        cout << endl;
    }
}

Polynomial operator*(const Polynomial& first, const Polynomial& second) {
    Polynomial result;
    for (const auto& [exponent_first, coefficient_first] : first) {
        for (const auto& [exponent_second, coefficient_second] : second) {
            result[exponent_first + exponent_second] += coefficient_first * coefficient_second;
        }
    }
    return result;
}

template <typename Value>
Polynomial operator/(const Polynomial& polynomial, Value value) {
    Polynomial result = polynomial;
    for (const auto& [exponent, coefficient] : result) {
        result[exponent] = coefficient / value;
    }
    return result;
}

//map<int32_t, double> operator/(const map<int32_t, double>& divisible, const map<int32_t, double>& divider) {
//    ASSERT_HINT(divider.rbegin()->first < divisible.rbegin()->first, 
// "The highest degree of the divisor must be less than or equal to the degree of the divisible"s);
//    //cout << "divider.rbegin()->first = "s << divider.rbegin()->first << endl;
//    //cout << "divisible.rbegin()->first = "s << divisible.rbegin()->first << endl;
//    map<int32_t, double> result = divisible;
//    
//    
//    return result;
//}

Polynomial operator-(const Polynomial& first, const Polynomial& second) {
    Polynomial result = first;
    for (const auto& [exponent, coefficient] : second) {
        result[exponent] -= coefficient;
    }
    return result;
}

template <typename Value>
map<int32_t, double> ValueToMap(Value value) {
    return { {0, static_cast<double>(value)} };
}

void SynthesisLaguerrePolynomials(vector<Polynomial>& all_polynom) {
    for (size_t i = 2; i < all_polynom.size(); ++i) {
        Polynomial tmp_polynom = { {0, 2 * i - 1}, {1, -1} };
        all_polynom[i] = ((tmp_polynom * all_polynom[i - 1]) - (ValueToMap(i - 1) * all_polynom[i - 2])) / i;
    }
    //map<int32_t, double> a = { {5,1}, {4,2}, {3,3}, {2,4}, {1,2} };
    //map<int32_t, double> b = { {3,1}, {2,1}, {1,3}, {0,3} };
    //map<int32_t, double> mult = a / b;
    //PrintPolynomial(mult);
}

int main()
{
    const double alpha = 0; // параметр масштаба
    const size_t min_quantity_polynomials = 2; // минимально допустимое число полиномов Лагерра
    const size_t quantity_polynomials = 7;
    ASSERT_HINT(quantity_polynomials >= min_quantity_polynomials, 
        "Incorrect number of polynomials. Their number should not be less than 2."s);
    vector<Polynomial> Laguerre_polynomials(quantity_polynomials); // все полиномы Лагерра
    Laguerre_polynomials[0] = { {0,1} };
    Laguerre_polynomials[1] = { {0,1}, {1,-1} };
    SynthesisLaguerrePolynomials(Laguerre_polynomials);
    PrintAllPolynomials(Laguerre_polynomials);
    WriteAllPolynomialsToTxt(Laguerre_polynomials);
    return 0;
}