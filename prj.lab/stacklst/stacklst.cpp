#include <cstdlib>
#include <stdexcept>
#include <algorithm>
#include <complex/complex.hpp>
#include "stacklst.hpp"

StackLst::StackLst(const StackLst& other) {
	if (other.head_ == nullptr) {
		head_ = nullptr;
	}
	else {
		head_ = new Node;
		head_->v = other.head_->v;
		Node* next_element = other.head_;
		Node* temp = head_;

		while (next_element->next != nullptr) {
			temp->next = new Node;
			temp = temp->next;
			next_element = next_element->next;
			temp->v = next_element->v;
		}
		temp->next = nullptr;
	}

}


StackLst::StackLst(StackLst&& other) noexcept {
	if (other.head_ == nullptr) {
		head_ = nullptr;
	}
	else {
		head_ = new Node;
		std::swap(head_, other.head_);
	}
}

StackLst& StackLst::operator=(const StackLst& other) {
	if (head_ != other.head_) {
		(*this).Clear();
		if (other.head_ == nullptr) {
			head_ = nullptr;
		}
		else {
			head_ = new Node;
			head_->v = other.head_->v;
			Node* next_element = other.head_;
			Node* temp = head_;

			while (next_element->next != nullptr) {
				temp->next = new Node;
				temp = temp->next;
				next_element = next_element->next;

				temp->v = next_element->v;

			}
			temp->next = nullptr;
		}
	}
	return *this;

}

StackLst& StackLst::operator=(StackLst&& other) noexcept {
	if (head_ != other.head_) {
		if (other.head_ == nullptr) {
			head_ = nullptr;
		}
		else {
			std::swap(head_, other.head_);
		}
	}
	return *this;
}


void StackLst::Push(const Complex& complex) {
		Node* new_element = new Node;
		new_element->v = complex;
		new_element->next = head_;
		head_ = new_element;

	//new_element = nullptr;
} 

void StackLst::Pop() noexcept{
	if (head_ != nullptr) {
		Node* next_element;
		next_element = head_->next;
		Node* x = head_;
		delete x;
		head_ = next_element;
		//next_element = nullptr;
	}
}

bool StackLst::IsEmpty() const noexcept {
		return (head_ == nullptr);
}

const Complex& StackLst::Top() const{
	if (head_ == nullptr) {
		throw std::invalid_argument("top of empty stack");
	}
	else {
		return head_->v;
	}
}

Complex& StackLst::Top() {
	if (head_ == nullptr) {
		throw std::invalid_argument("top of empty stack");
	}
	else {
		return head_->v;
	}
}

void StackLst::Clear() noexcept {
	if (head_ != nullptr){
		Node* temp;

		while (head_ != nullptr) {
			temp = head_->next;
			delete (head_);
			head_ = temp;
		}
	}
}

StackLst::~StackLst() {
	(*this).Clear();
}