//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodSecundar NodSecundar;
typedef struct NodPrincipal NodPrincipal;
typedef struct Metrou Metrou;

struct Metrou {
	int serie;
	int nrStatii;
	char* magistrala;
};


struct NodSecundar {
	NodPrincipal* nod;
	NodSecundar* next;
};

//nodul pt lista principala

struct NodPrincipal {
	Metrou info;
	NodPrincipal* next;
	NodSecundar* vecini;
};



//functie de creare metrou
Metrou creareMetrou(int serie, int nrStatii, const char* magistrala) {
	Metrou m;
	m.serie = serie;
	m.nrStatii = nrStatii;
	m.magistrala = (char*)malloc((strlen(magistrala) + 1) * sizeof(char));
	strcpy_s(m.magistrala, strlen(magistrala)+1, magistrala);

	return m;
}

//functie de inserare la inceput in lista principala

void inserarePrinciapala(NodPrincipal** cap, Metrou m)
{
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = m;
	nou->next = *cap;
	nou->vecini = NULL;
	*cap = nou;
}
//functie de cautare nod dupa serie

NodPrincipal* cautaNodDupaSerie(NodPrincipal* graf, int serie) {
	while (graf && graf->info.serie != serie) { graf = graf->next; }
	return graf;
}


//functie de inserare la final in lista secundara

NodSecundar* inserareSecundara(NodSecundar* cap, NodPrincipal* nod) {
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->next = NULL;
	nou->nod = nod;
	if (cap) {
		NodSecundar* p = cap;
		while (p->next) { p = p->next; }
		p->next = nou;
		return cap;


	}

	else {
		return nou;
	}

}

//functie de inserare muchie

void inserareMuchie(NodPrincipal* graf, int serieStart, int serieStop) {
	NodPrincipal* nodStart = cautaNodDupaSerie(graf, serieStart);
	NodPrincipal* nodStop = cautaNodDupaSerie(graf, serieStop);

	if (nodStart && nodStop) {
		nodStart->vecini = inserareSecundara(nodStart->vecini, nodStop);
		nodStop->vecini = inserareSecundara(nodStop->vecini, nodStart);
	}


}
//functie de dezalocare

void main() {
	NodPrincipal* graf=NULL;



	//functia trebuie apelata pt toate nodurile
	inserarePrincipala(&graf, creareMetrou(4,6, "M2"));
	inserarePrincipala(&graf, creareMetrou(3, 4, "M1"));
	inserarePrincipala(&graf, creareMetrou(2, 8, "M4"));
	inserarePrincipala(&graf, creareMetrou(1, 12, "M3"));
	inserarePrincipala(&graf, creareMetrou(0, 4, "M6"));
	

	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 1, 3);
	inserareMuchie(graf, 1, 4);
	inserareMuchie(graf, 2, 3);

}