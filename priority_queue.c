#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

// Yer degistirme islemi (Swap)
static void swap_requests(Request *r1, Request *r2) {
    Request temp = *r1;
    *r1 = *r2;
    *r2 = temp;
}

// Min-Heap asagi dogru duzenleme (Heapify)
static void heapify_down_node(PriorityQueue *pq, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < pq->current_size &&
        pq->buffer[left].urgency_level < pq->buffer[smallest].urgency_level) {
        smallest = left;
    }

    if (right < pq->current_size &&
        pq->buffer[right].urgency_level < pq->buffer[smallest].urgency_level) {
        smallest = right;
    }

    if (smallest != idx) {
        swap_requests(&pq->buffer[idx], &pq->buffer[smallest]);
        heapify_down_node(pq, smallest);
    }
}

// Kuyrugu baslatma (%15 Bellek Yonetimi)
PriorityQueue* init_priority_queue(int starting_cap) {
    PriorityQueue *pq = (PriorityQueue*)calloc(1, sizeof(PriorityQueue));
    if (!pq) return NULL;

    pq->buffer = (Request*)calloc(starting_cap, sizeof(Request));
    if (!pq->buffer) {
        free(pq);
        return NULL;
    }
    pq->max_capacity = starting_cap;
    pq->current_size = 0;
    return pq;
}

// Kuyruga ekleme (Insert)
void enqueue_request(PriorityQueue *pq, Request new_req) {
    // Dinamik dizi genisletme (Realloc)
    if (pq->current_size == pq->max_capacity) {
        pq->max_capacity = (pq->max_capacity * 2) + 1;
        Request *temp_buffer = (Request*)realloc(pq->buffer, pq->max_capacity * sizeof(Request));
        if (!temp_buffer) return;
        pq->buffer = temp_buffer;
    }

    int i = pq->current_size;
    pq->buffer[i] = new_req;
    pq->current_size++;

    // Yukari dogru duzenleme (Bubble-Up)
    while (i != 0 && pq->buffer[(i - 1) / 2].urgency_level > pq->buffer[i].urgency_level) {
        swap_requests(&pq->buffer[i], &pq->buffer[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// En oncelikli elemani cekme (Extract-Min)
Request dequeue_min(PriorityQueue *pq) {
    if (pq->current_size == 0) {
        Request dummy = {-1, -1, false, "NULL"};
        return dummy;
    }

    Request top_priority = pq->buffer[0];

    pq->buffer[0] = pq->buffer[pq->current_size - 1];
    pq->current_size--;

    if (pq->current_size > 0) {
        heapify_down_node(pq, 0);
    }

    return top_priority;
}

// Bellek temizligi (Free)
void free_priority_queue(PriorityQueue *pq) {
    if (pq) {
        if (pq->buffer) free(pq->buffer);
        free(pq);
    }
}
