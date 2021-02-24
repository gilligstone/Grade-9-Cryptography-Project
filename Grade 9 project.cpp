/*

Gil Shteyman, Aditya Agashe, Sanjana Gunda
Grade 9 Cyptography Project

*/



#include <vector>
#include <Windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <time.h>
#include <Windows.h>
#include <iostream>       
#include <thread>     
#include <chrono> 
#include<stdlib.h>
#include <fstream>
#include <algorithm>
#include <mmsystem.h>
using namespace std;

vector<vector<int>> generateKey();
string CreateAFile();
void WriteInFile(vector<vector<int>>, vector<vector<float>>, string, int length);
vector<vector<float>> generateInverse(vector<vector<int>> key);
void Encrypt();
vector<vector<int>> findTheDeterminant(vector<vector<int>>);
vector<vector<int>> messageToVector(vector<int>);
vector<int> messageSingleRow(string receivedMessage);
vector<vector<int>> Multiplication(vector<vector<int>>, vector<vector<int>>, vector<int>);
vector<vector<int>> DecryptMultiplication(vector<vector<float>>, vector<vector<int>>, int);
vector<vector<char>> DecryptNumsToLetters(vector<vector<int>> message, int numberOfLines);
void DisplayMessage(vector<vector<char>> message, int numberOfLines);
void Decrypt();
void readMessage();
void displayLock();
void Space(int);

int main()
{
	displayLock();
	while (1)
	{
		
		string whatToDo = "encrypt";
		cout << "Would you like to encrypt or decrypt or exit: ";
		cin.clear();
		fflush(stdin);
		getline(cin, whatToDo);
		if (whatToDo == "encrypt" or whatToDo == "Encrypt" or whatToDo == "ENCRYPT")
			Encrypt();
		else if (whatToDo == "decrypt" or whatToDo == "Decrypt" or whatToDo == "DECRYPT")
			Decrypt();
		else
		{
			return 0;
		}
	}
	return 0;
}

void displayLock()
{
	system("color 1C");
	cout << endl << endl << endl << endl;
	Space(20); cout << "    ************    "; Space(15); cout << endl;
	Space(20); cout << "   *            *   "; Space(15); cout << endl;
	Space(20); cout << "  *              *  "; Space(15); cout << endl;
	Space(20); cout << " *                * "; Space(15); cout << endl;
	Space(20); cout << "*                  *"; Space(15); cout << endl;
	Space(20); cout << "*                  *"; Space(15); cout << endl;
	Space(20); cout << "********************"; Space(15); cout << endl;
	Space(20); cout << "********************"; Space(15); cout << endl;
	Space(20); cout << "********* **********"; Space(15); cout << "    **  **    *         " << endl;
	Space(20); cout << "********   *********"; Space(15); cout << "    **  **    *         " << endl;
	Space(20); cout << "********   *********"; Space(15); cout << "    **  ***   *      ***" << endl;
	Space(20); cout << "********* **********"; Space(15); cout << "   **********************" << endl;
	Space(20); cout << "********   *********"; Space(15); cout << "   **********************" << endl;
	Space(20); cout << "*******     ********"; Space(15); cout << "                     *** " << endl;
	Space(20); cout << "********************"; Space(15); cout << endl;
	Space(20); cout << "********************"; Space(15); cout << endl;
	cout << endl; Space(27); cout << "Encryption and Decryption!! Cryptography Project!!" << endl;
	Space(20); cout << "Brought to you by: Gil Shteyman, Aditya Agashe, Sanjana Gunda" << endl << endl << endl << endl;
	

}
void Space(int x)
{
	for (int i = 0; i < x; i++)
		cout << " ";
}
void Decrypt()
{
	 readMessage();
	 cout << endl;
}
void readMessage()
{
	string fileName;
	ifstream read;
	cout << "What is the name of the file which contains the encripted message: ";
	getline(cin, fileName);
	fileName += ".txt";
	read.open(fileName);
	if (read.fail())
		exit(1);
	vector<vector<int>> EncryptedMessage(10000, vector<int>(3));
	vector<vector<float>> inverse(3, vector<float>(3));
	int numberOfLines = 0;
	string line;
	ifstream myfile(fileName);

	while (getline(myfile, line))
	{
		++numberOfLines;
	}
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			read >> inverse[j][i];
			//cout << inverse[j][i];
		}
	}
	for (int z = 0; z < numberOfLines - 4; z++)
	{
		for (int x = 0; x < 3; x++)
		{
			read >> EncryptedMessage[z][x];
			//cout << EncryptedMessage[z][x];
		}
	}
	vector<vector<int>>decryptedMessage = DecryptMultiplication(inverse, EncryptedMessage, numberOfLines);
	vector<vector<char>> charMessage = DecryptNumsToLetters(decryptedMessage, numberOfLines);
	DisplayMessage(charMessage, numberOfLines);
}
vector<vector<char>> DecryptNumsToLetters(vector<vector<int>> message, int numberOfLines)
{
	vector<vector<char>> letterMessage(10000, vector<char>(3));
	for (int i = 0; i < numberOfLines - 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			letterMessage[i][j] = message[i][j];
		}
	}
	return letterMessage;
}
void DisplayMessage(vector<vector<char>> message, int numberOfLines)
{
	for (int i = 0; i < numberOfLines - 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << message[i][j];
		}
	}
	cout << endl;
}

void Encrypt()
{
	string receivedMessage;
	cout << "What message would you like to encrypt?" << endl;
	getline(cin, receivedMessage);
	vector<int> messageRow = messageSingleRow(receivedMessage);
	int length = messageRow.size();
	vector<vector<int>> encryptedMessage = messageToVector(messageRow);
	vector<vector<int>> key = generateKey();
	vector<vector<float>> inverse = generateInverse(key);
	vector<vector<int>> multipledMatrix = Multiplication(key, encryptedMessage, messageRow);
	string nameOfFile = CreateAFile();
	WriteInFile(multipledMatrix, inverse, nameOfFile, length);
	cout << endl;
}

vector<vector<int>> DecryptMultiplication(vector<vector<float>> inverse, vector<vector<int>> encryptedMessage, int numberOfLines)
{
	vector<vector<int>> MultipliedVector(10000, vector<int>(3));
	int total = 0;
	for (int k = 0; k < (numberOfLines - 4); k++)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				total += encryptedMessage[k][j] * inverse[j][i];
			}
			MultipliedVector[k][i] = total;
			//cout << MultipliedVector[k][i] << endl;
			total = 0;
		}

	}
	return MultipliedVector;
}

vector<vector<int>> Multiplication(vector<vector<int>> key, vector<vector<int>> encryptedMessage, vector<int> messageSingleRow)
{
	vector<vector<int>> MultipliedVector(10000, vector<int>(3));
	int total = 0;
	for (int k = 0; k < (messageSingleRow.size() / 3); k++)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				total += encryptedMessage[k][j] * key[j][i];
			}
			MultipliedVector[k][i] = total;
			//cout << MultipliedVector[k][i] << endl;
			total = 0;
		}

	}
	return MultipliedVector;
}


vector<int> messageSingleRow(string receivedMessage)
{
	vector<int> messageSingleRow;
	int a;
	for (int i = 0; i < receivedMessage.size(); i++)
	{
		a = receivedMessage[i];
		messageSingleRow.push_back(a);
	}
	int leftover;
	if (receivedMessage.size() % 3 == 0)
	{
		leftover = 0;
	}
	else 	if (receivedMessage.size() % 3 == 2)
	{
		leftover = 1;
	}
	else
	{
		leftover = 2;
	}
	for (leftover = leftover; leftover > 0; leftover--)
	{
		messageSingleRow.push_back(0);
	}
	return messageSingleRow;
}

vector<vector<int>> messageToVector(vector<int> messageSingleRow)
{
	vector<vector<int>> messageInVector(10000, vector<int>(3));
	int a;
	int x = 0;
	for (int i = 0; i < messageSingleRow.size() / 3; i++)
	{
		for (int j = 0; j < 3; j++, x++)
		{
			messageInVector[i][j] = messageSingleRow[x];
			//cout << messageInVector[i][j] << endl;
		}
	}
	return (messageInVector);
}

vector<vector<int>> generateKey()
{
	srand(time(0));
	vector<vector<int>> key;
	int place = 0;
	int fakeKey[9];
	int n = 10 - rand() % 21;
	

	fakeKey[0] = 8 * n * n + 8 * n;;
	fakeKey[1] = 2 * n + 1;
	fakeKey[2] = 4 * n;
	fakeKey[3] = 4 * n*n + 4 * n;
	fakeKey[4] = n + 1;
	fakeKey[5] = 2 * n + 1;
	fakeKey[6] = 4 * n*n + 4 * n + 1;
	fakeKey[7] = n;
	fakeKey[8] = 2 * n - 1;
	for (int length = 0; length < 3; length++)
	{
		vector<int> row;

		for (int i = 0; i < 3; i++)
		{
			int a = fakeKey[place];
			//cout << fakeKey[place] << endl;
			row.push_back(a);
			place++;
		}
		key.push_back(row);
	}
	key = findTheDeterminant(key);
	return key;
}

vector<vector<int>> findTheDeterminant(vector<vector<int>> key)
{
	int determinant;
	do
	{
		determinant = key[0][0] * key[1][1] * key[2][2] + key[0][1] * key[1][2] * key[2][0] + key[0][2] * key[1][0] * key[2][1] -
			key[2][0] * key[1][1] * key[0][2] - key[2][1] * key[1][2] * key[0][0] - key[2][2] * key[1][0] * key[0][1];
		if (determinant == 0)
		{
			key = generateKey();

		}
	} while (determinant == 0);
	return key;
}

vector<vector<float>> generateInverse(vector<vector<int>> key)
{
	int determinant = key[0][0] * key[1][1] * key[2][2] + key[0][1] * key[1][2] * key[2][0] + key[0][2] * key[1][0] * key[2][1] -
		key[2][0] * key[1][1] * key[0][2] - key[2][1] * key[1][2] * key[0][0] - key[2][2] * key[1][0] * key[0][1];
	//cout << determinant << endl;
	vector<vector<float>> inverse;
	float a;
	for (int length = 0; length < 3; length++)
	{
		vector<float> row;

		for (int i = 0; i < 3; i++)
		{
			a = ((float)(key[(i + 1) % 3][(length + 1) % 3] * (float)key[(i + 2) % 3][(length + 2) % 3]) -
				((float)key[(i + 1) % 3][(length + 2) % 3] * (float)key[(i + 2) % 3][(length + 1) % 3])) / (float)determinant;
			row.push_back(a);
			//cout << a;
		}
		inverse.push_back(row);
	}
	return inverse;
}

string CreateAFile()
{
	ofstream output;
	string nameOfFile;
	cout << "What file would you like to export the encripted message: ";
	 getline(cin, nameOfFile);
	nameOfFile += ".txt";
	output.open(nameOfFile);
	output.close();
	return nameOfFile;
}
void WriteInFile(vector<vector<int>> message, vector<vector<float>> inverse, string nameOfFile, int length)
{
	int lengthOfLine = length / 3;
	ofstream output;
	output.open(nameOfFile);
	for (int x = 0; x < 3; x++)
	{
		for (int z = 0; z < 3; z++)
		{
			output << inverse[x][z] << " ";
		}
		output << endl;
	}
	output << endl;
	for (int a = 0; a < lengthOfLine; a++)
	{
		for (int i = 0; i < 3; i++)
		{
			output << message[a][i] << " ";
		}
		output << endl;
	}
}
