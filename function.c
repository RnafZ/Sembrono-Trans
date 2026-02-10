#include "function.h"

arahBus tentukanArahBus(char *asal, char *tujuan) {
    int index_asal, index_tujuan;

    for (index_asal = 0; index_asal < 10; index_asal++) {
        if (strcmp(asal, jurusan[index_asal]) == 0) {
            break;
        }
    }

    for (index_tujuan = 0; index_tujuan < 10; index_tujuan++) {
        if (strcmp(tujuan, jurusan[index_tujuan]) == 0) {
            break;
        }
    }

    if (index_asal < index_tujuan) {
        return Timur;
    }
    else {
        return Barat;
    }
}

void tentukanJam(char *asal, char *tujuan, char jam_berangkat[3][6], char jam_tiba[3][6]) {
    int index_asal, index_tujuan;

    int arah = tentukanArahBus(asal, tujuan);

    for (index_asal = 0; index_asal < 10; index_asal++) {
        if (strcmp(asal, jurusan[index_asal]) == 0) {
            if (arah == Timur) {
                strcpy(jam_berangkat[0], waktu_timur1[index_asal]);
                strcpy(jam_berangkat[1], waktu_timur2[index_asal]);
                strcpy(jam_berangkat[2], waktu_timur3[index_asal]);
                break;
            }
            else {
                strcpy(jam_berangkat[0], waktu_barat1[9-index_asal]);
                strcpy(jam_berangkat[1], waktu_barat2[9-index_asal]);
                strcpy(jam_berangkat[2], waktu_barat3[9-index_asal]);
                break;
            }
        }
    }

    for (index_tujuan = 0; index_tujuan < 10; index_tujuan++) {
        if (strcmp(tujuan, jurusan[index_tujuan]) == 0) {
            if (arah == Timur) {
                strcpy(jam_tiba[0], waktu_timur1[index_tujuan]);
                strcpy(jam_tiba[1], waktu_timur2[index_tujuan]);
                strcpy(jam_tiba[2], waktu_timur3[index_tujuan]);
                break;
            }
            else {
                strcpy(jam_tiba[0], waktu_barat1[9-index_tujuan]);
                strcpy(jam_tiba[1], waktu_barat2[9-index_tujuan]);
                strcpy(jam_tiba[2], waktu_barat3[9-index_tujuan]);
                break;
            }
        }
    }
}

void tentukanStatusKursi(FILE *file_kelas, int kursi[36], int arah, int jam) {
    char buffer[50];

    if (arah == Timur) {
        for (int i = 0; i < jam; i++) {
            fgets(buffer, 100, file_kelas);
        }
    }
    else {
        for (int i = 0; i < jam+3; i++) {
            fgets(buffer, 100, file_kelas);
        }
    }

    for (int i = 0; buffer[i] != '\0' && buffer[i] != '\n'; i++) {
        kursi[i] = buffer[i] - '0';
    }
}

void tampilkanKursi(Tiket *tiket, int kursi[36]) {
    puts("\n=== Pilih Kursi ===\n");
    if (strcmp(tiket->kelas, "Executive") == 0) {
        for (int i = 0; i < 36; i++) {
            printf(" %-2s{%d]", nomor_kursi_executive[i], kursi[i]);
            if ((i + 1) % 9 == 0) printf("\n");
            if ((i + 1) % 18 == 0) printf("\n");
        }
    }
    else {
        int i;

        puts("Lantai 1:");
        for (i = 0; i < 12; i++) {
            printf(" %-4s[ %d ]", nomor_kursi_suite[i], kursi[i]);
            if ((i + 1) % 6 == 0) puts("\n");
        }
        puts("Lantai 2:");
        for (i; i < 22; i++) {
            printf(" %-4s[ %d ]", nomor_kursi_suite[i], kursi[i]);
            if ((i - 1) % 5 == 0) puts("\n");
        }
    }
    puts("Ket: 0 = kosong, 1 = terisi");
}

int cekSisaKursi(Tiket *tiket, int kursi[36], int jumlah_kursi) {
    int sisa_kursi_kosong = 0;

    if (strcmp(tiket->kelas, "Executive") == 0) {
        for (int i = 0; i < 36; i++) {
            if (kursi[i] == 0) sisa_kursi_kosong++;
        }
    }
    else {
        for (int i = 0; i < 22; i++) {
            if (kursi[i] == 0) sisa_kursi_kosong++;
        }
    }

    if (sisa_kursi_kosong >= jumlah_kursi) {
        return 1;
    }
    else {
        return 0;
    }
}

void perbaruiFileSeat(FILE *file_kelas, Tiket *tiket, int kursi[36], int arah, int jam) {
    char buffer[50];
    char semuaBaris[6][50];

    rewind(file_kelas);

    for (int i = 0; i < 6; i++) {
        fgets(semuaBaris[i], sizeof(semuaBaris[i]), file_kelas);
    }

    int barisTarget = (arah == Timur ? 0 : 3) + (jam - 1);

    if (strcmp(tiket->kelas, "Executive") == 0) {
        for (int i = 0; i < 36; i++) {
            buffer[i] = kursi[i] + '0';
        }
        buffer[36] = '\n';
        buffer[37] = '\0';
    }
    else {
        for (int i = 0; i < 22; i++) {
            buffer[i] = kursi[i] + '0';
        }
        buffer[22] = '\n';
        buffer[23] = '\0';
    }

    strcpy(semuaBaris[barisTarget], buffer);

    rewind(file_kelas);
    for (int i = 0; i < 6; i++) {
        fputs(semuaBaris[i], file_kelas);
    }

    fflush(file_kelas);
}

void tulisTiket(Tiket *tiket) {
    FILE *file_tiket = fopen("tiket.txt", "a");

    if (!file_tiket) {
        puts("Gagal membuka file tiket!");
        return;
    }

    generateKode(tiket->kode);

    fprintf(file_tiket, "%s|%s|%s|%s|%s|%s|%s\n",
        tiket->kode,
        tiket->nama_pemesan,
        tiket->asal,
        tiket->tujuan,
        tiket->waktu_perjalanan,
        tiket->kelas,
        tiket->nomor_kursi
    );
}

void generateKode(char kode[6]) {
    FILE *f = fopen("kode.txt", "r+");
    int nomor = 1;

    fscanf(f, "%d", &nomor);

    sprintf(kode, "ST%03d", nomor);

    rewind(f);
    fprintf(f, "%d", nomor + 1);

    fclose(f);
}

void kursiArrayToString(char kursi[][5], int jumlah, char *hasil) {
    hasil[0] = '\0';

    for (int i = 0; i < jumlah; i++) {
        strcat(hasil, kursi[i]);

        if (i < jumlah - 1) {
            strcat(hasil, ",");
        }
    }
}

int cariPesanan(char kode[6], Tiket *tiket) {
    FILE *file_tiket = fopen("tiket.txt", "r");

    if (!file_tiket) {
        puts("Gagal membuka file!");
        return 0;
    }

    char line[100];
    while (fgets(line, 100, file_tiket)) {
        Tiket cari_tiket;

        line[strcspn(line, "\n")] = '\0';

        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]",
            cari_tiket.kode,
            cari_tiket.nama_pemesan,
            cari_tiket.asal,
            cari_tiket.tujuan,
            cari_tiket.waktu_perjalanan,
            cari_tiket.kelas,
            cari_tiket.nomor_kursi);

        if (strcmp(cari_tiket.kode, kode) == 0) {
            *tiket = cari_tiket;
            fclose(file_tiket);
            return 1;
        }
    }

    fclose(file_tiket);
    return 0;
}