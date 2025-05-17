#include <iostream>
#include <memory>
#include <string>

class Inventory {
private:
    std::unique_ptr<std::string[]> items;
    size_t capacity;
    size_t size;

    void resize() {
        capacity *= 2;
        std::unique_ptr<std::string[]> newItems(new std::string[capacity]);

        for (size_t i = 0; i < size; ++i) {
            newItems[i] = items[i];
        }

        items = std::move(newItems);
    }

public:
    Inventory() : capacity(5), size(0) {
        items.reset(new std::string[capacity]);
    }

    void addItem(const std::string& item) {
        if (size >= capacity) {
            resize();
        }
        items[size++] = item;
    }

    void displayInventory() const {
        if (size == 0) {
            std::cout << "Инвентарь пуст.\n";
            return;
        }

        std::cout << "=== Инвентарь ===\n";
        for (size_t i = 0; i < size; ++i) {
            std::cout << "- " << items[i] << "\n";
        }
        std::cout << "=================\n";
    }
};

int main() {
    Inventory inv;

    inv.addItem("Меч");
    inv.addItem("Щит");
    inv.addItem("Зелье здоровья");
    inv.addItem("Лук");
    inv.addItem("Стрелы");
    inv.addItem("Кольцо маны");

    inv.displayInventory();

    return 0;
}
