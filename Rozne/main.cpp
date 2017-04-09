#include <iostream>

using namespace std;

int ilosc_testow, minimum, maximum;
int n, k;
int liczba;
int usuwana;

struct TrieNode {
	TrieNode **dzieci;
	//TrieNode* rodzic;
	int klucz;

	TrieNode() {}
	~TrieNode(){
		this->klucz = NULL;
		delete[] dzieci;
		this->dzieci = NULL;
		//	delete this;
	}
	
	TrieNode(int klucz, int wielkosc){
		this->klucz = klucz;
		(*this).dzieci = new TrieNode* [wielkosc];
		for (int i = 0; i < wielkosc; i++) {
			//this->dzieci[i].klucz = NULL;
			this->dzieci[i] = NULL;
		}
	}
};

TrieNode *root = NULL;
TrieNode *usuwanywezel = NULL;
TrieNode *rodzic;
int rodzica;

void search(int key, TrieNode *tree = root, int modul = n)
{
	int div = key / modul;
	int mod = key % modul;
	//TrieNode *drzewo = tree->dzieci[mod];

	if (tree->klucz == liczba)
		//printf("%liczba exist\n", liczba);
		cout << liczba << " exist" << endl;
	else if ((*tree).dzieci[mod] == NULL) {
		TrieNode *nowy = new TrieNode(liczba, k);
		tree->dzieci[mod] = nowy;
	}
	else
		search(div, tree->dzieci[mod], k);

	/*
	else if (drzewo->klucz == NULL)
	printf("%liczba exist\n", liczba);
	*/
}

void searchshow(int key, TrieNode *tree = root, int modul = n) {
	int div = key / modul;
	int mod = key % modul;
//	TrieNode *drzewo = tree->dzieci[mod];

	if (tree->klucz == liczba)
		//printf("%liczba exist\n", liczba);
		cout << liczba << " exist" << endl;
	else if (tree->dzieci[mod] == NULL) {
		//printf("%liczba not exist\n", liczba);
		cout << liczba << " not exist" << endl;
	}
	else
		searchshow(div, tree->dzieci[mod], k);

}

void searchtodelete(TrieNode *tree, int modul) {
	int i = 0;
	int j = 0;
	while (tree->dzieci[i] == NULL){
		i++;
	}
	if (tree->dzieci[i] != NULL)
		while (tree->dzieci[i]->dzieci[j] == NULL && j < k){	//
		j++;									//
		}


	if (j != k)
		searchtodelete(tree->dzieci[i], k);
	else {
		usuwana = tree->dzieci[i]->klucz;	
		tree->dzieci[i]->~TrieNode();
		tree->dzieci[i] = NULL;
		delete tree->dzieci[i];
	}
	/*
	if (i != modul)
		searchtodelete(tree->dzieci[i], k);
	else {
		usuwana = tree->klucz;
		usuwanywezel = tree;
		tree->~TrieNode();
	}
	*/
}

void searchdelete(int key, TrieNode *tree = root, int modul = n)
{
	int test = 0;

	int div = key / modul;
	int mod = key % modul;
	//TrieNode *drzewo = tree->dzieci[mod];

	if (tree->klucz == liczba) { // znajdz klucz, znaldz wezel ktury nie ma potomstwa, wrzuc do usuwanego wezla klucz, usun wezel bez potomstwa
		for (int i = 0; i < modul; i++)
			if (tree->dzieci[i] != NULL) { //sprwdzam czy usuwana liczba nie jest ostatnim wezlem
			test++;
			break;
			}
		if (test != 0) {			// jesli liczba, jest ostatnim wezlem to ją usuwam
			searchtodelete(tree, modul);
			tree->klucz = usuwana;
			//delete usuwanywezel;
		}
		else {
			rodzic->dzieci[rodzica] = NULL;
			tree->~TrieNode();
		}

	}
	else if (tree->dzieci[mod] == NULL)
		//printf("%liczba not exist\n", liczba);
		cout << liczba << " not exist" << endl;
	else {
		rodzic = tree;
		rodzica = mod;
		searchdelete(div, tree->dzieci[mod], k);
	}
}

void funkcjaI(int liczba){ //wstawienie klucza
	if (root == NULL)
		root = new TrieNode(liczba, n);
	else
		search(liczba);
}

void funkcjaL(int liczba){ // wyszukaj

	searchshow(liczba);
	//printf("%liczba exist\n", liczba);
	//printf("%liczba not exist\n", liczba);
}

void funkcjaD(int liczba){ //usuń
	searchdelete(liczba);
	//printf("%liczba not exist\n", liczba);
}

void funkcjaP(TrieNode *tree = root, int modul = n){ // przeglądaj inorder - rekurencja
	int key = tree->klucz;
	//printf("%key ", key);
	cout << key << " ";
	for (int i = 0; i < modul; i++)
		if (tree->dzieci[i] != NULL)
			funkcjaP(tree->dzieci[i], k);
}

int main()
{
	char znak;


	scanf("%i", &ilosc_testow);
	scanf("%i %i", &minimum, &maximum);
	scanf("%i %i", &n, &k);

	for (int i = 0; i < ilosc_testow; i++) {
		//scanf("%c", &znak);
		cin >> znak;

		if (znak == 'I') {
			scanf("%i", &liczba);
			funkcjaI(liczba);
		}
		else if (znak == 'L') {
			scanf("%i", &liczba);
			funkcjaL(liczba);
		}
		else if (znak == 'P') {
			funkcjaP();
			cout << endl;
		}
		else if (znak == 'D') {
			scanf("%i", &liczba);
			funkcjaD(liczba);
			//printf("\n", liczba);
		}
	}

	return 0;
}