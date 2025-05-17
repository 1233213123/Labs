#include <iostream>
#include <string>
#include <algorithm>

class Character {
private:
    std::string name;
    int health;
    int attack;
    int defense;
    int maxHealth;

public:
    Character(const std::string& n, int h, int a, int d, int maxH = 100)
        : name(n), health(h), attack(a), defense(d), maxHealth(maxH) {}

    int getHealth() const {
        return health;
    }

    void displayInfo() const {
        std::cout << "Имя: " << name << ", Здоровье: " << health
                  << ", Атака: " << attack << ", Защита: " << defense << std::endl;
    }

    void attackEnemy(Character& enemy) {
        int damage = attack - enemy.defense;
        if (damage > 0) {
            enemy.takeDamage(damage);
            std::cout << name << " атакует " << enemy.name << " и наносит " << damage << " урона!" << std::endl;
        } else {
            std::cout << name << " атакует " << enemy.name << ", но атака не имеет эффекта!" << std::endl;
        }
    }

    void heal(int amount) {
        health = std::min(health + amount, maxHealth);
        std::cout << name << " лечится на " << amount << " HP!" << std::endl;
    }

    void takeDamage(int amount) {
        health = std::max(health - amount, 0);
        std::cout << name << " получает " << amount << " урона!" << std::endl;
    }
};

int main() {
    Character hero("Герой", 80, 20, 10, 100);
    Character monster("Гоблин", 50, 15, 5, 60);

    hero.displayInfo();
    monster.displayInfo();

    hero.attackEnemy(monster);
    monster.displayInfo();

    monster.attackEnemy(hero);
    hero.displayInfo();

    hero.heal(20);
    hero.displayInfo();

    monster.takeDamage(100);
    monster.displayInfo();

    return 0;
}

