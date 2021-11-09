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

void CriaListaVaziaSequencial(TListaSequencial *listaS){
    listaS->primeiro = INICIO;
    listaS->ultimo = listaS->primeiro;
}

int VerificaListaVaziaS(TListaSequencial listaS){
    if(listaS.ultimo == 0){
        return 1;
    }else{
        return 0;
    }
}

void InsereSequencial(TProjeto proj, TListaSequencial *listaS){
    if(listaS->ultimo == MAXTAM){
        cout << "Lista Cheia!\n";
        Sleep(1000);
    } else {
        listaS->item[listaS->ultimo] = proj;
        listaS->ultimo++;
    }
}

void CadastraFuncionario(TListaEncadeada *listaE){
    TFuncionario fun;
    TApontador y = listaE->Primeiro;
    cout << "*******************************************\n";
    cout << "*        CADASTRO DE FUNCIONÁRIO          *\n";
    cout << "*******************************************\n\n";
    cout << "Codigo: ";
    cin >> fun.numero;

    //verificando se ja existe codigo igual dos funcionarios
    while(y->prox != NULL){
        if(y->prox->item.numero == fun.numero){
            cout << "Codigo ja existe, Digite outro: ";
            cin >> fun.numero;
            y = listaE->Primeiro;
        } else {
            y = y->prox;
        }
    }
    cin.ignore();
    cout << "Nome: ";
    gets(fun.nome);
    cout << "Endereço: ";
    gets (fun.endereco);
    
    while ((cout << "Número de Dependentes: ") && !(cin >> fun.dependentes)) {
            cout << "Você inseriu um valor nao numerico.\n"; // Exibe mensagem em caso de divergência encontrada
            cin.clear(); // Apaga o sinalizador de erro cin para que futuras operações funcionem corretamente
            cin.ignore(); // Pula para a próxima linha ignorando caracteres para o buffer de entrada
}
    
    CriaListaVaziaSequencial(&fun.projetos); //criando a lista de projetos
    
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

void ConsultaFuncionario(TListaEncadeada *listaE){
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
        
        cout << "\nPROJETOS do funcionario:\n";  
        ImprimeProjetos(p->prox->item.projetos);

    } else {
        cout << "\nFuncionário não encontrado.\n\n";
    }

    system("pause");
    system("cls");
}

void CadastraProjetos(TListaEncadeada *listaE){
    TProjeto proj;
    TApontador p;
    TChave cod;
    int ret, ret_proj;

    cout << "Informe o codigo do funcionario: ";
    cin >> cod;

    ret = Pesquisa(cod, *listaE, &p);

    ret_proj = QuantidadeProjetos(p->prox->item.projetos);

    if(ret_proj == MAXTAM){
        cout << "\nO funcionario só pode ter no máximo 5 projetos\n";
    } else {
        if(ret == 1){
            DadosFuncionario(cod, listaE); //exibe os dados do funcionario e seus projetos

            cout << "*******************************************\n";
            cout << "*        CADASTRO DE PROJETO              *\n";
            cout << "*******************************************\n\n";
            cout << "Codigo: ";
            cin >> proj.codigo;
            cin.ignore();
            cout << "Nome do projeto: ";
            gets(proj.nome);

            while((cout << "Horas trabalhadas: ") && !(cin >> proj.horas)){
                cout << "Você inseriu um valor nao numerico.\n"; // Exibe mensagem em caso de divergência encontrada
                cin.clear(); // Apaga o sinalizador de erro cin para que futuras operações funcionem corretamente
                cin.ignore(); // Pula para a próxima linha ignorando caracteres para o buffer de entrada
            }

            //inserindo na lista sequencial os projetos
            InsereSequencial(proj, &(p->prox->item.projetos));

            cout << "\nProjeto cadastrado com sucesso!\n\n";
            Sleep(1000);  
        } else {
            cout << "\nFuncionário não encontrado.\n\n";
        }
    }
    
}

void ExcluiFuncionario(TListaEncadeada *listaE) {
    TFuncionario fun;
    TApontador x = listaE->Primeiro;
    int cont = 0, ret_proj;

    while(x->prox != NULL){

        ret_proj = QuantidadeProjetos(x->prox->item.projetos);

        if(ret_proj == 0){
            ApagaFuncionario(x, listaE, &fun);
            cont++;
        } else {
            x = x->prox;
        }    

    }
    system("cls");
    cout << "*******************************************\n";
    cout << "*        EXCLUSÃO DE FUNCIONÁRIOS         *\n";
    cout << "*******************************************\n\n";
    cout << "\n" << cont << " funcionário(s) excluído(s) com sucesso!\n\n";
    system("pause");
    system("cls");
}

void ApagaFuncionario(TApontador x, TListaEncadeada *listaE, TFuncionario *fun){
    TApontador q;

    if((VerificaListaVaziaE(*listaE)) || (x == NULL) || (x->prox == NULL)){
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

void DadosFuncionario(TChave cod, TListaEncadeada *listaE){
    TApontador p;
    int ret;

    ret = Pesquisa(cod, *listaE, &p); //pesquisa para saber qual o funcionario

    //exibe os dados do funcionario e seus projetos
    if(ret == 1) { 
        cout << "*******************************************\n";
        cout << "*        DADOS DO FUNCIONÁRIO          *\n";
        cout << "*******************************************\n\n";
        cout << "Código: " << p->prox->item.numero << "\n";
        cout << "Nome: " << p->prox->item.nome << "\n";
        cout << "Endereço: " << p->prox->item.endereco << "\n";
        cout << "Dependentes: " << p->prox->item.dependentes << endl;
        
        cout << "\nPROJETOS do funcionario:\n";  
        ImprimeProjetos(p->prox->item.projetos); //imprimo a lista de projetos do funcionario

    } else {
        cout << "\nFuncionário não encontrado.\n\n";
    }

    system("pause");
}

void ImprimeProjetos(TListaSequencial listaS) {
    for (int i = 0; i < listaS.ultimo; i++){
	    cout << "\nCódigo do Projeto: " << listaS.item[i].codigo;
	    cout << "\nNome do Projeto: " << listaS.item[i].nome;
	    cout << "\nHoras Trabalhadas: " << listaS.item[i].horas << "\n";
    }
}

int QuantidadeProjetos(TListaSequencial listaS){
    int contador = 0;
    for(int i = 0; i < listaS.ultimo; i++){
        if(listaS.item[i].codigo != NULL && listaS.item[i].nome != NULL && listaS.item[i].horas != NULL){
            contador++;
        }
    }
    return contador;
}