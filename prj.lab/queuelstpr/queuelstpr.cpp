#include <memory>
#include <stdexcept>
#include "queuelstpr.hpp"

QueueLstPr::QueueLstPr(const QueueLstPr& other) {
	if (other.IsEmpty() == false) {
		root_ = new Node(other.root_);
		copy_node(root_, other.root_);
	}
}

QueueLstPr::QueueLstPr(QueueLstPr&& other) noexcept{
	std::swap(root_, other.root_);
	other.root_ = nullptr;
}

QueueLstPr::QueueLstPr(const std::initializer_list<float>& list) {
	for (float elem : list) {
		Push(elem);
	}
}

QueueLstPr& QueueLstPr::operator=(const QueueLstPr& other) {
	if (this != &other) {
		if (other.IsEmpty()) {
			(*this).Clear();
		}
		else {
			(*this).Clear();
			root_ = new Node(other.root_);
			copy_node(root_, other.root_);
		}
	}

	return *this;
}

QueueLstPr& QueueLstPr::operator=(QueueLstPr&& other) noexcept {
	std::swap(root_, other.root_);
	other.root_ = nullptr;

	return *this;
}

QueueLstPr& QueueLstPr::operator=(const std::initializer_list<float> list) {
	Clear();
	for (float elem : list) {
		Push(elem);
	}

	return *this;
}

bool QueueLstPr::IsEmpty() const noexcept{
	return (root_ == nullptr);
}

void QueueLstPr::Push(const float& elem) {
	if (IsEmpty()) {
		root_ = new Node;
		root_->value_ = elem;
	}

	else {
		Node* new_elem = new Node;
		new_elem->value_ = elem;

		Node* temp = root_;
		Node* prev_temp = nullptr;

		while (temp != nullptr) {

			prev_temp = temp;

			if (elem < temp->value_) {
				temp = temp->left_;
			}

			else if (elem > temp->value_) {
				temp = temp->right_;
			}

			else {
				++(temp->count_);
				break;
			}
		}

		if (elem < prev_temp->value_) {
			prev_temp->left_ = new_elem;
		}
		
		else if (elem > prev_temp->value_) {
			prev_temp->right_ = new_elem;
		}

	}
}

void QueueLstPr::Pop() noexcept {
	if ((*this).IsEmpty() == false) {

		Node* temp = root_;
		Node* prev_temp = nullptr;

		while (temp != nullptr) {
			if (temp->left_ != nullptr) {  // стараемся идти слева
				prev_temp = temp;
				temp = temp->left_;
			}

			else if (temp->count_ != 0) {
				--(temp->count_);
				break;
			}

			else if (temp->right_ != nullptr) {  // пришлось двигаться по правой ветке

				if (temp == root_) {   // корень смещается вправо
					root_ = temp->right_;
					delete (temp);
					temp = nullptr;
				}

				else if (prev_temp->left_ == temp) {  //  слева было пусто значит прев темп это мин
					prev_temp->left_ = temp->right_;
				}
				break;
			}

			else {  // пусто слева пусто справа и такой элемент один
				if (prev_temp == nullptr) {  // это ещё и корень какой кошмар
					Clear();  
					break;
				} 
				
				else if (prev_temp->left_ == temp) {
					prev_temp->left_ = nullptr;
				}
				else if (prev_temp->right_ == temp) {
					prev_temp->right_ = nullptr;
				}
				delete (temp);
				temp = nullptr;
			}
		}
	}
}


float& QueueLstPr::Top() {
	if (IsEmpty()) {
		throw std::logic_error("top of empty queue");
	}

	else {
		Node* temp = root_;

		while (temp != nullptr) {
			if (temp->left_ != nullptr) {
				temp = temp->left_;
			}

			else if (temp->count_ != 0) {
				return (temp->value_);
			}

			else {
				return (temp->value_);
			}
		}
	}
}

const float& QueueLstPr::Top() const {
	if (IsEmpty()) {
		throw std::logic_error("top of empty queue");
	}

	Node* temp = root_;

	while (temp != nullptr) {
		if (temp->left_ != nullptr) {
			temp = temp->left_;
		}

		else if (temp->count_ != 0) {
			return (temp->value_);
		}

		else {
			return (temp->value_);
		}
	}
}

void QueueLstPr::Clear() noexcept {
	Clear(root_);
	root_ = nullptr;
}

void QueueLstPr::Clear(Node* node) noexcept {
	if (node != nullptr) {

		Clear(node->left_);
		Clear(node->right_);  // ура рекурсии надеюсь всё упадёт
		delete(node);
		node = nullptr;   
	}
}

QueueLstPr::~QueueLstPr() {
	(*this).Clear();
}

QueueLstPr::Node::Node(const Node& other) {
	value_ = other.value_;
	count_ = other.count_;
}

QueueLstPr::Node::Node(const Node* other) {
	value_ = other->value_;
	count_ = other->count_;
}

QueueLstPr::Node& QueueLstPr::Node::operator= (const Node& other) {
	value_ = other.value_;
	count_ = other.count_;
	return *this;
}

void QueueLstPr::copy_node(Node* cur_node, const Node* other_node) noexcept {
	if (other_node != nullptr) {

		if (cur_node == nullptr) {
			cur_node = new Node;
			*cur_node = *other_node;
		}

		if (other_node->left_ != nullptr) {
			cur_node->left_ = new Node;
		  *(cur_node->left_) = *(other_node->left_);
			copy_node(cur_node->left_, other_node->left_);
		}
		if (other_node->right_ != nullptr) {
			cur_node->right_ = new Node;
			*(cur_node->right_) = *(other_node->right_);
			copy_node(cur_node->right_, other_node->right_);
		}
	}
} 