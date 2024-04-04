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
    md_html(mInput.c_str(), mInput.length(), nullptr, nullptr, MD_FLAG_LATEXMATHSPANS | MD_FLAG_NOHTMLBLOCKS, 0);
    
  }

	return 0;
}
