#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

// Map for keeping track of variables and their boolean value.
std::map<char, bool> m;

class bstnode // Binary search/ Expression tree node data structure.
{

public:
  char data {'\0'}; // Storing operands and variables. 
  bool negation {0}; // Storing variable's boolean value. 
  std::unique_ptr<bstnode> left {nullptr};    // Left node.
  std::unique_ptr<bstnode> right {nullptr};   // Right node.

  bstnode()
  {
    data = '\0';
    negation = 0;
    left = nullptr;
    right = nullptr;
  }

  bool evaluate(std::unique_ptr<bstnode>& root) // Evalute an expression tree with a concrete value.
  {
    if (root->data == '|' || root->data == '&') // If the node is an operand.
      return cal(root->data, root->negation, evaluate(root->left), evaluate(root->right)); // Calculate recursively.
    else 
      return (root->negation) ? !m[root->data] : m[root->data];
  }

  bool cal(char oper, bool neg, bool a, bool b) // Boolean operations. 
  {
    if (oper == '|' && !neg) // OR
      return (a | b);
    else if (oper == '&' && !neg) // AND
      return (a & b);
    else if (oper == '|' && neg) // Not OR
      return !(a | b);
    else if (oper == '&' && neg) // Not AND
      return !(a & b);
    else {
      std::cout << "Error: no operator like that\n";
      return -1;
    }
  }
// bstnode& root
  void result(std::unique_ptr<bstnode>& root) // Print out results.
  {
    for (std::int64_t i = pow(2, m.size()) - 1; i >= 0; --i) {
      std::size_t bit;
      std::map<char, bool>::iterator it;

      for (bit = 0, it = m.begin(); bit < m.size() && it != m.end(); ++bit, ++it)
        it->second = i ? (i >> bit) & 1 : 0;

        if (root->evaluate(root)) // If one set of variables is Satisfiable.
        {
          std::cout << "---------------------\nSatisfiable!!\n";

          for (auto item : m)
            std::cout << item.first << " : " << item.second << "\n";

          std::cout << "---------------------\n\n";
          return;
        }
      }
      // Otherwise it's Unsatisfiable.
      std::cout << "---------------------\nUnsatisfiable!!\n---------------------\n\n";
      return;
    }

  std::unique_ptr<bstnode> insert(std::string const& expression) // Insert tree node into tree.
  {
    std::vector<std::unique_ptr<bstnode>> stacknode{}; 
    std::unique_ptr<bstnode> root;

    for (int s = expression.length() - 1; s >= 0; s--) // Reading expression from the end of the expression.
    {
      std::unique_ptr<bstnode> temp = std::make_unique<bstnode>();

      if (expression[s] == '|' || expression[s] == '&') // When read operand in expression.
      {
        if (s && expression[s - 1] == '!')
        {
          temp->negation = 1; 
          temp->data = expression[s--];
        } 
        else 
          temp->data = expression[s];

        temp->left = std::move(stacknode[stacknode.size() - 1]);  // Take the variable out of the stack and assign the left of the operand.
        stacknode.pop_back();               // Delete previous node in stack.
        temp->right = std::move(stacknode[stacknode.size() - 1]); // Take the variable out of the stack and assign the right of the operand.
        stacknode.pop_back();               // Delete previous node in stack.
        root = std::move(temp);
        stacknode.push_back(std::move(root)); // Store the sub tree back to stack.
      } 
      else                  // Read in varaibles.
      {
        m[expression[s]] = true; // Storing variables into the map and assign deafult value as true.

        if (s && expression[s - 1] == '!') // Not a variable
        {
          temp->negation = 1;
          temp->data = expression[s--];
        }
        else
          temp->data = expression[s];

        temp->left = nullptr; // Variables are leaf nodes.
        temp->right = nullptr;
        stacknode.push_back(std::move(temp));  // Push variables into stack.
      }
    }

    root = std::move(stacknode[stacknode.size() - 1]);
    stacknode.pop_back();
    return root;
  }

};


int main(int, char **argv) {
  std::string str = argv[1]; // Get the command line argument.
  // std::string str = "&&&&&&&&&&&&&&&&&&&&&&&&&!a!b!c!d!e!f!g!h!i!j!k!l!m!n!o!p!q!r!s!t!u!v!w!x!y!z";
  // std::string str = "||uv&!w|v!|uy";
  std::size_t op_cnt = 0, alpha_cnt = 0; // Operand and alphabet count.

  for (size_t i = 0; i < str.length(); i++)
  {
    if (str[i] == '|' || str[i] == '&')
    {
      op_cnt++;
    }
    else if (isalpha(str[i]))
    {
      alpha_cnt++;
    }
    else if (str[i] == '!')
    {
      continue;
    }
    else
    {
      std::cout << "Please only enter alphabets or | or & or !.\n";
      return -1;
    } 
  }

  if (op_cnt != alpha_cnt - 1) // If operand count isn't the same as variables - 1.
  {
    std::cout << "Invalid query!!\n";
    return -1;
  }

  std::unique_ptr<bstnode> root = root->insert(str);
  root->result(root); // output.

  return 0;
}
