#ifndef VARIABLE_H
#define VARIABLE_H

#include "memoire.h"

#include <string.h>
#include <stdio.h>

/** Type de la variable**/
typedef enum {INT, CHAR , FLOAT, SHORT, LONG, DOUBLE} Type;

/** Variable **/
typedef struct
{
  char nom[100];
  unsigned int size;
  int adrs;
  Type type;
} Variable;


void lire_valeur(Variable var)
{
  #define LIRE_VALEUR_TYPE(TYPE, PERCENT)                               \
    {                                                                   \
      TYPE val = 0;                                                     \
      unsigned int i ;                                                  \
      for(i = 0; i < var.size / sizeof(TYPE); ++i)                      \
      {                                                                 \
        printf("element %d : ", i);                                   \
        char c;                                                         \
        while(c != '\n') c = getchar(); /*Vider le buffer*/             \
        scanf(PERCENT, &val);                                           \
        memcpy((void*) mem.info + var.adrs + i, &val, sizeof(TYPE));    \
      }                                                                 \
      break;                                                            \
    }

  switch(var.type)
    {
    case INT: LIRE_VALEUR_TYPE(int, "%d");
    case FLOAT: LIRE_VALEUR_TYPE(float, "%f");
    case CHAR: LIRE_VALEUR_TYPE(char, "%c");
    case SHORT: LIRE_VALEUR_TYPE(short, "%d");
    case LONG: LIRE_VALEUR_TYPE(long, "%ld");
    case DOUBLE: LIRE_VALEUR_TYPE(double, "%lf");
    }
}

char* type_a_chaine(Type type)
{
  switch (type)
    {
    case INT: return "int";
    case CHAR: return "char";
    case FLOAT: return "float";
    case SHORT: return "short";
    case LONG: return "long";
    case DOUBLE: return "double";
    default: return "";
    }
}

void afficher_val(Variable var)
{
  #define AFFICHER_VAL_TYPE(TYPE, PERC)                        \
    {                                                          \
      unsigned int i;                                          \
      for(i = 0; i < var.size / sizeof(TYPE); ++i)             \
        {                                                      \
          printf("element %d : ", i);                          \
          TYPE val;                                            \
          memcpy(&val, (void*) mem.info + var.adrs + i, sizeof(TYPE)); \
          printf(PERC, val);                                   \
          printf("\n");                                        \
        }                                                      \
      break;                                                   \
    }                                                          \

    switch(var.type)
      {
      case INT: AFFICHER_VAL_TYPE(int, "%d");
      case FLOAT: AFFICHER_VAL_TYPE(float, "%f");
      case CHAR: AFFICHER_VAL_TYPE(char, "%c");
      case SHORT: AFFICHER_VAL_TYPE(short,"%d");
      case LONG: AFFICHER_VAL_TYPE(long, "%ld");
      case DOUBLE: AFFICHER_VAL_TYPE(double, "%lf");
      }
}

void variable_copie(Variable src, Variable *dest)
{
  dest->adrs = src.adrs;
  strcpy(dest->nom, src.nom);
  dest->size = src.size;
  dest->type = src.type;
}

/** Liste **/
typedef struct Liste
{
  Variable var;
  struct Liste *suiv;
} Liste;

Liste* liste_creer(Variable var)
{
  Liste *liste = calloc(1, sizeof(Liste));
  if(!liste)
    {
      printf("Erreur d'allocation de mémoire\n");
      exit(1);
    }
  variable_copie(var, &liste->var);
  return liste;
}

void liste_ajout(Liste **list, Variable var)
{
  Liste *nouv = liste_creer(var);
  // Liste vide
  if(!(*list)) *list = nouv;
  // Ajout à la fin
  else
    {
      Liste *courant = *list;
      for(; courant->suiv; courant = courant->suiv);
      courant->suiv = nouv;
    }
}

void liste_supprimer(Liste **list, char *nom)
{
  if(!(*list))
    printf("Liste vide.\n");
  else
    {
      if(!strcmp((*list)->var.nom, nom))
        {
          Liste *tete = (*list);
          *list = (*list)->suiv;
          free(tete);
        }
      else
        {
          Liste *courant = *list;
          while(courant->suiv)
            {
              if(!strcmp(courant->suiv->var.nom, nom))
                {
                  Liste *supr = courant->suiv;
                  courant->suiv = courant->suiv->suiv;
                  free(supr);
                  printf("\"%s\" supprimée.\n", nom);
                  return;
                }
              courant = courant->suiv;
            }
          printf("\"%s\" n'existe pas.\n", nom);
        }
    }
}

Variable* recherche_variable(Liste *list, char *nom)
{
  Liste *courant = list;
  while(courant)
    {
      if(!strcmp(courant->var.nom, nom))
        return &courant->var;
      courant = courant->suiv;
    }

  return NULL;
}

void liste_detruire(Liste **liste)
{
  while(*liste) liste_supprimer(liste, 0);
  free(*liste);
  liste = NULL;
}
#endif // VARIABLE_H
