#include <iostream>
#include <chrono>

void stopSymbolHeuristic(std::string str, int size, int stopSymbol[256]) {

    // Ініціалізую всі входження як -1
    for (int i = 0; i < 256; i++)
        stopSymbol[i] = -1;

    // Заповняю фактичне значення останнього входження символу
    for (int i = 0; i < size; i++)
        stopSymbol[(int) str[i]] = i;
}


void search(std::string text, std::string pattern) {
    int m = pattern.size();
    int n = text.size();

    int stopSymbol[256];

    /* Заповняю неправильний масив символів, викликавши
    функцію попередньої обробки stopSymbolHeuristic() для
    заданого шаблону */
    stopSymbolHeuristic(pattern, m, stopSymbol);

    int shift = 0;
    while (shift <= (n - m)) {
        int j = m - 1;

        /* Продовжую зменшувати індекс j шаблону, поки символи
        шаблону та тексту збігаються при цьому зсуві shift */
        while (j >= 0 && pattern[j] == text[shift + j])
            j--;


        /* Якщо шаблон присутній під час поточного зсуву,
        то індекс j стане -1 після наведеного вище циклу. */
        if (j < 0) {
            std::cout << "pattern occurs at shift = " << shift << std::endl;

            /* Зміщую шаблон так, щоб наступний символ у тексті
            вирівнявся з останнім входженням у шаблон. Умова shift + m < n
            необхідна для випадку, коли шаблон зустрічається в кінці тексту. */
            shift += (shift + m < n) ? m - stopSymbol[text[shift + m]] : 1;

        } else
            /* Зміщую шаблон так, щоб неправильний символ у тексті
            вирівнявся з останнім входженням у шаблон. Функція max використовується,
            щоб переконатися, що ми отримуємо позитивний зсув. Ми можемо отримати
            негативний зсув, якщо останнє входження поганого символу в шаблоні
            знаходиться праворуч від поточного символу. */
            shift += std::max(1, j - stopSymbol[text[shift + j]]);
    }
}

void executionTime(std::string text, std::string pattern) {
    auto start = std::chrono::steady_clock::now();
    search(text, pattern);
    auto end = std::chrono::steady_clock::now();
    auto difference = end - start;
    std::cout << std::chrono::duration<double, std::milli>(difference).count() << "ms" << std::endl;
}

int main() {

    executionTime("ABAAABCDABAA", "ABC"); // середній показник часу
    std::cout << std::endl;

    executionTime("DDDDDDDDDDDDDDDDD", "DDDD"); // найгірший показник часу
    std::cout << std::endl;

    executionTime("DEMIAN", "MIA"); // найкращий показник часу
    std::cout << std::endl;

    return 0;
}



