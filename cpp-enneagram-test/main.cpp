#include <iostream>
#include <map>
#include <string>
#include <algorithm>

class Enneagramtest {
    public:
    std::map<std::string, int> questions = {
        {
            "You have a strong sense of right and wrong.", 1
        },
        {
            "You heavily care about improving the world around you.", 1
        },
        {
            "You want to be useful.", 1
        },
        {
            "You feel the need often to justify your actions.", 1
        },
        {
            "You have a set of principles that must be followed at all times.", 1
        },
        {
            "I always put others first.", 2
        },
        {
            "I try my best to please those around me.", 2
        },
        {
            "I want to help people a lot.", 2
        },
        {
            "The best thing is to put other people's needs first.", 2
        },
        {
            "You love unconditionally.", 2
        },
        {
            "You are goal oriented.", 3
        },
        {
            "You exhibit charisma and charm onto others.", 3
        },
        {
            "To be seen as a loser would be the worst thing for you.", 3
        },
        {
            "You are VERY competitive.", 3
        },
        {
            "You want to be noticed through success.", 3
        },
        {
            "My self-image is very important to me.", 4
        },
        {
            "I like to look at myself as different from other people.", 4
        },
        {
            "You base your identity on emotional reactions.", 4
        },
        {
            "When not stressed, you like to be honest to yourself.", 4
        },
        {
            "You always feel like you're missing something in life.", 4
        },
        {
            "You focus heavily on understanding complex ideas and skills.", 5
        },
        {
            "You have specialized skill sets for your expertise.", 5
        },
        {
            "You want to understand how the world works more than anything.", 5
        },
        {
            "You want to acquire as much knowledge as possible to understand something.", 5
        },
        {
            "You are scared of not being able to do things as well as others.", 5
        },
        {
            "You are very loyal to your friends and beliefs.", 6
        },
        {
            "You need guidance and help in life.", 6
        },
        {
            "You believe that all authority must be questioned.", 6
        },
        {
            "You get very anxious when doing a big thing on your own.", 6
        },
        {
            "You are easily influenced by others.", 6
        },
        {
            "You like working on a multitude of projects at the same time.", 7
        },
        {
            "You enjoy intellectually-stimulating activities.", 7
        },
        {
            "You are good at brainstorming.", 7
        },
        {
            "You have trouble listening to people.", 7
        },
        {
            "You fear boredom.", 7
        },
        {
            "You desire being in control of your life more than anything else.", 8
        },
        {
            "You like improving yourself with challenges.", 8
        },
        {
            "You don't care much about what other people think of you.", 8
        },
        {
            "You don't like showing weakness to others.", 8
        },
        {
            "You have a lot of determination and willpower.", 8
        },
        {
            "You are spiritual.", 9
        },
        {
            "You greatly value deep connections with others.", 9
        },
        {
            "You try to keep the peace between others.", 9
        },
        {
            "You would give up your own needs to benefit others.", 9
        },
        {
            "You value other perspectives on things.", 9
        }
    };
    std::map<int, float> stats = {
        {
            1, 0
        },
        {
            2, 0
        },
        {
            3, 0
        },
        {
            4, 0
        },
        {
            5, 0
        },
        {
            6, 0
        },
        {
            7, 0
        },
        {
            8, 0
        },
        {
            9, 0
        }
    };
    std::map<int, std::string> longnames = {
        {
            1, "Type 1"
        },
        {
            2, "Type 2"
        },
        {
            3, "Type 3"
        },
        {
            4, "Type 4"
        },
        {
            5, "Type 5"
        },
        {
            6, "Type 6"
        },
        {
            7, "Type 7"
        },
        {
            8, "Type 8"
        },
        {
            9, "Type 9"
        }
    };
    void ExtremelyAgree(int type) {
        this->stats.at(type) += 30;
    }
    void Agree(int type) {
        this->stats.at(type) += 25;
    }
    void KindaAgree(int type) {
        this->stats.at(type) += 20;
    }
    void Neutral(int type) {
        this->stats.at(type) += 15;
    }
    void KindaDisagree(int type) {
        this->stats.at(type) += 10;
    }
    void Disagree(int type) {
        this->stats.at(type) += 5;
    }
};

int main() {
    std::cout << "Welcome to the C++ Enneagram test! There are 45 questions.\n";
    Enneagramtest test;
    int num = 1;
    for(auto& i : test.questions) {
        std::cout << "\n" << num << ". " << i.first << "\n\n";
        std::cout << "Do you:\n" << "1. Extremely Agree\n" << "2. Agree\n" << "3. Kinda Agree\n" << "4. Neutral\n" << "5. Kinda Disagree\n" << "6. Disagree\n" << "7. Extremely Disagree\n\n" << "Please type the number of your choice.\n";
        std::cout << "> ";
        std::string choice;
        while(true) {
            std::getline(std::cin, choice);
            if (choice == "1") {
                test.ExtremelyAgree(i.second);
                num++;
                break;
            } else if (choice == "2") {
                test.Agree(i.second);
                num++;
                break;
            } else if (choice == "3") {
                test.KindaAgree(i.second);
                num++;
                break;
            } else if (choice == "4") {
                test.Neutral(i.second);
                num++;
                break;
            } else if (choice == "5") {
                test.KindaDisagree(i.second);
                num++;
                break;
            } else if (choice == "6") {
                test.Disagree(i.second);
                num++;
                break;
            } else if (choice == "7") {
                num++;
                break;
            } else {
                std::cout << "Answer not recognized.\n";
                std::cout << "> ";
            }
        }
    }
    std::cout << "\nHere are your results:\n";
    for(auto i : test.stats) {
        std::cout << test.longnames.at(i.first) << ": " << i.second << "\n";
    }
    test.stats.at(1) += 0.1;
    test.stats.at(2) += 0.2;
    test.stats.at(3) += 0.3;
    test.stats.at(4) += 0.4;
    test.stats.at(5) += 0.5;
    test.stats.at(6) += 0.6;
    test.stats.at(7) += 0.7;
    test.stats.at(8) += 0.8;
    test.stats.at(9) += 0.9;
    int type;
    float big;
    for(auto i : test.stats) {
        if (i.second > big) {
            big = i.second;
            type = i.first;
        }
    }
    std::cout << "Your highest is " << test.longnames.at(type) << ".\n";
    int wing = 0;
    if (type == 1) {
        if (test.stats.at(9) > test.stats.at(2)) {
            wing = 9;
        } else {
            wing = 2;
        }
    } else if(type == 9) {
        if (test.stats.at(8) > test.stats.at(1)) {
            wing = 8;
        } else {
            wing = 1;
        }
    } else {
        if(test.stats.at((type - 1)) > test.stats.at((type + 1))) {
            wing = (type - 1);
        } else {
            wing = (type + 1);
        }
    }
    std::cout << "When taking wings into account, you are a " << type << "w" << wing <<".\n";
    return 0;
}
