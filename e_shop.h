#ifndef E_SHOP_H
#define E_SHOP_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define TOTAL_ITEMS 20

typedef struct {
    char description[50];
    int posotita;
    float timi;
    int total_orders;
    int poliseis;
    int apotux_parag;
} antikeimeno;


typedef struct {
    antikeimeno antikeimeno[20];
    float esoda;
    int olokl_parag;
    int apotux_parag;
} Katastima;


typedef struct {
    char item_name[50];
    int posotita;
} parag;


void ftiakse_katastima(Katastima *katastima);
int process_order(Katastima *katastima, int i);

#endif 
