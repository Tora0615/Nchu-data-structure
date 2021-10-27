#include <iostream>

int main(int argc, char const *argv[]) {
  float a;
  std::cout<<"身高\n";
  std::cin>>a;
  //std::cout<<"你身高是"<<a<<"公尺\n";

  float b;
  std::cout<<"體重\n";
  std::cin>>b;
  //std::cout<<"你體重是"<<b<<"公斤\n";

  float bmi = b/(a*a);
  std::cout<<"BMI:"<<bmi<<'\n';

  if(bmi>=24){
    std::cout << "過重" << '\n';
  }
  else if (bmi>18.5 && bmi<24) {
    std::cout << "正常" << '\n';
  }
  else if (bmi <18.5); {
    std::cout << "過輕" << '\n';
  }


  return 0;
}
