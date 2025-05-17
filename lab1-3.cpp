#include <iostream>
#include <string>

class Entity {
public:
    std::string name;
    int health;
    int attackDamage;
    int defense;

    Entity(std::string name, int health, int attackDamage, int defense) :
        name(name), health(health), attackDamage(attackDamage), defense(defense) {}

    virtual void displayInfo() {
        std::cout << "Имя: " << name << std::endl;
        std::cout << "Здоровье: " << health << std::endl;
        std::cout << "Атака: " << attackDamage << std::endl;
        std::cout << "Защита: " << defense << std::endl;
    }

    virtual void attack(Entity& target) {
        int damage = attackDamage - target.defense;
        if (damage < 0) {
            damage = 0;
        }
        target.takeDamage(damage);
        std::cout << name << " атакует " << target.name << " и наносит " << damage << " урона!" << std::endl;
    }

    virtual void takeDamage(int damage) {
        health -= damage;
        std::cout << name << " получает " << damage << " урона!" << std::endl;
        if (health <= 0) {
            std::cout << name << " повержен!" << std::endl;
        }
    }

    virtual void heal(int amount) {
        health += amount;
        std::cout << name << " восстанавливает " << amount << " здоровья!" << std::endl;
    }

};

class Hero : public Entity {
public:
    Hero(std::string name, int health, int attackDamage, int defense) : Entity(name, health, attackDamage, defense) {}
};

class Monster : public Entity {
public:
    Monster(std::string name, int health, int attackDamage, int defense) : Entity(name, health, attackDamage, defense) {}
};

class Boss : public Entity {
public:
    Boss(std::string name, int health, int attackDamage, int defense) : Entity(name, health, attackDamage, defense) {}
};


int main() {
    Hero hero("Герой", 100, 20, 10);
    Monster goblin("Гоблин", 50, 15, 5);
    Boss dragon("Дракон", 150, 25, 20);

    Entity* entities[] = { &hero, &goblin, &dragon };

    for (auto& entity : entities) {
        entity->displayInfo();
    }


    hero.attack(goblin);
    goblin.attack(hero);
    dragon.attack(hero);

    hero.heal(20);
    return 0;
}

