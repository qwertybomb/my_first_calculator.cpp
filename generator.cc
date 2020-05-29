#include <iostream>
#include <fstream>
void get_formated_string(const ptrdiff_t& num1,const ptrdiff_t& num2,const char& op,char resulting_string[],const bool& first) {
    //floating point numbers only need to be printed if '/' is being used
    if(op ^ '/'){
    ptrdiff_t result = op=='+'?num1+num2:op=='-'?num1-num2:op=='*'?num1*num2:-1;
    sprintf(resulting_string,"%s(num1 == %td && sign == '%c' && num2 == %td) \n"
                       "    std::cout << %td << '%c' << %td << \" = \" << %td << std::endl;\n", first?"if":"else if", num1,op,num2,num1,op,num2,result);
    }
    else {
    //prevent 0/0
    double result = num1&&num2?num1/static_cast<double>(num2):0;
    sprintf(resulting_string,"%s(num1 == %td && sign == '%c' && num2 == %td) \n"
                       "    std::cout << %td << '/' << %td << \" = \" << %F << std::endl;\n", first?"if":"else if", num1,op,num2,num1,num2,result);
    }
}

int main() {
   constexpr size_t min = 0;
   constexpr size_t max = 50;
   const char signs[] = "+-*/";
   char if_statment[200];
   //open file
   std::ofstream output_file("my_first_calculator.cpp");
   char output_cpp[450];
   sprintf(&output_cpp[0],"#include<iostream>\n\n"
   "int main() { \n"
   "int num1, num2;\n"
   "char sign;\n"
   "std::cout << \"Welcome to this calculator\" << std::endl;\n"
   "std::cout << \"It can add, subtract, multiply and divide whole numbers from %zu to %zu\" << std::endl;\n"
   "std::cout << \"Please choose your first number: \";\n"
   "std::cin >> num1;\n"
   "std::cout << \"What do you want to do? +, -, /, or *: \";\n"
   "std::cin >> sign;\n"
   "std::cout << \"Please choose your second number: \";\n"
   "std::cin >> num2;\n",min,max);
   output_file << output_cpp << '\n';
   for(int i = 0; i < 4; ++i) {
    for(ptrdiff_t num1 = min; static_cast<size_t>(num1) <= max; ++num1){
        for(ptrdiff_t num2 = min; static_cast<size_t>(num2) <= max; ++num2){
        get_formated_string(num1,num2,signs[i],if_statment,!i&&!num1&&!num2);
        output_file << if_statment;
       }
     }
  }
  output_file << "std::cout << \"Thanks for using this calculator, goodbye :)\" << std::endl;\n\n}";
  output_file.close();

    return EXIT_SUCCESS;
}
