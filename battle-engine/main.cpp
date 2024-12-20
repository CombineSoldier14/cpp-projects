#include <functional>
#include <iostream>
#include <string>
#include <random>
#include <map>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string version = "1.1.1";

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

class Player {
    public:
        std::string name;
        int health = 100;
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

        std::map<std::string, std::function<int()>> getList(Player& opposingPlayer) {
            std::map<std::string, std::function<int()>> attacks;
            attacks["Small Attack"] = [&]() { return attack(opposingPlayer, 0, 15, 0, 1, 1); };
            attacks["Large Attack"] = [&]() { return attack(opposingPlayer, 15, 30, 1, 3, 3); };
            return attacks;
        }
};

void finish(Player& winningPlayer, Player& losingPlayer) {
    std::cout << "\n " << winningPlayer.name << " has won the battle with " << winningPlayer.health<< " health!\n";
}

void turn(Player& player1, Player& player2) {
    std::cout << "-------------------------------------------------------\n";
    std::cout << "Current Turn: " << player1.name << "\n" << player1.name << " health: " << player1.health << "\n" << player2.name << " health: " << player2.health << "\n";
    std::map<std::string, std::function<int()>> attacks = player1.getList(player2);
    std::cout << "\nAttacks:\n";
    int index = 0;
    for(auto i: attacks) {
        std::cout << index + 1 << ". " << i.first << "\n"; 
        index++;
    }
    std::cout << "-------------------------------------------------------\n";
    std::cout << "Type the name of your attack.\n";
    std::string x;
    int flag = 0;
    std::cout << "> ";
    while (flag == 0) {
        std::getline(std::cin, x);
        try {
            attacks[x]();
            break;
        }
        catch(std::bad_function_call) {
            std::cout << "Attack \"" << x <<"\" not found!\n";
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
    john.health = data["PLAYER2"]["STARTING_HEALTH"];
    Player tim;
    tim.name = data["PLAYER2"]["NAME"];
    tim.health = data["PLAYER2"]["STARTING_HEALTH"];
    start(john, tim);
    return 0;
}