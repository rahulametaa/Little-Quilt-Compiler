#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<map>
using namespace std;
#include "AST.h"
#include "Gcode.h"
#include "Quilt.h"
#include "Symtab.h"


int AST::c=0;

extern Symtab_Entry Global_Symtab; 
Call_Stack C_STK; //call stack
map<string,int> Formal_Param; //map for formal parameter to actual parameter

////////////////////////////////////////////////////////////////////////////////////////////////////

Turn_AST::Turn_AST(AST *ptr){
         this->ptr=ptr;
    } 
  

void Turn_AST::printtree(){
       
       for(int i=0;i<c;i++) cout<<" ";
       cout<<"(TURN"<<endl;
       c=c+4;
       ptr->printtree();
       c=c-4;
       for(int i=0;i<c;i++) cout<<" ";
       cout<<")"<<endl;

    }  

Quilt Turn_AST::solve(){
   Quilt m;
   m=ptr->solve();
   return m.turn();
}



Gcode Turn_AST::generate_cpp(){

  Gcode c1=ptr->generate_cpp();
  Quadruple *node=new Quadruple("turn",c1.tail->result,-1);
  c1.insert_node(node);
  return c1;  
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

Sew_AST::Sew_AST(AST *lptr,AST *rptr){
      this->lptr=lptr;
      this->rptr=rptr;
     }



void Sew_AST::printtree(){
       for(int i=0;i<c;i++) cout<<" ";
       cout<<"(SEW"<<endl;
        c=c+4;
        this->lptr->printtree();
        for(int i=0;i<c;i++) cout<<" ";
        cout<<","<<endl;
        this->rptr->printtree();
        c=c-4;
        for(int i=0;i<c;i++) cout<<" ";
        cout<<")"<<endl;

    }  


Quilt Sew_AST::solve(){
   Quilt m1,m2;
   m1=lptr->solve();
   m2=rptr->solve();
   
   return m1.sew(m2);
     


}


Gcode Sew_AST::generate_cpp(){

  Gcode c1=lptr->generate_cpp();
  Gcode c2=rptr->generate_cpp();
  Quadruple *node=new Quadruple("sew",c1.tail->result,c2.tail->result);
  Gcode c3=c1.add_list(c2);
  c3.insert_node(node);
  return c3;
}


////////////////////////////////////////////////////////////////////////////////////////////////

void A_AST::printtree(){
       for(int i=0;i<c;i++) cout<<" ";
       cout<<"(A"<<endl;
       for(int i=0;i<c;i++) cout<<" ";
       cout<<")"<<endl;
    }  
      


Quilt A_AST::solve(){
   Quilt m('a');
   return m;


}



Gcode A_AST::generate_cpp(){
   return Gcode("a");
            
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////

void B_AST::printtree(){
       for(int i=0;i<c;i++) cout<<" ";
       cout<<"(B"<<endl;
       for(int i=0;i<c;i++) cout<<" ";
       cout<<")"<<endl;
    }  
      


Quilt B_AST::solve(){
   Quilt m('b');
   return m;


}


Gcode B_AST::generate_cpp(){
   return Gcode("b");
            
}

 
///////////////////////////////////////////////////////////////////////////////////////////////////

HdRow_AST::HdRow_AST(AST *ptr){
         this->ptr=ptr;
    } 
  
void HdRow_AST::printtree(){
       for(int i=0;i<c;i++) cout<<" ";
       cout<<"(hdRow"<<endl;
       c=c+4;
       ptr->printtree();
       c=c-4;
       for(int i=0;i<c;i++) cout<<" ";
       cout<<")"<<endl;
 }

Quilt HdRow_AST::solve(){
   Quilt m;
   m=ptr->solve();
   return m.hdRow();
}  

Gcode HdRow_AST::generate_cpp(){

  Gcode c1=ptr->generate_cpp();
  Quadruple *node=new Quadruple("hdRow",c1.tail->result,-1);
  c1.insert_node(node);
  return c1;  
}




///////////////////////////////////////////////////////////////////////////////////////////

TlRows_AST::TlRows_AST(AST *ptr){
         this->ptr=ptr;
    } 


void TlRows_AST::printtree(){
       for(int i=0;i<c;i++) cout<<" ";
       cout<<"(tlRows"<<endl;
       c=c+4;
       ptr->printtree();
       c=c-4;
       for(int i=0;i<c;i++) cout<<" ";
       cout<<")"<<endl;

    }  
  
Quilt TlRows_AST::solve(){
   Quilt m;
   m=ptr->solve();
   return m.tlRows();
}

Gcode TlRows_AST::generate_cpp(){

  Gcode c1=ptr->generate_cpp();
  Quadruple *node=new Quadruple("tlRows",c1.tail->result,-1);
  c1.insert_node(node);
  return c1;  
}



//////////////////////////////////////////////////////////////////////////////////////

HdCol_AST::HdCol_AST(AST *ptr){
         this->ptr=ptr;
    } 

void HdCol_AST::printtree(){
       for(int i=0;i<c;i++) cout<<" ";
       cout<<"(hdCol"<<endl;
       c=c+4;
       ptr->printtree();
       c=c-4;
       for(int i=0;i<c;i++) cout<<" ";
       cout<<")"<<endl;

    } 

Quilt HdCol_AST::solve(){
   Quilt m;
   m=ptr->solve();
   return m.hdCol();
}
 

Gcode HdCol_AST::generate_cpp(){

  Gcode c1=ptr->generate_cpp();
  Quadruple *node=new Quadruple("hdCol",c1.tail->result,-1);
  c1.insert_node(node);
  return c1;  
}  



//////////////////////////////////////////////////////////////////////////////////////////////////

TlCols_AST::TlCols_AST(AST *ptr){
         this->ptr=ptr;
    } 
  

void TlCols_AST::printtree(){
       for(int i=0;i<c;i++) cout<<" ";
       cout<<"(tlCols"<<endl;
       c=c+4;
       ptr->printtree();
       c=c-4;
       for(int i=0;i<c;i++) cout<<" ";
       cout<<")"<<endl;
    }  


Quilt TlCols_AST::solve(){
   Quilt m;
   m=ptr->solve();
   return m.tlCols();
}


Gcode TlCols_AST::generate_cpp(){

  Gcode c1=ptr->generate_cpp();
  Quadruple *node=new Quadruple("tlCols",c1.tail->result,-1);
  c1.insert_node(node);
  return c1;  
}


///////////////////////////////////////////////////////////////////////////////
LET_AST::LET_AST(AST *decls,AST *expr){
    this->decls=decls;
    this->expr=expr;

}

void LET_AST::printtree(){
    for(int i=0;i<c;i++) cout<<" ";
    cout<<"(LET"<<endl;
    c=c+4;
    decls->printtree();
    for(int i=0;i<c;i++) cout<<" ";
    cout<<","<<endl;
    for(int i=0;i<c;i++) cout<<" ";
    cout<<"(IN EXPR"<<endl;
    c=c+4;
    expr->printtree();
    c=c-4; 
    for(int i=0;i<c;i++) cout<<" ";
    cout<<")"<<endl;
    c=c-4;
    for(int i=0;i<c;i++) cout<<" ";
    cout<<")"<<endl;
    
}

Quilt LET_AST::solve(){
 return expr->solve();
}

Gcode LET_AST::generate_cpp(){

}




/////////////////////////////////////////////////////////////////////////////////

DECL_AST::DECL_AST(AST *decl){
 no_decl=1;
 decls=(AST**)(malloc(sizeof(AST*)*200));
 decls[0]=decl;
     
}


void DECL_AST::Add_decl(AST *decl){
  for(int i=no_decl;i>0;i--)
      decls[i]=decls[i-1];
  decls[0]=decl;
  no_decl+=1;
}


void DECL_AST::printtree(){
    for(int i=0;i<c;i++) cout<<" ";
    cout<<"(DECLS"<<endl;
    c=c+4;

    for(int i=0;i<no_decl;i++){
      decls[i]->printtree();
      if(i!=(no_decl-1)){
      for(int j=0;j<c;j++) cout<<" ";
      cout<<","<<endl;
      }
    }

    c=c-4;
    for(int i=0;i<c;i++) cout<<" ";
    cout<<")"<<endl;
 } 


Quilt DECL_AST::solve(){
}

Gcode DECL_AST::generate_cpp(){

}


//////////////////////////////////////////////////////////////////////
VAL_AST::VAL_AST(char *name,AST* expr){
   this->name=name;
   this->expr=expr;
}

void VAL_AST::printtree(){
    for(int i=0;i<c;i++) cout<<" ";
    cout<<"(VAL "<<name<<"="<<endl;
    c=c+4;
    expr->printtree();
    c=c-4;
    for(int i=0;i<c;i++) cout<<" ";
    cout<<")"<<endl;
    
}

Quilt VAL_AST::solve(){
  return expr->solve();
}

Gcode VAL_AST::generate_cpp(){

}



////////////////////////////////////////////////////////////
FUN_AST::FUN_AST(char *name,AST *fplist,AST *expr){
   this->name=name;
   this->fplist=fplist;
   this->expr=expr;

}

void FUN_AST::printtree(){
   for(int i=0;i<c;i++) cout<<" ";
   cout<<"(FUN "<<name<<"="<<endl;
   c=c+4;
   fplist->printtree();
   for(int i=0;i<c;i++) cout<<" ";
   cout<<","<<endl;
   for(int i=0;i<c;i++) cout<<" ";
   cout<<"(EXPR"<<endl;
   c=c+4;
   expr->printtree();
   c=c-4;
   for(int i=0;i<c;i++) cout<<" ";
   cout<<")"<<endl;
   c=c-4;
   for(int i=0;i<c;i++) cout<<" ";
   cout<<")"<<endl;

}


Quilt FUN_AST::solve(){
    fplist->solve();
    return expr->solve();
}
 

Gcode FUN_AST::generate_cpp(){

}



///////////////////////////////////////////////////////////////////

FPARAM_AST::FPARAM_AST(char *name){
     fplist=(char**)malloc(sizeof(char *)*200);
     fplist[0]=name;
     no_fp=1;
}

void FPARAM_AST::Add_param(char *name){
   for(int i=no_fp;i>0;i--)
      fplist[i]=fplist[i-1];
  fplist[0]=name;
  no_fp+=1;
 }

void FPARAM_AST::printtree(){
        for(int i=0;i<c;i++) cout<<" ";
        cout<<"(PARAMS"<<endl;
        c=c+4;
        for(int j=0;j<c;j++) cout<<" ";
        cout<<"(";
        for(int i=0;i<no_fp;i++){
          cout<<fplist[i];
          if(i!=no_fp-1)
          cout<<",";
        }
        cout<<")"<<endl;
        c=c-4;
        for(int i=0;i<c;i++) cout<<" ";
        cout<<")"<<endl;
        
}

Quilt FPARAM_AST::solve(){
  for(int i=0;i<no_fp;i++)
     Formal_Param.insert(pair<string,int>(string(fplist[i]),i));
  Quilt q;
  return q;
}

Gcode FPARAM_AST::generate_cpp(){

}


///////////////////////////////////////////////////////////////
CALL_FUN_AST::CALL_FUN_AST(char *name,AST *aplist,int ptr){
  this->name=name;
  this->aplist=aplist;
  this->ptr=ptr;

}

void CALL_FUN_AST::printtree(){
    for(int i=0;i<c;i++) cout<<" ";
    cout<<"(CALL FUN "<<name<<endl;
    c=c+4;
    aplist->printtree();
    c=c-4;
    for(int i=0;i<c;i++) cout<<" ";
    cout<<")"<<endl;

}

Quilt CALL_FUN_AST::solve(){
     //cout<<"call fun AST "<<name<<endl<<endl;
     aplist->solve();
    // C_STK.get_top()[0].display();
     Quilt temp=Global_Symtab.symtab_entry[ptr].ptr->solve();
     C_STK.pop();
     Formal_Param.clear();
     return temp;
}

Gcode CALL_FUN_AST::generate_cpp(){

}





///////////////////////////////////////////////////////////////
CALL_VAL_AST::CALL_VAL_AST(char *name,int ptr){
  this->name=name;
  this->ptr=ptr;

}

void CALL_VAL_AST::printtree(){
    for(int i=0;i<c;i++) cout<<" ";
    cout<<"(CALL VAL"<<endl;
    c=c+4;
    for(int i=0;i<c;i++) cout<<" ";
    cout<<"("<<name<<endl;
    for(int i=0;i<c;i++) cout<<" ";
    cout<<")"<<endl;
    c=c-4;
    for(int i=0;i<c;i++) cout<<" ";
    cout<<")"<<endl;
    

}

Quilt CALL_VAL_AST::solve(){
    return Global_Symtab.symtab_entry[ptr].ptr->solve();
    
}

Gcode CALL_VAL_AST::generate_cpp(){

}



///////////////////////////////////////////////////////////////
CALL_PARAM_AST::CALL_PARAM_AST(char *name){
  this->name=name;

}

void CALL_PARAM_AST::printtree(){
    for(int i=0;i<c;i++) cout<<" ";
    cout<<"(Formal Param"<<endl;
    c=c+4;
    for(int i=0;i<c;i++) cout<<" ";
    cout<<name<<endl;
    c=c-4;
    for(int i=0;i<c;i++) cout<<" ";
    cout<<")"<<endl;
    

}

Quilt CALL_PARAM_AST::solve(){
  vector<Quilt> temp=C_STK.get_top();
  //cout<<Formal_Param[string(name)]<<endl;
  //cout<<temp.size()<<endl;
 // temp[Formal_Param[string(name)]].display();
  return temp[Formal_Param[string(name)]];
}

Gcode CALL_PARAM_AST::generate_cpp(){

}




/////////////////////////////////////////////////////////////////////////////////////////////
APARAM_AST::APARAM_AST(AST *expr){
    aplist=(AST**)malloc(sizeof(AST *)*200);
    aplist[0]=expr;
    no_ap=1;
    
}

void APARAM_AST::Add_param(AST *expr){
    for(int i=no_ap;i>0;i--)
      aplist[i]=aplist[i-1];
   aplist[0]=expr;
   no_ap+=1;


}


void APARAM_AST::printtree(){
    for(int i=0;i<c;i++) cout<<" ";
        cout<<"(ACTUAL PARAMS"<<endl;
        c=c+4;
        for(int i=0;i<no_ap;i++){
          aplist[i]->printtree();
          if(i!=no_ap-1){
          for(int i=0;i<c;i++) cout<<" ";
          cout<<","<<endl;
          }
        }
        c=c-4;
        for(int i=0;i<c;i++) cout<<" ";
        cout<<")"<<endl;

}

Quilt APARAM_AST::solve(){
  //C_STK.push();
  //cout<<C_STK.top<<endl;
  vector<Quilt> temp;
  for(int i=0;i<no_ap;i++)
  {
     //C_STK.insert(aplist[i]->solve());
      temp.push_back(aplist[i]->solve());
  }
   C_STK.push(temp);
  //cout<<C_STK.top<<endl;
   
   Quilt q;
   return q;
}


Gcode APARAM_AST::generate_cpp(){

}

