#ifndef TICKETING_H
#define TICKETING_H

#include <stdio.h>
#include <string.h>

typedef struct {
    char kode[6];
    char nama_pemesan[30];
    char asal[15];
    char tujuan[15];
    char waktu_perjalanan[16];
    char kelas[10];
    char nomor_kursi[30];
} Tiket;

typedef enum {
    Executive,
    Suite
} kelasBus;

typedef enum {
    Timur,
    Barat
} arahBus;

extern char jurusan[10][10];

extern char waktu_timur1[10][6];
extern char waktu_timur2[10][6];
extern char waktu_timur3[10][6];

extern char waktu_barat1[10][6];
extern char waktu_barat2[10][6];
extern char waktu_barat3[10][6];

extern char nomor_kursi_executive[36][3];
extern char nomor_kursi_suite[22][5];

void pesanTiketExecutive(Tiket *tiket_executive, int jumlah_kursi);
void pesanTiketSuite(Tiket *tiket_suite, int jumlah_kursi);
int pilihJam(char *asal, char *tujuan, char *waktu_perjalanan);
void pilihKursi(FILE *file_kelas, Tiket *tiket, int jam, int arah, int jumlah_kursi);
void lihatTiket(Tiket *tiket);

#endif