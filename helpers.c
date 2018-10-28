#include <stdbool.h>

void concat(char [], char);
void bind(char[], char[], char);
void copy(char[], char[]);
void intToChar(int, char[]);
bool iguais(char[], char[]);

// Concatena a string 'b' na string 'a' 
void concat(char a[], char b){
	int i, j;
	for(i = 0; a[i] != '\0'; i++);

	a[i] = b;

	a[i+1] = '\0';
}

void copy(char destino[], char origem[]){
	int i = 0;
	while(origem[i] != 0){
		destino[i] = origem[i];
		i++;
	}
	destino[i] = '\0';
}

void intToChar(int n, char v[]){
	if(n < 10){
		v[0] = n + '0';
		v[1] = '\0';
	}else{
		v[0] = n / 10 + '0';
		v[1] = n % 10 + '0';
	}
}

bool iguais(char a[], char b[]){
	int c;
	for(c = 0; a[c] != 0; c++){
		if(a[c] != b[c])
			return false;
	}
	if(a[c] != b[c])
		return false;
	else
		return true;	
}