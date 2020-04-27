#include <bits/stdc++.h>
#define Right 6
#define Left 4
#define Up 2
#define Down 8
#define F first 
#define S second 

using namespace std;

struct Node {
  int state[3][3]; 
  Node *par; 
  int move; 
  int nn; 
};

stack<Node*> s;
list<int> path;

int in[10], fin[10], finalState[3][3];
typedef pair<int, int> pii;

bool test() {
  int cnt1 = 0, cnt2 = 0;
  
  for(int i = 0; i < 8; i++) {
    for(int j = i; j < 8; j++) {
      if(in[j] < in[i]) cnt1++;
      if(fin[j] < fin[i]) cnt2++;
    }
  }
  //printf("%d %d\n", cnt1, cnt2);
  return !((cnt1 + cnt2) % 2);
}

bool cmp(int a[][3], int b[][3]) {
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      if(a[i][j] != b[i][j])
	return false;
    }
  }
  return true;
}

bool visited(Node* a) {
  Node* par = a->par;
  while(par != NULL) {
    if(cmp(a->state, par->state)) return true;
    par = par->par;
  }
  
  return false;
}

pii find0(int tab[3][3]) {
  pii pos;
  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
      if(tab[i][j] == 0) {
	pos = pii(i, j);
	break;
      }
  
  return pos;
}

void fill(Node* a, Node* b) {
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      a->state[i][j] = b->state[i][j];;
    }
  }
}

void move2(Node* a, int i, int j) {
  //i - 1
  a->state[i][j] = a->state[i - 1][j];
  a->state[i - 1][j] = 0;
}

void move4(Node* a, int i, int j) {
  //j - 1
  a->state[i][j] = a->state[i][j - 1];
  a->state[i][j - 1] = 0;
}

void move6(Node* a, int i, int j) {
  //j + 1
  a->state[i][j] = a->state[i][j + 1];
  a->state[i][j + 1] = 0;
}

void move8(Node* a, int i, int j) {
  //i + 1
  a->state[i][j] = a->state[i + 1][j];
  a->state[i + 1][j] = 0;
}

void addChilds(Node* cur) {
  pii pos0 = find0(cur->state);
  int i = pos0.F, j = pos0.S;
  
  Node* node2 = new Node();
  Node* node4 = new Node();
  Node* node6 = new Node();
  Node* node8 = new Node();
  fill(node2, cur); fill(node4, cur); fill(node6, cur); fill(node8, cur);
  node2->par = cur; node4->par = cur; node6->par = cur; node8->par = cur;
  node2->nn = cur->nn + 1; node4->nn = cur->nn + 1; node6->nn = cur->nn + 1; node8->nn = cur->nn + 1;
  
  if(i != 0) {
    move2(node2, i, j);
    node2->move = Up;
    if(!visited(node2))
      s.push(node2);
  }
  if(j != 0) {
    move4(node4, i, j);
    node4->move = Left;
    if(!visited(node4))
      s.push(node4);
  }
  if(i != 2) {
    move8(node8, i, j);
    node8->move = Down;
    if(!visited(node8))
      s.push(node8);
  }
  if(j != 2) {
    move6(node6, i, j);
    node6->move = Right;
    if(!visited(node6))
      s.push(node6);
  }
}

void getPath(Node* cur) {
  Node* par = cur;
  while(par != NULL) {
    path.push_front(par->move);
    par = par->par;
  }
}

int ans;
bool sol = false;
void iddfs(int lim) {
  int nodes = 0;
  while(!s.empty()) {
    Node* cur = s.top(); s.pop();
    nodes++;
    //printf("%d\n", cur->move);
    if(cmp(cur->state, finalState)) {
      ans = cur->nn;
      getPath(cur);
      sol = true;
      return;
    }
    
    if(cur->nn < lim) {
      addChilds(cur);
    }
    
    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
		printf("%d ", cur->state[i][j]);
      }
      printf("\n");
    }
    printf("\n");
  }
}

void dfs(Node* first) {
  for(int i = 1; !sol; i++) {
    s.push(first);
    iddfs(i);
    //printf("%d\n", i);
  }
}

int main() {
  
  int p = 1;
  
  Node* first = new Node();
  first->par = NULL;
  first->move = Right; 
  first->nn = 0;
  
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      int num; scanf("%d", &num);
      if(num != 0) in[p++] = num;
      first->state[i][j] = num;
    }
  }

  p = 0;
  
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      int num;
	  scanf("%d", &num);
      if(num != 0) fin[p++] = num;
      finalState[i][j] = num;
    }
  }
  
  bool hasSol = test();
    
  if(hasSol) {
    printf("This puzzle has a solution!\n");
    dfs(first);
    printf("The solution can be achieved in %d moves.\nThis is an optimal solution.\n", ans);
    printf("-------PATH TO SOLUTION:-------\n");
    printf("%d", path.front()); path.pop_front();
    while(!path.empty()) {
      printf(" %d", path.front()); path.pop_front();
    }
    printf("\n");
  }
  
  else {
    printf("No solution.\n");
  }
  
  return 0;
}
