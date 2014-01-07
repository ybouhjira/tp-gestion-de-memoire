#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memoire.h"

int main()
{
  int choix;
  Liste *liste = NULL; // Liste des variables
  do
    {
      printf("\n______________________________\n"
             "1 - Utilisation de la mémoire\n"
             "2 - Ajouter une variable\n"
             "3 - Afficher une variable\n"
             "4 - Supprimer une variable\n"
             "Autre - Quitter\n"
             "Choix : ");
      scanf("%d", &choix);
      printf("------------------------------\n\n");

      switch(choix)
        {
        case 1: // Utilisation de la mémoire
          printf("Mémoire utilisée : %d octet\n", mem.fin + 1);
          break;
        case 2: // Ajout d'une variable
          {
            // nom
            char nom[100];
            printf("Nom de la variable : ");
            scanf("%s", nom);

            // taille
            int taille;
            printf("Taille : ");
            scanf("%d", &taille);

            // type
            int typeNum = 0;
            printf("Type : \n"
                   "0 - INT\n"
                   "1 - CHAR\n"
                   "2 - FLOAT\n"
                   "3 - SHORT\n"
                   "4 - LONG\n"
                   "5 - DOUBLE\n");
            scanf("%d", &typeNum);

            // allocation
            Variable var = allouer(nom, taille, (Type) typeNum);

            // valeur
            printf("Valeurs : \n");
            lire_valeur(var);

            // stockage dans la liste
            liste_ajout(&liste, var);
            break;
          }
        case 3: // Affichage d'une variable
          {
            char nom[100];
            printf("Entrez le nom de la variable : ");
            scanf("%s", nom);
            Variable *var = recherche_variable(liste, nom);
            if(var)
              {
                printf("Adresse : %d\n"
                       "Type : %s\n"
                       "Valeur : \n",
                       var->adrs, type_a_chaine(var->type));
                afficher_val(*var);
                printf("\n");
                printf("Taille : %d\n", var->size);
              }
            else printf("\"%s\" n'existe pas\n", nom);
            break;
          }
        case 4: // Supression d'une variable
          {
            char nom[100];
            printf("Entrez le nom de la variable : ");
            scanf("%s", nom);

            supprimer(*(recherche_variable(liste, nom)));
            liste_supprimer(&liste, nom);
          }
        }

    } while( 1 <= choix && choix <= 4);

  return 0;
}
