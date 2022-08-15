#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <deque>
#include <list>
#include <deque>
// #include <algorithm>

void findOrder ( std::deque < std::string > & stack, std::list < std::string > & visited, std::string & file,
					std::list < std::list < std::string > > & files );

int main(int argc, char** argv)
{
	//first input argument is always the program name...
	char* fileName = argv[1];
	
	//open the file
	std::ifstream fin(fileName);
	
	if(!fin)
	{
		std::cout<< "File not found" << std::endl;
		return EXIT_FAILURE;
	}
	
	std::list < std::string > libraries;
	std::list < std::list < std::string > > files;
	std::list < std::string > current;

	std::string line;
	std::string key = "F";

	bool check = 0;

	while(std::getline(fin,line))
	{
		
		// std::cout << "key " << line[0] << std::endl;

		if(line[0] == key[0]){

			if (current.size() != 0) files.push_back(current);

			current.clear();
			
			current.push_back(line);	//start of all adjacency lists

		}
		
		else {			//if it is #include <>

			std::string temp = line.substr(10);		//substring: c++ libraries or files
			temp = temp.substr(0, temp.size()-1);
			
			if( (temp.find(".h") == std::string::npos) 				
				//&& ( std::find(libraries.begin(), libraries.end(), temp) == libraries.end() ) 
				){ 	//c++ libraries only (no FILE keyword) and no repititions
				
				check = 0;

				for (auto x = libraries.begin(); x != libraries.end(); ++x){	//check if this library was already found

					if (temp == *x){
								
						check = 1;
						break;

					}
					
				}

				if (check == 0) {	//if not, add library to list, and print it				

					libraries.push_back(temp);
					std::cout << temp << std::endl;
					
				}
			
			} else if (temp.find(key) != std::string::npos) {		//all files needed to compile (added to adjancency lists)

				current.push_back(temp);
				
			}

		}

	}

	files.push_back(current);

	std::deque < std::string > stack;
	// stack.reserve( files.size()*2 );					// *2 because I don't trust myself
	
	std::list < std::string > visited;
	check = 0;

	for (auto i = files.begin(); i != files.end(); ++i){
		
		check = 0;
		auto temp = *i;

		for (auto x = visited.begin(); x != visited.end(); ++x){

			if (*x == *(temp.begin())){
						
				check = 1;
				break;

			}
			
		}

		if (check == 0) findOrder( stack, visited, *(temp.begin()), files );

	}
	
	for (int i = 0; i < stack.size(); ++i){
		std::cout << stack[i] << std::endl;
	}
	
	return EXIT_SUCCESS;
}

void findOrder ( std::deque < std::string > & stack, std::list < std::string > & visited, std::string & file, std::list < std::list < std::string > > & files ){

	visited.push_back(file);		//add key to visited

	bool check = 0;

	for (auto i = files.begin(); i != files.end(); ++i){
		
		if (file == *((*i).begin())){					//file passed in is found

			for (auto j = ++(*i).begin(); j != (*i).end(); ++j){		//iterate through elements file points to

				check = 0;

				for (auto x = visited.begin(); x != visited.end(); ++x){	//check if each node was visited before

					if (*x == *j){
								
						check = 1;
						break;

					}
					
				}

				if (check == 0) findOrder( stack, visited, *j, files );	//if not, recursive call to add to stack

			}

		}

	}

	stack.push_back(file);	//add to stack

}