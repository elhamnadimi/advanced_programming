#include <iostream>// std::cout #is a header file library that lets us work with input and output objects, such as cout
#include <utility>
#include <vector>
#include <map>
#include <time.h>
#include <sstream>
#include <memory>
#include <string>
using namespace std;// not good!
template<class K,class V>
class BST {
public:
	class Node {
	public:
		pair<const K, V> data; // pair < data_type1, data_type2 > Pair_name;
	
		unique_ptr<Node> left;   // Create a unique_ptr object through raw pointer
		unique_ptr<Node> right;
		unique_ptr<Node> parent; 
		//Node(K&& k, V&& v):
		//data{std::move(k), std::move(v)}, right(nullptr),left(nullptr),parent(nullptr)
		//{
		//}
		//A constructor will have exact same name as the class and 
		//it does not have any return type at all, not even void.
		// Constructors can be very useful for setting initial values for certain member variables.
		Node(const K& k, const V& v): //constructor
		data{std::move(k),std::move(v)}, right(nullptr),left(nullptr),parent(nullptr)
		{
		}
		~Node() noexcept = default;

		/*we define a function for finding the next element.
         transfer value of current node into c
         for inorder traverse we should move to the right
         element and then find the most left node of that element*/
         
        //if there is no right node we go to parent,
        // if new parent will also dont have right node we go to next parent
		Node * next() noexcept {
			Node * c=this;
			if(c->right)
			{
				Node *temp = c->right.get();
				while(temp->left) {
					temp = temp->left.get();
				}
				return temp;
			}
			Node *p = c->parent.get();
			while(p != nullptr && c == p->right.get()) {
				c = p;
				p = p->parent.get();
			}
			return p;
		}
	};
public:
	// root of the BST tree that is pointer of node that its parent, left, right is null
	// Node *root;
	std::unique_ptr<Node> root;
public:
	//class MyIterator : public std::iterator<std::input_iterator_tag, int>
	/* it shows that our iterator is inherited
    from std::iterator some characteristic and we should
    define some characteristic for our iterator*/
	class iterator : public std::iterator <std::forward_iterator_tag, pair<const K, V>> {
	public:
		Node *current; //iterator that is pointing to a node currently
		iterator() : current(nullptr) {}; //constructor: initializes objects of a class
		iterator(Node *n) : current(n) {}; //constructor--given a node (n) and make an itrator to it
		pair<const K, V>& operator*() { // pointer
			return current->data;
		}
		//++i' nn
		iterator& operator++() {
			current = current->next();
			return *this;    //out put of this function must be iterator, we use *this
		}
		//i++
		BST::iterator operator++(int) { 
			iterator tmp = *this;
			++*this;
			return tmp;
		}
		pair<const K, V>* operator->() { //defining operator ->first  ->second
			return &current->data;
		}
		bool operator==(const iterator &rhs) {
			return current == rhs.current;
		}
		bool operator!=(const iterator &rhs) {
			return !(*this == rhs);
		}
		//bool operator!=(const iterator &rhs)
		//{ return current != rhs.current; }

	};
	class cons_iterator : public iterator {
	public:
		Node *current;
		using iterator::iterator;
		const pair<const K, V> & operator*() {  // constructor
			return current->data;
		}
	};    
	//START TO WRITE FUNCTION !
	//it is function that its output is a iterator to the first node inorder traverse
	iterator begin() noexcept {
		Node *temp = root.get();
		while(temp->left.get()) {
			temp = temp->left.get();
		}
		return iterator(temp);
	}
	cons_iterator cbegin() const noexcept {//begin but for const iterator
		Node *temp = root.get();
		while(temp->left.get()) {
			temp = temp->left.get();
		}
		return cons_iterator(temp);
	}
	iterator getLast() noexcept {
		Node *temp = root.get();
		while(temp->right.get()) {
			temp = temp->right.get();
		}
		return iterator(temp);
	}
	cons_iterator cgetLast() const noexcept  {
		Node *temp = root.get();
		while(temp->right.get()) {
			temp = temp->right.get();
		}
		return cons_iterator(temp);
	}
	cons_iterator cend() const noexcept  {
		return nullptr;
	}
	iterator end() noexcept {
		return nullptr;
	}
private:
	iterator search(Node *n, K key) noexcept {  //search a node in BST
		if(n == nullptr || (n->data.first == key))
			return iterator(n);
		if(n->data.first < key)
			return search(n->right.get(), key);
		return search(n->left.get(), key);
	}
	cons_iterator csearch(Node *n, K key) const noexcept {
		if(n == nullptr || (n->data.first == key))
			return cons_iterator(n);
		if(n->data.first < key)
			return search(n->right.get(), key);
		return search(n->left.get(), key);
	}
	void balance(vector<pair<const K, V>>& item, std::size_t left, std::size_t right) noexcept {
		if(right - left < 1) {
			return;
		}
		auto med = ((left + right) / 2);
		insert(item[med].first, item[med].second);
		balance(item, left, med);
		balance(item, med + 1, right);
	}
	void freeMemory(Node *node) noexcept {
		cout<<"Deleting node : "<<node->data.second<<endl;
		if(node == nullptr) {
			return;
		}
		else {
			if(node->right)node->right.reset();
			if(node->left)node->left.reset();
			delete node;
		}
	}
	//A deep copy copies all fields, and makes copies of dynamically 
	//allocated memory pointed to by the fields. To make a deep copy,
	// you must write a copy constructor and overload the assignment operator,
	// otherwise the copy will point to the original, with disasterous consequences.
	void deepCopying(Node* before) noexcept {
		if(before->left != nullptr) {
			root->left.reset(new Node(before->left.get()->data.first, before->left.get()->data.second));
			deepCopying(before->left.get());
		}
		if(before->right != nullptr) {
			root->right.reset(new Node(before->right.get()->data.first, before->right.get()->data.second));
			deepCopying(before->right.get());
		}
	}
public:
	/*a copy constructor is a special constructor for creating a new object as
    a copy of an existing object.*/

    /*And assignment operator is called when an already initialized object
     is assigned a new value from another existing object*/

    /*the copy constructor initializes new objects, whereas 
    the assignment operator replaces the contents of existing objects.*/  

	BST() : root(nullptr) {//constructors for class BST //BST(){ROOT=nulptr}
	}
	BST(const BST &other) {     //ClassName (const ClassName &old_obj);
		if(other.root != nullptr) {
			root.reset(new Node(other.root->data.first, other.root->data.second));
			deepCopying(other.root.get());
		}
		// root = other.root; //shallow copy
	}
	BST &operator=(const BST &other) { //copy assignment
		auto temp =other;
		*this=std::move(temp);
		return *this;
	}
	BST(BST&&) noexcept = default;  //move constructor
	BST & operator=(BST&&) noexcept = default; // move assignment
	
	void display() {
		for(auto i = begin(); i != end(); ++i)
			cout<<i->first<<"\t"<<i->second<<"\n";
	}
	void insert(K key, V value, Node* temp) noexcept {
		if(key < temp->data.first) {
			if(temp->left == nullptr) {
				temp->left.reset(new Node(key, value));
				return; // end function
			} else {
				temp = temp->left.get();
			}
		}
		else if (key == temp->data.first) {
			temp->data.second = value;
			return;
		}
		else if(key > temp->data.first) {
			if(temp->right == nullptr) {
				temp->right.reset(new Node(key, value));
				return;
			} else
				temp = temp->right.get();
		}
		insert(key, value, temp);
	}

	void insert(K key, V value) {
		if(root != nullptr) {
			insert(key, value, root.get());
		}
		else {
			root.reset(new Node(std::move(key),std::move(value)));
		}
		// Node *treeNode = new Node(std::move(key),std::move(value));
		// Node *temp = nullptr;
		// Node *prev = nullptr;
		// temp = root.get();
		// while(temp) {
		// 	prev = temp;
		// 	if(temp->data.first == treeNode->data.first)
		// 		return;
		// 	if(temp->data.first < treeNode->data.first)
		// 		temp = temp->right.get();
		// 	else
		// 		temp = temp->left.get();
		// }
		// if(prev == nullptr)
		// 	root.reset(treeNode);
		// else {
		// 	treeNode->parent.reset(prev);
		// 	if(prev->data.first < treeNode->data.first)
		// 		prev->right.reset(treeNode);
		// 	else
		// 		prev->left.reset(treeNode);
		// }
	}
	void clear() {
		root.reset();
		root = nullptr;
	}
	iterator find(const K& key) noexcept {
		return search(root.get(), key);
	}
	cons_iterator cfind(const K& key) const noexcept {
		return csearch(root.get, key);
	}
	void balance() {
		if(!root) {
			std::cout<<"Empty Tree"<<std::endl;
			return;
		}
		vector<pair<const K, V>> values;
		auto item{begin()};
		for(; item != nullptr; ++item) {
			values.push_back(*item);
		}
		clear();
		balance(values, 0, values.size());
	}
};
string numberToString(int num) {
	ostringstream os;
	os<<num;
	return os.str();
}
int main() {
	clock_t start;
	BST<int,string> tree;
	for(int i = 0; i < 20; ++i) {
		tree.insert(i,"A"+numberToString(i));
	}
	tree.display();
	// cout<<'\n';
	//BST<int, string> test(tree);
	//test.display();

	//tree.display();
	cout<<'\n';
	tree.display();

	//for (auto i = tree.begin(); i != tree.end(); ++i)
	//	cout<<"test the begin"<<i->first<<"\t"<<i->second<<"\n";
	cout << "first Node:"<<tree.begin()->first<<"\t"<<tree.begin()->second<<"\n";
	cout << "last Node:"<<tree.getLast()->first<<"\t"<<tree.getLast()->second<<"\n";


	cout<<tree.find(12)->first<<"-"<<endl;
	cout<<tree.find(12)->second<<"-"<<endl;

	auto t=tree.find(666);
	if(t != tree.end()) {
		cout<<tree.find(666)->first<<"-"<<endl;
	}
	else {
		cout<<"Not found!"<<endl;
	}

	cout<<std::next(tree.find(12))->first<<"-"<<endl;
	cout<<std::next(tree.find(12))->second<<"-"<<endl;

	// some test lines removed

	cout<<"Tree before balance: "<<endl;
	start=clock();
	cout<<tree.find(12)->second<<endl;
	cout<<"Before Balance Find Time :"<<clock() - start<<" ms "<<endl;
	cout<<endl;

	tree.balance();
	

	start=clock();
	cout<<tree.find(12)->second<<endl;
	cout<<"After Balance Find Time :"<<clock() - start<<" ms "<<endl;
	cout<<endl;

	map<int, int > mp;
	map<int, int>::iterator it ;
	for (int i = 0; i < 20; ++i) {
		mp[i]=i;
	}
	cout<<"print map"<<endl;
	for(int i=0; i < 20; ++i) {
		cout<<i<<" .... "<<mp[i]<<endl;
	}
	cout<<"end print map"<<endl;

	cout<<endl;
	start=clock();
	it = mp.find(12);
	cout<<" Map find time :"<<clock() - start<<"ms"<<endl;
	if(it == mp.end()) {
		cout<<"not found" ;
	}
	else {
		cout<<"Key and Value"<<(int)it->first<<"->"<<it->second<<endl;
	}


	cout<<endl;
	start=clock();
	auto iii = tree.find(12);
	cout<<" Tree find time :"<<clock() - start<<"ms"<<endl;
	if(iii == tree.end()) {
		cout<<"not found" ;
	}
	else {
		cout<<"Key and Value"<<(int)iii->first<<"->"<<iii->second<<endl;
	}

	auto ib=tree.begin();
	cout<<"first Node:"<<ib->second<<"-"<<ib->first<<endl;
	auto icb=tree.cbegin();
	cout<<" C First Node :"<<icb->second<<"-"<<icb->first<<endl;
	auto il=tree.getLast();
	cout<< "last Node:"<<il->second<<"-"<<il->first<<endl;
	auto ibl=tree.cgetLast();
	cout<<" C last Node :"<<ibl->second<<"-"<<ibl->first<<endl;

	tree.clear();

	return 0;
}
