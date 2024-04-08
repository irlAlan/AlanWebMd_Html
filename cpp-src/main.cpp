#include <algorithm>
#include <cctype>
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <string>
#include <md4c.h>
#include <md4c-html.h>
#include <md2.h>

/**
 * TODO: 
 *  - [ ] Finalise the templates and their locations
 *  - [ ] Finalise template design
 *  - [ ] Refactor the code and actually make it good
*/

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
            , html_output, MD_FLAG_TABLES | MD_FLAG_UNDERLINE | MD_FLAG_TABLES | MD_FLAG_LATEXMATHSPANS, 0);
}


int main(int argc, char **argv){
  namespace fs = std::filesystem;

  std::vector<std::string> arguments(argv, argc+argv);
  arguments.erase(arguments.begin());

  // create a html directory for the output files
  std::string input_directory{"../markdown-src"};
  std::string output_directory{"../web-src"}; 
  if(!fs::is_directory(output_directory)){
    fs::create_directory(output_directory);
  }

  for(const auto& files : fs::recursive_directory_iterator(input_directory)){
    std::fstream md_file{files.path().string(), std::ios::in};
    std::string line;
    std::stringstream buff;
    while(std::getline(md_file, line)){
      buff << line << '\n';
    }
    md_file.close();
    std::string markdownInput{buff.str()};
    std::string htmlOutput;
    convert_to_html(markdownInput, &htmlOutput);
    std::string filepath{files.path().string()};
    filepath.erase(0, filepath.find_last_of('/')); // get rid of original path
    filepath.erase(filepath.find_first_of('.'), filepath.find_last_of('d')); // get rid of extension
    filepath.erase(filepath.begin());
    filepath.append(".html");

    print(std::cout, filepath, '\n');

    // open up template and copy it into a vector of strings 
    std::fstream template_file{"../templates/template.html", std::ios::in};
    std::string template_line;
    std::vector<std::string> template_data;
    while(std::getline(template_file, template_line)){
      template_data.push_back(template_line);
    }


    std::vector<std::string> html_data_out;
    std::string val;
    std::stringstream ss(htmlOutput);
    while(std::getline(ss, val)){
      html_data_out.push_back(val);
    }

    std::vector<std::string> finalOutput;
    for(std::string line : template_data){
      print(std::cout, line, '\n');
      if( line == "  <body>"){
        finalOutput.push_back(line);
        for(const auto& i : html_data_out){
          finalOutput.push_back(i);
        }
      } else{
        finalOutput.push_back(line);
      }
    }

    std::fstream html_file{output_directory+"/"+filepath, std::ios::out};
    // html_file << htmlOutput;
    for(const auto& val : finalOutput){
      html_file << val << '\n';
    }
    html_file.close();

    print(std::cout, '\n');

  }

  return 0;
}
