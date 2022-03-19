#include <snappy.h>

#include <iostream>
#include <string>
using namespace std;

int main() {
  string input = "This is snappy example.";
  string output;
  for (int i = 0; i < 5; ++i)  // loop to increase the length of input string
  {
    input += input;
  }
  snappy::Compress(input.data(), input.size(),
                   &output);  // compress input string by snappy
  cout << "input size :" << input.size() << " output size :" << output.size()
       << endl;
  string output_uncom;  // define uncompressed output string variable
  snappy::Uncompress(output.data(), output.size(),
                     &output_uncom);  // uncompress the compressed string
  if (input == output_uncom)  // compare the string before compression and
                              // uncompressed string
  {
    cout << "Equal " << endl;
  } else {
    cout << "ERROR : not equal" << endl;
  }
  return 0;
}
