
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

template<typename T>
class Logger {
public:
    static void log(const T& message) {
        std::ofstream file("game_log.txt", std::ios::app);
        file << message << std::endl;
    }
};

class Inventory {
private:
    std::vector<std::string> items;
public:
    void addItem(const std::string& item) {
        items.push_back(item);
        Logger<std::string>::log("Добавлен предмет: " + item);
    }
    void showItems() const {
        std::cout << "Инвентарь: ";
        for (const auto& item : items) std::cout << item << ", ";
        std::cout << std::endl;
    }
    const std::vector<std::string>& getItems() const { return items; }
};

class Character {
private:
    std::string name;
    int health, attack, defense, level, experience;
    Inventory inventory;

public:
    Character(const std::string& n, int h, int a, int d)
        : name(n), health(h), attack(a), defense(d), level(1), experience(0) {}

    void takeDamage(int dmg) {
        health -= dmg;
        if (health <= 0) {
            health = 0;
            throw std::runtime_error(name + " погиб!");
        }
    }

    void attackEnemy(class Enemy& monster);

    void gainExperience(int exp) {
        experience += exp;
        if (experience >= 100) {
            level++;
            experience -= 100;
            std::cout << name << " повысил уровень до " << level << "!" << std::endl;
            Logger<std::string>::log(name + " повысил уровень до " + std::to_string(level));
        }
    }

    void heal(int amount) {
        health += amount;
        if (health > 100) {
            health = 100;
        }
        std::cout << name << " восстановил " << amount << " HP!" << std::endl;
        Logger<std::string>::log(name + " восстановил " + std::to_string(amount) + " HP");
    }


    void displayInfo() const {
        std::cout << "Имя: " << name << ", HP: " << health
                  << ", Атака: " << attack << ", Защита: " << defense
                  << ", Уровень: " << level << ", Опыт: " << experience << std::endl;
    }

    void showInventory() const {
        inventory.showItems();
    }

    const std::string& getName() const { return name; }
    int getHealth() const { return health; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    Inventory& getInventory() { return inventory; }

    void setHealth(int newHealth) { health = newHealth; }
    void setAttack(int newAttack) { attack = newAttack; }
    void setDefense(int newDefense) { defense = newDefense; }
    void setLevel(int newLevel) { level = newLevel; }
    void setExperience(int newExperience) { experience = newExperience; }

    int getLevel() const { return level; }
    int getExperience() const { return experience; }

};


class Enemy {
protected:
    std::string name;
    int health;
    int attack;
    int defense;

public:
    virtual ~Enemy() {}
    virtual void displayInfo() const {
        std::cout << "Монстр: " << name << ", HP: " << health << std::endl;
    }
    virtual void takeDamage(int dmg) {
        health -= dmg;
        if (health <= 0) throw std::runtime_error(name + " убит!");
    }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    const std::string& getName() const { return name; }

    int getHealth() const { return health; }
    virtual void setHealth(int newHealth) { health = newHealth; }
};

class Goblin : public Enemy {
public:
    Goblin() { name = "Гоблин"; health = 25; attack = 8; defense = 5; }
};


class Skeleton : public Enemy {
public:
    Skeleton() { name = "Скелет"; health = 50; attack = 15; defense = 10; }
};

class Dragon : public Enemy {
public:
    Dragon() { name = "Дракон"; health = 100; attack = 25; defense = 15; }
};

void Character::attackEnemy(Enemy& monster) {
    int damage = attack - monster.getDefense();
    if (damage > 0) {
        std::cout << name << " атакует " << monster.getName() << " и наносит " << damage << " урона!" << std::endl;
        Logger<std::string>::log(name + " атакует " + monster.getName() + " и наносит " + std::to_string(damage) + " урона!");
        monster.takeDamage(damage);
    } else {
        std::cout << name << " атакует " << monster.getName() << " без урона!" << std::endl;
    }
}

class Game {
private:
    Character player;

public:
    Game(const std::string& playerName) : player(playerName, 100, 20, 5) {}

    void start() {
        std::cout << "Игра началась!" << std::endl;
        Logger<std::string>::log("Начало игры.");
        player.displayInfo();
        player.showInventory();
    }

    void battle(Enemy& monster) {
        std::cout << "Начало битвы с " << monster.getName() << "!" << std::endl;
        Logger<std::string>::log("Начало битвы с " + monster.getName());
        try {
            while (true) {
                std::cout << "Ваш ход.  (1) Атаковать  (2) Показать инвентарь  (3) Выйти из битвы: ";
                int choice;
                std::cin >> choice;

                if (choice == 1) {
                    player.attackEnemy(monster);
                    if (monster.getHealth() <= 0) {
                        std::cout << monster.getName() << " повержен!" << std::endl;
                        player.gainExperience(50);
                        Logger<std::string>::log(monster.getName() + " повержен!");
                        break;
                    }
                } else if (choice == 2) {
                    player.showInventory();
                    continue;
                } else if (choice == 3) {
                    std::cout << "Вы сбежали из битвы." << std::endl;
                    Logger<std::string>::log("Игрок сбежал из битвы с " + monster.getName());
                    return;
                } else {
                    std::cout << "Неверный выбор. Попробуйте еще раз." << std::endl;
                    continue;
                }

                player.takeDamage(monster.getAttack() - player.getDefense());
                std::cout << monster.getName() << " атакует " << player.getName() << "!" << std::endl;
                player.displayInfo();
                monster.displayInfo();
                if (player.getHealth() <= 0) {
                    break;
                }
            }
        } catch (const std::runtime_error& e) {
            std::cout << e.what() << std::endl;
            Logger<std::string>::log(e.what());
        }
        std::cout << "Битва окончена!" << std::endl;
    }

    void saveGame() {
        std::ofstream file("save.txt");
        if (!file) throw std::runtime_error("Невозможно открыть файл для сохранения!");
        file << player.getName() << "\n"
             << player.getHealth() << "\n"
             << player.getAttack() << "\n"
             << player.getDefense() << "\n"
             << player.getLevel() << "\n"
             << player.getExperience() << "\n";

        for (const auto& item : player.getInventory().getItems()) file << item << " ";
        file << std::endl;

        std::cout << "Игра сохранена!" << std::endl;
        Logger<std::string>::log("Игра сохранена.");
    }

    void loadGame() {
        std::ifstream file("save.txt");
        if (!file) throw std::runtime_error("Невозможно открыть файл для загрузки!");

        std::string name;
        int health, attack, defense, level, experience;

        std::getline(file, name);
        file >> health >> attack >> defense >> level >> experience;
        file.ignore();

        player = Character(name, health, attack, defense);
        player.setHealth(health);
        player.setAttack(attack);
        player.setDefense(defense);
        player.setLevel(level);
        player.setExperience(experience);

        std::string item;
        while (file >> item) {
            player.getInventory().addItem(item);
        }
        std::cout << "Игра загружена!" << std::endl;
        Logger<std::string>::log("Игра загружена.");
    }

    Character& getPlayer() {
        return player;
    }

    void gameLoop() {
        int choice;
        while (true) {
            std::cout << "\nВыберите действие:\n";
            std::cout << "1. Начать битву с скелетом\n";
            std::cout << "2. Начать битву с гоблином\n";
            std::cout << "3. Добавить предмет в инвентарь\n";
            std::cout << "4. Показать инвентарь\n";
            std::cout << "5. Сохранить игру\n";
            std::cout << "6. Загрузить игру\n";
            std::cout << "7. Выйти из игры\n";
            std::cout << "Ваш выбор: ";
            std::cin >> choice;

            switch (choice) {
                case 1: {
                    Skeleton skeleton;
                    battle(skeleton);
                    break;
                }
                case 2: {
                    Goblin goblin;
                    battle(goblin);
                    break;
                }
                case 3: {
                    std::string newItem;
                    std::cout << "Введите название предмета: ";
                    std::cin >> newItem;
                    player.getInventory().addItem(newItem);
                    break;
                }
                case 4:
                    player.showInventory();
                    break;
                case 5:
                    saveGame();
                    break;
                case 6:
                    try {
                        loadGame();
                    } catch (const std::runtime_error& e) {
                        std::cerr << "Ошибка загрузки: " << e.what() << std::endl;
                        Logger<std::string>::log("Ошибка загрузки: " + std::string(e.what()));
                    }
                    break;
                case 7:
                    std::cout << "Выход из игры.\n";
                    Logger<std::string>::log("Выход из игры.");
                    return;
                default:
                    std::cout << "Неверный выбор. Попробуйте еще раз.\n";
            }
        }
    }
};

int main() {
    try {
        std::string playerName;
        std::cout << "Введите имя вашего героя: ";
        std::cin >> playerName;

        Game game(playerName);
        game.start();

        game.gameLoop();


    } catch (const std::runtime_error& error) {
        std::cerr << "Ошибка: " << error.what() << std::endl;
        Logger<std::string>::log("Ошибка: " + std::string(error.what()));
        return 1;
    }

    return 0;
}