#include <iostream>
#include <fstream> //Para leitura e escrita em arquivo
#include <string.h>  //para utilizar strcmp e strlen
#include <windows.h>
#include<conio.h>
#include <ctime>  //para os recursos utilizados na função imprimiHora()
#include <stdio.h>  //para rand() e srand()
#include <stdlib.h>
#include <time.h>   //para clock()
#include <math.h>  //para utilizar fabs()

#define ACIMA 72
#define ABAIXO 80
#define DIREITA 77
#define ESQUERDA 75

#define L 16
#define C 34

using namespace std;

void SetColor(int ForgC)
{
     //Essa função é usada para trocar a cor do texto.
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     //system("PAUSE");
     return;

}

void hidecursor()  //para o curso nao ficar piscando
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void mgotoxy(int x,int y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{x,y});
}

void imprimiHora()
{
  time_t timer;  //cria um Ponteiro para um objeto do tipo time_t, em que o valor de hora é armazenado.

  struct tm *horarioLocal;  //criar uma estrutura para poder salvar varias variaveis(membros) posteriormente

  time(&timer);  //Obtenha o horario atual do calendario como um valor do tipo time_t e define esse valor para o objeto apontado pelo timer.
  horarioLocal = localtime(&timer); /*Retorna um ponteiro para a estutura horarioLocal com seus membros preenchidos com os valores que correspondem
                                    a reprensentação de hora local do timer.*/

  int dia = horarioLocal->tm_mday;  //a seta (->) é para acessar o membro da strutura.
  int mes = horarioLocal->tm_mon + 1;
  int ano = horarioLocal->tm_year + 1900;

  int hora = horarioLocal->tm_hour;
  int min  = horarioLocal->tm_min;
  int sec  = horarioLocal->tm_sec;

  mgotoxy(0,17);
  cout <<endl<<"Horario: " << hora << ":" << min << ":" << sec << endl;
  //cout << "Data: "    << dia  << "/" << mes << "/" << ano << endl;

 // std::string horario = std::to_string(hora) + ":" + std::to_string(min) + ":" + std::to_string(sec);
}

void imprime(int m[L][C],int posicaoDaFormiga_I,int posicaoDaFormiga_J,int tamanhoVisivel,int dificuldade)  //os parametros default são zero para a dificuldade 1
{
    if(dificuldade==1)
    {
        for (int i=0;i<L;i++)  //imprime M mapa todo visivel
        {
            for (int j=0;j<C;j++) {
                if(m[i][j]==1){
                    SetColor(14);
                    cout<<(char)178;  //parede
                    SetColor(15);
                }
                else if(m[i][j]==0){  //espaços vazios
                    cout<<" ";
                }
                else if (m[i][j]==9){  //formiga minuscula f
                    SetColor(12);
                    cout<<"f";
                    SetColor(15);
                }
                else if (m[i][j]==8){  //formiga maiuscula F
                    SetColor(12);
                    cout<<"F";
                    SetColor(15);
                }
                else if(m[i][j]==2){   //T do armazem
                    SetColor(9);
                    cout<<"T";
                    SetColor(15);
                }
                else if(m[i][j]==3){   //1 do armazem 1
                    SetColor(9);
                    cout<<"1";
                    SetColor(15);
                }
                else if(m[i][j]==4){   //2 do armazem 2
                    SetColor(9);
                    cout<<"2";
                    SetColor(15);
                }
                else if(m[i][j]==5){   //3 do armazem 3
                    SetColor(9);
                    cout<<"3";
                    SetColor(15);
                }
                else if(m[i][j]==6){   //3 do armazem 3
                    SetColor(13);
                    cout<<"*";
                    SetColor(15);
                }
                else if(m[i][j]==7){   //ferramenta de Super
                    SetColor(13);
                    cout<<(char)83;    //83 é o codigo do S
                    SetColor(15);
                }
            }
            cout<<"\n";
        }
    }

    if(dificuldade==2)
    {
        mgotoxy(0,0);
        for (int i=0;i<L;i++)  //imprime M mapa parcialmente visivel
        {
            for (int j=0;j<C;j++)
            {
                if(m[i][j]==9){  //formiga minuscula f
                    SetColor(12);
                    cout<<"f";
                    SetColor(15);
                }
                else if(m[i][j]==8){  //formiga maiuscula F
                    SetColor(12);
                    cout<<"F";
                    SetColor(15);
                }
                else if(m[i][j]==1)
                     {
                         if(i>=posicaoDaFormiga_I-tamanhoVisivel && i<=posicaoDaFormiga_I+tamanhoVisivel)
                         {
                             if(j>=posicaoDaFormiga_J-tamanhoVisivel && j<=posicaoDaFormiga_J+tamanhoVisivel)
                             {
                                SetColor(13);
                                cout<<(char)178;  //parede
                                SetColor(15);
                             }
                             else {
                                    SetColor(14);
                                    cout<<"_";
                                    SetColor(15);
                                  }
                         }
                         else {
                                SetColor(14);
                                cout<<"_";
                                SetColor(15);
                              }
                     }
                else if(m[i][j]==0)
                     {
                        if(i>=posicaoDaFormiga_I-tamanhoVisivel && i<=posicaoDaFormiga_I+tamanhoVisivel)
                         {
                             if(j>=posicaoDaFormiga_J-tamanhoVisivel && j<=posicaoDaFormiga_J+tamanhoVisivel)
                             {
                                cout<<" ";  //espaços vazios
                             }
                             else {
                                    SetColor(14);
                                    cout<<"_";
                                    SetColor(15);
                                  }
                         }
                         else {
                                SetColor(14);
                                cout<<"_";
                                SetColor(15);
                              }
                     }
                else if(m[i][j]==2)
                     {
                         if(i>=posicaoDaFormiga_I-tamanhoVisivel && i<=posicaoDaFormiga_I+tamanhoVisivel)
                         {
                             if(j>=posicaoDaFormiga_J-tamanhoVisivel && j<=posicaoDaFormiga_J+tamanhoVisivel)
                             {
                                SetColor(9);
                                cout<<"T"; //T do armazem
                                SetColor(15);
                             }
                             else {
                                    SetColor(14);
                                    cout<<"_";
                                    SetColor(15);
                                  }
                         }
                         else {
                                SetColor(14);
                                cout<<"_";
                                SetColor(15);
                              }
                     }
                else if(m[i][j]==3)  //1 da torre 1
                     {
                         if(i>=posicaoDaFormiga_I-tamanhoVisivel && i<=posicaoDaFormiga_I+tamanhoVisivel)
                         {
                             if(j>=posicaoDaFormiga_J-tamanhoVisivel && j<=posicaoDaFormiga_J+tamanhoVisivel)
                             {
                                SetColor(9);
                                cout<<"1"; //1 do armazem 1
                                SetColor(15);
                             }
                             else {
                                    SetColor(14);
                                    cout<<"_";
                                    SetColor(15);
                                  }
                         }
                         else {
                                SetColor(14);
                                cout<<"_";
                                SetColor(15);
                              }
                     }
                else if(m[i][j]==4)
                     {
                         if(i>=posicaoDaFormiga_I-tamanhoVisivel && i<=posicaoDaFormiga_I+tamanhoVisivel)
                         {
                             if(j>=posicaoDaFormiga_J-tamanhoVisivel && j<=posicaoDaFormiga_J+tamanhoVisivel)
                             {
                                SetColor(9);
                                cout<<"2"; //2 do armazem 2
                                SetColor(15);
                             }
                             else {
                                    SetColor(14);
                                    cout<<"_";
                                    SetColor(15);
                                  }
                         }
                         else {
                                SetColor(14);
                                cout<<"_";
                                SetColor(15);
                              }
                     }
                else if(m[i][j]==5)
                     {
                         if(i>=posicaoDaFormiga_I-tamanhoVisivel && i<=posicaoDaFormiga_I+tamanhoVisivel)
                         {
                             if(j>=posicaoDaFormiga_J-tamanhoVisivel && j<=posicaoDaFormiga_J+tamanhoVisivel)
                             {
                                SetColor(9);
                                cout<<"3"; //3 do armazem 3
                                SetColor(15);
                             }
                             else {
                                    SetColor(14);
                                    cout<<"_";
                                    SetColor(15);
                                  }
                         }
                         else {
                                SetColor(14);
                                cout<<"_";
                                SetColor(15);
                              }
                     }
                     else if(m[i][j]==6)  //* do buraco de minhoca
                     {
                         if(i>=posicaoDaFormiga_I-tamanhoVisivel && i<=posicaoDaFormiga_I+tamanhoVisivel)
                         {
                             if(j>=posicaoDaFormiga_J-tamanhoVisivel && j<=posicaoDaFormiga_J+tamanhoVisivel)
                             {
                                SetColor(13);
                                cout<<"*"; //3 do armazem 3
                                SetColor(15);
                             }
                             else {
                                    SetColor(14);
                                    cout<<"_";
                                    SetColor(14);
                                  }
                         }
                         else {
                                SetColor(14);
                                cout<<"_";
                                SetColor(15);
                              }
                     }
                     else if(m[i][j]==7)  //* do buraco de minhoca
                     {
                         if(i>=posicaoDaFormiga_I-tamanhoVisivel && i<=posicaoDaFormiga_I+tamanhoVisivel)
                         {
                             if(j>=posicaoDaFormiga_J-tamanhoVisivel && j<=posicaoDaFormiga_J+tamanhoVisivel)
                             {
                                SetColor(13);
                                cout<<"S"; //3 do armazem 3
                                SetColor(15);
                             }
                             else {
                                    SetColor(14);
                                    cout<<"_";
                                    SetColor(15);
                                  }
                         }
                         else {
                                SetColor(14);
                                cout<<"_";
                                SetColor(15);
                              }
                     }
            }
            cout<<"\n";
        }
    }

}

void imprimirDeAcordoComDificuldade(int m[L][C],int tamanhoVisivel,int dificuldade)
{
    int posicaoDaFormiga_I, posicaoDaFormiga_J, X_doMgotoxy, Y_doMgotoxy;

    if(dificuldade==1)
    {
        mgotoxy(0,0);
        imprime(m,0,0,0,1);
    }
    if(dificuldade==2)
    {
        for (int i=0;i<L;i++)
        {
            for (int j=0;j<C;j++)
            {
                if(m[i][j]==9)  //para encontrar a formiga e salvar sua posicao
                {
                    posicaoDaFormiga_I=i;
                    posicaoDaFormiga_J=j;
                }
                else if(m[i][j]==8)
                {
                    posicaoDaFormiga_I=i;
                    posicaoDaFormiga_J=j;
                }
             }
         }

        X_doMgotoxy=posicaoDaFormiga_I-tamanhoVisivel;

        Y_doMgotoxy=posicaoDaFormiga_J-tamanhoVisivel;

    //    cout<<"X:"<<X_doMgotoxy; cout<<"Y:"<<Y_doMgotoxy;
    //    mgotoxy(X_doMgotoxy, Y_doMgotoxy);
        imprime(m, posicaoDaFormiga_I, posicaoDaFormiga_J, tamanhoVisivel, dificuldade);
    }

}

int verificaFormigaNoArmazem(int linha, int coluna,int salvaEstadoAnteriorFormiga)
{
    int auxIntertravaPenultimo=0; //****declaracao temporaria

    if(linha==14 && coluna==10 && auxIntertravaPenultimo==0)  //formiga esta em cima do T do T1
    {
        if(salvaEstadoAnteriorFormiga==9) //formiga minuscula
        {
            //verificarTorreOrigem();
            return 91;
        }
        if(salvaEstadoAnteriorFormiga==8) //formiga maiuscula
        {
            //verificarTorreDestino();
            return 81;
        }
    }
    else if(linha==14 && coluna==11 && auxIntertravaPenultimo==0)  //formiga esta em cima do 1 do T1
    {
        if(salvaEstadoAnteriorFormiga==9) //formiga minuscula
        {
            //verificarTorreOrigem();
            return 91;
        }
        if(salvaEstadoAnteriorFormiga==8) //formiga maiuscula
        {
            //verificarTorreDestino();
            return 81;
        }

       // *salvaUltimoArmazemPassado=1;
    }
    else if(linha==14 && coluna==24 && auxIntertravaPenultimo==0)  //formiga esta em cima do T do T2
    {
        if(salvaEstadoAnteriorFormiga==9) //formiga minuscula
        {
            //verificarTorreOrigem();
            return 92;
        }
        if(salvaEstadoAnteriorFormiga==8) //formiga maiuscula
        {
            //verificarTorreDestino();
            return 82;
        }

       // *salvaUltimoArmazemPassado=2;
    }
    else if(linha==14 && coluna==25 && auxIntertravaPenultimo==0)  //formiga esta em cima do 2 do T2
    {
        if(salvaEstadoAnteriorFormiga==9) //formiga minuscula
        {
            //verificarTorreOrigem();
            return 92;
        }
        if(salvaEstadoAnteriorFormiga==8) //formiga maiuscula
        {
           // verificarTorreDestino();
           return 82;
        }

       // *salvaUltimoArmazemPassado=2;
    }
    else if(linha==1 && coluna==31 && auxIntertravaPenultimo==0)  //formiga esta na frente do T do T3
    {
        if(salvaEstadoAnteriorFormiga==9) //formiga minuscula
        {
            //verificarTorreOrigem();
            return 93;
        }
        if(salvaEstadoAnteriorFormiga==8) //formiga maiuscula
        {
            //verificarTorreDestino();
            return 83;
        }

      //  *salvaUltimoArmazemPassado=3;
    }
    else
    { return 0; }

}

void move_formiga(int m[L][C], int *linha, int *coluna, int *salvaEstadoAnteriorFormiga,int *gatilhoIfSaveGame,int *gatilhoImprimeM,int gatilhoFormigaSuper,int *opcaoDoMenu){  //x é linha , y é coluna
  //  static int x=1,y=1;  //static nao perde o valor quando sai da funcao, só será x=1 e y=1 na primeira vez que rodar a funcao
    int x=*linha, y=*coluna;  //x=valor da variavel onde o ponteiro esta apontando.
    char tecla;

     if ( _kbhit() )  //faz leitura de uma letra do teclado
     {
        tecla = getch();   //pega esta letra

        *salvaEstadoAnteriorFormiga=m[x][y]; //para ser utilizado na função verificaFormigaNoArmazem, pq agora a formiga será apagada.

        m[x][y]=0;  //se eu apertar uma tecla, essa linha apaga a posicao anterior da formiga.

        if (tecla == -32)  //para identificar as tecla direcionais(setas) do teclado, é necessario usar getch duas vezes
        {
            tecla=getch();
        }
        if(gatilhoFormigaSuper==0)    //formiga não é super
        {
            switch(tecla)
            {
                case 'w':
                    if(m[x-1][y]==0 || m[x-1][y]==6 )  //para não atravessar parede para cima
                    {
                        x--;   //para cima
                    }
                    break;
                case ACIMA:  //tecla seta para cima
                    if(m[x-1][y]==0 || m[x-1][y]==6 )  //para não atravessar parede para cima
                    {
                        x--;   //para cima
                    }
                    break;
                case 's':
                    if(m[x+1][y]==0 || m[x+1][y]==6)
                    {
                        x++;   //para baixo
                    }
                    break;
                case ABAIXO:  //tecla seta para baixo
                    if(m[x+1][y]==0 || m[x+1][y]==6)
                    {
                        x++;   //para baixo
                    }
                    break;
                case 'a':
                    if(m[x][y-1]==0 || m[x][y-1]==6)
                    {
                        y--;   //esquerda
                    }
                    break;
                case ESQUERDA:
                    if(m[x][y-1]==0 || m[x][y-1]==6)
                    {
                        y--;   //para esquerda
                    }
                    break;
                case 'd':
                    if(m[x][y+1]==0 || m[x][y+1]==6)
                    {
                        y++;    //para direita
                    }
                    break;
                case DIREITA:
                    if(m[x][y+1]==0 || m[x][y+1]==6)
                    {
                        y++;    //para direita
                    }
                    break;
                case 'g':  //precionando a letra 'g' para acionar o gatilho do if dentro do main para a executar a funcao saveGame()
                    *gatilhoIfSaveGame=1;
                    break;
                case 51:  //tecla 3 em ASCII é 51
                    *opcaoDoMenu=3;
                    break;
                default:
                    mgotoxy(0,31);
                    SetColor(12);
                    cout<<"Tecla incorreta. Somente teclas direcionais ou letas w s d a"<<endl;
                    SetColor(15);
                    break;
            } //fim switch case
        } //fim do if

        if(gatilhoFormigaSuper==1)  //formiga em modo Super
        {
            switch(tecla)
            {
                case 'w':
                        x--;   //para cima
                    break;
                case ACIMA:  //tecla seta para cima
                        x--;   //para cima
                    break;
                case 's':
                        x++;   //para baixo
                    break;
                case ABAIXO:  //tecla seta para baixo
                        x++;   //para baixo
                    break;
                case 'a':
                        y--;   //esquerda
                    break;
                case ESQUERDA:
                        y--;   //para esquerda
                    break;
                case 'd':
                        y++;    //para direita
                    break;
                case DIREITA:
                        y++;    //para direita
                    break;
                case 'g':  //precionando a letra 'g' para acionar o gatilho do if dentro do main para a executar a funcao saveGame()
                    *gatilhoIfSaveGame=1;
                    break;
                case 51:  //tecla 3 em ASCII é 51
                    *opcaoDoMenu=3;  //opcao do menu para sair
                    break;
                default:
                    mgotoxy(0,31);
                    SetColor(12);
                    cout<<"Tecla incorreta. Somente teclas direcionais ou letas w s d a"<<endl;
                    SetColor(15);
                    break;
            } //fim switch case
        } //fim do if super formiga

        *linha=x;
        *coluna=y;
        *gatilhoImprimeM=1;
     }
}

void naoSoterrarFormiga(int M[L][C], int *pI, int *pJ)
{
    int i= *pI, j= *pJ;

    while(M[i][j]==1)  //se terá uma parede onde a formiga ficará
    {
        if(j==C)     //verifica se ja esta na ultima coluna
        {
            j=0;     //se estiver na ultima coluna entao volta para primeira
            if(i==L) //se estiver na ultima linha
            { i=0; }  //volta para primeira linha
            else
            { i++; }  //se nao estiver na ultima linha, entao pula para proxima linha primiera coluna j=0;
        }
        else
        { j++; }
    }

    *pI=i;  //salva valor de i no ponteiro pI para ser utilizado na função que chamou esta aqui.
    *pJ=j;

}

void criarArquivoComMatrizes()
{
    int m[L][C]={
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,5},
        {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1},
        {1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,0,1,0,1,1},
        {1,0,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1},
        {1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1},
        {1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
        {1,0,1,0,0,0,0,0,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,0,1,0,1,1,1,1,1,1,0,1,0,0,0,1,0,1,0,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1},
        {1,0,1,0,1,0,0,0,0,0,0,1,0,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,0,1,0,1},
        {1,0,1,0,1,0,1,1,1,1,1,1,0,1,0,1,0,1,1,1,1,0,0,0,1,0,1,1,1,1,0,1,0,1},
        {1,0,1,0,1,1,1,1,1,1,1,0,0,1,0,1,0,0,1,1,1,0,1,0,1,0,1,0,0,0,0,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,1,0,0,0,1,0,0,0,1,0,1,1,1,1,0,1},
        {1,0,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,2,3,1,1,1,1,1,1,1,1,1,1,1,1,2,4,1,1,1,1,1,1,1,1},
    };

    int m1[L][C]={
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//0
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,5},//1
        {1,1,1,1,1,1,1,0,1,7,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1},//2
        {1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,0,1,0,1,1},//3
        {1,0,1,1,6,1,0,1,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1},//4
        {1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1},//5
        {1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1},//6
        {1,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1},//7
        {1,0,1,0,1,1,1,0,1,1,0,1,0,0,0,1,0,1,0,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1},//8
        {1,0,1,0,1,0,0,0,0,0,0,1,0,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,0,1,0,1},//9
        {1,0,1,0,1,0,1,1,1,1,1,1,0,1,0,1,0,1,1,1,1,0,0,0,1,0,1,1,1,1,0,1,0,1},//10
        {1,0,1,0,1,0,1,1,1,1,1,0,0,0,0,1,0,0,1,1,1,0,1,0,1,0,1,0,0,0,0,1,0,1},//11
        {1,0,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,0,0,0,1,0,1,1,6,1,0,1},//12
        {1,0,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,0,1},//13
        {1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//14
        {1,1,1,1,1,1,1,1,1,1,2,3,0,0,1,1,1,1,1,1,1,1,1,1,2,4,1,1,1,1,1,1,1,1},//15
    }; //0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3

    int m2[L][C]={
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,1,1,1,0,2,5},
        {1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1},
        {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,0,1,0,1,1},
        {1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1},
        {1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,7,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,0,0,1},
        {1,1,1,0,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1},
        {1,1,1,0,1,0,0,0,0,0,0,1,0,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,0,1,0,1},
        {1,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,0,1,1,1,1,0,0,0,1,0,1,1,1,1,0,1,0,1},
        {1,1,1,0,1,0,1,1,1,1,1,0,0,1,0,1,0,0,1,1,1,0,1,0,1,0,1,0,0,0,0,1,0,1},
        {1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,0,0,0,1,0,1,1,1,1,0,1},
        {1,1,6,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,0,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,2,3,1,0,1,1,1,1,1,1,1,1,1,1,2,4,1,1,1,1,1,1,1,1},
    }; //0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3

    int m3[L][C]={
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,2,5},
        {1,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1},
        {1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,0,1,0,1,1},
        {1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,1,0,1,1},
        {1,0,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,1,1},
        {1,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,1},
        {1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,1,1},
        {1,0,1,0,1,1,1,1,1,1,0,0,0,0,0,1,0,1,0,1,0,1,1,0,1,0,0,0,0,0,0,0,1,1},
        {1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,1,1,1,1,1,0,1,0,1,1,1,1,0,1,1,1},
        {1,0,1,1,1,0,1,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1},
        {1,0,1,1,1,0,1,1,1,1,1,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,1,1},
        {1,0,1,1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,1,1,1,1,1,0,0,0,1,0,1,1,1,1,0,1},
        {1,0,1,1,1,1,1,1,1,1,1,0,1,1,0,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,2,3,1,0,1,1,1,1,1,1,1,1,1,1,2,4,1,1,1,1,1,1,1,1},
    };

    ifstream objetoParaLeitura("labirinto.txt");  //objeto para leitura de arquivo

    if(objetoParaLeitura == 0)  //se for zero significa que o arquivo nao existe ainda.
    {   //entao criasse um arquivo novo:

        ofstream escreverParaArquivo;  //objeto para escrever em arquivo

        escreverParaArquivo.open("labirinto.txt");  //metodo para criar um arquivo

        //------Para escrever as matrizes no arquivo ----//
        char qualMatriz='a';
        do
        {   escreverParaArquivo<<qualMatriz;
            for (int i=0;i<L;i++)
            {
                for (int j=0;j<C;j++)
                {
                    switch(qualMatriz) //para escolher qual a matris da vez que sera escrita no arquivo
                    {
                        case 'a':
                            escreverParaArquivo<<m[i][j];  //escrevendo a matriz no arquivo
                            break;
                        case 'b':
                            escreverParaArquivo<<m1[i][j];
                            break;
                        case 'c':
                            escreverParaArquivo<<m2[i][j];
                            break;
                        case 'd':
                            escreverParaArquivo<<m3[i][j];
                            break;
                    }
                }
                escreverParaArquivo<<"\n";
            }
            escreverParaArquivo<<"\n"; //para pular uma linha entre as matrizes do arquivo.

            if(qualMatriz=='a')     //esta logica é para que no final do for ele troque a matriz para a proxima a ser escrita
                qualMatriz='b';
            else if(qualMatriz=='b')
                qualMatriz='c';
            else if(qualMatriz=='c')
                qualMatriz='d';
            else if(qualMatriz=='d')
                qualMatriz='e';

        }while(qualMatriz <='d');  //roda até o d, que em decimal pela tabela ASCII é maior que 'a' 'b' 'c'

        escreverParaArquivo.close();
     }

}

void carregarLabirinto (int matriz[L][C], char qual_matriz){  //matriz[L][C] é um ponteiro para matrizAtual
    ifstream lerDoArquivo ("labirinto.txt"); //criar instancia da funcao para ler do arquivo
    char letra;
    char todos_os_caracteres;

       while(letra!=qual_matriz)  //procure a letra em todo o arquivo, quando encontrar salve na variavel letra.
       {
        lerDoArquivo.get(letra);
       }

       if(letra== qual_matriz)  //se chegou na letra que precede a matriz, entao carregue as proximas letra para dentro de matriz vazia.
       {
            for (int i=0;i<L;i++)
            {
                for (int j=0;j<C+1;j++)
                { //após cada linha do arquivo existe um \n
                 lerDoArquivo.get(letra);
                    if (j!=34)
                    {
                                                    //esse if ajuda a ignorar o \n
                        matriz[i][j]=(int)letra-48; //os digitos na tabela ASCII começão em 48 igual a '0',
                    }                               // por isso o valor inteiro da letra (int)letra
                                                    //deve ser diminuido de -48, para termos um resultado em inteiros
                }
            }

        }

}

void SaveGame(int m[L][C],int T,int *t1,int *t2,int *t3,clock_t tempoDeJogo,int movimentos,string nomeAtual)
{
    char tecla;

    //ifstream objetoParaLeitura("saveGame.txt");  //objeto para leitura de arquivo

    ofstream escreverParaArquivo;  //objeto para escrever em arquivo

    escreverParaArquivo.open("saveGame.txt");  //metodo para criar um arquivo

    escreverParaArquivo<<'m';   //m de matriz :escreve um caracter antes da matriz ou da torre para poder localizar depois
    for (int i=0;i<L;i++)
    {
        for (int j=0;j<C;j++)
        {
            escreverParaArquivo<<m[i][j];  //escrevendo a matriz no arquivo
        }
        escreverParaArquivo<<"\n";
    }
    escreverParaArquivo<<"\n";

    escreverParaArquivo<<'T';   //h de hanoy: escreve caracter antes da torre para localizar depois
        escreverParaArquivo<<T;
    escreverParaArquivo<<"\n";

    escreverParaArquivo<<'h';   //h de hanoy: escreve caracter antes da torre para localizar depois
    for (int i=T-1; i>=0; i--)
    {
        escreverParaArquivo<<t1[i];
    }
    escreverParaArquivo<<"\n";

    escreverParaArquivo<<'j';   //escreve a segunda torre
    for (int i=T-1; i>=0; i--)
    {
        escreverParaArquivo<<t2[i];
    }
    escreverParaArquivo<<"\n";

    escreverParaArquivo<<'k';   //escreve a terceira torre
    for (int i=T-1; i>=0; i--)
    {
        escreverParaArquivo<<t3[i];
    }
    escreverParaArquivo<<"\n";

    escreverParaArquivo<<'l';   //escreve o tempo decorrido
        escreverParaArquivo<<tempoDeJogo;
    escreverParaArquivo<<"\n";

    escreverParaArquivo<<'ç';   //escreve a quantidade de movimentos
        escreverParaArquivo<<movimentos;
    escreverParaArquivo<<"\n";

    escreverParaArquivo<<'p';   //escreve a quantidade de movimentos
        escreverParaArquivo<<nomeAtual;
    escreverParaArquivo<<"\n";

    escreverParaArquivo.close();  //fecha o arquivo

    mgotoxy(40,24);
    SetColor(12);
    cout<<"Jogo SALVO com SUCESSO!";
    SetColor(15);

}

void verificarJogoSalvo(int matriz[L][C],int *T,int *t1,int *t2,int *t3,int *tempoJogoSalvo,int *movimentosSalvos,string *nomeAtual)
{
    ifstream lerDoArquivo ("saveGame.txt"); //criar instancia da funcao para ler do arquivo
    char letra;
    string pegandoLinhaTempo, pegandoLinhaMovimentos;
    int tempoComoInteiro, movimentoComoInteiro;
    string nomeDoJogadorSalvo;

    if(lerDoArquivo == 0)  //se for zero significa que o arquivo nao existe ainda.
    {
        mgotoxy(40,19);
        SetColor(12);
        cout<<"Nao existe jogo salvo.";
        SetColor(15);
    }
    else
    {
       while(letra!='m')  //procure a letra em todo o arquivo, quando encontrar salve na variavel letra.
       {
        lerDoArquivo.get(letra);
       }
       if(letra== 'm')  //se chegou na letra que precede a matriz, entao carregue as proximas letra para dentro de matriz vazia.
       {
            for (int i=0;i<L;i++)
            {
                for (int j=0;j<C+1;j++)
                { //após cada linha do arquivo existe um \n
                 lerDoArquivo.get(letra);
                    if (j!=C)
                    {
                                                    //esse if ajuda a ignorar o \n
                        matriz[i][j]=(int)letra-48; //os digitos na tabela ASCII começão em 48 igual a '0',
                                                   // por isso o valor inteiro da letra (int)letra
                                                    //deve ser diminuido de -48, para termos um resultado em inteiros
                    }
                }
            }

        }

        while(letra!='T') //letra que precede o tamanho das torres
        {
            lerDoArquivo.get(letra);
        }
        if(letra== 'T')  //letra que indica o tamanho das torres
        {
           lerDoArquivo.get(letra);
           *T=(int)letra-48;
        }

        while(letra!='h')  //letra que precede a torre 1
        {
            lerDoArquivo.get(letra);
        }
        if(letra=='h')
        {
            for (int i=*T-1; i>=0;i--)
            {
                lerDoArquivo.get(letra);
                t1[i]=(int)letra-48;
                //t1[i]=letra;
            }
        }

        while(letra!='j')  //letra que precede a torre 2
        {
            lerDoArquivo.get(letra);
        }
        if(letra=='j')
        {
            for (int i=*T-1; i>=0;i--)
            {
                lerDoArquivo.get(letra);
                t2[i]=(int)letra-48;
                //t2[i]=letra;
            }
        }

        while(letra!='k')  //letra que precede a torre 3
        {
            lerDoArquivo.get(letra);
        }
        if(letra=='k')
        {
            for (int i=*T-1; i>=0;i--)
            {
                lerDoArquivo.get(letra);
                t3[i]=(int)letra-48;
                //t3[i]=letra;
            }
        }

        while(letra!='l') //letra que precede o tempoDeJogo
        {
            lerDoArquivo.get(letra);
        }
        if(letra== 'l')
        {
            getline(lerDoArquivo, pegandoLinhaTempo); //use a funcao lerDoArquivo para pegar uma linha após a letra l e salva na variavel pegandoLinhaTempo
            tempoComoInteiro = atoi(pegandoLinhaTempo.c_str()); //atoi - transforma a string pegandoLinhaTempo em numero inteiro.
            *tempoJogoSalvo=tempoComoInteiro;
        }

        while(letra!='ç') //letra que precede o tempoDeJogo
        {
            lerDoArquivo.get(letra);
        }
        if(letra== 'ç')
        {
            getline(lerDoArquivo, pegandoLinhaMovimentos); //use a funcao lerDoArquivo para pegar uma linha após a letra l e salva na variavel pegandoLinhaTempo
            movimentoComoInteiro = atoi(pegandoLinhaMovimentos.c_str()); //atoi - transforma a string pegandoLinhaTempo em numero inteiro.
            *movimentosSalvos=movimentoComoInteiro;
        }

        while(letra!='p') //letra que precede o tempoDeJogo
        {
            lerDoArquivo.get(letra);
        }
        if(letra== 'p')
        {
            getline(lerDoArquivo, nomeDoJogadorSalvo); //use a funcao lerDoArquivo para pegar uma linha após a letra l e salva na variavel pegandoLinhaTempo
            *nomeAtual=nomeDoJogadorSalvo;
        }

    }

}

void terremoto(int m[L][C], char *qual_matriz)
{
    int formigaMaiusculaOuMinuscula;

    /* srand(time(NULL)) objetiva inicializar o gerador de números aleatórios
  com o valor da função time(NULL). Este por sua vez, é calculado
  como sendo o total de segundos passados desde 1 de janeiro de 1970
  até a data atual.
  Desta forma, a cada execução o valor da "semente" será diferente.
  */
  srand(time(NULL));  //para que o rand() nao inicie sempre com o mesmo valor;
  switch( rand()%3 )  //rand()%3 retorna numeros aleatorios entre 0 a 2
  {
        case 0:  //imprime matriz numero zero
            for (int i=0;i<L;i++)
            {
                for (int j=0;j<C;j++)
                {
                    if(m[i][j]==9 || m[i][j]==8)  //se a formiga esta aqui
                    {
                        formigaMaiusculaOuMinuscula=m[i][j]; //salva se a formiga é maiscula ou minuscula para imprimila no final desta logica m1[i][j]
                        m[i][j]=0;  //apaga a posição antiga da formiga.

                        int pI, pJ;
                        pI=i;
                        pJ=j;
                        *qual_matriz='b';
                        carregarLabirinto(m, *qual_matriz);  //passar a matriz m1 para ser carregada pela matriz b do arquivo;
                        naoSoterrarFormiga(m, &pI, &pJ);
                        i= pI;    //depois de pI e pJ serem atualizados na função acima, eles retornam para atualizar o i e o j
                        j= pJ;
                        m[i][j]=formigaMaiusculaOuMinuscula;
                    }

                }
            }
            break;

        case 1:  //imprime matriz numero 1
            for (int i=0;i<L;i++)
            {
                for (int j=0;j<C;j++)
                {
                    if(m[i][j]==9 || m[i][j]==8)  //se a formiga esta aqui
                    {
                        formigaMaiusculaOuMinuscula=m[i][j]; //salva se a formiga é maiscula ou minuscula para imprimila no final desta logica m1[i][j]
                        m[i][j]=0;  //apaga a posição antiga da formiga.

                        int pI, pJ;
                        pI=i;
                        pJ=j;
                        *qual_matriz='c';
                        carregarLabirinto(m, *qual_matriz);
                        naoSoterrarFormiga(m, &pI, &pJ);
                        i= pI;    //depois de pI e pJ serem atualizados na função acima, eles retornam para atualizar o i e o j
                        j= pJ;
                        m[i][j]=formigaMaiusculaOuMinuscula;
                    }
                }
            }
            break;

        case 2:  //imprime matriz numero 2
            for (int i=0;i<L;i++)
            {
                for (int j=0;j<C;j++)
                {
                    if(m[i][j]==9 || m[i][j]==8)  //se a formiga esta aqui
                    {
                        formigaMaiusculaOuMinuscula=m[i][j];
                        m[i][j]=0;  //apaga a posição antiga da formiga.

                        int pI, pJ;
                        pI=i;
                        pJ=j;
                        *qual_matriz='d';
                        carregarLabirinto(m, *qual_matriz);
                        naoSoterrarFormiga(m, &pI, &pJ);
                        i= pI;    //depois de pI e pJ serem atualizados na função acima, eles retornam para atualizar o i e o j
                        j= pJ;
                        m[i][j]=formigaMaiusculaOuMinuscula;
                    }
                }
            }
            break;
  }

}

int verificarTorreDestino(int torreDestino[],int T,int *guardaPosicaoDestino)
{
    int valorNoDestino;

    for(int i=T-1; i>=0; i--)  //roda todas as posições da torre destino até encontrar um numero igual a zero.
    {
        if(torreDestino[i]!=0)  //quando encontrar um numero igual a zero, chama para verificar se o numero origem é menor que o destino
        {
            *guardaPosicaoDestino=i;  //ponteiro que salva direto no endereço da guardaPosicaoDestino lá do Main.
            valorNoDestino=torreDestino[i];
            return valorNoDestino;
            break;   //interrop o laço FOR
        }
        else if(i==0)  //se na posicao for igual a zero, verifica se esta é a primeira posição, entao retorna ela.
        {
            *guardaPosicaoDestino=i;  //ponteiro que salva direto no endereço da guardaPosicaoDestino lá da Main.
            return torreDestino[i];
        }
    }
}

int verificarTorreOrigem(int torreOrigem[],int T,int *guardaPosicaoOrigem)
{
    int valorDaOrigem=0;

    for(int i=T-1; i>=0; i--)  //roda todas as posições da torre 1 até encontrar um numero maior que zero.
        {
            if(torreOrigem[i]!=0)  //quando encontrar um numero maior que zero , chama para verificar a torre de destino
            {
                *guardaPosicaoOrigem=i;  //ponteiro que salva direto no endereço da guardaPosicaoTorreOrigem presente no Main.
                valorDaOrigem=torreOrigem[i];  //salva o valor, pq depois o torreOrigem[i] vai para zero.
                return valorDaOrigem;  //retorna o primeiro valor de cima para baixo diferente de zero da torre de origem
                break;   //interrop o laço FOR
            }
        }
}

void torreDeHanoi(int estadoDaFormiga,int torreOrigemOuDestino,int *t1,int *t2,int *t3,int T,int *movimentos,int *novoEstadoFormiga,int *acabou,int *gatilhoRanking)
{
   static int *torreOrigem, *torreDestino;  //para apontar para toda a torre de origem ou torre de destino
   static int valorDaOrigem, valorNoDestino;
   static int guardaPosicaoOrigem=1000, guardaPosicaoDestino=1000;
   static int intertrava=0;

   //torre de Origem:
    if(intertrava==0)  //para entrar somente uma vez na torre de origem
    {
        if(estadoDaFormiga==9)  //formiga minuscula entao pega da torre de origem
        {
            switch(torreOrigemOuDestino)  //Qual é a torre de origem
            {
                case  1:
                    valorDaOrigem=verificarTorreOrigem(t1, T, &guardaPosicaoOrigem);  //retorna o primeiro valor de cima para baixo diferente de zero da torre de origem.
                    torreOrigem=t1;
                    intertrava=1;  //intertravamento para logica de comparação valorOrigem ValorDestino
                    *novoEstadoFormiga=8; //após pegar o alimento o novoEstadoFormiga= maiuscula
                    break;
                case 2:
                    valorDaOrigem=verificarTorreOrigem(t2, T, &guardaPosicaoOrigem);
                    torreOrigem=t2;   //salvo em um ponteiro dinamico a matriz deste movimento
                    intertrava=1;  //intertravamento para logica de comparação valorOrigem ValorDestino
                    *novoEstadoFormiga=8; //após pegar o alimento o novoEstadoFormiga= maiuscula
                    break;
                case 3:
                    valorDaOrigem=verificarTorreOrigem(t3, T, &guardaPosicaoOrigem);
                    torreOrigem=t3;   //salvo em um ponteiro dinamico a matriz deste movimento
                    intertrava=1;  //intertravamento para logica de comparação valorOrigem ValorDestino
                    *novoEstadoFormiga=8; //após pegar o alimento o novoEstadoFormiga= maiuscula
                    break;
                default:
                    mgotoxy(0,33);
                    SetColor(12);
                    cout<<"Torre invalida"<<endl;
                    SetColor(15);
                    break;
            }
        }

    }
    //torre de Destino:
    else if(intertrava==1)  //para somente rodar esta logica depois de passar pela Origem
    {
        if(estadoDaFormiga==8)  //formiga maiuscula entao esta será a torre de destino
        {
            switch(torreOrigemOuDestino)  //Qual é a torre de Destino
            {
                case 1:
                    valorNoDestino=verificarTorreDestino(t1, T, &guardaPosicaoDestino);
                    torreDestino=t1;
                    intertrava++;  //intertravamento para logica de comparação valorOrigem ValorDestino
                    *novoEstadoFormiga=9; //após soltar o alimento o novoEstadoFormiga= minuscula
                    break;
                case 2:
                    valorNoDestino=verificarTorreDestino(t2, T, &guardaPosicaoDestino);
                    torreDestino=t2;
                    intertrava++;  //intertravamento para logica de comparação valorOrigem ValorDestino
                    *novoEstadoFormiga=9; //após soltar o alimento o novoEstadoFormiga= minuscula
                    break;
                case 3:
                    valorNoDestino=verificarTorreDestino(t3, T, &guardaPosicaoDestino);
                    torreDestino=t3;
                    intertrava++;
                    *novoEstadoFormiga=9;
                    break;
                default:
                    mgotoxy(0,34);
                    SetColor(12);
                    cout<<"Torre invalida"<<endl;
                    SetColor(15);
                    break;
            }
        }

    }
    else if(intertrava==2)  //para somente rodar esta logica depois de passar pela Origem e chegar no Destino
    {
        intertrava=0;

        if(valorNoDestino > valorDaOrigem) //se o valorNoDestino > valorDaOrigem ou se for a posicao zero no destino
        {
            if(guardaPosicaoDestino==T-1 && valorNoDestino==1)  //no inicio do programa se a pessoa for na torre 2 ou 3 e pegar o zero e tentar colocar em cima do 1 da primeira posição da torre 1, o programa nao vai deixar.
            {
                mgotoxy(0,31);
                *movimentos=*movimentos+1;
                SetColor(12);
                cout<<"Este movimento nao e' possivel."<<endl<<endl;
                SetColor(15);
            }
            else if(guardaPosicaoDestino!=0) //se não é a primeira posição da torre de Destino, entao salva na proxima posição.
            {
                torreDestino[guardaPosicaoDestino+1]=valorDaOrigem;
                torreOrigem[guardaPosicaoOrigem]=0;
                *movimentos=*movimentos+1;
            }
            else  if(valorNoDestino !=0 )//se for a primeira posição da torre de Destino, verifica se já tem valor nela.
            {
                torreDestino[guardaPosicaoDestino+1]=valorDaOrigem;
                torreOrigem[guardaPosicaoOrigem]=0;
                *movimentos=*movimentos+1;
            }
            else
            {
                mgotoxy(0,30);
                *movimentos=*movimentos+1;
                SetColor(12);
                cout<<endl<<"Este movimento nao e' possivel."<<endl<<endl;
                SetColor(15);
            }
        }
        else if(valorNoDestino< valorDaOrigem)  //se o valor do destinoo for menor que o de origem, verificar se é a primeira posição e se ela esta vazia
        {
            if(valorNoDestino==0 && guardaPosicaoDestino==0)  //se for a primeira posição da torre de Destino, e o valor contido nela for zero, entao salva em cima deste.
            {
                torreDestino[guardaPosicaoDestino]=valorDaOrigem;
                torreOrigem[guardaPosicaoOrigem]=0;
                *movimentos=*movimentos+1;
            }
            else
            {
                mgotoxy(0,31);
                *movimentos=*movimentos+1;
                SetColor(12);
                cout<<"Este movimento nao e' possivel."<<endl<<endl;
                SetColor(15);
            }
        }

    }

        if(t2[T-1]==1)
        {
            *gatilhoRanking=1;

            *acabou=1;
            SetColor(2);
            cout<<endl<<"YOU WIN!!";
            SetColor(15);
        }
        if(t3[T-1]==1)
        {
            *gatilhoRanking=1;

            *acabou=1;
            SetColor(2);
            cout<<endl<<"YOU WIN!!";
            SetColor(15);
        }

}

void ferramentasNoCaminho(int m[L][C],int *i,int *j)
{
    if(*i==4 && *j==4)  //buraco de minhoca lado esquerdo superior
    {
        *i=11;
        *j=30;
    }
    if(*i==12 && *j==30)  //minhoca lado direito inferior
    {
        *i=3;
        *j=4;
    }
    if(*i==13 && *j==2)
    {
        *i=1;
        *j=26;
    }
    if(*i==1 && *j==27)
    {
        *i=14;
        *j=2;
    }
}

struct NomeTempo
{
    string nome;
    int tempo;
};

struct NomeTempo jogadores[11];  //declaração de um vetor do tipo da strutu

void ranking(NomeTempo jogadores[11],string nomeAtual,int tempoDeJogoAtual,int *opcaoDoMenu)
{
   string pegandoLinhaNome, pegandoLinhaTempo;
   int tempoComoInteiro;
   string nomeatual;
   int gatilhoSubstituicao=0;

   ifstream objetoParaLeitura("ranking.txt");  //objeto para leitura de arquivo

   //quando o arquivo ranking EXISTE
   if(objetoParaLeitura != 0)  //se o arquivo ja existe
    {
        for(int i=0;i<10;i++)  //leia todo o arquivo ranking
        {
            getline(objetoParaLeitura, pegandoLinhaNome);  //pega uma linha inteira como string
            getline(objetoParaLeitura, pegandoLinhaTempo);

            jogadores[i].nome=pegandoLinhaNome;  //guarda a string pegandoLinhaTempo em jogadores[i].nome

            tempoComoInteiro=atoi(pegandoLinhaTempo.c_str());  //atoi transforma uma string em um inteiro
            jogadores[i].tempo=tempoComoInteiro;
        }

        jogadores[10].nome=nomeAtual;  //substitui a posicao 11° pelo atual
        jogadores[10].tempo=tempoDeJogoAtual;

        for(int i=1;i<11;i++)  //logica inserir o novo jogadores dentre os 10 primeiros
        {
            if(jogadores[i].tempo!=0 && jogadores[i-1].tempo==0 && (i-1)>=0 && gatilhoSubstituicao==0) //quando o anterior ainda é zero, os 10 ainda nao foram preenchidos
            {
                jogadores[i-1].nome=jogadores[10].nome;
                jogadores[i-1].tempo=jogadores[10].tempo;
                gatilhoSubstituicao=1;
            }
            if( jogadores[10].tempo < jogadores[i].tempo && gatilhoSubstituicao==0 && jogadores[i-1].tempo!=jogadores[10].tempo && (i-1)>=0) //quando jogador 0 for diferente de zero é porque os 10 foram preenchidos, entao pode subistituir um deles
            {
                if(jogadores[0].tempo!=0)
                {
                    jogadores[i].nome=jogadores[10].nome;
                    jogadores[i].tempo=jogadores[10].tempo;
                    gatilhoSubstituicao=1;  //para nao entrar novamente o substituir os outros do ranking que sao maiores do que o atual
                }
            }
        }

        for(int a=0;a<10;a++)  //logica para colocar em ordem crescente,
        {
            for(int b=0;b<10;b++)
            {
                if(jogadores[a].tempo<jogadores[b].tempo)
                {
                    int auxTempo;
                    string auxNome;
                    auxTempo=jogadores[a].tempo;
                    auxNome=jogadores[a].nome;
                    jogadores[a].tempo=jogadores[b].tempo;
                    jogadores[a].nome=jogadores[b].nome;
                    jogadores[b].tempo=auxTempo;
                    jogadores[b].nome=auxNome;
                }
            }
        }

        ofstream escreverParaArquivo;  //objeto para escrever em arquivo

        escreverParaArquivo.open("ranking.txt");  //metodo para criar um arquivo

        for(int i=0;i<10;i++)
        {
            escreverParaArquivo<<jogadores[i].nome<<"\n";
            escreverParaArquivo<<jogadores[i].tempo<<"\n";
        }
        escreverParaArquivo.close();

    }

    //quando o arquivo ranking NAO EXISTE
    if(objetoParaLeitura == 0)  //se for zero significa que o arquivo nao existe ainda.
    {
            jogadores[9].nome=nomeAtual;  //substitui a posicao 10° pelo atual
            jogadores[9].tempo=tempoDeJogoAtual;

            ofstream escreverParaArquivo;  //objeto para escrever em arquivo

            escreverParaArquivo.open("ranking.txt");  //metodo para criar um arquivo

            for(int i=0;i<10;i++)
            {
                escreverParaArquivo<<jogadores[i].nome<<"\n";
                escreverParaArquivo<<jogadores[i].tempo<<"\n";
            }
            escreverParaArquivo.close();
    }

    system("cls");  //para limpar a tela
    mgotoxy(52,20);
    SetColor(10);
    cout<<"Sr. "<<jogadores[10].nome<<" seu tempo foi: "<<jogadores[10].tempo<<"seg";
    SetColor(15);
    mgotoxy(52,22);
    SetColor(9);
    cout<<"RANCKING:";
    SetColor(15);
    SetColor(11);
    for(int i=0;i<10;i++)
    {
        if(jogadores[i].tempo!=0)
        {
            mgotoxy(52,23+i);
            cout<<jogadores[i].nome<<" "<<jogadores[i].tempo<<endl;
        }
    }
    SetColor(15);

    int opcao=0;
    mgotoxy(40,14);
    SetColor(11);
    cout<<"Deseja Sair ou iniciar um Novo Jogo?";
    mgotoxy(40,15);
    cout<<"Digite 3-para Sair. 2-para Menu Inicial";
    mgotoxy(40,16);
    cout<<"Opcao: ";
    SetColor(15);
    SetColor(10);
    cin>>opcao;
    SetColor(15);
    if(opcao==3)  //encerrar o programa
    {
        exit(0);
    }
    else if(opcao==2)  //para voltar ao menu principal
    {
        *opcaoDoMenu=0;
        system("cls");  //para limpar a tela
    }

}

void musicaEndGame()
{
            Beep(660,100);Sleep(150); //Beep que faz a emissão do som de ganhador
            Beep(660,100);Sleep(300);
            Beep(660,100);Sleep( 300);
            Beep(510,100);Sleep( 100);
            Beep(660,100);Sleep( 300);
            Beep(770,100);Sleep( 550);
            Beep(380,100);Sleep( 575);
            Beep(510,100);Sleep( 450);
            Beep(380,100);Sleep( 400);
            Beep(320,100);Sleep( 500);
            Beep(440,100);Sleep( 300);
            Beep(480,80);Sleep( 330);
            Beep(450,100);Sleep( 150);
            Beep(430,100);Sleep( 300);
            Beep(380,100);Sleep( 200);
            Beep(660,80);Sleep( 200);
            Beep(760,50);Sleep( 150);
            Beep(860,100);Sleep( 300);
            Beep(700,80);Sleep( 150);
            Beep(760,50);Sleep( 350);

}


int main()
{
    int opcaoDoMenu=0;

do    //do{}while que engloba todo o programa para só terminar o jogo de acordo com a opcao igual a sair
{
    int m[L][C];
    char qual_matriz='a';
    int gatilhoImprimeM=0;
    int T;
    int t1[15], t2[15], t3[15];
    int torreOrigemOuDestino;  //numero referente a torre de origem ou destino
    int movimentos=0, movimentosSalvos=0;
    int salvaEstadoAnteriorFormiga=9, novoEstadoFormiga;
    int formigaNoArmazem=0, estadoDaFormiga=0;
    int acabou=0;
    int cont=0;
    clock_t tempoDeJogo=0, tempoTerremoto=0, tempoAntesDeUmaOpcao;  //variaveis para o cronometro
    int tempoJogoSalvo=0;
    char tecla;
    int gatilhoIfSaveGame=0;
    int dificuldade=2, X_doMgotoxy, Y_doMgotoxy, posicaoDaFormiga_I, posicaoDaFormiga_J, tamanhoVisivel=4;
    int estadoAntesDoBuraco, gatilhoFormigaSuper=0;
    int gatilhoRanking=0, tempoDeJogoAtual;
    string nomeAtual;

    system("MODE con cols=100 lines=40");  //para editar o tamanho da tela Prompt que será aberta.

    criarArquivoComMatrizes();

    //Menu e objetivos
    mgotoxy(40,1);
    SetColor(11);
    cout<<"Menu selecione uma opcao:";
    mgotoxy(40,2);
    cout<<"1 - Novo jogo.";
    mgotoxy(40,3);
    cout<<"2 - Continuar jogo salvo.";
    mgotoxy(40,4);
    cout<<"3 - Sair.";
    mgotoxy(40,5);
    cout<<"4 - Informacoes dos Autores. ";
    mgotoxy(40,6);
    cout<<"Opcao: ";
    SetColor(15);
    SetColor(10);
    cin>>opcaoDoMenu;
    SetColor(15);

    if(opcaoDoMenu==4)  //informações sobre autores
    {
        mgotoxy(40,10);
        SetColor(9);
        cout<<"Autores do Programa:";
        SetColor(15);
        mgotoxy(40,11);
        SetColor(11);
        cout<<"Giulio C.F.";
        mgotoxy(40,12);
        cout<<"Eder";
        SetColor(15);

        mgotoxy(40,16);
        SetColor(11);
        cout<<"Escolha uma nova opcao:";
        mgotoxy(40,17);
        cout<<"Opcao: ";
        SetColor(15);
        SetColor(10);
        cin>>opcaoDoMenu;
        SetColor(15);

        mgotoxy(40,10);
        cout<<"                           ";
        mgotoxy(40,11);
        cout<<"                           ";
        mgotoxy(40,12);
        cout<<"                           ";
        mgotoxy(40,16);
        cout<<"                           ";
        mgotoxy(40,17);
        cout<<"                           ";
    }

  if(opcaoDoMenu!=4 && opcaoDoMenu!=3) //4 é a opcao somente para ver os autores do programa e depois voltar para o menu principal
  {
      if(opcaoDoMenu!=2)
      {
          mgotoxy(40,7);
          SetColor(11);
          cout<<"Digite seu nome: ";
          SetColor(15);
          SetColor(10);
          cin>>nomeAtual;
          SetColor(15);
      }
        mgotoxy(40,8);
        SetColor(11);
        cout<<"Seleciona a dificuldade ";
        mgotoxy(40,9);
        cout<<"1 - facil, 2 - medio. Diculdade: ";
        SetColor(15);
        SetColor(10);
        cin>>dificuldade;
        SetColor(15);

        mgotoxy(40,10);
        SetColor(9);
        cout<<"Precione a tecla 'g' a qualquer";
        mgotoxy(40,11);
        cout<<"momento para salvar o jogo. ";
        SetColor(15);

        mgotoxy(40,13);
        SetColor(11);
        cout<<"Objetivo: transferir todos os";
        mgotoxy(40,14);
        cout<<"numeros da torre 1 para a torre";
        mgotoxy(40,15);
        cout<<"2 ou 3, porem nao e possivel ";
        mgotoxy(40,16);
        cout<<"colocar um numero maior em cima";
        mgotoxy(40,17);
        cout<<"de um menor.";
        mgotoxy(40,18);
        cout<<"O status f nao esta carregando nada,";
        mgotoxy(40,19);
        cout<<"e o status F esta carregando um numero.";
        SetColor(15);

        tempoAntesDeUmaOpcao=clock()/1000;

        if(opcaoDoMenu==2)  //continuar jogo salvo
        {
            verificarJogoSalvo(m, &T, t1, t2, t3, &tempoJogoSalvo, &movimentosSalvos, &nomeAtual);
            movimentos= movimentos+movimentosSalvos;
        }
        if(opcaoDoMenu==1)  //Novo jogo
        {
            carregarLabirinto(m, qual_matriz);  //passa uma matriz vazia para ser preenchida por qual_matriz for escolhida, a principio
                                                //será a matriz 0 e depois do terremoto o qual_matriz mudará
            mgotoxy(40,21);
            SetColor(11);
            cout<<"Digite o tamanho da torre: ";
            SetColor(15);
            SetColor(10);
            cin>>T;
            SetColor(15);
            //preenche as TORRES iniciais
            for (int i=0; i<T;i++)
            {
                t1[i]=T-i;
                t2[i]=0;
                t3[i]=0;
            }
            tempoAntesDeUmaOpcao=clock()/1000;  //para atualizar o tempo caso a pessoa demore para escolher o tamaho da torre
        }

        hidecursor(); //para esconder o cursor

        imprimirDeAcordoComDificuldade(m, tamanhoVisivel, dificuldade);

        while(acabou!=1)  //enquanto a T2 ou a T3 não estiverem completas
        {
            for (int i=0;i<L;i++)
                {
                    for (int j=0;j<C;j++)
                    {
                        if(m[i][j]==9 || m[i][j]==8)
                        {
                            move_formiga(m, &i, &j, &salvaEstadoAnteriorFormiga, &gatilhoIfSaveGame, &gatilhoImprimeM, gatilhoFormigaSuper, &opcaoDoMenu);
                            formigaNoArmazem= verificaFormigaNoArmazem(i,j,salvaEstadoAnteriorFormiga); //formigaNoArmazem irá salvar o estado da formiga 9 ou 8 e se ela esta na frente do armazem ex:91 (minuscula na frente do armazem 1)
                            if(formigaNoArmazem!=0)  //se esta estiver na frente de algum armazem
                            {
                                estadoDaFormiga=formigaNoArmazem/10; //se for 91/10=9 formiga minuscula vai pegar material na torre de Origem
                                torreOrigemOuDestino=formigaNoArmazem%10; //se for 91%10=1 significa que a formiga esta na frente do armazem 1.
                                torreDeHanoi(estadoDaFormiga, torreOrigemOuDestino, t1, t2, t3, T, &movimentos, &novoEstadoFormiga, &acabou, &gatilhoRanking);
                                m[i][j]=novoEstadoFormiga; //de acordo com o que acontecer na torre de Hanoi a formiga muda de estado f ou F.
                            }
                            else //formigaNoArmazem=0  se a formiga nao estiver na frente de nenhum armazem
                            {
                                m[i][j]=salvaEstadoAnteriorFormiga; //após mover a formiga, como ela nao esta na frente de nenhum armazem, entao continua com o estado da formiga anterior
                            }

                            if(gatilhoIfSaveGame==1)  //variavel auxiliar que é atualizada dentro do moviformiga precionando a letra 'g para salvar o jogo'
                            {
                                    SaveGame(m, T, t1, t2, t3, tempoDeJogo, movimentos, nomeAtual);   //funcao que salva ou verifica se existe um jogo
                                    gatilhoIfSaveGame=0;
                            }

                            if( (i==4&&j==4)||(i==12&&j==30)||(i==13&&j==2)||(i==1&&j==27) )  //formiga no buraco de minhoca
                            {
                                estadoAntesDoBuraco=m[i][j];
                                m[i][j]=0;                        //apaga a formiga
                                ferramentasNoCaminho(m, &i, &j);
                                m[i][j]=estadoAntesDoBuraco;      //recoloca a formiga no seu novo lugar
                                imprimirDeAcordoComDificuldade(m, tamanhoVisivel, dificuldade); //imprime a matriz novamente
                            }
                            if( (i==3&&j==9)||(i==7&&j==14) )   //formiga no Super
                            {
                                gatilhoFormigaSuper=1;
                            }
                        }
                    }
                }

            if(gatilhoImprimeM==1) //vai para 1 após movimentos da formiga.
            {
                imprimirDeAcordoComDificuldade(m, tamanhoVisivel, dificuldade);
                gatilhoImprimeM=0; //volta para zero para nao ficar imprimindo constantemente
            }

            imprimiHora();

            tempoDeJogo = clock()/1000 +tempoJogoSalvo-tempoAntesDeUmaOpcao; //divide por mil para transformar de milesegundos para segundos.
            cout<<"Cronometro: "<<tempoDeJogo<<" seg"<<endl;

            if(opcaoDoMenu==3)  //opcao do menu para sair, que é atulizada la no moveformiga.
            {
                int opcao=0;
                mgotoxy(40,23);
                SetColor(11);
                cout<<"Deseja realmente sair ou voltar para o jogo?";
                mgotoxy(40,24);
                cout<<"Digite 3-para Sair. 1-para Voltar. 2-para Menu Inicial";
                mgotoxy(40,25);
                cout<<"Opcao: ";
                SetColor(15);
                SetColor(10);
                cin>>opcao;
                SetColor(15);
                if(opcao==3)
                {
                    exit(0);
                }
                else if(opcao==1)
                {
                    opcaoDoMenu=0;  //para nao entrar mais no if anterior e voltar a rodar o while
                }
                else if(opcao==2)  //para voltar ao menu principal
                {
                    opcaoDoMenu=0;
                    system("cls");  //para limpar a tela
                    break;
                }
            }

            mgotoxy(0,21);
            SetColor(9);
            cout<<"Movimentos: "<<movimentos<<"\n\n1\t2\t3\n-----------------\n";

            for (int i=T-1; i>=0;i--){  //imprime as 3 torres
                cout<<t1[i]<<"\t"<<t2[i]<<"\t"<<t3[i]<<"\n";
            }
            SetColor(15);

            if(tempoDeJogo-tempoTerremoto >=5)  //inicia um terremoto a cada 5seg
            {
                tempoTerremoto=clock()/1000;
                terremoto(m, &qual_matriz);

                gatilhoFormigaSuper=0;  //a formiga perde o super após um terremoto

                cont++;
                if(cont==1)  //para apagar após um tempo o erro de "Este movimento nao é possivel."
                {
                    cont=0;
                    mgotoxy(40,23);
                    cout<<"                                                                   "; //para apagar o "Este movimento nao e' possivel."
                    mgotoxy(40,24);
                    cout<<"                                                                   ";
                    mgotoxy(40,25);
                    cout<<"                                                                   ";
                }
            }

            if(gatilhoRanking==1)
            {
                gatilhoRanking=0;
                tempoDeJogoAtual=tempoDeJogo;
                musicaEndGame();
                ranking(jogadores, nomeAtual, tempoDeJogoAtual, &opcaoDoMenu);  //jogadores é o vetor do tipo struct
            }

            if(opcaoDoMenu==3)
            {
                break;
            }

        } //fim do while
  } //fim do if(opcaoDoMenu!=4)

  if(opcaoDoMenu==3)  //opcao do menu para sair, que é atulizada la no moveformiga.
    {
        int opcao=0;
        mgotoxy(40,23);
        SetColor(11);
        cout<<"Deseja realmente sair ou voltar para o jogo?";
        mgotoxy(40,24);
        cout<<"Digite 3-para Sair. 1-para Voltar. 2-para Menu Inicial";
        mgotoxy(40,25);
        cout<<"Opcao: ";
        SetColor(15);
        SetColor(10);
        cin>>opcao;
        SetColor(15);
        if(opcao==3)
        {
            exit(0);
        }
        else if(opcao==1)
        {
            opcaoDoMenu=0;  //para nao entrar mais no if anterior e voltar a rodar o while
        }
        else if(opcao==2)  //para voltar ao menu principal
        {
            opcaoDoMenu=0;
            system("cls");  //para limpar a tela
            //break;
        }
    }


}while(opcaoDoMenu!=3);
    return 0;
} //fim do main
