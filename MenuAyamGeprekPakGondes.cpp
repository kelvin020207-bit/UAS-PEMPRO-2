#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Global username variable to track current user
string usernameAktif = "";

struct MenuItem {
    int id;
    string nama;
    int harga;
    MenuItem* next;
};

struct MenuList {
    MenuItem* head;
    int jumlah;
};

struct OrderItem {
    int id;
    string namaPelanggan;
    string namaMenu;
    int jumlah;
    int total;
    OrderItem* next;
};

struct OrderList {
    OrderItem* head;
    int jumlah;
    int totalPendapatan;
};

// Struktur untuk item dalam keranjang belanja (untuk multiple items per order)
struct CartItem {
    string namaMenu;
    int harga;
    int jumlah;
    int subtotal;
};

int bacaAngka(string pesan);
bool cekNama(string nama);
bool cekHarga(int harga);
bool cekJumlah(int jumlah);

int login(string username, string password);
string bacaUsername();

void tambahMenu(MenuList* list, string nama, int harga);
bool hapusMenu(MenuList* list, int id);
void tampilkanMenu(MenuList* list);
MenuItem* cariMenuById(MenuList* list, int id);
void cariMenu(MenuList* list, string keyword);
void urutkanMenu(MenuList* list);
void muatMenu(MenuList* list);
void simpanMenu(MenuList* list);
void isiMenuAwal(MenuList* list);

int hitungTotal(int harga, int jumlah);
void buatPesanan(OrderList* list, string pelanggan, string menu, int jumlah, int total);
void tampilkanPesanan(OrderList* list);
void cetakStruk(string pelanggan, vector<CartItem>& cart, int totalBayar);
void muatPesanan(OrderList* list);
void simpanPesanan(OrderList* list);
void tampilkanLaporan(OrderList* list);

void tampilkanHeader();
void menuAdmin(MenuList* menu, OrderList* pesanan);
void menuKasir(MenuList* menu, OrderList* pesanan);
void menuUtama(MenuList* menu, OrderList* pesanan);
void buatPesananMultiple(MenuList* menu, OrderList* pesanan);

void hapusSemuaMenu(MenuList* list);
void hapusSemuaPesanan(OrderList* list);

int bacaAngka(string pesan) {
    int angka;

    while (true) {
        cin >> angka;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Input salah! Masukkan angka untuk " << pesan << ": ";
        } else {
            return angka;
        }
    }
}

bool cekNama(string nama) {
    if (nama == "" || nama.length() < 2) {
        cout << "Nama tidak valid!\n";
        return false;
    }
    return true;
}

bool cekHarga(int harga) {
    if (harga <= 0) {
        cout << "Harga harus lebih dari 0!\n";
        return false;
    }
    return true;
}

bool cekJumlah(int jumlah) {
    if (jumlah <= 0) {
        cout << "Jumlah harus lebih dari 0!\n";
        return false;
    }
    return true;
}

// Fungsi untuk membaca username dengan validasi
string bacaUsername() {
    string username;
    while (true) {
        cout << "Username: ";
        cin >> username;
        
        if (username == "" || username.length() < 1) {
            cout << "Username tidak boleh kosong!\n";
            continue;
        }
        break;
    }
    return username;
}

int login(string username, string password) {
    if (username == "admin" && password == "admin123") {
        return 1;
    } else if (username == "kasir" && password == "kasir123") {
        return 2;
    }
    return 0;
}

void tambahMenu(MenuList* list, string nama, int harga) {
    MenuItem* baru = new MenuItem();
    baru->id = list->jumlah + 1;
    baru->nama = nama;
    baru->harga = harga;
    baru->next = NULL;

    if (list->head == NULL) {
        list->head = baru;
    } else {
        MenuItem* temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = baru;
    }

    list->jumlah++;
}

bool hapusMenu(MenuList* list, int id) {
    if (list->head == NULL) {
        return false;
    }

    MenuItem* temp = list->head;
    MenuItem* prev = NULL;

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return false;
    }

    if (prev == NULL) {
        list->head = temp->next;
    } else {
        prev->next = temp->next;
    }

    delete temp;
    list->jumlah--;
    return true;
}

void tampilkanMenu(MenuList* list) {
    cout << "\n--- DAFTAR MENU ---\n";
    cout << "ID | Nama Menu              | Harga\n";
    cout << "---+------------------------+--------\n";

    MenuItem* temp = list->head;
    while (temp != NULL) {
        cout << temp->id << "  | " << temp->nama << " | Rp " << temp->harga << "\n";
        temp = temp->next;
    }
}

MenuItem* cariMenuById(MenuList* list, int id) {
    MenuItem* temp = list->head;

    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

void cariMenu(MenuList* list, string keyword) {
    cout << "\nHasil pencarian: " << keyword << "\n";

    bool ketemu = false;
    MenuItem* temp = list->head;

    while (temp != NULL) {
        if (temp->nama.find(keyword) != string::npos) {
            cout << temp->id << " | " << temp->nama << " | Rp " << temp->harga << "\n";
            ketemu = true;
        }
        temp = temp->next;
    }

    if (!ketemu) {
        cout << "Menu tidak ditemukan.\n";
    }
}

void urutkanMenu(MenuList* list) {
    if (list->head == NULL) {
        return;
    }

    bool tukar;
    do {
        tukar = false;
        MenuItem* temp = list->head;

        while (temp->next != NULL) {
            if (temp->harga > temp->next->harga) {
                int idTemp = temp->id;
                string namaTemp = temp->nama;
                int hargaTemp = temp->harga;

                temp->id = temp->next->id;
                temp->nama = temp->next->nama;
                temp->harga = temp->next->harga;

                temp->next->id = idTemp;
                temp->next->nama = namaTemp;
                temp->next->harga = hargaTemp;

                tukar = true;
            }
            temp = temp->next;
        }
    } while (tukar);
}

void muatMenu(MenuList* list) {
    ifstream file("data/menu.txt");
    if (!file) {
        return;
    }

    list->head = NULL;
    list->jumlah = 0;

    string nama;
    int harga;

    while (getline(file, nama, '|')) {
        file >> harga;
        file.ignore(1000, '\n');
        tambahMenu(list, nama, harga);
    }

    file.close();
}

void simpanMenu(MenuList* list) {
    ofstream file("data/menu.txt");
    MenuItem* temp = list->head;

    while (temp != NULL) {
        file << temp->nama << "|" << temp->harga << "\n";
        temp = temp->next;
    }

    file.close();
}

void isiMenuAwal(MenuList* list) {
    tambahMenu(list, "Ayam Geprek Original", 15000);
    tambahMenu(list, "Ayam Geprek Mozzarella", 20000);
    tambahMenu(list, "Ayam Geprek Sambal Matah", 18000);
    tambahMenu(list, "Es Teh Manis", 5000);
    tambahMenu(list, "Es Jeruk", 7000);
}

int hitungTotal(int harga, int jumlah) {
    return harga * jumlah;
}

void buatPesanan(OrderList* list, string pelanggan, string menu, int jumlah, int total) {
    OrderItem* baru = new OrderItem();
    baru->id = list->jumlah + 1;
    baru->namaPelanggan = pelanggan;
    baru->namaMenu = menu;
    baru->jumlah = jumlah;
    baru->total = total;
    baru->next = NULL;

    if (list->head == NULL) {
        list->head = baru;
    } else {
        OrderItem* temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = baru;
    }

    list->jumlah++;
    list->totalPendapatan += total;
}

void tampilkanPesanan(OrderList* list) {
    cout << "\n--- ANTRIAN PESANAN ---\n";

    if (list->head == NULL) {
        cout << "Belum ada pesanan.\n";
        return;
    }

    OrderItem* temp = list->head;
    while (temp != NULL) {
        cout << "#" << temp->id << " | "
             << temp->namaPelanggan << " | "
             << temp->namaMenu << " x" << temp->jumlah
             << " | Rp " << temp->total << "\n";
        temp = temp->next;
    }
}

void cetakStruk(string pelanggan, vector<CartItem>& cart, int totalBayar) {
    cout << "\n===== STRUK PESANAN =====\n";
    cout << "Warung Ayam Geprek Pak Gondes\n";
    cout << "Pelanggan: " << pelanggan << "\n";
    cout << "Kasir    : " << usernameAktif << "\n";
    cout << "\n--- DETAIL PESANAN ---\n";
    cout << "Menu                      | Qty | Harga    | Subtotal\n";
    cout << "-------------------------+-----+----------+---------\n";
    
    for (int i = 0; i < cart.size(); i++) {
        cout << cart[i].namaMenu << " | " << cart[i].jumlah << " | Rp " 
             << cart[i].harga << " | Rp " << cart[i].subtotal << "\n";
    }
    
    cout << "========================= TOTAL: Rp " << totalBayar << " =\n";
    cout << "=========================\n";
}

void muatPesanan(OrderList* list) {
    ifstream file("data/pesanan.txt");
    list->head = NULL;
    list->jumlah = 0;
    list->totalPendapatan = 0;

    if (!file) {
        return;
    }

    string pelanggan, menu;
    int jumlah, total;

    while (getline(file, pelanggan, '|')) {
        getline(file, menu, '|');
        file >> jumlah;
        file.ignore(1);
        file >> total;
        file.ignore(1000, '\n');

        buatPesanan(list, pelanggan, menu, jumlah, total);
    }

    file.close();
}

void simpanPesanan(OrderList* list) {
    ofstream file("data/pesanan.txt");
    OrderItem* temp = list->head;

    while (temp != NULL) {
        file << temp->namaPelanggan << "|"
             << temp->namaMenu << "|"
             << temp->jumlah << "|"
             << temp->total << "\n";
        temp = temp->next;
    }

    file.close();
}

void tampilkanLaporan(OrderList* list) {
    cout << "\n===== LAPORAN PENJUALAN =====\n";
    cout << "Total Pesanan   : " << list->jumlah << "\n";
    cout << "Total Pendapatan: Rp " << list->totalPendapatan << "\n";

    cout << "\nDaftar Pesanan:\n";
    OrderItem* temp = list->head;

    while (temp != NULL) {
        cout << temp->namaMenu << " - " << temp->jumlah << " porsi\n";
        temp = temp->next;
    }

    cout << "=============================\n";
}

void tampilkanHeader() {
    cout << "\n================================\n";
    cout << " WARUNG AYAM GEPREK PAK GONDES\n";
    cout << "================================\n";
    if (usernameAktif != "") {
        cout << "Pengguna: " << usernameAktif << "\n";
    }
}

void menuAdmin(MenuList* menu, OrderList* pesanan) {
    int pilihan;
    bool kembali = false;

    while (!kembali) {
        cout << "\n--- MENU ADMIN ---\n";
        cout << "1. Lihat Menu\n";
        cout << "2. Tambah Menu\n";
        cout << "3. Hapus Menu\n";
        cout << "4. Cari Menu\n";
        cout << "5. Urutkan Menu\n";
        cout << "6. Lihat Laporan\n";
        cout << "7. Kembali\n";
        cout << "Pilihan: ";
        pilihan = bacaAngka("menu admin");

        if (pilihan == 1) {
            tampilkanMenu(menu);
        }
        else if (pilihan == 2) {
            string nama;
            int harga;

            cin.ignore(1000, '\n');
            cout << "Nama menu: ";
            getline(cin, nama);
            cout << "Berapa harganya? ";
            harga = bacaAngka("harga");

            if (cekHarga(harga)) {
                tambahMenu(menu, nama, harga);
                cout << "Menu berhasil ditambahkan.\n";
            }
        }
        else if (pilihan == 3) {
            tampilkanMenu(menu);
            cout << "Silakan pilih menu yang ingin dihapus dengan memasukkan ID menu di atas: ";
            int id = bacaAngka("ID menu");
            if (hapusMenu(menu, id)) {
                cout << "Menu berhasil dihapus.\n";
            } else {
                cout << "Menu tidak ditemukan.\n";
            }
        }
        else if (pilihan == 4) {
            string keyword;
            cin.ignore(1000, '\n');
            cout << "Cari menu: ";
            getline(cin, keyword);
            cariMenu(menu, keyword);
        }
        else if (pilihan == 5) {
            urutkanMenu(menu);
            cout << "Menu sudah diurutkan.\n";
            tampilkanMenu(menu);
        }
        else if (pilihan == 6) {
            tampilkanLaporan(pesanan);
        }
        else if (pilihan == 7) {
            kembali = true;
        }
        else {
            cout << "Pilihan tidak valid.\n";
        }
    }
}

// Fungsi baru untuk membuat pesanan dengan multiple items
void buatPesananMultiple(MenuList* menu, OrderList* pesanan) {
    string nama;
    int pilihan;
    vector<CartItem> cart;
    int totalBayar = 0;

    cin.ignore(1000, '\n');
    cout << "Nama pelanggan: ";
    getline(cin, nama);

    if (!cekNama(nama)) {
        return;
    }

    bool lanjutTambah = true;
    while (lanjutTambah) {
        cout << "\n--- TAMBAH ITEM KE KERANJANG ---\n";
        tampilkanMenu(menu);
        
        cout << "\nSilakan pilih menu yang ingin dipesan (masukkan ID): ";
        int idMenu = bacaAngka("ID menu");
        cout << "Berapa banyak yang ingin Anda pesan? ";
        int jumlah = bacaAngka("jumlah");

        if (!cekJumlah(jumlah)) {
            continue;
        }

        MenuItem* item = cariMenuById(menu, idMenu);
        if (item != NULL) {
            int subtotal = hitungTotal(item->harga, jumlah);
            CartItem cartItem;
            cartItem.namaMenu = item->nama;
            cartItem.harga = item->harga;
            cartItem.jumlah = jumlah;
            cartItem.subtotal = subtotal;
            
            cart.push_back(cartItem);
            totalBayar += subtotal;
            
            cout << "\nItem '" << item->nama << "' berhasil ditambahkan ke keranjang!\n";
            cout << "Subtotal: Rp " << subtotal << "\n";
        } else {
            cout << "Menu tidak ditemukan.\n";
        }

        cout << "\nTotal saat ini: Rp " << totalBayar << "\n";
        cout << "Apakah ingin menambah item lagi? (1=Ya, 0=Tidak): ";
        lanjutTambah = bacaAngka("pilihan");
    }

    // Proses checkout
    if (cart.size() > 0) {
        cetakStruk(nama, cart, totalBayar);
        
        // Simpan setiap item ke pesanan
        for (int i = 0; i < cart.size(); i++) {
            buatPesanan(pesanan, nama, cart[i].namaMenu, cart[i].jumlah, cart[i].subtotal);
        }
        
        cout << "\nPesanan berhasil dibuat!\n";
    } else {
        cout << "\nTidak ada item yang dipesan.\n";
    }
}

void menuKasir(MenuList* menu, OrderList* pesanan) {
    int pilihan;
    bool kembali = false;

    while (!kembali) {
        cout << "\n--- MENU KASIR ---\n";
        cout << "1. Lihat Menu\n";
        cout << "2. Buat Pesanan (Multiple Items)\n";
        cout << "3. Lihat Pesanan\n";
        cout << "4. Kembali\n";
        cout << "Pilihan: ";
        pilihan = bacaAngka("menu kasir");

        if (pilihan == 1) {
            tampilkanMenu(menu);
        }
        else if (pilihan == 2) {
            buatPesananMultiple(menu, pesanan);
        }
        else if (pilihan == 3) {
            tampilkanPesanan(pesanan);
        }
        else if (pilihan == 4) {
            kembali = true;
        }
        else {
            cout << "Pilihan tidak valid.\n";
        }
    }
}

void menuUtama(MenuList* menu, OrderList* pesanan) {
    int pilihan;
    bool jalan = true;

    while (jalan) {
        tampilkanHeader();
        cout << "1. Login\n";
        cout << "2. Keluar\n";
        cout << "Pilihan: ";
        pilihan = bacaAngka("menu utama");

        if (pilihan == 1) {
            // Minta username terlebih dahulu
            string username = bacaUsername();
            cout << "Password: ";
            string password;
            cin >> password;

            int role = login(username, password);

            if (role == 1) {
                usernameAktif = username;  // Set username global
                cout << "Login admin berhasil.\n";
                menuAdmin(menu, pesanan);
                usernameAktif = "";  // Clear username setelah logout
            }
            else if (role == 2) {
                usernameAktif = username;  // Set username global
                cout << "Login kasir berhasil.\n";
                menuKasir(menu, pesanan);
                usernameAktif = "";  // Clear username setelah logout
            }
            else {
                cout << "Login gagal. Username atau password salah.\n";
            }
        }
        else if (pilihan == 2) {
            simpanMenu(menu);
            simpanPesanan(pesanan);
            cout << "Program selesai. Data tersimpan.\n";
            jalan = false;
        }
        else {
            cout << "Pilihan tidak valid.\n";
        }
    }
}

void hapusSemuaMenu(MenuList* list) {
    MenuItem* temp = list->head;

    while (temp != NULL) {
        MenuItem* hapus = temp;
        temp = temp->next;
        delete hapus;
    }
}

void hapusSemuaPesanan(OrderList* list) {
    OrderItem* temp = list->head;

    while (temp != NULL) {
        OrderItem* hapus = temp;
        temp = temp->next;
        delete hapus;
    }
}

int main() {
    MenuList* menu = new MenuList();
    OrderList* pesanan = new OrderList();

    menu->head = NULL;
    menu->jumlah = 0;

    pesanan->head = NULL;
    pesanan->jumlah = 0;
    pesanan->totalPendapatan = 0;

    muatMenu(menu);
    muatPesanan(pesanan);

    if (menu->head == NULL) {
        isiMenuAwal(menu);
        simpanMenu(menu);
    }

    menuUtama(menu, pesanan);

    hapusSemuaMenu(menu);
    hapusSemuaPesanan(pesanan);

    delete menu;
    delete pesanan;

    return 0;
}
