#include <iostream>
#include <sstream>

using namespace std;

bool create(float ** matrix1, unsigned int &rows1, unsigned int &columns1, string &stroka, bool &prav) {
	unsigned int chislo;

	for (unsigned int i = 0; i < rows1; ++i) {
		matrix1[i] = new float[columns1];

		getline(cin, stroka);
		istringstream stream1(stroka);

		for (unsigned int j = 0; j < columns1; ++j) {
			if (stream1 >> chislo) {
				matrix1[i][j] = chislo;
			}
			else {
				prav = false;
			}
		}
	}
	
	return prav;
}

bool read(string &stroka, unsigned int &rows1, char &symb, unsigned int &columns1) {
	getline(cin, stroka);
	istringstream stream1(stroka);

	if (stream1 >> rows1 && stream1 >> symb && stream1 >> columns1) {
		return true;
	}
	else {
		return false;
	}
}

bool write(float ** matrix1, unsigned int &rows1, unsigned int &columns1) {
	cout << '\n';
	for (int i = 0; i < rows1; i++) {
		for (int j = 0; j < columns1; j++) {
			cout << matrix1[i][j] << "	";
		}
		cout << '\n';
	}
	return true;
}

bool add(float ** matrix1, float ** matrix2, unsigned int &rows1, unsigned int &columns1) {
	for (int i = 0; i < rows1; i++) {
		for (int j = 0; j < columns1; j++) {
			matrix1[i][j] += matrix2[i][j];
		}
	}
	return true;
}

bool sub(float ** matrix1, float ** matrix2, unsigned int &rows1, unsigned int &columns1) {
	for (int i = 0; i < rows1; i++) {
		for (int j = 0; j < columns1; j++) {
			matrix1[i][j] -= matrix2[i][j];
		}
	}
	return true;
}

bool mul(float ** matrix1, float ** matrix2, unsigned int &rows1, unsigned int &columns1){
	int kol, min, schet = 0;
	kol = rows1 * columns1;
	
	if (columns1 < rows1) {
		min = columns1;
	}
	else {
		min = rows1;
	}

	float *mass = new float[kol];
	//обнуляем созданный массив
	for (int i = 0; i < kol; i++) {
		mass[i] = 0;
	}

	//заполняем его значениями итогого массива
	for (int i = 0; i < rows1; i++) {
		for (int j = 0; j < columns1; j++) {		
			for (int k = 0; k < min; k++) {
				mass[schet] += matrix1[i][k] * matrix2[k][j];
			}
			
			schet++;
		}	
	}

	schet = 0;
	// переводим его в matrix1
	for (int i = 0; i < rows1; i++) {
		for (int j = 0; j < columns1; j++) {
			matrix1[i][j] = mass[schet];
			schet++;
		}
	}

	return true;
}

bool trans(float ** mass, float ** matrix1, unsigned int &rows1, unsigned int &columns1) {
	for (int i = 0; i < columns1; i++) {
		mass[i] = new float[rows1];
		for (int j = 0; j < rows1; j++) {
			mass[i][j] = matrix1[j][i];
		}
	}

	cout << '\n';
	for (int i = 0; i < columns1; i++) {
		for (int j = 0; j < rows1; j++) {
			cout << mass[i][j] << "	";
		}
		cout << '\n';
	}
	
	return true;
}

bool revers(float ** mass, float ** matrix1, unsigned int &rows1) {

	int i, j, k;

	/////////новая матрица
	for (i = 0; i < rows1; i++) {
		mass[i] = new float[rows1];

		for (j = 0; j < rows1; j++) {
				mass[i][j] = 0;
				mass[i][i] = 1;
		}
	}

	float a, b;

	for (i = 0; i < rows1; i++) {
		a = matrix1[i][i];

		for (j = i + 1; j < rows1; j++) {
			b = matrix1[j][i];

			for (k = 0; k < rows1; k++) {
				matrix1[j][k] = matrix1[i][k] * b - matrix1[j][k] * a;
				mass[j][k] = mass[i][k] * b - mass[j][k] * a;
			}
		}
	}

	float result;
	
	for (i = 0; i < rows1; i++) {
		for (j = rows1 - 1; j > - 1; j--) {
			result = 0;

			for (k = rows1 - 1; k > j; k--) {
				result += matrix1[j][k] * mass[k][i];

				if (matrix1[j][j] == 0) {
					for (i = 0; i < rows1; i++) {
						delete [] mass[i];
						delete [] mass;
					}
				}
			}

			mass[j][i] = (mass[j][i] - result) / matrix1[j][j];
		}
	}

	cout << '\n';
	for (int i = 0; i < rows1; i++) {
		for (int j = 0; j < rows1; j++) {
			cout << mass[i][j] << "	";
		}
		cout << '\n';
	}

	return true;
}

void error() {
	cout << '\n' << "An error has occured while reading input data";
}

int main()
{
	char znak, symb;
	bool prav = true;
	
	unsigned int rows1 = 0;
	unsigned int columns1 = 0;

	unsigned int rows2 = 0;
	unsigned int columns2 = 0;
	
	string stroka;

	read(stroka, rows1, symb, columns1);

	if (symb == ',') {

		float ** matrix1 = new float *[rows1];
		
		create(matrix1, rows1, columns1, stroka, prav);
		if (prav == true) {

			getline(cin, stroka);
			istringstream stream(stroka);

			stream >> znak;

			if ((znak == '+') || (znak == '-') || (znak == '*')) {
				read(stroka, rows2, symb, columns2);
				if (symb == ',') {
					float ** matrix2 = new float *[rows2];
					create(matrix2, rows2, columns2, stroka, prav);
					
					if (prav == true) {
						if ((znak == '+') && (rows1 == rows2) && (columns1 == columns2)) {
							add(matrix1, matrix2, rows1, columns1);
							write(matrix1, rows1, columns1);
						}

						else if ((znak == '-') && (rows1 == rows2) && (columns1 == columns2)) {
							sub(matrix1, matrix2, rows1, columns1);
							write(matrix1, rows1, columns1);
						}

						else if ((znak == '*') && (rows1 == rows2) && (columns1 == columns2)) {
							mul(matrix1, matrix2, rows1, columns1);
							write(matrix1, rows1, columns1);
						}

						else {
							error();
						}
					}
					else {
						error();
					}
				}
				
			}

			else if (znak == 'T') {
				float **mass = new float *[columns1];
				trans(mass, matrix1, rows1, columns1);
			}

			else if ((znak == 'R') && (rows1 == columns1)) {
				float **mass = new float *[columns1];
				revers(mass, matrix1, rows1);
			}

			else {
				error();
			}
		}
		else {
			error();
		}
	}
	else {
		error();
	}

	cin.get();
    return 0;

	}
