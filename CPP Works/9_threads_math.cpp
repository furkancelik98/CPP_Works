/*
Bu kod, matematiksel ifadeyi çoklu thread kullanarak değerlendirir. Thread, parantez içi işlemleri de gerçekleştirir ve sonucu ana thread'e iletilir.
 Ayrıca sonuç değişkenini korumak için bir mutex kullanılır, böylece birden çok thread aynı anda sonucu değiştiremez.
*/

#include <iostream>
#include <string>
#include <stack>
#include <thread>
#include <mutex>

// Operatörlerin öncelik düzeylerini belirleme
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// İki sayıyı işlemi uygulama
double applyOperator(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0.0;
    }
}

// İfadenin sonucunu hesaplayan iş parçacığı
void evaluateExpressionThread(const std::string& expression, double& result, std::mutex& resultMutex) {
    std::stack<double> values;
    std::stack<char> operators;

    for (char token : expression) {
        if (token == ' ') // Boşlukları atla
            continue;

        if (isdigit(token) || token == '.') {
            // Sayıları işleme ve değerleri yığına ekle
            double value;
            std::cin.putback(token);
            std::cin >> value;
            values.push(value);
        } else if (token == '(') {
            // Açma parantezi işleme ve operatör yığına ekle
            operators.push(token);
        } else if (token == ')') {
            // Kapatma parantezi bulunduğunda hesaplama yap
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top();
                operators.pop();
                double b = values.top();
                values.pop();
                double a = values.top();
                values.pop();
                values.push(applyOperator(a, b, op));
            }
            operators.pop(); // '(' parantezini kaldır
        } else {
            // Operatör işleme
            while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
                char op = operators.top();
                operators.pop();
                double b = values.top();
                values.pop();
                double a = values.top();
                values.pop();
                values.push(applyOperator(a, b, op));
            }
            operators.push(token);
        }
    }

    // İfadedeki kalan operatörleri işle
    while (!operators.empty()) {
        char op = operators.top();
        operators.pop();
        double b = values.top();
        values.pop();
        double a = values.top();
        values.pop();
        values.push(applyOperator(a, b, op));
    }

    // Son sonucu kaydet
    resultMutex.lock();
    result = values.top();
    resultMutex.unlock();
}

int main() {
    std::string expression;
    std::cout << "Matematiksel bir ifade girin: ";
    std::getline(std::cin, expression);

    try {
        double result = 0.0;
        std::mutex resultMutex;

        // İş parçacığı oluştur ve ifadeyi değerlendir
        std::thread workerThread(evaluateExpressionThread, expression, std::ref(result), std::ref(resultMutex));

        // Ana iş parçacığı sonucu bekler
        workerThread.join();

        std::cout << "Sonuç: " << result << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Hata: " << e.what() << std::endl;
    }

    return 0;
}
