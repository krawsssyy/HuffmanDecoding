#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <list>
using namespace std;

struct MinHeapNode {
    char data;
    unsigned freq;
    MinHeapNode* left, * right;
    MinHeapNode(char data, unsigned freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

void makeLowestChar(struct MinHeapNode* node, list<int>& s) {
    if (!node)
        return;
    if (node->data != '$')
        s.emplace_front(node->data);
    makeLowestChar(node->left, s);
    makeLowestChar(node->right, s);
}

int getLowestChar(struct MinHeapNode* node) {
    list<int> s;
    makeLowestChar(node, s);
    s.sort(less<int>());
    return s.front();
}

struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r) {
        if (l->freq != r->freq)
            return l->freq > r->freq;
        else
            return getLowestChar(l) > getLowestChar(r);
    }
};


string decode(struct MinHeapNode* root, string s) {
    string ans = "";
    struct MinHeapNode* curr = root;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;
        if (curr->data != '$')
        {
            ans += curr->data;
            curr = root;
        }
    }
    return ans;
}

string buildTreeDecode(char arr[], int freq[], int N, string line) {
    struct MinHeapNode* left,* right,* top;
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
    for (int i = 0; i < N; i++)
        minHeap.push(new MinHeapNode(arr[i], freq[i]));
    for(int i = 0; i < N - 1; i++) {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
     return decode(minHeap.top(), line);
}

int main(int argc, char** argv)
{
    ifstream f("2-in.txt");
    ofstream g("2-out.txt");
    string line;
    getline(f, line);
    int N = stoi(line);
    char* arr = new char[N];
    int* freq = new int[N];
    for (int i = 0; i < N; i++) {
        getline(f, line);
        arr[i] = line[0];
        freq[i] = stoi(line.substr(2, line.length() - 1));
    }
    getline(f, line);
    g << buildTreeDecode(arr, freq, N, line);
    g.close();
    f.close();
    delete[] freq;
    freq = NULL;
    delete[] arr;
    arr = NULL;
    return 0;
}