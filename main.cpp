#include<iostream>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<iomanip>
using namespace std;

int max(int a, int b) {

	return a > b ? a : b;

}

void GenerateKeySequence(int *&keySeq, int &beg, int &fin, int &len) {

	cout << "Unesite nizu granicu opsega: ";
	cin >> beg;
	cout << "Unesite visu granicu opsega: ";
	cin >> fin;
	cout << "Unesite broj generisanih kljuceva: ";
	cin >> len;

	srand(time(NULL));

	keySeq = new int[len];
	for (int i = 0;i < len;i++) keySeq[i] = rand() % (fin - beg + 1) + beg;

}

int FindKeyMatrix(int **&matrix, int &n, int &m, int &key, bool output = true) {

	int numSteps = 1, i = 0, j = m - 1;
	while (i < n && j >= 0) {
		if (matrix[i][j] == key) {
			if (output) {
				cout << "Matrica sadrzi kjluc sa zadatom vrednoscu na poziciji: (" << i << ", " << j << ")\n";
				cout << "Trebalo je " << numSteps << " koraka da se nadje kljuc sa zadatom vrednoscu.\n";
			}
			return numSteps;
		}
		else if (matrix[i][j] < key) i++;
		else j--;
		numSteps++;
	}
	if (output) {
		cout << "Matrica ne sadrzi kljuc sa zadatom vrednoscu.\n";
		cout << "Broj koraka u pokusaju trazenja kljuca sa zadatom vrednoscu iznosi " << numSteps << "\n";
	}
	return numSteps;

}

void EnterKey(int &key) {
	
	cout << "Unesite vrednost kljuca koji trazite: ";
	cin >> key;

}

void DetermineAverageMatrix(int *&keySeq, int &beg, int &fin, int &len, int **&matrix, int &n, int &m) {

	int sumSteps = 0;
	for (int i = 0;i < len;i++) {
		int val = FindKeyMatrix(matrix, n, m, keySeq[i], 0);
		//cout << "(" << i << ", " << keySeq[i] << ", " << val << ")\n";
		sumSteps += val;
	}
	delete[]keySeq;

	cout << "Za zadati opseg (" << beg << ", " << fin << ") i " << len << " nasumicno generisanih kljuceva,\n"
		"prosecan broj koraka u pretrazi zadatog kljuca u matrici dimenzija " << n << "x" << m << " je:\n"
		<< static_cast <double> (sumSteps) / len << "\n";
}

void PrintMatrix(int **&matrix, int &n, int &m) {
	
	cout << "Matrica je dimenzija " << n << "x" << m << " sa sledecim elementima:\n";
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < m;j++) {
			cout << setw(3) << matrix[i][j] << (j == m - 1 ? "\n" : " ");
		}
	}

}

void FreeMatrix(int **&matrix, int &n, int &m) {

	for (int i = 0;i < n;i++) delete[]matrix[i];
	delete[]matrix;
	matrix = nullptr;
	n = m = 0;

}

void GenerateMatrix(int **&matrix, int &n, int &m) {

	FreeMatrix(matrix, n, m);
	
	const int randN = 10, randA = 300;
	srand(time(NULL));
	n = rand() % randN + 1;
	m = rand() % randN + 1;

	matrix = new int*[n];
	for (int i = 0;i < n;i++) matrix[i] = new int[m];

	int *genSeq = new int[n*m];
	for (int i = 0;i < n*m;i++) genSeq[i] = rand() % randA + 1;
	sort(genSeq, genSeq + n * m);

	int x, y, num;
	for (int k = 0;k < n + m - 1;k++) {  // O(n*m)
		if (k == 0) x = y = num = 0;
		else if (y + 1 == m) x++;
		else y++;

		int i = x, j = y;
		while (i < n && j >= 0) matrix[i++][j--] = genSeq[num++];
	}
	delete[]genSeq;
	cout << "Matrica je uspesno generisana.\n";

}

void InputMatrix(int **&matrix, int &n, int &m) {

	FreeMatrix(matrix, n, m);

	cout << "Unesite broj vrsta: ";
	cin >> n;
	cout << "Unesite broj kolona: ";
	cin >> m;

	matrix = new int*[n];
	for (int i = 0;i < n;i++) { matrix[i] = new int[m]; }

	cout << "Unesite clanove matrice linearizovanim po vrstama:\n";
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < m;j++) {
			cin >> matrix[i][j];
		}
	}

	cout << "Matrica je napravljena.\n";

}

void ClearTheScrean() { 
	
	system("cls");

}

void PrintText() {

	cout << "\nUnesite redni broj zeljene stavke:\n";
	cout << "1. Unesite matricu.\n";
	cout << "2. Generisite matricu.\n";
	cout << "3. Ispisite matricu.\n";
	cout << "4. Pretrazite matricu na zadati kljuc.\n";
	cout << "5. Generisanje nasumicnog niza kljuceva i odredjivanje perfomanse algoritma za trazenje kljuca.\n";
	cout << "6. Izlaz.\n\n";

}

bool MainMenu(int **&matrix, int &n, int &m) {

	PrintText();

	int item;
	cin >> item;

	ClearTheScrean();

	if (item != 1 && item != 2 && !matrix) {
		cout << "Morate prvo uneti matricu odabirom stavke 1 ili je generisati odabirom stavke 2.\n";
		return true;
	}

	if (item == 1) InputMatrix(matrix, n, m);
	else if (item == 2) GenerateMatrix(matrix, n, m);
	else if (item == 3) PrintMatrix(matrix, n, m);
	else if (item == 4) {
		int key;
		EnterKey(key);
		FindKeyMatrix(matrix, n, m, key);
	}
	else if (item == 5) {
		int *keySeq = nullptr, beg, fin, len;
		GenerateKeySequence(keySeq, beg, fin, len);
		DetermineAverageMatrix(keySeq, beg, fin, len, matrix, n, m);
	}
	else if (item == 6) {
		FreeMatrix(matrix, n, m);
		return false;
	}

	return true;

}

void PrintIntro() {
	
	cout << "Dobrodosli.\n"; 

}

void PrintOutro() {
	
	cout << "Dovidjenja.\n";

}

int main() {

	int **matrix = nullptr, n = 0,  m = 0;

	PrintIntro();
	while (MainMenu(matrix, n, m));
	PrintOutro();

	return 0;

}