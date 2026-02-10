/*
 * ========================================
 * SISTEMA DE INVENTÁRIO - FREE FIRE
 * Nível: Aventureiro
 * ========================================
 *
 * Este programa implementa um sistema de inventário comparando
 * DUAS estruturas de dados: vetores e listas encadeadas.
 *
 * Objetivo:
 * - Demonstrar diferenças de performance entre vetores e listas
 * - Implementar as mesmas operações em ambas estruturas
 * - Aplicar algoritmos de busca e ordenação
 * - Comparar número de comparações em cada tipo de busca
 *
 * Funcionalidades:
 * - Cadastro de itens em vetor ou lista encadeada
 * - Remoção de itens
 * - Listagem de todos os itens
 * - Busca sequencial com contador de comparações
 * - Ordenação de vetor (Selection Sort)
 * - Busca binária com contador de comparações
 * - Comparação de performance entre estruturas
 *
 * Autor: Estrutura de Dados - Nível Aventureiro
 * Data: 2026
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* ========================================
 * DEFINIÇÃO DE STRUCTS
 * ========================================
 *
 * Item: estrutura que armazena informações sobre um item
 * - nome: identificação do item (ex: "Rifle AK")
 * - tipo: categoria do item (ex: "arma", "munição", "cura")
 * - quantidade: número de unidades desse item
 *
 * No: nó da lista encadeada
 * - dados: contém as informações do item
 * - proximo: ponteiro para o próximo nó (ou NULL)
 */

typedef struct
{
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No
{
    Item dados;
    struct No *proximo;
} No;

/* ========================================
 * CONSTANTES E VARIÁVEIS GLOBAIS
 * ========================================
 *
 * MAX_ITENS: limite de itens na mochila
 * Contadores globais para comparações
 * Arrays e listas para armazenar dados
 */

#define MAX_ITENS 10
#define LINHA "===================================================="

// Estruturas de dados - VETOR
Item mochilaVetor[MAX_ITENS];
int totalItensVetor = 0;
int comparacoesSequencialVetor = 0;
int comparacoesBinariaVetor = 0;

// Estruturas de dados - LISTA ENCADEADA
No *mochilaLista = NULL;
int totalItensLista = 0;
int comparacoesSequencialLista = 0;

/* ========================================
 * FUNÇÕES - VETOR (Lista Sequencial)
 * ======================================== */

/*
 * Função: inserirItemVetor
 * Descrição: adiciona um novo item no vetor
 * Parâmetros: nome, tipo, quantidade do item
 * Retorno: 1 se sucesso, 0 se falhou
 */
int inserirItemVetor(const char *nome, const char *tipo, int quantidade)
{
    if (totalItensVetor >= MAX_ITENS)
    {
        return 0;
    }

    strcpy(mochilaVetor[totalItensVetor].nome, nome);
    strcpy(mochilaVetor[totalItensVetor].tipo, tipo);
    mochilaVetor[totalItensVetor].quantidade = quantidade;

    totalItensVetor++;
    return 1;
}

/*
 * Função: removerItemVetor
 * Descrição: remove um item do vetor pelo nome
 * Parâmetros: nome do item a remover
 * Retorno: 1 se sucesso, 0 se falhou
 */
int removerItemVetor(const char *nome)
{
    int indice = -1;

    // Busca sequencial do item
    for (int i = 0; i < totalItensVetor; i++)
    {
        if (strcmp(mochilaVetor[i].nome, nome) == 0)
        {
            indice = i;
            break;
        }
    }

    if (indice == -1)
    {
        return 0;
    }

    // Remove o item deslocando os posteriores
    for (int i = indice; i < totalItensVetor - 1; i++)
    {
        mochilaVetor[i] = mochilaVetor[i + 1];
    }

    totalItensVetor--;
    return 1;
}

/*
 * Função: listarItensVetor
 * Descrição: exibe todos os itens do vetor em formato tabular
 * Parâmetros: nenhum
 * Retorno: nenhum
 */
void listarItensVetor()
{
    printf("\n%s\n", LINHA);
    printf("           📦 ITENS DO INVENTÁRIO (VETOR) 📦\n");
    printf("%s\n", LINHA);

    if (totalItensVetor == 0)
    {
        printf("⚠️  Sua mochila está vazia! Colete itens para começar.\n");
        printf("%s\n\n", LINHA);
        return;
    }

    printf("Total de itens: %d/%d\n\n", totalItensVetor, MAX_ITENS);

    printf("┌────┬──────────────────────────┬────────────────┬────────────┐\n");
    printf("│ #  │ Nome do Item             │ Tipo           │ Quantidade │\n");
    printf("├────┼──────────────────────────┼────────────────┼────────────┤\n");

    for (int i = 0; i < totalItensVetor; i++)
    {
        printf("│ %2d │ %-24s │ %-14s │ %10d │\n",
               i + 1,
               mochilaVetor[i].nome,
               mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
    }

    printf("└────┴──────────────────────────┴────────────────┴────────────┘\n");
    printf("\n");
}

/*
 * Função: buscarSequencialVetor
 * Descrição: busca item no vetor sequencialmente e conta comparações
 * Parâmetros: nome do item
 * Retorno: índice do item ou -1 se não encontrado
 */
int buscarSequencialVetor(const char *nome)
{
    comparacoesSequencialVetor = 0;

    for (int i = 0; i < totalItensVetor; i++)
    {
        comparacoesSequencialVetor++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0)
        {
            return i;
        }
    }

    return -1;
}

/*
 * Função: ordenarVetor (Selection Sort)
 * Descrição: ordena os itens do vetor alfabeticamente por nome
 * Parâmetros: nenhum
 * Retorno: nenhum
 *
 * Complexidade: O(n²)
 * Estratégia: encontra o menor elemento e coloca no início
 */
void ordenarVetor()
{
    printf("\n⏳ Ordenando itens (Selection Sort)...\n");

    for (int i = 0; i < totalItensVetor - 1; i++)
    {
        int menorIndice = i;

        // Encontra o índice do menor elemento
        for (int j = i + 1; j < totalItensVetor; j++)
        {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[menorIndice].nome) < 0)
            {
                menorIndice = j;
            }
        }

        // Troca os elementos
        if (menorIndice != i)
        {
            Item temp = mochilaVetor[i];
            mochilaVetor[i] = mochilaVetor[menorIndice];
            mochilaVetor[menorIndice] = temp;
        }
    }

    printf("✅ Itens ordenados alfabeticamente!\n");
}

/*
 * Função: buscarBinariaVetor
 * Descrição: busca item no vetor ordenado usando busca binária
 * Parâmetros: nome do item
 * Retorno: índice do item ou -1 se não encontrado
 *
 * Precondição: vetor deve estar ORDENADO
 * Complexidade: O(log n)
 */
int buscarBinariaVetor(const char *nome)
{
    comparacoesBinariaVetor = 0;
    int esquerda = 0;
    int direita = totalItensVetor - 1;

    while (esquerda <= direita)
    {
        comparacoesBinariaVetor++;
        int meio = (esquerda + direita) / 2;
        int comparacao = strcmp(mochilaVetor[meio].nome, nome);

        if (comparacao == 0)
        {
            return meio; // Encontrado!
        }
        else if (comparacao < 0)
        {
            esquerda = meio + 1; // Procura na metade direita
        }
        else
        {
            direita = meio - 1; // Procura na metade esquerda
        }
    }

    return -1; // Não encontrado
}

/* ========================================
 * FUNÇÕES - LISTA ENCADEADA
 * ======================================== */

/*
 * Função: criarNo
 * Descrição: cria um novo nó para a lista encadeada
 * Parâmetros: nome, tipo, quantidade do item
 * Retorno: ponteiro para o novo nó
 */
No *criarNo(const char *nome, const char *tipo, int quantidade)
{
    No *novoNo = (No *)malloc(sizeof(No));

    if (novoNo == NULL)
    {
        printf("❌ Erro ao alocar memória!\n");
        return NULL;
    }

    strcpy(novoNo->dados.nome, nome);
    strcpy(novoNo->dados.tipo, tipo);
    novoNo->dados.quantidade = quantidade;
    novoNo->proximo = NULL;

    return novoNo;
}

/*
 * Função: inserirItemLista
 * Descrição: insere um novo item no final da lista encadeada
 * Parâmetros: nome, tipo, quantidade do item
 * Retorno: 1 se sucesso, 0 se falhou
 */
int inserirItemLista(const char *nome, const char *tipo, int quantidade)
{
    No *novoNo = criarNo(nome, tipo, quantidade);

    if (novoNo == NULL)
    {
        return 0;
    }

    if (mochilaLista == NULL)
    {
        mochilaLista = novoNo;
    }
    else
    {
        // Encontra o último nó
        No *atual = mochilaLista;
        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
    }

    totalItensLista++;
    return 1;
}

/*
 * Função: removerItemLista
 * Descrição: remove um item da lista pelo nome
 * Parâmetros: nome do item a remover
 * Retorno: 1 se sucesso, 0 se falhou
 */
int removerItemLista(const char *nome)
{
    if (mochilaLista == NULL)
    {
        return 0;
    }

    // Se é o primeiro nó
    if (strcmp(mochilaLista->dados.nome, nome) == 0)
    {
        No *temp = mochilaLista;
        mochilaLista = mochilaLista->proximo;
        free(temp);
        totalItensLista--;
        return 1;
    }

    // Procura nos próximos nós
    No *atual = mochilaLista;
    while (atual->proximo != NULL)
    {
        if (strcmp(atual->proximo->dados.nome, nome) == 0)
        {
            No *temp = atual->proximo;
            atual->proximo = temp->proximo;
            free(temp);
            totalItensLista--;
            return 1;
        }
        atual = atual->proximo;
    }

    return 0;
}

/*
 * Função: listarItensLista
 * Descrição: exibe todos os itens da lista em formato tabular
 * Parâmetros: nenhum
 * Retorno: nenhum
 */
void listarItensLista()
{
    printf("\n%s\n", LINHA);
    printf("      📦 ITENS DO INVENTÁRIO (LISTA) 📦\n");
    printf("%s\n", LINHA);

    if (mochilaLista == NULL)
    {
        printf("⚠️  Sua mochila está vazia! Colete itens para começar.\n");
        printf("%s\n\n", LINHA);
        return;
    }

    printf("Total de itens: %d/%d\n\n", totalItensLista, MAX_ITENS);

    printf("┌────┬──────────────────────────┬────────────────┬────────────┐\n");
    printf("│ #  │ Nome do Item             │ Tipo           │ Quantidade │\n");
    printf("├────┼──────────────────────────┼────────────────┼────────────┤\n");

    No *atual = mochilaLista;
    int contador = 1;

    while (atual != NULL)
    {
        printf("│ %2d │ %-24s │ %-14s │ %10d │\n",
               contador,
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);
        atual = atual->proximo;
        contador++;
    }

    printf("└────┴──────────────────────────┴────────────────┴────────────┘\n");
    printf("\n");
}

/*
 * Função: buscarSequencialLista
 * Descrição: busca item na lista sequencialmente e conta comparações
 * Parâmetros: nome do item
 * Retorno: ponteiro para o nó encontrado ou NULL
 */
No *buscarSequencialLista(const char *nome)
{
    comparacoesSequencialLista = 0;
    No *atual = mochilaLista;

    while (atual != NULL)
    {
        comparacoesSequencialLista++;
        if (strcmp(atual->dados.nome, nome) == 0)
        {
            return atual;
        }
        atual = atual->proximo;
    }

    return NULL;
}

/*
 * Função: liberarLista
 * Descrição: libera toda a memória alocada pela lista
 * Parâmetros: nenhum
 * Retorno: nenhum
 *
 * Importante: deve ser chamada ao sair do programa
 */
void liberarLista()
{
    No *atual = mochilaLista;

    while (atual != NULL)
    {
        No *temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    mochilaLista = NULL;
    totalItensLista = 0;
}

/* ========================================
 * FUNÇÕES - MENUS INTERATIVOS
 * ======================================== */

/*
 * Função: menuVetor
 * Descrição: menu de operações sobre a mochila com VETOR
 * Parâmetros: nenhum
 * Retorno: nenhum
 */
void menuVetor()
{
    int opcao;

    while (1)
    {
        printf("\n%s\n", LINHA);
        printf("     🎮 SISTEMA COM VETOR (Lista Sequencial) 🎮\n");
        printf("%s\n", LINHA);
        printf("Escolha uma opção:\n\n");
        printf("  1️⃣  - Adicionar item à mochila\n");
        printf("  2️⃣  - Remover item da mochila\n");
        printf("  3️⃣  - Listar todos os itens\n");
        printf("  4️⃣  - Buscar item (Sequencial com contador)\n");
        printf("  5️⃣  - Ordenar itens alfabeticamente\n");
        printf("  6️⃣  - Buscar binária (requer ordenação)\n");
        printf("  7️⃣  - Comparar desempenho de buscas\n");
        printf("  8️⃣  - Voltar ao menu principal\n");
        printf("%s\n", LINHA);
        printf("Digite sua opção (1-8): ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
        {
            printf("\n%s\n", LINHA);
            printf("         ➕ CADASTRAR NOVO ITEM ➕\n");
            printf("%s\n", LINHA);

            if (totalItensVetor >= MAX_ITENS)
            {
                printf("❌ Erro: Sua mochila está cheia! Máximo de %d itens.\n", MAX_ITENS);
                printf("   Remova alguns itens antes de adicionar novos.\n");
                printf("%s\n\n", LINHA);
                break;
            }

            char nome[30], tipo[20];
            int quantidade;

            printf("Digite o nome do item: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;

            printf("Digite o tipo (ex: arma, munição, cura, ferramenta): ");
            fgets(tipo, sizeof(tipo), stdin);
            tipo[strcspn(tipo, "\n")] = 0;

            printf("Digite a quantidade: ");
            scanf("%d", &quantidade);
            getchar();

            if (quantidade <= 0)
            {
                printf("❌ Erro: A quantidade deve ser maior que zero!\n");
                printf("%s\n\n", LINHA);
                break;
            }

            if (inserirItemVetor(nome, tipo, quantidade))
            {
                printf("✅ Item '%s' adicionado com sucesso à mochila!\n", nome);
                printf("%s\n", LINHA);
                listarItensVetor();
            }
            else
            {
                printf("❌ Erro ao adicionar item!\n");
            }
            break;
        }

        case 2:
        {
            printf("\n%s\n", LINHA);
            printf("         ❌ REMOVER ITEM ❌\n");
            printf("%s\n", LINHA);

            if (totalItensVetor == 0)
            {
                printf("⚠️  Sua mochila está vazia! Nada para remover.\n");
                printf("%s\n\n", LINHA);
                break;
            }

            char nome[30];
            printf("Digite o nome do item a remover: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;

            if (removerItemVetor(nome))
            {
                printf("✅ Item '%s' encontrado e removido!\n", nome);
                printf("%s\n", LINHA);
                listarItensVetor();
            }
            else
            {
                printf("❌ Item '%s' não encontrado na mochila!\n", nome);
                printf("%s\n\n", LINHA);
            }
            break;
        }

        case 3:
            listarItensVetor();
            break;

        case 4:
        {
            printf("\n%s\n", LINHA);
            printf("         🔍 BUSCAR ITEM 🔍\n");
            printf("%s\n", LINHA);

            if (totalItensVetor == 0)
            {
                printf("⚠️  Sua mochila está vazia! Nada para buscar.\n");
                printf("%s\n\n", LINHA);
                break;
            }

            char nome[30];
            printf("Digite o nome do item a buscar: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;

            int resultado = buscarSequencialVetor(nome);

            if (resultado != -1)
            {
                printf("✅ Item encontrado!\n\n");
                printf("📌 Nome: %s\n", mochilaVetor[resultado].nome);
                printf("🏷️  Tipo: %s\n", mochilaVetor[resultado].tipo);
                printf("📊 Quantidade: %d\n", mochilaVetor[resultado].quantidade);
            }
            else
            {
                printf("❌ Item '%s' não encontrado na mochila!\n", nome);
            }

            printf("\n📊 Estatísticas da busca:\n");
            printf("   Comparações realizadas: %d\n", comparacoesSequencialVetor);
            printf("   Complexidade: O(n)\n");
            printf("%s\n\n", LINHA);
            break;
        }

        case 5:
        {
            if (totalItensVetor == 0)
            {
                printf("\n⚠️  Sua mochila está vazia! Nada para ordenar.\n");
                break;
            }

            printf("\n%s\n", LINHA);
            printf("        ⬆️✔️ ORDENANDO ITENS ✔️⬆️\n");
            printf("%s\n", LINHA);
            printf("\n⏳ Ordenando itens alfabeticamente (Selection Sort)...\n");

            ordenarVetor();

            printf("✅ Itens ordenados com sucesso!\n");
            printf("%s\n", LINHA);
            listarItensVetor();
            break;
        }

        case 6:
        {
            printf("\n%s\n", LINHA);
            printf("      🔦 BUSCA BINÁRIA (RÁPIDA) 🔦\n");
            printf("%s\n", LINHA);
            printf("⚠️  IMPORTANTE: Os itens devem estar ORDENADOS!\n");
            printf("   Use a opção 5 para ordenar antes.\n\n");

            if (totalItensVetor == 0)
            {
                printf("⚠️  Sua mochila está vazia!\n");
                printf("%s\n\n", LINHA);
                break;
            }

            char nome[30];
            printf("Digite o nome do item a buscar: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;

            int resultado = buscarBinariaVetor(nome);

            if (resultado != -1)
            {
                printf("\n✅ ITEM ENCONTRADO!\n\n");
                printf("📌 Nome: %s\n", mochilaVetor[resultado].nome);
                printf("🏷️  Tipo: %s\n", mochilaVetor[resultado].tipo);
                printf("📊 Quantidade: %d\n", mochilaVetor[resultado].quantidade);
            }
            else
            {
                printf("\n❌ Item '%s' não encontrado!\n", nome);
            }

            printf("\n📊 Estatísticas da busca:\n");
            printf("   Comparações realizadas: %d\n", comparacoesBinariaVetor);
            printf("   Complexidade: O(log n)\n");
            printf("%s\n\n", LINHA);
            break;
        }

        case 7:
        {
            printf("\n%s\n", LINHA);
            printf("    📈 COMPARAÇÃO DE DESEMPENHO - VETOR 📈\n");
            printf("%s\n", LINHA);

            if (totalItensVetor == 0)
            {
                printf("⚠️  Adicione itens para comparar!\n");
                break;
            }

            printf("\n1️⃣  BUSCA SEQUENCIAL:\n");
            printf("   Comparações na última busca: %d\n", comparacoesSequencialVetor);
            printf("   Complexidade: O(n)\n");
            printf("   Melhor caso: 1 comparação\n");
            printf("   Pior caso: %d comparações\n", totalItensVetor);

            printf("\n2️⃣  BUSCA BINÁRIA (com vetor ordenado):\n");
            printf("   Comparações na última busca: %d\n", comparacoesBinariaVetor);
            printf("   Complexidade: O(log n)\n");

            int comparacoesTeoricas = 1;
            int temp = totalItensVetor;
            while (temp > 1)
            {
                temp /= 2;
                comparacoesTeoricas++;
            }
            printf("   Máx comparações teóricas: ~%d\n", comparacoesTeoricas);

            printf("\n💡 CONCLUSÃO:\n");
            if (totalItensVetor > 5)
            {
                printf("   A busca binária é MAIS EFICIENTE para este tamanho!\n");
                printf("   Ganho: redução de até %d comparações.\n",
                       comparacoesSequencialVetor - comparacoesBinariaVetor);
            }
            else
            {
                printf("   Para poucos itens, ambas são rápidas.\n");
                printf("   Busca binária fica melhor com mais dados.\n");
            }

            printf("%s\n", LINHA);
            break;
        }

        case 8:
            return;

        default:
            printf("\n❌ Opção inválida! Digite um número entre 1 e 8.\n");
        }
    }
}

/*
 * Função: menuLista
 * Descrição: menu de operações sobre a mochila com LISTA ENCADEADA
 * Parâmetros: nenhum
 * Retorno: nenhum
 */
void menuLista()
{
    int opcao;

    while (1)
    {
        printf("\n%s\n", LINHA);
        printf("   🎮 SISTEMA COM LISTA ENCADEADA 🎮\n");
        printf("%s\n", LINHA);
        printf("Escolha uma opção:\n\n");
        printf("  1️⃣  - Adicionar item à mochila\n");
        printf("  2️⃣  - Remover item da mochila\n");
        printf("  3️⃣  - Listar todos os itens\n");
        printf("  4️⃣  - Buscar item (Sequencial com contador)\n");
        printf("  5️⃣  - Voltar ao menu principal\n");
        printf("%s\n", LINHA);
        printf("Digite sua opção (1-5): ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
        {
            printf("\n%s\n", LINHA);
            printf("         ➕ CADASTRAR NOVO ITEM ➕\n");
            printf("%s\n", LINHA);

            if (totalItensLista >= MAX_ITENS)
            {
                printf("❌ Erro: Sua mochila está cheia! Máximo de %d itens.\n", MAX_ITENS);
                printf("   Remova alguns itens antes de adicionar novos.\n");
                printf("%s\n\n", LINHA);
                break;
            }

            char nome[30], tipo[20];
            int quantidade;

            printf("Digite o nome do item: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;

            printf("Digite o tipo (ex: arma, munição, cura, ferramenta): ");
            fgets(tipo, sizeof(tipo), stdin);
            tipo[strcspn(tipo, "\n")] = 0;

            printf("Digite a quantidade: ");
            scanf("%d", &quantidade);
            getchar();

            if (quantidade <= 0)
            {
                printf("❌ Erro: A quantidade deve ser maior que zero!\n");
                printf("%s\n\n", LINHA);
                break;
            }

            if (inserirItemLista(nome, tipo, quantidade))
            {
                printf("✅ Item '%s' adicionado com sucesso à mochila!\n", nome);
                printf("%s\n", LINHA);
                listarItensLista();
            }
            else
            {
                printf("❌ Erro ao adicionar item!\n");
            }
            break;
        }

        case 2:
        {
            printf("\n%s\n", LINHA);
            printf("         ❌ REMOVER ITEM ❌\n");
            printf("%s\n", LINHA);

            if (mochilaLista == NULL)
            {
                printf("⚠️  Sua mochila está vazia! Nada para remover.\n");
                printf("%s\n\n", LINHA);
                break;
            }

            char nome[30];
            printf("Digite o nome do item a remover: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;

            if (removerItemLista(nome))
            {
                printf("✅ Item '%s' encontrado e removido!\n", nome);
                printf("%s\n", LINHA);
                listarItensLista();
            }
            else
            {
                printf("❌ Item '%s' não encontrado na mochila!\n", nome);
                printf("%s\n\n", LINHA);
            }
            break;
        }

        case 3:
            listarItensLista();
            break;

        case 4:
        {
            printf("\n%s\n", LINHA);
            printf("         🔍 BUSCAR ITEM 🔍\n");
            printf("%s\n", LINHA);

            if (mochilaLista == NULL)
            {
                printf("⚠️  Sua mochila está vazia! Nada para buscar.\n");
                printf("%s\n\n", LINHA);
                break;
            }

            char nome[30];
            printf("Digite o nome do item a buscar: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;

            No *resultado = buscarSequencialLista(nome);

            if (resultado != NULL)
            {
                printf("✅ Item encontrado!\n\n");
                printf("📌 Nome: %s\n", resultado->dados.nome);
                printf("🏷️  Tipo: %s\n", resultado->dados.tipo);
                printf("📊 Quantidade: %d\n", resultado->dados.quantidade);
            }
            else
            {
                printf("❌ Item '%s' não encontrado na mochila!\n", nome);
            }

            printf("\n📊 Estatísticas da busca:\n");
            printf("   Comparações realizadas: %d\n", comparacoesSequencialLista);
            printf("   Complexidade: O(n)\n");
            printf("%s\n\n", LINHA);
            break;
        }

        case 5:
            return;

        default:
            printf("❌ Opção inválida! Digite um número entre 1 e 5.\n");
        }
    }
}

/*
 * Função: telaComparacao
 * Descrição: exibe análise comparativa entre vetor e lista encadeada
 * Parâmetros: nenhum
 * Retorno: nenhum
 */
void telaComparacao()
{
    printf("\n%s\n", LINHA);
    printf("   🔬 ANÁLISE COMPARATIVA: VETOR x LISTA 🔬\n");
    printf("%s\n", LINHA);

    printf("\n📊 DADOS COLETADOS:\n");
    printf("   Itens no Vetor: %d/%d\n", totalItensVetor, MAX_ITENS);
    printf("   Itens na Lista: %d/%d\n\n", totalItensLista, MAX_ITENS);

    printf("🔍 OPERAÇÕES DE BUSCA REGISTRADAS:\n");
    printf("   Última busca sequencial (Vetor): %d comparações\n", comparacoesSequencialVetor);
    printf("   Última busca sequencial (Lista): %d comparações\n", comparacoesSequencialLista);

    if (comparacoesBinariaVetor > 0)
    {
        printf("   Última busca binária (Vetor): %d comparações\n", comparacoesBinariaVetor);
    }

    printf("\n%s\n", LINHA);
    printf("   💡 ANÁLISE DETALHADA POR ESTRUTURA\n");
    printf("%s\n", LINHA);

    printf("\n🔷 VETOR (Lista Sequencial):\n");
    printf("   ✅ Pontos positivos:\n");
    printf("      • Acesso direto por índice: O(1)\n");
    printf("      • Busca binária possível: O(log n) ⚡\n");
    printf("      • Cache memory friendly\n");
    printf("      • Implementação simples\n");
    printf("   ❌ Limitações:\n");
    printf("      • Inserção no início: O(n) (requer deslocamento)\n");
    printf("      • Memória fixa: limite de %d itens\n", MAX_ITENS);
    printf("      • Desperdício de memória se não cheio\n");

    printf("\n🔶 LISTA ENCADEADA:\n");
    printf("   ✅ Pontos positivos:\n");
    printf("      • Inserção/remoção no início: O(1) ⚡\n");
    printf("      • Memória dinâmica: cresce conforme necessário\n");
    printf("      • Sem limite de itens (apenas memória)\n");
    printf("      • Sem desperdício de memória\n");
    printf("   ❌ Limitações:\n");
    printf("      • Acesso sequencial obrigatório: O(n)\n");
    printf("      • Sem busca binária direta\n");
    printf("      • Overhead de memória (ponteiros)\n");

    printf("\n%s\n", LINHA);
    printf("   🎯 QUANDO USAR CADA UMA?\n");
    printf("%s\n", LINHA);

    printf("\n📍 Use VETOR quando:\n");
    printf("   • Acesso frequente aos elementos\n");
    printf("   • Quantidade de itens é conhecida e pequena\n");
    printf("   • Performance de busca é crítica\n");
    printf("   • Ordenação será necessária\n");

    printf("\n📍 Use LISTA ENCADEADA quando:\n");
    printf("   • Muitas inserções/remoções no início\n");
    printf("   • Tamanho varia significativamente\n");
    printf("   • Memória é limitada/escassa\n");
    printf("   • Acesso sequencial é suficiente\n");

    printf("\n%s\n", LINHA);
    printf("   📊 RESUMO DO APRENDIZADO\n");
    printf("%s\n\n", LINHA);

    printf("Cada estrutura tem seu propósito:\n");
    printf("➜ VETOR: melhor para LEITURA e BUSCA rápida\n");
    printf("➜ LISTA: melhor para MODIFICAÇÕES dinâmicas\n\n");
}

/*
 * Função: menuPrincipal
 * Descrição: menu principal que permite escolher entre vetor e lista
 * Parâmetros: nenhum
 * Retorno: nenhum
 */
int menuPrincipal()
{
    printf("\n%s\n", LINHA);
    printf("     🎮 SISTEMA DE INVENTÁRIO - FREE FIRE 🎮\n");
    printf("             NÍVEL AVENTUREIRO\n");
    printf("%s\n", LINHA);
    printf("\nEscolha a estrutura de dados para gerenciar sua mochila:\n\n");
    printf("  1️⃣  - Usar VETOR (Lista Sequencial)\n");
    printf("  2️⃣  - Usar LISTA ENCADEADA\n");
    printf("  3️⃣  - Ver análise comparativa\n");
    printf("  4️⃣  - Sair do jogo\n");
    printf("%s\n", LINHA);
    printf("Digite sua opção (1-4): ");

    int opcao;
    scanf("%d", &opcao);
    getchar();

    return opcao;
}

/* ========================================
 * FUNÇÃO PRINCIPAL
 * ======================================== */

int main()
{
    printf("\n╔════════════════════════════════════════════════════╗\n");
    printf("║  BEM-VINDO AO FREE FIRE - NÍVEL AVENTUREIRO 📦    ║\n");
    printf("║     Compare Vetores vs Listas Encadeadas!          ║\n");
    printf("║   Organize seus itens e sobreviva no jogo!         ║\n");
    printf("╚════════════════════════════════════════════════════╝\n");

    int opcao;

    while (1)
    {
        opcao = menuPrincipal();

        switch (opcao)
        {
        case 1:
            menuVetor();
            break;

        case 2:
            menuLista();
            break;

        case 3:
            telaComparacao();
            break;

        case 4:
            printf("\n╔════════════════════════════════════════════════════╗\n");
            printf("║    👋 OBRIGADO POR JOGAR! ATÉ A PRÓXIMA! 👋       ║\n");
            printf("╚════════════════════════════════════════════════════╝\n\n");
            liberarLista();
            return 0;

        default:
            printf("\n❌ Opção inválida! Digite um número entre 1 e 4.\n");
        }
    }

    liberarLista();
    return 0;
}
