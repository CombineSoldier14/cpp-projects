#include <csignal>
#include <functional>
#include <iostream>
#include <string>
#include <random>
#include <map>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string version = "1.2.0";

std::ifstream f("settings.json");
json data = json::parse(f);

// the rng ranges might be off. not sure. have to test later.
int rangeRng(int lowest, int highest) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(lowest, highest);
    int rng = distr(gen);
    return rng;
}

int genericEx() {
    return 0;
}

class Player {
    public:
        std::string name;
        int health = 100;
        int max_health;
        int healingPotions;
        int attack(Player& opposingPlayer, int lowest, int highest, int testlowest, int testhighest, int hitSpecifier) {
            int testRng = rangeRng(testlowest, testhighest);
            if (testRng == hitSpecifier) {
                int hitRng = rangeRng(lowest, highest);
                opposingPlayer.health -= hitRng;
                std::cout << "\nThat's a hit! " << hitRng << " damage.\n\n";
                return 0;
            } else {
                std::cout << "\nThat's a miss!\n\n";
                return 1;
            }
        }

        int heal() {
            if (this->health >= 100) {
                return 2;
            }
            if (this->healingPotions <= 0) {
                return 3;
            }
            this->healingPotions -= 1;
            int healedHealth = rangeRng(3, 20);
            this->health += healedHealth;
            if (this->health > this->max_health) {
                int total = 0;
                while (this->health > this->max_health) {
                    total++;
                    this->health--;
                }
                healedHealth -= total;
            }
            std::cout << this->name << " healed " << healedHealth << " health!\n";
            return 0;
        }

        std::map<std::string, std::function<int()>> getList(Player& opposingPlayer) {
            std::map<std::string, std::function<int()>> attacks;
            attacks["Small Attack"] = [&]() { return attack(opposingPlayer, 1, 15, 0, 1, 1); };
            attacks["Large Attack"] = [&]() { return attack(opposingPlayer, 15, 30, 1, 3, 3); };
            attacks["Healing Potion"] = [&]() { return heal(); };
            return attacks;
        }
};

void finish(Player& winningPlayer, Player& losingPlayer) {
    std::cout << "\n " << winningPlayer.name << " has won the battle with " << winningPlayer.health<< " health!\n";
}

void turn(Player& player1, Player& player2) {
    std::cout << "-------------------------------------------------------\n";
    std::cout << "Current Turn: " << player1.name << "\n" << player1.name << "'s health: " << player1.health << "\n" << player2.name << "'s health: " << player2.health << "\n";
    std::map<std::string, std::function<int()>> attacks = player1.getList(player2);
    std::cout << "\nAttacks:\n";
    int index = 0;
    for(auto i: attacks) {
        std::cout << index + 1 << ". " << i.first << "\n"; 
        index++;
    }
    std::cout << "\nHealing Potions left: " << player1.healingPotions;
    std::cout << "\n-------------------------------------------------------\n";
    std::cout << "Type the name of your attack.\n";
    std::string x;
    std::cout << "> ";
    while (true) {
        std::getline(std::cin, x);
        try {
            int attak = attacks[x]();
            if (attak == 2) {
                std::cout << "You health is already at max!\n";
                std::cout << "> ";
            } else if (attak == 3) {
                std::cout << "You don't have any healing potions!\n";
                std::cout << "> ";
            } else {
                break;
            }
        }
        catch(std::bad_function_call) {
            std::cout << "Attack \"" << x <<"\" not found!\n";
            std::cout << "> ";
        }
    }
}

void start(Player& player1, Player& player2) {
    std::cout << "Made with BattleEngine v" << version << " by CombineSoldier14\n";
    std::cout << "-------------------------------------------------------\n";
    std::cout << "The battle has begun!\n" << player1.name << " vs " << player2.name << "\n\n";
    while (player1.health > 0 && player2.health > 0) {  // Fix the condition to end when both players' health are 0 or less
        turn(player1, player2);
        if (player2.health <= 0) { break; finish(player1, player2); }
        turn(player2, player1);
        if (player1.health <= 0) { break; finish(player2, player1); }
    }
    Player* losingPlayer;
    Player* winningPlayer;
    if (player1.health > 0) {
        winningPlayer = &player1;
        losingPlayer = &player2;
    } else {
        winningPlayer = &player2;
        losingPlayer = &player1;
    }
    finish(*winningPlayer, *losingPlayer);
}

int main() {
    Player john;
    john.name = data["PLAYER1"]["NAME"];
    john.health = data["PLAYER1"]["STARTING_HEALTH"];
    john.max_health = data["PLAYER1"]["STARTING_HEALTH"];
    john.healingPotions = data["PLAYER1"]["ATTACKS"]["HEALING_POTIONS"];
    Player tim;
    tim.name = data["PLAYER2"]["NAME"];
    tim.health = data["PLAYER2"]["STARTING_HEALTH"];
    tim.max_health = data["PLAYER2"]["STARTING_HEALTH"];
    tim.healingPotions = data["PLAYER2"]["ATTACKS"]["HEALING_POTIONS"];
    start(john, tim);
    return 0;
}
