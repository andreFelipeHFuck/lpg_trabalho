#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include <time.h>

typedef struct
{
    int dia, mes, ano;
}Data;

typedef struct
{
    int hora, minuto;
}Hora;

typedef struct 
{
    Data data;
    Hora inicio, fim;
    char local[100];
    char descricao[1000];
}Evento;

typedef struct 
{
    int n_eventos;
    Evento *eventos;
}Agenda;

