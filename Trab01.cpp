#include <iostream>
#include <windows.h>
#include <fstream>
#include <string.h>
#include "Listas.cpp"

using namespace std;

int main()
{
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    TListaEncadeada listaE;
    TListaSequencial listaS;
    CriaListaVaziaEncadeada(&listaE);

    //Lendo do arquivo
    FILE *arquivo;
    TFuncionario fun;
    TApontador y = listaE.Primeiro;
    
    arquivo = fopen("funcionarios.bin", "rb");
    if (arquivo != NULL)
    {
        while (fread(&fun, sizeof(TFuncionario), 1, arquivo))
        {
            InsereEncadeada(fun, &listaE);
        }
        fclose(arquivo);
    }
    else
    {
        cout << "Arquivo vazio!!";
        system("pause");
    }

    int opcao;

    do
    {
        menu();
        cout << "Escolha a opção: ";
        cin >> opcao;
        system("cls");
        switch (opcao)
        {
        case 1:
            CadastraFuncionario(&listaE);
            break;
        case 2:
            CadastraProjetos(&listaE);
            break;
        case 3:
            ExcluiProjetos(&listaE);
            break;
        case 4:
            ExcluiFuncionario(&listaE);
            break;
        case 5:
            ConsultaFuncionario(&listaE);
            break;
        case 6:
            ImprimiContraCheque(&listaE);
            system("pause");
            system("cls");
            break;
        }
    } while (opcao != 7);

    //Gravando no arquivo
    arquivo = fopen("funcionarios.bin", "wb");

    while (y->prox != NULL)
    {
        fun = y->prox->item;
        fwrite(&fun, sizeof(TFuncionario), 1, arquivo);
        y = y->prox;
    }

    fclose(arquivo);

    system("pause");
    return 0;
}
