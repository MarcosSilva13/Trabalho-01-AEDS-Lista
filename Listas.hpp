#ifndef LISTAS_H
#define LISTAS_H

#define MAXTAM 5 //numero maximo de projetos
#define INICIO 0

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
  char nome[40];             // nome do funcionario
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

void menu(); //menu do programa

//TADS Lista Encadeada
void CriaListaVaziaEncadeada(TListaEncadeada *listaE);
void InsereEncadeada(TFuncionario fun, TListaEncadeada *listaE);
int VerificaListaVaziaE(TListaEncadeada listaE); 
int Pesquisa(TChave cod, TListaEncadeada listaE, TApontador *p);

//TADS Lista Sequencial
void CriaListaVaziaSequencial(TListaSequencial *listaS); 
void InsereSequencial(TProjeto proj, TListaSequencial *listaS);
int VerificaListaVaziaS(TListaSequencial listaS);

//ações 
void CadastraFuncionario(TListaEncadeada *listaE); //cadastro de funcionarios
void ConsultaFuncionario(TListaEncadeada *listaE);  //consulta de funcionarios
void DadosFuncionario(TChave cod, TListaEncadeada *listaE); //dados do funcionario
void ExcluiFuncionario(TListaEncadeada *listaE); //exclui funcionarios
void ApagaFuncionario(TApontador x, TListaEncadeada *listaE, TFuncionario *fun); //apaga funcionario
void CadastraProjetos(TListaEncadeada *listaE); //cadastro de projetos
void ImprimeProjetos(TListaSequencial listaS); //imprimi projeto 
int QuantidadeProjetos(TListaSequencial listaS); //quantidade de projetos na lista 

#endif