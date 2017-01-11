#include<iostream>

int main(int argc, char* argv[]) {
  int diff_year = 1988;
  int current_heisei;
  int res[2];
  int i;
  bool flg;
  current_heisei = 28;
  for (i=0; i<2; ++i) {
    flg = true;
    while(flg) {
      if ( (current_heisei + diff_year) % current_heisei == 0 ) {
	res[i] = current_heisei;
	flg = false;
      }
      ++current_heisei;
    }
  }
  std::cout << "(" << res[0] << "," << res[0] + diff_year << "), ("
	    << res[1] << "," << res[1] + diff_year << ")" << std::endl;
  return 0;
}

