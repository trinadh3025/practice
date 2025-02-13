#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

//Binary tree node
struct TreeNode{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL){}
	TreeNode(int x, TreeNode* l, TreeNode* r) : val(x), left(l), right(r) {}
	TreeNode(initializer_list<int> values){
		auto it = values.begin();
		val = *it;
		left = (++it != values.end()) ? new TreeNode(*it) : nullptr;
		right = (++it != values.end()) ? new TreeNode(*it) : nullptr;
	}
};

class Traversal{
public:
	Traversal(TreeNode* root) : treeRoot(root) {}

	vector<int> preOrder(){
		vector<int> result;
		preOrderHelper(treeRoot, result);
		return result;
	}

	vector<int> inOrder(){
		vector<int> result;
		inOrderHelper(treeRoot, result);
		return result;
	}

	vector<int> postOrder(){
		vector<int> result;
		postOrderHelper(treeRoot, result);
		return result;
	}

private:
	TreeNode* treeRoot;

	void preOrderHelper(TreeNode* node, vector<int>& result){
		if (!node) return;
		result.push_back(node->val);
		preOrderHelper(node->left, result);
		preOrderHelper(node->right, result);
	}

	void inOrderHelper(TreeNode* node, vector<int>& result){
		if (!node) return;
		inOrderHelper(node->left, result);
		result.push_back(node->val);
		inOrderHelper(node->right, result);
	}

	void postOrderHelper(TreeNode* node, vector<int>& result){
		if (!node) return;
		postOrderHelper(node->left, result);
		postOrderHelper(node->right, result);
		result.push_back(node->val);
	}
};

//Function to create sample tree
TreeNode* createSampleTree(){
	TreeNode* root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);

	return root;
}

//Utility function to print
void printTraversal(const vector<int>& traversal){
	for(int val: traversal){
		cout << val << " ";
	}
	cout << endl;
}

int main(){
	TreeNode* root = new TreeNode(1,
			new TreeNode(2, new TreeNode(4), new TreeNode(5)),
			new TreeNode(3, new TreeNode(6), new TreeNode(7))
			);

	Traversal traversal(root);

	cout << "Pre-order Traversal: ";
	printTraversal(traversal.preOrder());


	cout << "In-order Traversal: ";
	printTraversal(traversal.inOrder());

	cout << "Post-order Traversal: ";
	printTraversal(traversal.postOrder());

	return 0;
}
