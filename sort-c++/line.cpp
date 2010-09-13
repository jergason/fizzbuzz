#include "line.h"

using namespace std;

Line::Line() {
	return;
}

//TODO constructor like in class
Line::Line(char * lineOrig, int oColumnNum) {
	columnNum = oColumnNum;
	comparable = true;
	line = new char[strlen(lineOrig)+1];
	strcpy(line,lineOrig);
}

Line::~Line() {
	return;
}

void Line::parseLine() {
	char * lineOrig = new char[strlen(line) +1];
	strcpy(lineOrig, line);
	char * columnOrig = strtok(lineOrig, LINE_DELIMS);
	if ( columnOrig == NULL ) {
		column = NULL;
		delete lineOrig;
		return;
	}
	if (columnNum > 1) {
		for (int i = 1; i < columnNum; ++i) {
			columnOrig = strtok(NULL, LINE_DELIMS);
			if (columnOrig == NULL) {
				comparable = false;
				break;
			}
		}
	}
	if (comparable) {
		column = new char[strlen(columnOrig)+1];
		strcpy(column, columnOrig);
		//cout << columnOrig << endl;
	} else
		column = NULL;
	delete lineOrig;
}

bool Line::isComparable() {
	return comparable;
}

char *	Line::getColumn() const{
	return column;
}

void Line::printLine() {
	cout << line << endl;
}