#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Autovehicul { // Tomescu Miruna -> T si M
    int id;
    char* nume;
    int anProductie;
    float cost;
};

void citesteAutovehicul(struct Autovehicul* a) {
    printf("Introduceti ID-ul autovehiculului:");
    scanf("%d", &a->id);

    a->nume = (char*)malloc(100 * sizeof(char));
    printf("Introduceti numele autovehiculului:");
    scanf("%s", a->nume);

    printf("Introduceti anul de productie al autovehiculului:");
    scanf("%d", &a->anProductie);

    printf("Introduceti costul autovehiculului:");
    scanf("%f", &a->cost);
}

float calculeazaDiscount(struct Autovehicul* a) {
    float discount = 0.0;

    if (a->anProductie >= 2005) {
        discount = a->cost * 0.1;
        a->cost -= discount;
    }
    else {
        discount = a->cost * 0.2;
        a->cost -= discount;
    }

    return discount;
}

void modificaAnProductie(struct Autovehicul* a, int noulAnProductie) {
    a->anProductie = noulAnProductie;
}

void afiseazaAutovehicul(struct Autovehicul a) {
    printf("ID: %d\n", a.id);
    printf("Nume: %s\n", a.nume);
    printf("An de productie: %d\n", a.anProductie);
    printf("Cost: %.2f\n", a.cost);
}

struct Autovehicul* filtreazaAutovehiculeDupa2005(struct Autovehicul* autovehicule, int numarAutovehicule, int* numarAutovehiculeFiltrate) {
    int contor = 0;
    for (int i = 0; i < numarAutovehicule; i++) {
        if (autovehicule[i].anProductie >= 2005) {
            contor++;
        }
    }

    struct Autovehicul* autovehiculeFiltrate = (struct Autovehicul*)malloc(contor * sizeof(struct Autovehicul));
    int index = 0;
    for (int i = 0; i < numarAutovehicule; i++) {
        if (autovehicule[i].anProductie >= 2005) {
            autovehiculeFiltrate[index] = autovehicule[i];
            index++;
        }
    }

    *numarAutovehiculeFiltrate = contor;
    return autovehiculeFiltrate;
}

struct Autovehicul* mutaAutovehiculeSub2005(struct Autovehicul* autovehicule, int numarAutovehicule, int* numarAutovehiculeMutate) {
    int contor = 0;
    for (int i = 0; i < numarAutovehicule; i++) {
        if (autovehicule[i].anProductie < 2005) {
            contor++;
        }
    }

    struct Autovehicul* autovehiculeMutate = (struct Autovehicul*)malloc(contor * sizeof(struct Autovehicul));
    int index = 0;
    for (int i = 0; i < numarAutovehicule; i++) {
        if (autovehicule[i].anProductie < 2005) {
            autovehiculeMutate[index] = autovehicule[i];
            index++;
        }
    }

    *numarAutovehiculeMutate = contor;
    return autovehiculeMutate;
}

void elibereazaMemorie(struct Autovehicul* a) {
    free(a->nume);
    free(a);
}

struct Autovehicul* concateneazaAutovehicule(struct Autovehicul* autovehicule1, int dimensiune1, struct Autovehicul* autovehicule2, int dimensiune2) {
    struct Autovehicul* autovehiculeConcat = (struct Autovehicul*)malloc((dimensiune1 + dimensiune2) * sizeof(struct Autovehicul));
    int index = 0;

    for (int i = 0; i < dimensiune1; i++) {
        autovehiculeConcat[index] = autovehicule1[i];
        index++;
    }

    for (int i = 0; i < dimensiune2; i++) {
        autovehiculeConcat[index] = autovehicule2[i];
        index++;
    }

    return autovehiculeConcat;
}

void afiseazaAutovehicule(struct Autovehicul* autovehicule, int dimensiune) {
    for (int i = 0; i < dimensiune; i++) {
        afiseazaAutovehicul(autovehicule[i]);
    }
}

int main() {
    int numarAutovehicule = 3;

    struct Autovehicul* autovehicule = (struct Autovehicul*)malloc(numarAutovehicule * sizeof(struct Autovehicul));

    for (int i = 0; i < numarAutovehicule; i++) {
        printf("Introduceti informatii despre autovehiculul %d:\n", i + 1);
        citesteAutovehicul(&autovehicule[i]);
    }

    for (int i = 0; i < numarAutovehicule; i++) {
        printf("\nInformatii autovehicul %d:\n", i + 1);
        afiseazaAutovehicul(autovehicule[i]);
        printf("Discountul aplicat: %.2f\n", calculeazaDiscount(&autovehicule[i]));
    }

    int numarAutovehiculeDupa2005 = 0;
    struct Autovehicul* autovehiculeDupa2005 = filtreazaAutovehiculeDupa2005(autovehicule, numarAutovehicule, &numarAutovehiculeDupa2005);

    free(autovehiculeDupa2005);

    int numarAutovehiculeSub2005 = 0;
    struct Autovehicul* autovehiculeSub2005 = mutaAutovehiculeSub2005(autovehicule, numarAutovehicule, &numarAutovehiculeSub2005);

    free(autovehiculeSub2005);

    struct Autovehicul* autovehicule1 = (struct Autovehicul*)malloc(numarAutovehicule * sizeof(struct Autovehicul));
    struct Autovehicul* autovehicule2 = (struct Autovehicul*)malloc(numarAutovehicule * sizeof(struct Autovehicul));

    for (int i = 0; i < numarAutovehicule; i++) {
        printf("Introduceti informatii despre autovehiculul %d din setul 1:\n", i + 1);
        citesteAutovehicul(&autovehicule1[i]);
    }

    for (int i = 0; i < numarAutovehicule; i++) {
        printf("Introduceti informatii despre autovehiculul %d din setul 2:\n", i + 1);
        citesteAutovehicul(&autovehicule2[i]);
    }

    struct Autovehicul* autovehiculeConcatenate = concateneazaAutovehicule(autovehicule1, numarAutovehicule, autovehicule2, numarAutovehicule);

    afiseazaAutovehicule(autovehiculeConcatenate, numarAutovehicule * 2);

    free(autovehicule1);
    free(autovehicule2);
    free(autovehiculeConcatenate);

    return 0;
}
