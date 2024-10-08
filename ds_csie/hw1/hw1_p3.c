#include <stdio.h>

#define printArray(arr, n)                                                     \
  for (int i = 0; i < n; i++) {                                                \
    printf("%d ", arr[i]);                                                     \
  }                                                                            \
  printf("\n")

#define panic(msg)                                                             \
  do {                                                                         \
    printf(msg);                                                               \
    return 1;                                                                  \
  } while (0)

#define queueEmpty(front, rare) (front == rare)
#define queueFull(front, rare, n) ((rare + 1) % n == front)
#define queuePush(queue, rare, n, value)                                       \
  if (!queueFull(front, rare, n)) {                                            \
    queue[rare] = value;                                                       \
    rare = (rare + 1) % n;                                                     \
  } else {                                                                     \
    panic("Queue is full");                                                    \
  }
#define queuePop(queue, front, n)                                              \
  if (!queueEmpty(front, rare)) {                                              \
    front = (front + 1) % n;                                                   \
  } else {                                                                     \
    panic("Queue is empty");                                                   \
  }

#define queuePrint(queue, front, rare, n)                                      \
  for (int i = front; i != rare; i = (i + 1) % n) {                            \
    printf("%d ", queue[i]);                                                   \
  }                                                                            \
  printf("\n")

int main() {
  int n;
  scanf("%d", &n);

  int visited[n];
  int matrix[n][n];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &matrix[i][j]);
    }
    visited[i] = 0;
  }

  int queue[n];
  int front = 0;
  int rare = 0;

  visited[0] = 1;
  queuePush(queue, rare, n, 0);

  while (!queueEmpty(front, rare)) {
    /* printf("visited: "); */
    /* printArray(visited, n); */
    /* printf("queue: "); */
    /* queuePrint(queue, front, rare, n); */
    /* printf("front: %d, rare: %d\n", front, rare); */

    int vertex = queue[front];
    queuePop(queue, front, n);

    /* printf("verted: %d\n", vertex + 1); */

    printf("%d ", vertex + 1);

    for (int i = 0; i < n; i++) {
      if (matrix[vertex][i] && !visited[i]) {
        visited[i] = 1;
        queuePush(queue, rare, n, i)
      }
    }
  }

  return 0;
}
