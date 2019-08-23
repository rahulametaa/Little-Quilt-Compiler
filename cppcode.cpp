#include<iostream>
#include"Quilt.h"
using namespace std;
int main(){
Quilt q0('a');
Quilt q1('b');
Quilt q2=q0.sew(q1);
q2.display();
return 0;
}
