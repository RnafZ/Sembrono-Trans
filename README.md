# PO Sembrono Trans - Sistem Pemesanan Tiket Bus

**PO Sembrono Trans** adalah aplikasi berbasis *Command Line Interface* (CLI) yang ditulis dalam bahasa C untuk menangani pemesanan tiket bus Antar Kota Antar Provinsi (AKAP). Sistem ini mensimulasikan operasional bus rute **Jakarta - Malang (PP)** dengan fitur pemilihan kursi, kelas armada, dan manajemen jadwal.

## 📋 Deskripsi Proyek

Aplikasi ini dirancang untuk memudahkan calon penumpang dalam memesan tiket dan petugas dalam mengelola data pesanan. Program ini menggunakan manipulasi file (file handling) untuk menyimpan status kursi dan riwayat pemesanan secara persisten, sehingga data tidak hilang setelah program ditutup.

### Rute yang Dilayani
Program mencakup pemberhentian di kota-kota berikut (berlaku dua arah/PP):
* Jakarta
* Bekasi
* Cikarang
* Karawang
* Cikampek
* Semarang
* Solo
* Ngawi
* Mojokerto
* Malang

## ✨ Fitur Utama

1.  **Pemesanan Tiket (`Pesan Tiket`)**
    * Input data penumpang.
    * Pemilihan kota asal dan tujuan.
    * **Pilihan Kelas Bus:**
        * **Executive:** Konfigurasi kursi standar (Total 36 kursi).
        * **Suite:** Konfigurasi *sleeper* mewah 2 lantai (Total 22 kursi).
    * **Penjadwalan Otomatis:** Menampilkan jam keberangkatan dan tiba yang akurat berdasarkan arah perjalanan (Barat ke Timur atau Timur ke Barat).
    * **Pemilihan Kursi Visual:** Menampilkan denah kursi secara *real-time* (Kosong/Terisi).

2.  **Pencarian Pesanan (`Cari Pesanan`)**
    * Mencari data tiket berdasarkan **Kode Booking** (contoh: `ST001`).
    * Menampilkan detail lengkap tiket jika ditemukan.

3.  **Manajemen Data (File Handling)**
    * Penyimpanan data tiket otomatis ke `tiket.txt`.
    * Update status ketersediaan kursi secara *real-time* di database (`seat_executive.txt` & `seat_suite.txt`).
    * Generator kode tiket unik auto-increment.

## 📂 Struktur File

Program ini terdiri dari beberapa modul untuk memudahkan *maintenance*:

* **Source Code:**
    * `main.c`: Entry point program.
    * `menu.c`: Mengatur antarmuka menu utama dan input user.
    * `ticketing.c`: Definisi data rute, jadwal, dan konfigurasi kursi.
    * `function.c`: Logika utama (arah bus, update file, algoritma kursi).
* **Header Files:**
    * `menu.h`, `ticketing.h`, `function.h`: Deklarasi fungsi dan struktur data.
* **Database (Txt Files):**
    * `tiket.txt`: Log seluruh transaksi tiket.
    * `seat_executive.txt`: Matrix ketersediaan kursi Executive.
    * `seat_suite.txt`: Matrix ketersediaan kursi Suite.
    * `kode.txt`: Counter untuk nomor tiket terakhir.

## 🚀 Cara Menjalankan Program

### Prasyarat
Pastikan Anda memiliki compiler C (seperti GCC) terinstall di komputer Anda.

### Langkah Kompilasi
Buka terminal atau command prompt, arahkan ke direktori proyek, lalu jalankan perintah berikut untuk mengompilasi seluruh file:

```bash
gcc main.c menu.c ticketing.c function.c -o sembrono_trans
