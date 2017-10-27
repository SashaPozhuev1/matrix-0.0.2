#include <iostream>
#include <sstream>

using namespace std;

bool create(float **& matrix, 
			unsigned int &rows, 
			unsigned int &columns,
			string &stroka) 
{
	unsigned int chislo;

	matrix = new float *[rows];

	for (unsigned int i = 0; i < rows; ++i) {
		matrix[i] = new float[columns];

		if( getline(cin, stroka) ) {
			istringstream stream1(stroka);

			for (unsigned int j = 0; j < columns; ++j) {
				if (stream1 >> chislo) {
					matrix[i][j] = chislo;
				}
				else {
					return false;
				}
			}
		}
	}

	return true;
}

bool read(string &stroka, 
	unsigned int &rows, 
	char &symb, 
	unsigned int &columns) 
{
	getline(cin, stroka);
	istringstream stream1(stroka);

	if (stream1 >> rows && 
		stream1 >> symb && symb == ',' && 
		stream1 >> columns) {
		return true;
	}
	else {
		return false;
	}

}

bool write(float ** matrix, unsigned int rows, unsigned int columns) {
	cout << '\n';
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (matrix[i][j] == -0.0f) {
				cout << 0.0f << "	";
			}
			else {
				cout << matrix[i][j] << "	";
			}
		}
		cout << '\n';
	}
	return true;
}

void add(float ** matrix1, float ** matrix2, float ** & matrix3, unsigned int rows, unsigned int columns) {
	matrix3 = new float *[rows];

	for (int i = 0; i < rows; i++) {
		matrix3[i] = new float [columns];
		
		for (int j = 0; j < columns; j++) {
			matrix3[i][j] = matrix1[i][j] + matrix2[i][j];
		}
	}
}

void sub(float ** matrix1, float ** matrix2, float ** & matrix3, unsigned int rows, unsigned int columns) {
	matrix3 = new float *[rows];

	for (int i = 0; i < rows; i++) {
		matrix3[i] = new float[columns];
		
		for (int j = 0; j < columns; j++) {
			matrix3[i][j] = matrix1[i][j] - matrix2[i][j];
		}
	}
}

void mul(float ** matrix1, float ** matrix2, float ** & matrix3, unsigned int rows, unsigned int columns) {
	if (rows == columns) {
		matrix3 = new float *[rows];

		for (int i = 0; i < rows; i++) {
			matrix3[i] = new float[rows];
			
			for (int j = 0; j < rows; j++) {
				float element = 0.0f;
				
				for (int k = 0; k < rows; k++) {		
					element += matrix1[i][k] * matrix2[k][j];
					matrix3[i][j] = element;
					
				}
			}
		}
	}
}

void trans(float ** & matrix3, float ** matrix1, unsigned int rows, unsigned int columns) {
	matrix3 = new float *[columns];
	for (int i = 0; i < columns; i++) {
		matrix3[i] = new float[rows];
		for (int j = 0; j < rows; j++) {
			matrix3[i][j] = matrix1[j][i];
		}
	}
}

void revers(float ** & matrix3, float ** & matrix1, unsigned int rows) {

	int i, j, k;

	matrix3 = new float *[rows];
	for (i = 0; i < rows; i++) {
		matrix3[i] = new float[rows];

		for (j = 0; j < rows; j++) {
			matrix3[i][j] = 0;
			matrix3[i][i] = 1;
		}
	}

	float a, b;

	for (i = 0; i < rows; i++) {
		a = matrix1[i][i];

		for (j = i + 1; j < rows; j++) {
			b = matrix1[j][i];

			for (k = 0; k < rows; k++) {
				matrix1[j][k] = matrix1[i][k] * b - matrix1[j][k] * a;
				matrix3[j][k] = matrix3[i][k] * b - matrix3[j][k] * a;
			}
		}
	}

	float result;

	for (i = 0; i < rows; i++) {
		for (j = rows - 1; j > -1; j--) {
			result = 0;

			for (k = rows - 1; k > j; k--) {
				result += matrix1[j][k] * matrix3[k][i];
			}

			matrix3[j][i] = (matrix3[j][i] - result) / matrix1[j][j];
		}
	}
}  

void destroy(float ** matrix,
			 unsigned int rows)
{
	for (unsigned int i = 0; i < rows; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

void error() {
	cout << '\n' << "An error has occured while reading input data";
}

float ** matrix1, ** matrix2, ** matrix3;
unsigned int rows1, rows2, columns1, columns2;


int main()
{
	char znak, symb;
	bool prav = true;

	string stroka;

	prav = read(stroka, rows1, symb, columns1);

	if (prav == true) {

		prav = create(matrix1, rows1, columns1, stroka);
		if (prav == true) {

			getline(cin, stroka);
			istringstream stream(stroka);

			stream >> znak;

			if ((znak == '+') || (znak == '-') || (znak == '*')) {

				prav = read(stroka, rows2, symb, columns2);
				if (prav == true) {

					prav = create(matrix2, rows2, columns2, stroka);
					if (prav == true) {
						
						if ((znak == '+') && (rows1 == rows2) && (columns1 == columns2)) {
							add(matrix1, matrix2, matrix3, rows1, columns1);
							write(matrix3, rows1, columns1);
						}

						else if ((znak == '-') && (rows1 == rows2) && (columns1 == columns2)) {
							sub(matrix1, matrix2, matrix3, rows1, columns1);
							write(matrix3, rows1, columns1);
						}

						else if ((znak == '*') && (rows1 == rows2) && (columns1 == columns2)) {
							mul(matrix1, matrix2, matrix3, rows1, columns2);
							write(matrix3, rows1, columns1);
						}

						else {
							error();
						}
					}
					else {
						error();
					}
				}

				destroy(matrix1, rows1);
				destroy(matrix2, rows2);
				destroy(matrix3, rows1);

			}

			else if (znak == 'T') {
				trans(matrix3, matrix1, rows1, columns1);
				write(matrix3, columns1, rows1);

				destroy(matrix1, rows1);
				destroy(matrix3, rows1);
			}

			else if ((znak == 'R') && (rows1 == columns1)) {

				revers(matrix3, matrix1, rows1);
				write(matrix3, rows1, columns1);

				destroy(matrix1, rows1);
				destroy(matrix3, rows1);
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
