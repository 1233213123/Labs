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
        : name(n), health(h), attack(a), defense(d) {}

    bool operator==(const Character& other) const {
        return name == other.name && health == other.health;
    }

    friend std::ostream& operator<<(std::ostream& os, const Character& character) {
        os << "Персонаж: " << character.name << ", Здоровье: " << character.health
           << ", Атака: " << character.attack << ", Защита: " << character.defense;
        return os;
    }
};

class Weapon {
private:
    std::string name;
    int damage;
    int weight;

public:
    Weapon(const std::string& n, int d, int w) : name(n), damage(d), weight(w) {}

    // Перегрузка оператора +
    Weapon operator+(const Weapon& other) const {
        return Weapon(name + "+" + other.name, damage + other.damage, weight + other.weight);
    }

    // Перегрузка оператора >
    bool operator>(const Weapon& other) const {
        return damage > other.damage;
    }

    friend std::ostream& operator<<(std::ostream& os, const Weapon& weapon) {
        os << "Оружие: " << weapon.name << ", Урон: " << weapon.damage
           << ", Вес: " << weapon.weight;
        return os;
    }

    int getDamage() const { return damage; } // Добавлено для main()
};

int main() {
    Character hero1("Герой", 100, 20, 10);
    Character hero2("Герой", 100, 20, 10);
    Character hero3("Воин", 150, 25, 15);

    if (hero1 == hero2) {
        std::cout << "Герой1 и Герой2 одинаковые!\n";
    }
    if (!(hero1 == hero3)) {
        std::cout << "Герой1 и Герой3 разные!\n";
    }

    std::cout << hero1 << std::endl;

    Weapon sword("Меч", 20, 5);
    Weapon bow("Лук", 15, 3);

    Weapon combinedWeapon = sword + bow;
    std::cout << combinedWeapon << std::endl;

    if (sword > bow) {
        std::cout << "Меч наносит больше урона, чем лук!\n";
    } else {
        std::cout << "Лук наносит больше урона, чем меч, или урон одинаковый!\n";
    }

    return 0;
}