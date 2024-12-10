#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <climits>
using namespace std;

vector<int> sequence;

struct Node {
  int value;
  vector<Node*> child;
  Node* parent; // Added parent pointer for backtracking
  int index; // Added index for backtracking
  int length; // Length of subsequence ending at this node

  // Memory Destructor
  ~Node() {
    for (Node* childNode: child) {
      delete childNode;
    }
  }
};

struct Tree {
  Node *root;
  int size;
  Node* longestNode; // Track the node with longest subsequence

  // Constructor
  Tree() {
    init();
  } 

  // Destructor
  ~Tree() {
    if(root) {
      delete root;
    }
  }

  void init() {
    root = NULL;
    size = 0;
    longestNode = NULL;
  }

  bool isEmpty() {
    return root == NULL;
  }

  // Modified insert to support subsequence tracking
  Node* insert(Node *parent, int value, int index) {
    if(isEmpty()){
      root = __createNode(value, index);
      size++;
      return root;
    }

    if(parent == NULL)
      return NULL;

    Node* newNode = __createNode(value, index);
    newNode->parent = parent;
    parent->child.push_back(newNode);
    size++;

    return newNode;
  }

  int getHeight() {
    if(isEmpty())
      return 0;

    return __getNodeHeight(root);
  }

  void traverse() {
    if(isEmpty())
      return;

    __traverse(root, 1);
  }

  // Method to print the longest subsequence
  void printLongestSubsequence() {
    if(!longestNode) return;

    vector<int> subsequence;
    Node* current = longestNode;
    
    while(current && current != root) {
      subsequence.push_back(current->value);
      current = current->parent;
    }

    reverse(subsequence.begin(), subsequence.end());

    cout << "Longest Monotonically Increasing Subsequence: ";
    for(int val : subsequence) {
      cout << val << " ";
    }
    cout << endl;
    
    cout << "Length of Subsequence: " << subsequence.size() << endl;
  }

  private:
    Node* __createNode(int value, int index) {
      Node *newNode = new Node();
      newNode->value = value;
      newNode->parent = NULL;
      newNode->index = index;
      newNode->length = 1;
      
      return newNode;
    }

    int __getNodeHeight(Node* node) {
      if(node == NULL) 
        return 0;

      if(node->child.empty()) {
        return 1;
      }

      int maxHeight = 0;
      for(Node* childNode: node->child) {
        maxHeight = max(maxHeight, __getNodeHeight(childNode));
      }

      return maxHeight + 1;
    }

    void __traverse(Node* node, int currentLength) {
      if(node == NULL)
        return;

      // Update the longest node tracking
      if(longestNode == NULL || currentLength > longestNode->length) {
        longestNode = node;
      }

      for(int i = node->index + 1; i < sequence.size(); i++) {
        if(sequence[i] > node->value) {
          Node* newNode = insert(node, sequence[i], i);
          newNode->length = currentLength + 1;
          __traverse(newNode, currentLength + 1);
        }
      }
    }
};

int main() {
  int N;
  cout << "Input the length of the sequence: ";
  cin >> N;

  Tree newTree;
  newTree.insert(NULL, INT_MIN, -1); // tree root with minimum value
  
  cout << "Input " << N << " values of the sequence: ";
  sequence.resize(N);

  for (int i = 0; i < N; i++) {
    cin >> sequence[i];
    newTree.insert(newTree.root, sequence[i], i);
  }

  // Find the longest monotonically increasing subsequence
  newTree.traverse();

  // Print the longest subsequence
  newTree.printLongestSubsequence();

  return 0;
}