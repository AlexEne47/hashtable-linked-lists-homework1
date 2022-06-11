/* ENE Alexandru - 321CBa Anul 2 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "main.h"

#define MAX_LINE_SIZE 100

int codHash(void * element)
{
    // Calculez codul hash primului caracter
	char *nume = (char *) element;
	if(nume[0] >= 'A' && nume[0] <= 'Z') {
		nume[0] = tolower(nume[0]);
		return nume[0] - 'a';
	}
	else if(nume[0] >= 'a' && nume[0] <= 'z')
	return nume[0] - 'a';
	else
	return -1;
}

TH InitTH()
{
    size_t M = ('Z'-'A') + 1;
    TH h = (TH) calloc(sizeof(struct tabela), 1);

    // Verific alocarea tabelei
    if (h == NULL) {
        printf("Eroare alocare hash\n");
        return NULL;
    }

    // Verific alocarea listelor din tabela
    h->v = (TLG *) calloc(M, sizeof(struct lista));
    if(h->v == NULL) {
        printf("Eroare alocare liste in tabela hash\n");
        free(h);
        return NULL;
    }

    h->M = M;
    h->fh = codHash;
    return h;
}

TLS AlocTLS(void *el) {
    TLS aux = (struct sublista *) malloc(sizeof(struct sublista));
    aux->info = malloc(sizeof(el)*sizeof(char));
    strcpy(aux->info, (char *)el);
    aux->nr_aparitii = 1;
    aux->urm = NULL;

    return aux;
}

TLG AlocTLG(void *el) {
    TLG aux = (struct lista *) malloc(sizeof(struct lista));
    aux->info = malloc(sizeof(int));
    *((int *)(aux->info)) = ((int) strlen((char *)el));
    aux->sub = (struct sublista *)malloc(sizeof(struct sublista));
    aux->sub->info = malloc(sizeof(el)*sizeof(char));
    strcpy(aux->sub->info, (char *)el);
    aux->sub->nr_aparitii = 1;
    aux->sub->urm = NULL;
    aux->urm = NULL;

    return aux;
}

void InsertTLS(void *el, TLG l) {

    if(l->sub == NULL) {
    TLS aux = AlocTLS(el);
    l->sub = aux;
    }
    else
    for(TLS temp = l->sub; temp != NULL; temp = temp -> urm) {
        if(strcmp((char*)(temp->info),(char*)el) == 0) {
            temp -> nr_aparitii++;
            break;
        }
        if(temp -> urm == NULL) {
            TLS aux = AlocTLS(el);
            temp -> urm = aux;
            break;
        }
    }
}


int InsertTH(void *el, TH h, int cod) {
    size_t M = ('Z'-'A') + 1;
    if(strlen((char *)el) < 3)
    return 0;
    if(((char *)el)[0] >= '0' && ((char *)el)[0] <= '9')
    return 0;

    // Introduc lista creata in tabela hash
    if(h->v[cod] == NULL) {
        TLG aux = AlocTLG(el);
        h->v[cod] = aux;
    }
    else {
        for(TLG temp = h->v[cod]; temp != NULL; temp = temp -> urm) {
            if(*((int *)(temp->info)) == strlen((char *)el)) { //Daca avem deja lungimea
                InsertTLS(el, temp);
                break;
            } else if(temp -> urm == NULL) {
                TLG aux = AlocTLG(el);
                temp -> urm = aux;
                break;
            }
        }
    }

    return 1;
}

void PrintTH(TH h) {
    size_t M = ('Z'-'A') + 1;

    // Parcurg toate listele/sublistele din TH
    for(int i=0; i<M; i++) {
        TLG temp = h->v[i];

        if(h->v[i] != NULL) {
        printf("pos %d: ",i);
        for(TLG temp = h->v[i]; temp != NULL; temp = temp -> urm) {
            printf("(%d:",*((int *)(temp->info)));
            for(TLS temp1 = temp->sub; temp1 != NULL; temp1 = temp1 -> urm)
            if(temp1 -> urm != NULL)
            printf("%s/%d, ",(char*)(temp1->info), temp1->nr_aparitii);
            else
            printf("%s/%d",(char*)(temp1->info), temp1->nr_aparitii);

            printf(")");
        }
        printf("\n");
        }
    }
}

void PrintnTH(TH h, int n) {
    size_t M = ('Z'-'A') + 1;

    // Parcurg listele si verific fiecare caz
    for(int i=0; i<M; i++) {
        
        int gasit = 0;
        for(TLG temp = h->v[i]; temp != NULL; temp = temp -> urm)
        for(TLS temp1 = temp->sub; temp1 != NULL; temp1 = temp1 -> urm)
        if(temp1 -> nr_aparitii  <= n) 
        gasit = 1;

        if(gasit) {
        printf("pos%d: ",i);
        
        for(TLG temp = h->v[i]; temp != NULL; temp = temp -> urm) {
            int gasit1 = 0;

            for(TLS temp1 = temp->sub; temp1 != NULL; temp1 = temp1 -> urm) 
            if(temp1 -> nr_aparitii  <= n)
            gasit1++;

            if(gasit1) {
            printf("(%d: ",*((int *)(temp->info)));
            for(TLS temp1 = temp->sub; temp1 != NULL; temp1 = temp1 -> urm) {
            if(temp1 -> nr_aparitii  <= n)
            if(temp1 -> urm != NULL && gasit1 - 1) {
            printf("%s/%d, ",(char*)(temp1->info), temp1->nr_aparitii);
            gasit1--;}
            else
            printf("%s/%d",(char*)(temp1->info), temp1->nr_aparitii);
            }

            printf(")");
            }
        }
            printf("\n");
        }
        
    
    }
}

void PrintcnTH(TH h, char c, int n) {
    char str[1];
    str[0] = c;
    int poz = codHash(str), gasit = 0;
    
    // Creez un cod hash pentru caracterul c 
    // si parcurg lista corespunzatoare
    for(TLG temp = h->v[poz]; temp != NULL; temp = temp -> urm)
    if(*((int *)(temp->info)) == n) {
        printf("(%d:",*((int *)(temp->info)));
        for(TLS temp1 = temp->sub; temp1 != NULL; temp1 = temp1 -> urm){
            if(temp1 -> urm != NULL) 
            printf("%s/%d, ",(char*)(temp1->info), temp1->nr_aparitii);
            else
            printf("%s/%d",(char*)(temp1->info), temp1->nr_aparitii);
        }
        printf(")\n");
    }
}

void SortareTLS(TH h) {
    size_t M = ('Z'-'A') + 1;

    for(int i=0; i<M; i++) {
        TLG temp = h->v[i];

        if(temp == NULL)
        continue;

        for(; temp != NULL; temp = temp -> urm) {

        TLS head = temp->sub, prev;
        if(head == NULL)
        continue;
        if(head -> urm == NULL)
        continue;

        head = head -> urm;

        int sortat = 0;
        while(!sortat) {
        sortat = 1;
        prev = temp->sub;
        head = temp->sub->urm;
        for(; head != NULL; head = head -> urm, prev = prev -> urm) {
            if(prev->nr_aparitii < head->nr_aparitii ) {
                int aux = prev -> nr_aparitii;
                prev->nr_aparitii = head->nr_aparitii;
                head->nr_aparitii = aux;
                sortat = 0;

                char cuv[50];
                strcpy(cuv, (char *)(prev->info));
                strcpy((char *)(prev->info),(char *)(head->info));
                strcpy((char *)(head->info),cuv);
            }
            else if(prev->nr_aparitii == head->nr_aparitii) {
                if(strcmp((char *)(prev->info) , (char *)(head->info)) > 0) {
                int aux = prev -> nr_aparitii;
                prev->nr_aparitii = head->nr_aparitii;
                head->nr_aparitii = aux;
                sortat = 0;

                char cuv[50];
                strcpy(cuv, (char *)(prev->info));
                strcpy((char *)(prev->info),(char *)(head->info));
                strcpy((char *)(head->info),cuv);
            }
            }
        }
        }
        }

    }
}

void SortareTH(TH h) {
    size_t M = ('Z'-'A') + 1;

    for(int i=0; i<M; i++) {
        TLG head = h->v[i], prev;

        //Daca avem 0/1 elemente continuam
        if(head == NULL)
        continue;
        else if(head -> urm == NULL)
        continue;
    
        //Altfel parcurg lista si 
        //aplic bubblesort
        int sortat = 0;
        while(!sortat) {
        sortat = 1;
        prev=h->v[i];
        head=h->v[i]->urm;
        for(; head != NULL; head=head->urm, prev=prev->urm) {
            if(*(int *)(prev->info) > *(int *)(head->info)) { 
                int aux = *(int *)(prev->info);
                *(int *)(prev->info) = *(int *)(head->info);
                *(int *)(head->info) = aux;

                TLS temp = prev->sub;
                prev->sub = head->sub;
                head->sub = temp;
                sortat = 0;
            }
        }
        }
    }
    SortareTLS(h);
}

void freeTH(TH *h) {
    size_t M = ('Z'-'A') + 1;

    for(int i=0; i<M; i++) 
    for(TLG temp = (*h)->v[i]; temp != NULL; temp = temp -> urm) {
    // Eliberam sublistele

    TLS prev = temp->sub;
    if(prev -> urm == NULL) {
        free(prev->info);
        free(prev);
        continue;
    }

    for(TLS temp1=prev->urm; temp1!=NULL; temp1=temp1->urm, prev=prev->urm) {
        free(prev->info);
        free(prev);
    }

        free(prev->info);
        free(prev);
    }

    for(int i=0; i<M; i++) {
    // Eliberam listele
    TLG prev = (*h)->v[i];
    if(prev != NULL) {

    if(prev -> urm == NULL){ 
        free(prev->info);
        free(prev);
        continue;
    }

    for(TLG temp = prev->urm; temp != NULL; temp=temp->urm, prev=prev->urm) {
        free(prev->info);
        free(prev);
    }
    free(prev->info);
    free(prev);
    }
    }

    // Eliberam tabela hash
    free((*h)->v);
    free(*h);
}


int main(int argc, char *argv[]) {

    FILE *input = fopen(argv[1],"r");
    char line[MAX_LINE_SIZE], line_copy[MAX_LINE_SIZE];
    TH h = InitTH();
    char sep[] = " .,";

    // Verificam daca exista fisierul
    if(input == NULL) {
        freeTH(&h);
        printf("Nu exista fisierul \n");
        exit(0);
    }

    while(fgets(line,sizeof(line),input)) {

		// Scoatem newline adaugat de fgets
		if(line[strlen(line) - 1] == '\n')
        line[strlen(line) - 1] = '\0';
        strcpy(line_copy, line);

        // Spargem linia in cuvinte
		char *p = strtok(line, sep);
		if(strcmp(p,"insert") == 0) {
			p = strtok(NULL, sep);

            // Introducem toate cuvintele in lista
			while(p) {
                char aux[50]; strcpy(aux,p);
                InsertTH(aux,h,codHash(p));
				p = strtok(NULL, sep);
			}
		}
        else if(strcmp(p,"print") == 0) {
            int nr = 0,n;
            char *k,c;
            for(; p != NULL; p = strtok(NULL, sep), nr++);
            SortareTH(h);

            switch (nr)
            {
            case 1: // print
                PrintTH(h);
                break;
            case 2: // print n
                k = strtok(line_copy, sep);
                k = strtok(NULL, sep);
                n = (int) strtol(k, (char **)NULL, 10);

                PrintnTH(h,n);
                break;
            case 3: // print c n 
                k = strtok(line_copy, sep);
                k = strtok(NULL, sep);
                c = k[0];
                k = strtok(NULL, sep);
                n = (int) strtol(k, (char **)NULL, 10);

                PrintcnTH(h,c,n);
                break;
            default:
                break;
            }
        }
    }
    
    freeTH(&h);
    fclose(input);

    return 0;
}