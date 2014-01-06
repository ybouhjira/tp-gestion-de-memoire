#ifndef MEMOIRE_H
#define MEMOIRE_H

#include "variable.h"

/** Memoire**/
#define TAILLE_MEMOIRE 256
typedef struct {
  char info[TAILLE_MEMOIRE];
  int fin;
} Memoire;
Memoire mem = {{0}, -1};

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
Variable allouer(char *nom, unsigned int taille)
{
  Variable var;
  strcpy(var.nom, nom);
  var.size = taille;

  if(mem.fin + taille >= TAILLE_MEMOIRE)
    {
      printf("Memoire insuffisante\n");
      var.adrs = -1;
    }
  else
    {
      var.adrs =  mem.fin + 1;
      mem.fin += taille;
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
  unsigned int i;
  for(i = 0; i < mem.fin - (var.adrs + var.size); ++i)
    mem.info[var.adrs + i] = mem.info[var.adrs + var.size + i];

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