#include <iostream>

using namespace std;


struct Node{        // Struktur Node
    int data;
    Node *prev;
    Node *next;
};


Node *createNode(int data){     // Fungsi untuk membuat node baru
    Node *newNode = new Node;
    newNode->data = data;
    newNode->prev = nullptr;
    newNode->next = nullptr;
    return newNode;
}

// Fungsi untuk menambahkan node baru pada elemen pertama dalam linked list
void insertFirst(Node *&head, int data)
{
    Node *newNode = createNode(data);
    if (head == nullptr)
    {
        head = newNode; // Jika linked list kosong, node baru menjadi head
    }
    else
    {
        newNode->next = head;
        head->prev = newNode; // Mengatur prev dari head menjadi node baru
        head = newNode;       // Mengatur node baru sebagai head
    }
}

// Fungsi untuk menambahkan node baru sebagai terakhir/tail dalam linked list
void insertLast(Node*& head, int data) {
    Node* newNode = createNode(data);
    if (head == nullptr) {
        head = newNode;                     // Jika linked list kosong, node baru menjadi head
    } else {
        Node* current = head;
        
        while (current->next != nullptr) {  // Mencari posisi terakhir dalam linked list
            current = current->next;
        }
        // Menyisipkan node baru setelah posisi terakhir
        current->next = newNode; // Mengatur next dari posisi terakhir menjadi node baru
        newNode->prev = current; // Mengatur prev dari node baru
    }

}

// Fungsi untuk menambahkan node baru setelah node yang dipilih ada dalam linked list
void insertAfter(Node* head, int valueToInsertAfter, int data) {
    Node* current = head;       // Mulai pencarian dari head
    while (current != nullptr && current->data != valueToInsertAfter) { // Mencari node dengan value yang diinginkan
        current = current->next;
    }

    if (current == nullptr) {       // Jika node dengan nilai yang sesuai tidak ditemukan
        cout << "Node dengan nilai " << valueToInsertAfter << " tidak ditemukan" << endl;
        return;
    }
    
    Node* newNode = createNode(data);   // Membuat node baru
    // Menyisipkan node baru setelah node dengan nilai yang sesuai
    newNode->next = current->next;      // Mengatur next dari node baru
    newNode->prev = current;            // Mengatur prev dari node baru
    current->next = newNode;            // Mengatur next dari node yang sebelumnya menunjuk ke node baru
    
    if (newNode->next != nullptr) {     // Mengatur prev dari node yang berada setelah node baru, jika ada
        newNode->next->prev = newNode;
    }
}

// Fungsi untuk menambahkan node baru sebelum node yang dipilih ada dalam linked list
void insertBefore(Node*& head, int valueToInsertAfter, int data) {
    Node* current = head;                                                   // Mulai pencarian dari head
    while (current != nullptr && current->data != valueToInsertAfter) {     // Mencari node dengan nilai yang sesuai
        current = current->next;
    }
    
    if (current == nullptr) {         // Jika node dengan nilai yang sesuai tidak ditemukan
        cout << "Node dengan nilai " << valueToInsertAfter << " tidak ditemukan" << endl;
        return;
    }
    
    Node* newNode = createNode(data);               // Membuat node baru
    // Menyisipkan node baru setelah node dengan nilai yang sesuai
    newNode->next = current;                        // Mengatur next dari node baru
    newNode->prev = current->prev;                  // Mengatur prev dari node baru
    current->prev = newNode;                        // Mengatur prev dari node yang sebelumnya menunjuk ke node baru
    
    if (newNode->prev != nullptr) {                 // Mengatur prev node baru yang berada sebelum node baru, jika ada
        newNode->prev->next = newNode ;
    }
    else {
        head = newNode;                             //jika sebelum node baru tidak ada node maka node baru menjadi head
    }
}

// Fungsi untuk menghapus node pertama dari linked list
void deleteFirst(Node *&head){
    if (head == nullptr){        // Kondisi jika linked list kosong maka akan menampilkan 
        cout << "Linked list kosong, tidak ada yang dihapus" << endl;
        return;
    }
    
    Node *temp = head;          // Membuat pointer dengan alamat node yang akan dihapus yang menujuk ke head
    head = head->next;          // Ubah head menjadi node setelahnya

    if (head != nullptr){       // Jika linked list head tidak null atau ada isinya
        head->prev = nullptr;
    }
    
    delete temp;            // Hapus node pertama
}

// Fungsi untuk menghapus node terakhir dari linked list
void deleteLast(Node *&head){
    if (head == nullptr){           // Kondisi jika linked list kosong maka akan menampilkan 
        cout << "Linked list kosong, tidak ada yang dihapus" << endl;
        return;
    }

    if (head->next == nullptr){    // Kondisi jika didalam linked list hanya memiliki satu node
        delete head;               // Menghapus head
        head = nullptr;            // Mengubah head menjadi nullptr
        return;
    }

    Node *current = head;                       // pointer current menujuk ke head untuk
    while (current->next->next != nullptr){     // mencari node terakhir dalam linked list
        current = current->next;
    }

    Node *temp = current->next;    // ponter temp yang menunjuk alamat node terakhir
    current->next = nullptr;       // Mengatur prev dari node sebelumnya menjadi nullptr 

    delete temp;         // Hapus node terakhir
}

// Fungsi untuk menghapus node setelah node dengan nilai yang ditentukan dari linked list
void deleteAfter(Node *head, int valueToDeleteAfter){
    if (head == nullptr){       // Kondisi jika linked list kosong maka akan menampilkan 
        cout << "Linked list kosong, tidak ada yang dihapus" << endl;
        return;
    }

    Node *current = head;           //Pointer current menujuk ke head untuk 
    while (current != nullptr && current->data != valueToDeleteAfter){   // Mencari node dengan nilai yang sesuai
        current = current->next;
    }

    if (current == nullptr || current->next == nullptr){    // Jika node dengan nilai yang sesuai tidak ditemukan maka akn muncul
        cout << "Node dengan nilai " << valueToDeleteAfter << " tidak ditemukan atau tidak memiliki node setelahnya" << endl;
        return;
    }

    Node *temp = current->next;         // Simpan alamat node yang akan dihapus
    current->next = temp->next;         // Hubungkan next node sebelumnya dengan node setelah yang akan dihapus
    if (temp->next != nullptr){         // Jika node setelah yang akan dihapus bukan node terakhir
        temp->next->prev = current;     // Hubungkan prev node setelah temp dengan alamat sebelumnya
    }
    
    delete temp;   // Hapus node
}

// Fungsi untuk menghapus node sebelum node dengan nilai yang ditentukan dari linked list
void deleteBefore(Node* &head, int valueToDeleteBefore){
    if (head == nullptr){              // Kondisi jika linked list kosong maka akan menampilkan 
        cout << "List kosong, tidak ada yang dihapus" << endl;
    }
    else{                                     // Kondisi jika linked list terdapat node
        Node *current = head;                // Current menunjuk ke head untuk
        while (current != nullptr && current->data != valueToDeleteBefore){ // mencari node dengan nilai sesuai
            current = current->next;
        }

        Node *temp = current->prev;     // Pointer untuk menyimpan node yang akan di hapus
        current->prev = temp->prev;     // Mengubah current prev menjadi alamat sebelum temp
        if (current->prev == nullptr){  // Kondisi jika prev berisi nullptr
            head = head->next;          // Mengubah head menjadi head next
        }
        else{
            current->prev->next = current; // Jika prev bukan nullptr maka current prev diisi dengan alamat current
        }
        delete temp; // Hapus temp
        //if (current == nullptr || current->prev == nullptr){
        //    cout << "Gagal menghapus. Node " << key << " Tidak ditemukan atau node sebelumnya tidak ada" << endl;
        //}
        //else
        //{
        //    
        //}
    }
}

// Fungsi untuk menghapus node sesuai nilai yang ditentukan
void deleteToPoint(Node* &head, int valueToDeleteToPoint){
    if (head == nullptr) {  // Kondisi jika linked list kosong maka akan menampilkan 
        cout << "List kosong, tidak ada yang dihapus" << endl;
    }
    else{                       // Kondisi jika linked list tidak kosong
        Node *current = head;    // Pointer current menujuk head untuk
        while (current != nullptr && current->data != valueToDeleteToPoint){ // Mancari node dengan nilai sesuai
            current = current->next;
        }

        if (current == nullptr){    //Kondisi jika node yang dicari tidak ditemukan
            cout << "node " << valueToDeleteToPoint << " tidak ditemukan" << endl;
        }
        else{
            if (current->prev == nullptr){        // Kondisi jika menghapus node pertama
                head = head->next;                  // Ubah head menjadi head next
                head->prev = nullptr;               // Ubah head prev menjadi nullptr
            }
            else if (current->prev == nullptr){   // Kondisi jika menghapus node terakhir
                current->prev->next = nullptr;      // Ubah next pada node sebelumnya menjadi nullptr 
            }
            else {                                // Kondisi jika menghapus node ditengah
                current->prev->next = current->next; // Ubah node sebelum current diisi alamat node setelah current
                current->next->prev = current->prev; // Ubah prev dari node setelah current diisi alamat node sebelum current
            }
            delete current;                       // Hapus current
        }
    }
}

// Fungsi untuk menampilkan informasi tentang setiap node dalam linked list
void displayList(Node *head)
{
    Node *current = head;
    cout << "Informasi tentang setiap node:" << endl;
    while (current != nullptr)
    {
        cout << "Alamat: " << current << endl;
        cout << "Nilai: " << current->data << endl;
        cout << "Alamat prev: " << current->prev << endl;
        cout << "Alamat next: " << current->next << endl << endl;
        current = current->next;
    }
}


int main()
{
    // Inisialisasi pointer simpul
    Node *head = nullptr;

    cout << "            Isi dalam Linked List" << endl;
    head = createNode(5);
    insertFirst(head, 8);
    insertFirst(head, 3);
    displayList(head);
    cout << "           Delete First" << endl;
    deleteFirst(head);
    displayList(head);
    cout << "=====================================================================" << endl;

    cout << "            Isi dalam Linked List" << endl;
    insertFirst(head, 3);
    displayList(head);
    cout << "           Delete Last" << endl;
    deleteLast(head);
    displayList(head);
    cout << "=====================================================================" << endl;

    cout << "            Isi dalam Linked List" << endl;
    insertLast(head, 5);
    displayList(head);
    cout << "           Delete After" << endl;
    deleteAfter(head, 3);
    displayList(head);
    cout << "=====================================================================" << endl;

    cout << "            Isi dalam Linked List" << endl;
    insertAfter(head, 3, 8);
    displayList(head);
    cout << "           Delete Before" << endl;
    deleteBefore(head, 5);
    displayList(head);
    cout << "=====================================================================" << endl;

    cout << "            Isi dalam Linked List" << endl;
    insertBefore(head, 5, 8);
    displayList(head);
    cout << "           Delete To Point" << endl;
    deleteToPoint(head, 8);
    displayList(head);
    cout << "=====================================================================" << endl;
    return 0;
}