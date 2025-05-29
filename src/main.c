#include <stdlib.h>
#include <stdio.h>

struct ram
{
    int capacidade;
    char * capacidade_unidade;
    int frequência;
    char * tipo;
};

struct cpu
{
    char marca[2];
    char modelo[2];
    int nucleos[5];
    char socket[3];

};
struct motherboard
{
    char marca[2];
    char modelo[5];
    char formato[4];
    char socket[3];
    char chipset[6];
};

struct gpu
{
    char marca[3];
    char modelo[5];
    char lineup[25];
};


typedef enum { RAM = 1, CPU, MOTHER, GPU } tipo_hardware;

static char* nome_hardwares[] = { "RAM", "Processador (CPU)", "Placa Mãe", "Placa Dedicada (GPU)" };

int main() {
    //#region Minhas escolhas
    struct ram * minha_ram;
    //#endregion Minhas escolhas

    //#region RAM pré-definidas
    struct ram rams_disponíveis[2] = {
        {2, "G", 4444, "DDR4"},
        {4, "G", 3666, "DDR5"}
    };
    //#endregion RAM pré-definidas

    tipo_hardware hardware_escolha = RAM;
    int escolha_tipo_hardware = 0;

    printf("Monte seu PC!\n");
    printf("Escolha o hardware: ");
    printf("(1) RAM, (2) Processador [CPU], (3) Placa Mãe, (4) Placa Dedicada [GPU]\n");
    printf("Sua escolha: ");

    scanf("%d", &escolha_tipo_hardware);

    if (escolha_tipo_hardware < RAM || escolha_tipo_hardware > GPU) {
        printf("Escolha inválida, por favor escolha entre tipos de hardware 1 até 4\n");
        return 1;
    }

    escolha_tipo_hardware = (tipo_hardware)escolha_tipo_hardware;

    switch (escolha_tipo_hardware)
    {
    case RAM: {
        printf("RAMs disponíveis:\n");

        printf("----------------------\n");

        for (size_t i = 0; i < 2; i++)
        {
            printf("Índice: %d\n", i);
            printf("Capacidade: %d%s\n", rams_disponíveis[i].capacidade, rams_disponíveis[i].capacidade_unidade);
            printf("Frequência: %d\n", rams_disponíveis[i].frequência);
            printf("Tipo: %s\n", rams_disponíveis[i].tipo);
            printf("----------------------\n");
        }

        printf("----------------------\n");

        int ram_escolha = 0;
        printf("Escolha uma memória RAM: ");
        scanf("%d", &ram_escolha);

        minha_ram = &rams_disponíveis[ram_escolha];

        printf("Minha RAM:\n");
        printf("Capacidade: %d\n", minha_ram->capacidade);
        printf("Capacidade unidade: %s\n", minha_ram->capacidade_unidade);
        printf("Frequência: %d\n", minha_ram->frequência);
        printf("Tipo: %s\n", minha_ram->tipo);

            // printf("Sua escolha foi: %s", nome_hardwares[escolha_tipo_hardware - 1]);
    } break;
    default:
        printf("Escolha ainda não disponível.\n");
        return 1;
    }

    printf("\n");

    return 0;
}