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

void html_converter_callback(const MD_CHAR* input, MD_SIZE input_size, void* arg){
  static_cast<std::string*>(arg)->append(input, input_size);
};

void convert_to_html(std::string text, std::string *html_output){
    md_html(text.c_str(), text.length(), html_converter_callback
            , html_output, MD_FLAG_LATEXMATHSPANS | MD_FLAG_NOHTMLBLOCKS, 0);
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
    std::string html_output;
    // convert into markdown and shove it into its own html file
    convert_to_html(mInput, &html_output);
    print(std::cout, '\n', html_output);
    
  }

	return 0;
}
