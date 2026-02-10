/*
 * ========================================
 * SISTEMA DE MONTAGEM DE TORRE - FREE FIRE
 * Nível: MESTRE
 * ========================================
 *
 * Este é o DESAFIO FINAL do Free Fire!
 *
 * Você chegou ao momento decisivo: a última safe zone está se fechando
 * e precisa montar uma TORRE DE RESGATE com componentes na ordem exata.
 *
 * Funcionalidades:
 * - Cadastro de até 20 componentes para a torre
 * - 3 Algoritmos de ORDENAÇÃO diferentes:
 *   → Bubble Sort (ordena por NOME)
 *   → Insertion Sort (ordena por TIPO)
 *   → Selection Sort (ordena por PRIORIDADE)
 * - Busca binária para encontrar componente-chave
 * - Medição de desempenho (comparações e tempo)
 * - Análise comparativa de algoritmos
 *
 * Autor: Estrutura de Dados - Nível Mestre
 * Data: 2026
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* ========================================
 * DEFINIÇÃO DE STRUCTS
 * ======================================== */

typedef struct
{
    char nome[30];
    char tipo[20];
    int prioridade; // 1 a 10
    int quantidade; // quantidade do componente
} Componente;

/* ========================================
 * CONSTANTES E VARIÁVEIS GLOBAIS
 * ======================================== */

#define MAX_COMPONENTES 20
#define LINHA "=================================================="

Componente torre[MAX_COMPONENTES];
int totalComponentes = 0;

// Contadores de comparações para análise de desempenho
int comparacoesBubble = 0;
int comparacoesInsertion = 0;
int comparacoesSelection = 0;

// Flags para controlar estado da ordenação
int ordenadoPorNome = 0;
int ordenadoPorTipo = 0;
int ordenadoPorPrioridade = 0;

/* ========================================
 * FUNÇÕES AUXILIARES
 * ======================================== */

/*
 * Função: copiarComponentes
 * Descrição: copia os componentes para um vetor temporário
 * Parâmetros: vetor origem
 * Retorno: vetor cópia
 *
 * Importante: usado para não modificar dados originais
 */
Componente *copiarComponentes(Componente src[])
{
    Componente *copia = (Componente *)malloc(totalComponentes * sizeof(Componente));
    for (int i = 0; i < totalComponentes; i++)
    {
        copia[i] = src[i];
    }
    return copia;
}

/*
 * Função: trocar
 * Descrição: troca dois componentes de posição
 * Parâmetros: dois ponteiros para Componente
 * Retorno: nenhum
 */
void trocar(Componente *a, Componente *b)
{
    Componente temp = *a;
    *a = *b;
    *b = temp;
}

/* ========================================
 * OPERAÇÕES BÁSICAS
 * ======================================== */

/*
 * Função: adicionarComponente
 * Descrição: adiciona um novo componente à torre
 * Parâmetros: nenhum
 * Retorno: nenhum
 */
void adicionarComponente()
{
    printf("\n%s\n", LINHA);
    printf("      ➕ ADICIONAR COMPONENTE À TORRE ➕\n");
    printf("%s\n", LINHA);

    if (totalComponentes >= MAX_COMPONENTES)
    {
        printf("❌ Erro: Torre cheia! Máximo de %d componentes.\n", MAX_COMPONENTES);
        printf("%s\n\n", LINHA);
        return;
    }

    printf("Digite o nome do componente: ");
    fgets(torre[totalComponentes].nome, sizeof(torre[totalComponentes].nome), stdin);
    torre[totalComponentes].nome[strcspn(torre[totalComponentes].nome, "\n")] = 0;

    printf("Digite o tipo (controle/suporte/propulsão/etc): ");
    fgets(torre[totalComponentes].tipo, sizeof(torre[totalComponentes].tipo), stdin);
    torre[totalComponentes].tipo[strcspn(torre[totalComponentes].tipo, "\n")] = 0;

    printf("Digite a prioridade (1-10): ");
    scanf("%d", &torre[totalComponentes].prioridade);
    getchar();

    printf("Digite a quantidade: ");
    scanf("%d", &torre[totalComponentes].quantidade);
    getchar();

    if (torre[totalComponentes].prioridade < 1 || torre[totalComponentes].prioridade > 10)
    {
        printf("❌ Erro: Prioridade deve estar entre 1 e 10!\n");
        printf("%s\n\n", LINHA);
        return;
    }

    if (torre[totalComponentes].quantidade <= 0)
    {
        printf("❌ Erro: A quantidade deve ser maior que zero!\n");
        printf("%s\n\n", LINHA);
        return;
    }

    totalComponentes++;
    printf("✅ Componente '%s' adicionado com sucesso à torre!\n", torre[totalComponentes - 1].nome);
    printf("%s\n", LINHA);

    // Reseta flags de ordenação
    ordenadoPorNome = 0;
    ordenadoPorTipo = 0;
    ordenadoPorPrioridade = 0;

    // Exibe a listagem atualizada
    listarComponentes();
}

/*
 * Função: removerComponente
 * Descrição: remove um componente pelo nome
 * Parâmetros: nenhum
 * Retorno: nenhum
 */
void removerComponente()
{
    printf("\n%s\n", LINHA);
    printf("      ❌ REMOVER COMPONENTE ❌\n");
    printf("%s\n", LINHA);

    if (totalComponentes == 0)
    {
        printf("⚠️  Torre vazia! Nada para remover.\n");
        printf("%s\n\n", LINHA);
        return;
    }

    char nome[30];
    printf("Nome do componente a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    int indice = -1;
    for (int i = 0; i < totalComponentes; i++)
    {
        if (strcmp(torre[i].nome, nome) == 0)
        {
            indice = i;
            break;
        }
    }

    if (indice != -1)
    {
        printf("✅ Componente '%s' removido!\n", nome);

        for (int i = indice; i < totalComponentes - 1; i++)
        {
            torre[i] = torre[i + 1];
        }
        totalComponentes--;
        printf("%s\n", LINHA);

        listarComponentes();

        // Reseta flags de ordenação
        ordenadoPorNome = 0;
        ordenadoPorTipo = 0;
        ordenadoPorPrioridade = 0;
    }
    else
    {
        printf("❌ Componente '%s' não encontrado!\n", nome);
        printf("%s\n\n", LINHA);
    }
}

/*
 * Função: listarComponentes
 * Descrição: exibe todos os componentes em formato tabular
 * Parâmetros: nenhum
 * Retorno: nenhum
 */
void listarComponentes()
{
    printf("\n%s\n", LINHA);
    printf("      📦 COMPONENTES DA TORRE 📦\n");
    printf("%s\n", LINHA);

    if (totalComponentes == 0)
    {
        printf("⚠️  Torre vazia! Adicione componentes para começar.\n");
        printf("%s\n\n", LINHA);
        return;
    }

    printf("Total de componentes: %d/%d\n\n", totalComponentes, MAX_COMPONENTES);

    printf("┌────┬──────────────────────────┬─────────────┬────────────┬────────────┐\n");
    printf("│ #  │ Nome                     │ Tipo        │ Prioridade │ Quantidade │\n");
    printf("├────┼──────────────────────────┼─────────────┼────────────┼────────────┤\n");

    for (int i = 0; i < totalComponentes; i++)
    {
        printf("│ %2d │ %-24s  │ %-11s   │ %10d  │ %10d  │\n",
               i + 1,
               torre[i].nome,
               torre[i].tipo,
               torre[i].prioridade,
               torre[i].quantidade);
    }

    printf("└────┴──────────────────────────┴─────────────┴────────────┴────────────┘\n\n");
}

/* ========================================
 * ALGORITMOS DE ORDENAÇÃO COM CONTADORES
 * ======================================== */

/*
 * Função: bubbleSortNome
 * Descrição: ordena componentes por NAME usando Bubble Sort
 * Parâmetros: nenhum
 * Retorno: nenhum
 *
 * Complexidade: O(n²)
 * Melhor caso: O(n) - já ordenado
 * Pior caso: O(n²) - ordem reversa
 *
 * Como funciona:
 * - Compara elementos adjacentes
 * - Troca se estiverem na ordem errada
 * - Repete até não haver mais trocas
 */
void bubbleSortNome()
{
    comparacoesBubble = 0;
    int trocas = 1;

    printf("\n⏳ Executando BUBBLE SORT por NOME...\n");

    // Bubble sort com otimização (pare se não houver trocas)
    for (int i = 0; i < totalComponentes - 1 && trocas; i++)
    {
        trocas = 0;

        for (int j = 0; j < totalComponentes - i - 1; j++)
        {
            comparacoesBubble++;

            // Compara nomes
            if (strcmp(torre[j].nome, torre[j + 1].nome) > 0)
            {
                trocar(&torre[j], &torre[j + 1]);
                trocas = 1;
            }
        }
    }

    ordenadoPorNome = 1;
    printf("✅ Bubble Sort concluído!\n");
}

/*
 * Função: insertionSortTipo
 * Descrição: ordena componentes por TIPO usando Insertion Sort
 * Parâmetros: nenhum
 * Retorno: nenhum
 *
 * Complexidade: O(n²)
 * Melhor caso: O(n) - já ordenado
 * Pior caso: O(n²) - ordem reversa
 *
 * Como funciona:
 * - Percorre cada elemento
 * - Insere na posição correta entre os anteriores
 * - Eficiente para poucos elementos
 */
void insertionSortTipo()
{
    comparacoesInsertion = 0;

    printf("\n⏳ Executando INSERTION SORT por TIPO...\n");

    for (int i = 1; i < totalComponentes; i++)
    {
        Componente chave = torre[i];
        int j = i - 1;

        // Move elementos maiores uma posição adiante
        while (j >= 0 && strcmp(torre[j].tipo, chave.tipo) > 0)
        {
            comparacoesInsertion++;
            torre[j + 1] = torre[j];
            j--;
        }

        if (j >= 0)
            comparacoesInsertion++;

        torre[j + 1] = chave;
    }

    ordenadoPorTipo = 1;
    printf("✅ Insertion Sort concluído!\n");
}

/*
 * Função: selectionSortPrioridade
 * Descrição: ordena componentes por PRIORIDADE usando Selection Sort
 * Parâmetros: nenhum
 * Retorno: nenhum
 *
 * Complexidade: O(n²) - sempre
 *
 * Como funciona:
 * - Encontra o elemento máximo
 * - Coloca na posição correta
 * - Repete para o restante
 * - Ordena em ordem DECRESCENTE de prioridade
 */
void selectionSortPrioridade()
{
    comparacoesSelection = 0;

    printf("\n⏳ Executando SELECTION SORT por PRIORIDADE...\n");

    for (int i = 0; i < totalComponentes - 1; i++)
    {
        int maiorIndice = i;

        // Encontra o componente com MAIOR prioridade
        for (int j = i + 1; j < totalComponentes; j++)
        {
            comparacoesSelection++;

            if (torre[j].prioridade > torre[maiorIndice].prioridade)
            {
                maiorIndice = j;
            }
        }

        if (maiorIndice != i)
        {
            trocar(&torre[i], &torre[maiorIndice]);
        }
    }

    ordenadoPorPrioridade = 1;
    printf("✅ Selection Sort concluído!\n");
}

/* ========================================
 * BUSCA BINÁRIA
 * ======================================== */

/*
 * Função: buscaBinariaPorNome
 * Descrição: busca componente por nome (requer ordenação)
 * Parâmetros: nenhum
 * Retorno: nenhum
 *
 * Complexidade: O(log n)
 * Precondição: dados devem estar ordenados por nome
 *
 * Como funciona:
 * - Divide o espaço de busca pela metade a cada comparação
 * - MUITO mais rápido que busca sequencial para muitos dados
 */
void buscaBinariaPorNome()
{
    printf("\n%s\n", LINHA);
    printf("      🔦 BUSCA BINÁRIA POR NOME 🔦\n");
    printf("%s\n", LINHA);

    if (totalComponentes == 0)
    {
        printf("⚠️  Torre vazia!\n");
        printf("%s\n\n", LINHA);
        return;
    }

    if (!ordenadoPorNome)
    {
        printf("⚠️  ATENÇÃO: Os componentes devem estar ORDENADOS POR NOME!\n");
        printf("   Use a opção 'Ordenar por Nome (Bubble Sort)' primeiro.\n");
        printf("%s\n\n", LINHA);
        return;
    }

    char nome[30];
    printf("Digite o nome do componente a buscar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    int comparacoes = 0;
    int esquerda = 0;
    int direita = totalComponentes - 1;
    int encontrado = -1;

    while (esquerda <= direita)
    {
        comparacoes++;
        int meio = (esquerda + direita) / 2;
        int resultado = strcmp(torre[meio].nome, nome);

        if (resultado == 0)
        {
            encontrado = meio;
            break;
        }
        else if (resultado < 0)
        {
            esquerda = meio + 1;
        }
        else
        {
            direita = meio - 1;
        }
    }

    if (encontrado != -1)
    {
        printf("\n✅ COMPONENTE ENCONTRADO! ⚡\n\n");
        printf("📌 Nome: %s\n", torre[encontrado].nome);
        printf("🏷️  Tipo: %s\n", torre[encontrado].tipo);
        printf("⭐ Prioridade: %d\n", torre[encontrado].prioridade);
        printf("📊 Quantidade: %d\n", torre[encontrado].quantidade);

        // Simula ativação
        if (strcmp(torre[encontrado].nome, "chip central") == 0 ||
            strcmp(torre[encontrado].nome, "cristal energético") == 0 ||
            strcmp(torre[encontrado].nome, "núcleo de controle") == 0)
        {
            printf("\n🚀 Este é um componente-CHAVE! Pode ativar a torre!\n");
        }
    }
    else
    {
        printf("\n❌ Componente '%s' não encontrado!\n", nome);
    }

    printf("\n📊 Estatísticas da busca:\n");
    printf("   Comparações realizadas: %d\n", comparacoes);
    printf("   Complexidade: O(log n) ⚡\n");

    // Cálculo teórico
    int comparacoesTeoricas = 0;
    int temp = totalComponentes;
    while (temp > 1)
    {
        temp /= 2;
        comparacoesTeoricas++;
    }
    printf("   Máx comparações teóricas: ~%d\n", comparacoesTeoricas);
    printf("%s\n\n", LINHA);
}

/* ========================================
 * MENUS DE ORDENAÇÃO
 * ======================================== */

/*
 * Função: menuOrdenacao
 * Descrição: apresenta opções de ordenação com análise de desempenho
 * Parâmetros: nenhum
 * Retorno: nenhum
 */
void menuOrdenacao()
{
    int opcao;

    while (1)
    {
        printf("\n%s\n", LINHA);
        printf("      ⬆️ ESCOLHA UM ALGORITMO DE ORDENAÇÃO ⬆️\n");
        printf("%s\n", LINHA);
        printf("Escolha uma opção:\n\n");
        printf("  1️⃣  - BUBBLE SORT (ordena por NOME)\n");
        printf("  2️⃣  - INSERTION SORT (ordena por TIPO)\n");
        printf("  3️⃣  - SELECTION SORT (ordena por PRIORIDADE)\n");
        printf("  4️⃣  - Comparar os 3 algoritmos\n");
        printf("  5️⃣  - Voltar ao menu principal\n");
        printf("%s\n", LINHA);
        printf("Digite sua opção (1-5): ");
        scanf("%d", &opcao);
        getchar();

        clock_t inicio, fim;
        double tempo;

        switch (opcao)
        {
        case 1:
            if (totalComponentes == 0)
            {
                printf("\n⚠️  Torre vazia!\n");
                break;
            }

            printf("\n%s\n", LINHA);
            printf("     🔄 BUBBLE SORT - ORDENANDO POR NOME\n");
            printf("%s\n", LINHA);

            inicio = clock();
            bubbleSortNome();
            fim = clock();
            tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

            printf("\n📊 DESEMPENHO DO BUBBLE SORT:\n");
            printf("   Comparações: %d\n", comparacoesBubble);
            printf("   Tempo: %.6f segundos\n", tempo);
            printf("   Complexidade: O(n²)\n");
            printf("%s\n", LINHA);

            listarComponentes();
            break;

        case 2:
            if (totalComponentes == 0)
            {
                printf("\n⚠️  Torre vazia!\n");
                break;
            }

            printf("\n%s\n", LINHA);
            printf("    🔄 INSERTION SORT - ORDENANDO POR TIPO\n");
            printf("%s\n", LINHA);

            inicio = clock();
            insertionSortTipo();
            fim = clock();
            tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

            printf("\n📊 DESEMPENHO DO INSERTION SORT:\n");
            printf("   Comparações: %d\n", comparacoesInsertion);
            printf("   Tempo: %.6f segundos\n", tempo);
            printf("   Complexidade: O(n²)\n");
            printf("%s\n", LINHA);

            listarComponentes();
            break;

        case 3:
            if (totalComponentes == 0)
            {
                printf("\n⚠️  Torre vazia!\n");
                break;
            }

            printf("\n%s\n", LINHA);
            printf("   🔄 SELECTION SORT - ORDENANDO POR PRIORIDADE\n");
            printf("%s\n", LINHA);

            inicio = clock();
            selectionSortPrioridade();
            fim = clock();
            tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

            printf("\n📊 DESEMPENHO DO SELECTION SORT:\n");
            printf("   Comparações: %d\n", comparacoesSelection);
            printf("   Tempo: %.6f segundos\n", tempo);
            printf("   Complexidade: O(n²)\n");
            printf("%s\n", LINHA);

            listarComponentes();
            break;

        case 4:
        {
            if (totalComponentes == 0)
            {
                printf("\n⚠️  Torre vazia!\n");
                break;
            }

            printf("\n%s\n", LINHA);
            printf("   📈 COMPARAÇÃO DOS 3 ALGORITMOS 📈\n");
            printf("%s\n", LINHA);

            // Copia dados 3 vezes
            Componente *copia1 = copiarComponentes(torre);
            Componente *copia2 = copiarComponentes(torre);
            Componente *copia3 = copiarComponentes(torre);

            // Executa cada algoritmo
            printf("\n⏳ Executando BUBBLE SORT...\n");
            inicio = clock();
            comparacoesBubble = 0;
            int tempTrocas = 1;
            for (int i = 0; i < totalComponentes - 1 && tempTrocas; i++)
            {
                tempTrocas = 0;
                for (int j = 0; j < totalComponentes - i - 1; j++)
                {
                    comparacoesBubble++;
                    if (strcmp(copia1[j].nome, copia1[j + 1].nome) > 0)
                    {
                        trocar(&copia1[j], &copia1[j + 1]);
                        tempTrocas = 1;
                    }
                }
            }
            fim = clock();
            double tempoBubble = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

            printf("⏳ Executando INSERTION SORT...\n");
            inicio = clock();
            comparacoesInsertion = 0;
            for (int i = 1; i < totalComponentes; i++)
            {
                Componente chave = copia2[i];
                int j = i - 1;
                while (j >= 0 && strcmp(copia2[j].tipo, chave.tipo) > 0)
                {
                    comparacoesInsertion++;
                    copia2[j + 1] = copia2[j];
                    j--;
                }
                if (j >= 0)
                    comparacoesInsertion++;
                copia2[j + 1] = chave;
            }
            fim = clock();
            double tempoInsertion = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

            printf("⏳ Executando SELECTION SORT...\n");
            inicio = clock();
            comparacoesSelection = 0;
            for (int i = 0; i < totalComponentes - 1; i++)
            {
                int maiorIndice = i;
                for (int j = i + 1; j < totalComponentes; j++)
                {
                    comparacoesSelection++;
                    if (copia3[j].prioridade > copia3[maiorIndice].prioridade)
                    {
                        maiorIndice = j;
                    }
                }
                if (maiorIndice != i)
                {
                    trocar(&copia3[i], &copia3[maiorIndice]);
                }
            }
            fim = clock();
            double tempoSelection = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

            // Exibe resultados
            printf("\n%s\n", LINHA);
            printf("   📊 RESULTADOS COMPARATIVOS\n");
            printf("%s\n", LINHA);

            printf("\n1️⃣  BUBBLE SORT (por Nome):\n");
            printf("   Comparações: %d\n", comparacoesBubble);
            printf("   Tempo: %.6f segundos\n", tempoBubble);

            printf("\n2️⃣  INSERTION SORT (por Tipo):\n");
            printf("   Comparações: %d\n", comparacoesInsertion);
            printf("   Tempo: %.6f segundos\n", tempoInsertion);

            printf("\n3️⃣  SELECTION SORT (por Prioridade):\n");
            printf("   Comparações: %d\n", comparacoesSelection);
            printf("   Tempo: %.6f segundos\n", tempoSelection);

            printf("\n%s\n", LINHA);
            printf("   💡 ANÁLISE\n");
            printf("%s\n", LINHA);

            if (totalComponentes <= 5)
            {
                printf("\nPara %d componentes:\n", totalComponentes);
                printf("✓ Todos os algoritmos são RÁPIDOS\n");
                printf("✓ Diferenças de tempo são negligenciáveis\n");
            }
            else
            {
                printf("\nPara %d componentes:\n", totalComponentes);

                if (comparacoesBubble > comparacoesInsertion)
                {
                    printf("🏆 INSERTION SORT é mais eficiente que Bubble Sort\n");
                    printf("   Economia: %d comparações\n", comparacoesBubble - comparacoesInsertion);
                }

                if (comparacoesSelection < comparacoesBubble)
                {
                    printf("🏆 SELECTION SORT é competitivo\n");
                }
            }

            printf("\n📌 CONCLUSÃO EDUCACIONAL:\n");
            printf("✓ O(n²) é aceitável para dados pequenos (<100)\n");
            printf("✓ Para dados maiores, use O(n log n) (Quick/Merge/Heap Sort)\n");
            printf("✓ Insertion Sort: melhor para dados quase ordenados\n");
            printf("✓ Selection Sort: número fixo de iterações\n");

            printf("%s\n", LINHA);

            free(copia1);
            free(copia2);
            free(copia3);
            break;
        }

        case 5:
            return;

        default:
            printf("❌ Opção inválida!\n");
        }
    }
}

/* ========================================
 * MENU PRINCIPAL
 * ======================================== */

int menuPrincipal()
{
    printf("\n%s\n", LINHA);
    printf("    🎮 TORRE DE FUGA - SISTEMA DE MONTAGEM 🎮\n");
    printf("             NÍVEL MESTRE\n");
    printf("%s\n", LINHA);
    printf("\nOrganize os componentes para escapar da ilha:\n\n");
    printf("  1️⃣  - Adicionar componente\n");
    printf("  2️⃣  - Remover componente\n");
    printf("  3️⃣  - Listar componentes\n");
    printf("  4️⃣  - Ordenar componentes\n");
    printf("  5️⃣  - Buscar componente-chave (binária)\n");
    printf("  6️⃣  - Sair do jogo\n");
    printf("%s\n", LINHA);
    printf("Digite sua opção (1-6): ");

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
    printf("║      BEM-VINDO AO FREE FIRE - NÍVEL MESTRE 🏆    ║\n");
    printf("║  Construa a torre de fuga com os componentes!     ║\n");
    printf("║  Escolha a estratégia certa para sobreviver!      ║\n");
    printf("╚════════════════════════════════════════════════════╝\n");

    int opcao;

    while (1)
    {
        opcao = menuPrincipal();

        switch (opcao)
        {
        case 1:
            adicionarComponente();
            break;

        case 2:
            removerComponente();
            break;

        case 3:
            listarComponentes();
            break;

        case 4:
            menuOrdenacao();
            break;

        case 5:
            buscaBinariaPorNome();
            break;

        case 6:
            printf("\n╔════════════════════════════════════════════════════╗\n");
            printf("║    👋 OBRIGADO POR JOGAR! VOCÊ ESCAPOU! 🚀👋       ║\n");
            printf("╚════════════════════════════════════════════════════╝\n\n");
            return 0;

        default:
            printf("\n❌ Opção inválida! Digite um número entre 1 e 6.\n");
        }
    }

    return 0;
}
