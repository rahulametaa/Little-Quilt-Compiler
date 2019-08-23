#ifndef SYMTAB_H
#define SYMTAB_H

#include<iostream>
#include<stdio.h>
#include<string>
#include<map>
#include<vector>
#include "AST.h"
using namespace std;

struct Entry{
        string name;
        string type;
        AST *ptr;
};

class Symtab_Entry{
    public:
    vector<Entry> symtab_entry;
   int insert_entry(string name,string type,AST *ptr);
   void display();
   
  
};


class Symtable{
   vector<int> symtab;
   public:
     void insert(string name,string type,AST *ptr);
     int get_entry(string name);
     void display();

};

class Symtab_Stack{
     vector<Symtable> stk;
     public:
      int top;
      Symtab_Stack();
      void push(Symtable tab);
      void pop();
      Symtable* get_top();
      int get_entry(string name);
      void display();

};


class Call_Stack{
    vector<vector<Quilt>> c_stk;
  public:
     int top;
     Call_Stack();
     void push(vector<Quilt> q);
     void pop();
     void insert(Quilt q);
     vector<Quilt> get_top();
     void display();


};









#endif
 
