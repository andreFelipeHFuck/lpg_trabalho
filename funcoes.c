void menu(int *opt){
    system("clear");
    printf("Agenda de eventos\n");
    printf("1 - Cadastrar evento\n");
    printf("2 - Mostrar todos os eventos da agenda\n");
    printf("3 - Mostrar eventos por data\n");
    printf("4 - Mostrar os 5 proximos eventos do dia\n");
    printf("5 - Remover evento\n");
    printf("0 - Sair\n");
    printf("Opção: ");
    scanf("%d", opt);
}

Agenda* iniciarAgenda(){
    Agenda *agenda = (Agenda*) malloc(sizeof(Agenda));
    FILE *arq = fopen("agenda", "rb");

    if(arq){
        fread(&agenda->n_eventos, sizeof(int), 1, arq);
        agenda->eventos = (Evento *) malloc (agenda->n_eventos * sizeof(Evento));

        if(!agenda->eventos){
            printf("Não fois possivel alocar vetor de eventos\n");
        }else{
            fread(agenda->eventos, sizeof(Evento), agenda->n_eventos, arq);
            fclose(arq);
        }
    }else{
        agenda->n_eventos = 0;
        agenda->eventos = 0;
    }
    return agenda;
}

void escreverArquivo(Agenda *agenda){
    FILE *arq = fopen("agenda", "wb+");

    if(arq == NULL){
        printf("Erro ao abrir o arquivo");
    }else{
        printf("Salvando alterações.");
        fwrite(&agenda->n_eventos, sizeof(int), 1, arq);
        fwrite(agenda->eventos, sizeof(Evento), agenda->n_eventos, arq);
    }
    fclose(arq);
}

void insereEvento(Agenda *agenda){
    system("clear");
    int resp;

    agenda->eventos = (Evento*) realloc(agenda->eventos, (agenda->n_eventos + 1) * sizeof(Evento));

    if(!agenda->eventos){
        printf("Não foi possivel aumentar o vetor de eventos");
    }else{
        // Local e descrição
        printf("Local: ");
        scanf("%s", agenda->eventos[agenda->n_eventos].local);

        printf("Descrição: ");
        scanf("%s", agenda->eventos[agenda->n_eventos].descricao);
        
        // Data
        printf("Data \n");
        printf("Dia: ");
        scanf("%d", &agenda->eventos[agenda->n_eventos].data.dia);
        printf("Mês: ");
        scanf("%d", &agenda->eventos[agenda->n_eventos].data.mes);
        printf("Ano: ");
        scanf("%d", &agenda->eventos[agenda->n_eventos].data.ano);

        // Horário de ínicio
        printf("Horario de ínico\n");
        printf("Hora: ");
        scanf("%d", &agenda->eventos[agenda->n_eventos].inicio.hora);
        printf("Minuto: ");
        scanf("%d", &agenda->eventos[agenda->n_eventos].inicio.minuto);

        // Horário de fim
        printf("Horirio de fim\n");
        printf("Hora: ");
        scanf("%d", &agenda->eventos[agenda->n_eventos].fim.hora);
        printf("Minuto: ");
        scanf("%d", &agenda->eventos[agenda->n_eventos].fim.minuto);

        printf("\n");
        agenda->n_eventos++;
    }

     while (1)
        {
            printf("Deseja registrar um novo evento?\n");
            printf("1 - Sim\n");
            printf("2 - Nao\n");
            scanf("%d", &resp);
            if((resp == 1) || (resp == 2)){
                break;
            }
            
        }
        if(resp == 1){
            insereEvento(agenda);
        }

}

void mostrarEventos(Agenda *agenda){
    system("clear");

    char finalizar[10];
    int i;

    if(agenda->n_eventos == 0){
        printf("Nenhum evento encontrado...\n");
    }else{
        printf("Eventos\n");
        for(i = 0; i < agenda->n_eventos; i++){
            printf("==========================================\n");
            // Local e descrição
            printf("Local: %s\n", agenda->eventos[i].local);
            printf("Descrição: %s\n", agenda->eventos[i].descricao);

            // Data
            printf("Data: %d/%d/%d\n",
                                     agenda->eventos[i].data.dia,
                                     agenda->eventos[i].data.mes,
                                     agenda->eventos[i].data.ano
            );

            //Horário de ínicio e finalização
            printf("Horário de ínicio: %d: %d\n",
                                                agenda->eventos[i].inicio.hora,
                                                agenda->eventos[i].inicio.minuto
            );
            printf("Hórario de final: %d: %d\n",
                                              agenda->eventos[i].fim.hora,
                                              agenda->eventos[i].fim.minuto
            );

            printf("==========================================\n");
        }
    }

    printf("\nAperte qualquer botão para sair: ");
    __fpurge(stdin);
    fgets(finalizar, 10, stdin);
}