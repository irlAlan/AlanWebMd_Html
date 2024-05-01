#include <iostream>
#include <memory>
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
void print(T ...args){
	auto printArg{
		[](const auto &arg){std::cout << arg;}
	};
	(printArg(args), ...);
}

void html_converter_callback(const MD_CHAR* text, MD_SIZE text_size, void* arg){
  static_cast<std::string*>(arg)->append(text, text_size);
};

void convert_to_html(std::string text, std::string *html_output){
    md_html(text.c_str(), text.length(), html_converter_callback
            , html_output, MD_FLAG_TABLES | MD_FLAG_UNDERLINE | MD_FLAG_TABLES | MD_FLAG_LATEXMATHSPANS, 0);
}


int main(int argc, char **argv){
  namespace fs = std::filesystem;

  // create a html directory for the output files
  std::string input_directory{"../markdown-src"};
  std::string output_directory{"../web-src"}; 
  if(!fs::is_directory(output_directory)){
    fs::create_directory(output_directory);
  }

  // loop through the input directory and convert to html
  for(const auto& files : fs::recursive_directory_iterator(input_directory)){
    std::fstream md_file{files.path().string(), std::ios::in};
    std::string md_line;
    std::stringstream md_buff;
    while(std::getline(md_file, md_line)){
      md_buff << md_line << '\n';
    }
    md_file.close();
    std::string markdownInput{md_buff.str()};
    std::string htmlOutput;
    convert_to_html(markdownInput, &htmlOutput);
    std::string html_filepath{files.path().string()};
    html_filepath.erase(0, html_filepath.find_last_of('/')); // get rid of original path
    html_filepath.erase(html_filepath.find_first_of('.'), html_filepath.find_last_of('d')); // get rid of extension
    html_filepath.erase(html_filepath.begin());
    html_filepath.append(".html");

    // open up template and copy it into a vector of strings 
    std::fstream html_template_file{"../templates/template.html", std::ios::in};
    std::string html_template_line;
    std::vector<std::string> html_template_data;
    while(std::getline(html_template_file, html_template_line)){
      html_template_data.push_back(html_template_line);
    }


    std::fstream css_template_file{"../templates/template.css", std::ios::in};
    std::fstream css_style_file{"../web-src/style/style.css", std::ios::out};
    std::string template_css_line{};
    while(std::getline(css_template_file, template_css_line)){
      css_style_file << template_css_line << '\n';
    }
    css_template_file.close();
    css_style_file.close();


    std::vector<std::string> html_data_out;
    std::string val;
    std::stringstream ss(htmlOutput);
    while(std::getline(ss, val)){
      html_data_out.push_back(val);
    }

    std::vector<std::string> finalOutput;
    for(std::string line : html_template_data){
      if( line == "    </header>"){
        finalOutput.push_back(line);
        for(const auto& i : html_data_out){
          finalOutput.push_back(i);
        }
      } else{
        finalOutput.push_back(line);
      }
    }

    std::fstream html_file{output_directory+"/"+html_filepath, std::ios::out};
    for(const auto& val : finalOutput){
      html_file << val << '\n';
    }
    html_file.close();

  }
  return 0;
}
