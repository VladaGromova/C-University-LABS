#include <initializer_list>
#include <iostream>
#include <string>

class Stack {
 private:
  int _length = 0;
  int* _stack = nullptr;

 public:
  class Iterator {
   public:
    Iterator(const Stack* l) { lt = l; }
    void first() { index = 0; }
    void next() { ++index; }
    bool isDone() { return index == (lt->_length - 1); }
    int currentItem() { return lt->_stack[index]; }
    Iterator& operator++(int) {
      Iterator itr = *this;
      ++index;
      return itr;
    }
    Iterator& operator--(int) {
      Iterator itr = *this;
      --index;
      return itr;
    }
    bool operator==(const Iterator& itr) {
      return ((lt == itr.lt) && (index = itr.index));
    }
    bool operator!=(const Iterator& itr) {
      return !((lt == itr.lt) && (index = itr.index));
    }
    int operator*() { return this->lt->_stack[index]; }

   private:
    const Stack* lt;
    int index;
  };
  Stack();
  Stack(const std::initializer_list<int>& list);
  Stack(const Stack& s);
  Stack(Stack&& s);
  ~Stack();
  void swap(Stack& s);
  bool IsEmpty();
  int Size();
  void Clear();
  int Top();
  void Push(const int& el );
  void Pop();
  void Swap(Stack& s);
  friend std::ostream& operator<<(std::ostream& out, const Stack& s);
  friend std::istream& operator>>(std::istream& in, Stack& s);
  friend bool operator==(const Stack& s1, const Stack& s2);
  friend bool operator!=(const Stack& s1, const Stack& s2);
  Stack operator+(const Stack& s);
  Stack operator+=(const Stack& s);
  Stack& operator=(const Stack& s);
  Stack& operator=(Stack&& s);
  Iterator* createIterator() const { return new Iterator(this); }
};

Stack::Stack() {
  _length = 0;
  _stack = new int[_length];
}

Stack::Stack(const std::initializer_list<int>& list) {
  _length = list.size();
  _stack = new int[_length];
  int index = 0;
  for (auto& element : list) {
    _stack[index] = element;
    ++index;
  }
}

inline Stack::Stack(const Stack& s) {
  this->_stack = new int[s._length];
  this->_length = s._length;
  for (int i = 0; i < _length; ++i) {
    this->_stack[i] = s._stack[i];
  }
}

Stack::Stack(Stack&& s) { swap(s); }

Stack::~Stack() { delete[] _stack; }

void Stack::swap(Stack& s) {
  std::swap(this->_stack, s._stack);
  std::swap(this->_length, s._length);
}

bool Stack::IsEmpty() { return (_length == 0); }

int Stack::Size() { return _length; }

void Stack::Clear() {
  delete[] _stack;
  _stack = nullptr;
  _length = 0;
}

int Stack::Top() { return this->_stack[(this->_length - 1)]; }

void Stack::Push(const int& el) {
  int* new_stack = new int[(_length + 1)];
  for (int i = 0; i < _length; ++i) {
    new_stack[i] = _stack[i];
  }
  new_stack[_length] = el;
  ++_length;
  _stack = new_stack;
}

void Stack::Pop() {
  --_length;
  int* new_stack = new int[_length];
  for (int i = 0; i < _length; ++i) {
    new_stack[i] = _stack[i];
  }
  _stack = new_stack;
}

void Stack::Swap(Stack& s) {
  auto tmp(std::move(*this));
  *this = std::move(s);
  s = std::move(tmp);
}

Stack Stack::operator+(const Stack& s) {
  Stack result;
  result._length = (this->_length + s._length);
  result._stack = new int[(this->_length + s._length)];
  for (int i = 0; i < this->_length; ++i) {
    result._stack[i] = this->_stack[i];
  }
  int i = this->_length;
  for (int j = 0; j < s._length; ++j) {
    result._stack[i] = s._stack[j];
    ++i;
  }
  return result;
}

Stack Stack::operator+=(const Stack& s) {
  int* new_stack = new int[(this->_length + s._length)];
  for (int i = 0; i < this->_length; ++i) {
    new_stack[i] = this->_stack[i];
  }
  int i = this->_length;
  for (int j = 0; j < s._length; ++j) {
    new_stack[i] = s._stack[j];
    ++i;
  }
  int size = (this->_length + s._length);
  this->_length = size;
  delete[] this->_stack;
  this->_stack = new_stack;
  return *this;
}

Stack& Stack::operator=(const Stack& s) {
  this->Clear();
  if (this != &s) {
    this->_stack = new int[s._length];
    this->_length = s._length;
    for (size_t i = 0; i < this->_length; i++) {
      this->_stack[i] = s._stack[i];
    }
  }
  return *this;
}

Stack& Stack::operator=(Stack&& s) {
  swap(s);
  s.Clear();
  return *this;
}

std::ostream& operator<<(std::ostream& out, const Stack& s) {
  out << "[";
  int size = s._length;
  for (int i = 0; i < size; ++i) {
    out << s._stack[i];
    if (i != (size - 1)) {
      out << ", ";
    }
  }
  out << "]";
  return out;
}

std::istream& operator>>(std::istream& in, Stack& s) {
  std::string str;
  std::getline(std::cin, str);
  int str_length = str.length();
  int* arr = new int[str_length];
  for (int i = 0; i < str_length; ++i) {
    arr[i] = 0;
  }
  int j = 0;

  for (int i = 0; str[i] != '\0'; ++i) {
    if (str[i] == ' ') {
      j++;
    } else {
      arr[j] = arr[j] * 10 + (str[i] - 48);
    }
  }
  s._length = j;
  s._stack = arr;
  return in;
}

bool operator==(const Stack& s1, const Stack& s2) {
  if (s1._length != s2._length) {
    return false;
  }
  int size = s1._length;
  for (int i = 0; i < size; ++i) {
    if (s1._stack[i] != s2._stack[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const Stack& s1, const Stack& s2) { return !(s1 == s2); }

int main() {}