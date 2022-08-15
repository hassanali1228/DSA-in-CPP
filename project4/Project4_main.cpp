#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <list>
#include <deque>

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
	
	std::list < std::list < std::string > > files;
	std::list < std::string > current;					//keep track of current file, we are pushing neighbors

	//first element of list is the key, where all the other elements after in list are neighbors of first element
		//for example, where a points to b, c, and b points to c:
			//{ {a, b, c} , {b, c} } = files  : list of lists

	std::string line;
	std::string key = "#";

	bool check = 0;

	while(std::getline(fin,line))
	{

		if(line[0] != key[0]){		//if it is a file

			if (current.size() != 0) files.push_back(current);

			current.clear();
			
			current.push_back(line);	//start of all adjacency lists

		}
		
		else {			//if it is #include <>

			std::string temp = line.substr(10);		//substring: c++ libraries or files
			temp = temp.substr(0, temp.size()-1);

			current.push_back(temp);
			
		}

	}

	files.push_back(current);

	std::deque < std::string > stack;	
	std::list < std::string > visited;
	check = 0;

	for (auto i = files.begin(); i != files.end(); ++i){
		
		check = 0;

		for (auto x = visited.begin(); x != visited.end(); ++x){	//check if file has been visited

			if ( *x == *( i->begin() ) ){
						
				check = 1;
				break;

			}
			
		}

		if (check == 0) findOrder( stack, visited, *( i->begin() ), files );

	}
	
	// for (int i = 0; i < stack.size(); ++i){		//print result
	// 	std::cout << stack[i] << std::endl;
	// }
	
	return EXIT_SUCCESS;
}

void findOrder ( std::deque < std::string > & stack, std::list < std::string > & visited, std::string & file, std::list < std::list < std::string > > & files ){

	visited.push_back(file);		//add key to visited

	bool check = 0;

	for (auto i = files.begin(); i != files.end(); ++i){
		
		if (file == *( i->begin() )){					//file passed in is found

			for (auto j = ++( i->begin() ); j != ( i->end() ); ++j){		//iterate through elements file points to

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

	std::cout << file << std::endl;	//add to stack

}