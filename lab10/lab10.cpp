#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <memory>
#include <stdexcept>

class User {
private:
    std::string name;
    int id;
    int accessLevel;

public:
    User(std::string name, int id, int accessLevel) : name(name), id(id), accessLevel(accessLevel) {
        if (name.empty()) {
            throw std::invalid_argument("Имя пользователя не может быть пустым.");
        }
        if (accessLevel < 0) {
            throw std::invalid_argument("Уровень доступа не может быть отрицательным.");
        }
    }

    std::string getName() const { return name; }
    int getId() const { return id; }
    int getAccessLevel() const { return accessLevel; }

    void setName(std::string name) {
        if (name.empty()) {
            throw std::invalid_argument("Имя пользователя не может быть пустым.");
        }
        this->name = name;
    }
    void setAccessLevel(int accessLevel) {
        if (accessLevel < 0) {
            throw std::invalid_argument("Уровень доступа не может быть отрицательным.");
        }
        this->accessLevel = accessLevel;
    }

    virtual void displayInfo() const {
        std::cout << "Имя: " << name << ", ID: " << id << ", Уровень доступа: " << accessLevel;
    }
    virtual std::string getType() const { return "User"; }
};

class Student : public User {
private:
    std::string group;

public:
    Student(std::string name, int id, int accessLevel, std::string group) : User(name, id, accessLevel), group(group) {}

    std::string getGroup() const { return group; }
    void setGroup(std::string group) { this->group = group; }

    void displayInfo() const override {
        User::displayInfo();
        std::cout << ", Группа: " << group;
    }
    std::string getType() const override { return "Student"; }
};

class Teacher : public User {
private:
    std::string department;

public:
    Teacher(std::string name, int id, int accessLevel, std::string department) : User(name, id, accessLevel), department(department) {}

    std::string getDepartment() const { return department; }
    void setDepartment(std::string department) { this->department = department; }

    void displayInfo() const override {
        User::displayInfo();
        std::cout << ", Департамент: " << department;
    }
    std::string getType() const override { return "Teacher"; }
};

class Administrator : public User {
private:
    std::string role;

public:
    Administrator(std::string name, int id, int accessLevel, std::string role) : User(name, id, accessLevel), role(role) {}

    std::string getRole() const { return role; }
    void setRole(std::string role) { this->role = role; }

    void displayInfo() const override {
        User::displayInfo();
        std::cout << ", Роль: " << role;
    }
    std::string getType() const override { return "Administrator"; }
};

class Resource {
private:
    std::string name;
    int requiredAccessLevel;

public:
    Resource(std::string name, int requiredAccessLevel) : name(name), requiredAccessLevel(requiredAccessLevel) {}

    std::string getName() const { return name; }
    int getRequiredAccessLevel() const { return requiredAccessLevel; }

    bool checkAccess(const User& user) const {
        return user.getAccessLevel() >= requiredAccessLevel;
    }
};

template <typename T>
class AccessControlSystem {
private:
    std::vector<std::unique_ptr<User>> users;
    std::vector<Resource> resources;

public:
    void addUser(std::unique_ptr<User> user) {
        users.push_back(std::move(user));
    }

    void addResource(const Resource& resource) {
        resources.push_back(resource);
    }

    bool checkAccess(int userId, const std::string& resourceName) const {
        User* user = findUserById(userId);
        if (!user) return false;

        for (const auto& resource : resources) {
            if (resource.getName() == resourceName) {
                return resource.checkAccess(*user);
            }
        }
        return false;
    }
    User* findUserById(int id) const {
        for (const auto& user : users) {
            if (user->getId() == id) {
                return user.get();
            }
        }
        return nullptr;
    }
    std::vector<User*> findUsersByName(const std::string& name) const {
        std::vector<User*> foundUsers;
        for (const auto& user : users) {
            if (user->getName() == name) {
                foundUsers.push_back(user.get());
            }
        }
        return foundUsers;
    }
    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл для записи.");
        }

        for (const auto& user : users) {
            file << user->getType() << ",";
            file << user->getName() << "," << user->getId() << "," << user->getAccessLevel() << ",";

            if (user->getType() == "Student") {
                Student* student = dynamic_cast<Student*>(user.get());
                file << student->getGroup();
            } else if (user->getType() == "Teacher") {
                Teacher* teacher = dynamic_cast<Teacher*>(user.get());
                file << teacher->getDepartment();
            } else if (user->getType() == "Administrator") {
                Administrator* administrator = dynamic_cast<Administrator*>(user.get());
                file << administrator->getRole();
            }
            file << std::endl;
        }

        for (const auto& resource : resources) {
            file << "Resource," << resource.getName() << "," << resource.getRequiredAccessLevel() << std::endl;
        }

        file.close();
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл для чтения.");
        }

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string type;
            std::getline(ss, type, ',');

            if (type == "User") {
                std::string name, idStr, accessLevelStr;
                std::getline(ss, name, ',');
                std::getline(ss, idStr, ',');
                std::getline(ss, accessLevelStr, ',');

                int id = std::stoi(idStr);
                int accessLevel = std::stoi(accessLevelStr);

                addUser(std::unique_ptr<User>(new User(name, id, accessLevel)));
            } else if (type == "Student") {
                std::string name, idStr, accessLevelStr, group;
                std::getline(ss, name, ',');
                std::getline(ss, idStr, ',');
                std::getline(ss, accessLevelStr, ',');
                std::getline(ss, group, ',');

                int id = std::stoi(idStr);
                int accessLevel = std::stoi(accessLevelStr);

                addUser(std::unique_ptr<Student>(new Student(name, id, accessLevel, group)));
            } else if (type == "Teacher") {
                std::string name, idStr, accessLevelStr, department;
                std::getline(ss, name, ',');
                std::getline(ss, idStr, ',');
                std::getline(ss, accessLevelStr, ',');
                std::getline(ss, department, ',');

                int id = std::stoi(idStr);
                int accessLevel = std::stoi(accessLevelStr);

                addUser(std::unique_ptr<Teacher>(new Teacher(name, id, accessLevel, department)));
            } else if (type == "Administrator") {
                std::string name, idStr, accessLevelStr, role;
                std::getline(ss, name, ',');
                std::getline(ss, idStr, ',');
                std::getline(ss, accessLevelStr, ',');
                std::getline(ss, role, ',');

                int id = std::stoi(idStr);
                int accessLevel = std::stoi(accessLevelStr);

                addUser(std::unique_ptr<Administrator>(new Administrator(name, id, accessLevel, role)));
            } else if (type == "Resource") {
                std::string name, requiredAccessLevelStr;
                std::getline(ss, name, ',');
                std::getline(ss, requiredAccessLevelStr, ',');

                int requiredAccessLevel = std::stoi(requiredAccessLevelStr);

                addResource(Resource(name, requiredAccessLevel));
            }
        }

        file.close();
    }

    void sortUsersByAccessLevel() {
        std::sort(users.begin(), users.end(), [](const std::unique_ptr<User>& a, const std::unique_ptr<User>& b) {
            return a->getAccessLevel() < b->getAccessLevel();
        });
    }

    void displayAllUsers() const {
        for (const auto& user : users) {
            user->displayInfo();
            std::cout << std::endl;
        }
    }

};

int main() {
    AccessControlSystem<User> system;

    try {
        system.loadFromFile("data.txt");
    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка при загрузке данных: " << e.what() << std::endl;
    }

   

    system.sortUsersByAccessLevel();
    system.displayAllUsers();

    
    int userId1 = 12345; 
    int userId2 = 67890; 
    std::string resourceName1 = "Аудитория 101"; 
    std::string resourceName2 = "Лаборатория";  

    std::cout << "Доступ к " << resourceName1 << " для пользователя с ID " << userId1 << ": " << (system.checkAccess(userId1, resourceName1) ? "Разрешен" : "Запрещен") << std::endl;
    std::cout << "Доступ к " << resourceName2 << " для пользователя с ID " << userId1 << ": " << (system.checkAccess(userId1, resourceName2) ? "Разрешен" : "Запрещен") << std::endl;
    std::cout << "Доступ к " << resourceName2 << " для пользователя с ID " << userId2 << ": " << (system.checkAccess(userId2, resourceName2) ? "Разрешен" : "Запрещен") << std::endl;

    try {
        system.saveToFile("data.txt");
    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка при сохранении данных: " << e.what() << std::endl;
    }

    return 0;
}
