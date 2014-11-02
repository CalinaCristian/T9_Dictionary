/*CALINA CRISTIAN FLORIN 313CA*/
using namespace std;
//Supraincarc operatorii < si > pentru a compara o pereche de <int,string>
bool operator< (const std::pair<int, std::string>& lhs,
			const std::pair<int, std::string>& rhs) {
	return lhs.first > rhs.first ||
			(rhs.first == lhs.first && lhs.second < rhs.second);
	};

bool operator> (const std::pair<int, std::string>& lhs,
			const std::pair<int, std::string>& rhs) {
	return lhs.first < rhs.first ||
			(rhs.first == lhs.first && lhs.second > rhs.second);
	};

//Treapul este conform scheletului din laborator 11 cu exceptia functiilor
//ce nu au folosit la aceasta tema
template <typename T> struct Treap {
	//cheia este de tip pair pentru a retine nr de aparitii si cuvantul
	std::pair<int,string> key;
	int priority;
	Treap<T> *left, *right;
	bool nil;
	int nr_nodes;
	//Constructor
	Treap() :
		priority(-1), left(NULL) , right(NULL) , nil(true), nr_nodes(0){}
	//Destructor
	~Treap(){
		if (left) delete left;
		if (right) delete right;
	}
	//Adaug informatii pe un nod
	void addData(std::pair<int,string>& key, int priority){
		this->nil = false;
		this->key = key;
		this->priority = priority;
		this->nr_nodes = 1;
		this->left = new Treap();
		this->right = new Treap();
	}
	//Sterg informatii de pe nod
	void delData() {
		this->nil = true;
		this->priority = -1;
		delete this->left;
		delete this->right;
		left = right = NULL;
		this->nr_nodes = 0;
	}
	//Verific daca nodul este NULL
	bool isNil() {
		return this->nil;
	}
	//Rotire dreapta
	void rotateRight(Treap<T> *&nod) {
		Treap<T> *aux;
		aux = nod->left;
		nod->nr_nodes = 1 + nod->right->nr_nodes + aux->right->nr_nodes;
		aux->nr_nodes = 1 + aux->left->nr_nodes + nod->nr_nodes;
		nod->left = aux->right;
		aux->right = nod;
		nod = aux;
	}
	//Rotire stanga
	void rotateLeft(Treap<T> *&nod) {
		Treap<T> *aux;
		aux = nod->right;
		nod->nr_nodes = 1 + nod->left->nr_nodes + aux->left->nr_nodes;
		aux->nr_nodes = 1 + aux->right->nr_nodes + nod->nr_nodes;
		nod->right = aux->left;
		aux->left = nod;
		nod = aux;
	}
	//Adaug element in treap
	void insert (Treap<T> *&fatherPointer, std::pair<int,string>& key,
			int priority){
		if (this->isNil()) {
			this->addData(key, priority);
			return;
		}
		if (key < this->key) {
			this->left->insert(fatherPointer->left,key,priority);
			nr_nodes++;
		}
		else {
			this->right->insert(fatherPointer->right,key,priority);
			nr_nodes++;
		}
		if (this->left->priority > this->priority) {
			this->rotateRight(fatherPointer);
		}
		else if (this->right->priority > this->priority) {
			this->rotateLeft(fatherPointer);
		}
	}
	//Sterg nod din treap
	void erase (Treap<T> *&fatherPointer, std::pair<int,string>& key){
		if (this->isNil()){
			return;
		}
		if (key < this->key) {
			nr_nodes--;
			left->erase(left,key);
		}
		else if (key > this->key) {
			nr_nodes--;
			right->erase(right,key);
		}
		else if (this->left->isNil() && this->right->isNil()){
			this->delData();
		}
		else {
			if (this->left->priority > this->right->priority) {
				rotateRight(fatherPointer);
				fatherPointer->nr_nodes--;
				fatherPointer->right->erase(fatherPointer->right,key);
			}
			else {
				rotateLeft(fatherPointer);
				fatherPointer->nr_nodes--;
				fatherPointer->left->erase(fatherPointer->left,key);
			}
		}
	}
	//Returnez al k-lea element(drept pair)
	std::pair<int,string>& findK(int k) {
		int aux = this->left->nr_nodes;
		if ( k == aux + 1 ) {
			return this->key;
		}
		if ( k < aux + 1 ) {
			return this->left->findK(k);
		}
		return this->right->findK(k-aux-1);
	}
};
