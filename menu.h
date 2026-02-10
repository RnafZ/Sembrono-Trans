#ifndef MENU_H
#define MENU_H

#include "function.h"
#include "ticketing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menuUtama();
void menuPesanTiket();
void menuCariPesanan();
kelasBus pilihKelas();
void pilihAsal(char *asal);
void pilihTujuan(char *tujuan);

#endif