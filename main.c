#include "init.h"
#include "funcoes.c"

int main(){
    //Evento *eventos;
    int opt;
    Agenda *agenda = iniciarAgenda();

    do{
        menu(&opt);
        switch (opt)
        {
        case 1:
            insereEvento(agenda);
            break;
        
        case 2:
            mostrarEventos(agenda);
            break;

        case 0:
            escreverArquivo(agenda);
            break;

        default:
            break;
        }
        
    }while(opt != 0);
    free(agenda);
    return 0;
}