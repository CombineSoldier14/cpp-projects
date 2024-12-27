#include <csignal>
#include <functional>
#include <iostream>
#include <string>
#include <random>
#include <map>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string version = "1.3.4";

std::ifstream f("settings.json");
json data = json::parse(f);


std::string getDivider() {
    std::string divider = "";
    int loopnum = 0;
    while (loopnum <= 56) {
        divider.append(data["DIVIDER"]);
        loopnum++;
    }
    return divider;
}

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
    int max_health;
    int healingPotions;
    std::string HealingPotionsName;
    bool minionActive;
    int minions;
    int minionTurns;
    int minionMaxTurns;
    std::string minionName;
    int attack(Player& opposingPlayer, int lowest, int highest, int testlowest, int testhighest, int missPercent) {
        int minionDamage = 0;
        if (minionActive) {
            if (this->minionTurns == 1) {
                std::cout << this->minionName << " will be deactivated after this turn.";
            }
            this->minionTurns--;
            minionDamage = rangeRng(lowest, highest);
            testhighest += 1;
        }
        int testRng = rangeRng(testlowest, testhighest);
        if (testRng > missPercent) {
            int hitRng = rangeRng(lowest, highest);
            opposingPlayer.health -= hitRng + minionDamage;
            std::cout << "\nThat's a hit! " << hitRng << " damage.\n";
            if (minionActive) {
                std::cout << "Active " << this->minionName <<  " added " << minionDamage << " damage.";
                if (minionTurns <= 0) {
                    this->minionActive = false;
                }
            }
            std::cout << "\n";
            return 0;
        } else {
            std::cout << "\nThat's a miss!\n\n";
            return 1;
        }
    }

    int heal() {
        if (this->health >= this->max_health) {
            return 2;
        }
        if (this->healingPotions <= 0) {
            return 3;
        }
        this->healingPotions -= 1;
        int healedHealth = rangeRng(7, 20);
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
        attacks["Small Attack"] = [&]() { return attack(opposingPlayer, 1, 15, 1, 100, 25); };
        attacks["Large Attack"] = [&]() { return attack(opposingPlayer, 15, 30, 1, 100, 50); };
        attacks[this->HealingPotionsName] = [&]() { return heal(); };
        attacks["Summon " + this->minionName] = [&]() {
            if(this->minions <= 0) {
                return 4;
            }
            if(this->minionActive) {
                return 5;
            }
            this->minions--;
            this->minionActive = true;
            this->minionTurns = data["PLAYER1"]["ATTACKS"]["MINIONS"]["TURNS"];
            std::cout << this->minionName << " summoned and active!\n";
            return 0;
        };
        return attacks;
    }
};

void finish(Player& winningPlayer, Player& losingPlayer) {
    std::cout << "\n " << winningPlayer.name << " has won the battle with " << winningPlayer.health<< " health!\n";
}

// 56

void turn(Player& player1, Player& player2) {
    std::cout << "\n" << getDivider() << "\n";
    std::cout << "Current Turn: " << player1.name << "\n" << player1.name << "'s health: " << player1.health << "\n" << player2.name << "'s health: " << player2.health << "\n";
    std::map<std::string, std::function<int()>> attacks = player1.getList(player2);
    std::cout << "\nAttacks:\n";
    int index = 0;
    for(auto i: attacks) {
        std::cout << index + 1 << ". " << i.first << "\n";
        index++;
    }
    std::cout << "\nHealing Potions left: " << player1.healingPotions << "\n";
    std::cout << "Available " << player1.minionName << "s: " << player1.minions << "\n" << player1.minionName << "s add a random damage boost (potentially double) but lower your chances of hitting. They last for " << player1.minionMaxTurns << " of your turns.\n";
    std::cout << player1.minionName << " Active?: ";
    if (player1.minionActive) {
        std::cout << "Yes";
    } else {
        std::cout << "No";
    }
    std::cout << "\n" << getDivider() << "\n";
    std::cout << "Type the name of your attack.\n";
    std::string x;
    std::cout << "> ";
    while (true) {
        std::getline(std::cin, x);
        try {
            int attak = attacks[x]();
            if (attak == 2) {
                std::cout << "Your health is already at max!\n";
                std::cout << "> ";
            } else if (attak == 3) {
                std::cout << "You don't have any " << player1.HealingPotionsName << "s!\n";
                std::cout << "> ";
            } else if (attak == 4) {
                std::cout << "You don't have any " << player1.minionName << "s left!\n";
                std::cout << "> ";
            } else if (attak == 5) {
                std::cout << "You already have a " << player1.minionName << " active!\n";
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
    std::cout << getDivider() << "\n";
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
    john.healingPotions = data["PLAYER1"]["ATTACKS"]["HEALING_POTIONS"]["AMOUNT"];
    john.HealingPotionsName = data["PLAYER1"]["ATTACKS"]["HEALING_POTIONS"]["NAME"];
    john.minions = data["PLAYER1"]["ATTACKS"]["MINIONS"]["AMOUNT"];
    john.minionActive = false;
    john.minionTurns =  data["PLAYER1"]["ATTACKS"]["MINIONS"]["TURNS"];
    john.minionMaxTurns = data["PLAYER1"]["ATTACKS"]["MINIONS"]["TURNS"];
    john.minionName = data["PLAYER1"]["ATTACKS"]["MINIONS"]["NAME"];
    Player tim;
    tim.name = data["PLAYER2"]["NAME"];
    tim.health = data["PLAYER2"]["STARTING_HEALTH"];
    tim.max_health = data["PLAYER2"]["STARTING_HEALTH"];
    tim.healingPotions = data["PLAYER2"]["ATTACKS"]["HEALING_POTIONS"]["AMOUNT"];
    tim.HealingPotionsName = data["PLAYER2"]["ATTACKS"]["HEALING_POTIONS"]["NAME"];
    tim.minions = data["PLAYER2"]["ATTACKS"]["MINIONS"]["AMOUNT"];
    tim.minionActive = false;
    tim.minionTurns = data["PLAYER2"]["ATTACKS"]["MINIONS"]["TURNS"];
    tim.minionMaxTurns = data["PLAYER2"]["ATTACKS"]["MINIONS"]["TURNS"];
    tim.minionName = data["PLAYER2"]["ATTACKS"]["MINIONS"]["NAME"];
    start(john, tim);
    return 0;
}
