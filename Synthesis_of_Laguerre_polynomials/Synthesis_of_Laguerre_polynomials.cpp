#include <iostream>
#include <vector>
#include <string>
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
void WriteAllPolynomialsToTxt(const vector<Polynomial>& all_polynom, const string& file_name) {
    ofstream Laguerre_polynomials;
    Laguerre_polynomials.open(file_name + ".txt"s);
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

// Синтез quantity_polynomials полиномов Лаггера
vector<Polynomial> SynthesisLaguerrePolynomials(const double alpha, const int32_t quantity_polynomials) {
    const size_t min_quantity_polynomials = 2; // минимально допустимое число полиномов Лагерра
    ASSERT_HINT(quantity_polynomials >= static_cast<int32_t>(min_quantity_polynomials),
        "Incorrect number of polynomials. Their number should not be less than 2."s);
    vector<Polynomial> Laguerre_polynomials(quantity_polynomials); // все полиномы Лагерра
    Laguerre_polynomials[0] = { {0,1} };
    Laguerre_polynomials[1] = { {0,1 + alpha}, {1,-1} };
    for (size_t i = 2; i < Laguerre_polynomials.size(); ++i) {
        Polynomial tmp_polynom = { {0, 2 * i - 1 + alpha}, {1, -1} };
        Laguerre_polynomials[i] = ((tmp_polynom * Laguerre_polynomials[i - 1]) - (ValueToMap(i - 1 + alpha) 
            * Laguerre_polynomials[i - 2])) / i;
    }
    return Laguerre_polynomials;
}

int main()
{
    const double alpha = 0; // параметр масштаба
    const int32_t quantity_polynomials = 5; // количество генерируемых полиномов
    // все полиномы Лагерра
    vector<Polynomial> Laguerre_polynomials = SynthesisLaguerrePolynomials(alpha, quantity_polynomials); 
    PrintAllPolynomials(Laguerre_polynomials);
    WriteAllPolynomialsToTxt(Laguerre_polynomials, "Laguerre_polynomials__alpha="s + to_string(alpha) + "_n="s +
        to_string(quantity_polynomials));
    return 0;
}