/*
 * ========================================
 * SISTEMA DE INVENTÁRIO - FREE FIRE
 * Nível: Novato
 * ========================================
 *
 * Este programa implementa um sistema de inventário para o jogo Free Fire
 * permitindo que o jogador gerencie seus itens coletados durante a partida.
 *
 * Funcionalidades:
 * - Cadastro de itens (máx 10 itens)
 * - Remoção de itens
 * - Listagem de todos os itens
 * - Busca sequencial por nome
 *
 * Autor: Estrutura de Dados - Nível Novato
 * Data: 2026
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ========================================
 * DEFINIÇÃO DA STRUCT
 * ========================================
 *
 * Struct Item: armazena informações sobre um item do inventário
 * - nome: identificação do item (ex: "Rifle AK")
 * - tipo: categoria do item (ex: "arma", "munição", "cura")
 * - quantidade: número de unidades desse item
 */
typedef struct
{
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

/* ========================================
 * CONSTANTES E VARIÁVEIS GLOBAIS
 * ======================================== */
#define MAX_ITENS 10
#define LINHA "=================================================="

Item mochila[MAX_ITENS]; // Vetor para armazenar até 10 itens
int totalItens = 0;      // Contador de itens atualmente na mochila

/* ========================================
 * FUNÇÃO: listarItens
 * ========================================
 * Descrição: exibe todos os itens registrados na mochila
 * Parâmetros: nenhum
 * Retorno: nenhum
 *
 * Comportamento:
 * - Se não houver items, exibe mensagem informativa
 * - Caso contrário, lista todos com nome, tipo e quantidade
 */
void listarItens()
{
    printf("\n%s\n", LINHA);
    printf("           📦 ITENS DO INVENTÁRIO 📦\n");
    printf("%s\n", LINHA);

    // Verifica se a mochila está vazia
    if (totalItens == 0)
    {
        printf("⚠️  Sua mochila está vazia! Colete itens para começar.\n");
        printf("%s\n\n", LINHA);
        return;
    }

    printf("Total de itens: %d/10\n\n", totalItens);

    // Exibe cabeçalho da tabela
    printf("┌────┬──────────────────────────┬────────────────┬────────────┐\n");
    printf("│ #  │ Nome do Item             │ Tipo           │ Quantidade │\n");
    printf("├────┼──────────────────────────┼────────────────┼────────────┤\n");

    // Percorre e exibe todos os itens em formato tabular
    for (int i = 0; i < totalItens; i++)
    {
        printf("│ %2d │ %-24s │ %-14s │ %10d │\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }

    // Exibe rodapé da tabela
    printf("└────┴──────────────────────────┴────────────────┴────────────┘\n");
    printf("\n");
}

/* ========================================
 * FUNÇÃO: inserirItem
 * ========================================
 * Descrição: cadastra um novo item na mochila
 * Parâmetros: nenhum
 * Retorno: nenhum
 *
 * Comportamento:
 * - Verifica se há espaço disponível (máx 10 itens)
 * - Solicita nome, tipo e quantidade ao jogador
 * - Adiciona o item ao vetor
 */
void inserirItem()
{
    printf("\n%s\n", LINHA);
    printf("         ➕ CADASTRAR NOVO ITEM ➕\n");
    printf("%s\n", LINHA);

    // Verifica se a mochila está cheia
    if (totalItens >= MAX_ITENS)
    {
        printf("❌ Erro: Sua mochila está cheia! Máximo de %d itens.\n", MAX_ITENS);
        printf("   Remova alguns itens antes de adicionar novos.\n");
        printf("%s\n\n", LINHA);
        return;
    }

    // Solicita informações do novo item
    printf("Digite o nome do item: ");
    fgets(mochila[totalItens].nome, sizeof(mochila[totalItens].nome), stdin);
    // Remove a quebra de linha adicionada por fgets
    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = 0;

    printf("Digite o tipo (ex: arma, munição, cura, ferramenta): ");
    fgets(mochila[totalItens].tipo, sizeof(mochila[totalItens].tipo), stdin);
    mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = 0;

    printf("Digite a quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    getchar(); // Limpa o buffer de entrada

    // Valida a quantidade
    if (mochila[totalItens].quantidade <= 0)
    {
        printf("❌ Erro: A quantidade deve ser maior que zero!\n");
        printf("%s\n\n", LINHA);
        return;
    }

    totalItens++;
    printf("✅ Item '%s' adicionado com sucesso à mochila!\n", mochila[totalItens - 1].nome);
    printf("%s\n", LINHA);

    // Exibe a listagem atualizada
    listarItens();
}

/* ========================================
 * FUNÇÃO: removerItem
 * ========================================
 * Descrição: remove um item da mochila pelo nome
 * Parâmetros: nenhum
 * Retorno: nenhum
 *
 * Comportamento:
 * - Solicita o nome do item a remover
 * - Busca sequencialmente o item
 * - Se encontrado, remove mantendo a ordem
 * - Se não encontrado, exibe mensagem de erro
 */
void removerItem()
{
    printf("\n%s\n", LINHA);
    printf("         ❌ REMOVER ITEM ❌\n");
    printf("%s\n", LINHA);

    // Verifica se a mochila está vazia
    if (totalItens == 0)
    {
        printf("⚠️  Sua mochila está vazia! Nada para remover.\n");
        printf("%s\n\n", LINHA);
        return;
    }

    char nomeRemover[30];
    printf("Digite o nome do item a remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = 0;

    // Busca sequencial do item
    int indice = -1;
    for (int i = 0; i < totalItens; i++)
    {
        if (strcmp(mochila[i].nome, nomeRemover) == 0)
        {
            indice = i;
            break;
        }
    }

    // Se encontrou, remove o item
    if (indice != -1)
    {
        printf("✅ Item '%s' encontrado e removido!\n", mochila[indice].nome);

        // Desloca todos os itens posteriores uma posição para frente
        for (int i = indice; i < totalItens - 1; i++)
        {
            mochila[i] = mochila[i + 1];
        }
        totalItens--;
        printf("%s\n", LINHA);

        // Exibe a listagem atualizada
        listarItens();
    }
    else
    {
        printf("❌ Item '%s' não encontrado na mochila!\n", nomeRemover);
        printf("%s\n\n", LINHA);
    }
}

/* ========================================
 * FUNÇÃO: buscarItem
 * ========================================
 * Descrição: realiza busca sequencial de um item pelo nome
 * Parâmetros: nenhum
 * Retorno: nenhum
 *
 * Comportamento:
 * - Solicita o nome do item a buscar
 * - Percorre sequencialmente a mochila
 * - Exibe os dados completos se encontrado
 * - Exibe mensagem de erro se não encontrado
 */
void buscarItem()
{
    printf("\n%s\n", LINHA);
    printf("         🔍 BUSCAR ITEM 🔍\n");
    printf("%s\n", LINHA);

    // Verifica se a mochila está vazia
    if (totalItens == 0)
    {
        printf("⚠️  Sua mochila está vazia! Nada para buscar.\n");
        printf("%s\n\n", LINHA);
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    // Busca sequencial
    int encontrado = 0;
    for (int i = 0; i < totalItens; i++)
    {
        if (strcmp(mochila[i].nome, nomeBusca) == 0)
        {
            printf("✅ Item encontrado!\n\n");
            printf("📌 Nome: %s\n", mochila[i].nome);
            printf("🏷️  Tipo: %s\n", mochila[i].tipo);
            printf("📊 Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("❌ Item '%s' não encontrado na mochila!\n", nomeBusca);
    }
    printf("%s\n\n", LINHA);
}

/* ========================================
 * FUNÇÃO: exibirMenu
 * ========================================
 * Descrição: exibe o menu principal do sistema
 * Parâmetros: nenhum
 * Retorno: int (opção escolhida pelo usuário)
 */
int exibirMenu()
{
    printf("\n%s\n", LINHA);
    printf("     🎮 SISTEMA DE INVENTÁRIO - FREE FIRE 🎮\n");
    printf("%s\n", LINHA);
    printf("Escolha uma opção:\n\n");
    printf("  1️⃣  - Adicionar item à mochila\n");
    printf("  2️⃣  - Remover item da mochila\n");
    printf("  3️⃣  - Listar todos os itens\n");
    printf("  4️⃣  - Buscar item específico\n");
    printf("  5️⃣  - Sair do jogo\n");
    printf("%s\n", LINHA);
    printf("Digite sua opção (1-5): ");

    int opcao;
    scanf("%d", &opcao);
    getchar(); // Limpa o buffer de entrada

    return opcao;
}

/* ========================================
 * FUNÇÃO: main
 * ========================================
 * Descrição: função principal do programa
 * Comportamento:
 * - Exibe menu até que o usuário escolha sair
 * - Executa ação correspondente à opção
 * - Valida entrada do usuário
 */
int main()
{
    int opcao;

    printf("\n╔════════════════════════════════════════════════════╗\n");
    printf("║     BEM-VINDO AO SISTEMA DE INVENTÁRIO 📦         ║\n");
    printf("║     Organize seus itens e sobreviva no jogo!       ║\n");
    printf("╚════════════════════════════════════════════════════╝\n");

    // Loop principal do programa
    while (1)
    {
        opcao = exibirMenu();

        switch (opcao)
        {
        case 1:
            inserirItem();
            break;
        case 2:
            removerItem();
            break;
        case 3:
            listarItens();
            break;
        case 4:
            buscarItem();
            break;
        case 5:
            printf("\n👋 Obrigado por jogar! Até a próxima!\n");
            printf("════════════════════════════════════════════════════\n\n");
            return 0;
        default:
            printf("\n❌ Opção inválida! Digite um número entre 1 e 5.\n");
        }
    }

    return 0;
}
