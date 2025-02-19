#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>

#define TAMANHO100 100
#define TAMANHO1000 1000
#define TAMANHO10000 10000
#define TAMANHO100000 100000

struct Ordenar{
    unsigned long trocas;
    unsigned long comparacao;
}; 

void Menu();

void CriandoArquivos(int tamanho, const char *NOMEARQUIVO,int contaArquivo)
{
    FILE* Arquivo = fopen(NOMEARQUIVO, "w");

    for(int i = 0; i < tamanho; i++)
    {
        fprintf(Arquivo,"%d ", rand()%100000);
    }
    fclose(Arquivo);

    if(Arquivo == NULL)
    {
        printf("ERRO AO CRIAR ARQUIVO\n");
    }
    
    printf("O arquivo foi criado com sucesso! \n");
    Sleep(1000);
    system("cls");
}

void bubble(int n, int vet[], const char *NOVOARQUIVO,struct Ordenar *contar)
{
    clock_t start, end;

    start = clock();

    int i, j;
    for(i =n-1; i>= 1; i-- )
    {
        for(j = 0; j<n-i-1;j++)
        {
            contar->comparacao++;
            if(vet[j] > vet[j+1])
            {
                int aux = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = aux;
                contar->trocas++;
            }
        }
    }
    end = clock();
    double tempoexec = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("BUBBLE SORT:\n");
    printf("Trocas = %lu | Comparacoes = %lu\n", contar->trocas, contar->comparacao);
    printf("Tempo de execucao: %.6lfs (%.3lf ms)\n\n", tempoexec, tempoexec * 1000);
    contar->trocas = 0;
    contar->comparacao = 0;

    char novoOrdenado[50];
    sprintf(novoOrdenado, "%s_BUBBLE.txt", NOVOARQUIVO);

    FILE* bubbleOrdenado = fopen(novoOrdenado, "w");
    for(int k = 0; k< n; k++)
    {
        fprintf(bubbleOrdenado, "%d ", vet[k]);
    }
    fclose(bubbleOrdenado);
}

void selection(int n, int vet[], const char *NOVOARQUIVO, struct Ordenar *contar)
{
    int i, j, min_index, aux;

    clock_t start, end;

    start = clock();
    for(i= 0; i< n -1; i++)
    {
        min_index = i;
        for(j = i+1;j<n;j++)
        {
            contar->comparacao++;
            if(vet[j] < vet[min_index])
            {
                min_index =j;
            }
        }
        contar->trocas++;
        aux = vet[min_index];
        vet[min_index] = vet[i];
        vet[i] =aux;

    } 

    end = clock();
    double tempoexec = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("SELECTION SORT:\n");
    printf("Trocas = %lu | Comparacoes = %lu\n", contar->trocas, contar->comparacao);
    printf("Tempo de execucao: %.6lfs (%.3lf ms)\n\n", tempoexec, tempoexec * 1000);

    contar->comparacao = 0;
    contar->trocas = 0;

    
    char tipoOrdenacao[50] = "SELECTION";
    char novoOrdenado[50];
    sprintf(novoOrdenado, "%s_SELECTION.txt", NOVOARQUIVO);
    
    FILE* selectionOrdenado = fopen(novoOrdenado, "w");
    for(int k = 0; k< n; k++)
    {
        fprintf(selectionOrdenado, "%d ", vet[k]);
    }
    fclose(selectionOrdenado);

}

void insertion(int n, int vet[], const char *NOVOARQUIVO, struct Ordenar *contar)
{
    clock_t start, end;

    start = clock();
    int chave, i, j;
    for(i = 1; i< n; i++)
    {
        chave = vet[i];
        j = i - 1;
        
        
        while (j>=0 && vet[j] > chave)
        {
            vet[j+1] = vet[j];
            j--;
            contar->trocas++;
            contar->comparacao++;
        }
        vet[j+1] =chave;
        contar->trocas++;
    }
    
    end = clock();
    double tempoexec = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("INSERTION SORT:\n");
    printf("Trocas = %lu | Comparacoes = %lu\n", contar->trocas, contar->comparacao);
    printf("Tempo de execucao: %.6lfs (%.3lf ms)\n\n", tempoexec, tempoexec * 1000);

    contar->comparacao = 0;
    contar->trocas = 0;

    char novoOrdenado[50];
    sprintf(novoOrdenado, "%s_INSERTION.txt", NOVOARQUIVO);
    
    FILE* insertionOrdenado = fopen(novoOrdenado, "w");
    for(int k = 0; k< n; k++)
    {
        fprintf(insertionOrdenado, "%d ", vet[k]);
    }
    fclose(insertionOrdenado);

}

/*INICIO HEAP SORT*/

void heapify(int n, int vet[], int i, struct Ordenar *contar)// Verificar o 100.000 quando chegar em casa.
{
    int maior = i;
    int l = i + 1;
    int r = i + 2; 

    contar->comparacao++;
    if(l < n && vet[l] > vet[maior])
    {
        maior = l;
    }

    contar->comparacao++;
    if(r < n && vet[r] > vet[maior])
    {
        maior = r;
    }

    contar->comparacao++;
    if(maior != i)
    {
        contar->trocas++;
        int aux = vet[i];
        vet[i] = vet[maior];
        vet[maior] = aux;
        heapify(n,vet,maior, contar);
    }
}

void heap(int n, int vet[],const char *NOVOARQUIVO, struct Ordenar *contar)
{
    clock_t start, end;

    start = clock();
    for(int i = n - 1; i>=0;i--)
    {
        heapify(n,vet,i,contar);
    }
    for(int j = n -1; j>=0;j--)
    {
        contar->trocas++;
        int aux = vet[0];
        vet[0] = vet[j];
        vet[j] = aux;
        heapify(j,vet,0, contar);
    }
    end = clock();
    
    double tempoexec = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("HEAP SORT:\n");
    printf("Trocas = %lu | Comparacoes = %lu\n", contar->trocas, contar->comparacao);
    printf("Tempo de execucao: %.6lfs (%.3lf ms)\n\n", tempoexec, tempoexec * 1000);
    contar->trocas = 0;
    contar->comparacao = 0;

    char novoOrdenado[50];
    sprintf(novoOrdenado, "%s_HEAP.txt", NOVOARQUIVO);
    
    FILE* heapOrdenado = fopen(novoOrdenado, "w");
    for(int k = 0; k< n; k++)
    {
        fprintf(heapOrdenado, "%d ", vet[k]);
    }
    fclose(heapOrdenado);
}

/*FIM HEAP SORT*/

/*INICIO Radix */ //Não precisa de contador 
int PegaMax(int n, int vet[])
{
    int max =vet[0];
    for (int i =1;i<n;i++)
    {
        if(vet[i]> max)
        {
            max = vet[i];
        }
    }
    return max;
}

void ContaSort(int n, int vet[], int exp)
{
    int saida[n];
    int contador[10] ={0};

    for(int i = 0; i < n; i++)
    {
        contador[(vet[i]/ exp) % 10]++;
    }
    for(int i = 1; i < 10; i++)
    {
        contador[i] += contador[i-1];
    }
    for(int i = n -1; i>=0;i--)
    {
        int pos = contador[(vet[i]/exp) % 10] -1;
        saida[pos] = vet[i];
        contador[(vet[i]/exp) % 10] --;
    }
    for(int i = 0; i< n; i++)
    {
        vet[i] =saida[i];
    }
}

void radix(int n, int vet[], const char *NOVOARQUIVO)
{
    clock_t start, end;
    start = clock();
    int max = PegaMax(n,vet);

    for(int exp =1; max/exp > 0; exp*=10)
    {
        ContaSort(n, vet, exp);
    }
    end = clock();
    double tempoexec = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %.6lfs (%.3lf ms)\n\n", tempoexec, tempoexec * 1000);


    char novoOrdenado[50];
    sprintf(novoOrdenado, "%s_RADIX.txt", NOVOARQUIVO);
    
    FILE* radixOrdenado = fopen(novoOrdenado, "w");
    for(int k = 0; k< n; k++)
    {
        fprintf(radixOrdenado, "%d ", vet[k]);
    }
    fclose(radixOrdenado);
}   

/*FIM Radix */

/*INICIO Quick*/

void troca(int *a, int *b)
{
    int temp = *a;
    *a= *b;
    *b= temp;
}

int particao(int vet[], int min, int max, struct Ordenar *contar)
{
    int pivo = vet[max];
    int i = min - 1;

    for(int j=min;j<max;j++)
    {
        contar->comparacao++;
        if(vet[j] < pivo)
        {
            i++;
            troca(&vet[i], &vet[j]);
            contar->trocas++;
        }
    }
    troca(&vet[i+1], &vet[max]);
    contar->trocas++;
    return (i+1);

}

void quicksort(int n, int vet[], int min, const char *NOVOARQUIVO, struct Ordenar *contar)
{

    contar->comparacao++;
    if(min < n)
    {
        int indexpivo = particao(vet, min, n,contar);
        quicksort(indexpivo - 1,vet,min,NOVOARQUIVO,contar);
        quicksort(n,vet,indexpivo + 1,NOVOARQUIVO,contar);  
    }
    
}

void printQuick(int n, int vet[], int min, const char *NOVOARQUIVO, struct Ordenar *contar)
{
    clock_t start, end;
    start = clock();
    quicksort(n,vet,min,NOVOARQUIVO,contar);
    end = clock();

    double tempoexec = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("QUICK SORT:\n");
    printf("Trocas = %lu | Comparacoes = %lu\n", contar->trocas, contar->comparacao);
    printf("Tempo de execucao: %.9lfs (%.5lf ms)\n\n", tempoexec, tempoexec * 1000);

    contar->comparacao = 0;
    contar->trocas = 0;

    char novoOrdenado[50];
    sprintf(novoOrdenado, "%s_QUICK.txt", NOVOARQUIVO);
    
    FILE* quickOrdenado = fopen(novoOrdenado, "w");
    for(int k = 0; k< n; k++)
    {
        fprintf(quickOrdenado, "%d ", vet[k]);
    }
    fclose(quickOrdenado);

}
/*FIM Quick*/

void OrdenarArquivos(const char *NOMEARQUIVO, const char *NOVOARQUIVO)
{
    int escolhaOrdenacao;
    printf("Escolha uma das opcoes de ordenacao\n");
    printf("1-SelectionSort \n2-InsertionSort \n3-BubbleSort \n4-HeapSort \n5-RadixSort \n6-QuickSort \n7-MergeSort \n 8-Voltar");
    printf(":");
    scanf("%d", &escolhaOrdenacao);

    struct Ordenar contar = {0,0};
    
    printf("\n");

    FILE* fp = fopen(NOMEARQUIVO, "r");

    int *numeros = malloc(TAMANHO100000 * sizeof(int));
    int tamanho = 0;
    while (fscanf(fp, "%d", &numeros[tamanho]) != EOF) {
        tamanho++;
    }
    fclose(fp);
    
    
    switch (escolhaOrdenacao)
    {
    case 1:
        printf("Arquivo selecionado: %s\n", NOMEARQUIVO);
        selection(tamanho,numeros,NOVOARQUIVO, &contar);
        break;
    case 2:
        printf("Arquivo selecionado: %s\n", NOMEARQUIVO);    
        insertion(tamanho,numeros,NOVOARQUIVO, &contar);
        break;
    case 3:
        printf("Arquivo selecionado: %s\n", NOMEARQUIVO);    
        bubble(tamanho,numeros,NOVOARQUIVO, &contar);
        break;
    case 4:
        printf("Arquivo selecionado: %s\n", NOMEARQUIVO);        
        heap(tamanho, numeros, NOVOARQUIVO, &contar);
        break;
    case 5:
        printf("Arquivo selecionado: %s\n", NOMEARQUIVO);    
        radix(tamanho, numeros, NOVOARQUIVO);
        break;
    case 6:
        printf("Arquivo selecionado: %s\n", NOMEARQUIVO);        
        printQuick(tamanho -1,numeros, 0, NOVOARQUIVO,&contar);
        break;
    case 7:
        /* code */ //merge
        printf("Arquivo selecionado: %s\n", NOMEARQUIVO);    
        break;
    case 8:
        system("cls");
        Menu();
        break;
    
    default:
        printf("ERRO! \nEsse tipo de ordenacao nao pertence ao menu");
        break;
    }

}
void Menu()
{
    int escolha;
    int contaArquivo = 0;
    while(escolha != 3)
    {

        printf("Escolha uma das opcoes: \n");
        printf("0-Gerar arquivos \n");
        printf("1-Ordenar arquivos \n");
        printf("2-Busca Binaria arquivos \n");
        printf("3-Fechar programa \n");
        printf(":");
        scanf("%d", &escolha);
        while (getchar() != '\n');  // Limpa buffer de entrada

        system("cls");

        switch (escolha)
        {
        case 0:
            srand(time(NULL));
            CriandoArquivos(TAMANHO100, "ARQUIVO100.txt",contaArquivo++);
            CriandoArquivos(TAMANHO1000,"ARQUIVO1000.txt",contaArquivo++);
            CriandoArquivos(TAMANHO10000,"ARQUIVO10000.txt",contaArquivo++);
            CriandoArquivos(TAMANHO100000,"ARQUIVO100000.txt",contaArquivo);
            break;
        case 1:           
            OrdenarArquivos("ARQUIVO100.txt","ARQUIVO100_ORDENADO");
            OrdenarArquivos("ARQUIVO1000.txt","ARQUIVO1000_ORDENADO");
            OrdenarArquivos("ARQUIVO10000.txt","ARQUIVO10000_ORDENADO");
            OrdenarArquivos("ARQUIVO100000.txt","ARQUIVO100000_ORDENADO");
            break;
        case 2:
            /*CODE*/
            break;
        case 3:
            printf("Saindo do sistema!!!!");
            Sleep(1000);
            system("cls");
            break;
        default:
            printf("ERRO! \nESCOLHA NAO EXISTE\n");
            Sleep(1000);
            system("cls");
            break;
        }
    }
    
}

int main()
{
    Menu();
    system("Pause");
    return 0;
}