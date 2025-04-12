#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

// 二叉排序树节点类
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 二叉排序树实现类
class BinarySearchTree {
private:
    TreeNode* root;

    // 私有辅助方法
    TreeNode* searchRecursive(TreeNode* node, int val) {
        if (node == nullptr || node->val == val) {
            return node;
        }
        if (val < node->val) {
            return searchRecursive(node->left, val);
        }
        return searchRecursive(node->right, val);
    }

    TreeNode* insertRecursive(TreeNode* node, int val) {
        if (node == nullptr) {
            return new TreeNode(val);
        }
        if (val < node->val) {
            node->left = insertRecursive(node->left, val);
        }
        else if (val > node->val) {
            node->right = insertRecursive(node->right, val);
        }
        return node;
    }

    TreeNode* deleteRecursive(TreeNode* node, int val) {
        if (node == nullptr) {
            return node;
        }

        if (val < node->val) {
            node->left = deleteRecursive(node->left, val);
        }
        else if (val > node->val) {
            node->right = deleteRecursive(node->right, val);
        }
        else {
            // 节点有一个子节点或没有子节点
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            // 节点有两个子节点: 获取右子树的最小节点
            TreeNode* minNode = findMin(node->right);
            node->val = minNode->val;
            node->right = deleteRecursive(node->right, minNode->val);
        }
        return node;
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void preorderRecursive(TreeNode* node, vector<int>& result) {
        if (node != nullptr) {
            result.push_back(node->val);
            preorderRecursive(node->left, result);
            preorderRecursive(node->right, result);
        }
    }

    void inorderRecursive(TreeNode* node, vector<int>& result) {
        if (node != nullptr) {
            inorderRecursive(node->left, result);
            result.push_back(node->val);
            inorderRecursive(node->right, result);
        }
    }

    void postorderRecursive(TreeNode* node, vector<int>& result) {
        if (node != nullptr) {
            postorderRecursive(node->left, result);
            postorderRecursive(node->right, result);
            result.push_back(node->val);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    // 基本操作
    TreeNode* search(int val) {
        return searchRecursive(root, val);
    }

    void insert(int val) {
        root = insertRecursive(root, val);
    }

    void remove(int val) {
        root = deleteRecursive(root, val);
    }

    // 递归遍历
    vector<int> preorderTraversal() {
        vector<int> result;
        preorderRecursive(root, result);
        return result;
    }

    vector<int> inorderTraversal() {
        vector<int> result;
        inorderRecursive(root, result);
        return result;
    }

    vector<int> postorderTraversal() {
        vector<int> result;
        postorderRecursive(root, result);
        return result;
    }

    // 非递归遍历
    vector<int> preorderIterative() {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }

        stack<TreeNode*> st;
        st.push(root);

        while (!st.empty()) {
            TreeNode* node = st.top();
            st.pop();
            result.push_back(node->val);

            if (node->right != nullptr) {
                st.push(node->right);
            }
            if (node->left != nullptr) {
                st.push(node->left);
            }
        }
        return result;
    }

    vector<int> inorderIterative() {
        vector<int> result;
        stack<TreeNode*> st;
        TreeNode* current = root;

        while (current != nullptr || !st.empty()) {
            while (current != nullptr) {
                st.push(current);
                current = current->left;
            }
            current = st.top();
            st.pop();
            result.push_back(current->val);
            current = current->right;
        }
        return result;
    }

    vector<int> postorderIterative() {
        vector<int> result;
        if (root == nullptr) {
            return result;
        }

        stack<TreeNode*> st;
        st.push(root);
        TreeNode* prev = nullptr;

        while (!st.empty()) {
            TreeNode* current = st.top();
            // 如果当前节点是叶子节点或已经处理过子节点
            if ((current->left == nullptr && current->right == nullptr) ||
                (prev != nullptr && (prev == current->left || prev == current->right))) {
                result.push_back(current->val);
                st.pop();
                prev = current;
            }
            else {
                if (current->right != nullptr) {
                    st.push(current->right);
                }
                if (current->left != nullptr) {
                    st.push(current->left);
                }
            }
        }
        return result;
    }

    // 层序遍历
    vector<vector<int>> levelOrder() {
        vector<vector<int>> result;
        if (root == nullptr) {
            return result;
        }

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> currentLevel;
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* node = q.front();
                q.pop();
                currentLevel.push_back(node->val);
                if (node->left != nullptr) {
                    q.push(node->left);
                }
                if (node->right != nullptr) {
                    q.push(node->right);
                }
            }
            result.push_back(currentLevel);
        }
        return result;
    }
};

// 测试函数
void testBST() {
    cout << "=== 二叉排序树测试 ===" << endl;

    // 创建二叉排序树
    BinarySearchTree bst;

    // 插入元素
    vector<int> nums = { 8, 3, 10, 1, 6, 14, 4, 7, 13 };
    cout << "插入元素: ";
    for (int num : nums) {
        cout << num << " ";
        bst.insert(num);
    }
    cout << endl;

    // 查找测试
    cout << "\n=== 查找测试 ===" << endl;
    vector<int> testValues = { 6, 14, 99 };
    for (int val : testValues) {
        TreeNode* found = bst.search(val);
        cout << "查找 " << val << ": " << (found ? "找到" : "未找到") << endl;
    }

    // 遍历测试
    cout << "\n=== 遍历测试 ===" << endl;
    cout << "递归前序遍历: ";
    for (int num : bst.preorderTraversal()) {
        cout << num << " ";
    }
    cout << endl;

    cout << "递归中序遍历: ";
    for (int num : bst.inorderTraversal()) {
        cout << num << " ";
    }
    cout << endl;

    cout << "递归后序遍历: ";
    for (int num : bst.postorderTraversal()) {
        cout << num << " ";
    }
    cout << endl;

    cout << "\n非递归前序遍历: ";
    for (int num : bst.preorderIterative()) {
        cout << num << " ";
    }
    cout << endl;

    cout << "非递归中序遍历: ";
    for (int num : bst.inorderIterative()) {
        cout << num << " ";
    }
    cout << endl;

    cout << "非递归后序遍历: ";
    for (int num : bst.postorderIterative()) {
        cout << num << " ";
    }
    cout << endl;

    cout << "\n层序遍历:" << endl;
    vector<vector<int>> levels = bst.levelOrder();
    for (const auto& level : levels) {
        for (int num : level) {
            cout << num << " ";
        }
        cout << endl;
    }

    // 删除测试
    cout << "\n=== 删除测试 ===" << endl;
    vector<int> deleteValues = { 3, 10 };
    cout << "删除元素: ";
    for (int val : deleteValues) {
        cout << val << " ";
        bst.remove(val);
    }
    cout << endl;

    cout << "删除后的中序遍历: ";
    for (int num : bst.inorderTraversal()) {
        cout << num << " ";
    }
    cout << endl;

    cout << "\n删除后的层序遍历:" << endl;
    levels = bst.levelOrder();
    for (const auto& level : levels) {
        for (int num : level) {
            cout << num << " ";
        }
        cout << endl;
    }
}

int main() {
    testBST();
    return 0;
}