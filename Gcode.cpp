#include<iostream>
#include<string>
#include "Gcode.h"

using namespace std;

Quadruple::Quadruple(string op,int op1,int op2){
    operation=op;
    opd1=op1;
    opd2=op2;
    result=count++;
    next=NULL;
  }

int Quadruple::count=0;


string Quadruple::write_node(){
  if(operation=="a")
       return "Quilt q"+to_string(result)+"('a');\n";
  else if(operation=="b")
       return "Quilt q"+to_string(result)+"('b');\n";
  else if(operation=="turn")
       return "Quilt q"+to_string(result)+"=q"+to_string(opd1)+".turn();\n";
  else if(operation=="sew")
     return "Quilt q"+to_string(result)+"=q"+to_string(opd1)+".sew(q"+to_string(opd2)+");\n";
  else if(operation=="hdRow")
     return "Quilt q"+to_string(result)+"=q"+to_string(opd1)+".hdRow();\n";
  else if(operation=="tlRows")
     return "Quilt q"+to_string(result)+"=q"+to_string(opd1)+".tlRows();\n"; 
  else if(operation=="hdCol")
     return "Quilt q"+to_string(result)+"=q"+to_string(opd1)+".hdCol();\n";
 else if(operation=="tlCols")
     return "Quilt q"+to_string(result)+"=q"+to_string(opd1)+".tlCols();\n";


}


Gcode::Gcode(){
   head=NULL;
   tail=NULL;
}

Gcode::Gcode(string s){
  head=new Quadruple(s,-1,-1);
  tail=head;
}


void Gcode::insert_node(Quadruple *node){
    tail->next=node;
    tail=node;

}

Gcode Gcode::add_list(Gcode c){
  Gcode temp;
  tail->next=c.head;
  temp.head=head;
  temp.tail=c.tail;
  return temp; 
  

}


void Gcode::write_list(){
 Quadruple *ptr;
 ptr=head;
 string s;
 ofstream fout;
 fout.open("cppcode.cpp");
 fout<<"#include<iostream>\n#include\"Quilt.h\"\nusing namespace std;\nint main(){\n";
 while(ptr!=NULL){
   s=ptr->write_node();
   ptr=ptr->next;
   fout<<s;
  }
 fout<<"q"<<tail->result<<".display();\nreturn 0;\n}\n";

fout.close();

}
