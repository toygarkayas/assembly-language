#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include "image_processing.cpp"

using namespace std;

void sagaDondur(short n, int resim);
void solaDondur(short n, int resim);

int main(void) {
	int M, N, Q, i, j, k;
	bool type;
	int efile, islem;
	char resimadi[100], sonek[10];
	printf("Toygar KAYAS Numara:16011080\n");
	do {
		printf("Islem yapilacak resmin yolunu (path) giriniz:\n-> ");
		scanf("%s", &resimadi);
		system("CLS");
		efile = readImageHeader(resimadi, N, M, Q, type);
	} while (efile > 1);
	printf("%s\n", resimadi);
	int** resim = resimOku(resimadi);

	short *resimdizi;
	resimdizi = (short*) malloc(N*M * sizeof(short));

	for (i = 0; i < N; i++) 
		for (j = 0; j < M; j++) 
			resimdizi[i*N + j] = (short) resim[i][j];

	int resimadres = (int) resimdizi;

	do {
		system("CLS");
		printf("\t     ISLEMLER\n");
		printf("------------------------------------\n");
		printf("1)  Resmi saga dondur\n");
		printf("2)  Resmi sola dondur\n");
		printf("0)  Cikis\n\n");
		printf("\"%s\" yolundaki resim icin yapilacak islemi seciniz\n-> ", resimadi);
		scanf("%d", &islem);
	} while (islem > 2 || islem < 0);

	switch (islem) {
		case 0:
			exit(0);
		case 1:
			sagaDondur(N, resimadres);
			strcpy(sonek, "_sag.pgm");
			break;
		case 2:
			solaDondur(N , resimadres);
			strcpy(sonek, "_sol.pgm");
			break;
		default:
			strcpy(sonek, "_orj.pgm");
			break;
	}

	for (k = 0; k < N * M; k++) {
		j = k % N;
		i = k / N;
		resim[i][j] = (int)resimdizi[k];
	}
	
	string::size_type pos = string(resimadi).find_last_of(".");
	resimadi[pos] = '\0';
	strcat(resimadi, sonek);
	resimYaz(resimadi, resim, N, M, Q);
	printf("\nIslem basariyla tamamlandi :)\n\"%s\" yolunda resim olusturuldu.\n\n", resimadi);
	system("PAUSE");
	return 0;
}

void sagaDondur(short n, int resim) {

	int i = 0, j = 0;
	int n2 =(int) n;
	__asm {
		MOV CX, n
		MOV EDI, resim
		XOR EAX,EAX
	L2: PUSH CX
		MOV CX, n
		MOV EAX,i
		MOV j,EAX
		SHR EAX,1
		SUB ECX,EAX
    L1: XOR EDX,EDX
		
		MOV EAX,i
		MUL n2
		ADD EAX,j
		MOV ESI,EDI
		ADD ESI,EAX
		
		XOR EDX,EDX

		MOV EAX,j
		MUL n2
		ADD EAX,i
		MOV EBX,EDI
		ADD EBX,EAX

		MOV AX,WORD PTR[ESI]
		XCHG AX,WORD PTR[EBX]
		XCHG AX,WORD PTR[ESI]

		ADD j,2
		LOOP L1
		POP CX
		ADD i,2
		LOOP L2	
	///////////
		MOV i,0
	    MOV CX, n
		XOR EAX, EAX
   L4 : PUSH CX
		MOV CX, n
		SHR CX,1
		MOV j, 0

   L3 : XOR EDX, EDX

		MOV EAX, i
		MUL n2
		ADD EAX, j
		MOV ESI, EDI
		ADD ESI, EAX

		XOR EDX, EDX

		MOV EAX, i
		MUL n2
		SHL n2,1
		ADD EAX, n2
		SHR n2,1
		SUB EAX, j		
		SUB EAX,2
		MOV EBX, EDI
		ADD EBX, EAX

		MOV AX, WORD PTR[ESI]
		XCHG AX, WORD PTR[EBX]
		XCHG AX, WORD PTR[ESI]

		ADD j, 2
		LOOP L3
		POP CX
		ADD i, 2
		LOOP L4
	
	}
	
}

void solaDondur(short n, int resim) {
	
	int i = 0, j = 0;
	int n2 = (int)n;
	__asm {
		MOV CX, n
		MOV EDI, resim
   L2 : PUSH CX
		MOV CX, n
		MOV EAX, i
		MOV j, EAX
		SHR EAX, 1
		SUB ECX, EAX
		L1 : XOR EDX, EDX

		MOV EAX, i
		MUL n2
		ADD EAX, j
		MOV ESI, EDI
		ADD ESI, EAX

		XOR EDX, EDX

		MOV EAX, j
		MUL n2
		ADD EAX, i
		MOV EBX, EDI
		ADD EBX, EAX

		MOV AX, WORD PTR[ESI]
		XCHG AX, WORD PTR[EBX]
		XCHG AX, WORD PTR[ESI]



		ADD j, 2
		LOOP L1
		POP CX
		ADD i, 2
		LOOP L2
		///////////
		MOV i, 0
		MOV CX, n
		SHR CX,1
		XOR EAX, EAX
L4 :    PUSH CX
		MOV CX, n
		MOV j, 0

L3 :    XOR EDX, EDX

		MOV EAX, i
		MUL n2
		ADD EAX, j
		MOV ESI, EDI
		ADD ESI, EAX

		XOR EDX, EDX

		SHL n2,1
		MOV EAX,n2
		SHR n2,1
		SUB EAX, i
		SUB EAX,2
		MUL n2
		ADD EAX,j

		MOV EBX, EDI
		ADD EBX, EAX

		MOV AX, WORD PTR[ESI]
		XCHG AX, WORD PTR[EBX]
		XCHG AX, WORD PTR[ESI]

		ADD j, 2
		LOOP L3
		POP CX
		ADD i, 2
		LOOP L4
	}

}

