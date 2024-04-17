#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

// Node structure for Huffman tree
struct Node {
  char data;
  int frequency;
  Node *left;
  Node *right;

  Node(char d, int freq)
      : data(d), frequency(freq), left(nullptr), right(nullptr) {}
};

// Comparator for priority queue
struct compare {
  bool operator()(Node *l, Node *r) { return (l->frequency > r->frequency); }
};

// Function to generate Huffman codes
void printCodes(Node *root, std::string str, std::ofstream &output) {
  if (root == nullptr)
    return;

  if (!root->left && !root->right) {
    output << root->data << ": " << str << "\n";
  }

  printCodes(root->left, str + "0", output);
  printCodes(root->right, str + "1", output);
}

// Function to perform Huffman coding
void huffman(std::string str, std::ofstream &output, int caseNum) {
  // 1. Counting frequency and sort in ascending order
  std::unordered_map<char, int> frequencyMap;
  for (char c : str) {
    frequencyMap[c]++;
  }

  // 2. Build Huffman tree
  std::priority_queue<Node *, std::vector<Node *>, compare> minHeap;
  for (auto pair : frequencyMap) {
    minHeap.push(new Node(pair.first, pair.second));
  }

  while (minHeap.size() != 1) {
    Node *left = minHeap.top();
    minHeap.pop();
    Node *right = minHeap.top();
    minHeap.pop();

    int sum = left->frequency + right->frequency;
    Node *newNode = new Node('\0', sum);
    newNode->left = left;
    newNode->right = right;

    minHeap.push(newNode);
  }

  Node *root = minHeap.top();

  // 3. Generate Huffman codes
  output << "Case " << caseNum << ":\n";
  printCodes(root, "", output);
  output << "\n";
}

int main() {
  std::ifstream input("input.txt");
  std::ofstream output("output.txt");

  if (!input.is_open()) {
    std::cout << "Unable to open input file" << std::endl;
    return 1;
  }

  if (!output.is_open()) {
    std::cout << "Unable to open output file" << std::endl;
    return 1;
  }

  std::string line;
  while (std::getline(input, line)) {
    if (line.find("case") != std::string::npos) {
      // Extract case number
      std::string caseNumberStr = line.substr(4, line.find(':') - 4);
      int caseNumber = std::stoi(caseNumberStr);

      // Extract the input string
      std::string inputString;
      std::getline(input, inputString);

      // Call the function huffman with the extracted values
      huffman(inputString, output, caseNumber);
    }
  }

  input.close();
  output.close();

  return 0;
}
