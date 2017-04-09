#include <iostream>

using namespace std;

struct TrieNode {
	TrieNode **dzieci;
	int klucz;

	TrieNode() {}
	~TrieNode(){
		this->klucz = NULL;
		delete[] dzieci;
		this->dzieci = NULL;
	}
	
	TrieNode(int klucz, int wielkosc){
		this->klucz = klucz;
		(*this).dzieci = new TrieNode* [wielkosc];
		for (int i = 0; i < wielkosc; i++) 
			this->dzieci[i] = NULL;		
	}
};

int n, k;
int liczba;
int usuwana;
TrieNode *root = NULL;
TrieNode *rodzic;
int rodzica;

void search(int key, TrieNode *tree = root, int modul = n)
{
	int div = key / modul;
	int mod = key % modul;

	if (tree->klucz == liczba)
		cout << liczba << " exist" << endl;
	else if (tree->dzieci[mod] == NULL) {
		TrieNode *nowy = new TrieNode(liczba, k);
		tree->dzieci[mod] = nowy;
	}
	else
		search(div, tree->dzieci[mod], k);
}

void searchshow(int key, TrieNode *tree = root, int modul = n) 
{
	int div = key / modul;
	int mod = key % modul;

	if (tree->klucz == liczba)
		cout << liczba << " exist" << endl;
	else if (tree->dzieci[mod] == NULL) 
		cout << liczba << " not exist" << endl;
	else
		searchshow(div, tree->dzieci[mod], k);

}

void searchtodelete(TrieNode *tree, int modul) 
{
	int i = 0;
	int j = 0;

	while (tree->dzieci[i] == NULL){ //znajduje miejsce w którym jest dziecko
		i++;
	}
	if (tree->dzieci[i] != NULL) // sprawdzam czy dziecko nie ma dzieci
		while (tree->dzieci[i]->dzieci[j] == NULL && j < k)
		j++;

	if (j != k)
		searchtodelete(tree->dzieci[i], k);
	else {
		usuwana = tree->dzieci[i]->klucz;	
		tree->dzieci[i]->~TrieNode();
		tree->dzieci[i] = NULL;
		delete tree->dzieci[i];
	}
}

void searchdelete(int key, TrieNode *tree = root, int modul = n)
{
	int test = 0; //liczy czy wezel nie ma dzieci

	int div = key / modul;
	int mod = key % modul;

	if (tree->klucz == liczba) { // znajdz klucz, znaldz wezel ktory nie ma potomstwa, wrzuc do usuwanego wezla klucz, usun wezel bez potomstwa
		for (int i = 0; i < modul; i++)
			if (tree->dzieci[i] != NULL) { //sprwdzam czy usuwana liczba nie jest ostatnim wezlem
			test++;
			break;
			}
		if (test != 0) {			
			searchtodelete(tree, modul); // szukam po lewej wezla ktory nie ma dzieci
			tree->klucz = usuwana;
		}
		else {	// jesli liczba, jest ostatnim wezlem to j¹ usuwam
			rodzic->dzieci[rodzica] = NULL;
			tree->~TrieNode();
		}

	}
	else if (tree->dzieci[mod] == NULL)
		cout << liczba << " not exist" << endl;
	else {
		rodzic = tree; //wskaŸnik do zerowania w rodzicu usuwanego wezla
		rodzica = mod;
		searchdelete(div, tree->dzieci[mod], k);
	}
}

void funkcjaP(TrieNode *tree = root, int modul = n){ // przegl¹daj inorder - rekurencja
	int key = tree->klucz;
	cout << key << " ";
	for (int i = 0; i < modul; i++)
		if (tree->dzieci[i] != NULL)
			funkcjaP(tree->dzieci[i], k);
}

int main()
{
	char znak;
	int ilosc_testow, minimum, maximum;

	scanf("%i", &ilosc_testow);
	scanf("%i %i", &minimum, &maximum);
	scanf("%i %i", &n, &k); // wielkosc tablicy korzenia, wielkosc tablicy dzieci

	for (int i = 0; i < ilosc_testow; i++) {
		cin >> znak;

		if (znak == 'I') { // wstawianie klucza
			scanf("%i", &liczba);
			if (root == NULL)
				root = new TrieNode(liczba, n);
			else
				search(liczba);
		}
		else if (znak == 'L') { // sprawdzanie czy instnieje czy nie istnieje
			scanf("%i", &liczba);
			searchshow(liczba);
		}
		else if (znak == 'P') { // wyswiwetlanie drzewa
			funkcjaP();
			cout << endl;
		}
		else if (znak == 'D') { // usuwanie
			scanf("%i", &liczba);
			searchdelete(liczba);
		}
	}

	return 0;
}