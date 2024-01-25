#include <iostream>
#include <string>
#include <vector>

// Прототип Посередника
class Mediator {
public:
    virtual void sendMessage(const class Colleague* sender, const std::string& message) const = 0;
    virtual ~Mediator() = default;
};

// Абстрактний клас Колега
class Colleague {
public:
    virtual void sendMessage(const std::string& message) const = 0;
    virtual void receiveMessage(const std::string& message) const = 0;
    virtual void setMediator(std::shared_ptr<Mediator> mediator) = 0;
    virtual ~Colleague() = default;
};

// Конкретний клас Колега
class ConcreteColleague : public Colleague {
public:
    ConcreteColleague(const std::string& name) : name_(name) {}

    void sendMessage(const std::string& message) const override {
        mediator_->sendMessage(this, message);
    }

    void receiveMessage(const std::string& message) const override {
        std::cout << name_ << " received message: " << message << "\n";
    }

    void setMediator(std::shared_ptr<Mediator> mediator) override {
        mediator_ = mediator;
    }

private:
    std::string name_;
    std::shared_ptr<Mediator> mediator_;
};

// Конкретний клас Посередника
class ConcreteMediator : public Mediator {
public:
    void addColleague(std::shared_ptr<Colleague> colleague) {
        colleagues_.push_back(colleague);
    }

    void sendMessage(const Colleague* sender, const std::string& message) const override {
        for (const auto& colleague : colleagues_) {
            if (colleague.get() != sender) {
                colleague->receiveMessage(message);
            }
        }
    }

private:
    std::vector<std::shared_ptr<Colleague>> colleagues_;
};

int main() {
    // Використання паттерна "Посередник"
    std::shared_ptr<ConcreteMediator> mediator = std::make_shared<ConcreteMediator>();

    std::shared_ptr<Colleague> colleague1 = std::make_shared<ConcreteColleague>("Colleague 1");
    std::shared_ptr<Colleague> colleague2 = std::make_shared<ConcreteColleague>("Colleague 2");

    colleague1->setMediator(mediator);
    colleague2->setMediator(mediator);

    mediator->addColleague(colleague1);
    mediator->addColleague(colleague2);

    colleague1->sendMessage("Hello from Colleague 1");
    colleague2->sendMessage("Hi from Colleague 2");

    return 0;
}
