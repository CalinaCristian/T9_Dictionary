/*CALINA CRISTIAN FLORIN 313CA*/
#include "treap.h"

using namespace std;

class Trie {
private:
	int digit;
	Treap< pair<int,string> > *words;
	Trie *children[8];
public:
	//Constructorul
	Trie(int x) {
		digit = x; //numarul nodului
		words = new Treap< pair<int,string> >;
		for (int i = 0; i <= 7; i++){
			children[i] = NULL; //initializez cele
			//8 noduri(cifrele tastaturii) cu NULL
		}
	}
	//Destructorul
	~Trie(){
		delete words; //Sterg words
		for (int i = 0; i <= 7; i++){
			delete children[i]; //sterg cele 8 noduri
		}
	}
	//Adaug cuvant in Treapul din Trie
	void addWord (string& word, int wcount){
		//current retine pozitia curenta in trie
		Trie* current = this;
		//creez o cheie cu elementele cuvant si numarul de aparitii
		std::pair<int,string> key;
		key.first = wcount;
		key.second= word;
		//nr retine tasta corespunzatoare literei
		int nr;
		for (int i = 0; i < (int) word.size() ; i++){
			nr = convert(word[i]);
			//daca nu am nod pentru urmatoarea cifra o creez
			if (current->children[nr-2] == NULL) {
				current->children[nr-2] = new Trie (nr);
			}
			//ma duc pe nodul urmatoarei cifre
			current = current->children[nr-2];
		}
		//adaug pe nodul ultimei cifre a numarului cheia
		current->words->insert(current->words,key,rand()%1000);
	}
	//Functie ce converteste literele din T9 in cifre alte tastaturii
	int convert (char letter){
		switch (letter) {
			case 'a':
				return 2;
			case 'b':
				return 2;
			case 'c':
				return 2;
			case 'd':
				return 3;
			case 'e':
				return 3;
			case 'f':
				return 3;
			case 'g':
				return 4;
			case 'h':
				return 4;
			case 'i':
				return 4;
			case 'j':
				return 5;
			case 'k':
				return 5;
			case 'l':
				return 5;
			case 'm':
				return 6;
			case 'n':
				return 6;
			case 'o':
				return 6;
			case 'p':
				return 7;
			case 'q':
				return 7;
			case 'r':
				return 7;
			case 's':
				return 7;
			case 't':
				return 8;
			case 'u':
				return 8;
			case 'v':
				return 8;
			case 'w':
				return 9;
			case 'x':
				return 9;
			case 'y':
				return 9;
			case 'z':
				return 9;
		}
		return 0;
	}
	//Cauta cuvantul in functie de numerele din tastatura T9
	string searchWord (string& after, string& before){
		Trie *current = this;
		//Un pair ce retine numarul de aparitii si cuvantul cautat
		std::pair<int,string> result;
		int requested=0;
		for (int i=0; i < (int) before.size() ; i++){
			//ma duc pe nodul urmatoarei cifre (cum ascii incepe de la 48
			//('0') , scad elementul '0' pentru a face conversia in int
			current = current->children[before[i]-'0'-2];
		}
		//Daca after nu e gol , retin in requested un int al acestuia
		//Altfel requested este 0
		if (after != ""){
			requested = atoi(after.c_str());
		}
		//pentru cazul in care se depaseste nr de noduri din treap
		requested = (requested + 1) % current->words->nr_nodes;
		//daca requested e 0 apelez findK pentru nr de noduri alfel pt requested
		(requested == 0) ? (result = current->words->findK(current->words->nr_nodes)):
			(result = current->words->findK(requested));
		//sterg din Treap cuvantul gasit
		current->words->erase(current->words,result);
		//ii incrementez valoarea
		result.first++;
		//si il inserez in Treap cu noua sa valoare
		current->words->insert(current->words, result, rand()%1000);
		//returnez cuvantul
		return result.second;
	}
};
