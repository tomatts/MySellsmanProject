#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// constante para usar no csv
#define MAX_RAMS 10
#define MAX_CPUS 10

struct ram
{
    char marca[10];
    char modelo[10];
    int capacidade;
    char capacidade_unidade[3];
    int frequência;
    char tipo[10];
    float preco;
};

struct cpu
{
    char marca[10];
    char modelo[30];
    int nucleos[10];
    char socket[10];
    float preco;
};
struct motherboard
{
    char marca[10];
    char modelo[30];
    char formato[10];
    char socket[10];
    char chipset[10];
    float preco;
};

struct gpu
{
    char marca[10];
    char modelo[30];
    char lineup[10];
    float preco;
};

struct storage
{
    char marca[10];
    char modelo[30];
    char tamanho[10];
    char tipo[10];
    float preco;
};

struct psu
{
    char marca[10];
    char modelo[30];
    char potencia[10];
    char formato[10];
    float preco;
};

struct cases
{
    char marca[10];
    char modelo[30];
    char formato[10];
    char tipo[10];
    float preco;
};

// converte a escolha para o tipo enum e identifica com tipo_hardware e pode assumir valores
typedef enum
{
    RAM = 1,
    CPU,
    MOTHER,
    GPU
} tipo_hardware;

// Vetor de ponteiro para char
// static char *nome_hardwares[] = {"RAM", "Processador (CPU)", "Placa Mãe", "Placa Dedicada (GPU)"};

//  configura CSV para ram
int carregar_rams(struct ram rams[], const char *arquivo)

{
    FILE *fp = fopen(arquivo, "r"); //Abre o arquivo em modo de leitura ("r") e guarda o ponteiro em fp.
    if (!fp)//Se não conseguir abrir o arquivo, mostra uma mensagem de erro e retorna 0 (ou seja, nenhuma RAM foi carregada).
    {
        perror("Erro ao abrir o arquivo de RAM");
        return 0;
    }

    int count = 0;
    char linha[256]; //ria uma variável count para contar quantas RAMs foram carregadas e linha para armazenar cada linha lida do arquivo.

    // Ignorar cabeçalho

    fgets(linha, sizeof(linha), fp); //Lê a primeira linha do arquivo (cabeçalho) e descarta, porque não é um dado útil.

    while (fgets(linha, sizeof(linha), fp) && count < MAX_RAMS) // Lê cada linha do arquivo, até o final ou até atingir o limite máximo de RAMs.
    {
        struct ram *r = &rams[count]; // Cria um ponteiro para a próxima posição livre do vetor rams, onde os dados da linha atual serão armazenados.

        //Extrai os dados da linha CSV (separados por vírgula) e coloca dentro da struct RAM.
        sscanf(linha, "%[^,],%[^,],%d,%[^,],%d,%[^,],%f",
               r->marca, r->modelo, &r->capacidade, r->capacidade_unidade,
               &r->frequência, r->tipo, &r->preco);
        count++;
    }

    fclose(fp); //Fecha o arquivo após terminar a leitura.
    return count;
}

// configura CSV para cpu
int carregar_cpus(struct cpu cpus[], const char *arquivo)
{
    {
        FILE *fp = fopen(arquivo, "r");
        if (!fp)
        {
            perror("Erro ao abrir o arquivo de CPU");
            return 0;
        }

        int count = 0;
        char linha[256];

        // Ignorar cabeçalho
        fgets(linha, sizeof(linha), fp);

        while (fgets(linha, sizeof(linha), fp) && count < 10)
        {
            struct cpu *c = &cpus[count];
            sscanf(linha, "%[^,],%[^,],%[^,],%f",
                   c->marca, c->modelo, c->socket, &c->preco);
            count++;
        }

        fclose(fp);
        return count;
    }
}

int main()
{
    // #region Minhas escolhas
    //criação da variavel minha_ram do tipo ram que starta nulo mas declara ponteiro para apontar a opção escolhida no
    struct ram *minha_ram = NULL;
    struct cpu *minha_cpu = NULL;
    // #endregion Minhas escolhas

    // #region RAM pré-definidas
    //  struct ram rams_disponíveis[2] = {
    //      {2, "G", 4444, "DDR4", 149,90},
    //      {4, "G", 3666, "DDR5", 149,90}
    //  };
    // #endregion RAM pré-definidas

    // Implementação do CSV

    // criando uma struct (class em java) de elementos do tipo ram, definido antes, ele vai ter 10 posições definido na constante e esse array se chamará rams_disponvies
    struct ram rams_disponíveis[MAX_RAMS];

    int num_rams = carregar_rams(rams_disponíveis, "rams.csv");

    if (num_rams == 0)
    {
        printf("Nenhuma RAM carregada. Verifique o arquivo CSV.\n");
        return 1;
    }

    struct cpu cpus_disponíveis[MAX_CPUS];
    int num_cpus = carregar_cpus(cpus_disponíveis, "cpus.csv");

    if (num_cpus == 0)
    {
        printf("Nenhuma CPU carregada. Verifique o arquivo CSV.\n");
        return 1;
    }

    // inicializando a variavel que armazena a escolha com RAM
    tipo_hardware hardware_escolha = RAM;
    int escolha_tipo_hardware = 0;

    // #############
    int continuar = 1;

    while (continuar)
    {
        printf("\nMonte seu PC - Menu de Hardware:\n");
        printf("(1) Escolher RAM\n");
        printf("(2) Escolher CPU\n");
        printf("(3) Gerar boleto e sair\n");
        printf("(4) Remover item\n");
        printf("(5) Ver carrinho\n");
        printf("Sua escolha: ");
        scanf("%d", &escolha_tipo_hardware);

        switch (escolha_tipo_hardware)
        {
        case RAM:
        {
            printf("RAMs disponíveis:\n");
            printf("----------------------\n");

            for (int i = 0; i < num_rams; i++)
            {
                printf("Índice: %d\n", i);
                printf("Marca: %s\n", rams_disponíveis[i].marca);
                printf("Modelo: %s\n", rams_disponíveis[i].modelo);
                printf("Capacidade: %d%s\n", rams_disponíveis[i].capacidade, rams_disponíveis[i].capacidade_unidade);
                printf("Frequência: %d MHz\n", rams_disponíveis[i].frequência);
                printf("Tipo: %s\n", rams_disponíveis[i].tipo);
                printf("Preço: R$ %.2f\n", rams_disponíveis[i].preco);
                printf("----------------------\n");
            }

            int ram_escolha = 0;
            printf("Escolha uma memória RAM (0 a %d): ", num_rams - 1);
            scanf("%d", &ram_escolha);

            if (ram_escolha < 0 || ram_escolha >= num_rams)
            {
                printf("RAM inválida.\n");
                break;
            }

            minha_ram = &rams_disponíveis[ram_escolha];

            printf("\nMinha RAM escolhida:\n");
            printf("Marca: %s\n", minha_ram->marca);
            printf("Modelo: %s\n", minha_ram->modelo);
            printf("Capacidade: %d%s\n", minha_ram->capacidade, minha_ram->capacidade_unidade);
            printf("Frequência: %d MHz\n", minha_ram->frequência);
            printf("Tipo: %s\n", minha_ram->tipo);
            printf("Preço: R$ %.2f\n", minha_ram->preco);
        }
        break;

        case CPU:
        {
            printf("CPUs disponíveis:\n");
            printf("----------------------\n");

            for (int i = 0; i < num_cpus; i++)
            {
                printf("Índice: %d\n", i);
                printf("Marca: %s\n", cpus_disponíveis[i].marca);
                printf("Modelo: %s\n", cpus_disponíveis[i].modelo);
                printf("Socket: %s\n", cpus_disponíveis[i].socket);
                printf("Preço: R$ %.2f\n", cpus_disponíveis[i].preco);
                printf("----------------------\n");
            }

            int cpu_escolha = 0;
            printf("Escolha um processador (0 a %d): ", num_cpus - 1);
            scanf("%d", &cpu_escolha);

            if (cpu_escolha < 0 || cpu_escolha >= num_cpus)
            {
                printf("CPU inválida.\n");
                break;
            }

            minha_cpu = &cpus_disponíveis[cpu_escolha];

            printf("\nMinha CPU escolhida:\n");
            printf("Marca: %s\n", minha_cpu->marca);
            printf("Modelo: %s\n", minha_cpu->modelo);
            printf("Socket: %s\n", minha_cpu->socket);
            printf("Preço: R$ %.2f\n", minha_cpu->preco);
        }
        break;

        case 3:
        {
            continuar = 0;

            printf("\n== ITENS SELECIONADOS ATÉ AGORA ==\n");

            if (minha_ram != NULL)
            {
                printf("RAM:\n");
                printf("Marca: %s\n", minha_ram->marca);
                printf("Modelo: %s\n", minha_ram->modelo);
                printf("Capacidade: %d%s\n", minha_ram->capacidade, minha_ram->capacidade_unidade);
                printf("Frequência: %d MHz\n", minha_ram->frequência);
                printf("Tipo: %s\n", minha_ram->tipo);
                printf("Preço: R$ %.2f\n", minha_ram->preco);
                printf("----------------------\n");
            }
            else
            {
                printf("RAM: Nenhuma selecionada.\n");
            }

            if (minha_cpu != NULL)
            {
                printf("CPU:\n");
                printf("Marca: %s\n", minha_cpu->marca);
                printf("Modelo: %s\n", minha_cpu->modelo);
                printf("Socket: %s\n", minha_cpu->socket);
                printf("Preço: R$ %.2f\n", minha_cpu->preco);
                printf("----------------------\n");
            }
            else
            {
                printf("CPU: Nenhuma selecionada.\n");
            }

            // Geração do boleto
            FILE *arquivo = fopen("nota.txt", "w");
            if (!arquivo)
            {
                perror("Erro ao gerar o boleto");
                return 1;
            }

            fprintf(arquivo, "===== BOLETO DE VENDA - MONTE SEU PC =====\n\n");

            if (minha_ram != NULL)
            {
                fprintf(arquivo, "RAM ESCOLHIDA:\n");
                fprintf(arquivo, "Marca: %s\n", minha_ram->marca);
                fprintf(arquivo, "Modelo: %s\n", minha_ram->modelo);
                fprintf(arquivo, "Capacidade: %d%s\n", minha_ram->capacidade, minha_ram->capacidade_unidade);
                fprintf(arquivo, "Frequência: %d MHz\n", minha_ram->frequência);
                fprintf(arquivo, "Tipo: %s\n", minha_ram->tipo);
                fprintf(arquivo, "Preço: R$ %.2f\n\n", minha_ram->preco);
            }

            if (minha_cpu != NULL)
            {
                fprintf(arquivo, "CPU ESCOLHIDA:\n");
                fprintf(arquivo, "Marca: %s\n", minha_cpu->marca);
                fprintf(arquivo, "Modelo: %s\n", minha_cpu->modelo);
                fprintf(arquivo, "Socket: %s\n", minha_cpu->socket);
                fprintf(arquivo, "Preço: R$ %.2f\n\n", minha_cpu->preco);
            }

            float total = 0.0;
            if (minha_ram)
                total += minha_ram->preco;
            if (minha_cpu)
                total += minha_cpu->preco;

            fprintf(arquivo, "------------------------------------------\n");
            fprintf(arquivo, "TOTAL: R$ %.2f\n", total);
            fclose(arquivo);

            printf("\nBoleto gerado com sucesso: nota.txt\n");
        }
        break;

        case 4:
        {
            int remover_opcao = 0;

            printf("\n== REMOVER ITEM SELECIONADO ==\n");
            printf("(1) RAM\n");
            printf("(2) CPU\n");
            printf("(3) Voltar\n");
            printf("Sua escolha: ");
            scanf("%d", &remover_opcao);

            switch (remover_opcao)
            {
            case 1:
                minha_ram = NULL;
                printf("RAM removida da seleção!\n");
                break;
            case 2:
                minha_cpu = NULL;
                printf("CPU removida da seleção!\n");
                break;
            case 3:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida.\n");
                break;
            }
        }
        break;

        case 5:
        {
            printf("\n== ITENS SELECIONADOS ATÉ AGORA ==\n");

            if (minha_ram != NULL)
            {
                printf("RAM:\n");
                printf("Marca: %s\n", minha_ram->marca);
                printf("Modelo: %s\n", minha_ram->modelo);
                printf("Capacidade: %d%s\n", minha_ram->capacidade, minha_ram->capacidade_unidade);
                printf("Frequência: %d MHz\n", minha_ram->frequência);
                printf("Tipo: %s\n", minha_ram->tipo);
                printf("Preço: R$ %.2f\n", minha_ram->preco);
                printf("----------------------\n");
            }
            else
            {
                printf("RAM: Nenhuma selecionada.\n");
            }

            if (minha_cpu != NULL)
            {
                printf("CPU:\n");
                printf("Marca: %s\n", minha_cpu->marca);
                printf("Modelo: %s\n", minha_cpu->modelo);
                printf("Socket: %s\n", minha_cpu->socket);
                printf("Preço: R$ %.2f\n", minha_cpu->preco);
                printf("----------------------\n");
            }
            else
            {
                printf("CPU: Nenhuma selecionada.\n");
            }
        }
        break;

        default:
            printf("Opção inválida. Tente novamente.\n");
            break;
        }
    }
    // GERAÇÃO DE BOLETO DA VENDA
    FILE *arquivo = fopen("nota.txt", "w");

    if (!arquivo)
    {
        perror("Erro ao gerar o boleto");
        return 1;
    }

    fprintf(arquivo, "===== BOLETO DE VENDA - MONTE SEU PC =====\n\n");

    if (minha_ram != NULL)
    {
        fprintf(arquivo, "RAM ESCOLHIDA:\n");
        fprintf(arquivo, "Marca: %s\n", minha_ram->marca);
        fprintf(arquivo, "Modelo: %s\n", minha_ram->modelo);
        fprintf(arquivo, "Capacidade: %d%s\n", minha_ram->capacidade, minha_ram->capacidade_unidade);
        fprintf(arquivo, "Frequência: %d MHz\n", minha_ram->frequência);
        fprintf(arquivo, "Tipo: %s\n", minha_ram->tipo);
        fprintf(arquivo, "Preço: R$ %.2f\n\n", minha_ram->preco);
    }

    if (minha_cpu != NULL)
    {
        fprintf(arquivo, "CPU ESCOLHIDA:\n");
        fprintf(arquivo, "Marca: %s\n", minha_cpu->marca);
        fprintf(arquivo, "Modelo: %s\n", minha_cpu->modelo);
        fprintf(arquivo, "Socket: %s\n", minha_cpu->socket);
        fprintf(arquivo, "Preço: R$ %.2f\n\n", minha_cpu->preco);
    }

    float total = 0.0;
    if (minha_ram)
        total += minha_ram->preco;
    if (minha_cpu)
        total += minha_cpu->preco;

    fprintf(arquivo, "------------------------------------------\n");
    fprintf(arquivo, "TOTAL: R$ %.2f\n", total);

    fclose(arquivo);

    printf("\nBoleto gerado com sucesso: nota.txt\n");
}
