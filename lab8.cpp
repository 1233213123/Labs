#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int age;
    std::string email;
    std::string address;

public:
    // Геттеры
    std::string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    std::string getEmail() const {
        return email;
    }

    std::string getAddress() const {
        return address;
    }

    // Сеттеры
    void setName(const std::string& newName) {
        if (!newName.empty()) {
            name = newName;
        } else {
            std::cerr << "Ошибка: Имя не может быть пустым!" << std::endl;
        }
    }

    void setAge(int newAge) {
        if (newAge >= 0 && newAge <= 120) {
            age = newAge;
        } else {
            std::cerr << "Ошибка: Возраст должен быть от 0 до 120!" << std::endl;
        }
    }

    void setEmail(const std::string& newEmail) {
        if (newEmail.find('@') != std::string::npos) {
            email = newEmail;
        } else {
            std::cerr << "Ошибка: Некорректный формат email!" << std::endl;
        }
    }

    void setAddress(const std::string& newAddress) {
        if (!newAddress.empty()) {
            address = newAddress;
        } else {
            std::cerr << "Ошибка: Адрес не может быть пустым!" << std::endl;
        }
    }

    // Метод для вывода информации о человеке
    void displayInfo() const {
        std::cout << "Имя: " << name << ", Возраст: " << age << ", Email: " << email << ", Адрес: " << address << std::endl;
    }
};

int main() {
    Person person;

    person.setName("Иван Иванов");
    person.setAge(30);
    person.setEmail("ivan.ivanov@example.com");
    person.setAddress("ул. Ленина, 1");

    std::cout << "Имя: " << person.getName() << std::endl;
    std::cout << "Возраст: " << person.getAge() << std::endl;
    std::cout << "Email: " << person.getEmail() << std::endl;
    std::cout << "Адрес: " << person.getAddress() << std::endl;

    person.setName("");
    person.setAge(150);
    person.setEmail("invalid-email");
    person.setAddress("");

    person.displayInfo();

    return 0;
}

