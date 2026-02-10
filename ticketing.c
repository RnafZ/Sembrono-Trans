#include "function.h"
#include "ticketing.h"

char jurusan[10][10] = {
    "Jakarta",
    "Bekasi",
    "Cikarang",
    "Karawang",
    "Cikampek",
    "Semarang",
    "Solo",
    "Ngawi",
    "Mojokerto",
    "Malang"
};

char waktu_timur1[10][6] = {
    "06.30", //Jakarta
    "07.00", //Bekasi
    "07.30", //Cikarang
    "08.00", //Karawang
    "08.30", //Cikampek
    "13.45", //Semarang
    "15.15", //Solo
    "16.30", //Ngawi
    "18.20", //Mojokerto
    "20.20"  //Malang
};

char waktu_timur2[10][6] = {
    "12.30", //Jakarta
    "13.00", //Bekasi
    "13.30", //Cikarang
    "14.00", //Karawang
    "14.30", //Cikampek
    "19.45", //Semarang
    "21.15", //Solo
    "22.30", //Ngawi
    "00.20", //Mojokerto
    "02.20"  //Malang
};

char waktu_timur3[10][6] = {
    "18.30", //Jakarta
    "19.00", //Bekasi
    "19.30", //Cikarang
    "20.00", //Karawang
    "20.30", //Cikampek
    "01.45", //Semarang
    "03.15", //Solo
    "04.30", //Ngawi
    "06.20", //Mojokerto
    "08.20"  //Malang
};

char waktu_barat1[10][6] = {
    "06.30", //Malang
    "08.30", //Mojokerto
    "10.20", //Ngawi
    "11.35", //Solo
    "13.05", //Semarang
    "18.20", //Cikampek
    "18.50", //Karawang
    "19.20", //Cikarang
    "19.50", //Bekasi
    "20.20"  //Jakarta
};

char waktu_barat2[10][6] = {
    "12.30", //Malang
    "14.30", //Mojokerto
    "16.20", //Ngawi
    "17.35", //Solo
    "19.05", //Semarang
    "00.20", //Cikampek
    "00.50", //Karawang
    "01.20", //Cikarang
    "01.50", //Bekasi
    "02.20"  //Jakarta
};

char waktu_barat3[10][6] = {
    "18.30", //Malang
    "20.30", //Mojokerto
    "22.20", //Ngawi
    "23.35", //Solo
    "01.05", //Semarang
    "06.20", //Cikampek
    "06.50", //Karawang
    "07.20", //Cikarang
    "07.50", //Bekasi
    "08.20"  //Jakarta
};

char nomor_kursi_executive[36][3] = {
    "1A", "2A", "3A", "4A", "5A", "6A", "7A", "8A", "9A",
    "1B", "2B", "3B", "4B", "5B", "6B", "7B", "8B", "9B",

    "1C", "2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C",
    "1D", "2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D"
};

char nomor_kursi_suite[22][5] = {
    //Lt 1
    "SB2", "SB4", "SB6", "SB8", "SB10", "SB12",

    "SB1", "SB3", "SB5", "SB7", "SB9", "SB11",

    //Lt 2
    "SA2", "SA4", "SA6", "SA8", "SA10",

    "SA1", "SA3", "SA5", "SA7", "SA9"
};

int kursi[36];

void pesanTiketExecutive(Tiket *tiket_executive, int jumlah_kursi) {
    FILE *file_executive = fopen("seat_executive.txt", "r+");

    if (!file_executive) {
        puts("Gagal membuka file!");
        return;
    }

    strcpy(tiket_executive->kelas, "Executive");

    int jam = pilihJam(tiket_executive->asal, tiket_executive->tujuan, tiket_executive->waktu_perjalanan);
    int arah = tentukanArahBus(tiket_executive->asal, tiket_executive->tujuan);

    pilihKursi(file_executive, tiket_executive, jam, arah, jumlah_kursi);

    perbaruiFileSeat(file_executive, tiket_executive, kursi, arah, jam);

    tulisTiket(tiket_executive);
    
    fclose(file_executive);
}

void pesanTiketSuite(Tiket *tiket_suite, int jumlah_kursi) {
    FILE *file_suite = fopen("seat_suite.txt", "r+");

    if (!file_suite) {
        puts("Gagal membuka file!");
        return;
    }

    strcpy(tiket_suite->kelas, "Suite");

    int jam = pilihJam(tiket_suite->asal, tiket_suite->tujuan, tiket_suite->waktu_perjalanan);
    int arah = tentukanArahBus(tiket_suite->asal, tiket_suite->tujuan);

    pilihKursi(file_suite, tiket_suite, jam, arah, jumlah_kursi);

    perbaruiFileSeat(file_suite, tiket_suite, kursi, arah, jam);

    tulisTiket(tiket_suite);

    fclose(file_suite);
}

int pilihJam(char *asal, char *tujuan, char *waktu_perjalanan) {
    int pilihan;
    char jam_berangkat[3][6], jam_tiba[3][6];

    tentukanJam(asal, tujuan, jam_berangkat, jam_tiba);

    while (1) {
        puts("\n=== Pilih Jam Keberangkatan ===");
        for (int i = 0; i < 3; i++) {
            printf("%d. Berangkat %s --> %s Tiba\n", i+1, jam_berangkat[i], jam_tiba[i]);
        }
        printf("Pilihanmu: ");
        scanf("%d", &pilihan);

        if (pilihan >= 1 && pilihan <= 3) {
            sprintf(waktu_perjalanan, "%s --> %s", jam_berangkat[pilihan-1], jam_tiba[pilihan-1]);
            return pilihan;
        }
        puts("Input tidak valid!");
    };
}

void pilihKursi(FILE *file_kelas, Tiket *tiket, int jam, int arah, int jumlah_kursi) {
    tentukanStatusKursi(file_kelas, kursi, arah, jam);

    if (cekSisaKursi(tiket, kursi, jumlah_kursi) == 0) {
        puts("Maaf, kursi sudah penuh.");
        return;
    }

    tampilkanKursi(tiket, kursi);

    char input_kursi[5];
    char arr_nomor_kursi[10][5];

    printf("Pilih %d kursi\n", jumlah_kursi);
    for (int i = 0; i < jumlah_kursi; i++) {
        int ketemu = 0;

        printf("Pilihanmu: ");
        scanf("%s", input_kursi);

        if (strcmp(tiket->kelas, "Executive") == 0) {
            for (int j = 0; j < 36; j++) {
                if (strcmp(input_kursi, nomor_kursi_executive[j]) == 0) {
                    if (kursi[j] == 0) {
                        strcpy(arr_nomor_kursi[i], input_kursi);
                        kursi[j] = 1;
                        ketemu = 1;
                    }
                }
            }
        } 
        else {
            for (int j = 0; j < 22; j++) {
                if (strcmp(input_kursi, nomor_kursi_suite[j]) == 0) {
                    if (kursi[j] == 0) {
                        strcpy(arr_nomor_kursi[i], input_kursi);
                        kursi[j] = 1;
                        ketemu = 1;
                    }
                }
            }
        }

        if (!ketemu) {
            puts("Nomor kursi tidak valid!");
            i--;
        }
    }

    kursiArrayToString(arr_nomor_kursi, jumlah_kursi, tiket->nomor_kursi);
}

void lihatTiket(Tiket *tiket) {
    puts  ("===============================");
    printf(" Kode tiket -> %s\n", tiket->kode);
    puts  ("-------------------------------");
    printf(" Nama Pemesan: %s\n", tiket->nama_pemesan);
    printf(" Asal        : %s\n", tiket->asal);
    printf(" Tujuan      : %s\n", tiket->tujuan);
    printf(" Jam         : %s\n", tiket->waktu_perjalanan);
    printf(" Kelas       : %s\n", tiket->kelas);
    printf(" Nomor kursi : %s\n", tiket->nomor_kursi);
    puts  ("===============================");
}