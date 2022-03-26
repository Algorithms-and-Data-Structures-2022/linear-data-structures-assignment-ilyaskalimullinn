#include "assignment/linked_queue.hpp"

namespace assignment {

  LinkedQueue::~LinkedQueue() {

    // эквивалентно очистке очереди
    LinkedQueue::Clear();
  }

  void LinkedQueue::Enqueue(int value) {
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

  bool LinkedQueue::Dequeue() {
    if (size_ == 0) return false;
    if (size_ == 1) {
      Clear();
      return true;
    }
    Node* next = front_->next;
    delete front_;
    front_ = next;
    size_--;
    return true;
  }

  void LinkedQueue::Clear() {
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

  std::optional<int> LinkedQueue::front() const {
    if (size_ == 0) return std::nullopt;
    return front_->value;
  }

  std::optional<int> LinkedQueue::back() const {
    if (size_ == 0) return std::nullopt;
    return back_->value;
  }

  bool LinkedQueue::IsEmpty() const {
    return size_ == 0;
  }

  int LinkedQueue::size() const {
    return size_;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedQueue::LinkedQueue(const std::vector<int>& values) {

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

  std::vector<int> LinkedQueue::toVector() const {
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