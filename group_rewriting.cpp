#include<iostream>
#include<fstream>
#include<vector>
#include<deque>
#include<string>
#include <sstream>

template <typename T> std::string tostr( const T& t )
{
    std::ostringstream os;
    os << t;
    return os.str();
}

class StringGenerators{
public:
  int id; // identify the generating set
  std::vector< std::string > gen_names; // tuple of displayed names of generators, beginning at 0-th position
  std::string error_symbol;

  StringGenerators();

  void set_id( int ); // give the identification number
  bool add( std::string ); // add new generator (specified by name string) to the tuple
  std::string read( int ); // return the (int)-th generator's name
  int read_id(); // return the ID of the generating set
};

class ElementExpression{
public:
  std::deque< std::pair< int, int > > element; // sequence of generators (denoted by number) and exponents

  ElementExpression(); // empty expression
  ElementExpression( int, int ); // initialize by a power of a single generator

  std::string read(); // return the expression of the element
  void MultiplyFromLeftBy( ElementExpression ); // multiply by the input element from left
  void MultiplyFromLeftBy( int, int ); // multiply by the input element (a power of a single generator) from left
  void MultiplyFromRightBy( ElementExpression ); // multiply by the input element from right
  void MultiplyFromRightBy( int, int ); // multiply by the input element (a power of a single generator) from right
  ElementExpression operator*( const ElementExpression& ) const; // multiplication operator
  ElementExpression InverseOf(); // return the inverse of the element
  void ToInverse(); // convert to its inverse element
};

std::ostream& operator<<( std::ostream&, const ElementExpression& ); // output the expression of the element

class ElementRelations{
public:
  std::vector< std::pair< ElementExpression, ElementExpression > > equality; // list of equality relations
  std::vector< std::pair< ElementExpression, ElementExpression > > rewriting; // list of rewriting rules (from left to right)

  void InsertEquality( ElementExpression, ElementExpression ); // add a new equality relation
  void InsertRewriting( ElementExpression, ElementExpression ); // add a new rewriting relation

/*
  ElementExpression(); // empty expression
  ElementExpression( int, int ); // initialize by a power of a single generator

  std::deque< std::pair< int, int > > element; // sequence of generators (denoted by number) and exponents

  std::string read(); // return the expression of the element
  void MultiplyFromLeftBy( ElementExpression ); // multiply by the input element from left
  void MultiplyFromLeftBy( int, int ); // multiply by the input element (a power of a single generator) from left
  void MultiplyFromRightBy( ElementExpression ); // multiply by the input element from right
  void MultiplyFromRightBy( int, int ); // multiply by the input element (a power of a single generator) from right
  ElementExpression operator*( const ElementExpression& ) const; // multiplication operator
  ElementExpression InverseOf(); // return the inverse of the element
  void ToInverse(); // convert to its inverse element
*/
};


//
// definitions for StringGenerators
//

StringGenerators::StringGenerators() {
  this->error_symbol = std::string("error");
}

void StringGenerators::set_id( int i ) {
  this->id = i;
}

bool StringGenerators::add( std::string name ) {
  if ( name == this->error_symbol ) {
    return false;
  }
  this->gen_names.push_back( name );
  return true;
}

std::string StringGenerators::read( int i ) {
  if ( i > this->gen_names.size() ) {
    return this->error_symbol;
  }
  return this->gen_names.at(i);
}

int StringGenerators::read_id() {
  return this->id;
}

//
// definitions for ElementExpression
//

ElementExpression::ElementExpression() {}

ElementExpression::ElementExpression( int idx, int e ) {
  this->element.push_back( std::pair< int, int >( idx, e ) );
}

std::string ElementExpression::read() {
  std::string res;
  std::deque< std::pair< int, int > >::iterator it;
  for ( it = this->element.begin(); it != this->element.end(); ++it ) {
    if ( it != this->element.begin() ) {
      res += std::string(" ");
    }
    res += std::string( tostr( it->first ) )
      + std::string("^")
      + std::string( tostr( it->second ) );
  }
  return res;
}

std::ostream& operator<<( std::ostream& os, const ElementExpression& elm ) {
  std::deque< std::pair< int, int > >::const_iterator it;
  for ( it = elm.element.begin(); it != elm.element.end(); ++it ) {
    if ( it != elm.element.begin() ) {
      os << std::string(" ");
    }
    os << std::string( tostr( it->first ) )
      + std::string("^")
      + std::string( tostr( it->second ) );
  }
  return os;
}

void ElementExpression::MultiplyFromLeftBy( ElementExpression elm ) {
  bool b = true;

  while ( b ) {
    if ( this->element.empty() || elm.element.empty() || this->element.front().first != elm.element.back().first ) {
      b = false;
    } else {
      this->element.front().second += elm.element.back().second;
      elm.element.pop_back();
      if ( this->element.front().second == 0 ) {
	this->element.pop_front();
      }
    }
  }
  while ( !elm.element.empty() ) {
    this->element.push_front( elm.element.back() );
    elm.element.pop_back();
  }
}

void ElementExpression::MultiplyFromLeftBy( int idx, int e ) {
  this->MultiplyFromLeftBy( ElementExpression( idx, e ) );
}

void ElementExpression::MultiplyFromRightBy( ElementExpression elm ) {
  bool b = true;

  while ( b ) {
    if ( this->element.empty() || elm.element.empty() || this->element.back().first != elm.element.front().first ) {
      b = false;
    } else {
      this->element.back().second += elm.element.front().second;
      elm.element.pop_front();
      if ( this->element.back().second == 0 ) {
	this->element.pop_back();
      }
    }
  }
  while ( !elm.element.empty() ) {
    this->element.push_back( elm.element.front() );
    elm.element.pop_front();
  }
}

void ElementExpression::MultiplyFromRightBy( int idx, int e ) {
  this->MultiplyFromRightBy( ElementExpression( idx, e ) );
}

ElementExpression ElementExpression::operator*( const ElementExpression& elm ) const {
  ElementExpression res(*this);
  res.MultiplyFromRightBy( elm );
  return res;
}

ElementExpression ElementExpression::InverseOf() {
  ElementExpression res;
  std::deque< std::pair< int, int > >::iterator it;
  for ( it = this->element.begin(); it != this->element.end(); ++it ) {
    res.MultiplyFromLeftBy( it->first, -it->second );
  }
  return res;
}

void ElementExpression::ToInverse() {
  (*this) = this->InverseOf();
}

//
// definitions for ElementRelations
//

void ElementRelations::InsertEquality( ElementExpression ex1, ElementExpression ex2 ){

}

/*
class ElementRelations
public:
  std::vector< std::pair< ElementExpression, ElementExpression > > equality; // list of equality relations
  std::vector< std::pair< ElementExpression, ElementExpression > > rewriting; // list of rewriting rules (from left to right)

  void InsertEquality( ElementExpression, ElementExpression ); // add a new equality relation
  void InsertRewriting( ElementExpression, ElementExpression ); // add a new rewriting relation
*/

//
// main
//

int main( int argc, char* argv[] ) {
  StringGenerators gen;

  ElementExpression elm( 1, 3 );
  ElementExpression elm2( 2, -3 );
  ElementExpression elm3;

  elm.MultiplyFromLeftBy( 2, -2 );
  elm.MultiplyFromRightBy( ElementExpression( 2, 3 ) );
  elm2.MultiplyFromRightBy( ElementExpression( 1, -3 ) );
  elm.MultiplyFromRightBy( elm2 );

  std::cout << gen.read(3) << std::endl;
  std::cout << elm3 << std::endl;
  std::cout << elm << std::endl;
  std::cout << elm2 << std::endl;
  elm3 = elm * elm2;
  std::cout << elm3 << std::endl;  
  elm3 = elm3.InverseOf();
  std::cout << elm3 << std::endl;  
  elm3.ToInverse();
  std::cout << elm3 << std::endl;  

  return 0;
}


/*
class StringWithRelations{
  
}
*/


/*
bool enc( std::vector<bool>& c, std::vector<bool> m, std::vector<bool> key ) {
  using namespace std;
  vector<bool>::iterator it_m, it_key;
  c.clear();
  for ( it_m = m.begin(), it_key = key.begin();
	it_m != m.end(); it_m++ ) {
    if ( it_key == key.end() ) {
      cerr << "Too short encryption key: Abort." << endl;
      return false;
    } else {
      c.push_back( *it_m ^ *it_key );
      it_key++;
    }
  }
  return true;
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
  std::string input_key;
  std::string::iterator it_input_key;
  std::vector<bool> m;
  std::vector<bool>::iterator it_m;
  std::vector<bool> key;
  std::vector<bool>::iterator it_key;
  std::vector<bool> c;
  std::vector<bool>::iterator it_c;
  char ch;

  std::string input_file_name( "plaintext_Vernam.dat" );
  std::ifstream fin( input_file_name.c_str(), std::ios::in );
  if ( !fin ) {
    std::cerr << "Can't open the input file \""
	      << input_file_name.c_str() << "\"." << std::endl;
    return 1;
  }
  while ( fin.get(ch) ) {
    if ( ch != '\n' ) {
      m.push_back( ch != '0' );
    }
  }

  std::cout << "Input encryption key ( length >= " << m.size() << " )" << std::endl;
  std::cin >> input_key;
  key = s_to_b( input_key );

  std::string output_file_name( "ciphertext_Vernam.dat" );
  if ( enc( c, m, key ) ) {
    std::ofstream fout( output_file_name.c_str(), std::ios::app );
    if ( !fout ) {
      std::cerr << "Can't open the output file \""
		<< output_file_name.c_str() << "\"." << std::endl;
      return 1;
    }
    for ( it_c = c.begin(); it_c != c.end(); it_c++ ) {
      fout << *it_c;
    }
    fout << std::endl;
    std::cout << "Encryption succeeded: Ciphertext file \""
	      << output_file_name.c_str() << "\"." << std::endl;
  } else {
    std::cerr << "Encryption failed." << std::endl;
    return 1;
  }
  return 0;
}
*/
