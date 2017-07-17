#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
using namespace std;

#include <vector>

#include "gnuplot_i.hpp" //Gnuplot class handles POSIX-Pipe-communikation with Gnuplot
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)
 #include <conio.h>   //for getch(), needed in wait_for_key()
 #include <windows.h> //for Sleep()
 void sleep(int i) { Sleep(i*1000); }
#endif

#define SLEEP_LGTH 2  // sleep time in seconds
void wait_for_key(); // Programm halts until keypress

void graph(int n, vector<double>& valores, double s){

  cout << "VALOR RESULTANTE DE LA SERIE ES: "+std::to_string(s)+"\n";

  try{
        Gnuplot g1("Taylor");
        std::vector<double> x, y;
        // for(int i=valores.size()-1 ; i>= 0; i--){
        //   cout << "valor dentro"+ std::to_string(valores[i])+"\n";
        // }

        for (int i = 0; i < n; i++) {
            x.push_back((double)valores[i]);             // x[i] = i
            y.push_back((double)valores[i] * (double)valores[i]); // y[i] = i^2
        }

        g1.reset_plot();
        g1.set_grid();
        g1.set_style("points").plot_xy(x,y,"user-defined points 2d");
        wait_for_key();
    }
    catch (GnuplotException ge){
        cout << ge.what() << endl;
    }
}

void wait_for_key (){
  #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)  // every keypress registered, also arrow keys
    cout << endl << "Cualquier tecla para continuar..." << endl;
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    _getch();
  #elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
    cout << endl << "Presiona ENTER para continuar..." << endl;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
  #endif
    return;
}


double factorial(int n){
  double fac = 1;
  for(int i = 2; i <= n; i++){
    fac*=i;
  }
  return fac;
}


double taylor(int n, int x){
  double t, s =0;
  vector<double> MyVector;
  for(int i = 0; i <n ; i++){
    t = pow(x,i)/factorial(i);
    cout << std::to_string(t)+"\n";
    //llenamos el vector de valores de cada iteracion
    MyVector.insert(MyVector.begin(),t); // Inserts the value i at the start of the array 10 times.
    s+=t;
  }

  graph(n, MyVector, s);

  return s;
}


int main(){
  int n,x;
   cout << "dame N?";
   cin >> n;
   cout << "dame X?";
   cin >> x;
   cout << "El valor para N="+std::to_string(n)+"y X="+std::to_string(x)+" es:"+std::to_string(taylor(n, x)) << endl;
   cout << "\n";
  taylor(n, x);
  //taylor(10, 2);
    return 0;
}
