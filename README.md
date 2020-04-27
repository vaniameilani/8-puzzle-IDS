# 8-puzzle-IDS

IDS adalah salah satu metode algortima pencarian yang merupakan jenis dari uninformed search dan gabungan dari kelebihan Breath First Search(BFS) dan Depth First Search (DFS). 
IDS ini melakukan proses pencarian secara iterative.

Contoh permasalahan yang akan dibahas kali ini adalah 8-puzzle. 
Untuk pembahasan programnnya, saya tidak akan menjelaskan semuanya, karena beberapa program IDS ini sama dengan program pada DFS.
Disini saya akan menjelaskan bagian pemanggilan fungsi IDS  :
Proses pencarian IDS ini terdapat dalma fungsi `getPath` dimana untuk melakukan permindahan pada node selanjutnya.
Bagian ini adalah pencarian IDS. 
```
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
```
