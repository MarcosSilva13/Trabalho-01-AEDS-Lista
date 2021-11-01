#include <iostream>
#include <windows.h>
#include "Listas.hpp"

using namespace std;

void menu()
{
  system("color 0B");
  cout << "  \n        ����������������������������������������������������������������";
  cout << "  \n        �                                                              �";
  cout << "  \n        �                     DEPARTAMENTO PESSOAL                     �";
  cout << "  \n        �                                                              �";
  cout << "  \n        ����������������������������������������������������������������";
  cout << "  \n        �                                                              �";
  cout << "  \n        � 1 - INCLUIR NOVO FUNCIONÁRIO                                 �";
  cout << "  \n        �                                                              �";
  cout << "  \n        � 2 - INCLUIR NOVOS PROJETOS                                   �";
  cout << "  \n        �                                                              �";
  cout << "  \n        � 3 - EXCLUIR PROJETOS                                         �";
  cout << "  \n        �                                                              �";
  cout << "  \n        � 4 - EXCLUIR FUNCIONARIOS SEM PROJETO                         �";
  cout << "  \n        �                                                              �";
  cout << "  \n        � 5 - CONSULTAR FUNCIONARIO                                    �";
  cout << "  \n        �                                                              �";
  cout << "  \n        � 6 - IMPRIMIR CONTRA-CHEQUE                                   �";
  cout << "  \n        �                                                              �";
  cout << "  \n        � 7 - SAIR                                                     �";
  cout << "  \n        �                                                              �";
  cout << "  \n        ����������������������������������������������������������������\n\n";
}

void CriaListaVaziaEncadeada(TListaEncadeada *listaE){
    listaE->Primeiro = new TCelula;
    listaE->Ultimo = listaE->Primeiro;
    listaE->Primeiro->prox = NULL;
}

int VerificaListaVaziaE(TListaEncadeada listaE){
    return(listaE.Primeiro == listaE.Ultimo);
}

void InsereEncadeada(TFuncionario fun, TListaEncadeada *listaE){
    listaE->Ultimo->prox = new TCelula;
    listaE->Ultimo = listaE->Ultimo->prox;
    listaE->Ultimo->item = fun;
    listaE->Ultimo->prox = NULL;
}

void CriaListaVaziaSequencial(TListaSequencial &listaS){
    listaS.primeiro = INICIO;
    listaS.ultimo = listaS.primeiro;
}

int VerificaListaVaziaS(TListaSequencial listaS){
    if(listaS.ultimo == 0){
        return 1;
    }else{
        return 0;
    }
}

void InsereSequencial(TProjeto proj, TListaSequencial &listaS){
    if(listaS.ultimo == MAXTAM){
        cout << "Lista Cheia!\n";
        Sleep(1000);
    } else {
        listaS.item[listaS.ultimo] = proj;
        listaS.ultimo++;
    }
}

void CadastraFuncionario(TListaEncadeada *listaE){
    TFuncionario fun;
    int op;
    cout << "*******************************************\n";
    cout << "*        CADASTRO DE FUNCIONÁRIO          *\n";
    cout << "*******************************************\n\n";
    cout << "Codigo: ";
    cin >> fun.numero;
    cin.ignore();
    cout << "Nome: ";
    gets(fun.nome);
    cout << "Endereço: ";
    gets (fun.endereco);
    cout << "Numero de Dependentes: ";
    cin >> fun.dependentes;

    //inserindo na lista encadeada os funcionarios
    InsereEncadeada(fun, listaE);

    cout << "\nFuncionário cadastrado com sucesso!\n\n";
    Sleep(1000);
    system("cls");   
}

int Pesquisa(TChave cod, TListaEncadeada listaE, TApontador *p){
    TApontador aux = listaE.Primeiro;
    while(aux->prox != NULL){
      if(aux->prox->item.numero == cod){
          *p = aux;
          return 1;
      } else {
        aux = aux->prox;
        *p = aux;
      }
    }
    return 0;
}

void ConsultaFuncionario(TListaEncadeada *listaE, TListaSequencial listaS){
    TChave cod;
    TApontador p;
    int ret;
    cout << "*******************************************\n";
    cout << "*        CONSULTA DE FUNCIONÁRIO          *\n";
    cout << "*******************************************\n\n";
    cout << "Informe o código do funcionário: ";
    cin >> cod;

    ret = Pesquisa(cod, *listaE, &p); //pesquisa para saber qual o funcionario

    //exibe os dados do funcionario e seus projetos
    if(ret == 1) { 
        cout << "Código: " << p->prox->item.numero << "\n";
        cout << "Nome: " << p->prox->item.nome << "\n";
        cout << "Endereço: " << p->prox->item.endereco << "\n";
        cout << "Dependentes: " << p->prox->item.dependentes << endl;
        
        cout << "PROJETOS\n";  //quando adiciona outro cara ele mostra com lixo de memoria parece
        for(int i = listaS.primeiro; i < listaS.ultimo; i++){
            cout << "Codigo: " << p->prox->item.projetos.item[i].codigo << "\n";
            cout << "Projeto nome: " << p->prox->item.projetos.item[i].nome << "\n";
            cout << "Horas trabalhadas: " << p->prox->item.projetos.item[i].horas << "\n";
        }
    } else {
        cout << "\nFuncionário não encontrado.\n\n";
    }

    system("pause");
    system("cls");
}

void CadastraProjetos(TListaSequencial &listaS, TListaEncadeada *listaE){
    TProjeto proj;
    TApontador p;
    TChave cod;
    //TFuncionario fun;
    cout << "Informe o codigo do funcionario: ";
    cin >> cod;

    int ret;

    ret = Pesquisa(cod, *listaE, &p);
  
    if(ret == 1){
        cout << "*******************************************\n";
        cout << "*        CADASTRO DE PROJETO              *\n";
        cout << "*******************************************\n\n";
        cout << "Codigo: ";
        cin >> proj.codigo;
        cin.ignore();
        cout << "Nome do projeto: ";
        gets(proj.nome);
        cout << "Horas trabalhadas: ";
        cin >> proj.horas;
        
        p->prox->item.projetos.item[listaS.ultimo] = proj;
      
        //inserindo na lista sequencial os projetos
        InsereSequencial(proj, listaS);

        cout << "\nProjeto cadastrado com sucesso!\n\n";
        Sleep(1000);  
    } else {
        cout << "\nFuncionário não encontrado.\n\n";
    }
}

void ExcluiFuncionario(TListaEncadeada *listaE, TListaSequencial &listaS) {
    TFuncionario fun;
    //TProjeto proj;
    TApontador x = listaE->Primeiro;
    int cont = 0;

    while (x->prox != NULL) {
        
        //COMPARAR SE TEM PROJETO
          
            ApagaFuncionario(x, listaE, &fun);
            cont++;
        
    }
    system("cls");
    cout << "*******************************************\n";
    cout << "*        EXCLUSÃO DE FUNCIONÁRIOS         *\n";
    cout << "*******************************************\n\n";
    cout << "\n" << cont << " funcionário(s) excluído(s) com sucesso!\n\n";
    system("pause");
    system("cls");
}

void ApagaFuncionario(TApontador x, TListaEncadeada *listaE, TFuncionario *fun) {
    TApontador q;

    if ((VerificaListaVaziaE(*listaE)) || (x == NULL) || (x->prox == NULL)) {
        cout << "Erro. Lista vazia";
    } else {
        q = x->prox;
        *fun = q->item;
        x->prox = q->prox;
        if (x->prox == NULL) {
            listaE->Ultimo = x;
        }
        delete q;
    }
}

