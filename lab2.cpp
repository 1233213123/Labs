#include <iostream>
#include <string>

class Character {
private:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    Character(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {
        std::cout << "Персонаж " << name << " создан!\n";
    }

    ~Character() {
        std::cout << "Персонаж " << name << " уничтожен!\n";
    }

    void displayInfo() const {
        std::cout << "Имя: " << name << ", Здоровье: " << health
                  << ", Атака: " << attack << ", Защита: " << defense << std::endl;
    }
};

class Monster {
private:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    Monster(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {
        std::cout << "Монстр " << name << " создан!\n";
    }

    ~Monster() {
        std::cout << "Монстр " << name << " уничтожен!\n";
    }

    void displayInfo() const {
        std::cout << "Имя: " << name << ", Здоровье: " << health
                  << ", Атака: " << attack << ", Защита: " << defense << std::endl;
    }
};

class Weapon {
private:
    std::string name;
    int damage;
    int weight;

public:
    Weapon(const std::string& n, int d, int w) : name(n), damage(d), weight(w) {
        std::cout << "Оружие " << name << " создано!\n";
    }

    ~Weapon() {
        std::cout << "Оружие " << name << " уничтожено!\n";
    }

    void displayInfo() const {
        std::cout << "Название: " << name << ", Урон: " << damage << ", Вес: " << weight << std::endl;
    }
};

int main() {
    Character hero("Герой", 100, 20, 10);
    Monster monster("Гоблин", 50, 10, 5);

    Weapon sword("Меч", 15, 5);
    Weapon axe("Топор", 20, 8);
    Weapon dagger("Кинжал", 10, 2);

    hero.displayInfo();
    monster.displayInfo();

    sword.displayInfo();
    axe.displayInfo();
    dagger.displayInfo();

    return 0;
}