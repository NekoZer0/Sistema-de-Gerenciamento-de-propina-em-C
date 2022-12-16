#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
void *malloc(size_t);

typedef struct{
    char nome[50],curso[50],turma[50];
    char situacao;
    int dia, mes, ano,numeroEstudante,propina1,propina,anoQueFrequenta;
}Contato;

void imprimir(Contato **c, int quant){
    int i;

    printf("\n\t\tLista de alunos:\n");
    printf("\t-----------------------------------------------------------------------------------------------------------------------------\n");
    for(i = 0; i < quant; i++){
        printf("\tcodigo aluno: %d | Data: %2d/%2d/%4d\tNome: %s\t Curso: %s\t Turma: %s\t Ano: %d ano\t numero de estudante: %d\t propina: %d kz,\t Situacao: %c\n\n", i+1, c[i]->dia, c[i]->mes, c[i]->ano, c[i]->nome,c[i]->curso,c[i]->turma,c[i]->anoQueFrequenta,c[i]->numeroEstudante,c[i]->propina,c[i]->situacao );
    }
    printf("\t-----------------------------------------------------------------------------------------------------------------------------\n");
}

int cadastrar_contato(Contato **c, int quant, int tam){

    if(quant < tam){
        Contato *novo = malloc(sizeof(Contato));

        printf("\nDigite o nome do aluno: ");
        scanf("%50[^\n]", novo->nome);
        getchar();
        printf("\nDigite o curso do aluno: ");
        scanf("%50[^\n]", novo->curso);
        getchar();
        printf("\nDigite a turma do aluno: ");
        scanf("%50[^\n]", novo->turma);
        getchar();
        printf("\nDigite a data de pagemento de propina dd mm aaaa: ");
        scanf("%d%d%d", &novo->dia, &novo->mes, &novo->ano);
        getchar();
        printf("\nDigite o ano que o aluno frequenta: ");
        scanf("%d", &novo->anoQueFrequenta);
        getchar();
        printf("\nDigite o numero de estudante: ");
        scanf("%d", &novo->numeroEstudante);
        getchar();
        printf("\nDigite o valor da propina: ");
        scanf("%d", &novo->propina1);
        getchar();
        if(novo->dia<=10){
            novo->propina=novo->propina1;
        }
        else{
            novo->propina=novo->propina1 + ((novo->propina1)*10)/100;
        }

        if (novo->propina>=45000){
            novo->situacao='P';
        }
        else{
            novo->situacao='D';
        }
        c[quant] = novo;
        return 1;
    }
    else{
        printf("\n\tImpossivel novo cadastro. Vetor cheio!\n");
        return 0;
    }
}

void alterar_contato(Contato **c, int quant){
    int id;

    imprimir(c, quant);

    printf("\n\tDigite o codigo do aluno que deseja alterar: \n");
    scanf("%d", &id);
    getchar();
    id--;

    if(id >= 0 && id < quant){
        Contato *novo = malloc(sizeof(Contato));
        printf("\nDigite o nome do aluno: ");
        scanf("%50[^\n]", novo->nome);
        getchar();
        printf("\nDigite o curso do aluno: ");
        scanf("%50[^\n]", novo->curso);
        getchar();
        printf("\nDigite a turma do aluno: ");
        scanf("%50[^\n]", novo->turma);
        getchar();
        printf("\nDigite a data de pagemento de propina dd mm aaaa: ");
        scanf("%d%d%d", &novo->dia, &novo->mes, &novo->ano);
        getchar();
        printf("\nDigite o ano que o aluno frequenta: ");
        scanf("%d", &novo->anoQueFrequenta);
        getchar();
        printf("\nDigite o numero de estudante: ");
        scanf("%d", &novo->numeroEstudante);
        getchar();
        printf("\nDigite o valor da propina: ");
        scanf("%d", &novo->propina);
        getchar();
        
        if(novo->dia<=10){
            novo->propina=novo->propina1;
        }
        else{
            novo->propina=novo->propina1 + ((novo->propina1)*10)/100;
        }
        if (novo->propina>=45000){
            novo->situacao='P';
        }
        else{
            novo->situacao='D';
        }

        c[id] = novo;
    }
    else
        printf("\n\tCodigo invalido!\n");
}

// -------- excluir contato ------------------------------
int excluir_contato(Contato **c, int quant){
    int id;

    imprimir(c, quant);

    printf("\n\tDigite o codigo do Aluno que deseja excluir: \n");
    scanf("%d", &id);
    getchar();
    id--;

    if(id >= 0 && id < quant){
        // apagar contato
        free(c[id]);
        if(id < quant - 1)
            c[id] = c[quant - 1];
        return -1; // excluido com sucesso
    }
    else{
        printf("\n\tCodigo invalido!\n");
        return 0; // nenhum contato excluido
    }
}

void salvar(Contato **c, int quant, char arq[]){
    FILE *file = fopen(arq, "w");
    int i;

    if(file){
        fprintf(file, "%d\n", quant);
        for(i = 0; i < quant; i++){
            fputs(c[i]->nome, file);
            fputc('\n', file);
            fputs(c[i]->curso, file);
            fputc('\n', file);
            fputs(c[i]->turma, file);
            fputc('\n', file);
            fputc('\n', file);
            fprintf(file, "%c\n",c[i]->situacao);
            fputc('\n', file);
            fprintf(file, "%d %d %d\n", c[i]->dia, c[i]->mes, c[i]->ano);
            fputc('\n', file);
            fprintf(file, "%d\n", c[i]->anoQueFrequenta);
            fputc('\n', file);
            fprintf(file, "%d\n", c[i]->numeroEstudante);
            fputc('\n', file);
            fprintf(file, "%d\n", c[i]->propina);
        }
        fclose(file);
    }
    else
        printf("\n\tNAO FOI POSSIVEL ABRIR/CRIAR O ARQUIVO!\n");
}

int ler_arquivo(Contato **c, char arq[]){
    FILE *file = fopen(arq, "r");
    int quant = 0, i;
    Contato *novo = malloc(sizeof(Contato));

    if(file){
        fscanf(file, "%d\n", &quant);
        for(i = 0; i < quant; i++){
            //fgets(novo->nome, 50, file);
            fscanf(file, "%50[^\n]", novo->nome);
            fscanf(file, "%50[^\n]", novo->curso);
            fscanf(file, "%50[^\n]", novo->turma);
            fscanf(file, "%c", novo->situacao);
            fscanf(file, "%d %d %d\n", &novo->dia, &novo->mes, &novo->ano);
            fscanf(file, "%d\n", &novo->anoQueFrequenta);
            fscanf(file, "%d\n", &novo->numeroEstudante);
            fscanf(file, "%d\n", &novo->propina);
            c[i] = novo;
            novo = malloc(sizeof(Contato));
        }
        fclose(file);
    }
    else
        printf("\n\tNAO FOI POSSIVEL ABRIR/CRIAR O ARQUIVO!\n");
    return quant;
}

int main(){

    Contato *sistema[50];
    char arquivo[] = {"sistema.txt"};
    int opcao, tam = 50, quant = 0;

    do{
        printf("\n\t0 - Sair\n\t1 - Cadastrar\n\t2 - Alterar\n\t3 - Imprimir\n\t4 - Salvar\n\t5 - Ler arquivo\n\t6 - Excluir Contato\n");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
        case 1:
            quant += cadastrar_contato(sistema, quant, tam);
            break;
        case 2:
            alterar_contato(sistema, quant);
            break;
        case 3:
            imprimir(sistema, quant);
            break;
        case 4:
            salvar(sistema, quant, arquivo);
            break;
        case 5:
            quant = ler_arquivo(sistema, arquivo);
            break;
        case 6:
            quant += excluir_contato(sistema, quant);
            break;
        default:
            if(opcao != 0)
                printf("\n\tOpcao invalida!!!\n");
        }
    }while(opcao != 0);

    return 0;
}
