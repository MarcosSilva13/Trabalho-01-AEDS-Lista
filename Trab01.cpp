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
  
  int opcao;

  do
  {
    menu();
    cout << "Escolha a opção: ";
    cin >> opcao;
    system("cls");
    switch(opcao) {
        case 1:
            CadastraFuncionario(&listaE);
            break;
        case 2:
            CadastraProjetos(&listaE);
            break;
        case 3:
            //função
            break;
        case 4:
            ExcluiFuncionario(&listaE);
            break;
        case 5:
            ConsultaFuncionario(&listaE);
            break;
        case 6:
            //função
            break;
    }
  } while (opcao != 7);

  system("pause");
  return 0;
}

