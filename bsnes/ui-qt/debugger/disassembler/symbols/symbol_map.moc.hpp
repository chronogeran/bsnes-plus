#ifndef __SYMBOL_MAP__H__
#define __SYMBOL_MAP__H__

class SymbolFileAdapters;
class SymbolFileInterface;

struct Symbol {
  enum Type { INVALID, LOCATION, COMMENT };

  static Symbol createInvalid() {
    Symbol s;
    s.type = INVALID;
    return s;
  }

  static Symbol createComment(const string &name) {
    Symbol s;
    s.type = COMMENT;
    s.name = name;
    return s;
  }

  static Symbol createLocation(const string &name) {
    Symbol s;
    s.type = LOCATION;
    s.name = name;
    return s;
  }

  inline bool isInvalid() const {
    return type == INVALID;
  }

  inline bool isSymbol() const {
    return type == LOCATION;
  }

  inline bool isComment() const {
    return type == COMMENT;
  }

  string name;
  Type type;
};

struct Symbols {
  typedef nall::linear_vector<Symbol> SymbolList;

  uint32_t address;
  SymbolList symbols;

  Symbol getSymbol();
  Symbol getComment();

  bool operator <(const Symbols &other) {
    return address < other.address;
  }
};

class SymbolMap : public QObject {
  Q_OBJECT

public:
  SymbolMap();

  typedef nall::linear_vector<Symbols> SymbolsLists;

  void reset();
  void addLocation(uint32_t address, const string &name);
  void addComment(uint32_t address, const string &name);
  void addSymbol(uint32_t address, const Symbol &name);
  void removeSymbol(uint32_t address, Symbol::Type type);
  bool loadFromString(const string &file);
  bool loadFromFile(const string &baseName, const string &ext = "");
  bool saveToFile(const string &baseName, const string &ext = "");
  void finishUpdates();

  void revalidate();

  int32_t getSymbolIndex(uint32_t address);
  Symbol getSymbol(uint32_t address);
  Symbol getComment(uint32_t address);

  bool isValid;
  bool isModified;
  SymbolsLists symbols;
  SymbolFileAdapters *adapters;
  SymbolFileInterface *adapter;

signals:
  void updated();

};

#endif
