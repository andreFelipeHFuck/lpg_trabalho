#include "init.h"
#include "funcoes.c"

int main(){
    int opt;

    // Pegando o dia, mes e ano do computador
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);

    Agenda *agenda = iniciarAgenda();
    Data dataAtual;

    dataAtual.dia = tm.tm_mday;
    dataAtual.mes = tm.tm_mon + 1;
    dataAtual.ano = tm.tm_year + 1900;
   
    do{
        menu(&opt);
        switch (opt)
        {
        case 1:
            insereEvento(agenda, dataAtual);
            ordenarPorData(agenda);
            break;
        
        case 2:
            mostrarEventos(agenda);
            break;

        case 3:
            mostrarEventosPorData(agenda);
            break;

        case 4:
            mostrarEventosCincoProximos(agenda, dataAtual);
            break;    

        case 5:
            removerEvento(agenda);
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