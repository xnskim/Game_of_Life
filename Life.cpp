#include <iostream>
#include <cstdlib>
#include <time.h>
#include <curses.h>
#include <stddef.h>
#include <random>
#include <thread>
#include <chrono>

using namespace std;

//function

void zone_prepare(char tab[50][50])
{
    for(int i=0; i<50; i++)
    {
        for(int j=0; j<50; j++)
        {
            tab[i][j] = ' ';
        }
    }
}

void zone_prepare_int(int tab2[50][50])
{
    for(int i=0; i<50; i++)
    {
        for(int j=0; j<50; j++)
        {
            tab2[i][j] = 0;
        }
    }
}

void draw_tab(char tab[50][50])
{
    for(int i=0; i<50; i++)
    {
        for(int j=0; j<50; j++)
        {
            cout << tab[i][j] << " ";
        }
        cout << endl;
    }
}

void clean()
{
    system("clear");
}

void choice_point(char tab[50][50], int x, int y, int n, int m)
{
    // x - wsp. pionowa punktu
    // y - wsp. pozioma punktu
    // n - ilość punktów startowych
    // m - ilość kroków symulacji

    cout << "Ilosc punktow, z ktorych bedzie zbudowana struktura: ";
    cin >> n;

    for (int i=0; i<n; i++)
    {
        cout << endl << "Wspolrzedne " << i+1 << " punktu:\n- wspolrzedna pionowa: ";
        cin >> x;
        cout << "- wspolrzedna pozioma: ";
        cin >> y;
        tab[x][y] = 'o';
        clean();
        draw_tab(tab);
    }
    cout << endl << "Ilosc krokow symulacji: ";
    cin >> m;
}

void sleep(int milisec)
{
    //sleep(1000) -> 1 second delay
    clock_t end = clock() + milisec * CLOCKS_PER_SEC / 1000.0;
    while(clock() < end) continue;
}

int counter_(char tab[50][50], int i, int j, int count_)
{
    count_ = 0;
    for(int p=0; p<3; p++)
    {
        for(int q=0; q<3; q++)
        {
            if(tab[i][j] == ' ' and tab[i-1+p][j-1+q] == 'o')
            {
                count_++;
            }
        }
    }
    return count_;
}

int counter_o(char tab[50][50], int i, int j, int count_o)
{
    count_o = -1;
    for(int p=0; p<3; p++)
    {
        for(int q=0; q<3; q++)
        {
            if(tab[i][j] == 'o' and tab[i-1+p][j-1+q] == 'o')
            {
                count_o++;
            }
        }
    }
    return count_o;
}

void step(char tab[50][50], int tab2[50][50], int count_, int count_o)
{
    for(int i=1; i<49; i++)
    {
        for(int j=1; j<49; j++)
        {
            if(tab[i][j] == 'o')
            {
                tab2[i][j] = counter_o(tab, i, j, count_o);
            }
            else if(tab[i][j] == ' ')
            {
                tab2[i][j] = counter_(tab, i, j, count_);
            }
        }
    }  
} 

void requ(char tab[50][50], int tab2[50][50])
{
    for(int i=1; i<49; i++)
    {
        for(int j=1; j<49; j++)
        {
            if(tab[i][j] == ' ' and (tab2[i][j] == 3 or tab2[i][j] == 6))
            {
                tab[i][j] = 'o';
            }
            else if(tab[i][j] == 'o' and (tab2[i][j] == 2 or tab2[i][j] == 3))
            {
                tab[i][j] = 'o';
            }
            else if(tab[i][j] == 'o' and (tab2[i][j] != 2 or tab2[i][j] != 3))
            {
                tab[i][j] = ' ';
            }
        }
    }
}

int loop_break(char tab[50][50], int add_o)
{
    add_o = 0;
    for(int i=1; i<49; i++)
    {
        for(int j=1; j<49; j++)
        {
            if(tab[i][j] == 'o')
            {
                add_o++;
            }
        }
    }
    return add_o;
}

int tab_compare(char tab[50][50], char tab_b[50][50], int tab_add)
{
    tab_add = 0;
    for(int i=0; i<50; i++)
    {
        for(int j=0; j<50; j++)
        {
            if(tab[i][j] == 'o' and tab_b[i][j] == 'o')
            {
                tab_add++;
            }
        }
    }
    return tab_add;
}

void tab_equal(char tab[50][50], char tab_b[50][50])
{
    for(int i=0; i<50; i++)
        {
            for(int j=0; j<50; j++)
            {
                tab_b[i][j] = tab[i][j];
            }
        }
} 

//endfunction

int main()
{
    char tab[50][50], tab_b[50][50];
    int tab2[50][50];
    int x, y, n, m, count_, count_o, sum, add_o, tab_add, t=100;

    clean();
    zone_prepare(tab);
    zone_prepare(tab_b);
    zone_prepare_int(tab2);
    choice_point(tab, x, y, n, m);
    for(int i=0; i<t; i++)
    {
        if(loop_break(tab, add_o) == 0 and i > 0)
        {
            draw_tab(tab);
            cout << "Area is empty. Life ended in " << i << " steps.\n" << endl;
            break;
        }

        if(tab_compare(tab, tab_b, tab_add) == loop_break(tab, add_o))
        {
            draw_tab(tab);
            cout << "The simulation stuck. End in " << i+1 << " step.\n" << endl;
            break;
        }
        
        cout << "step " << i+1 << endl;
        step(tab, tab2, count_, count_o);
        requ(tab, tab2);
        
        draw_tab(tab);
        sleep(250);
        clean(); 
    }
    
    return 0;
}