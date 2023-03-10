//Realizzato da Habili e Simnica
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <sys/ioctl.h>
#include "color.hpp"
using namespace std;
using namespace Color;

const int N=10; //grandezza mappa
int contlAff[4]; // vettore coordinate
int giocatori[2]; //numero giocati

//funzione per centrare scritte 
////////////////////////////////////////////////////
int get_console_width()                           //
{                                                 // 
    struct winsize w;                             //
    ioctl(0, TIOCGWINSZ, &w);                     //
    return w.ws_col;                              //
}                                                 //
int screen_width = get_console_width();           //   
int string_width = 70;                            //
int padding = (screen_width - string_width) / 2;  //
////////////////////////////////////////////////////

//prototipi
void menu1(); //Amodeo
void menu2(); //Canucciari
void difficile(char difesa1[][N], char attacco1[][N], char difesa2[][N], char attacco2[][N], int N); //Modalità gioco 2 giocatori
void cpu(char difesa1[][N], char attacco1[][N], char difesa2[][N], char attacco2[][N], int N); //funzione per giocare contro il computer
bool validaPos(char mappa[][N], int x, int y, int direzione, int nav);//funzione per validare la posizioni delle navi per non piazzarle accanto 
void inizMappa(char mappa[][N], int N); // inizializza le mappa di gioco
void stampa(char mappa[][N], int N); // stampa la mappa
void stampa2(char mappa1[N], char mappa2[][N], int giocatore); // stampa le due mappe
void piazzaNav(char mappa[][N], int N); // funzione per piazzare le navi nella mappa
void casualNav(char mappa[][N], int N); // funzione per piazzare le navi nella mappa in modo casuale
void attacco(char mappa1[][N],char mappa2[][N],int x, int y, int giocatore); //funzione per attaccare le navi
void checkNave(char mappa[][N], int x, int y); // funzione che controll se le nave è stata affondata
string affondato(char mappa, int giocatore);// funzione per controllare se una nave è affondata
void logo(); // Battaglia Navale
void regole(); // Regole
//Amodeo
void cerca(char M[][N], int N);
void semplice();

//main
int main()
{
    char scelta;
    logo();
    cout<<setw(padding)<<" ";
    cout<<"Realizzato da Habili Ragip e Simnica Ylli"<<endl;
    system("clear");   
    do
    {
        cout<<endl;
        cout<<setw(padding)<<" ";
        cout<<"Conosci le regole del gioco? Digita y per (si) o n per (no): ";
        cin>>scelta;
    }while(scelta != 'n' && scelta != 'y' );
    if(scelta == 'n')
        regole();
    menu1(); 
    
    return 0;
}

//funzioni

//menu
void menu1()
{
    int scelta;
    bool esci=false;
    
    while (!esci) 
    {
        system("clear");
        cout<<setw(padding)<<" ";
        cout<<color(MAGENTA)<<"███╗   ███╗███████╗███╗   ██╗██╗   ██╗"<<endl;
        cout<<setw(padding)<<" ";
        cout<<"████╗ ████║██╔════╝████╗  ██║██║   ██║"<<endl;
        cout<<setw(padding)<<" ";
        cout<<"██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║"<<endl;
        cout<<setw(padding)<<" ";
        cout<<"██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║"<<endl;
        cout<<setw(padding)<<" ";
        cout<<"██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝"<<endl;
        cout<<setw(padding)<<" ";
        cout<<"╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝ "<<color(DEFAULT)<<endl<<endl<<endl;;
        cout<<setw(padding)<<" ";
        cout<<"Scegli la modalita': "<<endl;
        cout<<setw(padding)<<" ";
        cout<<"1. semplice"<<endl;
        cout<<setw(padding)<<" ";
        cout<<"2. Difficile"<<endl;
        cout<<setw(padding)<<" ";
        cout<<"3. Esci"<<endl;
        cout<<setw(padding)<<" ";
        cout<<"Inserisci il numero della tua scelta: ";
        cin>>scelta;
        
        switch (scelta) 
        {
            case 1:
                semplice();
                break;
            case 2:
                menu2();
                break;
            case 3:
                cout<<setw(padding)<<" ";
                cout<<"Arrivederci!"<<endl;
                esci=true;
                break;
            default:
                cout<<setw(padding)<<" ";
                cout<<"Scelta non valida, riprova."<<endl;
                break;
        }
    }
}

void menu2()
{
    char difesa1[N][N], attacco1[N][N],difesa2[N][N], attacco2[N][N];   
    int scelta;
    bool esci=false;
    
    while (!esci) 
    {
        system("clear");
        cout<<setw(padding)<<" ";
        cout<<color(MAGENTA)<<"███╗   ███╗███████╗███╗   ██╗██╗   ██╗"<<endl;
        cout<<setw(padding)<<" ";
        cout<<"████╗ ████║██╔════╝████╗  ██║██║   ██║"<<endl;
        cout<<setw(padding)<<" ";
        cout<<"██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║"<<endl;
        cout<<setw(padding)<<" ";
        cout<<"██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║"<<endl;
        cout<<setw(padding)<<" ";
        cout<<"██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝"<<endl;
        cout<<setw(padding)<<" ";
        cout<<"╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝ "<<color(DEFAULT)<<endl<<endl<<endl;;
        cout << setw(padding) <<" ";
        cout<<"Scegli la modalita': "<<endl;
        cout<<setw(padding)<<" ";
        cout<<"1. 2 giocatori"<<endl;
        cout << setw(padding)<<" ";
        cout<<"2. CPU"<<endl;
        cout << setw(padding) << " ";
        cout<<"3. Esci"<<endl;
        cout << setw(padding) << " ";
        cout<<"Inserisci il numero della tua scelta: ";
        cin>>scelta;
        
        switch (scelta)
        {
            case 1:
                difficile(difesa1, attacco1, difesa2, attacco2, N);
                break;
            case 2:
                cpu(difesa1, attacco1, difesa2, attacco2, N);
                break;
            case 3:
                cout<<setw(padding)<<" ";
                cout<<"Arrivederci!"<<endl;
                esci=true;
                break;
            default:
                cout<<setw(padding)<<" ";
                cout<<"Scelta non valida, riprova."<<endl;
                break;
        }
    }
}

void inizMappa(char mappa[][N], int N)
{
    for(int i=0; i < N; i++)
    {
        for(int j=0; j < N; j++)
            mappa[i][j]='.';
    }  
}

//stampa
void stampa(char mappa[][N], int N)
{
    system("clear");
    cout<<setw(padding)<<" ";
    cout<<"       Mappa       "<<endl<<endl;
    cout<<setw(padding)<<" ";
    cout<<"  0 1 2 3 4 5 6 7 8 9"<<endl;
    for(int i=0; i < N; i++)
    {
        cout<<setw(padding)<<" ";
        cout<<i<<" ";
        for(int j=0; j < N; j++)
           {
                if(mappa[i][j] == '*') 
                    cout<<color(GREEN)<<mappa[i][j]<<color(DEFAULT)<<" ";
                else
                    cout<<mappa[i][j]<<" "; 
           }
        cout<<endl;
    }
    cout<<endl<<endl;
}

void stampa2(char mappa1[][N], char mappa2[][N], int giocatore)
{
    cout<<"\nLEGENDA:"<<endl<<endl;
    cout<<"Nave: "<<color(GREEN)<<"*"<<color(DEFAULT)<<endl;
    cout<<"Colpito: "<<color(RED)<<"X"<<color(DEFAULT)<<endl;
    cout<<"Mancato: "<<color(BLUE)<<"O"<<color(DEFAULT)<<endl<<endl;
    cout<<"Navi avversario: "<<giocatori[giocatore]<<endl;
    if(giocatori[giocatore-1] <= 4)
        cout<<"Le tue navi: "<<color(RED)<<giocatori[giocatore-1]<<color(DEFAULT)<<endl;
    else
        cout<<"Le tue navi: "<<giocatori[giocatore-1]<<endl;
    cout<<setw(padding)<<" ";
    cout<<"       DIFESA       "<<setw(10)<<" "<<"         ATTACCO       "<<endl<<endl;
    cout<<setw(padding)<< " ";
    cout<<"  0 1 2 3 4 5 6 7 8 9"<<setw(11)<<" "<<"  0 1 2 3 4 5 6 7 8 9"<<endl;
    for (int i=0; i < N; i++)
    {
        cout<<setw(padding)<<" ";
        cout<<i<<" ";
        for (int j = 0; j < N; j++)
        {
            if (mappa1[i][j] == '*' || mappa1[i][j] == 'X' || mappa1[i][j] == 'O')
            {
                if (mappa1[i][j] == 'X')
                    cout<<color(RED)<<mappa1[i][j]<<color(DEFAULT)<<" ";
                else if (mappa1[i][j] == 'O')
                    cout<<color(BLUE)<<mappa1[i][j]<<color(DEFAULT)<<" ";
                else
                    cout<<color(GREEN)<<mappa1[i][j]<<color(DEFAULT)<<" ";
            }
            else
                cout<<mappa1[i][j]<<" ";
        }
        cout<<setw(10)<<" ";
        cout<<i<<" ";
        for (int j=0; j < N; j++)
        {
            if (mappa2[i][j] == 'X' || mappa2[i][j] == 'O')
            {
                if (mappa2[i][j] == 'X')
                    cout<<color(RED)<<mappa2[i][j]<<color(DEFAULT)<<" ";
                else
                    cout<<color(BLUE)<<mappa2[i][j]<<color(DEFAULT)<<" ";
            }
            else
                cout<<mappa2[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl<<endl;
}

void piazzaNav(char mappa[][N], int N)
{
    int x, y, direzione,nav;
    int navi[10]={4, 3, 3, 2, 2, 2, 1, 1, 1};
    for(int i=0; i < N; i++)
    {
        stampa(mappa, N);
        nav=navi[i];
        do
        {
            cout<<endl<<endl;
            cout<<setw(padding)<<" ";
            cout<<"Inserisci la posizione della nave da "<<nav<<" (x y (da 0 a 9), orizzontale (0), verticale(1)): ";
            cin>>x>>y>>direzione;
            if(x>9 || x <0 || y>9 || y<0 || direzione == 0 && direzione == 1 )
            {
                cout<<setw(padding)<<" ";
                cout<<"Le informazioni non sono corrette....... Prego inserire di nuovo i dati corretamente......";
            }
        }while(x<0 || x >9 || y<0 || y>9 || direzione !=0 && direzione != 1 );
        while (validaPos (mappa,x, y, direzione, nav)) 
        {
            do
            {
                cout<<endl<<endl;
                cout<<setw(padding)<<" ";
                cout <<"Posizione Invalida! La nave non entrera' nella mappa o si scontrera' con un'altra nave.\n";
                cout<<setw(padding)<<" ";
                cout<<"Inserisci la posizione della nave da "<<nav<<" (x y (da 0 a 9), orizzontale (0), verticale(1)): ";
                cin>>x>>y>>direzione;
                if(x>9 || x <0 || y>9 || y<0 || direzione == 0 && direzione == 1 )
                {
                    cout<<setw(padding)<<" ";
                    cout<<"Le inforazioni non sono corrette....... Prego inserire di nuovo i dati corretamente......";
                }
            }while(x<0 || x >9 || y<0 || y>9 || direzione != 0 && direzione != 1 );
        }
        for (int i=0; i < nav; i++) 
        {
            if (direzione == 0) 
                mappa[x][y+i]='*'; // orizzontale

            else 
                mappa[x+i][y]='*'; // verticale
        }
    }

}

void casualNav(char mappa[][N], int N)
{
    srand(time(NULL));
    int x, y, direzione,nav;
    int navi[10]={4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    for(int i=0; i < N; i++)
    {
        nav=navi[i];
            do
            {
                x=rand()%N;
                y=rand()%N;
                direzione=rand()%2;

            } while(validaPos(mappa,x, y, direzione, nav));

        for (int i=0; i < nav; i++) 
        {
            if (direzione == 0) 
                mappa[x][y+i]='*'; // orizzontale
            else 
                mappa[x+i][y]='*'; // verticale
        }
    }
}

bool validaPos(char mappa[][N],int x, int y, int direzione, int nav)
{
    // Verifica che la nave non esca fuori dalla mappa
    if (direzione == 0) 
    { 
        if (y + nav > N) //Orizzontale
            return true;
    } 
    else
    {  
        if (x + nav > N) // Verticale
            return true;
    }

    // Verifica che la nave non si sovrapponga ad altre navi
    for (int i=0; i < nav; i++) 
    {
        int r, c;
        if (direzione == 0) // Orizzontale
        {
            r=x;
            c=y + i;
        } 
        else  // Verticale
        {
            r=x + i;
            c=y;
        }
        if (mappa[r][c] == '*') 
            return true;
    }

    // Verifica che la nave non sia attaccata ad altre navi
    for (int i = -1; i <= nav; i++)
    {
        for (int j = -1; j <= 1; j++) 
        {
            int r, c;
            if (direzione == 0) 
            {  // Orizzontale
                r=x + j;
                c=y + i;
            } 
            else 
            {  // Verticale
                r=x + i;
                c=y + j;
            }

        if (r >= 0 && r < N && c >= 0 && c < N && mappa[r][c] == '*') 
            return true;
        }
    }

    return false;
}

void checkNave(char mappa[][N], int x, int y)
{

    int y1=0, y2=0;
    int x1=0, x2=0;
    int barca=0;
    int x0;
    if (mappa[x - 1][y] == '*' || mappa[x + 1][y] == '*' || mappa[x - 1][y] == 'X' || mappa[x + 1][y] == 'X')
    {
        x0=0;
        while (mappa[x - barca][y] == '*' || mappa[x - barca][y] == 'X')
        {
            contlAff[0]=x-barca;
            contlAff[1]=y;
            barca++;
        }
        barca=0;
        x0=0;
        while (mappa[x + barca][y] == '*' || mappa[x + barca][y] == 'X')
        {
            contlAff[2]=x+barca;
            contlAff[3]=y;
            barca++;
        }
    }

    else if (mappa[x][y - 1] == '*' || mappa[x][y + 1] == '*' || mappa[x - 1][y] == 'X' || mappa[x + 1][y] == 'X')
    {
        x0=0;
        while (mappa[x][y - barca] == '*' || mappa[x][y - barca] == 'X')
        {
            contlAff[0]=x;
            contlAff[1]=y-barca;
            barca++;
        }
        barca=0;
        x0=0;
        while (mappa[x][y + barca] == '*' || mappa[x][y + barca] == 'X')
        {
            contlAff[2]=x;
            contlAff[3]=y+barca;
            barca++;
        }
    }
}

string affondato(char mappa[][N], int giocatore) //int giocatore=0 / 1
{
    bool naveAffondata = true;
    if (contlAff[0] == contlAff[2] && contlAff[1] == contlAff[3]) // nave da 1
        naveAffondata = mappa[contlAff[0]][contlAff[1]] == 'X' ? false : true;
    else 
    { // nave con più di 1 cella
        for (int i = contlAff[0]; i <= contlAff[2]; i++) {
            for (int j = contlAff[1]; j <= contlAff[3]; j++) 
            {
                if (mappa[i][j] == 'X') 
                    naveAffondata = true;
                if (mappa[i][j] == '*') 
                {
                    naveAffondata = false;
                    break;
                }
            }
            if (!naveAffondata) 
                break;
        }
    }
    if (naveAffondata) 
    {
        giocatori[giocatore] -= 1;
        cout<<setw(padding)<<" ";
        return "affondata!\n";
    }
    cout<<setw(padding)<<" ";
    return "colpita!\n";
}

void attacco(char mappa1[][N],char mappa2[][N],int x, int y, int giocatore) 
{

    if(mappa1[x][y] == '*') //mappa avversario
    {
        mappa2[x][y]='X';
        mappa1[x][y]='X';
        checkNave(mappa1, x, y);
        cout<<affondato(mappa1, giocatore);
    } 
    else
        {
            cout<<"\n";
            cout<<setw(padding)<<" ";
            cout<<"Mancato."<<endl;
            mappa2[x][y]='O';
            mappa1[x][y]='O';
        }
}

bool controlloAtt(char mappa[][N], int x, int y)
{
    if(mappa[x][y] == 'X')
    {
        cout<<setw(padding)<<" ";
        cout<<color(RED)<<" Hai gia colpito in questo punto"<<color(DEFAULT)<<endl;
        return true;
    }
    else(mappa[x][y] == 'O');
    {
        cout<<setw(padding)<<" ";
        cout<<color(RED)<<" Hai gia colpito in questo punto"<<color(DEFAULT)<<endl;
        return true;
    }
    return false;
}

//cpu
void cpu(char difesa1[N][N], char attacco1[N][N], char difesa2[N][N], char attacco2[N][N], int N)
{
    giocatori[0]=10; //giocatore 1
    giocatori[1]=10; //giocatore 2
    srand(time(NULL));
    inizMappa(difesa1, N);
    inizMappa(attacco1, N);
    inizMappa(difesa2, N);
    inizMappa(attacco2, N);
    casualNav(difesa2, N);
    system("clear");  
    int scelta;
    bool esci=false;
    while (!esci) 
    {

        cout << setw(padding) << " ";
        cout << "Piazzamento navi:" << endl;
        cout << setw(padding) << " ";
        cout << "1. manuale" << endl;
        cout << setw(padding) << " ";
        cout << "2. casuale" << endl;
        cout << setw(padding) << " ";
        cout << "Inserisci il numero della tua scelta: ";
        cin>>scelta;
        
        switch (scelta)
        {
            case 1:
                piazzaNav(difesa1, N);
                esci=true;
                break;
            case 2:
                casualNav(difesa1, N);
                esci=true;
                break;
            default:
                cout<<setw(padding)<<" ";
                cout<<"Scelta non valida, riprova."<<endl;
                break;
        }
    
    }

    int x, y;
    bool turno=true;
    do
    {
        if (turno) 
        {
            system("clear");
            cout<<setw(padding)<<" ";
            cout<< "E' il tuo turno" <<endl<<endl;
            stampa2(difesa1,attacco1, 1);
            do{
                do
                {
                    x=rand()%10;
                    y=rand()%10;
                    //cout<<"\nInserisci le coordinate per attaccare (x e y (da 0, 9)): ";
                    //cin>>x>>y;
                    //if(x > 9 || x < 0 || y > 9 || y < 0)
                    //   cout<<"\nLe coordinate non sono corrette....... Prego inserire di nuovo i dati corretamente......";
                }while(x < 0 || x > 9 || y < 0 || y > 9); // controllo input
            }while(controlloAtt(attacco1, x, y));
            attacco(difesa2,attacco1,x,y, 1);
            sleep(1);
            turno=false;
        } 
        else 
        {
            system("clear");
            cout<<"Turno del computer"<<endl<<endl;
            do
            {
                    x=rand()%N;
                    y=rand()%N;

            }while(controlloAtt(attacco2, x, y));
            attacco(difesa1,attacco2,x,y, 0);
            turno=true;
        }  
    } while (giocatori[0] > 0 && giocatori[1] > 0); // Continua il ciclo finché entrambi i giocatori hanno ancora navi
    system("clear");
    if (giocatori[0] > 0) 
    {
        cout<<setw(padding)<<" ";
        cout<<color(YELLOW)<<"██╗  ██╗ █████╗ ██╗    ██╗   ██╗██╗███╗   ██╗████████╗ ██████╗ ██╗"<<endl;
        cout<<setw(padding)<<" ";  
        cout<<"██║  ██║██╔══██╗██║    ██║   ██║██║████╗  ██║╚══██╔══╝██╔═══██╗██║"<<endl;
        cout<<setw(padding)<<" ";  
        cout<<"███████║███████║██║    ██║   ██║██║██╔██╗ ██║   ██║   ██║   ██║██║"<<endl;
        cout<<setw(padding)<<" ";  
        cout<<"██╔══██║██╔══██║██║    ╚██╗ ██╔╝██║██║╚██╗██║   ██║   ██║   ██║╚═╝"<<endl;
        cout<<setw(padding)<<" ";  
        cout<<"██║  ██║██║  ██║██║     ╚████╔╝ ██║██║ ╚████║   ██║   ╚██████╔╝██╗"<<endl;
        cout<<setw(padding)<<" ";  
        cout<<"╚═╝  ╚═╝╚═╝  ╚═╝╚═╝      ╚═══╝  ╚═╝╚═╝  ╚═══╝   ╚═╝    ╚═════╝ ╚═╝"<<color(DEFAULT)<<endl<<endl<<endl;
    }                                        
    else  if (giocatori[1] > 0)
    {
        cout<<setw(padding)<< " ";
        cout<<color(RED)<<"██╗  ██╗ █████╗ ██╗    ██████╗ ███████╗██████╗ ███████╗ ██████╗ ██╗"<<endl;
        cout<<setw(padding)<< " ";
        cout<<"██║  ██║██╔══██╗██║    ██╔══██╗██╔════╝██╔══██╗██╔════╝██╔═══██╗██║"<<endl;
        cout<<setw(padding)<< " ";
        cout<<"███████║███████║██║    ██████╔╝█████╗  ██████╔╝███████╗██║   ██║██║"<<endl;
        cout<<setw(padding)<< " ";
        cout<<"██╔══██║██╔══██║██║    ██╔═══╝ ██╔══╝  ██╔══██╗╚════██║██║   ██║╚═╝"<<endl;
        cout<<setw(padding)<< " ";
        cout<<"██║  ██║██║  ██║██║    ██║     ███████╗██║  ██║███████║╚██████╔╝██╗"<<endl;
        cout<<setw(padding)<< " ";
        cout<<"╚═╝  ╚═╝╚═╝  ╚═╝╚═╝    ╚═╝     ╚══════╝╚═╝  ╚═╝╚══════╝ ╚═════╝ ╚═╝"<<color(DEFAULT)<<endl<<endl<<endl;
    }
    cout<<setw(padding)<<" ";                                        
    cout<<"Premi INVIO per continuare...";
    cin.ignore();
    cin.get();     
}

// 2 giocatori
void difficile(char difesa1[][N], char attacco1[][N], char difesa2[][N], char attacco2[][N], int N)
{
    system("clear");
    giocatori[0]=10; //giocatore 1
    giocatori[1]=10; //giocatore 2
    int scelta;
    bool esci=false;
    inizMappa(difesa1, N);
    inizMappa(attacco1, N);
    inizMappa(difesa2, N);
    inizMappa(attacco2, N);
    cout << setw(padding) << " ";
    cout<<"Giocatore 1"<<endl<<endl;
    while (!esci) 
    {
        cout << setw(padding) << " ";
        cout<<"Piazzamento navi:"<<endl;
        cout << setw(padding) << " ";
        cout<<"1. manuale"<<endl;
        cout << setw(padding) << " ";
        cout<<"2. casuale"<<endl;
        cout << setw(padding) << " ";
        cout<<"Inserisci il numero della tua scelta: ";
        cin>>scelta;
        switch (scelta)
        {
            case 1:
                piazzaNav(difesa1,N);
                esci=true;
                break;
            case 2:
                casualNav(difesa1,N);
                esci=true;
                break;
            default:
                cout<<setw(padding)<<" ";
                cout<<"Scelta non valida, riprova."<<endl;
                break;
        }
    }
    scelta=0;
    esci=false;
    system("clear");
    cout << setw(padding) << " ";
    cout<<"Giocatore 2"<<endl<<endl;
    while (!esci) 
    {
        cout << setw(padding) << " ";
        cout<<"Piazzamento navi:"<<endl;
        cout << setw(padding) << " ";
        cout<<"1. manuale"<<endl;<<color(DEFAULT)
        cout << setw(padding) << " ";
        cout<<"2. casuale"<<endl;
        cout << setw(padding) << " ";
        cout<<"Inserisci il numero della tua scelta: ";
        cin>>scelta;
        
        switch (scelta)
        {
            case 1:
                piazzaNav(difesa2,N);
                esci=true;
                break;
            case 2:
                casualNav(difesa2,N);
                esci=true;
                break;
            default:
                cout<<setw(padding)<<" ";
                cout<<"Scelta non valida, riprova."<<endl;
                break;
        }
    }
    int x, y;
    bool turno=true;
    do
    {
        if (turno) 
        {
            system("clear");
            cout<<setw(padding)<<" ";
            cout<< "Turno del giocatore 1" <<endl<<endl;
            stampa2(difesa1,attacco1, 1);
            do
            {
                cout<<setw(padding)<<" ";
                cout<<"Inserisci le coordinate per attaccare (x e y (da 0, 9)): ";
                cin>>x>>y;
                if(x>9 || x <0 || y>9 || y<0)
                {
                    cout<<setw(padding)<<" ";
                    cout<<"Le coordinate non sono corrette....... Prego inserire di nuovo i dati corretamente......";
                }
            }while(x<0 || x >9 || y<0 || y>9); // controllo input
            attacco(difesa2,attacco1,x,y, 1);
            sleep(1);
            turno = false;
        } 
        else 
        {
            system("clear");
            cout<<setw(padding)<<" ";
            cout<<"Turno del giocatore 2"<<endl<<endl;
            stampa2(difesa2,attacco2, 0);
            do
            {
                cout<<setw(padding)<<" ";
                cout<<"Inserisci le coordinate per attaccare (x e y (da 0, 9)): ";
                cin>>x>>y;
                if(x>9 || x <0 || y>9 || y<0)
                {
                    cout<<setw(padding)<<" ";
                    cout<<"Le coordinate non sono corrette....... Prego inserire di nuovo i dati corretamente......";
                }
            }while(x<0 || x >9 || y<0 || y>9); // controllo input
            attacco(difesa1,attacco2,x,y, 0);
            sleep(1);
            turno=true;
        }  
    } while (giocatori[0] > 0 && giocatori[1] > 0); // Continua il ciclo finché entrambi i giocatori hanno ancora navi
    system("clear");
    if (giocatori[0] > 0) 
    {
        cout<<setw(padding)<<" ";
        cout<<"Il giocatore 1 ha vinto!"<<endl<<endl;
    }
    else  if (giocatori[1] > 0) 
    {
        cout<<setw(padding)<<" ";
        cout<<"Il giocatore 2 ha vinto!"<<endl<<endl;
    }
    cout<<setw(padding)<<" ";    
    cout<<"\nPremi INVIO per continuare...";
    cin.ignore();
    cin.get();
}

void regole()
{
    system("clear");
    cout<<setw(padding)<<" ";
    cout<<color(DARK_GRAY)<<"██████╗ ███████╗ ██████╗  ██████╗ ██╗     ███████╗"<<endl;
    cout<<setw(padding)<<" ";
    cout<<"██╔══██╗██╔════╝██╔════╝ ██╔═══██╗██║     ██╔════╝"<<endl;
    cout<<setw(padding)<<" ";     
    cout<<"██████╔╝█████╗  ██║  ███╗██║   ██║██║     █████╗  "<<endl;
    cout<<setw(padding)<<" ";    
    cout<<"██╔══██╗██╔══╝  ██║   ██║██║   ██║██║     ██╔══╝  "<<endl;
    cout<<setw(padding)<<" ";   
    cout<<"██║  ██║███████╗╚██████╔╝╚██████╔╝███████╗███████╗"<<endl;
    cout<<setw(padding)<<" ";
    cout<<"╚═╝  ╚═╝╚══════╝ ╚═════╝  ╚═════╝ ╚══════╝╚══════╝"<<color(DEFAULT)<<endl<<endl<<endl;
    cout << setw(padding) << " ";
    cout<<"Al vostro turno, chiamate una lettera e un numero che identifica una riga e una"<<endl;
    cout << setw(padding) << " ";
    cout<<"colonna sulla griglia di destinazione. Il tuo avversario controlla lo spazio sulla sua"<<endl;
    cout << setw(padding) << " ";
    cout<<"griglia dell’oceano e risponde “manca” se non c’è la nave o “colpisce” se hai trovato"<<endl;
    cout << setw(padding) << " ";
    cout<<"uno spazio che conteneva una nave."<<endl<<endl;
    cout << setw(padding) << " ";
    cout<<"Segna ciascuna dei tuoi colpi sulla tua griglia superiore del bersaglio utilizzando i"<<endl;
    cout << setw(padding) << " ";
    cout<<"segnalini bianchi per le tue mancate e le punte rosse per i colpi andati a segno. In"<<endl;
    cout << setw(padding) << " ";
    cout<<"questo modo potrai tenere traccia dei tuoi colpi!"<<endl<<endl;
    cout << setw(padding) << " ";
    cout<<"Quando una delle tue navi viene colpita, si mette una punta rossa nel buco su quella"<<endl;
    cout << setw(padding) << " ";
    cout<<"nave sulla griglia oceano nella posizione del colpo. Le navi sono di diverse"<<endl;
    cout << setw(padding) << " ";
    cout<<"dimensioni e hanno diversi fori."<<endl<<endl;                                                                                             
    cout << setw(padding) << " ";
    cout<<"Premi INVIO per continuare...";
    cin.ignore();
    cin.get();
}

void logo()
{
    system("clear");
    cout<<setw(padding)<<" ";
    cout<<color(BLUE)<<"██████╗  █████╗ ████████╗████████╗ █████╗  ██████╗ ██╗     ██╗ █████╗ "<<endl;
    cout<<setw(padding)<<" ";
    cout<<color(LIGHT_BLUE)<<"██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██╔══██╗██╔════╝ ██║     ██║██╔══██╗"<<endl;
    cout<<setw(padding)<<" ";
    cout<<color(BLUE)<<"██████╔╝███████║   ██║      ██║   ███████║██║  ███╗██║     ██║███████║"<<endl;
    cout<<setw(padding)<<" ";
    cout<<color(LIGHT_BLUE)<<"██╔══██╗██╔══██║   ██║      ██║   ██╔══██║██║   ██║██║     ██║██╔══██║"<<endl;
    cout<<setw(padding)<<" ";
    cout<<color(BLUE)<<"██████╔╝██║  ██║   ██║      ██║   ██║  ██║╚██████╔╝███████╗██║██║  ██║"<<endl;
    cout<<setw(padding)<<" ";
    cout<<color(LIGHT_BLUE)<<"╚═════╝ ╚═╝  ╚═╝   ╚═╝      ╚═╝   ╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝╚═╝  ╚═╝"<<endl;
    cout<<setw(padding)<<" ";
    cout<<color(BLUE)<<"         ███╗   ██╗ █████╗ ██╗   ██╗ █████╗ ██╗     ███████╗          "<<endl;
    cout<<setw(padding)<<" ";
    cout<<color(LIGHT_BLUE)<<"         ████╗  ██║██╔══██╗██║   ██║██╔══██╗██║     ██╔════╝          "<<endl;
    cout<<setw(padding)<<" ";
    cout<<color(BLUE)<<"         ██╔██╗ ██║███████║██║   ██║███████║██║     █████╗            "<<endl;
    cout<<setw(padding)<<" ";
    cout<<color(LIGHT_BLUE)<<"         ██║╚██╗██║██╔══██║╚██╗ ██╔╝██╔══██║██║     ██╔══╝            "<<endl;
    cout<<setw(padding)<<" ";
    cout<<color(BLUE)<<"         ██║ ╚████║██║  ██║ ╚████╔╝ ██║  ██║███████╗███████╗          "<<endl;
    cout<<setw(padding)<<" ";
    cout<<color(LIGHT_BLUE)<<"         ╚═╝  ╚═══╝╚═╝  ╚═╝  ╚═══╝  ╚═╝  ╚═╝╚══════╝╚══════╝          "<<color(DEFAULT)<<endl<<endl<<endl;
    cout << setw(padding) << " ";
    cout<<"Premi INVIO per continuare...";
    cin.get();
}

//Amodeo
void semplice()
{
    system("clear");
    char M[][N]={
        {'*','.','.','*','*','*','*','.','*','.'},
        {'.','.','.','.','.','.','.','.','.','.'},
        {'.','.','.','*','.','.','.','.','.','*'},
        {'.','.','.','.','.','.','.','.','.','*'},
        {'.','.','.','.','*','.','.','.','.','.'},
        {'.','.','.','.','*','.','.','*','.','*'},
        {'.','*','.','.','*','.','.','*','.','*'},
        {'.','.','.','.','.','.','.','*','.','.'},
        {'.','.','.','.','.','.','.','.','.','*'},
        {'.','.','.','*','*','.','.','.','.','*'},
    };
    //stampa(M,N);       
    cerca(M, N);
    cout<<endl<<endl;
    cout<<setw(padding)<<" ";
    cout<<"Premi INVIO per continuare...";
    cin.ignore();
    cin.get();
}

void cerca(char M[][N], int N)
{
    int r, c, r2, c2;
    int numero=0;
    for(int i=0; i < N; i++)
    {
        numero=0;
        for(int j=0; j < N; j++)
        {
            
            if(M[i][j]=='*')
                numero++;
            if(numero == 1)
            {
                r=i;
                c=j;
            }
            if(numero == 4)
            {
                r2=i;
                c2=j;
                i=N;
                j=N;
            }
            if(M[i][j] == '.')
                numero=0;

        }
    }
       
    if(numero == 4)
    {
        cout<<setw(padding)<<" ";
        cout<<"La nave da 4 caselle inizia dalla cordinata : ["<<r<<"],["<<c<<"].... e finisce a : ["<<r2<<"],["<<c2<<"]"<<endl;
    }
    else
    {
        cout<<setw(padding)<<" ";
        cout<<"Non e' stata trovata nessuna nave lunga 4 caselle in orizzontale"<<endl;
    } 
      
    for(int i=0; i < N; i++)
    {
        numero=0;
        for(int j=0; j < N; j++)
        {
            if(M[j][i]=='*')
                numero++;
            
            if(numero == 1)
            {
                r=j;
                c=i;
            }
            if(numero == 4)
            {
                r2=j;
                c2=i;
                i=N;
                j=N;
            }
            if(M[j][i] == '.')
                numero=0;
        }
    }
        
    if(numero == 4)
    {
        cout<<setw(padding)<<" ";
        cout<<"La nave da 4 caselle inizia dalla cordinata : ["<<r<<"],["<<c<<"].... e finisce a : ["<<r2<<"],["<<c2<<"]"<<endl;
    }
    else
    {
        cout<<setw(padding)<<" ";
        cout<<"Non e' stata trovata nessuna nave lunga 4 caselle in verticale"<<endl;
    }
}
/*
void logo()
{
    system("clear");
    cout<<R"(
                                                           *_______          ____     _______     * _______          ____         ______       _______           ____          ____                                      
                                                           |  _____\        |  ___\   | ______\     | ______\       |  ___\      /  ____\  *  |   ____\         | ___\     *  |  ___\
                                                            | |  _  \   *   / |   |   \ |_   __|    \ |_   __|   *  / |   |      | / ___ \     \ |    |         \ |_ _|       / |   |
                                                          * | | |_) |      / / ^  /    |  | |     *  |  | |        / / ^  /      | | | |_|     |  |  |      *    | | |       / / ^  /
                                                            | |  _ <      / / /_\ \  * |  | |        |  | |       / / /_\ \  *   | | |  __     |  |  |           | | |      / / /_\ \
                                                            | | |_) |    | /  ___  \   |  | |   *    |  | |      | /  ___  \     | | \_\ |    |   |  |___/|      | | |     | /  ___  \
                                                            \_|____/  *  \|__| \|__|   \ |___|       \ |___|  *  \|__| \|__|     \ \_____/   * \ |________|    * \|___|    \|__| \|__|
                                                            
                                                                            _____  _____          ____       *  ____   _____           ____       _______      *  _________
                                                                *          |   __\ |  __\    *   |  ___\       |   _\ |    _\     *   |  ___\    |   ____\       |   ______\
                                                                *     *     | |   \| |   |       / |   |        \ |  | |  |  |        / |   |   * \ |    |        \ |  _____|
                                                                *           |  | ^ \  | |       / / ^  /    *    \ \ \ |  / /        / / ^  /     |  |  |       * |  | |___
                                                                *           |  | |\ \ | |      / / /_\ \          \ \ \| / /  *     / / /_\ \     |  |  |  *      |  |  ___|
                                                                    *      |   | | \ \| |  *  | /  ___  \          | | \/ |        | /  ___  \   |   |  |___/|   |   | |___\
                                                                      *     \ |___| \____|    \|__| \|__|      *   \|______|       \|__| \|__| *  \ |________|    \ |_______|
                                                                      
                                                                      
                                                                      
                                                                      
                                                                     
    )";
    cout << setw(padding) << " ";
    cout<<"Premi INVIO per continuare...";
    cin.get();
}
*/
