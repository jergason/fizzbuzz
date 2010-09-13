/*
 * Objective:
 * Read commandline params including options
 * Parse file line-by-line
 * Parse line column-by-column while preserving lines
 * Sort lines by column
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "line.h"

#define CLEAN 0
#define BAD_ARGS -3
#define BAD_FILE -4

#define LINES_IN_FILE 10240
#define CHARS_PER_LINE 10240
#define DELIMS " \t\n\r"
#define WHITE_SPACE " \t"


		char *	fileName;					// Input file
		char *	lines[LINES_IN_FILE];		// Input file line-by-line in array
		char *	disallowed[LINES_IN_FILE];	// Lines that match Disallowed:
		int 	curLine;					// The current line of the file
		int 	lastLine;
		int 	selectedColumn;
		int     length;						// The number of disallowed paths
		void	openFile();
		int 	parseFile();
		bool	sortInsensitive = false;
		bool	sortReverse = false;
		bool	sortNumber = false;
		int		column;
		void 	sort();
		char *	wsFix(char *);
		Line **	myLines;
//	public:
//		Sort240(int, char *, bool, bool, bool);
//		~Sort240();
		void setCaseInsensitive(bool);
		void setIntegerSort(bool);
		void setReverse(bool);
		//int *  qCompare(const void *, const void *);

//bool sortInsensitive;
//bool sortNumber = false;
//bool sortReverse = false;
//bool Sort240::sortInsensitive = false;
//bool Sort240::sortReverse = false;
//bool Sort240::sortNumber = false;
