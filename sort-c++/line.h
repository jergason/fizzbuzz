#include <cstring>
#include <iostream>
#include <stdlib.h>


#define LINE_DELIMS " \t\n\r"
#define MAX_LINE_LENGTH 10240

class Line {
private:
	char *	line;
	char *	column;
	bool 	comparable;
	int		columnNum;
	bool 	sortInsensitive;
	bool 	sortNumber;
	bool 	sortReverse;
public:
	Line();
	Line(char*, int);
	//Line(char*);
	~Line();
	char *	getColumn() const;
	int		compare(char *);
	//static int		qCompare(const void *, const void *);
	void	printLine();
	bool	isComparable();
	void	parseLine();
};