#include <iostream>
#include <fstream>
#include <string>
#include <NTL/ZZ.h>
#include <vector>

NTL::ZZ str_to_ZZ( std::string& str ) {
  std::string::iterator it_str;
  NTL::ZZ res;
  for ( it_str = str.begin(); it_str != str.end(); it_str++ ) {
    res = res * 256 + unsigned(*it_str);
  }
  return res;
}

std::vector< NTL::ZZ > str_to_ZZtuple ( std::string& str, unsigned bitlength ) {
  std::vector< NTL::ZZ > res;
  NTL::ZZ res_cur;
  std::string::iterator it_str;
  int i, char_max;
  const unsigned bytes = (bitlength - 1) / (sizeof(char) * 8);

  char_max = 1;
  for ( i = 0; i < sizeof(char) * 8; i++ ) {
    char_max *= 2;
  }
  it_str = str.begin();
  while ( it_str != str.end() ) {
    res_cur = 0;
    for ( i = 0; i < bytes && it_str != str.end() ; i++, it_str++ ) {
      res_cur = res_cur * char_max + unsigned( *it_str );
    }
    res.push_back( res_cur );
  }
  return res;
}

std::vector< NTL::ZZ > file_to_ZZtuple ( std::ifstream& fin, unsigned bitlength ) {
  std::vector< NTL::ZZ > res;
  NTL::ZZ res_cur;
  int i, char_max;
  const unsigned bytes = (bitlength - 1) / (sizeof(char) * 8);
  char in_char;

  char_max = 1;
  for ( i = 0; i < sizeof(char) * 8; i++ ) {
    char_max *= 2;
  }
  res_cur = 0;
  i = 0;
  while ( fin.get( in_char ) ) {
    if ( i < bytes ) {
      res_cur = res_cur * char_max + unsigned( in_char );
      ++i;
    } else {
      res.push_back( res_cur );
      res_cur = unsigned( in_char );
      i = 1;
    }
  }
  res.push_back( res_cur );
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

  NTL::ZZ a, n;
  while ( !( std::cin >> n ) ) {}
  a = NTL::RandomBnd(n);
  std::cout << a << std::endl;

  return 0;

  // temporarily disabled below
  std::string ifile_name, ofile_name;
  unsigned bitlength;
  std::vector< NTL::ZZ > zz_tuple;
  std::vector< NTL::ZZ >::iterator it_zz_tuple;

  std::cout << "bit length of N = ? ";
  std::cin >> bitlength;
  //  std::cout << "input file name = ? ";
  //  std::cin >> ifile_name;
  ifile_name = "NTL_practice_input.dat";
  std::ifstream fin( ifile_name.c_str(), std::ios::in );
  if ( !fin ) {
    std::cerr << "Can't open the file: " << ifile_name << std::endl;
    return 1;
  }
  zz_tuple = file_to_ZZtuple( fin, bitlength );
  /*
  for ( it_zz_tuple = zz_tuple.begin();
	it_zz_tuple != zz_tuple.end(); it_zz_tuple++ ) {
    std::cout << *it_zz_tuple << std::endl;
  }
  */
  ofile_name = "NTL_practice_output.dat";
  std::ofstream fout( ofile_name.c_str(), std::ios::out );
  if ( !fout ) {
    std::cerr << "Can't open the file: " << ofile_name << std::endl;
    return 1;
  }
  for ( it_zz_tuple = zz_tuple.begin();
	it_zz_tuple != zz_tuple.end(); it_zz_tuple++ ) {
    fout << *it_zz_tuple << std::endl;
  }

  return 0;
}
