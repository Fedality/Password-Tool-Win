
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


// cc
#define red "\x1b[31m"
#define cyana "\x1b[36m"
#define yel "\x1b[33m"

// declares
void ascii();
void vPass(const char* pass);
void hPassGhandle();
void hPassCheck();
void rndPassGen(int len);
void safeInput();


void safeInput() {

	int c; 
	while ((c = getchar()) != '\n' && c != EOF) {
	}
}


// CLI

void ascii() {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);


	printf(" ______  __  __  ______      __     __  ______  ______  __      _____    \n");
	printf("/\\__  _\\/\\ \\_\\ \\/\\  ___\\    /\\ \\  _ \\ \\/\\  __ \\/\\  == \\/\\ \\    /\\  __-.  \n");
	printf("\\/_/\\ \\/\\ \\  __ \\ \\  __\\    \\ \\ \\/ \".\\ \\ \\ \\/\\ \\ \\  __<\\ \\ \\___\\ \\ \\/\\ \\ \n");
	printf("   \\ \\_\\ \\ \\_\\ \\_\\ \\_____\\   \\ \\__/\"~\\_\\ \\_____\\ \\_\\ \\_\\ \\_____\\ \\____- \n");
	printf("    \\/_/  \\/_/\\/_/\\/_____/    \\/_/   \\/_/\\/_____/\\/_/ /_/\\/_____/\\/____/ \n");
	printf("                                                                         \n");
	printf(" __  ______      __  __  ______  __  __  ______  ______                  \n");
	printf("/\\ \\/\\  ___\\    /\\ \\_\\ \\/\\  __ \\/\\ \\/\\ \\/\\  == \\/\\  ___\\                 \n");
	printf("\\ \ \ \ ___  \   \\ \\____ \\ \\ \\/\\ \\ \\ \\_\\ \\ \\  __<\\ \\___  \                \n");
	printf(" \\ \\_\\/\\_____\\   \\/\\_____\\ \\_____\\ \\_____\\ \\_\\ \\_\\/\\_____\\               \n");
	printf("  \\/_/\\/_____/    \\/_____/\\/_____/\\/_____/\\/_/ /_/\\/_____/               \n");
	printf("                                                                         \n");


}

//BOOL spChar(char c) {
//	return !(isalpha(c) || isdigit(c));
//}
//
//BOOL spValP(const char* pass) {
//	
//	int len = strlen(pass);
//
//	if (len <= 10)
//	{
//		printf(red"Password must be at least 10 characters long.\n");
//		return FALSE;
//	}
//
//	BOOL has_lower = FALSE;
//	BOOL has_upper = FALSE;
//	BOOL has_digit = FALSE;
//	BOOL has_special = FALSE;
//}

void vPass(const char* pass) {

	int len = strlen(pass);
	int score = 0;

	bool hasLower = false;
	bool hasUpper = false;
	bool hasDigit = false;
	bool hasSpecial = false;

	for (int i = 0; i < len; i++) {
		if (islower(pass[i])) {
			hasLower = true;
		}
		else if (isupper(pass[i])) {
			hasUpper = true;
		}
		else if (isdigit(pass[i])) {
			hasDigit = true;
		}
		else if (ispunct(pass[i])) {
			hasSpecial = true;
		}
	}

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	printf(cyana "\n-- Password Strenght --\n");

	if (len >= 16) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf(" [S+] Very Secure!\n");
		score += 2;
	}
	else if (len >= 12) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf(" [S] Secure\n");
		score += 1;
	}
	else if (len >= 8) {
		//SetConsoleTextAttribute(hConsole, FOREGROUND_YELLOW | FOREGROUND_INTENSITY);
		printf(yel" [M] Medium\n");
	}
	else {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf(" [W] Weak\n");
	}

	if (hasLower) { score++; SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("[+] Contains lowercase letters (a-z)\n"); }
	else { SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); printf("[-] Missing lowercase letters (a-z)\n"); }

	if (hasUpper) { score++; SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("[+] Contains uppercase letters (A-Z)\n"); }
	else { SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); printf("[-] Missing uppercase letters (A-Z)\n"); }

	if (hasDigit) { score++; SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("[+] Contains numbers (0-9)\n"); }
	else { SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); printf("[-] Missing numbers (0-9)\n"); }

	if (hasSpecial) { score++; SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); printf("[+] Contains special characters (!@#$..)\n"); }
	else { SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); printf("[-] Missing special characters (!@#$..)\n"); }

	printf("\n--- Verdict ---\n");
	if (score >= 5) { // Requires good length and most character types
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf("Strength: STRONG\n");
	}
	else if (score >= 3) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf("Strength: MODERATE. Consider adding more character types or length.\n");
	}
	else {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf("Strength: WEAK. Could be easily guessed.\n");
	}
}


void hPassGhandle() {

	int len = 0;
	int inputStatus = 0;

	while (true) {
		printf("\nEnter a desired pass lenghth: ");
		inputStatus = scanf_s("%d", &len);

		if (inputStatus != 1) {
			printf("Invalid input. Please enter a number.\n");
			safeInput();
			continue;
		}

		if (len < 10) {
			printf("Length must be above 10!\n");
		}
		else {
			break;
		}
	}

	safeInput();
	rndPassGen(len);
}


void hPassCheck() {
	char passBaf[256];

	printf("\nEnter the password for check ->  ");
	fgets(passBaf, sizeof(passBaf), stdin);
	passBaf[strcspn(passBaf, "\n")] = '\0';

	vPass(passBaf);
}

void rndPassGen(int len) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()";
	char charsetS[] = "@!=<>?,_-:';[]|}{~";
	char* pass = NULL;

	pass = malloc(sizeof(char) * (len + 1));
	if (pass == NULL) {
		printf("memory failed\n");
		return;
	}

	srand(time(0));

	for (int i = 0; i < len; i++) {
		if (i % 2 == 0) {
			pass[i] = charset[rand() % (sizeof(charset) - 1)];
		}
		else {
			pass[i] = charsetS[rand() % (sizeof(charsetS) - 1)];
		}
	}

	pass[len] = '\0';

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("Generated password -> ");

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	printf("%s\n", pass);

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	free(pass);
}

int main() {

	/*ascii();
	for (;;) {
		int len = 0;
		int inputStatus = 0;
		while (1) {
			printf("\nPlease enter the desired password length (10 or more): ");
			inputStatus = scanf_s("%d", &len);

			if (inputStatus != 1) { 
				printf("Invalid input. Please enter a number.\n");
				safeInput();
				continue;
			}

			if (len < 10) {
				printf("Length must be 10 or greater. Please try again.\n");
			}
			else {
				break;
			}
		}

		safeInput();
		rndPassGen(len);

		char choice;
		printf("\nGenerate another password? (y/n): ");
		scanf_s(" %c", &choice);
		safeInput();

		if (choice != 'y' && choice != 'Y') {
			break;
		}
	}
	printf("\nGoodbye! Stay safe...\n");
	getchar();
	return 0;
	*/

	int choice = 0;
	ascii();
	while (true) {

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		printf("\n-- Password Generator and Checker --\n");
		printf("1. Generate a random password\n");
		printf("2. Password strength check\n");
		printf("3. Exit\n");

		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf("Enter your choice ->  ");

		if (scanf_s("%d", &choice) != 1) {
			printf(red"Invalid input. Please enter a number.\n");
			safeInput();
			continue;
		}

		safeInput();
		switch (choice) {
		case 1:
			hPassGhandle();
			break;
		case 2:
			hPassCheck();
			break;
		case 3:
			printf("\nGoodbye! Stay safe...\n");
			getchar();
			return 0;
		default:
			printf("Invalid choice. Please select 1, 2, or 3.\n");
			break;
		}
	}
}