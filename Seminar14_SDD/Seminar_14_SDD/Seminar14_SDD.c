#define _CRT_SECURE_NO_WARNINGS

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

struct NodPrincipal {
	Metrou info;
	NodPrincipal* next;
	NodSecundar* vecini;
};

Metrou creareMetrou(int serie, int nrStatii, const char* magistrala) {
	Metrou m;
	m.serie = serie;
	m.nrStatii = nrStatii;
	m.magistrala = (char*)malloc((strlen(magistrala) + 1) * sizeof(char));
	strcpy(m.magistrala, magistrala);
	return m;
}

void inserarePrinciapala(NodPrincipal** cap, Metrou m)
{
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = m;
	nou->next = *cap;
	nou->vecini = NULL;
	*cap = nou;
}

NodPrincipal* cautaNodDupaSerie(NodPrincipal* graf, int serie) {
	while (graf && graf->info.serie != serie) { graf = graf->next; }
	return graf;
}

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

void inserareMuchie(NodPrincipal* graf, int serieStart, int serieStop) {
	NodPrincipal* nodStart = cautaNodDupaSerie(graf, serieStart);
	NodPrincipal* nodStop = cautaNodDupaSerie(graf, serieStop);

	if (nodStart && nodStop) {
		nodStart->vecini = inserareSecundara(nodStart->vecini, nodStop);
		nodStop->vecini = inserareSecundara(nodStop->vecini, nodStart);
	}
}

typedef struct NodCoada NodCoada;

struct NodCoada {
	int serie;
	NodCoada* next;
};

void inserareCoada(NodCoada** cap, int serie) {
	NodCoada* nodNou = (NodCoada*)malloc(sizeof(NodCoada));
	nodNou->serie = serie;
	nodNou->next = NULL;
	if (*cap) {
		NodCoada* aux = *cap;
		while (aux->next != NULL)
		{
			aux = aux->next;
		}
		aux->next = nodNou;
	}
	else
		*cap = nodNou;
}

int extragereCoada(NodCoada** cap)
{
	if (*cap) {
		int rezultat = (*cap)->serie;
		NodCoada* aux = *cap;
		*cap = aux->next;
		free(aux);
		return rezultat;
	}
	else
		return -1;
}

int getNumarNoduri(NodPrincipal* graf) {
	int nr = 0;
	while (graf) {
		nr++;
		graf = graf->next;
	}
	return nr;
}

void afisareMetrou(Metrou m) {
	printf("%d, numar statii:%d magistrala:%s\n", m.serie, m.nrStatii, m.magistrala);
}

void afisareParcurgereInLatime(NodPrincipal* graf, int serie) {

	NodCoada* coada = NULL;
	int nrNoduri = getNumarNoduri(graf);
	char* vizitate = (char*)malloc(nrNoduri);
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}
	inserareCoada(&coada, serie);
	vizitate[serie] = 1;
	while (coada) {
		int serieNoua = extragereCoada(&coada);
		NodPrincipal* nou = cautaNodDupaSerie(graf, serieNoua);
		afisareMetrou(nou->info);
		NodSecundar* temp = nou->vecini;
		while (temp) {
			if (vizitate[temp->nod->info.serie] == 0) {
				vizitate[temp->nod->info.serie] = 1;
				inserareCoada(&coada, temp->nod->info.serie);
			}
			temp = temp->next;
		}
	}
	free(vizitate);
}

void dezalocareGraf(NodPrincipal** graf) {
	while (*graf) {
		NodPrincipal* aux = *graf;
		free(aux->info.magistrala);
		while (aux->vecini) {
			NodSecundar* temp = aux->vecini;
			aux->vecini = temp->next;
			free(temp);
		}
		*graf = aux->next;
		free(aux);
	}
}

void main() {
	NodPrincipal* graf = NULL;

	inserarePrincipala(&graf, creareMetrou(4, 6, "M2"));
	inserarePrincipala(&graf, creareMetrou(3, 4, "M1"));
	inserarePrincipala(&graf, creareMetrou(2, 8, "M4"));
	inserarePrincipala(&graf, creareMetrou(1, 12, "M3"));
	inserarePrincipala(&graf, creareMetrou(0, 4, "M6"));

	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 1, 3);
	inserareMuchie(graf, 1, 4);
	inserareMuchie(graf, 2, 3);

	afisareParcurgereInLatime(graf, 0);

	dezalocareGraf(&graf);
}
