//Bibliotecas utilizadas.
#include <iostream>
#include <locale.h>
using namespace std;
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <time.h>
#include "matriz.h"



void Criar_Mapas(Mapa (&Mapas)[3]);
void Case_Menu(int &Escolha_Menu, Mapa (&Mapas)[3], Player &Jogador);
void Titulo(string palavra);
void Sobre();
void Modo_de_Jogo(Player &Jogador);
void Dificuldade(Player &Jogador);
void Placar();
void Jogar(Mapa (&Mapas)[3], Player &Jogador);
void Novo_Jogo(Mapa (&Mapas)[3], Player &Jogador);
void Jogar_Mapas(Mapa (&Mapas)[3],Player &Jogador);
void Continuar(Mapa (&Mapas)[3], Player &Jogador);
void Desabilitar_Cursor();

void Menu_Principal(){
  
  Player Jogador;
  Jogador.Contador_Jogadas = 0;
  Jogador.Contador_Mapa = 0;
  Jogador.Contador_Total = 0;
  Jogador.Modo_Jogo = 0;
  Jogador.Mapa_Escolhido = 0;
  Jogador.Vida = 100;
  //Array com os mapas.
  Mapa Mapas[3];

  string Personagem;
  //Fun??o para criar os mapas.
  Criar_Mapas(Mapas);

  int Escolha_Menu = 0;
  while(Escolha_Menu != 7){
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);
    system("cls");
    Titulo(R"(
     _          _     _      _       _
    | |    __ _| |__ (_)_ __(_)_ __ | |_ ___
    | |   / _` | '_ \| | '__| | '_ \| __/ _ \
    | |__| (_| | |_) | | |  | | | | | || (_) |
    |_____\__,_|_.__/|_|_|  |_|_| |_|\__\___/

    )");
    cout << "[1] Novo Jogo" << endl <<
            "[2] Continuar" << endl <<
            "[3] Modo de Jogo" << endl <<
            "[4] Dificuldade" << endl <<
            "[5] Placar" << endl <<
            "[6] Sobre" << endl <<
            "[7] Fim" << endl;
    cout <<"==================================================" << endl;
    cout << "Informe a opção desejada: ";
    SetConsoleOutputCP(CPAGE_DEFAULT);
    //Vari?vel que vai receber a escolha do jogador no menu.
    cin >> Escolha_Menu;
    //Fun??o com o switch para cada op??o do menu.
    Case_Menu(Escolha_Menu , Mapas, Jogador);
  }
}


void Case_Menu(int &Escolha_Menu, Mapa (&Mapas)[3], Player &Jogador){

  switch (Escolha_Menu){
    case 1:
      //Vai para a fun??o de come?ar um novo jogo.
      system("cls");
      Novo_Jogo(Mapas, Jogador);
      system("Pause");
      break;
    case 2:
      //Vai para fun??o de continuar um jogo.
      system("cls");
      if (Jogador.Vida != 0){
        Continuar(Mapas, Jogador);
      } 
      else {
        Novo_Jogo(Mapas, Jogador);
      }
      break;
    case 3:
      //Vai para a fun??o de escolher o modo de jgoo.
      system("cls");
      Modo_de_Jogo(Jogador);
      system("Pause");
      break;
    case 4:
      //Vai para a fun??o de escolher a dificuldade.
      system("cls");
      Dificuldade(Jogador);
      system("Pause");
      break;
    case 5:
      //placar
      system("cls");
      Placar();
      break;
    case 6:
      //Vai para a fun??o de mostrar o sobre.
      system("cls");
      Sobre();
      system("Pause");
      break;
    case 7:
      //Termina o jogo.
      system("cls");
      Titulo("Fim");
      cout << "Obrigado por jogar!" << endl;
      cout <<"==============================" << endl;
      system("Pause");
      break;
    default:
      UINT CPAGE_UTF8 = 65001;
      UINT CPAGE_DEFAULT = GetConsoleOutputCP();
      SetConsoleOutputCP(CPAGE_UTF8);
      //Default para caso o usu?rio digite uma op??o inv?lida.
      cout <<endl <<"Opção inválida, tente novamente!" << endl;
      Escolha_Menu = 0;
      system("Pause");
      SetConsoleOutputCP(CPAGE_DEFAULT);
      break;
  }
  
}

//Funзгo para continuar um jogo jб comeзado.
void Continuar(Mapa (&Mapas)[3], Player &Jogador){
  switch (Jogador.Modo_Jogo){
    case 0:
      Jogador.Vitoria = true;
      Jogador.Modo_Jogo = 1;
      Jogar(Mapas,Jogador);
      break;
    case 1:
      Jogar(Mapas,Jogador);
      break;
    case 2:
      Jogar_Mapas(Mapas,Jogador);
      break;
  }
}
//Fun??o onde ? o modo de jogo.
void Modo_de_Jogo(Player &Jogador){
  int Escolha;
  UINT CPAGE_UTF8 = 65001;
  UINT CPAGE_DEFAULT = GetConsoleOutputCP();
  SetConsoleOutputCP(CPAGE_UTF8);
  Titulo(R"(
    __  __           _             _            _
   |  \/  | ___   __| | ___     __| | ___      | | ___   __ _  ___
   | |\/| |/ _ \ / _` |/ _ \   / _` |/ _ \  _  | |/ _ \ / _` |/ _ \
   | |  | | (_) | (_| | (_) | | (_| |  __/ | |_| | (_) | (_| | (_) |
   |_|  |_|\___/ \__,_|\___/   \__,_|\___|  \___/ \___/ \__, |\___/
                                                         |___/
  )");
  cout<< "[1] Escolha um dos três mapas disponíveis para jogar." << endl <<
         "[2] Jogue os três mapas disnponíveis em sequ?ncia." << endl <<
         "[3] Volte para o menu." << endl;
  cout <<"==================================================" << endl;
  cout << "Escolha a opção desejada: ";
  cin >> Escolha;
  switch(Escolha){
    case 1:
      Reset_Jogador(Jogador);
      Jogador.Modo_Jogo = 1;
      cout << "Escolha entre o mapa 1, 2 e 3: ";
      cin>> Jogador.Mapa_Escolhido;
      cout << "Mapa " << Jogador.Mapa_Escolhido << "Escolhido!";
      Jogador.Mapa_Escolhido -=1;
      break;
    case 2:
      Reset_Jogador(Jogador);
      Jogador.Modo_Jogo = 2;
      cout << "Modo historia selecionado!\n";
      break;
    case 3:
      cout << "Retornando ao menu...\n";
      return;
      break;
    default:
      cout << "Opção invalida, Digite Novamente:\n";
      break;
  }  
    SetConsoleOutputCP(CPAGE_DEFAULT);

}
void Dificuldade(Player &Jogador){
  int Escolha;
  UINT CPAGE_UTF8 = 65001;
  UINT CPAGE_DEFAULT = GetConsoleOutputCP();
  SetConsoleOutputCP(CPAGE_UTF8);
  Titulo(R"(
  ____  _  __ _            _     _           _
 |  _ \(_)/ _(_) ___ _   _| | __| | __ _  __| | ___
 | | | | | |_| |/ __| | | | |/ _` |/ _` |/ _` |/ _ \
 | |_| | |  _| | (__| |_| | | (_| | (_| | (_| |  __/
 |____/|_|_| |_|\___|\__,_|_|\__,_|\__,_|\__,_|\___|
  )");
  cout<< "[1] Modo Fácil." << endl <<
         "[2] Modo Difícil." << endl <<
         "[3] Volte para o menu." << endl;
  cout <<"==================================================" << endl;
  cout << "Escolha a opção desejada: ";
  cin >> Escolha;
  switch (Escolha){
    case 1:
      Jogador.Dificuldade = 1;
      cout << "Modo Fácil selecionado\n";
      break;
    case 2:
      Jogador.Dificuldade = 2;
      cout << "Modo Difícil selecionado\n";
      break;
    case 3:
      cout << "Retornando ao menu...\n";
      return;
      break;
    default:
      cout << "Opção invalida, Digite novamente\n";
      break;
  }
  SetConsoleOutputCP(CPAGE_DEFAULT);

    Jogador.Vitoria = true;
    Jogador.px = 1, Jogador.py = 1;
    Jogador.Contador_Jogadas = 0;
    Jogador.Contador_Total = 0;
    Jogador.Vida = 100;
}

void Placar(){
  int EscolhaPlacar;
  UINT CPAGE_UTF8 = 65001;
  UINT CPAGE_DEFAULT = GetConsoleOutputCP();
  SetConsoleOutputCP(CPAGE_UTF8);
  Titulo(R"(
  ____  _
 |  _ \| | __ _  ___ __ _ _ __
 | |_) | |/ _` |/ __/ _` | '__|
 |  __/| | (_| | (_| (_| | |
 |_|   |_|\__,_|\___\__,_|_|

  )");
  cout << "Qual Placar você quer ver: \n";
  cout << "[1] Vida restante\n";
  cout << "[2] Passos Dados\n";
  cout << "[3] Volte para o menu.\n";

  cout <<"==================================================" << endl;
  cout << "Escolha a opção desejada: ";
  cin >> EscolhaPlacar;

  switch(EscolhaPlacar){
    case 1:
      system("cls");
      Mostra_PlacarVida();
      system("Pause");
      break;
    case 2:
      system("cls");
      Mostra_PlacarPassos();
      system("Pause");
      break;
    case 3:
      cout << "Retornando ao menu...\n";
      return;
      break;
    default:
      cout << "Escolha invalida";
      system("Pause");
      break;
  }
  SetConsoleOutputCP(CPAGE_DEFAULT);
}

void Sobre(){
  UINT CPAGE_UTF8 = 65001;
  UINT CPAGE_DEFAULT = GetConsoleOutputCP();
  SetConsoleOutputCP(CPAGE_UTF8);

  cout <<"===================================================================" <<endl;
  cout << R"(
                  ____        _
                 / ___|  ___ | |__  _ __ ___
                 \___ \ / _ \| '_ \| '__/ _ \
                  ___) | (_) | |_) | | |  __/
                 |____/ \___/|_.__/|_|  \___|

            )";
  cout << endl;
  cout <<
  "===================================================================" <<endl<<
  "                         Informações gerais: " <<endl<<
  " - Equipe de Desenvolvimento: Pablo Augusto de Quadros,"<<endl <<
  "   Bernardo Henrique Gaya e Guilherme Victor Butzke." << endl <<
  " - Produzido em Outubro de 2021." << endl <<
  " - Professor: Thiago Felski Pereira." << endl <<
  " - Disciplina: Algoritmos e Programação 2." << endl <<
  "==================================================================="<< endl << endl << endl <<
  "===================================================================" << endl <<
  "              Informações sobre o jogo / Como jogar:"<<endl<<
  " - O jogo Labirinto é jogado através das teclas para cima, para" <<endl<< 
  "baixo, para a esquerda e para a direita, o jogador só poderá se"<<endl<< 
  "mover em direções a qual não há paredes e seu objetivo é chegar ao"<<endl<<
  "final do labirinto. Porém ele precisa primeiramente ir atrás de uma"<<endl<<
  "chave para consegueir liberar a porta que bloqueia a saída, em"<< endl<<
  "quanto tenta sair do labirinto precisa tomar cuidado com as" <<endl<<
  "armadilhas." <<
    endl<< endl<<
  " - O jogo possui dois modos de jogo. O primeiro que" << endl<<
  "o jogador jogará apenas um único mapa ele "<<endl<<
  "deverá escolher qual dos três mapas ele deseja jogar. O segundo "<<endl<<
  "modo de jogo fará com que o jogador passe por todos os três mapas "<<endl<<
  "e só acabe quando os três mapas forem finalizados. Os dois modos "<<endl<<
  "de jogo possuem um contador de jogadas para o jogador saber "<<endl<<
  "quantas foram necessárias para concluir o labirinto."<<endl<<
  "===================================================================" << endl;
  SetConsoleOutputCP(CPAGE_DEFAULT);
}

//Fun??o para iniciar um novo jogo.
void Novo_Jogo(Mapa (&Mapas)[3], Player &Jogador){
  Reset_Jogador(Jogador);
  Reset_Armadilha(Mapas, Jogador);
  Aleatorio(Mapas, Jogador);

  switch (Jogador.Modo_Jogo){
    case 0:
      Jogador.Modo_Jogo = 1;
      Jogar(Mapas,Jogador);
      break;
    case 1:
      Jogar(Mapas,Jogador);
      break;
    case 2:
      Jogar_Mapas(Mapas,Jogador);
      break;
  }
}

void Desabilitar_Cursor(){
 //Comandos para que o cursos n?o fique piscando na tela.
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO     cursorInfo;
  GetConsoleCursorInfo(out, &cursorInfo);
  cursorInfo.bVisible = false;
  SetConsoleCursorInfo(out, &cursorInfo);
}

void Reposiciona_Cursor(){
  COORD coord;
  coord.X = 0;   
  coord.Y = 0;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Jogar(Mapa (&Mapas)[3], Player &Jogador){  

  if (Jogador.Vitoria == true){
    Reset_Armadilha(Mapas, Jogador);
    Aleatorio(Mapas, Jogador);
    Jogador.Vida = 100;
    Jogador.Porta = false;
  }

  Jogador.Fala = "Boa sorte!                                                                                                          ";
  Jogador.Vitoria = false;
  Jogador.Menu = false;

  Desabilitar_Cursor();

  system("cls");

  while(Jogador.Vitoria != true && Jogador.Vida > 0 && Jogador.Menu != true){

    Titulo_Mapa(Jogador);
    cout << endl;
    Mostrar_Mapa(Mapas, Jogador);

    Comandos<string>("Comandos: \nM = Voltar ao menu \nR = Reseta o Jogo\nSeta para cima = cima\nSeta para baixo = baixo\nSeta para esquerda = Esquerda\nSeta para direita = direita");
    cout <<"==============================" << endl;
    cout << "Vida: " << Jogador.Vida << endl;
    cout << "Jogadas realizadas: " << Jogador.Contador_Jogadas << endl;
    cout << Jogador.Fala << endl;
    cout <<"==============================" << endl;

    Movimento(Mapas, Jogador);
    Reposiciona_Cursor();
  }
  Verificacao_Derrota(Jogador);
}

void Jogar_Mapas(Mapa (&Mapas)[3],Player &Jogador){

  Desabilitar_Cursor();
  system("cls");

  for(Jogador.Mapa_Escolhido = Jogador.Contador_Mapa; Jogador.Mapa_Escolhido < 3 ; Jogador.Mapa_Escolhido++) {

    if (Jogador.Vitoria == true){
      Reset_Armadilha(Mapas, Jogador);
      Aleatorio(Mapas, Jogador);
      Jogador.Porta = false;
    }

    Jogador.Vitoria = false;
    Jogador.Menu = false;
    Jogador.Fala = "Boa sorte!                                                                                                          ";

     while(Jogador.Vitoria != true && Jogador.Vida > 0 && Jogador.Menu != true){

      Titulo_Mapa(Jogador);
      cout << endl;
      Mostrar_Mapa(Mapas, Jogador);
      Comandos<string>("Comandos: \nM = Voltar ao menu \nR = Reseta o Jogo\nSeta para cima = cima\nSeta para baixo = baixo\nSeta para esquerda = Esquerda\nSeta para direita = direita");
      cout <<"==============================" << endl;
      cout << "Vida: " << Jogador.Vida << endl;
      cout << "Jogadas realizadas neste mapa: " << Jogador.Contador_Jogadas;
      cout << endl << "No total voc? realizou " << Jogador.Contador_Total << " jogadas." << endl;
      cout << Jogador.Fala << endl;
      cout <<"==============================" << endl;
      Movimento(Mapas, Jogador);
      Reposiciona_Cursor();
    }
    if (Jogador.Menu == true){
      return;
    }
    Jogador.Contador_Mapa++;
  }
}

