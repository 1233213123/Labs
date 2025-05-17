#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept> // Для исключений

// Шаблонный класс Queue (очередь)
template <typename T>
class Queue {
private:
    std::vector<T> elements;

public:
    // Добавление элемента в конец очереди
    void push(const T& item) {
        elements.push_back(item);
        std::cout << "Добавлен в очередь: " << item << std::endl;
    }

    // Удаление элемента из начала очереди
    void pop() {
        if (elements.empty()) {
            throw std::out_of_range("Попытка удаления из пустой очереди!");
        }
        std::cout << "Удален из очереди: " << elements.front() << std::endl;
        elements.erase(elements.begin());
    }

    // Просмотр первого элемента в очереди
    T front() const {
        if (elements.empty()) {
            throw std::out_of_range("Очередь пуста!");
        }
        return elements.front();
    }

    // Проверка на пустоту
    bool empty() const {
        return elements.empty();
    }

    // Получение размера очереди
    size_t size() const {
        return elements.size();
    }

    // Вывод содержимого очереди
    void display() const {
        if (empty()) {
            std::cout << "Очередь пуста." << std::endl;
            return;
        }

        std::cout << "Содержимое очереди (" << size() << " элементов): ";
        for (const auto& item : elements) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

// Пример класса Entity для демонстрации работы с пользовательскими типами
class Entity {
protected:
    std::string name;
    int health;

public:
    Entity(const std::string& n, int h) : name(n), health(h) {}

    friend std::ostream& operator<<(std::ostream& os, const Entity& entity) {
        os << entity.name << " (Здоровье: " << entity.health << ")";
        return os;
    }
};

int main() {
    // Тестирование обработки исключений в очереди
    std::cout << "=== Тестирование исключений в очереди ===" << std::endl;
    Queue<int> intQueue;

    try {
        intQueue.pop(); // Попытка удалить из пустой очереди
    } catch (const std::out_of_range& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    intQueue.push(10);
    intQueue.push(20);
    intQueue.display();

    try {
        std::cout << "Первый элемент: " << intQueue.front() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    intQueue.pop();
    intQueue.pop();
    try {
        intQueue.front(); // попытка доступа к первому элементу в пустой очереди
    } catch (const std::out_of_range& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
