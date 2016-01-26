template <typename T>
bool next_vector_by_left_first( std::vector< T >& iv,
				T fst, T lst );

template <typename T>
bool prev_vector_by_left_first( std::vector< T >& iv,
				T fst, T lst );



template <typename T>
bool next_vector_by_left_first( std::vector< T >& iv,
				T fst, T lst ) {
  std::vector< T > v_tmp;
  while ( !iv.empty() ) {
    if ( iv.back() < lst ) {
      iv.back()++;
      while ( !v_tmp.empty() ) {
	v_tmp.pop_back();
	iv.push_back( fst );
      }
      return true;
    }
    v_tmp.push_back( iv.back() );
    iv.pop_back();
  }
  while ( !v_tmp.empty() ) {
    iv.push_back( v_tmp.back() );
    v_tmp.pop_back();
  }
  return false;
}

template <typename T>
bool prev_vector_by_left_first( std::vector< T >& iv,
				T fst, T lst ) {
  std::vector< T > v_tmp;
  while ( !iv.empty() ) {
    if ( iv.back() > fst ) {
      iv.back()--;
      while ( !v_tmp.empty() ) {
	v_tmp.pop_back();
	iv.push_back( lst );
      }
      return true;
    }
    v_tmp.push_back( iv.back() );
    iv.pop_back();
  }
  while ( !v_tmp.empty() ) {
    iv.push_back( v_tmp.back() );
    v_tmp.pop_back();
  }
  return false;
}
