#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <filesystem>


using namespace std;

// Base class
class User {
protected:
    string name;

public:
    User(string n) : name(n) {}

    string getName() const { return name; }
};

// Derived class
class Player : public User {
    int score;

public:
    Player(string n) : User(n), score(0) {}

    void addScore(int s) { score += s; }

    int getScore() const { return score; }

    void saveScore() {
        if (score > 0) {
            ofstream file("C:/study/project/sem 2 project/leader.txt", ios::app);
            if (file) {
               file << name << " " << score << "\n";


                file.close();
            } else {
                cout << "Error opening file.\n";
            }
        } else {
            cout << "Score is 0. Not saving.\n";
        }
    }

    void showScore() const {
        cout << "\nTotal Score: " << score << "\n";
    }

    friend void displayPlayerData(const Player& p);
};

// Friend function
void displayPlayerData(const Player& p) {
    cout << "\n[Friend Function] Player Name: " << p.name << ", Score: " << p.score << "\n";
}

// Game class
class Game {
public:
    static int pseudoRandomIndex(int seed, int mod) {
        return (seed * 17 + 13) % mod;
    }

    static void quickMath(Player& p) {
        static int counter = 1;
        int a, b, correctAnswer;
        string operation;

        switch (counter % 4) {
            case 0:
                a = 10 * counter; b = 5;
                operation = "/"; correctAnswer = a / b;
                break;
            case 1:
                a = 15 + counter; b = 20;
                operation = "+"; correctAnswer = a + b;
                break;
            case 2:
                a = 30 - counter; b = 10;
                operation = "-"; correctAnswer = a - b;
                break;
            case 3:
                a = 5 * counter; b = 3;
                operation = "*"; correctAnswer = a * b;
                break;
        }

        cout << "\nQuick Math: What is " << a << " " << operation << " " << b << "?\n";
        int ans;
        cin >> ans;

        if (ans == correctAnswer) {
            cout << "Correct!\n";
            p.addScore(10);
        } else {
            cout << "Incorrect.\n";
        }

        counter++;
    }

    static void shuffleString(string& str, int seed) {
        int n = str.size();
        for (int i = 0; i < n - 1; ++i) {
            int j = pseudoRandomIndex(seed + i, n - i) + i;
            swap(str[i], str[j]);
        }
    }

    static void wordScramble(Player& p) {
        static int seed = 1;
        vector<string> words = {"apple", "banana", "grape", "orange", "watermelon"};
        int index = pseudoRandomIndex(seed, words.size());
        string word = words[index];
        string scrambledWord = word;

        shuffleString(scrambledWord, seed);

        string guess;
        cout << "\nWord Scramble: Unscramble the word: " << scrambledWord << "\n";
        cout << "Your guess: ";
        cin >> guess;

        if (guess == word) {
            cout << "Correct! You guessed the word!\n";
            p.addScore(10);
        } else {
            cout << "Incorrect. The correct word was: " << word << "\n";
        }

        seed++;
    }

    static void oddOneOut(Player& p) {
        struct Puzzle {
            vector<string> words;
            int oddone;
            string reason;
        };

        vector<Puzzle> puzzles = {
            { {"Car", "Bus", "Train", "Banana"}, 3, "Banana is not a vehicle." },
            { {"Table", "Chair", "Sofa", "Tiger"}, 3, "Tiger is not furniture." },
            { {"January", "March", "Apple", "May"}, 2, "Apple is not a month." },
            { {"Python", "C++", "Java", "Burger"}, 3, "Burger is not a programming language." },
            { {"Sun", "Moon", "Star", "Potato"}, 3, "Potato is not a celestial body." }
        };

        static int level = 0;
        Puzzle current = puzzles[level % puzzles.size()];

        cout << "\nOdd One Out: Which word doesn't belong?\n\n";
        for (int i = 0; i < current.words.size(); ++i) {
            cout << (i + 1) << ". " << current.words[i] << "\n";
        }

        cout << "\nYour choice (enter number): ";
        int choice;
        cin >> choice;

        if (choice - 1 == current.oddone) {
            cout << "Correct! " << current.reason << "\n";
            p.addScore(10);
        } else {
            cout << "Incorrect. " << current.words[current.oddone] << " was the odd one.\n";
            cout << "Reason: " << current.reason << "\n";
        }

        level++;
    }

    static int showLeaderboard() {
ifstream file("leader.txt");
    string word;
    cout << "Contents (word by word):\n";
    while (file >> word) {
        cout << word << " \n";
    }

    file.close();
    return 0;


    }
};

// Main function
int main() {
    string name;
    cout << "Welcome to Brain Burst!\nEnter your name: ";
    getline(cin, name);
    Player player(name);

    int choice;
    do {
        cout << "\n====== MENU ======\n";
        cout << "1. Quick Math Game\n";
        cout << "2. Word Scramble Game\n";
        cout << "3. Odd One Out Game\n";
        cout << "4. Show Score\n";
        cout << "5. Leaderboard\n";
        cout << "6. Friend Display Player Info\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1: Game::quickMath(player); break;
            case 2: Game::wordScramble(player); break;
            case 3: Game::oddOneOut(player); break;
            case 4: player.showScore(); break;
            case 5: Game::showLeaderboard(); break;
            case 6: displayPlayerData(player); break;
            case 0:
                cout << "Saving your score...\n";
                player.saveScore();
                break;
            default:
                cout << "Invalid option.\n";
        }

    } while (choice != 0);

    cout << "Thanks for playing, " << player.getName() << "!\n";
    return 0;
}
