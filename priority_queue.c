#include <stdio.h>

#define MAXL (10000)
#define FMAX (0xc0c0c0c0)
#define PARENT(i) (i >> 1)
#define LEFT(i) (i << 1)
#define RIGHT(i) ((i << 1) + 1)

int A[MAXL];
int length, heap_size;

void swap(int i, int j) {
	int tmp = A[i];
	A[i] = A[j];
	A[j] = tmp;
}

void max_heapify(int i) {
	int l, r, largest;
	l = LEFT(i);
	r = RIGHT(i);
	if (l <= heap_size && A[l] > A[i]) largest = l;
	else largest = i;
	if (r <= heap_size && A[r] > A[largest]) largest = r;
	if (largest != i) {
		swap(i, largest);
		max_heapify(largest);
	}
}

void build_max_heap() {
	int i;
	heap_size = length;
	for (i=length/2; i>0; i--)
		max_heapify(i);
	return;
}

void heap_sort() {
	int i;
	build_max_heap();
	for (i=length; i>1; i--) {
		swap(1, i);
		heap_size--;
		max_heapify(1);
	}
	return;
}

int heap_maximum() {
	return A[1];
}

int heap_extract_max() {
	int maxitem;
	if (heap_size < 1) {
		printf("error: heap underflow\n");
		return -1;
	}
	maxitem = A[1];
	A[1] = A[heap_size];
	heap_size--;
	max_heapify(1);
	return maxitem;
}

void heap_increase_key(int i, int key) {
	if (key < A[i]) {
		printf("error: new key is small than current key\n");
		return;
	}
	A[i] = key;
	while (i > 1 && A[PARENT(i)] < A[i]) {
		swap(i, PARENT(i));
		i = PARENT(i);
	}
}

void max_heap_insert(int key) {
	heap_size++;
	A[heap_size] = FMAX;
	heap_increase_key(heap_size, key);
}

void print_it() {
	int i;
	for (i=1; i<=length; ++i)
		printf("%d ", A[i]);
	printf("\n");
}

int main() {
	int i, a;
	length = 0;
	while (scanf("%d", &a)) {
		A[++length] = a;
	}
	print_it();
	heap_sort();
	print_it();
	build_max_heap();
	for (i=0; i<length; ++i) {
		a = heap_extract_max();
		printf("get %d\n", a);
	}
	return 0;
}
