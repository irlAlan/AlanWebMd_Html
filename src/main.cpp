#include <cstring>
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <string>
#include <md4c.h>
#include <md4c-html.h>

template<typename ...T>
void print(std::ostream &out, T ...args){
	auto printArg{
		[&out](const auto &arg){out << arg;}
	};
	(printArg(args), ...);
}

// being a pain in the arse so ill sort it some other time
void p(const MD_CHAR* input, MD_SIZE input_size, void* arg){
  std::string new_file{*(static_cast<std::string*>(arg))};
  new_file.erase(new_file.find_first_of('.'), new_file.find_last_of('d'));
  //print(std::cout, new_file+".html\n");
  print(std::cout, input, '\n');
  
};


int main(int argc, char **argv){
  namespace fs = std::filesystem;

  // get all arguments into a vector
  std::vector<std::string> markdown_files(argv, argc+argv);
  markdown_files.erase(markdown_files.begin());

  // create a html directory for the output files
  std::string output_directory{"HTML"}; 
  if(!fs::is_directory(output_directory)){
    fs::create_directory(output_directory);
  }

  //open and read the files
  for(std::string file : markdown_files){
    std::fstream current_file{file, std::ios::in};
    std::stringstream markdown_input;
    std::string line;
    while(std::getline(current_file, line)){
      markdown_input << line << '\n';
    }
    std::string mInput{markdown_input.str()};
    current_file.close();
    // convert into markdown and shove it into its own html file
    // TODO: change one of the nullptrs to a function that shoves it into a file and hope it works
    // TODO: fix p
    md_html(mInput.c_str(), mInput.length(), p
            , static_cast<void*>(&file), MD_FLAG_LATEXMATHSPANS | MD_FLAG_NOHTMLBLOCKS, 0);
    
  }

	return 0;
}
