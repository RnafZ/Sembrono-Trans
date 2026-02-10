#include "menu.h"
#include "function.h"
#include "ticketing.h"
#include <stdio.h>

int main() {
    while(1) {
        switch (menuUtama()) {
        case 1:
            menuPesanTiket();
            break;

        case 2:
            menuCariPesanan();
            break;

        case 0:
            puts("Sampai jumpa di perjalanan berikutnya!");
            return 0;
        }
    }
}