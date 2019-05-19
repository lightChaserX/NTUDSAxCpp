#include <cstdio>
#include <deque>
#include <algorithm>
 
int main() {
  int N, M, K, num;
  scanf("%d%d%d", &N, &M, &K);
  std::deque<int> int_sequence(N, 0);
  std::deque<int> cloned(M, 0);
  for (int i=0; i<N; i++) {
    scanf("%d", &int_sequence[i]);
    if (i>=M-1) {
      if (i == M-1) {
        cloned = std::deque<int>(
          int_sequence.begin(), 
          int_sequence.begin()+M);
        std::sort(cloned.begin(), cloned.end());
      }
      else {
      auto searched_num_a = int_sequence.at((i-M));
      auto searched_num_b = int_sequence.at((i));
      //*find* and *ease* the old head in sorted order
      //NOte that you should consider duplicate case      
      //auto where_a = std::find(cloned.begin(), cloned.end(), searched_num_a);
      auto where_a = lower_bound(cloned.begin(), cloned.end(), searched_num_a); 
      cloned.erase(where_a);
      //*find* and *insert* the new end element in cutted sorted order
      auto upper = upper_bound(cloned.begin(), cloned.end(), searched_num_b);
      cloned.insert(upper, searched_num_b);
      //auto where_b = binarySearchRough(cloned, 0, M-1, searched_num_b);
      //cloned.insert(cloned.begin()+where_b, searched_num_b);
      }
      printf("%d\n", cloned[K-1]);
    }
  }
}
