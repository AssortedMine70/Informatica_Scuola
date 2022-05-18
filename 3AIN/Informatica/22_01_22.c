#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main() {
	// Es 2
	char name[20], surname[20];
	printf("Inserire Nome: ");
	scanf("%s", name);
	printf("Inserire Cognome: ");
	scanf("%s", surname);

	name[0] = toupper(name[0]);
	surname[0] = toupper(surname[0]);
	printf("\nNome e Cognome: %s %s\n", name, surname);
	
	// Es 3
	size_t n = strlen(name);
	for(size_t i = 0; i<n/2; ++i) {
		char temp = name[n-i-1];
		name[n-1-i] = name[i];
		name[i] = temp;
	}
	printf("Nome Inverso: %s\n", name);
	
	// Es 5
	int x;
	char num[20];
	printf("\n\nInserire un numero: ");
	scanf("%i", &x);
	switch((x/10)%10) {
		case 0:
			strcat(num, "cento");
			break;
		case 1:
			switch(x%10) {
				case 0:
					strcat(num, "dieci");
					break;
				case 1:
					strcat(num, "undici");
					break;
				case 2:
					strcat(num, "dodici");
					break;
				case 3:
					strcat(num, "tredici");
					break;
				case 4:
					strcat(num, "quattordici");
					break;
				case 5:
					strcat(num, "quindici");
					break;
				case 6:
					strcat(num, "sedici");
					break;
				case 7:
					strcat(num, "diciasette");
					break;
				case 8:
					strcat(num, "diciotto");
					break;
				case 9:
					strcat(num, "diciannove");
					break;
			}
			break;
		case 2:
			strcat(num, x%10 == 1 || x%10 == 8 ? "vent" : "venti");
			break;
		case 3:
			strcat(num, x%10 == 1 || x%10 == 8 ? "trent" : "trenta");
			break;
		case 4:
			strcat(num, x%10 == 1 || x%10 == 8 ? "quarant" : "quaranta");
			break;
		case 5:
			strcat(num, x%10 == 1 || x%10 == 8 ? "cinquant" : "cinquanta");
			break;
		case 6:
			strcat(num, x%10 == 1 || x%10 == 8 ? "sessant" : "sessanta");
			break;
		case 7:
			strcat(num, x%10 == 1 || x%10 == 8 ? "settant" : "settanta");
			break;
		case 8:
			strcat(num, x%10 == 1 || x%10 == 8 ? "ottant" : "ottanta");
			break;
		case 9:
			strcat(num, x%10 == 1 || x%10 == 8 ? "novant" : "novanta");
			break;
	}
	if(((x/10)%10)!=1)
		switch(x%10) {
			case 0:
				break;
			case 1:
				strcat(num, "uno");
				break;
			case 2:
				strcat(num, "due");
				break;
			case 3:
				strcat(num, "tre");
				break;
			case 4:
				strcat(num, "quattro");
				break;
			case 5:
				strcat(num, "cinque");
				break;
			case 6:
				strcat(num, "sei");
				break;
			case 7:
				strcat(num, "sette");
				break;
			case 8:
				strcat(num, "otto");
				break;
			case 9:
				strcat(num, "nove");
				break;
			
		}
	printf("Numero in lettere: %s\n\n", num);
	
	return 0;
}
