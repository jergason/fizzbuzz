#include "sort240.h"

using namespace std;

int	qCompare( const void* m, const void* n ) {
	Line * myLineA = *((Line**) m);
	Line * myLineB = *((Line**) n);
	
	if (myLineA->getColumn() == NULL)
		return -1;
	if (myLineB->getColumn() == NULL)
		return 1;
	
	int result = 0;

	if (sortInsensitive) {
		//cout << "I" << endl;
		result = strcasecmp(myLineA->getColumn(), myLineB->getColumn());
	} else {
		if (sortNumber) {
			//cout << "N" << endl;
			result = (atoi(myLineA->getColumn()) > atoi(myLineB->getColumn())) ? 1 : -1;
		} else {
			//cout << "X" << endl;
			result = strcmp(myLineA->getColumn(), myLineB->getColumn());
		}
	}

	if (sortReverse) {
		//cout << "R" << endl;
		result *= -1;
	}
	
	/*
	cout << "\nA: " << myLineA->getColumn() << endl;
	cout << "B: " << myLineB->getColumn() << endl;
	cout << "R: " << result << endl;
	*/
	
	return result;
}

int main (int argc, char * argv[]) {
	if (argc != 3 && argc !=4) {
		cerr << "Usage: sort240 [-rni] <column> <file-path>\n" << endl;
		return BAD_ARGS;
	}
	
	int i = 1;

	if (argv[i][0] == '-') {
		int len = strlen(argv[i]);
		for (int j = 1; j < len; j++) {
			switch (argv[i][j]) {
			case 'r':
				sortReverse = true;
				break;
			case 'i':
				if (!sortNumber) {
					sortInsensitive = true;
				} else {
					//cout << "Ignoring case insensitivity for numbers." << endl;
				}
				break;
			case 'n':
				sortNumber = true;
				sortInsensitive = false;
				break;
			}
		}
		++i;
	}
	
	column = atoi(argv[i]);
	fileName = argv[++i];
	
	openFile();
	
	parseFile();
	
	qsort(myLines, length, sizeof(Line**), qCompare);
	
	for (int k = 0; k < length; ++k) {
		myLines[k]->printLine();
	}
	
	//delete sort;

	return CLEAN;
}

void openFile() {
	//cout << "Opening file" << endl;
	memset(lines, 0, sizeof(lines));
	
	// Open the file or exit
	ifstream file;	
	file.open(fileName);
	if (!file.is_open()) {
		cerr << "Unable to open file: " << fileName << "\n" << endl;
		exit(BAD_FILE);
	}
	
	// Read up to 1024 lines of 1024 char length	
	lastLine = 0;
	char line[CHARS_PER_LINE];
	char * lineCopy;
	while (file.getline(line, CHARS_PER_LINE)) {
    if ('\n' == line[0] || '\r' == line[0]) {
      continue;
    }
		lineCopy = new char[strlen(line) + 1];
		strcpy(lineCopy, line);
    if (NULL == strtok(line, "\n\t\r "))
    {
      continue;
    }
		lines[lastLine] = lineCopy;
		lastLine++;
	}
	file.close();
}

int parseFile() {
	//cout << "Parsing File" << endl;
	length = 0;
	curLine = 0;
	
	// TODO off by one?
	myLines = new Line*[lastLine];
	while (curLine < lastLine) {
		char * lineCopy = new char[strlen(lines[curLine])];
		strcpy(lineCopy, lines[curLine]);
		myLines[curLine] = new Line(lines[curLine], column);
		myLines[curLine]->parseLine();
		//cout << myLines[curLine]->getColumn() << endl;
		++curLine;
		//delete lineCopy;
	} 
	length = curLine;
}
