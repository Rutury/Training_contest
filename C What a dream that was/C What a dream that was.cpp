#include<iostream>
#include<vector>

using namespace std;

class TNode {
public:
    int idx;
    TNode* parent;
    TNode* lchild;
    TNode* rchild;

    TNode(int idx) : idx(idx), parent(NULL), lchild(NULL), rchild(NULL) {}

    void setParentAndChilds(TNode* newParent, TNode* newLChild, TNode* newRChild) {
        parent = newParent;
        lchild = newLChild;
        rchild = newRChild;
    }

    void LVRcout() const {
        if (lchild) lchild->LVRcout();
        cout << idx << ' ';
        if (rchild) rchild->LVRcout();
    }

    bool isRoot() const { return !parent; }

    bool isLeft() const { return !isRoot() && parent->lchild != NULL && parent->lchild->idx == idx; }

    bool isRight() const { return !isRoot() && parent->rchild != NULL && parent->rchild->idx == idx; }
};

class TTree {
public:
    TNode* root;
    vector<TNode> nodes;

    TTree(int n) {
        nodes.reserve(n);
        for (int i = 1; i <= n; i++) {
            nodes.emplace_back(i);
        }
        for (int i = 1; i <= n; i++) {
            TNode* parent = (i == 1 ? NULL : &nodes[i / 2 - 1]),
                * lchild = (2 * i > n ? NULL : &nodes[2 * i - 1]),
                * rchild = (2 * i + 1 > n ? NULL : &nodes[2 * i]);
            nodes[i - 1].setParentAndChilds(parent, lchild, rchild);
        }
        root = &nodes[0];
    }

    void LVRcout() const { root->LVRcout(); }

    void swap(int idx) {
        if (idx < 1 || idx > nodes.size()) return;
        TNode* u = &nodes[idx - 1];
        if (u->isLeft()) swapL(u);
        else if (u->isRight()) swapR(u);
    }

    void swapL(TNode* u) {
        if (u == NULL || u->isRoot()) return;
        TNode* p = u->parent, * ul = u->lchild, * pp = p->parent;
        if (p->isRoot()) root = u;
        else if (p->isLeft()) pp->lchild = u;
        else if (p->isRight()) pp->rchild = u;

        p->lchild = ul;
        p->parent = u;

        u->parent = pp;
        u->lchild = p;

        if (ul) ul->parent = p;
    }

    void swapR(TNode* u) {
        if (u == NULL || u->isRoot()) return;
        TNode* p = u->parent, * ur = u->rchild, * pp = p->parent;
        if (p->isRoot()) root = u;
        else if (p->isLeft()) pp->lchild = u;
        else if (p->isRight()) pp->rchild = u;

        p->rchild = ur;
        p->parent = u;

        u->parent = pp;
        u->rchild = p;

        if (ur) ur->parent = p;
    }
};

int main()
{
    int N, Q;
    cin >> N >> Q;
    TTree tree(N);
    for (int i = 0; i < Q; i++) {
        int idxToSwap;
        cin >> idxToSwap;
        tree.swap(idxToSwap);
    }
    tree.LVRcout();
    return 0;
}
