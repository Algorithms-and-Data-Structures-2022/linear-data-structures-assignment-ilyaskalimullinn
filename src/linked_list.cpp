#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    if (size_ == 0) {
      back_ = new Node(value, nullptr);
      front_ = back_;
      size_++;
      return;
    }
    back_->next = new Node(value, nullptr);
    back_ = back_->next;
    size_++;
  }

  bool LinkedList::Insert(int index, int value) {
    if (index < 0 || index > size_) return false;
    if (size_ == 0) {
      if (index != 0) return false;
      front_ = new Node(value, nullptr);
      back_ = front_;
      size_++;
      return true;
    }
    if (index == 0) {
      front_ = new Node(value, front_);
      size_++;
      return true;
    }
    if (index == size_) {
      Add(value);
      return true;
    }
    if (index == size_ - 1) {
      FindNode(index - 1)->next = new Node(value, back_);
      size_++;
      return true;
    }
    Node* node_left = FindNode(index - 1);
    node_left->next = new Node(value, node_left->next);
    size_++;
    return true;
  }

  bool LinkedList::Set(int index, int new_value) {
    if (index < 0 || index >= size_) return false;
    FindNode(index)->value = new_value;
    return true;
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (index < 0 || index >= size_) return std::nullopt;
    if (index == 0) {
      Node* node = front_->next;
      int result = front_->value;
      delete front_;
      front_ = node;
      size_--;
      return result;
    }
    if (index == size_ - 1) {
      int result = back_->value;
      delete back_;
      back_ = FindNode(index - 1);
      size_--;
      back_->next = nullptr;
      return result;
    }
    Node* node = FindNode(index - 1);
    Node* nextNode = node->next->next;
    int result = node->next->value;
    delete node->next;
    node->next = nextNode;
    size_--;
    return result;
  }

  void LinkedList::Clear() {
    if (size_ == 0) return;
    Node* node = front_;
    Node* nextNode;
    for (int i = 1; i < size_; i++) {
      nextNode = node->next;
      delete node;
      node = nextNode;
    }
    size_ = 0;
    delete back_;
    front_ = nullptr;
    back_ = nullptr;
  }

  std::optional<int> LinkedList::Get(int index) const {
    if (index < 0 || index >= size_) return std::nullopt;
    return FindNode(index)->value;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    if (front_->value == value) return 0;
    Node* node = front_;
    for (int i = 1; i < size_; i++) {
      node = node->next;
      if (node->value == value) return i;
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    return (IndexOf(value) != std::nullopt);
  }

  bool LinkedList::IsEmpty() const {
    return size_ == 0;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (size_ == 0) return std::nullopt;
    return front_->value;
  }

  std::optional<int> LinkedList::back() const {
    if (size_ == 0) return std::nullopt;
    return back_->value;
  }

  Node* LinkedList::FindNode(int index) const {
    if (index < 0 || index >= size_) return nullptr;
    Node* node = front_;
    for (int i = 0; i < index; i++) {
      node = node->next;
    }
    return node;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment