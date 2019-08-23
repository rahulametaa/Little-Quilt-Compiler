%{
#include<iostream>
#include<string>
#include<stdio.h>
#include "AST.h"
#include "Quilt.h"
#include "Symtab.h"
#include<map>
#include<vector>
extern int yylex(void);
extern "C" void yyerror(char *s);
using namespace std;
AST *tree;
Symtab_Stack STK; //Global stack
Symtab_Entry Global_Symtab;//Global Symbol table
extern vector<Quilt> Actual_Param;
%}

%union{
  char *name;
  class AST *ast;
  class DECL_AST *decl_ast;
  class FPARAM_AST *fparam_ast;
  class APARAM_AST *aparam_ast;
}


%token <name> A
%token <name> B
%token <name> TURN
%token <name> SEW
%token <name> HDROW
%token <name> TLROWS
%token <name> HDCOL
%token <name> TLCOLS
%token <name> COMMA
%token <name> OB
%token <name> CB
                                                                                     
%token <name> LET
%token <name> FUN
%token <name> VAL
%token <name> ID
%token <name> IN
%token <name> END
%token <name> ASSIGN
%start Start
%type <ast> Expr
%type <ast> Decl
%type <aparam_ast> Actuals
%type <decl_ast> Decls
%type <fparam_ast> Formals
%%


Start : Expr {tree=$1;};

Expr : TURN OB Expr CB { $$=new Turn_AST($3); }
       | SEW OB Expr COMMA Expr CB  {$$=new Sew_AST($3,$5);}
       | HDROW OB Expr CB      {$$=new HdRow_AST($3);}
       | TLROWS OB Expr CB     {$$=new TlRows_AST($3);}
       | HDCOL OB Expr CB      {$$=new HdCol_AST($3);}
       | TLCOLS OB Expr CB     {$$=new TlCols_AST($3);}
       | A {$$=new A_AST();}
       | B {$$=new B_AST();}
       | LET {Symtable tab;STK.push(tab);} Decls IN Expr END   {$$=new LET_AST($3,$5);STK.pop();}  
       | ID OB Actuals CB        {int temp=STK.get_entry(string($1)); 
                                  if(Global_Symtab.symtab_entry[temp].type=="fun") $$=new CALL_FUN_AST($1,$3,temp);}



       | ID    {int temp=STK.get_entry(string($1)); 
                if(temp==-1){cout<<"\nError:variable "<<$1<<" is not declared\n";exit(1);}
                else if(Global_Symtab.symtab_entry[temp].type=="param") $$=new CALL_PARAM_AST($1);
                else if(Global_Symtab.symtab_entry[temp].type=="val")  $$=new CALL_VAL_AST($1,temp);
                
               }                   

       ; 

Actuals : Expr {$$=new APARAM_AST($1);}
          | Expr COMMA Actuals {$3->Add_param($1);$$=$3;}
          ; 

Decls : Decl {$$=new DECL_AST($1);}
        | Decl Decls {$2->Add_decl($1);$$=$2;}   
        ;

Decl :  FUN ID {int temp=STK.get_top()->get_entry(string($2));
                                              if(temp!=-1) {cout<<"\nError:variable "<<$2<<" is already declared\n";exit(1);}
                                              Symtable tab;
                                              STK.push(tab);
                                             }  
               OB Formals CB ASSIGN Expr {$$=new FUN_AST($2,$5,$8);STK.pop();
                                         STK.get_top()->insert(string($2),"fun",$$);
                                          }

        | VAL ID ASSIGN Expr { int temp=STK.get_top()->get_entry(string($2)); 
                               if(temp==-1){
                                $$=new VAL_AST($2,$4);
                                STK.get_top()->insert(string($2),"val",$$);
                                }
                                else {cout<<"\nError:variable "<<$2<<" is already declared\n";exit(1);} }
        ;


Formals : ID    {$$=new FPARAM_AST($1);STK.get_top()->insert(string($1),"param",NULL);}      
          | ID COMMA Formals  { 
                               int temp=STK.get_top()->get_entry(string($1));
                               if(temp==-1){
                               $3->Add_param($1);$$=$3;
                               STK.get_top()->insert(string($1),"param",NULL);
                               }
                               else {cout<<"\nError:variable "<<$1<<" is already declared\n";exit(1);} }
                               
          ;
 




%%


void print_help(){
   cout<<"Usage: lqp [options]\n";
   cout<<" options:\n -eval: evaluate the expression\n -qast :print AST\n";
     

}


int main(int argc,char** argv)
 {

  string *s=new string[argc];
  for(int i=1;i<argc;i++)
     {
       string temp(argv[i]);
       s[i-1]=temp;
     }

  //declaring a map for every argument
  map<string,bool> x;
  for(int i=0;i<argc-1;i++)
    x.insert(pair<string,bool>(s[i],true));
 
 // if there is no argument or -help is present then
 if(argc==1 || x["-help"]==true)
  {
            print_help();
            return 0;
  }
  
  yyparse();

  //if demo is true then
  if(x["-d"]==true){
     if(x["-eval"]==true)
            tree->solve().display();
     if(x["-qast"]==true)
            tree->printtree();
     }
     

 }


