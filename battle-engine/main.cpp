#include <iostream>
#include <string>
#include <random>

class Player {
    public:
        std::string name = "John";
        int health = 100;
        void attack(int* opposingHealth, int damage) {
            std::random_device rd; // obtain a random number from hardware
            std::mt19937 gen(rd()); // seed the generator
            std::uniform_int_distribution<> distr(25, 63); // define the range
            int rng = distr(gen);
            *opposingHealth = *opposingHealth - damage;
        }
};

void finish(Player winningPlayer, Player losingPlayer) {
    std::cout << "\n " << winningPlayer.name << " has won the battle with " << winningPlayer.health<< "!\n";
}

void start(Player player1, Player player2) {
    std::cout << "The battle has begun!\n" << player1.name << " vs " << player2.name;
    while (player1.health > 0 || player2.health > 0) {
        std::cout << "Current Turn: " << player1.health << "\n" << player1.name << " health: " << player1.health;
    }
}

int main() {
    Player john;
    Player tim;
    tim.name = "Tim";
    return 0;
}