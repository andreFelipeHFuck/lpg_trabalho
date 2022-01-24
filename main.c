#include "init.h"
#include "funcoes.c"

int main(){
    //Evento *eventos;
    int opt;

    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);

    Agenda *agenda = iniciarAgenda();
    Data data;

    data.dia = tm.tm_mday;
    data.mes = tm.tm_mon + 1;
    data.ano = tm.tm_year + 1900;
   
    do{
        menu(&opt);
        switch (opt)
        {
        case 1:
            insereEvento(agenda, data);
            escreverArquivo(agenda);
            break;
        
        case 2:
            mostrarEventos(agenda);
            break;

        case 3:
            mostrarEventosPorData(agenda);
            break;

        case 4:
            mostrarEventosCincoProximos(agenda, data);
            break;    

        case 5:
            excluirEvento(agenda);
            escreverArquivo(agenda);
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