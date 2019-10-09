#include "../includes_usr/fileIO.h"


#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;



/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
fstream fileStream;
int loadBooks(std::vector<book> &books, const char* filename)
{
	fileStream.open(filename);
	books.clear();
	if (fileStream.is_open()) {

	   std::ifstream myfile(filename);

	   std::string line;

	   while (!myfile.eof()) {
		   book tempbook;
		   getline(myfile, line, ',');
		   if(line.length()==0){
		   		   break;
		   }
		   tempbook.book_id=stoi(line,0);
		   getline(myfile, line, ',');
		   tempbook.title=line;
		   getline(myfile, line, ',');
		   tempbook.author=line;
		   getline(myfile, line, ',');
		   int num = stoi(line,0);
		   switch(num){
		   case 0:
			   tempbook.state=UNKNOWN;
			   break;
		   case 1:
		   		   tempbook.state=IN;
		   		   break;
		   case 2:
		   		   tempbook.state=OUT;
		   		   break;

	   }
		   getline(myfile, line);
		   tempbook.loaned_to_patron_id=stoi(line,0);

		   books.push_back(tempbook);
	   }


	   if (books.size() == 0) {

	     //  cout << "No Books in Library";

	       return NO_BOOKS_IN_LIBRARY;

	   }

	}
	else {

	   //cout << "Error opening the file";

	   return COULD_NOT_OPEN_FILE;

	}

	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename)
{
	ofstream out;

		//open input file name filename

		out.open(filename);

		//check if file open

		if (out.is_open()){
			for(book b: books){
				out << to_string(b.book_id) << ","
						<< b.title << ","
						<< b.author << ","
						<< to_string(b.state) << ","
						<< to_string(b.loaned_to_patron_id) << "\n";
			}
		} else{
			return COULD_NOT_OPEN_FILE;
		}
		return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename)
{
	fileStream.open(filename);
		patrons.clear();

		if (fileStream.is_open()) {

		   std::ifstream myfile(filename);

		   std::string line;

		   while (!myfile.eof()) {
			   patron temppat;
			   getline(myfile, line, ',');
			  // cout << line <<endl;
			   if(line.length()==0){
			   		   break;
			   }
			   temppat.patron_id=stoi(line,0);
			   getline(myfile, line, ',');
			   //cout << line <<endl;
			   temppat.name=line;
			   getline(myfile, line);
			   //cout << line <<endl;
			   temppat.number_books_checked_out=stoi(line,0);
			   patrons.push_back(temppat);
		   }
		} else{
		   return COULD_NOT_OPEN_FILE;
		}
		if (patrons.size() == 0) {
			return NO_PATRONS_IN_LIBRARY;
		}
		return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename)
{
	ofstream out;

			//open input file name filename

			out.open(filename);

			//check if file open

			if (out.is_open()){
				for(patron p : patrons){
					out << to_string(p.patron_id) << ","
							<< p.name << ","
							<< to_string(p.number_books_checked_out) << "\n";
				}
			} else{
				return COULD_NOT_OPEN_FILE;
			}
			return SUCCESS;
}


