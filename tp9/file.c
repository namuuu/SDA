#include "file.h" 


void initFile(T_File *ptrF) //mettre Tete et Queue à -1
{
    ptrF->Tete=-1;
    ptrF->Queue=-1;
}

int  retirer(T_File *ptrF,T_Elt *ptrE) //si pas vide, en tete de file
{
    if(fileVide(ptrF)==0){
       affecterElt(ptrE,&(ptrF->Elts[ptrF->Tete]));
       if(ptrF->Tete==ptrF->Queue){
           initFile(ptrF);
       }else if(ptrF->Tete==MAX){
            ptrF->Tete=0;
       }else{
           ptrF->Tete=ptrF->Tete+1;
       }
        
    return 1;
    }
return 0;
}

int ajouter(T_File *ptrF,T_Elt *ptrE) // si espace libre, ajout en queue
{
    if(filePleine(ptrF)==0){
        if(ptrF->Tete==MAX){
            ptrF->Elts[ptrF->Queue]=0;
        }else {
            ptrF->Queue=ptrF->Queue+1;
        }
        printf("%d",ptrF->Queue);
        affecterElt(&(ptrF->Elts[ptrF->Queue]),ptrE);
        return 1;   
    }

return 0;
} 

int fileVide(const  T_File *prtF) // qd Tete == 0 
{
    if(prtF->Queue==-1){
        return 1;
    }
return 0;
}

int filePleine(const  T_File *ptrF) // qd MAX elts dans la file 
{
    if( (ptrF->Tete ==0 && ptrF->Queue==MAX) || ptrF->Queue==ptrF->Tete-1 ){
        return 1;
    }
return 0;
}

T_Elt  premier(T_File *ptrF) //valeur en tete de file
{ if(fileVide(ptrF)==0){
    afficherElt(&(ptrF->Elts[ptrF->Tete+1]));
    return 1;
}
return 0;
}

void afficherFile(T_File *ptrF)
{
    if(ptrF->Tete <= ptrF->Queue){
        for(int i=ptrF->Tete+1;i<=ptrF->Queue;i++){
        afficherElt(&(ptrF->Elts[i]));
        }
    }else{
        for(int i=ptrF->Tete;i<=MAX;i++){
         afficherElt(&(ptrF->Elts[i]));
        }
         for(int i=0;i<=ptrF->Queue;i++){
         afficherElt(&(ptrF->Elts[i]));
        }

    }
}






