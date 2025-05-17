#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstdlib>

class Character {
private:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    Character(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {}

    void displayInfo() const {
        std::cout << "Имя: " << name << ", Здоровье: " << health
                  << ", Атака: " << attack << ", Защита: " << defense << std::endl;
    }

    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    int getHealth() const { return health; }
    std::string getName() const { return name; }

    void setHealth(int h) { health = h; }
};

class Monster {
private:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    Monster(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d) {}

    void displayInfo() const {
        std::cout << "Имя: " << name << ", Здоровье: " << health
                  << ", Атака: " << attack << ", Защита: " << defense << std::endl;
    }

    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    int getHealth() const { return health; }
    std::string getName() const { return name; }

    void setHealth(int h) { health = h; }
};

std::mutex battleMutex;

void battle(Character& hero, Monster& monster) {
    while (hero.getHealth() > 0 && monster.getHealth() > 0) {
        std::lock_guard<std::mutex> lock(battleMutex);

        // Герой атакует
        int heroDamage = hero.getAttack() - monster.getDefense();
        if (heroDamage > 0) {
            int newMonsterHealth = monster.getHealth() - heroDamage;
            monster.setHealth(newMonsterHealth);
            std::cout << hero.getName() << " атакует " << monster.getName() << " и наносит " << heroDamage << " урона." << std::endl;
        } else {
            std::cout << hero.getName() << " не может пробить защиту " << monster.getName() << "." << std::endl;
        }

        if (monster.getHealth() <= 0) {
            std::cout << monster.getName() << " повержен!" << std::endl;
            break;
        }

        // Монстр атакует
        int monsterDamage = monster.getAttack() - hero.getDefense();
        if (monsterDamage > 0) {
            int newHeroHealth = hero.getHealth() - monsterDamage;
            hero.setHealth(newHeroHealth);
            std::cout << monster.getName() << " атакует " << hero.getName() << " и наносит " << monsterDamage << " урона." << std::endl;
        } else {
            std::cout << monster.getName() << " не может пробить защиту " << hero.getName() << "." << std::endl;
        }

        if (hero.getHealth() <= 0) {
            std::cout << hero.getName() << " повержен!" << std::endl;
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::lock_guard<std::mutex> lock(battleMutex);
    std::cout << "Бой окончен!" << std::endl;
    hero.displayInfo();
    monster.displayInfo();
}

int main() {
    Character hero("Герой", 100, 20, 10);
    Monster monster("Гоблин", 70, 15, 5);

    std::thread battleThread(battle, std::ref(hero), std::ref(monster));

    battleThread.join();

    return 0;
}