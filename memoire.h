#ifndef MEMOIRE_H
#define MEMOIRE_H

/** Memoire**/
#define TAILLE_MEMOIRE 256
typedef struct
{
  char info[TAILLE_MEMOIRE];
  int fin;
} Memoire;
Memoire mem = {{0}, -1};


#include "variable.h"

// FONCTIONS
/** Nom de la fonction : allouer
 * Entrées :
 *    taille : La taille de la variable
 * Sorties :
 *    int adresse : L'adresse de la variable dans le tableau memoire
 * Description:
 *    Alloue de la place pour une variable dans le tableau memoire
 *  et retourne l'adresse de la memoire allouée
 */
Variable allouer(char *nom, unsigned int taille, Type type)
{
  int size;
  switch (type)
    {
    case INT: size = taille * sizeof(int); break;
    case CHAR: size = taille * sizeof(char); break;
    case FLOAT: size = taille * sizeof(float); break;
    case SHORT: size = taille * sizeof(short); break;
    case LONG: size = taille * sizeof(long); break;
    case DOUBLE: size = taille * sizeof(double); break;
    }

  Variable var;
  strcpy(var.nom, nom);
  var.size = size;
  var.type = type;

  if(mem.fin + size >= TAILLE_MEMOIRE)
    {
      printf("Memoire insuffisante\n");
      var.adrs = -1;
    }
  else
    {
      var.adrs =  mem.fin + 1;
      mem.fin += size;
    }
  return var;
}

/** Nom de la fonction : supprimer
  * Entrées :
  *   Variable var : La varible a supprimer
  * Description :
  *   Supprime l'espace allouée pour une variable dans la mémoire
  */
void supprimer(Variable var)
{
  int i;
  for(i = var.adrs; i + var.size < mem.fin; ++i)
    mem.info[i] = mem.info[i + var.size];

  mem.fin -= var.size;
}

void mem_afficher()
{
  printf("\n");
  int i;
  for(i = 0; i < TAILLE_MEMOIRE; ++i)
    printf("%d ", mem.info[i]);
  printf("\n");
}

#endif // MEMOIRE_H
