#include<iostream>
using namespace std;

int adjust_matrix(int m[4][4]) {
	for (int i = 0; i <= 3; i++) {
		int minrow = m[0][0];
		for (int j = 0; j <= 3; j++) { //to get min row
			if (minrow > m[i][j])
				minrow = m[i][j];
		}
		for (int j = 0; j <= 3; j++) { //substract the min row
			m[i][j] -= minrow;
		}
	}

	for (int j = 0; j <= 3; j++) {
		int mincol = m[0][0];
		for (int i = 0; i <= 3; i++) { //get min column
			if (mincol > m[i][j])
				mincol = m[i][j];
		}
		for (int i = 0; i <= 3; i++) { //subtract min column
			m[i][j] -= mincol;
		}
	}
	return m[4][4]; //Adjusted matrix
}

int drawLines(int matrix[4][4], int OriginalMatrix[4][4]) {
	bool rowZeroline[4] = { false }; //if true it acts as a drawn line
	bool colZeroline[4] = { false }; //if true it acts as a drawn line
	int solMatrix[4]; //store selected job to each person

	//draw vertical line on zeros (if there is only 1 zero in the row)
	for (int i = 0; i <= 3; i++) {
		int ZerosNo = 0; //number of zeros in one row or column
		int colNo = 0; //column location at which vertical line could be drawn
		for (int j = 0; j <= 3; j++) {
			if (matrix[i][j] == 0 && colZeroline[j] == false) {
				ZerosNo++;
				colNo = j; 
			}
			if (ZerosNo == 1 && colZeroline[colNo] == false) {
				colZeroline[colNo] = true; //drawn line
				solMatrix[i] = colNo; //store selected job to person number i
			}
		}
	}

	//draw horizontal line on zeros (if there is only 1 zero in the column)
	for (int j = 0; j <= 3; j++) {
		int ZerosNo = 0; //number of zeros in one row or column
		int rowNo = 0; //row location at which horizontal line could be drawn
		for (int i = 0; i <= 3; i++) {
			if (matrix[i][j] == 0 && colZeroline[j] == false) {
				ZerosNo++;
				rowNo = i;
			}
		}
		if (ZerosNo == 1 && rowZeroline[rowNo] == false) {
			rowZeroline[rowNo] = true; //drawn line
			solMatrix[rowNo] = j; //store selected job to person number i(rowNo)
		}
	}

	//check that no zeros left
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			if (matrix[i][j] == 0 && colZeroline[j] == false && rowZeroline[i] == false) {
				rowZeroline[i] = true;
				solMatrix[i] = j; //store selected job to person number i
			}
		}
	}

	int NoLines = 0;
	for (int m = 0; m <= 3; m++) {
		if (rowZeroline[m] == true)
			NoLines += 1;
		if (colZeroline[m] == true)
			NoLines += 1;
	}
	cout << "\nNumber of drawn lines : " << NoLines << endl;
	if (NoLines < 4) {
		for (int i = 0; i <= 3; i++) {
			int minno = 10000; // min no zero elemnt
			for (int j = 0; j <= 3; j++) {
				if (rowZeroline[i] == false && colZeroline[j] == false) {
					if (minno > matrix[i][j] && matrix[i][j] > 0)
						minno = matrix[i][j];
				}
			}
			for (int j = 0; j <= 3; j++) { //substract the min number from unmarked numbers
				if (rowZeroline[i] == false && colZeroline[j] == false) {
					matrix[i][j] -= minno;
				}
			}	
		}
		drawLines(matrix, OriginalMatrix);
	}
	 
	//display jobs assignment
	for (int i = 0; i <= 3; i++) {
		cout << "\nPerson " << i + 1 << " do job no. " << solMatrix[i] + 1;
	}
	int sum = 0; //optimal solution
	for (int k = 0; k <= 3; k++) {
		sum += OriginalMatrix[k][solMatrix[k]];
	}
	return sum;
}

int main() {
	int matrix[4][4] = { 9,2,7,8,6,4,3,7,5,8,1,8,7,6,9,4 };
	int OriginalMatrix[4][4] = { 9,2,7,8,6,4,3,7,5,8,1,8,7,6,9,4 };
	/*
	cout<<"enter the 4x4 matrix you want to solve : \n";
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			cout << "Enter element for ("<<i<<","<<j<<"): ";
			cin>> matrix[i][j];
		}
	}*/
	matrix[4][4] = adjust_matrix(matrix);

	cout << "Adjusted matrix :\n--------------------------";
	for (int i = 0; i <= 3; i++) { //display after subtract min column & min row
		cout << "\n";
		for (int j = 0; j <= 3; j++) {
			cout << matrix[i][j] << "\t";
		}
	}
	cout << "\n--------------------------\n";
	cout << "\n\nOptimal solution = " << drawLines(matrix, OriginalMatrix) << "\n";
}
