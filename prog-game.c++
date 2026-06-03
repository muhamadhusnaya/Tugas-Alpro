#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

// ===== COLOR =====
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

// ===== UTIL =====
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void delay(int ms) {
    this_thread::sleep_for(milliseconds(ms));
}

// Efeek typing atau mengetik
void printSlow(string text, int speed = 20) {
    for (char c : text) {
        cout << c << flush;
        delay(speed);
    }
}

// Randomm
int acak(int min, int max) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

// ===== Interfaces =====
void box(string title) {
    cout << CYAN << "\n==============================\n";
    cout << "  " << title << endl;
    cout << "==============================\n" << RESET;
}

void hpBar(int hp) {
    cout << "HP: [";
    int bars = hp ;

    for (int i = 0; i < 20; i++) {
        if (i < bars) cout << GREEN << "#" << RESET;
        else cout << "-";
    }
    cout << "] " << hp << endl;
}

// ===== DATA STRUCT =====
struct Player {
    int hp = 100;
    vector<string> inventory {"Potion"};
};

struct Enemy {
    string name;
    int hp;
};

// ===== INVENTORY =====
void showInventory(const vector<string>& inv) {
    box("INVENTORY");

    if (inv.empty()) {
        cout << "Kosong\n";
        return;
    }

    for (int i = 0; i < inv.size(); i++) {
        cout << "[" << i+1 << "] " << inv[i] << endl;
    }
}

// ===== ITEM =====
void addItem(vector<string>& inv) {
    vector<string> pool {"Potion", "Elixir", "Bomb asap"};
    int i = acak(0, pool.size()-1);

    box("LOOT");
    cout << YELLOW;
    printSlow("Kamu menemukan: " + pool[i] + "\n");
    cout << RESET;

    inv.push_back(pool[i]);
    delay(500);
}

void useItem(Player& p, bool inBattle = false) {
    showInventory(p.inventory);
    cout << "Pilih item: ";
    int pilih;
    cin >> pilih;

    if (pilih < 1 || pilih > p.inventory.size()) return;

    string item = p.inventory[pilih-1];

    if (item == "Potion") {
        cout << GREEN;
        printSlow("HP +20\n");
        cout << RESET;
        p.hp += 20;
    } else if (item == "Elixir") {
        cout << GREEN;
        printSlow("HP +50\n");
        cout << RESET;
        p.hp += 50;
    } else if (item == "Bomb asap") {
        if (!inBattle) {
            printSlow("Bomb hanya bisa dipakai saat battle!\n");
            return;
        }
        printSlow("Kamu melempar Bomb!\n");
    }

    p.inventory.erase(p.inventory.begin() + (pilih-1));
    delay(700);
}

// ===== BATTLE =====
bool battle(Player& p) {
    vector<string> names {"Goblin", "Orc", "Skeleton"};
    Enemy e {names[acak(0,2)], acak(40,80)};

    clearScreen();
    box("BATTLE");
    cout << RED;
    printSlow("Musuh muncul: " + e.name + "!\n");
    cout << RESET;
    delay(800);

    while (e.hp > 0 && p.hp > 0) {
        clearScreen();
        box("BATTLE");

        cout << "Musuh: " << e.name << endl;
        hpBar(e.hp);
        cout << endl;
        hpBar(p.hp);

        cout << "\n[1] Attack\n[2] Use Item\nPilih: ";
        int pilih;
        cin >> pilih;

        if (pilih == 1) {
            int dmg = acak(10,25);
            cout << GREEN;
            printSlow("Kamu menyerang -" + to_string(dmg) + "\n");
            cout << RESET;
            e.hp -= dmg;
        } else if (pilih == 2) {
            useItem(p, true);
            continue;
        }

        delay(500);

        if (e.hp > 0) {
            int dmg = acak(5,20);
            cout << RED;
            printSlow(e.name + " menyerang kamu -" + to_string(dmg) + "\n");
            cout << RESET;
            p.hp -= dmg;
        }

        delay(800);
    }

    if (p.hp <= 0) {
        cout << RED;
        printSlow("Kamu kalah...NT kawan\n");
        cout << RESET;
        delay(1000);
        return false;
    }

    cout << GREEN;
    printSlow("Kamu menang! Uhuuyyyyy\n");
    cout << RESET;

    addItem(p.inventory);
    return true;
}

// ===== EXPLORE =====
bool explore(Player& p) {
    clearScreen();
    box("EXPLORE");

    int event = acak(1,3);

    if (event == 1) {
        printSlow("Kamu berjalan... tidak ada apa-apa.\n");
        delay(800);
    } 
    else if (event == 2) {
        return battle(p);
    } 
    else {
        addItem(p.inventory);
    }

    return true;
}

// ===== MAIN =====
int main() {
    Player p;
    bool hidup = true;

    while (hidup) {
        clearScreen();
        box("DUNGEON GAME");

        hpBar(p.hp);

        cout << "\n[1] Explore\n";
        cout << "[2] Inventory\n";
        cout << "[3] Exit\n";
        cout << "Pilih: ";


        int pilih;
        cin >> pilih;

        switch (pilih) {
            case 1: hidup = explore(p); break;
            case 2:
                useItem(p); 
                cin.ignore(); cin.get();
                break;
            case 3: hidup = false; break;
        }

        if (p.hp <= 0) hidup = false;
    }

    clearScreen();
    box("GAME OVER");
    printSlow("Terima kasih sudah bermain...\n");
}
