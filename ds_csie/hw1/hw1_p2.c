#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int minHeap[MAX_SIZE];
int minHeapSize = 0;

#define parent(x) ((x - 1) / 2)
#define left(x) (2 * x + 1)
#define right(x) (2 * x + 2)

int push(int val) {
  int idx = minHeapSize++;

  while (idx > 0 && val < minHeap[parent(idx)]) {
    minHeap[idx] = minHeap[parent(idx)];
    idx = parent(idx);
  }

  minHeap[idx] = val;
  return 0;
}

int delete(int val) {
  int targetIdx = 0;
  while (minHeap[targetIdx] != val) {
    targetIdx++;
  }

  minHeap[targetIdx] = minHeap[--minHeapSize];

  // heapify
  // while the target node has two children
  while (right(targetIdx) < minHeapSize) {
    int smallIdx = minHeap[left(targetIdx)] < minHeap[right(targetIdx)]
                       ? left(targetIdx)
                       : right(targetIdx);
    /* printf("while %d, %d\n", targetIdx, smallIdx); */
    if (minHeap[targetIdx] < minHeap[smallIdx]) {
      break;
    }

    int tmp = minHeap[targetIdx];
    minHeap[targetIdx] = minHeap[smallIdx];
    minHeap[smallIdx] = tmp;

    targetIdx = smallIdx;
  }

  // in case of target node has no right child but has left child
  if (left(targetIdx) < minHeapSize &&
      minHeap[left(targetIdx)] < minHeap[targetIdx]) {
    int tmp = minHeap[targetIdx];
    minHeap[targetIdx] = minHeap[left(targetIdx)];
    minHeap[left(targetIdx)] = tmp;
  }

  /* printf("\n"); */

  return 0;
}

//       0
//   1      2
// 3   4   5  6

//        20
//    21       25
//  30  40   
//  minHeapSize = 4

int main() {
  char *cmd = malloc(sizeof(char) * MAX_SIZE);
  int val;

  while (scanf("%s %d", cmd, &val) != EOF) {
    if (cmd[0] == 'i') {
      // insert
      push(val);
    } else if (cmd[0] == 'd') {
      // delete
      delete (val);
    }
  }

  for (int i = 0; i < minHeapSize; i++) {
    printf("%d ", minHeap[i]);
  }

  return 0;
}
