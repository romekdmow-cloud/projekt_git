#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_TXT 100

typedef struct {
    char nazwa[MAX_TXT];
    char swiat[MAX_TXT];
    int chaos;
    char opis[MAX_TXT];
    int stabilnosc;
} Przedmiot;

Przedmiot baza[MAX_ITEMS];
int ilosc = 0;

void wczytajTekst(char* cel, int rozmiar) {
    if (fgets(cel, rozmiar, stdin) != NULL) {
        cel[strcspn(cel, "\n")] = 0;
    }
}

const char* nazwaStabilnosci(int s) {
    if (s == 0) return "Stabilny";
    if (s == 1) return "Chwiejny";
    if (s == 2) return "Niestabilny";
    return "Nieklasyfikowany";
}

void dodaj() {
    if (ilosc >= MAX_ITEMS) {
        printf("Baza pelna!\n");
        return;
    }  
    printf("\n  DODAWANIE  \n");
    char tempNazwa[MAX_TXT];
    printf("Nazwa: ");
    wczytajTekst(tempNazwa, MAX_TXT);
    for (int i = 0; i < ilosc; i++) {
        if (strcmp(baza[i].nazwa, tempNazwa) == 0) {
            printf("Blad! Taka nazwa juz istnieje!\n");
            return;
        }
    }
    strcpy(baza[ilosc].nazwa, tempNazwa);
    printf("Swiat pochodzenia: ");
    wczytajTekst(baza[ilosc].swiat, MAX_TXT);
    printf("Poziom chaosu (0-10): ");
    scanf("%d", &baza[ilosc].chaos);
    getchar();
    printf("Opis efektu: ");
    wczytajTekst(baza[ilosc].opis, MAX_TXT);
    printf("Stabilnosc (0-Stab, 1-Chwiej, 2-Niestab, 3-Inne): ");
    scanf("%d", &baza[ilosc].stabilnosc);
    getchar();
    ilosc++;
    printf("Dodano!\n");
}

void wyswietl() {
    printf("\n--- LISTA PRZEDMIOTOW (%d) ---\n", ilosc);
    for (int i = 0; i < ilosc; i++) {
        printf("%d. %s | Swiat: %s | Chaos: %d | Status: %s\n",
            i + 1,
            baza[i].nazwa,
            baza[i].swiat,
            baza[i].chaos,
            nazwaStabilnosci(baza[i].stabilnosc)
        );
        printf("   Opis: %s\n", baza[i].opis);
    }
}
void usun() {
    char cel[MAX_TXT];
    printf("Podaj NAZWE do usuniecia: ");
    wczytajTekst(cel, MAX_TXT);
    int index = -1;
    for (int i = 0; i < ilosc; i++) {
        if (strcmp(baza[i].nazwa, cel) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Nie znaleziono!\n");
        return;
    }

    if (baza[index].stabilnosc == 2) {
        printf("BLAD: Nie mozna usunac przedmiotu NIESTABILNEGO! Grozi wybuchem!\n");
        return;
    }
    for (int i = index; i < ilosc - 1; i++) {
        baza[i] = baza[i + 1];
    }
    ilosc--;
    printf("Usunieto.\n");
}
void edytuj() {
    char cel[MAX_TXT];
    printf("Podaj NAZWE do edycji: ");
    wczytajTekst(cel, MAX_TXT);

    for (int i = 0; i < ilosc; i++) {
        if (strcmp(baza[i].nazwa, cel) == 0) {
            printf("Nowy poziom chaosu: ");
            scanf("%d", &baza[i].chaos);
            printf("Nowa stabilnosc (0-3): ");
            scanf("%d", &baza[i].stabilnosc);
            getchar();
            printf("Zaktualizowano!\n");
            return;
        }
    }
    printf("Nie znaleziono.\n");
}
void sortuj() {
    for (int i = 0; i < ilosc - 1; i++) {
        for (int j = 0; j < ilosc - 1; j++) {
            if (strcmp(baza[j].nazwa, baza[j + 1].nazwa) > 0) {
                Przedmiot temp = baza[j];
                baza[j] = baza[j + 1];
                baza[j + 1] = temp;
            }
        }
    }
    printf("Posortowano alfabetycznie!\n");
}
void zapisz() {
    FILE* f = fopen("baza.txt", "w");
    if (f == NULL) return;
    fprintf(f, "%d\n", ilosc);
    
    for (int i = 0; i < ilosc; i++) {
        fprintf(f, "%s\n%s\n%d\n%s\n%d\n",
            baza[i].nazwa, baza[i].swiat, baza[i].chaos,
            baza[i].opis, baza[i].stabilnosc);
    }
    fclose(f);
    printf("Zapisano do pliku!\n");
}
void wczytaj() {
    FILE* f = fopen("baza.txt", "r");
    if (f == NULL) return;

    if (fscanf(f, "%d\n", &ilosc) != 1) {
        fclose(f);
        return;
    } 
    for (int i = 0; i < ilosc; i++) {
        fgets(baza[i].nazwa, MAX_TXT, f);
        baza[i].nazwa[strcspn(baza[i].nazwa, "\n")] = 0;

        fgets(baza[i].swiat, MAX_TXT, f);
        baza[i].swiat[strcspn(baza[i].swiat, "\n")] = 0;

        fscanf(f, "%d\n", &baza[i].chaos);

        fgets(baza[i].opis, MAX_TXT, f);
        baza[i].opis[strcspn(baza[i].opis, "\n")] = 0;

        fscanf(f, "%d\n", &baza[i].stabilnosc);
    }
    fclose(f);
    printf("Wczytano dane z pliku.\n");
}
int main() {
    wczytaj();
    
    int wybor = -1;
    while (wybor != 0) {
        printf("\n=== BIURO ZAGUBIONYCH RZECZY ===\n");
        printf("1. Dodaj  2. Wyswietl  3. Usun\n");
        printf("4. Edytuj 5. Sortuj    0. Wyjdz\n");
        printf("Wybor: ");
        if (scanf("%d", &wybor) != 1) {
            while(getchar() != '\n');
            continue;
        }
        getchar();

        switch(wybor) {
            case 1: dodaj(); break;
            case 2: wyswietl(); break;
            case 3: usun(); break;
            case 4: edytuj(); break;
            case 5: sortuj(); break;
            case 0: zapisz(); break;
            default: printf("Zla opcja!\n");
        }
    }
    return 0;
}