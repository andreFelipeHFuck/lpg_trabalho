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

int filtro(int limite, char erro[100], char mensagem[50]){
    int num;
    while (1)
    {
        printf("%s", mensagem);
        scanf("%d", &num);

        if(num > limite || num < 0){
            printf("%s", erro);
        }else{
            break;
        }
    }
    return num;
}

int filtroAno(int limite, char erro[100], char mensagem[50]){
    int num;
    while (1)
    {
        printf("%s", mensagem);
        scanf("%d", &num);

        if(num < limite){
            printf("%s", erro);
        }else{
            break;
        }
    }
    return num;
}

int filtroHorario(int final, int limite, char erro[100], char mensagem[50]){
    int num;
    while (1)
    {
        printf("%s", mensagem);
        scanf("%d", &num);

        if(num <= final){
            printf("%s", erro);
        }else{
            break;
        }
    }
    return num;
}

int opcaoInsereEvento(){
    int resp;
    while(1){
        printf("Deseja registrar um novo evento?\n");
        printf("1 - Sim\n");
        printf("2 - Nao\n");
        scanf("%d", &resp);
        if((resp == 1) || (resp == 2)){
            break;
        }
    }
    return resp;
}

void insereEvento(Agenda *agenda, Data data){
    system("clear");

    int resp, i, cont;
    char local[100];

    agenda->eventos = (Evento*) realloc(agenda->eventos, (agenda->n_eventos + 1) * sizeof(Evento));

    if(!agenda->eventos){
        printf("Não foi possivel aumentar o vetor de eventos");
    }else{
        // Local e descrição

        // Filtro local
        while (1)
        {
            printf("Local: ");
            __fpurge(stdin);
            fgets(local, 100, stdin);

            for(i = 0; i < agenda->n_eventos; i++){
                if(strcmp(agenda->eventos[i].local, local) == 0){
                    printf("Erro! Esse local já possui um evento marcado!\n");
                }else{
                    cont++;
                }
                if(cont > 0){
                    strcpy(agenda->eventos[agenda->n_eventos].local, local);
                    break;
                }
                cont = 0;
            }
        }
        

        printf("Descrição: ");
        __fpurge(stdin);
        fgets(agenda->eventos[agenda->n_eventos].descricao, 500, stdin);
        
        // Data
        printf("Data \n");

        agenda->eventos[agenda->n_eventos].data.dia = filtro(31, "Erro, digite um número de 1 a 31\n", "Dia: ");

        agenda->eventos[agenda->n_eventos].data.mes = filtro(12, "Erro, digite um número de 1 a 12\n", "Mes: ");

        agenda->eventos[agenda->n_eventos].data.ano = filtroAno(data.ano - 1, "Erro, não é possível marcar um evento num ano que já passou.\n", "Ano: ");

        // Horário de ínicio
        printf("Horario de ínico\n");

        agenda->eventos[agenda->n_eventos].inicio.hora = filtro(24, "Erro, digite um número de 0 a 23\n", "Hora: ");
       
        agenda->eventos[agenda->n_eventos].inicio.minuto = filtro(59, "Erro digite um número de 0 a 59\n", "Minuto: ");

        // Horário de fim
        printf("Horirio de fim\n");
      
        agenda->eventos[agenda->n_eventos].fim.hora = filtro(24, "Erro, digite um número de 0 a 23\n", "Hora: ");
       
        agenda->eventos[agenda->n_eventos].fim.minuto = filtroHorario(agenda->eventos[agenda->n_eventos].inicio.hora, 59, "Erro digite um número de 0 a 59\n", "Minuto: ");

        printf("\n");
        agenda->n_eventos++;
    }

    resp = opcaoInsereEvento();

    if(resp == 1){
        insereEvento(agenda, data);
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
            printf("Local: %s", agenda->eventos[i].local);
            printf("Descrição: %s", agenda->eventos[i].descricao);

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

int dataIgual(Data dataEventos, Data dataAtual){
    if(dataEventos.ano == dataAtual.ano && dataEventos.mes == dataAtual.mes && dataEventos.dia == dataAtual.dia){
        return 1;
    }
}

void mostrarEventosPorData(Agenda *agenda){
    system("clear");

    char finalizar[10];
    int i, cont = 0;
    Data data;

    printf("Entre com uma data\n");
    printf("Dia: ");
    data.dia = filtro(31, "Erro, digite um número de 1 a 31\n", "Dia: ");
    printf("Mês: ");
    data.mes = filtro(12, "Erro, digite um número de 1 a 12\n", "Mes: ");
    printf("Ano: ");
    data.ano = filtro(2022, "Erro, não é possível marcar um evento num ano que já passou.", "Ano: ");

    if(agenda->n_eventos == 0){
        printf("Nenhum evento encontrado...\n");
    }else{
        printf("Eventos\n");
        for(i = 0; i < agenda->n_eventos; i++){
            if(dataIgual(agenda->eventos[i].data, data) == 1){
                printf("==========================================\n");
                // Local e descrição
                printf("Local: %s", agenda->eventos[i].local);
                printf("Descrição: %s", agenda->eventos[i].descricao);

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
                cont++;
            }

        }
    }

    if(cont == 0){
        printf("Nenhum evento encontrado...\n");
    }

    printf("\nAperte qualquer botão para sair: ");
    __fpurge(stdin);
    fgets(finalizar, 10, stdin);
}

void mostrarEventosCincoProximos(Agenda *agenda, Data data){
    system("clear");

    char finalizar[10];
    int i, cont = 0;

    if(agenda->n_eventos == 0){
        printf("Nenhum evento encontrado...\n");
    }else{
        printf("5 proximos eventos do dia:\n");
         for(i = 0; i < agenda->n_eventos; i++){
            if(dataIgual(agenda->eventos[i].data, data) == 1 && cont <= 5){
                printf("==========================================\n");
                // Local e descrição
                printf("Local: %s", agenda->eventos[i].local);
                printf("Descrição: %s", agenda->eventos[i].descricao);

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
                cont++;
            }

        }
    }

    if(cont == 0){
        printf("Nenhum evento encontrado...\n");
    }

    printf("\nAperte qualquer botão para sair: ");
    __fpurge(stdin);
    fgets(finalizar, 10, stdin);
    
}

void excluirEvento(Agenda *agenda){
    system("clear");

    int i = 0, conta_excluido = 0;
    char local[100], finalizar[10];

    printf("Entre com o local do evento a ser removido: \n");
    printf("Local: ");
    __fpurge(stdin);
    fgets(local, 100, stdin);

    while(i < agenda->n_eventos){
        if(strcmp(agenda->eventos[i].local, local) == 0){
            conta_excluido++;
            agenda->eventos[i] = agenda->eventos[agenda->n_eventos - 1];
            agenda->eventos = (Evento*) realloc(agenda->eventos, (agenda->n_eventos - 1) * sizeof(Evento));
            agenda->n_eventos--;
            printf("Evento excluido\n");
            break;
        }
        i++;
    }
    
    if(conta_excluido == 0){
        printf("Nenhum contato encontrado\n");
    }

    printf("\nAperte qualquer botão para sair: ");
    __fpurge(stdin);
    fgets(finalizar, 10, stdin);

}

