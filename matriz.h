//Bibliotecas utilizadas.
#include <iostream>
#include <locale.h>
using namespace std;
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <time.h>

struct Player
{
  string Nome;
  string Fala;
  int Mapa_Escolhido;
  int Dificuldade = 1;
  int Modo_Jogo = 0;
  int px = 1;
  int py = 1;
  int Contador_Jogadas;
  int Contador_Mapa;
  int Contador_Total;
  int Vida = 100;
  bool Menu;
  bool Vitoria;
  bool Porta = false;
};
struct Mapa{
  int Tamanho;
  int Labirinto[30][30];

};



void Titulo(string palavra = "Labirinto"){
  cout <<"===================================================" << endl;
  cout << "           "+palavra<< endl;
  cout <<"===================================================" << endl;
}
template<typename Tipo>
void Comandos(Tipo Comando){
  cout <<"==============================" << endl;
  cout << "           "+Comando<< endl;
}

//Mostra qual mapa o jogador esta
void Titulo_Mapa(Player Jogador){
    if (Jogador.Mapa_Escolhido == 0){
    Titulo(R"(
             __  __                     _
            |  \/  | __ _ _ __   __ _  / |
            | |\/| |/ _` | '_ \ / _` | | |
            | |  | | (_| | |_) | (_| | | |
            |_|  |_|\__,_| .__/ \__,_| |_|
                         |_|
    )");
    } else if (Jogador.Mapa_Escolhido == 1){
        Titulo(R"(
             __  __                     ____
            |  \/  | __ _ _ __   __ _  |___ \
            | |\/| |/ _` | '_ \ / _` |   __) |
            | |  | | (_| | |_) | (_| |  / __/
            |_|  |_|\__,_| .__/ \__,_| |_____|
                         |_|
    )");
    } else if (Jogador.Mapa_Escolhido == 2){
        Titulo(R"(
            __  __                     _____
            |  \/  | __ _ _ __   __ _  |___ /
            | |\/| |/ _` | '_ \ / _` |   |_ \
            | |  | | (_| | |_) | (_| |  ___) |
            |_|  |_|\__,_| .__/ \__,_| |____/
                         |_|
    )");
    }
}


//Cria o mapa
void Criar_Mapas(Mapa (&Mapas)[3]){

    int numero;
    string lido;
    ifstream meu_mapa;
    meu_mapa.open("mapa.txt");

    if (meu_mapa.is_open()==true){

        for (int i = 0; i < 3; i++){
            getline(meu_mapa,lido);
            Mapas[i].Tamanho = stoi(lido);
        }
        
        for (int i = 0; i < 3 ; i++){
            for (int linha = 0; linha < Mapas[i].Tamanho; linha++){
                for(int coluna = 0 ; coluna <= Mapas[i].Tamanho; coluna++){
                    switch(i){
                        case 0:
                            numero = meu_mapa.get();
                            Mapas[0].Labirinto[linha][coluna] = numero-48 ;
                            break;
                        case 1:
                            numero = meu_mapa.get();
                            Mapas[1].Labirinto[linha][coluna] = numero-48 ;
                            break;
                        case 2:
                            numero = meu_mapa.get();
                            Mapas[2].Labirinto[linha][coluna] = numero-48 ;
                            break;
                    }
                }
            }
        }
    }
}

//Mostra o Mapa para o jogador
void Mostrar_Mapa(Mapa (&Mapas)[3], Player Jogador){
    for(int linha = 0; linha < Mapas[Jogador.Mapa_Escolhido].Tamanho; linha++){
        for(int coluna = 0; coluna < Mapas[Jogador.Mapa_Escolhido].Tamanho ; coluna++){
            if (linha==Jogador.px and coluna==Jogador.py){
                cout<< char(258);
            } else {
                switch (Mapas[Jogador.Mapa_Escolhido].Labirinto[linha][coluna]) {
                case 0: cout << " "; break;
                case 1: cout << char(219); break;
                case 2: cout << char(158); break;
                case 3: cout << char(157); break;
                case 4: cout << char(157); break;
                case 5: cout << char(176); break;
                case 6: cout << char(190); break;
                }
            }
        }
        cout<<"\n";
    }
}

//Movimenta para cima
void Movimentar_Cima(Mapa (&Mapas)[3], Player &Jogador){

    Jogador.px--;
    Jogador.Contador_Jogadas++;
    Jogador.Contador_Total++;
    
    if (Mapas[Jogador.Mapa_Escolhido].Labirinto[Jogador.px][Jogador.py] == 1){
        Jogador.px++;
        Jogador.Contador_Jogadas--;
        Jogador.Contador_Total--;
    } 
    else if (Mapas[Jogador.Mapa_Escolhido].Labirinto[Jogador.px][Jogador.py] == 5){
        switch (Jogador.Porta){
            case true:
                Jogador.Fala = "Porta Destrancada                                                                     ";
                break;
            case false:
                Jogador.px++;
                Jogador.Fala = "Porta Trancada                                                                     ";
                Jogador.Contador_Jogadas--;
                Jogador.Contador_Total--;
                break;
        }
    }
}

//Movimenta para baixo
void Movimentar_Baixo(Mapa (&Mapas)[3], Player &Jogador){

    Jogador.px++;
    Jogador.Contador_Jogadas++;
    Jogador.Contador_Total++;

    if (Mapas[Jogador.Mapa_Escolhido].Labirinto[Jogador.px][Jogador.py] == 1){
        Jogador.px--;
        Jogador.Contador_Jogadas--;
        Jogador.Contador_Total--;
    } 
    else if (Mapas[Jogador.Mapa_Escolhido].Labirinto[Jogador.px][Jogador.py] == 5){
        switch (Jogador.Porta){
            case true:
                Jogador.Fala = "Porta Destrancada                                                                     ";
                break;
            case false:
                Jogador.px--;
                Jogador.Fala = "Porta Trancada                                                                     ";
                Jogador.Contador_Jogadas--;
                Jogador.Contador_Total--;
                break;
        }
    }
}

//Movimenta para a esquerda
void Movimentar_Esquerda(Mapa (&Mapas)[3], Player &Jogador){

    Jogador.py--;
    Jogador.Contador_Jogadas++;
    Jogador.Contador_Total++;

    if (Mapas[Jogador.Mapa_Escolhido].Labirinto[Jogador.px][Jogador.py] == 1){
        Jogador.py++;
        Jogador.Contador_Jogadas--;
        Jogador.Contador_Total--;
    } 
    else if (Mapas[Jogador.Mapa_Escolhido].Labirinto[Jogador.px][Jogador.py] == 5){
        switch (Jogador.Porta){
            case true:
                Jogador.Fala = "Porta Destrancada                                                                     ";
                break;
            case false:
                Jogador.py++;
                Jogador.Fala = "Porta Trancada                                                                     ";
                Jogador.Contador_Jogadas--;
                Jogador.Contador_Total--;
                break;
        }
    }
}

//Movimenta para a direita
void Movimentar_Direita(Mapa (&Mapas)[3], Player &Jogador){

    Jogador.py++;
    Jogador.Contador_Jogadas++;
    Jogador.Contador_Total++;

    if (Mapas[Jogador.Mapa_Escolhido].Labirinto[Jogador.px][Jogador.py] == 1){
        Jogador.py--;
        Jogador.Contador_Jogadas--;
        Jogador.Contador_Total--;
    } 
    else if (Mapas[Jogador.Mapa_Escolhido].Labirinto[Jogador.px][Jogador.py] == 5){
        switch (Jogador.Porta){
            case true:
                Jogador.Fala = "Porta Destrancada                                                                     ";
                break;
            case false:
                Jogador.py--;
                Jogador.Fala = "Porta Trancada                                                                     ";
                Jogador.Contador_Jogadas--;
                Jogador.Contador_Total--;
                break;
        }
    }
}


void Placar_Vida(Player &Jogador, string &Usuario){
    string NomeArquivo[12], lido;
    int VidaArquivo[12], DificuldadeArquivo[12];
    fstream Arquivo;

    Arquivo.open("placarvida.txt");
    for (int i = 0; i <10; i++){
        getline(Arquivo, NomeArquivo[i]);
        getline(Arquivo, lido);
        VidaArquivo[i] = stoi(lido);
        getline(Arquivo, lido);
        DificuldadeArquivo[i] = stoi(lido);
    }
    Arquivo.close();


    Arquivo.open("placarvida.txt");
    int verificar =0;
    do{
        for (int i = 0; i < 10; i++){
            if (Usuario == NomeArquivo[i]){
                cout << "Nome ja inserido no placar de Vida, Digite um novo nome: ";
                cin >> Usuario;
                i--;
                verificar--;
            }
            else{
                verificar++;
            }
        } 
    }while(verificar == 10);  
    verificar == 0;
    for (int i = 0; i < 10; i++){
        if (Jogador.Vida > VidaArquivo[i]){
            for (int j = 10; j >= i; j--){
                NomeArquivo[j + 1] = NomeArquivo[j];
                VidaArquivo[j + 1] = VidaArquivo[j];
                DificuldadeArquivo[j + 1] = DificuldadeArquivo[j];
            }
            VidaArquivo[i] = Jogador.Vida;
            NomeArquivo[i] = Usuario;
            DificuldadeArquivo[i] = Jogador.Dificuldade;
            Jogador.Vida = 0;
            cout << "Parabens " << Usuario << " Você entrou para o placar de Vida!\nVocê entrou na posicao " << i + 1 << endl ;
        }
        Arquivo << NomeArquivo[i] << "\n";
        Arquivo << VidaArquivo[i] << "\n";
        Arquivo << DificuldadeArquivo[i] << "\n";

    }
    Arquivo.close();
}

void Placar_Passos(Player &Jogador, string &Usuario){

    string NomeArquivo[12], lido;
    int PassosArquivo[12], DificuldadeArquivo[12];
    fstream Arquivo;
    int PassosTemporarios = Jogador.Contador_Total;
    
    Arquivo.open("placarpassos.txt");

    for (int i = 0; i <10; i++){
        getline(Arquivo, NomeArquivo[i]);
        getline(Arquivo, lido);
        PassosArquivo[i] = stoi(lido);
        getline(Arquivo, lido);
        DificuldadeArquivo[i] = stoi(lido);

    }

    Arquivo.close();

    //Verificacao passos
    Arquivo.open("placarpassos.txt");
    int verificar = 0;
    do{
        for (int i = 0; i < 10; i++){
            if (Usuario == NomeArquivo[i]){
                cout << "Nome ja inserido no placar de Passos, Digite um novo nome: ";
                cin >> Usuario;
                i--;
                verificar--;
            }
            else{
                verificar++;
            }
        } 
    }while(verificar == 10);  
    verificar = 0;

    for (int i = 0; i < 10; i++){
        if (PassosTemporarios < PassosArquivo[i]){
            cout << "Parabens " << Usuario << " Você entrou para o placar de Passos!\nVocê entrou na posicao " << i + 1 << endl ;
            for (int j = 10; j >= i; j--){
                NomeArquivo[j + 1] = NomeArquivo[j];
                PassosArquivo[j + 1] = PassosArquivo[j];
                DificuldadeArquivo[j + 1] = DificuldadeArquivo[j];
            }
            PassosArquivo[i] = PassosTemporarios;
            NomeArquivo[i] = Usuario;
            DificuldadeArquivo[i] = Jogador.Dificuldade;
            PassosTemporarios = 1000000;
        }
        Arquivo << NomeArquivo[i] << "\n";
        Arquivo << PassosArquivo[i] << "\n";
        Arquivo << DificuldadeArquivo[i] << "\n";
    }
  Arquivo.close();
}







//Verificar se a posiзгo que o jogador estб tem armadilha, ou se ele ganhou.
void Verificacao_Posicao(Mapa (&Mapas)[3], Player &Jogador){
    switch(Mapas[Jogador.Mapa_Escolhido].Labirinto[Jogador.px][Jogador.py]){
    case 2:
    
        Jogador.px = 1;
        Jogador.py = 1;
        system("cls");
        cout << endl << R"(
-----------------------------------------------------------
 __     __         //\
 \ \   / /__   ___|/_\| __   _____ _ __   ___ ___ _   _
  \ \ / / _ \ / __/ _ \ \ \ / / _ \ '_ \ / __/ _ \ | | |
   \ V / (_) | (_|  __/  \ V /  __/ | | | (_|  __/ |_| |
    \_/ \___/ \___\___|   \_/ \___|_| |_|\___\___|\__,_|

-----------------------------------------------------------
      )" << endl;
      
        cout << "\tVoce terminou este mapa em " << Jogador.Contador_Jogadas << " Jogadas\n\n";
        cout << "\tVoce terminou com " << Jogador.Vida << " de vida\n \n";

        if (Jogador.Modo_Jogo == 2 && Jogador.Contador_Mapa == 2){
            string Usuario;
            cout << "\tVoc? terminou todos os mapas em " << Jogador.Contador_Total << " Jogadas\n \n";
            cout << "\tQual seu nome?\n";
            cout << "\t";
            cin >> Usuario;
            
            cout << endl;
            Placar_Passos(Jogador, Usuario);
            Placar_Vida(Jogador, Usuario);
            Jogador.Vida = 100;
        }
        cout << "-----------------------------------------------------------\n";
        system("Pause");
        system("cls");
        Jogador.Contador_Jogadas = 0;
        Jogador.Vitoria = true;
        if(Jogador.Contador_Mapa == 2){
        Jogador.Contador_Mapa = -1;
        }
        break;

    case 3:
        if (Jogador.Vida == 100){
            system("cls");
        }

        if (Jogador.Modo_Jogo == 1){
            Jogador.Fala = "Voce pisou em uma Bomba, Voce perdeu 10 de vida                                                                     ";
            Jogador.Vida = Jogador.Vida - 10;
            Mapas[Jogador.Mapa_Escolhido].Labirinto[Jogador.px][Jogador.py] = 0;
        }

        else if (Jogador.Modo_Jogo == 2){
            Jogador.Fala = "Voce pisou em uma Bomba, Voce perdeu 5 de vida                                                                     ";
            Jogador.Vida = Jogador.Vida - 5;
            Mapas[Jogador.Mapa_Escolhido].Labirinto[Jogador.px][Jogador.py] = 0;
        }

        break;
    case 4:
        if (Jogador.Vida == 100){
            system("cls");
        }

        Jogador.Vida = Jogador.Vida - 10;
        Jogador.Fala = "Voce pisou em uma Mega Bomba, Voce perdeu 10 de vida e voltou para o inicio";
        Mapas[Jogador.Mapa_Escolhido].Labirinto[Jogador.px][Jogador.py] = 0;
        Jogador.px = 1;
        Jogador.py = 1;        
        break;
    case 6:
        Jogador.Fala = "Porta Destrancada                                                                     ";
        Jogador.Porta = true;
        break;
  }
}

//Toda a movimentaзгo junta em um lugar, junto com os comandos de tecla
int Movimento(Mapa (&Mapas)[3], Player &Jogador){
  char tecla;
  tecla=getch();
    switch (tecla) {
      case 72: //Tecla para cima.
        Movimentar_Cima(Mapas, Jogador);
        Verificacao_Posicao(Mapas, Jogador);
        break;

      case 75: //Tecla para a esquerda.
        Movimentar_Esquerda(Mapas, Jogador);
        Verificacao_Posicao(Mapas, Jogador);
        break;

      case 77: //Tecla para a direita.
        Movimentar_Direita(Mapas, Jogador);
        Verificacao_Posicao(Mapas, Jogador);
        break;

      case 80: //Tecla para baixo.
        Movimentar_Baixo(Mapas, Jogador);
        Verificacao_Posicao(Mapas, Jogador);
        break;

      case 'r': //Tecla para resetar a posi??o do personagem.
        Jogador.px=1;Jogador.py=1;
        break;

      case 'm': //Tecla para voltar ao menu principal.
        return Jogador.Menu = true;
        break;
      case 'c':
        system("cls");
        break;
    }
}


//Reinicia as configurações do jogador
void Reset_Jogador(Player &Jogador){
    Jogador.px = 1;
    Jogador.py = 1;
    Jogador.Contador_Jogadas = 0;
    Jogador.Contador_Mapa = 0;
    Jogador.Contador_Total = 0;
    Jogador.Vida = 100;
    Jogador.Porta = false;
    Jogador.Vitoria = true;
}

//Reinicia as armadilhas do mapa
void Reset_Armadilha(Mapa (&Mapas)[3], Player &Jogador){
    for(int linha = 0; linha < Mapas[Jogador.Mapa_Escolhido].Tamanho; linha++){
        for(int coluna = 0; coluna < Mapas[Jogador.Mapa_Escolhido].Tamanho ; coluna++){
            if (Mapas[Jogador.Mapa_Escolhido].Labirinto[linha][coluna] == 3 || Mapas[Jogador.Mapa_Escolhido].Labirinto[linha][coluna] == 4){
                Mapas[Jogador.Mapa_Escolhido].Labirinto[linha][coluna] = 0;
            }
        }
    }
}

//Randomiza as armadilhas no mapa
void Aleatorio(Mapa (&Mapas)[3], Player &Jogador){
    int px, py;
    srand(time(NULL));

    for (int i = 0; i < (Mapas[Jogador.Mapa_Escolhido].Tamanho / 2) * Jogador.Dificuldade; i++){
        px = rand()% Mapas[Jogador.Mapa_Escolhido].Tamanho;
        py = rand()% Mapas[Jogador.Mapa_Escolhido].Tamanho;
        if(Mapas[Jogador.Mapa_Escolhido].Labirinto[px][py] == 0){
            Mapas[Jogador.Mapa_Escolhido].Labirinto[px][py] = 3;
        } 
        else {
            i--;
        }
    }

    for (int i = 0; i < (1 * Jogador.Dificuldade); i++){
        px = rand()% Mapas[Jogador.Mapa_Escolhido].Tamanho;
        py = rand()% Mapas[Jogador.Mapa_Escolhido].Tamanho;
        if(Mapas[Jogador.Mapa_Escolhido].Labirinto[px][py] == 0){
            Mapas[Jogador.Mapa_Escolhido].Labirinto[px][py] = 4;
        } 
        else {
            i--;
        }
    }
}

void Mostra_PlacarVida(){
    string NomeArquivo[12], lido;
    int VidaArquivo[12], DificuldadeArquivo[12];
    fstream Arquivo;

    Arquivo.open("placarvida.txt");
        for (int i = 0; i <10; i++){
            getline(Arquivo, NomeArquivo[i]);
            getline(Arquivo, lido);
            VidaArquivo[i] = stoi(lido);
            getline(Arquivo, lido);
            DificuldadeArquivo[i] = stoi(lido);
        
    }
    Arquivo.close();
    cout << "================================================\n";
    cout << "Nome\t\t" << "Vida Restante\t" << "Dificuldade\n";
    cout << "================================================\n";
    for (int i = 0; i < 10; i++){
        cout << NomeArquivo[i] << "\t\t";
        cout << VidaArquivo[i] << "\t\t";
        cout << DificuldadeArquivo[i] << "\t\n";
    }
    cout << "================================================\n";
}

void Mostra_PlacarPassos(){
    string NomeArquivo[12], lido;
    int PassosArquivo[12], DificuldadeArquivo[12];
    fstream Arquivo;

    Arquivo.open("placarpassos.txt");

    for (int i = 0; i <10; i++){
        getline(Arquivo, NomeArquivo[i]);
        getline(Arquivo, lido);
        PassosArquivo[i] = stoi(lido);
        getline(Arquivo, lido);
        DificuldadeArquivo[i] = stoi(lido);
    }
    cout << "================================================\n";
    cout << "Nome\t\t" << "Passos\t\t" << "Dificuldade\n";
    cout << "================================================\n";
    for (int i = 0; i < 10; i++){
        cout << NomeArquivo[i] << "\t\t";
        cout << PassosArquivo[i] << "\t\t";
        cout << DificuldadeArquivo[i] << "\t\n";
    }
    cout << "================================================\n";
}

void Verificacao_Derrota(Player &Jogador){
    Jogador.Menu = true;
    if (Jogador.Vida == 0){
        system("cls");
        Titulo(R"(
     __     __         //\                      _            
     \ \   / /__   ___|/_\|  _ __   ___ _ __ __| | ___ _   _ 
      \ \ / / _ \ / __/ _ \ | '_ \ / _ \ '__/ _` |/ _ \ | | |
       \ V / (_) | (_|  __/ | |_) |  __/ | | (_| |  __/ |_| |
        \_/ \___/ \___\___| | .__/ \___|_|  \__,_|\___|\__,_|
                            |_|         
        )");
        system("Pause");
    }
}


