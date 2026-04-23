#include<string>
#include<iostream>
#ifndef ROLE_HPP
#define ROLE_HPP
namespace final{
    
    class Fighter;
    class Protector;
    class Caster;

    class Base{
        friend class Fighter;
        friend class Protector;
        friend class Caster;
    private:
        std::string name;
        int health,attack;
        bool alive,defensive;
        static int aliveNumber;
    protected:
        Base(const std::string& name, const int health, const int attack)
            : name(name), health(health), attack(attack), alive(true), defensive(false) {
            aliveNumber++;
        }
    public:
        static int getAliveNumber() {
            return aliveNumber;
        }
        
        virtual ~Base() {
            if (alive) {
                aliveNumber--;
            }
        }
        
        virtual void launch_attack(Base* target) = 0;
        virtual void defend(bool flag) = 0;
        
        bool isAlive(){
            return alive;
        }

        bool isDefensive(){
            return defensive;
        }
    };

    int Base::aliveNumber = 0;

    class Fighter:public Base{
    public:
        Fighter (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                defensive = 1;
                health += 3;
                attack += 2;
            } else {
                defensive = 0;
            }
        }
    };

    class Protector:public Base{
    public:
        Protector (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                defensive = 1;
                health += 7;
                attack += 1;
            } else {
                defensive = 0;
            }
        }
    };

    class Caster:public Base{
    public:
        Caster (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                defensive = 1;
                health += 5;
            } else {
                defensive = 0;
            }
        }
    };

    void Fighter::launch_attack(Base *target) {
        int multiplier = 1;
        if (dynamic_cast<Caster*>(target)) {
            multiplier = 2;
        }
        
        if (!target->defensive) {
            target->health -= attack * multiplier;
        } else {
            int damage = attack * multiplier - target->attack;
            if (damage > 0) {
                target->health -= damage;
            }
            int counterDamage = target->attack;
            health -= counterDamage;
        }
        
        bool targetDied = false;
        if (target->health <= 0 && target->alive) {
            target->alive = false;
            aliveNumber--;
            targetDied = true;
            if (dynamic_cast<Fighter*>(target)) {
                std::cout << "Fighter " << target->name << " is killed\n";
            } else if (dynamic_cast<Protector*>(target)) {
                std::cout << "Protector " << target->name << " is killed\n";
            } else if (dynamic_cast<Caster*>(target)) {
                std::cout << "Caster " << target->name << " is killed\n";
            }
        }
        
        if (health <= 0 && alive) {
            alive = false;
            aliveNumber--;
            std::cout << "Fighter " << name << " is killed\n";
        }
    }

    void Protector::launch_attack(Base *target) {
        int multiplier = 1;
        if (dynamic_cast<Fighter*>(target)) {
            multiplier = 2;
        }
        
        if (!target->defensive) {
            target->health -= attack * multiplier;
        } else {
            int damage = attack * multiplier - target->attack;
            if (damage > 0) {
                target->health -= damage;
            }
            int counterDamage = target->attack;
            health -= counterDamage;
        }
        
        bool targetDied = false;
        if (target->health <= 0 && target->alive) {
            target->alive = false;
            aliveNumber--;
            targetDied = true;
            if (dynamic_cast<Fighter*>(target)) {
                std::cout << "Fighter " << target->name << " is killed\n";
            } else if (dynamic_cast<Protector*>(target)) {
                std::cout << "Protector " << target->name << " is killed\n";
            } else if (dynamic_cast<Caster*>(target)) {
                std::cout << "Caster " << target->name << " is killed\n";
            }
        }
        
        if (health <= 0 && alive) {
            alive = false;
            aliveNumber--;
            std::cout << "Protector " << name << " is killed\n";
        }
    }

    void Caster::launch_attack(Base *target) {
        int multiplier = 1;
        if (dynamic_cast<Protector*>(target)) {
            multiplier = 2;
        }
        
        if (!target->defensive) {
            target->health -= attack * multiplier;
        } else {
            int damage = attack * multiplier - target->attack;
            if (damage > 0) {
                target->health -= damage;
            }
            // Caster doesn't take counter damage
        }
        
        bool targetDied = false;
        if (target->health <= 0 && target->alive) {
            target->alive = false;
            aliveNumber--;
            targetDied = true;
            if (dynamic_cast<Fighter*>(target)) {
                std::cout << "Fighter " << target->name << " is killed\n";
            } else if (dynamic_cast<Protector*>(target)) {
                std::cout << "Protector " << target->name << " is killed\n";
            } else if (dynamic_cast<Caster*>(target)) {
                std::cout << "Caster " << target->name << " is killed\n";
            }
        }
        
        if (health <= 0 && alive) {
            alive = false;
            aliveNumber--;
            std::cout << "Caster " << name << " is killed\n";
        }
    }
}
#endif //ROLE_HPP
