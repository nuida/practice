#include <iostream>
#include <fstream>
#include <string>
#include <NTL/ZZ.h>

NTL::ZZ str_to_ZZ( std::string& str ) {
  std::string::iterator it_str;
  NTL::ZZ res;
  for ( it_str = str.begin(); it_str != str.end(); it_str++ ) {
    res = res * 256 + unsigned(*it_str);
  }
  return res;
}

std::string ZZ_to_str( NTL::ZZ zz ) {
  std::string res;
  while ( zz > 0 ) {
    res.insert( res.begin(), char( zz % 256 ) );
    zz /= 256;
  }
  return res;
}

int main( int argc, char* argv[] ) {
  NTL::ZZ a;
  std::string input_str;
  //  std::cin >> a;
  //  std::cout << a/sizeof(unsigned char) << std::endl;
  std::cin >> input_str;
  std::cout << str_to_ZZ( input_str ) << std::endl;
  std::cin >> a;
  std::cout << ZZ_to_str( a ) << std::endl;
  //  std::cout << unsigned(*input_str.begin()) << std::endl;
  return 0;
}
