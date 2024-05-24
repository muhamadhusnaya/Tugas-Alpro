#include <iostream>
using namespace std;

class node
{
private:
    char gerbong;
    node *next;

public:
    node(char gerbong, node *next = nullptr)      // kosntruktor
    {                                               // untuk mengisi value dari node 
        this->gerbong = gerbong;
        this->next = next;
    }

    char getGerbong() { return this->gerbong; }   //

    node *getNext() { return this->next; }

    void setNext(node *next) { this->next = next; }
};
typedef node *Gerbongptr;

class linklist
{
private:
    Gerbongptr head;

public:
    linklist()      // konstruktor
    {
        this->head = nullptr;
    }

    void insertFirst(char newData)
    {
        Gerbongptr newNode = new node(newData); // Membuat node baru
        newNode->setNext(head);                 // Mengatur next node baru ke head (node pertama sebelumnya)
        head = newNode;                         // Memperbarui head untuk menunjuk ke node baru
    }

    void insertAfter(char marker, char newNomor)
    {

        if (head == nullptr)
        {
            head = new node(newNomor);
        }

        else
        {
            Gerbongptr current = this->head;
            while (current->getGerbong() != marker)
            {
                current = current->getNext();
                if (current == nullptr)
                {
                    cout << "\nGAGAL!!! menambahkan node, input kamu tidak valid" << endl;
                    return;
                }
            }
            Gerbongptr newNode = new node(newNomor, current->getNext());
            current->setNext(newNode); // Mengatur next dari node sebelumnya ke node baru
        }
    }

    void insertLast(char newNomor)
    {
        Gerbongptr newNode = new node(newNomor); // Membuat node baru

        if (head == nullptr)    // Jika linked list masih kosong, node baru akan menjadi head
        { 
            head = newNode;
        }
        else
        {
            Gerbongptr current = head;
            while (current->getNext() != nullptr)
            { // Mencari node terakhir dalam linked list
                current = current->getNext();
            }
            current->setNext(newNode); // Mengaitkan node baru di akhir linked list
        }
    }

    void deleteFirst()
    {
        if (head)
        {
            Gerbongptr temp = head; // Simpan alamat node pertama
            head = head->getNext(); // Pindah head ke node kedua
            delete temp;            // Hapus node pertama
        }
        else
        {
            cout << "List is empty, nothing to delete." << endl; // Tampilkan pesan jika list kosong
        }
    }

    void deleteAfter(char value)
    {
        Gerbongptr prev = head;
        while (prev != nullptr && prev->getGerbong() != value)
        { // Cari node dengan nilai value
            prev = prev->getNext();
        }
        if (prev != nullptr && prev->getNext() != nullptr)
        {                                        // Jika node dengan nilai value ditemukan dan memiliki node setelahnya
            Gerbongptr target = prev->getNext(); // Simpan node yang akan dihapus
            prev->setNext(target->getNext());    // Hubungkan node sebelumnya dengan node setelah node yang akan dihapus
            delete target;                       // Hapus node yang akan dihapus
        }
        else
        {
            cout << "Element with value " << value << " not found or does not have a node after it." << endl;
        }
    }

    void deleteLast()
    {
        Gerbongptr current = head;
        Gerbongptr before = nullptr;
        while (current->getNext() != nullptr)
        {
            before = current;
            current = current->getNext();
            
        }
        if (before == nullptr)
        {
            delete current;
            head = nullptr;
        } else
        {
            before->setNext(nullptr);
            delete current;
        }
        
    }

    void deleteAll()
    {
        Gerbongptr temp = nullptr;
        while (head)
        {
            temp = head;
            head = head->getNext();
            delete temp;
        }
    }

    void printList()
    {
        cout << "Linked list: ";
        Gerbongptr temp = head;
        while (temp != nullptr)
        {
            cout << temp->getGerbong() << " " << temp->getNext() << " | "; // Mencetak data node
            temp = temp->getNext();            // Pindah ke node selanjutnya
        }
        cout << endl;
    }

    ~linklist() // destruktor
    { 
        deleteAll();
    }
};
int main()
{
    cout << "\n      LINKED LIST\n" << endl;

    linklist list;

    cout << "Gerbong awal = " << endl;
    list.insertFirst('a');
    list.insertLast('c');
    list.insertAfter('a', 'b');
    list.printList();
    
    cout << "Gerbong setelah ditambah = " << endl;
    list.insertAfter('a', 'x');
    list.printList();

    cout << "Gerbong akhir = " << endl;
    list.deleteAfter('a');
    list.deleteLast();
    list.printList();
}