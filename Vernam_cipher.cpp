#include<iostream>
#include<vector>

// #define MAX_M_LENGTH 100

std::vector<bool> enc( std::vector<bool> m, std::vector<bool> key ) {
  using namespace std;
  vector<bool>::iterator it_m, it_key;
  vector<bool> res;
  for ( it_m = m.begin(), it_key = key.begin();
	it_m != m.end(); it_m++ ) {
    if ( it_key == key.end() ) {
      res.push_back( *it_m );
    } else {
      res.push_back( *it_m ^ *it_key );
      it_key++;
    }
  }
  return res;
}

bool dec( std::vector<bool>& m, std::vector<bool> c, std::vector<bool> key ) {
  using namespace std;
  vector<bool>::iterator it_c, it_key;
  vector<bool>::iterator it_m;
  m.clear();
  for ( it_c = c.begin(), it_key = key.begin();
	it_c != c.end(); it_c++ ) {
    if ( it_key == key.end() ) {
      return false;
    } else {
      m.push_back( *it_c ^ *it_key );
      it_key++;
    }
  }
  return true;
}

std::vector<bool> s_to_b ( std::string str ) {
  using namespace std;
  vector<bool> res;
  string::iterator it_str;
  for ( it_str = str.begin(); it_str != str.end(); it_str++ ) {
    res.push_back( *it_str != '0' );
  }
  return res;
}

int main( int argc, char* argv[] ) {
  std::string input_m;
  std::string::iterator it_input_m;
  std::string input_key;
  std::string::iterator it_input_key;
  std::vector<bool> m;
  std::vector<bool>::iterator it_m;
  std::vector<bool> key;
  std::vector<bool>::iterator it_key;
  std::vector<bool> c;
  std::vector<bool>::iterator it_c;
  std::cin >> input_m;
  m = s_to_b( input_m );
  std::cin >> input_key;
  key = s_to_b( input_key );
  c = enc( m, key );
  for ( it_c = c.begin(); it_c != c.end(); it_c++ ) {
    std::cout << *it_c;
  }
  std::cout << std::endl;
  return 0;
}

