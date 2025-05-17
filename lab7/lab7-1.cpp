#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class Entity {
public:
    std::string name;
    int health;
    int level;

    Entity(std::string name, int health, int level) : name(name), health(health), level(level) {}

    virtual ~Entity() {}

    virtual void display() {
        std::cout << "Имя: " << name << ", Здоровье: " << health << ", Уровень: " << level << std::endl;
    }

    virtual std::string getType() { return "Entity"; }
};

class Player : public Entity {
public:
    Player(std::string name, int health, int level) : Entity(name, health, level) {}

     virtual std::string getType() { return "Player"; }
};


template <typename T>
class GameManager {
public:
    std::vector<T> entities;

    void addEntity(T entity) {
        entities.push_back(entity);
    }

    void displayAll() {
        for (auto& entity : entities) {
            entity->display();
        }
    }

    ~GameManager() {
        for (auto& entity : entities) {
            delete entity;
        }
    }
};

void saveToFile(const GameManager<Entity*>& manager, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл для записи.");
    }

    file << manager.entities.size() << std::endl; // Save number of entities

    for (const auto& entity : manager.entities) {
        file << entity->getType() << std::endl;
        file << entity->name << std::endl;
        file << entity->health << std::endl;
        file << entity->level << std::endl;
    }

    file.close();
}

void loadFromFile(GameManager<Entity*>& manager, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл для чтения.");
    }

    int entityCount;
    file >> entityCount;
    file.ignore(); // Consume newline after reading the count

    for (int i = 0; i < entityCount; ++i) {
        std::string type;
        std::string name;
        int health;
        int level;

        std::getline(file, type);
        std::getline(file, name);
        file >> health;
        file >> level;
        file.ignore(); // Consume newline after reading level

        if (type == "Player") {
            manager.addEntity(new Player(name, health, level));
        } else {
            manager.addEntity(new Entity(name, health, level)); // Default to Entity if type is unknown
        }
    }

    file.close();
}

int main() {
    GameManager<Entity*> manager;
    manager.addEntity(new Player("Hero", 100, 1));
    manager.addEntity(new Entity("Goblin", 50, 1));

    saveToFile(manager, "game_save.txt");

    GameManager<Entity*> loadedManager;
    loadFromFile(loadedManager, "game_save.txt");
    std::cout << "Загруженные данные:" << std::endl;
    loadedManager.displayAll();

    return 0;
}
