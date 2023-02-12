 #include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <windows.h>
using namespace std;
const int N=10;//grandezza mappa
int contlAff[4];
//prototipi
void menu1(); //Amodeo
void menu2(); //Canucciari
void difficile(char difesa1[][N], char attacco1[][N], char difesa2[][N], char attacco2[][N], int N); //Modalità gioco 2 giocatori
void cpu(char difesa1[][N], char attacco1[][N], char difesa2[][N], char attacco2[][N], int N); //funzione per giocare contro il computer
bool validaPos(char mappa[][N], int x, int y, int direzione, int nav);//funzione per validare la posizioni delle navi per non piazzarle accanto 
void inizMappa(char mappa[][N], int N); // inizializza le mappa di gioco
void stampa(char mappa[][N], int N); // stampa la mappa
void stampa2(char mappa1[N], char mappa2[][N], int N); // stampa le due mappe
void piazzaNav(char mappa[][N], int N); // funzione per piazzare le navi nella mappa
void casualNav(char mappa[][N], int N); // funzione per piazzare le navi nella mappa in modo casuale
void checkNave(char mappa[][N], int x, int y); // funzione che controll se le nave è stata affondata
bool affondato(char mappa);// funzione per controllare se una nave è affondata
void logo(); // Battaglia Navale
void regole(); // Regole
void color(int x);
//Amodeo
void cerca(char M[][N], int N);
void semplice();

//main
int main()
{
    logo();

    system("pause");
    menu1(); 
    
    return 0;
}

//funzioni

//menu
void menu1()
{
    system("CLS");
    int scelta;
    bool esci=false;
    
    while (!esci) 
    {
        cout<<"Menu:"<<endl;
        cout<<"1. semplice"<<endl;
        cout<<"2. Difficile"<<endl;
        cout<<"3. Esci"<<endl;
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
                cout<<"Arrivederci!"<<endl;
                esci=true;
                break;
            default:
                cout<<"Scelta non valida, riprova."<<endl;
                break;
        }
    }
}

void menu2()
{
    system("CLS");
    char difesa1[N][N], attacco1[N][N],difesa2[N][N], attacco2[N][N];   
    int scelta;
    bool esci=false;
    
    while (!esci) 
    {
        cout<<"Menu:"<<endl;
        cout<<"1. 2 giocatori"<<endl;
        cout<<"2. CPU"<<endl;
        cout<<"3. Esci"<<endl;
        cout<<"Inserisci il numero della tua scelta: ";
        cin>>scelta;
        
        switch (scelta)
        {
            case 1:
                difficile(difesa1, attacco1, difesa2 , attacco2, N);
                break;
            case 2:
                cpu(difesa1, attacco1, difesa2 , attacco2, N);
                break;
            case 3:
                cout<<"Arrivederci!" << endl;
                esci=true;
                break;
            default:
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
    system("cls");
    cout<<"       Mappa       "<<endl<<endl;
    cout<<"0.1.2.3.4.5.6.7.8.9."<<endl;
    for(int i=0; i < N; i++)
    {
        for(int j=0; j < N; j++)
            cout<<mappa[i][j]<<"|";
        cout<<endl;
    }
}

void stampa2(char mappa1[][N],char mappa2[][N], int N)
{
    cout<<"       difesa       "<<setw(10)<<" "<<"       attacco       "<<endl<<endl;
    for (int i=0; i < N; i++) 
    {
        for (int j=0; j < N; j++) 
            cout<<mappa1[i][j]<<"|";
        cout<<setw(10)<<" ";
        for (int j=0; j < N; j++) 
            cout<<mappa2[i][j]<<"|";
        cout<<endl;
    }
}

void piazzaNav(char mappa[][N], int N)
{
    int x, y, direzione,nav;
    int navi[10]={4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    for(int i=0; i < N; i++)
    {
        stampa(mappa, N);
        nav=navi[i];
        do
        {
            cout<<"\nInserisci la posizione della nave da "<<nav<<" (x y (da 0 a 9), orizzontale (0), verticale(1)): ";
            cin>>x>>y>>direzione;
            if(x>9 || x <0 || y>9 || y<0 || direzione == 0 && direzione == 1 )
                cout<<"\nLe inforazioni non sono corrette....... Prego insrire di nuovo i dati corretamente......";
        }while(x<0 || x >9 || y<0 || y>9 || direzione !=0 && direzione != 1 );
        while (validaPos (mappa,x, y, direzione, nav)) 
        {
            do
            {
                cout << "Posizione Invalida! La nave non entrera' nella mappa o si scontrera' con un'altra nave.\n";
                cout<<"\nInserisci la posizione della nave da "<<nav<<" (x y (da 0 a 9), orizzontale (0), verticale(1)): ";
                cin>>x>>y>>direzione;
                if(x>9 || x <0 || y>9 || y<0 || direzione == 0 && direzione == 1 )
                    cout<<"\nLe inforazioni non sono corrette....... Prego inserire di nuovo i dati corretamente......";
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
        if (y + nav > N-1) //Orizzontale
            return true;
    } 
    else
    {  
        if (x + nav > N-1) // Verticale
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

string affondato(char mappa[][N])
{
    // contrlAff = [0]-> xInizio [1]-> yInizio [2]-> xFine [3]-> yFine
    bool naveAffondata=true;
    for (int i=contlAff[0]; i <= contlAff[2]; i++)
    {
        for (int j=contlAff[1]; j <= contlAff[3]; j++)
        {
            if (mappa[i][j] != 'X')
            {
                naveAffondata=false;
                break;
            }
        }
    }
    if(naveAffondata==true)
        return "\naffondata!\n";
    return "\ncolpita!\n";
}

void attacco(char mappa1[][N],char mappa2[][N],int x, int y) 
{

    if(mappa1[x][y] == '*') //mappa avversario
    {
        //cout<<"Colpito!"<<endl;
        mappa2[x][y]='X';
        mappa1[x][y]='X';
        checkNave(mappa1, x, y);
        //contrlAff = [0]-> xInizio [1]-> yInizio [2]-> xFine [3]-> yFine
        /*for(int i=0;i<4;i++)
            cout<<contlAff[i]<<" ";
        */
        cout<<affondato(mappa1);
    } 
    else
        {
            cout<<"Mancato."<<endl;
            mappa2[x][y]='O';
            mappa1[x][y]='O';
        }
}

bool controlloAtt(char mappa[][N], int x, int y)
{
    if(mappa[x][y] == 'X')
    {
        cout<<" Hai gia colpito in questo punto"<<endl;
        return true;
    }
    else if(mappa[x][y] == 'O')
    {
        cout<<" Hai gia colpito in questo punto"<<endl;
        return true;
    }
    return false;
}

//cpu
void cpu(char difesa1[N][N], char attacco1[N][N], char difesa2[N][N], char attacco2[N][N], int N)
{
    //inizializza mappa del computer in modo casuale
    srand(time(0));
    inizMappa(difesa1, N);
    inizMappa(attacco1, N);
    inizMappa(difesa2, N);
    inizMappa(attacco2, N);
    casualNav(difesa2, N);
    system("cls");  
    int scelta;
    bool esci=false;
    while (!esci) 
    {
        cout<<"1. Piazzamento navi:"<<endl;
        cout<<"1. manuale"<<endl;
        cout<<"2. casuale"<<endl;
        cout<<"Inserisci il numero della tua scelta: ";
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
                cout<<"Scelta non valida, riprova."<<endl;
                break;
        }
    
    }

    int nGiocatore1=10, nGiocatore2=10, x, y;
    bool turno=true;
    do
    {
        if (turno) 
        {
            system("cls");
            cout<< "E' il tuo turno" <<endl<<endl;
            stampa2(difesa1,attacco1, N);
            do{
                do
                {
                    cout<<"\nInserisci le coordinate per attaccare (x e y (da 0, 9)): ";
                    cin>>x>>y;
                    if(x>9 || x <0 || y>9 || y<0)
                        cout<<"\nLe coordinate non sono corrette....... Prego inserire di nuovo i dati corretamente......";
                }while(x<0 || x >9 || y<0 || y>9); // controllo input
            }while(controlloAtt(attacco1, x, y));
            attacco(difesa2,attacco1,x,y);
            if(affondato(difesa2))
                nGiocatore2--;
            Sleep(2000);
            turno=false;
        } 
        else 
        {
            system("cls");
            cout<<"Turno del computer"<<endl<<endl;
            do
            {
                    x=rand()%N;
                    y=rand()%N;

            }while(controlloAtt(attacco2, x, y));
            attacco(difesa1,attacco2,x,y);
            turno=true;
        }  
    } while (nGiocatore1 > 0 && nGiocatore2 > 0); // Continua il ciclo finché entrambi i giocatori hanno ancora navi
     if (nGiocatore1 > 0) 
        cout<<"Hai vinto!"<<endl;
    else  
        if (nGiocatore2 > 0)
            cout<<"Il computer ha vinto!"<<endl;
        else 
            cout<<"La partita e' terminata in pareggio."<<endl;        
}

// 2 giocatori
void difficile(char difesa1[][N], char attacco1[][N], char difesa2[][N], char attacco2[][N], int N)
{
    system("cls");  
    int scelta;
    bool esci=false;
    inizMappa(difesa1, N);
    inizMappa(attacco1, N);
    inizMappa(difesa2, N);
    inizMappa(attacco2, N);
    cout<<"Giocatore 1"<<endl;
    while (!esci) 
    {
        cout<<"Piazzamento navi:"<<endl;
        cout<<"1. manuale"<<endl;
        cout<<"2. casuale"<<endl;
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
                cout<<"Scelta non valida, riprova."<<endl;
                break;
        }
    }
    scelta=0;
    esci=false;
    system("cls");
    cout<<"Giocatore 2"<<endl;
    while (!esci) 
    {
        cout<<"Piazzamento navi:"<<endl;
        cout<<"1. manuale"<<endl;
        cout<<"2. casuale"<<endl;
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
                cout<<"Scelta non valida, riprova."<<endl;
                break;
        }
    }
    int nGiocatore1=10, nGiocatore2=10, x, y;
    bool turno=true;
    do
    {
        if (turno) 
        {
            system("cls");
            cout<< "Turno del giocatore 1" <<endl<<endl;
            stampa2(difesa1,attacco1, N);
            do
            {
                cout<<"\nInserisci le coordinate per attaccare (x e y (da 0, 9)): ";
                cin>>x>>y;
                if(x>9 || x <0 || y>9 || y<0)
                    cout<<"\nLe coordinate non sono corrette....... Prego inserire di nuovo i dati corretamente......";
            }while(x<0 || x >9 || y<0 || y>9); // controllo input
            attacco(difesa2,attacco1,x,y);
            system("pause");

            turno = false;
        } 
        else 
        {
            system("cls");
            cout<<"Turno del giocatore 2"<<endl<<endl;
            stampa2(difesa2,attacco2, N);
            do
            {
                cout<<"\nInserisci le coordinate per attaccare (x e y (da 0, 9)): ";
                cin>>x>>y;
                if(x>9 || x <0 || y>9 || y<0)
                    cout<<"\nLe coordinate non sono corrette....... Prego inserire di nuovo i dati corretamente......";
            }while(x<0 || x >9 || y<0 || y>9); // controllo input
            attacco(difesa1,attacco2,x,y);
            system("pause");
            
            turno=true;
        }  
    } while (nGiocatore1 > 0 && nGiocatore2 > 0); // Continua il ciclo finché entrambi i giocatori hanno ancora navi

    if (nGiocatore1 > 0) 
        cout<<"Il giocatore 1 ha vinto!"<<endl;
    else  
        if (nGiocatore2 > 0) 
            cout<<"Il giocatore 2 ha vinto!"<<endl;
        else 
            cout<<"La partita e' terminata in pareggio."<<endl;        
}

//Amodeo
void semplice()
{
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
    stampa(M,N);       
    cerca(M, N);
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
        cout<<"\nLa nave da 4 caselle inizia dalla cordinata : ["<<r<<"],["<<c<<"].... e finisce a : ["<<r2<<"],["<<c2<<"]";
    else
        cout<<"\nNon e' stata trovata nessuna nave lunga 4 caselle in orizzontale\n"; 
      
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
        cout<<"\nLa nave da 4 caselle inizia dalla cordinata : ["<<r<<"],["<<c<<"].... e finisce a : ["<<r2<<"],["<<c2<<"]\n";
    else
        cout<<"\nNon e' stata trovata nessuna nave lunga 4 caselle in verticale\n";
}

void logo()
{
    color (5); cout << R"(
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



    )"<<endl; color(15);
}

void color(int x)
{
	HANDLE HCon;
	HCon= GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute (HCon,x);

}
