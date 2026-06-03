#include <iostream>
#include <string>
#include <limits>

using namespace std;

// ==========================================
// BASE CLASS: Pet (Abstract Class)
// ==========================================
class Pet {
protected:
    string m_name;
    int m_energy;
    int m_fun;

public:
    // Konstruktor
    Pet(string nama, int energi, int fun) 
        : m_name(nama), m_energy(energi), m_fun(fun) {}

    // Virtual Destructor (Clean Code: Mencegah memory leak pada class turunan)
    virtual ~Pet() = default;

    // Fungsi konstan (const) karena hanya membaca data, tidak mengubahnya
    virtual void talk() const;
    
    // Perilaku umum
    void eat(int food);
    void play(int toy);

    // Pure Virtual Functions (Wajib diimplementasikan oleh class turunan)
    virtual void attack() = 0; 
    virtual void specialSkill() = 0; 
};

void Pet::talk() const {
    cout << "=== Status Pet ===" << endl;
    cout << "Nama   : " << m_name << endl;
    cout << "Energi : " << m_energy << endl;
    cout << "Fun    : " << m_fun << endl;
}

void Pet::eat(int food) {
    cout << "[" << m_name << "] Nyamm! Makanannya enak." << endl;
    m_energy += food;
    m_fun = max(0, m_fun - 2); // Logika: Makan mengurangi fun, tapi cegah nilai minus
}

void Pet::play(int toy) {
    if (m_energy >= 2) {
        cout << "[" << m_name << "] Hore!! Asik sekali bermain." << endl;
        m_fun += toy;
        m_energy -= 2;
    } else {
        cout << "[" << m_name << "] Terlalu lelah untuk bermain. Butuh makan!" << endl;
    }
}

// ==========================================
// DERIVED CLASS 1: Leviathan
// ==========================================
class Leviathan : public Pet {
private:
    int m_swimPoint;

public:
    Leviathan(string nama, int en, int fun, int sp) 
        : Pet(nama, en, fun), m_swimPoint(sp) {
        cout << ">> Leviathan baru telah menetas dari dasar laut! <<" << endl;
    }

    void talk() const override {
        cout << "\n--- Leviathan Status ---" << endl;
        cout << "Spesies     : Leviathan (Monster Air)" << endl;
        Pet::talk(); // Memanggil fungsi talk() dari parent
        cout << "Swim Point  : " << m_swimPoint << endl;
        cout << "------------------------\n" << endl;
    }

    // Implementasi khusus perilaku Leviathan
    void specialSkill() override {
        if (m_swimPoint > 0) {
            cout << "[" << m_name << "] Berenang dengan sangat cepat melintasi samudra! (Swim!)" << endl;
            m_swimPoint--;
            m_fun += 3;
        } else {
            cout << "[" << m_name << "] Kehabisan Swim Point!" << endl;
        }
    }

    void attack() override {
        if (m_energy >= 3) {
            cout << "[" << m_name << "] Mengeluarkan serangan Water Blast! Swooosh!" << endl;
            m_energy -= 3;
        } else {
            cout << "[" << m_name << "] Energi tidak cukup untuk menyerang." << endl;
        }
    }
};

// ==========================================
// DERIVED CLASS 2: Phoenix (Turunan Baru)
// ==========================================
class Phoenix : public Pet {
private:
    int m_firePower;

public:
    Phoenix(string nama, int en, int fun, int fp) 
        : Pet(nama, en, fun), m_firePower(fp) {
        cout << ">> Phoenix baru telah bangkit dari abu! <<" << endl;
    }

    void talk() const override {
        cout << "\n--- Phoenix Status ---" << endl;
        cout << "Spesies     : Phoenix (Burung Api)" << endl;
        Pet::talk();
        cout << "Fire Power  : " << m_firePower << endl;
        cout << "----------------------\n" << endl;
    }

    // Implementasi khusus perilaku Phoenix
    void specialSkill() override {
        if (m_energy >= 1) {
            cout << "[" << m_name << "] Mengepakkan sayap api dan terbang ke langit! (Fly!)" << endl;
            m_firePower += 2; // Terbang menambah kekuatan api
            m_energy -= 1;
        } else {
            cout << "[" << m_name << "] Terlalu lelah untuk terbang." << endl;
        }
    }

    void attack() override {
        if (m_firePower >= 3) {
            cout << "[" << m_name << "] Menembakkan serangan Fireball! Booom!" << endl;
            m_firePower -= 3;
        } else {
            cout << "[" << m_name << "] Fire Power tidak cukup! Harus terbang (Special Skill) dulu." << endl;
        }
    }
};

// ==========================================
// MAIN FUNCTION & MENU
// ==========================================
int main() {
    Pet* myPet = nullptr; // Menggunakan pointer polymorphic
    int pilihan;
    string namaPet;

    cout << "===================================" << endl;
    cout << "      WELCOME TO PET SIMULATOR     " << endl;
    cout << "===================================" << endl;
    
    // Menu Pemilihan Pet
    while (myPet == nullptr) {
        cout << "Pilih spesies Pet awalmu:" << endl;
        cout << "1. Leviathan (Air)" << endl;
        cout << "2. Phoenix (Api)" << endl;
        cout << "Pilih (1/2): ";
        cin >> pilihan;

        if (pilihan == 1 || pilihan == 2) {
            cout << "Berikan nama untuk Pet kamu: ";
            cin >> namaPet;
            
            if (pilihan == 1) {
                myPet = new Leviathan(namaPet, 10, 5, 5); // nama, energi, fun, swimPoint
            } else {
                myPet = new Phoenix(namaPet, 10, 5, 5);   // nama, energi, fun, firePower
            }
        } else {
            cout << "Pilihan tidak valid. Coba lagi.\n" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Menu Interaksi (Game Loop)
    bool isPlaying = true;
    while (isPlaying) {
        cout << "\n=== MENU INTERAKSI ===" << endl;
        cout << "1. Cek Status (Talk)" << endl;
        cout << "2. Beri Makan" << endl;
        cout << "3. Ajak Bermain" << endl;
        cout << "4. Gunakan Special Skill" << endl;
        cout << "5. Lakukan Attack" << endl;
        cout << "6. Keluar Game" << endl;
        cout << "Aksi (1-6): ";
        cin >> pilihan;
        cout << endl;

        switch (pilihan) {
            case 1:
                myPet->talk();
                break;
            case 2:
                myPet->eat(5); // Tambah 5 energi
                break;
            case 3:
                myPet->play(3); // Tambah 3 fun
                break;
            case 4:
                // Berkat Polymorphism, kita tidak peduli apakah ini Leviathan atau Phoenix,
                // program otomatis menjalankan skill yang benar (Swim atau Fly).
                myPet->specialSkill();
                break;
            case 5:
                myPet->attack();
                break;
            case 6:
                cout << "Menyimpan data dan keluar... Sampai jumpa!" << endl;
                isPlaying = false;
                break;
            default:
                cout << "Aksi tidak dikenali!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
        }
    }
    delete myPet;
    return 0;
}
