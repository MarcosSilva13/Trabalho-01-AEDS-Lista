#include <iostream>
#include <windows.h>
#include <fstream>
#include <string.h>

using namespace std;

#define MAXTAM 5 //numero maximo de projetos
#define INICIO 1

typedef int TChave;

typedef struct TCelula_str *TApontador;

typedef struct
{
  TChave codigo; // codigo do projeto
  char nome[30]; // nome do projeto
  int horas;     // numero de horas trabalhadas no projeto
} TProjeto;

typedef struct
{
  TProjeto item[MAXTAM];
  int primeiro;
  int ultimo;
} TListaSequencial;

typedef struct
{
  TChave numero;             // codigo do funcionario
  char nome[30];             // nome do funcionario
  char endereco[40];         // endereco do funcionario
  int dependentes;           // numero de dependentes do funcionario
  TListaSequencial projetos; // Lista Sequencial que guarda os projetos nos quais o funcionario trabalha
} TFuncionario;

typedef struct TCelula_str
{
  TFuncionario item;
  TApontador prox;
} TCelula;

typedef struct
{
  TApontador Primeiro;
  TApontador Ultimo;
} TListaEncadeada;

void menu();
//TADS Lista Encadeada
void CriaListaVaziaEncadeada(TListaEncadeada *listaE);
void InsereEncadeada(TFuncionario fun, TListaEncadeada *listaE);
int VerificaListaVaziaE(TListaEncadeada listaE); 
int Pesquisa(TChave cod, TListaEncadeada listaE, TApontador *p);
void ExcluiFuncionario(TListaEncadeada *listaE, TListaSequencial &listaS);
void ApagaFuncionario(TApontador x, TListaEncadeada *listaE, TFuncionario *fun);
//void ListaFuncionario NÃO VAI PRECISAR EU ACHO

//TADS Lista Sequencial
void CriaListaVaziaSequencial(TListaSequencial &listaS);
void InsereSequencial(TProjeto proj, TListaSequencial &listaS);
int VerificaListaVazia(TListaEncadeada listaS);
//???? ExcluiProjeto

//ações 
void CadastraFuncionario(TListaEncadeada *listaE); //cadastro de funcionarios
void ConsultaFuncionario(TListaEncadeada *listaE, TListaSequencial listaS); //consulta de funcionarios 
void CadastraProjetos(TListaSequencial &listaS, TListaEncadeada *listaE);   //cadastro de projetos
void ImprimiLista(TListaEncadeada listaE, TListaSequencial listaS);



int main()
{
  UINT CPAGE_UTF8 = 65001;
  UINT CPAGE_DEFAULT = GetConsoleOutputCP();
  SetConsoleOutputCP(CPAGE_UTF8);
  
  TListaEncadeada listaE;
  TListaSequencial listaS;
  
  CriaListaVaziaEncadeada(&listaE);
  CriaListaVaziaSequencial(listaS);

  //NÃO ESQUECER QUE TEM QUE GRAVAR NO ARQUIVO AINDA...
  //A LISTA DE PROJETO PARECE NAO TA CRIANDO UMA LISTA PRA CADA FUNCIONARIO NAO...

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
            CadastraProjetos(listaS, &listaE);
            break;
        case 3:
            //função
            ImprimiLista(listaE, listaS);
            break;
        case 4:
            ExcluiFuncionario(&listaE, listaS);
            break;
        case 5:
            ConsultaFuncionario(&listaE, listaS);
            break;
        case 6:
            //função
            break;
    }
  } while (opcao != 7);

  system("pause");
  return 0;
}

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
    listaS.primeiro = 0;
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

int Pesquisa(TChave cod, TListaEncadeada listaE, TApontador *p){
    TApontador aux = listaE.Primeiro;
    while(aux->prox != NULL){
      if(aux->prox->item.numero == cod){
          *p = aux;
          return 1;
      } else {
        aux = aux->prox;
        //*p = aux;
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
        
        //TA GUARDANDO SEPARADO MAS AINDA DANDO UNS BO DOIDO PORQ PRA OUTRO APARECE ESPAÇO VAZIO
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
        //comparar se tem projeto
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



void ImprimiLista(TListaEncadeada listaE, TListaSequencial listaS){
    TApontador aux;
    aux = listaE.Primeiro->prox;

    while(aux != NULL) { 
        /*cout << "FUNCIONARIO\n"; 
        cout << "Codigo: " << aux->item.numero << "\n";
        cout << "Nome: " << aux->item.nome << "\n";
        cout << "Endereço: " << aux->item.endereco << "\n";
        cout << "Dependentes: " << aux->item.dependentes << "\n";
        */
        cout << "PROJETOS\n";
        /*for(int i = listaS.primeiro; i < listaS.ultimo; i++){
        cout << "Codigo: " << aux->item.projetos.item[i].codigo << "\n";
        cout << "Projeto nome: " << aux->item.projetos.item[i].nome << "\n";
        cout << "Horas trabalhadas: " << aux->item.projetos.item[i].horas << "\n";
        }*/
        for(int i = listaS.primeiro; i < listaS.ultimo; i++){
        cout << "Codigo: " << listaS.item[i].codigo << "\n";
        cout << "Projeto nome: " << listaS.item[i].nome << "\n";
        cout << "Horas trabalhadas: " << listaS.item[i].horas << "\n";
        }
        aux = aux->prox;
    }
}