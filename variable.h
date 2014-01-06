#ifndef VARIABLE_H
#define VARIABLE_H

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


#endif // VARIABLE_H
