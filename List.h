#pragma once
#ifndef LIST_H
#define LIST_H

enum TYPE_LIST_EXCEPTION {
  LIST_mem = 1,
  LIST_invalidInput,
  LIST_failure
};
class listExceptions {
  TYPE_LIST_EXCEPTION type;
 public:
  listExceptions(TYPE_LIST_EXCEPTION type)
      :
      type(type)
  {}
  TYPE_LIST_EXCEPTION getType() {
    return type;
  }
};

template<typename T>
struct Node
{
 public:
  T data;
  Node<T> *next;
  Node<T> *prev;
  explicit Node(const T &data)
      : data(data), next(nullptr), prev(nullptr)
  {}
};

template<typename T>
class List
{
 private:
  Node<T> *head;
  Node<T> *tail;
  int size;
 public:
  List()
      : head(nullptr), tail(nullptr), size(0)
  {}
  ~List()
  {
    Node<T> *current(head);
    while (current != nullptr) {
      Node<T> *next(current->next);
      delete current;
      current = next;
    }
  }
  class iterator
  {
   public:
    Node<T> *ptr;
    explicit iterator(Node<T> *Node = nullptr)
        : ptr(Node)
    {}
    bool operator==(const iterator &iter)
    {
      return ptr == iter.ptr;
    }
    bool operator!=(const iterator &iter)
    {
      return ptr != iter.ptr;
    }
    const iterator operator++(int)
    {
      ptr = ptr->next;
      return *this;
    }
    iterator &operator++()
    {
      ptr = ptr->next;
      return *this;
    }
    const iterator operator--(int)
    {
      ptr = ptr->prev;
      return *this;
    }
    iterator &operator--()
    {
      ptr = ptr->prev;
      return *this;
    }

    const T &operator*() const
    {
      return ptr->data;
    }
    T &operator*()
    {
      return ptr->data;
    }
  };
  iterator begin()
  {
    return iterator(head);
  }
  iterator end()
  {
    return iterator(nullptr);
  }
  iterator insert(const T &element)
  {
    Node<T>* temp_node = nullptr;
    try {
      temp_node = new Node<T>(element);
    }
    catch (std::bad_alloc a) {
      throw listExceptions(LIST_mem);
    }
    temp_node->prev = nullptr;
    if (size == 0) {
      tail = temp_node;
      temp_node->next = nullptr;
    }
    else {
      head->prev = temp_node;
      temp_node->next = head;

    }
    head = temp_node;
    size++;
    return iterator(temp_node);
  }
  void erase(iterator iter)
  {
    if (iter.ptr == nullptr) {
      return;
    }
    if (iter.ptr->prev != nullptr) {
      iter.ptr->prev->next = iter.ptr->next;
    }
    if (iter.ptr->next != nullptr) {
      iter.ptr->next->prev = iter.ptr->prev;
    }
    if (iter.ptr == head) {
      head = iter.ptr->next;
    }
    if (iter.ptr == tail) {
      tail = iter.ptr->prev;
    }
    delete iter.ptr;
    --size;
  }
  int getSize()
  {
    return size;
  }
  bool empty()
  {
    return (size == 0);
  }
};


#endif //LIST_H