#include "menu.h"

int menuUtama() {
    int pilihan;

    while (1) {
        puts("\n===========================================");
        puts("    Selamat Datang di PO Sembrono Trans      ");
        puts("===========================================\n");

        puts("PO Sembrono Trans merupakan sebuah perusahaan otobus antar kota antar provinsi (AKAP)");
        puts("jurusan Jakarta-Malang PP yang siap melayani dan mengantarkan anda ke berbagai tujuan.\n");

        puts("Jakarta, Bekasi, Cikarang, Karawang, Cikampek, Semarang, Solo, Ngawi, Mojokerto, Malang\n");

        puts("1. Pesan Tiket");
        puts("2. Cari Pesanan");
        puts("0. Exit");

        printf("Pilihanmu: ");
        scanf("%d", &pilihan);
        getchar();

        if (pilihan >= 0 && pilihan <= 2) {
            return pilihan;
        }
        else {
            puts("Input tidak valid!");
        }
    }
}

void menuPesanTiket() {
    Tiket *tiket = malloc(sizeof(Tiket));
    int jumlah_kursi;

    puts("\n=== Silahkan isi data dibawah ===");
    printf("Nama pemesan: ");
    fgets(tiket->nama_pemesan, 30, stdin);
    tiket->nama_pemesan[strcspn(tiket->nama_pemesan, "\n")] = '\0';

    printf("Jumlah kursi yang ingin dipesan: ");
    scanf("%d", &jumlah_kursi);

    while (1) {
        pilihAsal(tiket->asal);
        pilihTujuan(tiket->tujuan);

        if (strcmp(tiket->asal, tiket->tujuan) != 0) {
            break;
        }
        puts("Kota asal dan tujuan tidak boleh sama!");
    };

    switch (pilihKelas()) {
    case Executive:
        pesanTiketExecutive(tiket, jumlah_kursi);
        break;

    case Suite:
        pesanTiketSuite(tiket, jumlah_kursi);
        break;

    case -1:
        puts("Mengembalikan ke Menu Utama");
        free(tiket);
        return;
    }

    puts("Pemesanan berhasil! Mohon simpan tiket dengan baik.");
    lihatTiket(tiket);
    free(tiket);
}

void menuCariPesanan() {
    Tiket *tiket = malloc(sizeof(Tiket));
    char kode[6];

    printf("Masukkan kode pesananmu: ");
    scanf("%s", kode);

    if (cariPesanan(kode, tiket)) {
        puts("Tiket ditemukan!");
        lihatTiket(tiket);
    }
    else {
        puts("Tiket tidak ditemukan!");
    }

    free(tiket);
}

kelasBus pilihKelas() {
    int pilihan;

    while (1) {
        puts("\n=== Pilih Kelas ===");
        puts("1. Executive");
        puts("2. Suite");
        puts("0. Kembali ke Menu Utama");
        printf("Pilihanmu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                return Executive;

            case 2:
                return Suite;

            case 0:
                return -1;

            default:
                puts("Input tidak valid!");
                break;
        }
    }
}

void pilihAsal(char *asal) {
    int pilihan;

    while (1) {
        puts("\n=== Pilih Asal Keberangkatan ===");
        for (int i = 0; i < 10; i++) {
            printf("%d. %s\n", i+1, jurusan[i]);
        }
        printf("Pilihanmu: ");
        scanf("%d", &pilihan);

        for (int i = 0; i < 10; i++) {
            if (pilihan-1 == i) {
                strcpy(asal, jurusan[i]);
                return;
            }
        }
        puts("Input tidak valid!");
    }
}

void pilihTujuan(char *tujuan) {
    int pilihan;

    while (1) {
        puts("\n=== Pilih Tujuan ===");
        for (int i = 0; i < 10; i++) {
            printf("%d. %s\n", i+1, jurusan[i]);
        }
        printf("Pilihanmu: ");
        scanf("%d", &pilihan);

        for (int i = 0; i < 10; i++) {
            if (pilihan-1 == i) {
                strcpy(tujuan, jurusan[i]);
                return;
            }
        }
        puts("Input tidak valid!");
    }

}
