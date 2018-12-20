#include <iostream>
#include <string>
#include "dijkstra.h"
#include "maps.h"


int main() {



    dijkstra a ;
    maps* m = new maps() ;
    m->set_double("symbols_tables", "rudder", 5) ;
    m->set_double("symbols_tables", "throthle", -20) ;
    m->set_double("symbols_tables", "zibi", 80) ;
    m->set_double("symbols_tables", "shimon", 45) ;

    cout << a.calc("2+(shimon*throthle-rudder)/(zibi/shimon)", m) << endl;
    cout << a.calc("(0.8-(0.2*0.5)+0.8)/0.5", m) << endl;



    return 0;
}
// (4+2-3+5-(5*20-3)+   (5-7*6+(25*2/3)-8+10-5)







