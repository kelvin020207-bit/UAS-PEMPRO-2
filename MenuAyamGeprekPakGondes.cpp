#include <iostream>
#include <fstream> // Menyertakan library fstream untuk operasi file, memungkinkan aplikasi untuk membaca dan menulis data menu dan pesanan ke file untuk penyimpanan data yang persisten.
#include <string> // Menyertakan library string untuk menggunakan tipe data string, memungkinkan aplikasi untuk menyimpan dan memanipulasi teks seperti nama menu, nama pelanggan, dan kata kunci pencarian.
using namespace std;

struct MenuItem { // Struktur untuk item menu, menyimpan informasi tentang menu yang tersedia.
    int id;
    string nama;
    int harga;
    MenuItem* next;
};

struct MenuList { // Struktur untuk daftar menu, menyimpan pointer ke item menu pertama dan jumlah total menu.
    MenuItem* head;
    int jumlah;
};

struct OrderItem { // Struktur untuk item pesanan, menyimpan informasi tentang pesanan yang dibuat oleh pelanggan.
    int id;
    string namaPelanggan;
    string namaMenu;
    int jumlah;
    int total;
    OrderItem* next;
};

struct OrderList { // Struktur untuk daftar pesanan, menyimpan pointer ke item pesanan pertama, jumlah total pesanan, dan total pendapatan.
    OrderItem* head;
    int jumlah;
    int totalPendapatan;
};

int bacaAngka(string pesan); // Fungsi untuk membaca input angka dari pengguna dengan validasi.
bool cekNama(string nama); // Fungsi untuk memeriksa validitas nama, memastikan nama tidak kosong dan memiliki panjang minimal.
bool cekHarga(int harga); // Fungsi untuk memeriksa validitas harga, memastikan harga lebih dari 0.
bool cekJumlah(int jumlah); // Fungsi untuk memeriksa validitas jumlah, memastikan jumlah lebih dari 0.

int login(string username, string password); // Fungsi untuk memeriksa kredensial login, mengembalikan peran pengguna berdasarkan username dan password.

void tambahMenu(MenuList* list, string nama, int harga); // Fungsi untuk menambahkan item menu baru ke daftar menu.
bool hapusMenu(MenuList* list, int id); //  Fungsi untuk menghapus item menu berdasarkan ID, mengembalikan true jika berhasil dihapus, false jika tidak ditemukan.
void tampilkanMenu(MenuList* list);// Fungsi untuk menampilkan daftar menu yang tersedia.
MenuItem* cariMenuById(MenuList* list, int id); // Fungsi untuk mencari item menu berdasarkan ID, mengembalikan pointer ke item menu jika ditemukan, NULL jika tidak ditemukan.
void cariMenu(MenuList* list, string keyword); // Fungsi untuk mencari item menu berdasarkan kata kunci, menampilkan hasil pencarian yang cocok dengan nama menu.
void urutkanMenu(MenuList* list); // Fungsi untuk mengurutkan daftar menu berdasarkan harga menggunakan algoritma bubble sort.
void muatMenu(MenuList* list); // Fungsi untuk memuat data menu dari file "data/menu.txt" ke dalam daftar menu.
void simpanMenu(MenuList* list); // Fungsi untuk menyimpan data menu dari daftar menu ke file "data/menu.txt" dalam format yang sesuai.
void isiMenuAwal(MenuList* list); // Fungsi untuk mengisi daftar menu dengan data awal jika file menu tidak ditemukan atau kosong.

int hitungTotal(int harga, int jumlah); // Fungsi untuk menghitung total harga berdasarkan harga satuan dan jumlah yang dipesan.
void buatPesanan(OrderList* list, string pelanggan, string menu, int jumlah, int total); // Fungsi untuk membuat pesanan baru dan menambahkannya ke daftar pesanan.
void tampilkanPesanan(OrderList* list); // Fungsi untuk menampilkan daftar pesanan yang telah dibuat oleh pelanggan.
void cetakStruk(string pelanggan, string menu, int jumlah, int total); //   Fungsi untuk mencetak struk pesanan dengan informasi pelanggan, menu, jumlah, dan total harga.
void muatPesanan(OrderList* list); // Fungsi untuk memuat data pesanan dari file "data/pesanan.txt" ke dalam daftar pesanan, termasuk total pendapatan.
void simpanPesanan(OrderList* list); // Fungsi untuk menyimpan data pesanan dari daftar pesanan ke file "data/pesanan.txt" dalam format yang sesuai, termasuk total pendapatan.
void tampilkanLaporan(OrderList* list); // Fungsi untuk menampilkan laporan penjualan, termasuk total pesanan, total pendapatan, dan daftar pesanan yang telah dibuat.

void tampilkanHeader(); // Fungsi untuk menampilkan header utama aplikasi, memberikan identitas dan informasi tentang warung ayam geprek.
void menuAdmin(MenuList* menu, OrderList* pesanan); //  Fungsi untuk menampilkan menu admin, memungkinkan admin untuk melihat, menambah, menghapus, mencari, dan mengurutkan menu, serta melihat laporan penjualan.
void menuKasir(MenuList* menu, OrderList* pesanan); // Fungsi untuk menampilkan menu kasir, memungkinkan kasir untuk melihat menu, membuat pesanan, dan melihat daftar pesanan yang telah dibuat.
void menuUtama(MenuList* menu, OrderList* pesanan); // Fungsi untuk menampilkan menu utama aplikasi, memungkinkan pengguna untuk login sebagai admin atau kasir, atau keluar dari aplikasi.

void hapusSemuaMenu(MenuList* list); // Fungsi untuk menghapus semua item menu dari daftar menu, digunakan saat program selesai untuk membersihkan memori.
void hapusSemuaPesanan(OrderList* list); // Fungsi untuk menghapus semua item pesanan dari daftar pesanan, digunakan saat program selesai untuk membersihkan memori.

int bacaAngka(string pesan) { // Fungsi untuk membaca input angka dari pengguna dengan validasi, memastikan input yang diberikan adalah angka yang valid.
    int angka; // Variabel untuk menyimpan angka yang dibaca dari input pengguna.

    while (true) { // Loop terus-menerus hingga input yang valid diterima.
        cin >> angka; // Membaca input dari pengguna dan menyimpannya dalam variabel angka.

        if (cin.fail()) { // Memeriksa apakah input gagal (bukan angka).
            cin.clear(); //   Menghapus flag error pada cin agar bisa menerima input lagi.
            cin.ignore(1000, '\n'); // Mengabaikan sisa input yang tidak valid hingga akhir baris.
            cout << "Input salah! Masukkan angka untuk " << pesan << ": "; // Memberikan pesan kesalahan dan meminta input ulang.
        } else { // Jika input valid, keluar dari loop dan kembalikan angka yang dibaca.
            return angka; // Mengembalikan angka yang valid yang telah dibaca dari input pengguna.
        }
    }
}

bool cekNama(string nama) { // Fungsi untuk memeriksa validitas nama, memastikan nama tidak kosong dan memiliki panjang minimal 2 karakter.
    if (nama == "" || nama.length() < 2) { // Memeriksa apakah nama kosong atau memiliki panjang kurang dari 2 karakter.
        cout << "Nama tidak valid!\n"; // Memberikan pesan kesalahan jika nama tidak valid.
        return false; // Mengembalikan false jika nama tidak valid.
    }
    return true; // Mengembalikan true jika nama valid.
}

bool cekHarga(int harga) { // Fungsi untuk memeriksa validitas harga, memastikan harga lebih dari 0.
    if (harga <= 0) { // Memeriksa apakah harga kurang dari atau sama dengan 0.
        cout << "Harga harus lebih dari 0!\n"; // Memberikan pesan kesalahan jika harga tidak valid.
        return false;// Mengembalikan false jika harga tidak valid.
    }
    return true; // Mengembalikan true jika harga valid.
}

bool cekJumlah(int jumlah) { // Fungsi untuk memeriksa validitas jumlah, memastikan jumlah lebih dari 0.
    if (jumlah <= 0) { // Memeriksa apakah jumlah kurang dari atau sama dengan 0.
        cout << "Jumlah harus lebih dari 0!\n"; // Memberikan pesan kesalahan jika jumlah tidak valid.
        return false; // Mengembalikan false jika jumlah tidak valid.
    }
    return true; // Mengembalikan true jika jumlah valid.
}

int login(string username, string password) { // Fungsi untuk memeriksa kredensial login, mengembalikan peran pengguna berdasarkan username dan password.
    if (username == "admin" && password == "admin123") { // Memeriksa apakah username dan password cocok dengan kredensial admin.
        return 1; // Mengembalikan 1 jika login berhasil sebagai admin.
    } else if (username == "kasir" && password == "kasir123") { // Memeriksa apakah username dan password cocok dengan kredensial kasir.
        return 2;// Mengembalikan 2 jika login berhasil sebagai kasir.
    }
    return 0; //    Mengembalikan 0 jika login gagal (kredensial tidak cocok).
}

void tambahMenu(MenuList* list, string nama, int harga) { // Fungsi untuk menambahkan item menu baru ke daftar menu, membuat item menu baru dan menambahkannya ke akhir daftar.
    MenuItem* baru = new MenuItem(); // Membuat item menu baru dengan alokasi memori dinamis.
    baru->id = list->jumlah + 1; // Menetapkan ID untuk item menu baru berdasarkan jumlah menu saat ini ditambah satu.
    baru->nama = nama; // Menetapkan nama untuk item menu baru.
    baru->harga = harga; // Menetapkan harga untuk item menu baru.
    baru->next = NULL;// Menetapkan pointer next untuk item menu baru ke NULL, karena ini akan menjadi item terakhir dalam daftar.

    if (list->head == NULL) { // Memeriksa apakah daftar menu kosong (head adalah NULL).
        list->head = baru; // Jika daftar kosong, item menu baru menjadi head dari daftar.
    } else { // Jika daftar tidak kosong, cari item menu terakhir dan tambahkan item menu baru di akhir daftar.
        MenuItem* temp = list->head; // Membuat pointer sementara untuk menelusuri daftar menu, mulai dari head.
        while (temp->next != NULL) { // Loop untuk mencari item menu terakhir (item yang next-nya NULL).
            temp = temp->next; // Memindahkan pointer sementara ke item menu berikutnya dalam daftar.
        }
        temp->next = baru; // Setelah menemukan item menu terakhir, set pointer next-nya ke item menu baru, menambahkan item menu baru ke akhir daftar.
    }

    list->jumlah++; // Menambah jumlah menu dalam daftar setelah menambahkan item menu baru.
}

bool hapusMenu(MenuList* list, int id) { // Fungsi untuk menghapus item menu berdasarkan ID, mencari item menu dengan ID yang diberikan dan menghapusnya dari daftar.
    if (list->head == NULL) { // Memeriksa apakah daftar menu kosong (head adalah NULL).
        return false; // Jika daftar kosong, tidak ada menu yang bisa dihapus, jadi kembalikan false.
    }

    MenuItem* temp = list->head; // Membuat pointer sementara untuk menelusuri daftar menu, mulai dari head.
    MenuItem* prev = NULL;// Membuat pointer untuk menyimpan item menu sebelumnya saat menelusuri daftar.

    while (temp != NULL && temp->id != id) { // Loop untuk mencari item menu dengan ID yang cocok, terus menelusuri daftar hingga menemukan item menu dengan ID yang diberikan atau mencapai akhir daftar.
        prev = temp; // Menyimpan item menu saat ini sebagai item menu sebelumnya sebelum memindahkan pointer sementara ke item menu berikutnya.
        temp = temp->next; // Memindahkan pointer sementara ke item menu berikutnya dalam daftar.
    }

    if (temp == NULL) { //  Memeriksa apakah item menu dengan ID yang diberikan tidak ditemukan (temp menjadi NULL setelah menelusuri daftar).
        return false; // Jika item menu tidak ditemukan, kembalikan false.
    }

    if (prev == NULL) { // Memeriksa apakah item menu yang akan dihapus adalah item menu pertama dalam daftar (prev masih NULL).
        list->head = temp->next; // Jika item menu pertama yang akan dihapus, set head dari daftar ke item menu berikutnya, menghapus item menu pertama dari daftar.
    } else { // Jika item menu yang akan dihapus bukan item menu pertama, set pointer next dari item menu sebelumnya ke item menu berikutnya, menghapus item menu dari daftar.
        prev->next = temp->next; // Set pointer next dari item menu sebelumnya ke item menu berikutnya, menghapus item menu dari daftar.
    }

    delete temp; // Menghapus item menu yang telah dihapus dari memori untuk mencegah kebocoran memori.
    list->jumlah--; // Mengurangi jumlah menu dalam daftar setelah menghapus item menu.
    return true; // Mengembalikan true untuk menunjukkan bahwa item menu berhasil dihapus.
}

void tampilkanMenu(MenuList* list) { // Fungsi untuk menampilkan daftar menu yang tersedia, menampilkan ID, nama, dan harga dari setiap item menu dalam daftar.
    cout << "\n--- DAFTAR MENU ---\n"; // Menampilkan header untuk daftar menu.
    cout << "ID | Nama Menu              | Harga\n"; // Menampilkan header kolom untuk ID, Nama Menu, dan Harga.
    cout << "---+------------------------+--------\n"; // Menampilkan garis pemisah antara header dan daftar menu.

    MenuItem* temp = list->head; // Membuat pointer sementara untuk menelusuri daftar menu, mulai dari head.
    while (temp != NULL) { // Loop untuk menampilkan setiap item menu dalam daftar, terus menelusuri daftar hingga mencapai akhir (temp menjadi NULL).  
        cout << temp->id << "  | " << temp->nama << " | Rp " << temp->harga << "\n"; // Menampilkan ID, nama, dan harga dari item menu saat ini.
        temp = temp->next; // Memindahkan pointer sementara ke item menu berikutnya dalam daftar.
    }
}

MenuItem* cariMenuById(MenuList* list, int id) { // Fungsi untuk mencari item menu berdasarkan ID, menelusuri daftar menu untuk menemukan item menu dengan ID yang cocok dan mengembalikan pointer ke item menu tersebut.
    MenuItem* temp = list->head; // Membuat pointer sementara untuk menelusuri daftar menu, mulai dari head.

    while (temp != NULL) { // Loop untuk mencari item menu dengan ID yang cocok, terus menelusuri daftar hingga menemukan item menu dengan ID yang diberikan atau mencapai akhir daftar.
        if (temp->id == id) { // Memeriksa apakah ID dari item menu saat ini cocok dengan ID yang diberikan.
            return temp; // Jika item menu dengan ID yang cocok ditemukan, kembalikan pointer ke item menu tersebut.
        }
        temp = temp->next; // Memindahkan pointer sementara ke item menu berikutnya dalam daftar.
    }

    return NULL; // Jika item menu dengan ID yang diberikan tidak ditemukan setelah menelusuri seluruh daftar, kembalikan NULL untuk menunjukkan bahwa item menu tidak ditemukan.
}

void cariMenu(MenuList* list, string keyword) { // Fungsi untuk mencari item menu berdasarkan kata kunci, menelusuri daftar menu untuk menemukan item menu yang nama-nya mengandung kata kunci dan menampilkan hasil pencarian.
    cout << "\nHasil pencarian: " << keyword << "\n"; //    

    bool ketemu = false; // Variabel untuk melacak apakah ada item menu yang cocok dengan kata kunci ditemukan.
    MenuItem* temp = list->head; // Membuat pointer sementara untuk menelusuri daftar menu, mulai dari head.

    while (temp != NULL) { // Loop untuk mencari item menu yang nama-nya mengandung kata kunci, terus menelusuri daftar hingga mencapai akhir (temp menjadi NULL).
        if (temp->nama.find(keyword) != string::npos) { // Memeriksa apakah nama dari item menu saat ini mengandung kata kunci (menggunakan fungsi find untuk mencari substring).
            cout << temp->id << " | " << temp->nama << " | Rp " << temp->harga << "\n"; // Jika item menu yang cocok ditemukan, tampilkan ID, nama, dan harga dari item menu tersebut.
            ketemu = true; // Set variabel ketemu menjadi true untuk menunjukkan bahwa setidaknya satu item menu yang cocok ditemukan.
        }
        temp = temp->next; // Memindahkan pointer sementara ke item menu berikutnya dalam daftar untuk melanjutkan pencarian.
    }

    if (!ketemu) { // Setelah menelusuri seluruh daftar, jika tidak ada item menu yang cocok ditemukan (ketemu tetap false), tampilkan pesan bahwa menu tidak ditemukan.
        cout << "Menu tidak ditemukan.\n"; // Menampilkan pesan bahwa menu tidak ditemukan jika tidak ada item menu yang nama-nya mengandung kata kunci.
    }
}

void urutkanMenu(MenuList* list) { // Fungsi untuk mengurutkan daftar menu berdasarkan harga menggunakan algoritma bubble sort, menukar posisi item menu dalam daftar jika harga item menu saat ini lebih besar dari harga item menu berikutnya.
    if (list->head == NULL) { // Memeriksa apakah daftar menu kosong (head adalah NULL).
        return; // Jika daftar kosong, tidak ada menu yang perlu diurutkan, jadi keluar dari fungsi.
    }

    bool tukar; //      Variabel untuk melacak apakah terjadi pertukaran selama proses pengurutan, digunakan untuk menentukan apakah perlu melakukan iterasi lagi.
    do { // Loop untuk melakukan iterasi pengurutan, terus melakukan iterasi hingga tidak ada pertukaran yang terjadi (tukar tetap false), yang berarti daftar sudah terurut.
        tukar = false;
        MenuItem* temp = list->head;

        while (temp->next != NULL) { // Loop untuk membandingkan setiap item menu dengan item menu
            if (temp->harga > temp->next->harga) { // Memeriksa apakah harga dari item menu saat ini lebih besar dari harga item menu berikutnya.
                int idTemp = temp->id; // Menyimpan sementara ID dari item menu saat ini sebelum menukar posisi.
                string namaTemp = temp->nama; // Menyimpan sementara nama dari item menu saat ini sebelum menukar posisi.
                int hargaTemp = temp->harga; // Menyimpan sementara harga dari item menu saat ini sebelum menukar posisi.

                temp->id = temp->next->id;// Menukar ID dari item menu saat ini dengan ID dari item menu berikutnya.
                temp->nama = temp->next->nama; // Menukar nama dari item menu saat ini dengan nama dari item menu berikutnya.
                temp->harga = temp->next->harga; // Menukar harga dari item menu saat ini dengan harga dari item menu berikutnya.

                temp->next->id = idTemp; // Menukar ID dari item menu berikutnya dengan ID yang disimpan sementara dari item menu saat ini.
                temp->next->nama = namaTemp; // Menukar nama dari item menu berikutnya dengan nama yang disimpan sementara dari item menu saat ini.
                temp->next->harga = hargaTemp; // Menukar harga dari item menu berikutnya dengan harga yang disimpan sementara dari item menu saat ini.

                tukar = true; // Set variabel tukar menjadi true untuk menunjukkan bahwa terjadi pertukaran selama iterasi ini, yang berarti perlu melakukan iterasi lagi untuk memastikan daftar benar-benar terurut.
            }
            temp = temp->next; // Memindahkan pointer sementara ke item menu berikutnya dalam daftar untuk melanjutkan proses perbandingan dan pengurutan.
        }
    } while (tukar); // Setelah menyelesaikan iterasi pengurutan, jika tidak ada pertukaran yang terjadi (tukar tetap false), keluar dari loop dan fungsi, karena daftar sudah terurut berdasarkan harga.
}

void muatMenu(MenuList* list) { //  Fungsi untuk memuat data menu dari file "data/menu.txt" ke dalam daftar menu, membaca setiap baris dari file, memisahkan nama dan harga, dan menambahkan item menu ke daftar menu.
    ifstream file("data/menu.txt"); // Membuka file "data/menu.txt" untuk membaca data menu.
    if (!file) { // Memeriksa apakah file berhasil dibuka, jika tidak berhasil (file tidak ditemukan atau tidak dapat dibuka), keluar dari fungsi tanpa melakukan apa pun.
        return; // Jika file tidak dapat dibuka, tidak ada data menu yang dapat dimuat, jadi keluar dari fungsi.
    }

    list->head = NULL; // Menginisialisasi head dari daftar menu ke NULL, menandakan bahwa daftar menu saat ini kosong sebelum memuat data dari file.
    list->jumlah = 0; // Menginisialisasi jumlah menu dalam daftar ke 0, menandakan bahwa belum ada menu yang dimuat dari file.

    string nama; // Variabel untuk menyimpan nama menu yang dibaca dari file.
    int harga; // Variabel untuk menyimpan harga menu yang dibaca dari file.

    while (getline(file, nama, '|')) { // Loop untuk membaca setiap baris dari file, menggunakan getline untuk membaca nama menu hingga karakter '|' sebagai pemisah.
        file >> harga; // Setelah membaca nama menu, membaca harga menu yang mengikuti setelah karakter '|'.
        file.ignore(1000, '\n'); // Mengabaikan sisa input pada baris yang sama setelah membaca harga, hingga akhir baris, untuk mempersiapkan pembacaan nama menu berikutnya pada iterasi selanjutnya.
        tambahMenu(list, nama, harga); // Menambahkan item menu yang baru dibaca (nama dan harga) ke dalam daftar menu menggunakan fungsi tambahMenu.
    }

    file.close(); // Menutup file setelah selesai membaca data menu untuk membebaskan sumber daya yang digunakan oleh file.
}

void simpanMenu(MenuList* list) { // Fungsi untuk menyimpan data menu dari daftar menu ke file "data/menu.txt" dalam format yang sesuai, menulis setiap item menu ke file dengan format "nama|harga".
    ofstream file("data/menu.txt"); // Membuka file "data/menu.txt" untuk menulis data menu, jika file tidak ada, akan dibuat baru, jika sudah ada, akan ditimpa dengan data baru.
    MenuItem* temp = list->head; // Membuat pointer sementara untuk menelusuri daftar menu, mulai dari head.

    while (temp != NULL) { // Loop untuk menulis setiap item menu dalam daftar ke file, terus menelusuri daftar hingga mencapai akhir (temp menjadi NULL).
        file << temp->nama << "|" << temp->harga << "\n";
        temp = temp->next;
    }

    file.close(); // Menutup file setelah selesai menulis data menu untuk memastikan data tersimpan dengan benar dan membebaskan sumber daya yang digunakan oleh file.
}

void isiMenuAwal(MenuList* list) { // Fungsi untuk mengisi daftar menu dengan data awal jika file menu tidak ditemukan atau kosong, menambahkan beberapa item menu default ke dalam daftar menu.
    tambahMenu(list, "Ayam Geprek Original", 15000); // Menambahkan item menu "Ayam Geprek Original" dengan harga 15000 ke dalam daftar menu menggunakan fungsi tambahMenu.
    tambahMenu(list, "Ayam Geprek Mozzarella", 20000); // Menambahkan item menu "Ayam Geprek Mozzarella" dengan harga 20000 ke dalam daftar menu menggunakan fungsi tambahMenu.
    tambahMenu(list, "Ayam Geprek Sambal Matah", 18000); // Menambahkan item menu "Ayam Geprek Sambal Matah" dengan harga 18000 ke dalam daftar menu menggunakan fungsi tambahMenu.
    tambahMenu(list, "Es Teh Manis", 5000); // Menambahkan item menu "Es Teh Manis" dengan harga 5000 ke dalam daftar menu menggunakan fungsi tambahMenu.
    tambahMenu(list, "Es Jeruk", 7000); // Menambahkan item menu "Es Jeruk" dengan harga 7000 ke dalam daftar menu menggunakan fungsi tambahMenu.
}

int hitungTotal(int harga, int jumlah) { // Fungsi untuk menghitung total harga berdasarkan harga satuan dan jumlah yang dipesan, mengalikan harga satuan dengan jumlah untuk mendapatkan total harga.
    return harga * jumlah; // Mengembalikan hasil perkalian antara harga satuan dan jumlah sebagai total harga untuk pesanan yang dibuat.
}

void buatPesanan(OrderList* list, string pelanggan, string menu, int jumlah, int total) { // Fungsi untuk membuat pesanan baru dan menambahkannya ke daftar pesanan, membuat item pesanan baru dengan informasi yang diberikan dan menambahkannya ke akhir daftar pesanan.
    OrderItem* baru = new OrderItem(); // Membuat item pesanan baru dengan alokasi memori dinamis.
    baru->id = list->jumlah + 1;
    baru->namaPelanggan = pelanggan;
    baru->namaMenu = menu;
    baru->jumlah = jumlah;
    baru->total = total;
    baru->next = NULL;

    if (list->head == NULL) { // Memeriksa apakah daftar pesanan kosong (head adalah NULL).
        list->head = baru;
    } else { // Jika daftar tidak kosong, cari item pesanan terakhir dan tambahkan item pesanan baru di akhir daftar.
        OrderItem* temp = list->head;
        while (temp->next != NULL) { // Loop untuk mencari item pesanan terakhir (item yang next-nya NULL).
            temp = temp->next;
        }
        temp->next = baru;
    }

    list->jumlah++;
    list->totalPendapatan += total;
}

void tampilkanPesanan(OrderList* list) { // Fungsi untuk menampilkan daftar pesanan yang telah dibuat oleh pelanggan, menampilkan ID, nama pelanggan, nama menu, jumlah, dan total harga dari setiap pesanan dalam daftar.
    cout << "\n--- ANTRIAN PESANAN ---\n";

    if (list->head == NULL) { // Memeriksa apakah daftar pesanan kosong (head adalah NULL).
        cout << "Belum ada pesanan.\n";
        return;
    }

    OrderItem* temp = list->head; // Membuat pointer
    while (temp != NULL) { // Loop untuk menampilkan setiap pesanan dalam daftar, terus menelusuri daftar hingga mencapai akhir (temp menjadi NULL).
        cout << "#" << temp->id << " | "
             << temp->namaPelanggan << " | "
             << temp->namaMenu << " x" << temp->jumlah
             << " | Rp " << temp->total << "\n";
        temp = temp->next;
    }
}

void cetakStruk(string pelanggan, string menu, int jumlah, int total) { // Fungsi untuk mencetak struk pesanan dengan informasi pelanggan, menu, jumlah, dan total harga, menampilkan struk pesanan yang berisi detail pesanan yang dibuat oleh pelanggan.
    cout << "\n===== STRUK PESANAN =====\n";
    cout << "Warung Ayam Geprek Pak Gondes\n";
    cout << "Pelanggan: " << pelanggan << "\n";
    cout << "Menu     : " << menu << "\n";
    cout << "Jumlah   : " << jumlah << "\n";
    cout << "Total    : Rp " << total << "\n";
    cout << "=========================\n";
}

void muatPesanan(OrderList* list) { // Fungsi untuk memuat data pesanan dari file "data/pesanan.txt" ke dalam daftar pesanan, membaca setiap baris dari file, memisahkan informasi pesanan, dan menambahkan item pesanan ke daftar pesanan, serta menghitung total pendapatan.
    ifstream file("data/pesanan.txt"); // Membuka file "data/pesanan.txt" untuk membaca data pesanan.
    list->head = NULL;
    list->jumlah = 0;
    list->totalPendapatan = 0;

    if (!file) { // Memeriksa apakah file berhasil dibuka, jika tidak berhasil (file tidak ditemukan atau tidak dapat dibuka), keluar dari fungsi tanpa melakukan apa pun.
        return;
    }

    string pelanggan, menu; // Variabel untuk menyimpan nama pelanggan dan nama menu yang dibaca dari file.
    int jumlah, total; // Variabel untuk menyimpan jumlah dan total harga yang dibaca dari file.

    while (getline(file, pelanggan, '|')) { // Loop untuk membaca setiap baris dari file, menggunakan getline untuk membaca nama pelanggan hingga karakter '|' sebagai pemisah.
        getline(file, menu, '|'); // Setelah membaca nama pelanggan, menggunakan getline lagi untuk membaca nama menu yang mengikuti setelah karakter '|'.
        file >> jumlah;
        file.ignore(1);
        file >> total;
        file.ignore(1000, '\n');

        buatPesanan(list, pelanggan, menu, jumlah, total); // Menambahkan item pesanan yang baru dibaca (nama pelanggan, nama menu, jumlah, dan total) ke dalam daftar pesanan menggunakan fungsi buatPesanan, serta menghitung total pendapatan berdasarkan total harga dari setiap pesanan yang dimuat.
    }

    file.close(); // Menutup file setelah selesai membaca data pesanan untuk membebaskan sumber daya yang digunakan oleh file.
}

void simpanPesanan(OrderList* list) { // Fungsi untuk menyimpan data pesanan dari daftar pesanan ke file "data/pesanan.txt" dalam format yang sesuai, menulis setiap item pesanan ke file dengan format "namaPelanggan|namaMenu|jumlah|total", serta menyimpan total pendapatan.
    ofstream file("data/pesanan.txt"); //   Membuka file "data/pesanan.txt" untuk menulis data pesanan, jika file tidak ada, akan dibuat baru, jika sudah ada, akan ditimpa dengan data baru.
    OrderItem* temp = list->head; // Membuat pointer sementara untuk menelusuri daftar pesanan, mulai dari head.

    while (temp != NULL) { // Loop untuk menulis setiap item pesanan dalam daftar ke file, terus menelusuri daftar hingga mencapai akhir (temp menjadi NULL).
        file << temp->namaPelanggan << "|"
             << temp->namaMenu << "|"
             << temp->jumlah << "|"
             << temp->total << "\n";
        temp = temp->next;
    }

    file.close(); // Menutup file setelah selesai menulis data pesanan untuk memastikan data tersimpan dengan benar dan membebaskan sumber daya yang digunakan oleh file.
}

void tampilkanLaporan(OrderList* list) {// Fungsi untuk menampilkan laporan penjualan, termasuk total pesanan, total pendapatan, dan daftar pesanan yang telah dibuat, memberikan gambaran tentang kinerja penjualan warung ayam geprek.
    cout << "\n===== LAPORAN PENJUALAN =====\n";
    cout << "Total Pesanan   : " << list->jumlah << "\n";
    cout << "Total Pendapatan: Rp " << list->totalPendapatan << "\n";

    cout << "\nDaftar Pesanan:\n";
    OrderItem* temp = list->head;

    while (temp != NULL) { // Loop untuk menampilkan setiap pesanan dalam daftar, terus menelusuri daftar hingga mencapai akhir (temp menjadi NULL).
        cout << temp->namaMenu << " - " << temp->jumlah << " porsi\n";
        temp = temp->next;
    }

    cout << "=============================\n";
}

void tampilkanHeader() { // Fungsi untuk menampilkan header utama aplikasi, memberikan identitas dan informasi tentang warung ayam geprek, menciptakan suasana yang menarik bagi pengguna saat membuka aplikasi.
    cout << "\n================================\n";
    cout << " WARUNG AYAM GEPREK PAK GONDES\n";
    cout << "================================\n";
}

void menuAdmin(MenuList* menu, OrderList* pesanan) { // Fungsi untuk menampilkan menu admin, memungkinkan admin untuk melihat, menambah, menghapus, mencari, dan mengurutkan menu, serta melihat laporan penjualan, memberikan kontrol penuh kepada admin untuk mengelola menu dan memantau kinerja penjualan warung ayam geprek.
    int pilihan;
    bool kembali = false;

    while (!kembali) { // Loop untuk menampilkan menu admin dan menangani pilihan yang dibuat oleh admin, terus menampilkan menu hingga admin memilih untuk kembali ke menu utama.
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

        if (pilihan == 1) { // Jika admin memilih untuk melihat menu, panggil fungsi tampilkanMenu untuk menampilkan daftar menu yang tersedia.
            tampilkanMenu(menu);
        }
        else if (pilihan == 2) { // Jika admin memilih untuk menambah menu, minta input nama dan harga menu baru, validasi harga, dan jika valid, tambahkan menu baru ke daftar menu menggunakan fungsi tambahMenu.
            string nama;
            int harga;

            cin.ignore(1000, '\n'); // Mengabaikan sisa input yang mungkin ada sebelum membaca nama menu baru, untuk memastikan input nama menu baru dimulai dengan benar.
            cout << "Nama menu: ";
            getline(cin, nama);
            cout << "Berapa harganya? ";
            harga = bacaAngka("harga");

            if (cekHarga(harga)) { // Memeriksa apakah harga yang dimasukkan valid (lebih dari 0), jika valid, tambahkan menu baru ke daftar menu menggunakan fungsi tambahMenu.
                tambahMenu(menu, nama, harga);
                cout << "Menu berhasil ditambahkan.\n";
            }
        }
        else if (pilihan == 3) { // Jika admin memilih untuk menghapus menu, tampilkan daftar menu, minta input ID menu yang ingin dihapus, dan jika menu dengan ID tersebut ditemukan, hapus menu dari daftar menu menggunakan fungsi hapusMenu.
            tampilkanMenu(menu);
            cout << "Silakan pilih menu yang ingin dihapus dengan memasukkan ID menu di atas: ";
            int id = bacaAngka("ID menu");
            if (hapusMenu(menu, id)) { // Memeriksa apakah menu dengan ID yang diberikan berhasil dihapus, jika berhasil, tampilkan pesan bahwa menu berhasil dihapus.
                cout << "Menu berhasil dihapus.\n";
            } else { // Jika menu dengan ID yang diberikan tidak ditemukan, tampilkan pesan bahwa menu tidak ditemukan.
                cout << "Menu tidak ditemukan.\n";
            }
        }
        else if (pilihan == 4) { // Jika admin memilih untuk mencari menu, minta input kata kunci untuk pencarian, dan panggil fungsi cariMenu untuk menampilkan hasil pencarian menu yang nama-nya mengandung kata kunci tersebut.
            string keyword;
            cin.ignore(1000, '\n');
            cout << "Cari menu: ";
            getline(cin, keyword);
            cariMenu(menu, keyword);
        }
        else if (pilihan == 5) { // Jika admin memilih untuk mengurutkan menu, panggil fungsi urutkanMenu untuk mengurutkan daftar menu berdasarkan harga, dan setelah diurutkan, tampilkan pesan bahwa menu sudah diurutkan dan tampilkan daftar menu yang sudah diurutkan.
            urutkanMenu(menu);
            cout << "Menu sudah diurutkan.\n";
            tampilkanMenu(menu);
        }
        else if (pilihan == 6) { // Jika admin memilih untuk melihat laporan, panggil fungsi tampilkanLaporan untuk menampilkan laporan penjualan yang mencakup total pesanan, total pendapatan, dan daftar pesanan yang telah dibuat.
            tampilkanLaporan(pesanan);
        }
        else if (pilihan == 7) { // Jika admin memilih untuk kembali ke menu utama, set variabel kembali menjadi true untuk keluar dari loop dan kembali ke menu utama.
            kembali = true;
        }
        else {
            cout << "Pilihan tidak valid.\n";
        }
    }
}

void menuKasir(MenuList* menu, OrderList* pesanan) { // Fungsi untuk menampilkan menu kasir, memungkinkan kasir untuk melihat menu, membuat pesanan, dan melihat daftar pesanan yang telah dibuat, memberikan kemudahan bagi kasir untuk melayani pelanggan dan mengelola pesanan dengan efisien.
    int pilihan;
    bool kembali = false;

    while (!kembali) { // Loop untuk menampilkan menu kasir dan menangani pilihan yang dibuat oleh kasir, terus menampilkan menu hingga kasir memilih untuk kembali ke menu utama.
        cout << "\n--- MENU KASIR ---\n";
        cout << "1. Lihat Menu\n";
        cout << "2. Buat Pesanan\n";
        cout << "3. Lihat Pesanan\n";
        cout << "4. Kembali\n";
        cout << "Pilihan: ";
        pilihan = bacaAngka("menu kasir");

        if (pilihan == 1) { // Jika kasir memilih untuk melihat menu, panggil fungsi tampilkanMenu untuk menampilkan daftar menu yang tersedia.
            tampilkanMenu(menu);
        }
        else if (pilihan == 2) { // Jika kasir memilih untuk membuat pesanan, minta input nama pelanggan, validasi nama, tampilkan daftar menu, minta input ID menu yang ingin dipesan dan jumlah yang ingin dipesan, validasi jumlah, cari menu berdasarkan ID yang diberikan, jika menu ditemukan, hitung total harga, buat pesanan baru dengan informasi yang diberikan, dan cetak struk pesanan.
            string nama;
            int idMenu, jumlah;

            cin.ignore(1000, '\n');
            cout << "Nama pelanggan: ";
            getline(cin, nama);

            if (!cekNama(nama)) { // Memeriksa apakah nama pelanggan yang dimasukkan valid (tidak kosong dan memiliki panjang minimal 2 karakter), jika tidak valid, tampilkan pesan kesalahan dan kembali ke menu kasir tanpa membuat pesanan.
                continue;
            }

            tampilkanMenu(menu); // Menampilkan daftar menu yang tersedia untuk membantu kasir memilih menu yang ingin dipesan oleh pelanggan.
            cout << "Silakan pilih menu yang ingin Anda pesan dengan memasukkan ID menu di atas: ";
            idMenu = bacaAngka("ID menu");
            cout << "Berapa banyak yang ingin Anda pesan? ";
            jumlah = bacaAngka("jumlah");

            if (!cekJumlah(jumlah)) { // Memeriksa apakah jumlah yang dimasukkan valid (lebih dari 0), jika tidak valid, tampilkan pesan kesalahan dan kembali ke menu kasir tanpa membuat pesanan.
                continue;
            }

            MenuItem* item = cariMenuById(menu, idMenu); // Mencari item menu berdasarkan ID yang diberikan oleh kasir, jika menu dengan ID tersebut ditemukan, lanjutkan untuk membuat pesanan, jika tidak ditemukan, tampilkan pesan bahwa menu tidak ditemukan.
            if (item != NULL) { // Jika menu dengan ID yang diberikan ditemukan, hitung total harga berdasarkan harga menu dan jumlah yang dipesan, buat pesanan baru dengan informasi pelanggan, nama menu, jumlah, dan total harga, serta cetak struk pesanan untuk pelanggan.
                int total = hitungTotal(item->harga, jumlah);
                buatPesanan(pesanan, nama, item->nama, jumlah, total);
                cetakStruk(nama, item->nama, jumlah, total);
            } else { // Jika menu dengan ID yang diberikan tidak ditemukan, tampilkan pesan bahwa menu tidak ditemukan.
                cout << "Menu tidak ditemukan.\n";
            }
        }
        else if (pilihan == 3) { // Jika kasir memilih untuk melihat pesanan, panggil fungsi tampilkanPesanan untuk menampilkan daftar pesanan yang telah dibuat oleh pelanggan, memberikan informasi tentang pesanan yang sedang dalam antrian untuk diproses.
            tampilkanPesanan(pesanan);
        }
        else if (pilihan == 4) { // Jika kasir memilih untuk kembali ke menu utama, set variabel kembali menjadi true untuk keluar dari loop dan kembali ke menu utama.
            kembali = true;
        }
        else { // Jika kasir memilih opsi yang tidak valid, tampilkan pesan bahwa pilihan tidak valid.
            cout << "Pilihan tidak valid.\n";
        }
    }
}

void menuUtama(MenuList* menu, OrderList* pesanan) { // Fungsi untuk menampilkan menu utama aplikasi, memungkinkan pengguna untuk login sebagai admin atau kasir, atau keluar dari aplikasi, memberikan akses awal bagi pengguna untuk memilih peran mereka dan mengakses fitur yang sesuai berdasarkan peran yang dipilih.
    int pilihan;
    bool jalan = true;

    while (jalan) { // Loop untuk menampilkan menu utama dan menangani pilihan yang dibuat oleh pengguna, terus menampilkan menu utama hingga pengguna memilih untuk keluar dari aplikasi.
        tampilkanHeader();
        cout << "1. Login\n";
        cout << "2. Keluar\n";
        cout << "Pilihan: ";
        pilihan = bacaAngka("menu utama");

        if (pilihan == 1) { // Jika pengguna memilih untuk login, minta input username dan password, periksa kredensial login menggunakan fungsi login, jika login berhasil sebagai admin, tampilkan menu admin, jika login berhasil sebagai kasir, tampilkan menu kasir, jika login gagal, tampilkan pesan bahwa login gagal.
            string username, password;
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            int role = login(username, password); // Memeriksa kredensial login dan mendapatkan peran pengguna berdasarkan username dan password yang dimasukkan, jika login berhasil, role akan bernilai 1 untuk admin atau 2 untuk kasir, jika login gagal, role akan bernilai 0.

            if (role == 1) { // Jika login berhasil sebagai admin, tampilkan pesan bahwa login admin berhasil dan panggil fungsi menuAdmin untuk menampilkan menu admin.    
                cout << "Login admin berhasil.\n"; // Menampilkan pesan bahwa login admin berhasil.
                menuAdmin(menu, pesanan); // Memanggil fungsi menuAdmin untuk menampilkan menu admin, memberikan akses kepada pengguna yang login sebagai admin untuk mengelola menu dan melihat laporan penjualan.
            }
            else if (role == 2) { // Jika login berhasil sebagai kasir, tampilkan pesan bahwa login kasir berhasil dan panggil fungsi menuKasir untuk menampilkan menu kasir.
                cout << "Login kasir berhasil.\n"; // Menampilkan pesan bahwa login kasir berhasil.
                menuKasir(menu, pesanan); // Memanggil fungsi menuKasir untuk menampilkan menu kasir, memberikan akses kepada pengguna yang login sebagai kasir untuk membuat pesanan dan melihat daftar pesanan.
            }
            else { // Jika login gagal (role bernilai 0), tampilkan pesan bahwa login gagal.
                cout << "Login gagal.\n";
            }
        }
        else if (pilihan == 2) { // Jika pengguna memilih untuk keluar dari aplikasi, simpan data menu dan pesanan ke file menggunakan fungsi simpanMenu dan simpanPesanan, tampilkan pesan bahwa program selesai dan data tersimpan, serta set variabel jalan menjadi false untuk keluar dari loop dan mengakhiri aplikasi.
            simpanMenu(menu); // Menyimpan data menu ke file sebelum keluar dari aplikasi untuk memastikan perubahan pada menu tersimpan dengan benar.
            simpanPesanan(pesanan); // Menyimpan data pesanan ke file sebelum keluar dari aplikasi untuk memastikan semua pesanan yang dibuat selama sesi ini tersimpan dengan benar.
            cout << "Program selesai. Data tersimpan.\n";
            jalan = false;
        }
        else { // Jika pengguna memilih opsi yang tidak valid, tampilkan pesan bahwa pilihan tidak valid.
            cout << "Pilihan tidak valid.\n";
        }
    }
}

void hapusSemuaMenu(MenuList* list) { // Fungsi untuk menghapus semua item menu dari daftar menu, menelusuri daftar menu dan menghapus setiap item menu dari memori untuk membersihkan daftar menu sebelum keluar dari aplikasi.
    MenuItem* temp = list->head;

    while (temp != NULL) { // Loop untuk menghapus setiap item menu dalam daftar, terus menelusuri daftar hingga mencapai akhir (temp menjadi NULL), dan menghapus setiap item menu dari memori untuk mencegah kebocoran memori.
        MenuItem* hapus = temp; // Membuat pointer untuk menyimpan item menu yang akan dihapus saat menelusuri daftar.
        temp = temp->next;
        delete hapus;
    }
}

void hapusSemuaPesanan(OrderList* list) { // Fungsi untuk menghapus semua item pesanan dari daftar pesanan, menelusuri daftar pesanan dan menghapus setiap item pesanan dari memori untuk membersihkan daftar pesanan sebelum keluar dari aplikasi.
    OrderItem* temp = list->head;

    while (temp != NULL) { // Loop untuk menghapus setiap item pesanan dalam daftar, terus menelusuri daftar hingga mencapai akhir (temp menjadi NULL), dan menghapus setiap item pesanan dari memori untuk mencegah kebocoran memori.
        OrderItem* hapus = temp;
        temp = temp->next;
        delete hapus;
    }
}

int main() { // Fungsi utama untuk menjalankan aplikasi, menginisialisasi daftar menu dan pesanan, mem
    MenuList* menu = new MenuList(); // Membuat daftar menu baru dengan alokasi memori dinamis.
    OrderList* pesanan = new OrderList(); // Membuat daftar pesanan baru dengan alokasi memori dinamis.

    menu->head = NULL;
    menu->jumlah = 0;

    pesanan->head = NULL; // Menginisialisasi head dari daftar pesanan ke NULL, menandakan bahwa daftar pesanan saat ini kosong sebelum memuat data dari file.
    pesanan->jumlah = 0; // Menginisialisasi jumlah pesanan dalam daftar ke 0, menandakan bahwa belum ada pesanan yang dimuat dari file.
    pesanan->totalPendapatan = 0; // Menginisialisasi total pendapatan

    muatMenu(menu);
    muatPesanan(pesanan); // Memuat data menu dan pesanan dari file untuk memastikan aplikasi memiliki data yang diperlukan untuk menjalankan fitur-fitur yang tersedia, serta memastikan bahwa data yang sudah ada sebelumnya tetap terjaga saat aplikasi dijalankan kembali.

    if (menu->head == NULL) { // Jika daftar menu kosong setelah mencoba memuat data dari file, isi daftar menu dengan data awal menggunakan fungsi isiMenuAwal, dan simpan menu yang sudah diisi ke file menggunakan fungsi simpanMenu untuk memastikan data menu awal tersimpan dengan benar.
        isiMenuAwal(menu); // Mengisi daftar menu dengan data awal jika file menu tidak ditemukan atau kosong, memberikan beberapa item menu default untuk memulai aplikasi dengan menu yang sudah tersedia.
        simpanMenu(menu); // Menyimpan data menu ke file setelah mengisi daftar menu dengan data awal untuk memastikan bahwa data menu awal tersimpan dengan benar dan dapat dimuat kembali saat aplikasi dijalankan kembali.
    }

    menuUtama(menu, pesanan); // Memanggil fungsi menuUtama untuk menampilkan menu utama aplikasi dan memulai interaksi dengan pengguna, memberikan akses kepada pengguna untuk login sebagai admin atau kasir dan menggunakan fitur-fitur yang tersedia dalam aplikasi.

    hapusSemuaMenu(menu); // Memanggil fungsi hapusSemuaMenu untuk membersihkan daftar menu dari memori sebelum keluar dari aplikasi, memastikan bahwa semua item menu yang dialokasikan secara dinamis dihapus dengan benar untuk mencegah kebocoran memori.
    hapusSemuaPesanan(pesanan); // Memanggil fungsi hapusSemuaPesanan untuk membersihkan daftar pesanan dari memori sebelum keluar dari aplikasi, memastikan bahwa semua item pesanan yang dialokasikan secara dinamis dihapus dengan benar untuk mencegah kebocoran memori.

    delete menu; // Menghapus daftar menu dari memori setelah membersihkan semua item menu untuk memastikan bahwa memori yang digunakan oleh daftar menu juga dibebaskan dengan benar.
    delete pesanan; // Menghapus daftar pesanan dari memori setelah membersihkan semua item pesanan untuk memastikan bahwa memori yang digunakan oleh daftar pesanan juga dibebaskan dengan benar.

    return 0; // Mengembalikan nilai 0 untuk menunjukkan bahwa program selesai dengan sukses.
}
