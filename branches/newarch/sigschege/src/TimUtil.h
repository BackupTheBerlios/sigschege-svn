


template <class Type> class Range {
  public:
  Range() {}
  Range(Type start, Type end) {
    cStart = start;
    cEnd = end;
  }

  Type distance(void) { return cEnd-cStart; }
  bool contains(Type val) { return (val>=cStart && val<=cEnd); }

  Type cStart;
  Type cEnd;
};
