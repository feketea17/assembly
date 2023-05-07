// SZGA_I_08Feladat_CMBWX8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/* 08. Feladat
Írjon egy programot, ami bekér egy tetszőleges számot ellenőrzötten 1 és 4999 között,
majd kiírja a számot római számként a képernyőre. */

#include <iostream>

using namespace std;

int main()
{
    int N;
    int countC, countX, countI;

    int saveesp;

    const char* beker = "Kérek egy DECIMÁLIS számot 1-4999 között!\n";      // printf

    const char* formati = "%d";     // scanf
    const char* hun = "Hun";        // setlocale
    const char* _pause = "pause";   // system pause

    const char* rom[13] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
    char testArray[50];
    int count[13] = { 0 };

    setlocale(LC_ALL, hun);


    // BEÁLLÍTÁSOK
    _asm
    {
        // setlocale beállítása
        push hun;
        push LC_ALL;
        call dword ptr setlocale;
        push beker;
        call dword ptr printf;


    input:
        lea eax, N;             // N címe eax
        push eax;               // verem tetejére
        push formati;           // formázó karakter
        call dword ptr scanf;   // input bekérése

        // ELLENŐRZÉS
        cmp N, 1;
        jl input;
        cmp N, 4999;
        jle tovább;
        jmp input;

    tovább:
    }

    /*
    _asm
    {
        push N;
        push formati;
        call dword ptr printf;
    }
    */

    // SZÁM KONVERTÁLÁSA
    _asm
    {
        // osztás (1000)
        mov eax, N;         // N -> eax
        mov ebx, 1000;      // 1000 -> ebx
        xor edx, edx;
        div ebx;            // osztás 1000-el
        mov N, edx;         // N = osztás maradéka
        lea ebx, count;
        mov[ebx], eax;      // count[0] = osztás hányadosa

        // osztás (100)
        mov eax, N;
        mov ebx, 100;
        xor edx, edx;
        div ebx;
        mov countC, eax;    // countC = osztás hányadosa
        mov N, edx;

        // osztás (10)
        mov eax, N;
        mov ebx, 10;
        xor edx, edx;
        div ebx;
        mov countX, eax;
        mov N, edx;

        // osztáls (1)
        mov eax, N;
        mov ebx, 1;
        xor edx, edx;
        div ebx;
        mov countI, eax;
    }

    // (100) SZÁMOLÁSA
    _asm
    {
        mov eax, countC;
        cmp eax, 4;
        jl C;       // countC < 4
        je CD;      // countC == 4
        jg DC;      // countC > 4

    // (100-300)
    C:
        lea ebx, count;
        mov eax, countC;
        mov[ebx + 16], eax;         // (C) = countC
        mov dword ptr[countC], 0;   // countC = 0
        jmp tizesek;                // kilép, (10) számolásra ugrás

    // (400)
    CD:
        lea ebx, count;
        mov dword ptr[ebx + 12], 1; // (CD) +1
        mov dword ptr[countC], 0;
        jmp tizesek;

    // (500-900)
    DC:
        cmp countC, 9;
        je CM;
        lea ebx, count;
        mov dword ptr[ebx + 8], 1;  // (V) +1
        sub countC, 5;
        mov eax, countC;
        mov[ebx + 16], eax;         // (C) = countC
        mov dword ptr[countC], 0;
        jmp tizesek;

    // (900)
    CM:
        lea ebx, count;
        mov dword ptr[ebx + 4], 1;  // (CM) +1
        mov dword ptr[countC], 0;
        jmp tizesek;
    }

    // (10) SZÁMOLÁSA
    _asm
    {
    tizesek:
        mov eax, countX;
        cmp eax, 4;
        jl X;       // countX < 4
        je XL;      // countX == 4
        jg LX;      // countX > 4

    // (10-30)
    X:
        lea ebx, count;
        mov eax, countX;
        mov[ebx + 32], eax;         // (X) = countX
        mov dword ptr[countX], 0;   // countX = 0
        jmp egyesek;                // kilép, (10) számolásra ugrás

    // (40)
    XL:
        lea ebx, count;
        mov dword ptr[ebx + 28], 1; // (XL) +1
        mov dword ptr[countX], 0;
        jmp egyesek;

    // (50-90)
    LX:
        cmp countX, 9;
        je XC;
        lea ebx, count;
        mov dword ptr[ebx + 24], 1;  // (L) +1
        sub countX, 5;
        mov eax, countX;
        mov[ebx + 32], eax;         // (X) = countX
        mov dword ptr[countX], 0;
        jmp egyesek;

    // (90)
    XC:
        lea ebx, count;
        mov dword ptr[ebx + 20], 1;  // (XC) +1
        mov dword ptr[countX], 0;
        jmp egyesek;
    }

    // (1) SZÁMOLÁSA
    _asm
    {
    egyesek:
        mov eax, countI;
        cmp eax, 4;
        jl I;       // countI < 4
        je IV;      // countI == 4
        jg VI;      // countI > 4

    // (1-3)
    I:
        lea ebx, count;
        mov eax, countI;
        mov[ebx + 48], eax;         // (I) = countI
        mov dword ptr[countI], 0;   // countX = 0
        jmp kész;                   // kilép

    // (4)
    IV:
        lea ebx, count;
        mov dword ptr[ebx + 44], 1; // (IV) +1
        mov dword ptr[countI], 0;
        jmp kész;

    // (5-9)
    VI:
        cmp countI, 9;
        je IX;
        lea ebx, count;
        mov dword ptr[ebx + 40], 1;  // (V) +1
        sub countI, 5;
        mov eax, countI;
        mov[ebx + 48], eax;          // (I) = countI
        mov dword ptr[countI], 0;
        jmp kész;

    // (9)
    IX :
        lea ebx, count;
        mov dword ptr[ebx + 36], 1;  // (IX) +1
        mov dword ptr[countI], 0;
        jmp kész;
    }

    _asm
    {
    kész:
    }

    /*
    // INDEXELÉS ELLENŐRZÉSE
    printf("\ncountC: %d\n", countC);
    printf("countX: %d\n", countX);
    printf("countI: %d\n\n", countI);
    printf("1000:\t %d\n", count[0]);
    printf("900:\t %d\n", count[1]);
    printf("500:\t %d\n", count[2]);
    printf("400:\t %d\n", count[3]);
    printf("100:\t %d\n", count[4]);
    printf("90:\t %d\n", count[5]);
    printf("50:\t %d\n", count[6]);
    printf("40:\t %d\n", count[7]);
    printf("10:\t %d\n", count[8]);
    printf("9:\t %d\n", count[9]);
    printf("5:\t %d\n", count[10]);
    printf("4:\t %d\n", count[11]);
    printf("1:\t %d\n", count[12]);
    */


    _asm
    {
        lea ebx, count;
        cmp dword ptr[ebx], 0;  //count array 0. elemének összehasonlítása 0-val
        je jump;                // ha count[0] = 0 akkor ugorjon előre

        
        mov ecx, dword ptr[eax];
        mov ebx, 77;            // ebx = 77 (ASCII "M")
        mul ebx;
        lea edx, testArray;
        add edx, ecx;
        mov byte ptr[edx]
        add edx, 1;
        mov byte ptr[edx], 'M'
        

        jump:
    }
    // kapott hiba: C2414 illegal number of operands





    // C++ kiíratás
    for (int i = 0; i < 13; i++) {
        if (count[i] > 0) {
            for (int j = 0; j < count[i]; j++) {
                cout << rom[i];
            }
        }
    }

    _asm
    {
        mov saveesp, esp;
    }

    return 0;
}
