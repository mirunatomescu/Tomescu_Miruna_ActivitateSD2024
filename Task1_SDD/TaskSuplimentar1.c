#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Vehicul { // Tomescu Miruna -> T si M
    int cod;
    char* nume;
    int anProductie;
    float pret;
};

struct Vehicul* citesteVehicul(struct Vehicul* v) {

    printf("Introduceti codul vehiculului:");
    scanf("%d", &v->cod);

    v->nume = (char*)malloc(100 * sizeof(char));
    printf("Introduceti numele vehiculului:");
    scanf("%s", v->nume);

    printf("Introduceti anul de productie al vehiculului:");
    scanf("%d", &v->anProductie);

    printf("Introduceti pretul vehiculului:");
    scanf("%f", &v->pret);

    return v;
}

float discountVanzare(struct Vehicul* v) {

    float discount = 0.0;

    if (v->anProductie >= 2000) {
        v->pret = v->pret - (v->pret * 0.1);
        discount = v->pret * 0.1;
    }
    else {
        v->pret = v->pret - (v->pret * 0.2);
        discount = v->pret * 0.2;
    }

    return discount;

}

void modificaAnProductie(struct Vehicul* v, int noulAnProductie) {
    v->anProductie = noulAnProductie;
}

void afiseazaVehicul(struct Vehicul v) {
    printf("Cod: %d\n", v.cod);
    printf("Nume: %s\n", v.nume);
    printf("An de productie: %d\n", v.anProductie);
    printf("Pret: %.2f\n", v.pret);
}

int main() {

    struct Vehicul v;
    citesteVehicul(&v);

    printf("\nInformatii vehicul:\n");
    afiseazaVehicul(v);


    modificaAnProductie(&v, 2022);

    printf("\nInformatii despre vehicul:\n");
    afiseazaVehicul(v);
    printf("Discountul aplicat vehiculului:%.2f", discountVanzare(&v));

    printf("\nInformatii despre vehicul dupa aplicare discount:\n");
    afiseazaVehicul(v);


    free(v.nume);

    return 0;
}
