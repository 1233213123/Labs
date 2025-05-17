#include <iostream>
#include <vector>
#include <memory>
#include <string>

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
        if (!elements.empty()) {
            std::cout << "Удален из очереди: " << elements.front() << std::endl;
            elements.erase(elements.begin());
        } else {
            std::cout << "Очередь пуста! Нельзя удалить." << std::endl;
        }
    }

    // Просмотр первого элемента в очереди
    T front() const {
        if (!elements.empty()) {
            return elements.front();
        }
        throw std::out_of_range("Очередь пуста!");
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
    // Тестирование очереди для строк
    std::cout << "=== Тестирование очереди строк ===" << std::endl;
    Queue<std::string> stringQueue;

    stringQueue.push("Первое сообщение");
    stringQueue.push("Второе сообщение");
    stringQueue.push("Третье сообщение");
    stringQueue.display();

    stringQueue.pop();
    stringQueue.display();

    stringQueue.pop();
    stringQueue.pop();
    stringQueue.pop(); // Попытка удалить из пустой очереди
    stringQueue.display();

    // Тестирование очереди для чисел
    std::cout << "\n=== Тестирование очереди чисел ===" << std::endl;
    Queue<int> intQueue;

    intQueue.push(10);
    intQueue.push(20);
    intQueue.push(30);
    intQueue.display();

    intQueue.pop();
    std::cout << "Первый элемент теперь: " << intQueue.front() << std::endl;
    intQueue.display();

    // Тестирование очереди для пользовательского типа
    std::cout << "\n=== Тестирование очереди Entity ===" << std::endl;
    Queue<Entity> entityQueue;

    entityQueue.push(Entity("Герой", 100));
    entityQueue.push(Entity("Гоблин", 50));
    entityQueue.push(Entity("Дракон", 200));
    entityQueue.display();

    entityQueue.pop();
    entityQueue.display();

    return 0;
}

