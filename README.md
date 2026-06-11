# 🍗 Aplikasi Manajemen Warung Ayam Geprek Pak Gondes

Aplikasi berbasis *Command Line Interface* (CLI) ini dirancang untuk mendigitalisasi proses manajemen menu dan transaksi kasir di Warung Ayam Geprek Pak Gondes. Program ini menggunakan konsep struktur data dinamis **Singly Linked List** di C++ untuk mengelola data menu dan pesanan, serta mengimplementasikan **File Handling** untuk penyimpanan data yang persisten.

---

## 👥 Anggota Kelompok (Developer)
Proyek ini dikerjakan secara berkelompok oleh 5 orang:
1. **Kelvin** 
2. **Kelvin Franseco**
3. **Bagas**
4. **Sello**
5. **Vincent**

---

## 🚀 Fitur Utama

Aplikasi ini mendukung sistem multi-user dengan hak akses terpisah menggunakan fitur **Login**:

### 👨‍💼 Fitur Admin (Username: `admin` | Password: `admin123`)
* **Lihat Menu**: Menampilkan seluruh menu yang tersedia beserta ID dan harganya.
* **Tambah Menu**: Menambahkan menu baru ke dalam sistem secara dinamis.
* **Hapus Menu**: Menghapus menu dari daftar berdasarkan ID tertentu.
* **Cari Menu**: Menemukan menu dengan cepat menggunakan kata kunci (*substring matching*).
* **Urutkan Menu**: Mengurutkan harga menu dari yang termurah menggunakan algoritma *Bubble Sort*.
* **Lihat Laporan Penjualan**: Menampilkan total porsi yang terjual, riwayat pesanan, dan total pendapatan warung.

### 👩‍💼 Fitur Kasir (Username: `kasir` | Password: `kasir123`)
* **Lihat Menu**: Membaca menu sebelum melayani pesanan pelanggan.
* **Buat Pesanan**: Menginput pesanan pelanggan, menghitung total biaya otomatis, dan langsung mencetak struk belanja di layar.
* **Lihat Antrian Pesanan**: Memantau daftar antrian pesanan yang masuk.

### 💾 Sistem Otomatisasi & Persistensi Data
* **Auto-Load Data**: Program otomatis membaca file `data/menu.txt` dan `data/pesanan.txt` saat dijalankan.
* **Initial Menu Data**: Jika file data kosong/tidak ditemukan, program otomatis mengisi menu awal (*default*) seperti Ayam Geprek Original, Mozzarella, Sambal Matah, Es Teh, dan Es Jeruk.
* **Auto-Save Data**: Semua perubahan menu dan transaksi baru akan otomatis tersimpan kembali ke file text saat memilih opsi keluar dari program.
* **Memory Cleanup**: Program dilengkapi fungsi untuk menghapus seluruh *node linked list* dari memori (`delete`) guna mencegah terjadinya *memory leak*.

---

## 🛠️ Konsep Struktur Data yang Digunakan

1. **Singly Linked List**: Digunakan untuk menyimpan daftar objek `MenuItem` dan `OrderItem`. Memungkinkan penambahan dan penghapusan data secara dinamis tanpa batasan ukuran tetap (array).
2. **Struct Pointer**: Menggunakan struktur data bertingkat (`MenuList` dan `OrderList`) yang menyimpan pointer ke `head` untuk mempermudah pelacakan elemen pertama dan jumlah data.
3. **Data Validation**: Validasi input bawaan (`cin.fail()`) untuk mencegah *infinite loop* atau *crash* jika pengguna salah memasukkan tipe data (misal: menginput huruf pada menu angka).

---