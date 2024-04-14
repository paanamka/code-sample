#pragma once

#ifndef QUEUELSTPR_QUEUELSTPR_HPP
#define QUEUELSTPR_QUEUELSTPR_HPP

#include <stdexcept>
#include <initializer_list>

class QueueLstPr {
public:
	 QueueLstPr() = default;
	 QueueLstPr(const QueueLstPr& other);
	 QueueLstPr(QueueLstPr&& other) noexcept;
	 QueueLstPr(const std::initializer_list<float>& list);

	 QueueLstPr& operator= (const QueueLstPr& other);
	 QueueLstPr& operator= (QueueLstPr&& other) noexcept;
	 QueueLstPr& operator= (const std::initializer_list<float> list);

	 bool IsEmpty() const noexcept;

	 void Push(const float& elem);
	 void Pop() noexcept;

	 float& Top();
	 const float& Top() const;

	 void Clear() noexcept;

	 ~QueueLstPr();

private:
  struct Node {
		Node() = default;
		Node(const Node& other);
		Node(const Node* other);

		//bool operator < (const Node& other) const noexcept;
		//bool operator > (const Node& other) const noexcept;
		Node& operator = (const Node& other);

		float value_ = 0;
		Node* left_ = nullptr;
		Node* right_ = nullptr;
		size_t count_ = 0;

	};

	void copy_node(Node* cur_node, const Node* other_node) noexcept;
	void Clear(Node* node) noexcept;
	Node* root_ = nullptr;
};

#endif 