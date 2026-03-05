#include "../include/graph.h"
#include <windows.h>
int main()
 {SetConsoleOutputCP(65001);
    CityGraph ukraine;
    
// Завантажуємо дані про міста та відстані з твого файлу
    ukraine.loadFromFile("data/ukraine_map.txt");

//ДОДАЄМО ЦЕЙ БЛОК ДЛЯ ВІЗУАЛІЗАЦІЇ КАРТИ
    std::cout << "--- Ukraine Road Map (Visual Graph) ---" << std::endl;
    ukraine.visualizeMap(); 

    std::cout << "--- Shortest Path Calculation ---" << std::endl;
    
// Шукаємо шлях між містами (наприклад, Київ та Одеса)
    ukraine.findShortestPath("Kyiv", "Odessa");

    std::cout << "\nPress Enter to exit..." << std::endl;
    
// Чекаємо натискання клавіші, щоб вікно не закрилося
    std::cin.clear();
    std::cin.get(); 

    return 0;
}