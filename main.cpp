#include "Test.h"
#include <iostream>
using namespace std;
class Node
{
public:
  char character;
  int frequency;
  Node* left;
  Node* right;

  Node()
  {
    this->character = (char)NULL;
    this->frequency = 0;
    this->left = NULL;
    this->right = NULL;
  }

  Node(char character, int frequency)
  {
    this->character = character;
    this->frequency = frequency;
    this->left = NULL;
    this->right = NULL;
  }
};

void insertOnHeap(std::vector<Node*> *v, Node* value)
{
  if(v->size() == 0){
    v->push_back(value);
    return;
  }
  v->push_back(value);
  int j = v->size()-1;

  int parent = (j%2==0? (j-2)/2 : (j-1)/2);
  while(parent >=0 && (*v)[parent]->frequency>=(*v)[j]->frequency){
    Node *aux = (*v)[parent];
    (*v)[parent] = (*v)[j];
    (*v)[j]= aux;
    j = parent;
    parent = (j%2==0? (j-2)/2 : (j-1)/2);
  }
}
#define uint32 unsigned int

void make_min_heap(std::vector<Node*> *v, vector<char> characters, vector<int> frequencies){
    for(uint32 i =0; i < characters.size(); i++){
      insertOnHeap(v,new Node(characters[i],frequencies[i]));
    }
}

void print_min_heap(std::vector<Node*> v){
  for(uint32 i=0; i < v.size();i++){
    cout<<i<<" "<<v[i]->frequency<<endl;
  }
}

uint left_son(uint root){
    return (root*2)+1;
}

uint right_son(uint root){
    return (root*2)+2;
}

Node * removeTopFromHeap(vector<Node*> *answer)
{

  Node * return_node = (*answer)[0];
  (*answer)[0] = (*answer)[answer->size()-1];
  answer->pop_back();

  uint current = 0;
  while(current < answer->size()){
    uint lson = left_son(current);
    uint rson = right_son(current);
    if(lson < answer->size() && (*answer)[current]->frequency > (*answer)[lson]->frequency
      && (*answer)[lson]->frequency <= (*answer)[rson]->frequency){
      Node* aux = (*answer)[current];
      (*answer)[current] = (*answer)[lson];
      (*answer)[lson] = aux;
      current = lson;
    }else if(rson < answer->size() &&  (*answer)[current]->frequency > (*answer)[rson]->frequency
      && (*answer)[rson]->frequency <= (*answer)[lson]->frequency){
      Node* aux = (*answer)[current];
      (*answer)[current] = (*answer)[rson];
      (*answer)[rson] = aux;
      current = rson;
    }else
      break;
  }

  /*******for(int i = 0; i < answer.size(); i++)
    cout<<i<<" "<<answer[i]<<endl;
  */
  return return_node;
}

void make_huffman_tree(std::vector<Node*> *v){
  while(v->size()>1){
    Node *left = removeTopFromHeap(v);
    Node *right = removeTopFromHeap(v);

    Node * top = new Node('$',left->frequency + right->frequency);
    top->left = left;
    top->right = right;
    insertOnHeap(v,top);
  }
}

void print_back_tracking(Node * n){
  if(!n)
    return;

  cout<<n->frequency<<endl;
  print_back_tracking(n->left);
  print_back_tracking(n->right);
}

void backtracking(Node* current_node, string code, map<char,string>* codes)
{
  if(!current_node)
    return;

  if(current_node->character != '$')
  {
    (*codes)[current_node->character] = code;
  }

  backtracking(current_node->left, code+"0", codes);
  backtracking(current_node->right, code+"1", codes);
}

void print_codes(map<char,string> answer2){
  for(map<char,string>::const_iterator it = answer2.begin();
    it != answer2.end(); ++it)
  {
      std::cout << it->first << " " << it->second<<endl;
  }
}

map<char,string> getHuffman(vector<char> characters, vector<int> frequencies)
{
  vector<Node*> min_heap;
  make_min_heap(&min_heap, characters,frequencies);
  cout<<"min heap made it"<<endl;
  print_min_heap(min_heap);
  make_huffman_tree(&min_heap);
  cout<<"Huffman made it"<<endl;
  print_back_tracking(min_heap[0]);
  map<char,string> answer2;
  backtracking(min_heap[0], "", &answer2);
  cout<<"Codes"<<endl;
  print_codes(answer2);
  cout<<"finished"<<endl;
  return answer2;
}

int main ()
{
    test();
    return 0;
}
