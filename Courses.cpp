/**
Michael Berry
CS300 - DSA Analysis & Design
SNHU
4/23/2023
Project 2
**/

#include <iostream>
#include <regex>
#include "Courses.h"


// Default constructor
Courses::Courses() {
	// root equal to nullptr
	root = nullptr;
}

// Destructor
Courses::~Courses() {
	// recurse from root deleting every node
	destroyRecursive(root);
}

// Traverse the tree in order
void Courses::InOrder() {
	// call inOrder function and pass root
	inOrder(root);
}

// Traverse the tree in post-order
void Courses::PostOrder() {
	// postOrder root
	postOrder(root);
}

 // Traverse the tree in pre-order
void Courses::PreOrder() {
	// preOrder root
	preOrder(root);
}

 // Insert a course
void Courses::Insert(Course course) {
	// if root equal to nullptr
	if (root == nullptr) {
		// root is equal to new node course
		root = new Node(course);
	}
	// else
	else {
		// add Node root and course
		this->addNode(root, course);
	}
}

// Remove course
void Courses::Remove(std::string courseId) {
	// remove node root courseID
	this->removeNode(root, courseId);
}

// Search for a course
Course Courses::Search(std::string courseId) {
	// convert courseID to upper case for use in comparison
	transform(courseId.begin(), courseId.end(), courseId.begin(), ::toupper);
	// set current node equal to root
	Node* cur = root;
	// keep looping downwards until bottom reached or matching courseId found
	while (cur != nullptr) {
		// if match found, return current course
		if (cur->course.getId().compare(courseId) == 0) {
			return cur->course;
		}
		// if course is smaller than current node then traverse left
		else if (courseId.compare(cur->course.getId()) < 0) {
			cur = cur->left;
		}
		// else larger so traverse right
		else {
			cur = cur->right;
		}
	}
	// course not found so return empty course.
	Course course;
	return course;
}

// Add a course to node
void Courses::addNode(Node* node, Course course) {
	// if node is smaller than add to left
	if (node != nullptr && (node->course.getId().compare(course.getId()) > 0)) {
		// if no left node
		if (node->left == nullptr) {
			// this node becomes left
			node->left = new Node(course);
			return;
		}
		// else recurse down the left node
		else {
			this->addNode(node->left, course);
		}
	}
	// else
	else if (node != nullptr && (node->course.getId().compare(course.getId()) < 0)) {
		// if no right node
		if (node->right == nullptr) {
			// this node becomes right
			node->right = new Node(course);
			return;
		}
		// else if node is larger than add to right
		else {
			// recurse down the right node
			this->addNode(node->right, course);
		}
	}
}

void Courses::destroyRecursive(Node* node) {
	// if node is not equal to nullptr
	if (node != nullptr) {
		// call for destruction of any children
		destroyRecursive(node->left);
		destroyRecursive(node->right);
		// remove the current node
		delete node;
		node = nullptr;
	}
}

void Courses::inOrder(Node* node) {
	// if node is not equal to null ptr
	if (node != nullptr) {
		// inOrder left
		inOrder(node->left);
		// output courseID and courseName
		cout << node->course.getId() << ", "
			<< node->course.getName() << endl;
		// inOder right
		inOrder(node->right);
	}
}

void Courses::postOrder(Node* node) {
	// if node is not equal to nullptr
	if (node != nullptr) {
		// postOrder left
		postOrder(node->left);
		// postOrder right
		postOrder(node->right);
		// output courseID and courseName
		std::cout << node->course.getId() << ", "
			<< node->course.getName() << std::endl;
	}
}

void Courses::preOrder(Node* node) {
	// if node is not equal to nullptr
	if (node != nullptr) {
		// output courseID and courseName
		std::cout << node->course.getId() << ", "
			<< node->course.getName() << std::endl;
		// preOrder left
		preOrder(node->left);
		// preOrder right
		preOrder(node->right);
	}
}

Node* Courses::removeNode(Node* node, const std::string courseId) {
	if (node == nullptr) {
		return node;
	}
	// if course is smaller than current node then traverse left
	else if (courseId.compare(node->course.getId()) < 0) {
		node->left = removeNode(node->left, courseId);
	}
	// else if course is larger than current node then traverse right
	else if (courseId.compare(node->course.getId()) > 0) {
		node->right = removeNode(node->right, courseId);
	}
	// else match point found
	else {
		// leaf node
		if (node->left == nullptr && node->right == nullptr) {
			delete node;
			node = nullptr;
		}
		// else if left child
		else if (node->left != nullptr && node->right == nullptr) {
			Node* tmp = node;
			node = node->left;
			delete tmp;
			tmp = nullptr;
		}
		// else if right child
		else if (node->left == nullptr && node->right != nullptr) {
			Node* tmp = node;
			node = node->right;
			delete tmp;
			tmp = nullptr;
		}
		// else both children
		else {
			// find the minimum of the right subtree nodes for bst
			Node* tmp = node;
			while (tmp->left != nullptr) {
				tmp = tmp->left;
			}
			node->course = tmp->course;
			node->right = removeNode(node->right, tmp->course.getId());
		}
	}
	return node;
}