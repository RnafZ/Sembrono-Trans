#ifndef FUNCTION_H
#define FUNCTION_H

#include "ticketing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

arahBus tentukanArahBus(char *asal, char *tujuan);
void tentukanJam(char *asal, char *tujuan, char jam_berangkat[3][6], char jam_tiba[3][6]);
void tentukanStatusKursi(FILE *file_kelas, int kursi[36], int arah, int jam);
void tampilkanKursi(Tiket *tiket, int kursi[36]);
int cekSisaKursi(Tiket *tiket, int kursi[36], int jumlah_kursi);
void perbaruiFileSeat(FILE *file_kelas, Tiket *tiket, int kursi[36], int arah, int jam);
void tulisTiket(Tiket *tiket);
void generateKode(char kode[6]);
void kursiArrayToString(char kursi[][5], int jumlah, char *hasil);
int cariPesanan(char kode[6], Tiket *tiket);

#endif