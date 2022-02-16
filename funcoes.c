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

int dataIgual(Data dataEventos, Data dataAtual){
    if(dataEventos.ano == dataAtual.ano && dataEventos.mes == dataAtual.mes && dataEventos.dia == dataAtual.dia){
        return 1;
    }else{
        return 0;
    }
}

int horarioIgual(Hora horaEvento, Hora inputHora){
    if(horaEvento.hora == inputHora.hora && horaEvento.minuto == inputHora.minuto){
        return 1;
    }else{
        return 0;
    }
}

Agenda* iniciarAgenda(){
    Agenda *agenda = (Agenda*) malloc(sizeof(Agenda));

    if(!agenda){
        printf("Não foi possivel alocar o vetor agenda");
        return 0;
    }else{
        FILE *arq = fopen("agenda", "rb");

        if(arq){
            fread(&agenda->n_eventos, sizeof(int), 1, arq);
            agenda->eventos = (Evento *) malloc (agenda->n_eventos * sizeof(Evento));

            if(!agenda->eventos){
                printf("Não foi possivel alocar vetor de eventos\n");
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

// Bubblesort para ordenar Agenda
void ordenarPorData(Agenda *agenda){
    int i, j;
    Evento aux;
    // Ordenar por horario inicial (minuto)
    for(i = 1; i < agenda->n_eventos; i++){
        for(j = 0; j < agenda->n_eventos - 1; j++){
            if(agenda->eventos[j].inicio.minuto > agenda->eventos[j + 1].inicio.minuto){
                aux = agenda->eventos[j];
                agenda->eventos[j] = agenda->eventos[j + 1];
                agenda->eventos[j + 1] = aux;
            }    
        }
    }

    // Ordenar por horario inical (hora)
    for(i = 1; i < agenda->n_eventos; i++){
        for(j = 0; j < agenda->n_eventos - 1; j++){
            if(agenda->eventos[j].inicio.hora > agenda->eventos[j + 1].inicio.hora){
                aux = agenda->eventos[j];
                agenda->eventos[j] = agenda->eventos[j + 1];
                agenda->eventos[j + 1] = aux;
            }    
        }
    }

    // Ordenar por dia
    for(i = 1; i < agenda->n_eventos; i++){
        for(j = 0; j < agenda->n_eventos - 1; j++){
            if(agenda->eventos[j].data.dia > agenda->eventos[j + 1].data.dia){
                aux = agenda->eventos[j];
                agenda->eventos[j] = agenda->eventos[j + 1];
                agenda->eventos[j + 1] = aux;
            }    
        }
    }

    // Ordenar por mes
    for(i = 1; i < agenda->n_eventos; i++){
        for(j = 0; j < agenda->n_eventos - 1; j++){
            if(agenda->eventos[j].data.mes > agenda->eventos[j + 1].data.mes){
                aux = agenda->eventos[j];
                agenda->eventos[j] = agenda->eventos[j + 1];
                agenda->eventos[j + 1] = aux;
            }    
        }
    }

    // Ordenar por ano
    for(i = 1; i < agenda->n_eventos; i++){
        for(j = 0; j < agenda->n_eventos - 1; j++){
            if(agenda->eventos[j].data.ano > agenda->eventos[j + 1].data.ano){
                aux = agenda->eventos[j];
                agenda->eventos[j] = agenda->eventos[j + 1];
                agenda->eventos[j + 1] = aux;
            }    
        }
    }

    
    for(i = 0; i < agenda->n_eventos; i++){
        printf("%d/%d/%d hora: %d: %d\n", agenda->eventos[i].data.dia, agenda->eventos[i].data.mes, agenda->eventos[i].data.ano, agenda->eventos[i].inicio.hora, agenda->eventos[i].inicio.minuto);
    }

}

void insereEvento(Agenda *agenda, Data dataAtual){
    system("clear");

    int i, cont;
    Hora inicio;
    Data data;
    char finalizar[10];

    agenda->eventos = (Evento*) realloc(agenda->eventos, (agenda->n_eventos + 1) * sizeof(Evento));

    if(!agenda->eventos){
        printf("Não foi possivel aumentar o vetor de eventos");
    }else{
        // Local e descrição
        printf("Local: ");
         __fpurge(stdin);
        fgets(agenda->eventos[agenda->n_eventos].local, 100, stdin);
        
        printf("Descrição: ");
        __fpurge(stdin);
        fgets(agenda->eventos[agenda->n_eventos].descricao, 1000, stdin);
        
        // Data
        printf("Data \n");

        data.dia = filtro(31, "Erro, digite um número de 1 a 31\n", "Dia: ");

        data.mes = filtro(12, "Erro, digite um número de 1 a 12\n", "Mes: ");

        data.ano = filtroAno(dataAtual.ano, "Erro, não é possível marcar um evento num ano que já passou.\n", "Ano: ");

        // Horário inicial

        // Verificando se tem algum evento com a mesma data e horario de ínicio
        printf("Horario de ínico\n");
        while (1)
        {
            cont = 0;
            inicio.hora = filtro(23, "Erro, digite um número de 0 a 23\n", "Hora: ");
            inicio.minuto = filtro(59, "Erro digite um número de 0 a 59\n", "Minuto: ");

            for(i = 0; i < agenda->n_eventos; i++){
                if(dataIgual(data, agenda->eventos[i].data) == 1 && horarioIgual(inicio, agenda->eventos[i].inicio) == 1){
                    printf("Horario invalido, já existe um evento cadastrado nessa data e com esse horario\n");
                    printf("Por favor digite outro horario\n");
                    cont++;
                }
            }

            if(cont == 0){
                agenda->eventos[agenda->n_eventos].inicio = inicio;
                agenda->eventos[agenda->n_eventos].data = data;
                break;
            }
        }
        
        // Horário final
        printf("Horario de fim\n");
      
        agenda->eventos[agenda->n_eventos].fim.hora = filtro(23, "Erro, digite um número de 0 a 23\n", "Hora: ");
       
        agenda->eventos[agenda->n_eventos].fim.minuto = filtro(59, "Erro digite um número de 0 a 59\n", "Minuto: ");

        agenda->n_eventos++;

        printf("Evento incluído\n");
    }

    printf("\nAperte qualquer botão para sair: ");
    __fpurge(stdin);
    fgets(finalizar, 10, stdin);

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

            // Se o minuto for zero
            if(agenda->eventos[i].inicio.minuto == 0){
                printf("Horário de ínicio: %d: 00\n",agenda->eventos[i].inicio.hora);    
            }else{
                printf("Horário de ínicio: %d: %d\n",
                                                agenda->eventos[i].inicio.hora,
                                                agenda->eventos[i].inicio.minuto
                );
            }

            if(agenda->eventos[i].fim.minuto == 0){
                printf("Hórario de final: %d: 00\n", agenda->eventos[i].fim.hora);
            }else{
                printf("Horário de final: %d: %d\n",
                                                agenda->eventos[i].fim.hora,
                                                agenda->eventos[i].fim.minuto
                );
            }
            
            
            printf("==========================================\n");
            printf("\n");
        }
    }

    printf("\nAperte qualquer botão para sair: ");
    __fpurge(stdin);
    fgets(finalizar, 10, stdin);
}

void mostrarEventosPorData(Agenda *agenda){
    system("clear");

    char finalizar[10];
    int i, cont = 0;
    Data data;

    printf("Entre com uma data\n");
    data.dia = filtro(31, "Erro, digite um número de 1 a 31\n", "Dia: ");
    data.mes = filtro(12, "Erro, digite um número de 1 a 12\n", "Mes: ");
    printf("Ano: ");
    scanf("%d", &data.ano);

    system("clear");
    if(agenda->n_eventos == 0){
        printf("Nenhum evento encontrado...\n");
    }else{
        //printf("Eventos de %d/ %d/ %d\n", data.dia, data.mes, data.ano);
        for(i = 0; i < agenda->n_eventos; i++){
            if(dataIgual(agenda->eventos[i].data, data) == 1){
                printf("==========================================\n");
                // Local e descrição
                printf("Local: %s", agenda->eventos[i].local);
                printf("Descrição: %s", agenda->eventos[i].descricao);

                //Horário de ínicio e finalização

                // Se o minuto for 0
                if(agenda->eventos[i].inicio.minuto == 0){
                    printf("Horário de ínicio: %d: 00\n",agenda->eventos[i].inicio.hora);   
                }else{
                    printf("Horário de ínicio: %d: %d\n",
                                                agenda->eventos[i].inicio.hora,
                                                agenda->eventos[i].inicio.minuto
                    );
                }

                if(agenda->eventos[i].fim.minuto == 0){
                        printf("Hórario de final: %d: 00\n", agenda->eventos[i].fim.hora);

                }else{
                    printf("Hórario de final: %d: %d\n",
                                              agenda->eventos[i].fim.hora,
                                              agenda->eventos[i].fim.minuto
                     );

                }
                
                printf("==========================================\n");
                cont++;
            }

        }
    }

    if(cont == 0){
        printf("Nenhum evento encontrado nessa data\n");
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

                //Se o minuto for 0

                if(agenda->eventos[i].inicio.minuto == 0){
                    printf("Horário de ínicio: %d: 00\n", agenda->eventos[i].inicio.hora);
                }else{
                     printf("Horário de ínicio: %d: %d\n",
                                                agenda->eventos[i].inicio.hora,
                                                agenda->eventos[i].inicio.minuto
                    );
                }
               
                if(agenda->eventos[i].fim.minuto == 0){
                    printf("Hórario de final: %d: 00\n", agenda->eventos[i].fim.hora);
                }else{
                    printf("Hórario de final: %d: %d\n",
                                              agenda->eventos[i].fim.hora,
                                              agenda->eventos[i].fim.minuto
                    );
                }

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

void removerEvento(Agenda *agenda){
    system("clear");

    int i = 0, conta_excluido = 0;
    char finalizar[10];
    Data data;
    Hora inicio;

    printf("Entre com o data do evento e o horario inical para removel: \n");
    printf("Data:\n");
    
    data.dia = filtro(31, "Erro, digite um número de 1 a 31\n", "Dia: ");
    data.mes = filtro(12, "Erro, digite um número de 1 a 12\n", "Mes: ");
    printf("Ano: ");
    scanf("%d", &data.ano);

    printf("Horario inicial:\n");
    inicio.hora = filtro(23, "Erro, digite um número de 0 a 23\n", "Hora: ");
    inicio.minuto = filtro(59, "Erro digite um número de 0 a 59\n", "Minuto: ");


    while(i < agenda->n_eventos){
        if(dataIgual(agenda->eventos[i].data, data) == 1 && horarioIgual(agenda->eventos[i].inicio, inicio) == 1){
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
