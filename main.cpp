/*CALINA CRISTIAN FLORIN 313CA*/
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

using namespace std;

int main(){
	srand(time(NULL));
	int N, M;
	//Pentru before si after:
	//Daca am 224*2 , before va fi 224 si after 2.
	string before, after;
	Trie *t = new Trie(0);
	string word, number, result;
	int wcount;
	ifstream f ("date.in");
	ofstream g ("date.out");
	f >> N;
	for (int i = 1; i <= N; i++){
		//citesc word, nr de aparitii si il adaug in trie.
		f >> word;
		f >> wcount;
		t->addWord(word,wcount);
	}
	f >> M;
	for (int i = 1; i <= M; i++){
		//initializez before si after cu "" (nimic).
		before = "";
		after = "";
		f >> number;
		//citesc numarul ca string(e prea mare si pt long long)
		char * aux = strdup(number.c_str());
		//Iau un aux de tip char* pentru ca nu pot folosi strtok pe string
		before = strtok(aux,"*");
		//Daca dimensiunea stringului e mai mare ca before => am '*'
		if (number.size() > before.size() ) {
			//After ia tot ce urmeaza dupa '*'
			after = &number[before.size() + 1];
		}
		//returnez in result stringul intors de searchWord
		result = t->searchWord(after,before);
		//il scriu in fisierul "date.out".
		g << result << "\n";
		//eliberez aux folosind free (delete creeaza probleme)
		free(aux);
	}
	delete t;
	f.close();
	g.close();
	return 0;
}
