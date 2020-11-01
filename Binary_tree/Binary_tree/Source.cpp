#include <fstream>
#include <iostream>
#include <string>

class BinaryTree {
 private:
  int* _tree = nullptr;
  int _length = 0;
  int _numOfElements = 0;

 public:
  BinaryTree(int value);
  int max();
  void add(int value);
  void setleft(int parent_index, int value);
  void setright(int parent_index, int value);
  void save();
  class Iterator {
   public:
    Iterator(const BinaryTree* s) { st = s; }
    void first() { index = 0; }
    void next() { ++index; }
    bool isDone() { return index == (st->_length - 1); }
    int currentItem() { return st->_tree[index]; }
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
      return ((st == itr.st) && (index = itr.index));
    }
    bool operator!=(const Iterator& itr) {
      return !((st == itr.st) && (index = itr.index));
    }
    int operator*() { return this->st->_tree[index]; }

   private:
    const BinaryTree* st;
    int index;
  };

  Iterator* createIterator() const { return new Iterator(this); }
};

BinaryTree::BinaryTree(int value) {
  _numOfElements = 1;
  _length = (_numOfElements * 2 + 1);
  _tree = new int[_length];
  _tree[0] = value;
  _tree[1] = 0;
  _tree[2] = 0;
}

int BinaryTree::max() {
  int maximum = 0;
  int elements = 0;
  BinaryTree::Iterator itr = BinaryTree::Iterator(&(*this));
  for (int i = 0; i < _length; ++i) {
    if (*itr > maximum) {
      maximum = (*itr);
    }
    itr++;
  }
  return maximum;
}

void BinaryTree::add(int value) {
  if (value > this->_tree[0]) {
    setright(0, value);
  } else {
    setleft(0, value);
  }
}

void BinaryTree::setleft(int parent_index, int value) {
  if (_tree[(parent_index * 2 + 1)] == 0) {
    _tree[(parent_index * 2 + 1)] = value;
    ++_numOfElements;
    int new_length = (_numOfElements * 2 + 1);
    int* new_tree = new int[new_length];
    for (int i = 0; i < _length; ++i) {
      new_tree[i] = _tree[i];
    }
    for (int i = _length; i < new_length; ++i) {
      new_tree[i] = 0;
    }
    _length = new_length;
    _tree = new_tree;
  } else {
    if (value < _tree[(parent_index * 2 + 1)]) {
      setleft((parent_index * 2 + 1), value);
    } else {
      setright((parent_index * 2 + 1), value);
    }
  }
}

void BinaryTree::setright(int parent_index, int value) {
  if (_tree[(parent_index * 2 + 2)] == 0) {
    _tree[(parent_index * 2 + 2)] = value;
    ++_numOfElements;
    int new_length = (_numOfElements * 2 + 2);
    int* new_tree = new int[new_length];
    for (int i = 0; i < _length; ++i) {
      new_tree[i] = _tree[i];
    }
    for (int i = _length; i < new_length; ++i) {
      new_tree[i] = 0;
    }
    _length = new_length;
    _tree = new_tree;
  } else {
    if (value < _tree[(parent_index * 2 + 2)]) {
      setleft((parent_index * 2 + 2), value);
    } else {
      setright((parent_index * 2 + 2), value);
    }
  }
}

void BinaryTree::save() {
  std::string str = {};
  std::ofstream fout("binarytree.txt");
  int elements = 0;

  BinaryTree::Iterator itr = BinaryTree::Iterator(&(*this));
  for (; (elements < _numOfElements); itr++) {
    str += "[";
    str += std::to_string(*itr);
    str += "] ";
    if (*itr != 0) {
      ++elements;
    }
  }
  fout << str;
  fout.close();
}

class View {
 public:
  void ViewMax(BinaryTree& tr) { std::cout << tr.max(); }
};

class Controller {
 public:
  void Add(BinaryTree& tr, int el) { tr.add(el); }
  void Save(BinaryTree& tr) { tr.save(); }
  void Maximum(BinaryTree& tr) {
    View v;
    v.ViewMax(tr);
  }
};

int main() {
  Controller c;
  BinaryTree tr(20);
  c.Add(tr, 10);
  c.Add(tr, 5);
  c.Add(tr, 15);
  c.Add(tr, 30);
  c.Add(tr, 35);
  c.Maximum(tr);
  return 0;
}
