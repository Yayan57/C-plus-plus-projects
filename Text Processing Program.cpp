#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

struct Word
{
	int wordLength;
	string word;
};

void OCDsimulator(string filename) {
	//declare variables
	ifstream ifs;
	ifs.open(filename);
	bool swapped, spaceFlag;
	string curWord = "", curLine = "";
	int wordCount = 0, wordL = 0;
	ofstream ofs("alpha.txt");
	//getting each line in the file
	while (getline(ifs, curLine)) {
		//sets the for loop to the size of the line
		for (int i = 0; i < curLine.length(); i++) {
			
			if (isalpha(curLine.at(i))) {
				spaceFlag = false;
			}
			//if the current character is not an alphabetical letter
			if (!isalpha(curLine.at(i))) {
				//erase current character
				if (curLine.at(i) != ' ') {
					curLine.erase(i, 1);
					spaceFlag = false;
				}
				else if (spaceFlag == true) {
					curLine.erase(i, 1);
				}
				else {
					spaceFlag = true;
				}

			}
		}
		ofs << curLine << endl;
	}
	ofs.close();
	ifs.close();
	ifs.open("alpha.txt");
	ofs.open("sorted.txt");
	//group each word by length
	Word wordList[100];
	while (ifs >> curWord) {
		wordL = curWord.length();
		wordList[wordCount].wordLength = wordL;
		wordList[wordCount].word = curWord;
		wordCount++;
	}

	do {
		swapped = false;
		for (int i = 0; i < wordCount; i++) {
			if (wordList[i].wordLength > wordList[i + 1].wordLength) {
				swap(wordList[i], wordList[i + 1]);
				swapped = true;
			}
			//switch the words
			if (wordList[i].wordLength == wordList[i + 1].wordLength){
				if (wordList[i].word > wordList[i+1].word) {
					swap(wordList[i], wordList[i + 1]);
					swapped = true;
				}
		}
				//put the words alphabetically
		}
	} while (swapped);
	
	//print out the words in length and alphabetical order
	for (int i = 0; i < wordCount; i++) {
		ofs << wordList[i].word << endl;
		}
	//always close your files :)
	ofs.close();
	ifs.close();
	
}

void whitespaceReplace(string filename) {
	//declare variables
	ifstream ifs;
	ifs.open(filename);
	string wsr = "";
	int wordcount = 0;
	string word = "";
	//getting each line in the file
	while (getline(ifs, wsr)) {
		//sets the for loop to the size of the line
		for (int i = 0; i < wsr.length(); i++) {
			char curChar = wsr.at(i);
			//if the current character is not an alphabetical letter
			if (!isalpha(curChar)) {
				//set the current character to a whitespace
				curChar = ' ';
			}
			//set the character at i to the current character
			wsr.at(i) = curChar;
		}
		//print out current line
		cout << wsr << endl;

	}
	ifs.close();
}

string lastlongestword(string filename) {
	//declare variables
	ifstream ifs;
	ifs.open(filename);
	string llw = "";
	int wordcount = 0;
	// set word to empty string
	string word = "";
	//set longestword integer to 0;
	int longestWord = 0;
	while (ifs >> word) {
		int wordlength = word.length();
		//if the length of the current word is longer than the longest word
		if (wordlength > longestWord) {
			//set the return word to the current word and 
			//set the longestword number to current length
			llw = word;
			longestWord = wordlength;
		}
		//if the longest word length and the current word length are the same
		else if (wordlength == longestWord) {
			//check for alphabetical order
			if (word.compare(llw) > 0) {
				llw = word;
			}
		}
		else continue;
		for (int i = 0; i < llw.length(); i++) {
			//if the current character is not an alphabetical letter
			if (!isalpha(llw.at(i))) {
				//delete current character
				llw.erase(i, 1);
			}
		}
	}
	return llw;
}

int wordcount(string filename) {
	//declare variables
	int wordcount = 0;
	string word = "", wsr = "";
	ifstream ifs;
	ifs.open(filename);
	ofstream ofs("output.txt");
	//getting each line in the file
	while (getline(ifs, word)) {
		//sets the for loop to the size of the line
		for (int i = 0; i < word.length(); i++) {
			//if the current character is not an alphabetical letter
			if (!isalpha(word.at(i))) {
				//erase current character
				if (word.at(i) != ' ') {
					word.erase(i, 1);
				}
				
			}
		}
		ofs << word << endl;
	}
	ifs.close();
	ofs.close();
	ifs.open("output.txt");
	//read eachword
	while (ifs >> word) {
		for (int i = 0; i < word.length(); i++) {
			if (isalpha(word[i])) {
				wordcount++;
				break;
			}
		}
	}
		
	ifs.close();
	return wordcount;
}

int menu() {
	int num = -1;
	cout << "--------------------------------------------------------------" << endl;
	cout << "Please make your choice:" << endl;
	cout << " 0 - Exit" << endl;
	cout << " 1 - Word count" << endl;
	cout << " 2 - Find the longest word that appears the last alphabetically" << endl;
	cout << " 3 - Replace all none alphabetical characters with whitespaces and output the new text on screen" << endl;
	cout << " 4 - Output all words in order of their lengths and alphabetically" << endl;
	cout << "--------------------------------------------------------------" << endl;
	cin >> num;

	return num;
}


int main() {
	string fileName, llw;
	cin >> fileName;
	int menuNum;
	bool menuFlag = false;
	ifstream ifs;
	ifs.open(fileName);
	if (!ifs.is_open()) {
		cout << "File not found!" << endl;
		return -1;
	}

	while (!menuFlag) {
		int userChoice = menu();
		
		switch(userChoice) {
			case 0: {
				menuFlag = true;
				break;
			}
			case 1: {
				int count = wordcount(fileName);
				cout << "The number of words in the text is " << count << endl;
				break;
			}
			case 2: {
				llw = lastlongestword(fileName);
				cout << "The longest word that appears the last alphabetically is " << llw << endl;
				break;
			}
			case 3: {
				whitespaceReplace(fileName);
				break;
			}
			case 4: {
				OCDsimulator(fileName);
				break;
			}
			default: {
				cout << "Please only enter 0, 1, 2, 3, or 4!" << endl;
				break;
			}
		}
	}
	//always close your files :)
	ifs.close();

	return 0;
}
