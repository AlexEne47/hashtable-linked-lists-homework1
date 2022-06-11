/* ENE Alexandru - 321CBa Anul 2 */

#include <stdio.h>
#include <string.h>

typedef int (*TFHash)(void*);

typedef struct lista
{
  void* info;        
  struct sublista *sub; 
  struct lista *urm;   
} *TLG;

typedef struct sublista
{
  void* info;          
  int nr_aparitii;
  struct sublista *urm;       
} *TLS;

typedef struct tabela
{
    size_t M;
    TFHash fh;
    TLG *v;
} *TH;

