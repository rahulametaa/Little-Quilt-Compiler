#include<iostream>
#include<stdio.h>
#include<string>
#include<map>
#include "AST.h"
#include "Symtab.h"
//Symtab_Entry Global_Symtab;

using namespace std;
extern Symtab_Entry Global_Symtab; 

int Symtab_Entry::insert_entry(string name,string type,AST *ptr){
    Entry ent={name,type,ptr};
    symtab_entry.push_back(ent);
    return (symtab_entry.size()-1);

}


void Symtab_Entry::display(){
   for(int i=0;i<symtab_entry.size();i++){
      cout<<symtab_entry[i].name<<"    "<<symtab_entry[i].type<<"   "<<symtab_entry[i].ptr<<endl;
   }

}

void Symtable::insert(string name,string type,AST *ptr){
     symtab.push_back(Global_Symtab.insert_entry(name,type,ptr));      

}

int Symtable::get_entry(string name){
  for(int i=0;i<symtab.size();i++){
      if(Global_Symtab.symtab_entry[symtab[i]].name==name)
               return symtab[i];
  }
  return -1;
}

void Symtable::display(){
  for(int i=0;i<symtab.size();i++)
      cout<<symtab[i]<<" ";

}

Symtab_Stack::Symtab_Stack(){
 top=-1;
}

void Symtab_Stack::push(Symtable tab){
   stk.push_back(tab);
   top++;

}

void Symtab_Stack::pop(){
   if(top==-1) return; 
   stk.pop_back();
   top--;
}


void Symtab_Stack::display(){
  for(int i=0;i<stk.size();i++){
      stk[i].display();
      cout<<endl<<endl;
  }

}

Symtable* Symtab_Stack::get_top()
{
   return &stk[top];

}

int Symtab_Stack::get_entry(string name){
   int temp;
   for(int i=top;i>=0;i--){
        temp=stk[i].get_entry(name); 
        if(temp!=-1)
            return temp;        
   }
   return -1;
}


Call_Stack::Call_Stack(){
 top=-1;
}

void Call_Stack::push(vector<Quilt> q){
   // vector<Quilt> temp;
    c_stk.push_back(q);
    top++;

}

void Call_Stack::pop(){
     c_stk.pop_back();
     top--;

}

void Call_Stack::insert(Quilt q){
     c_stk[top].push_back(q);

}

vector<Quilt> Call_Stack::get_top(){
   if(top==-1)
     cout<<"stack is empty\n";
   else   
     return c_stk[top];

}

void Call_Stack::display(){
    for(int i=0;i<=top;i++){
      for(int j=0;j<c_stk[i].size();j++)
          c_stk[i][j].display();
      cout<<endl;
   } 
}



/*
int main(){
   Call_Stack s;
   Quilt q1('a');
   Quilt q2('b');
   s.push();
   s.insert(q1);
   s.insert(q2);
   s.push();
   s.insert(q2);
   s.insert(q2);
   s.pop();
   s.get_top()[0].display();
   
   return 0; 


}*/
