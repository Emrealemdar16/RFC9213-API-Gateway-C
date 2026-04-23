#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdbool.h>

// Hocanin istedigi standartlara uygun Istek yapisi
typedef struct {
    int req_id;             // Istek numarasi
    int urgency_level;      // RFC 9213 Urgency (0-7)
    bool is_incremental;    // RFC 9213 Incremental
    char target_url[64];    // Hedef adres
} Request;

// Priority Queue (Min-Heap) yapisi
typedef struct {
    Request *buffer;        // Verilerin tutulacagi dizi
    int max_capacity;       // Toplam kapasite
    int current_size;       // Su anki eleman sayisi
} PriorityQueue;

// Fonksiyon prototipleri
PriorityQueue* init_priority_queue(int starting_cap);
void enqueue_request(PriorityQueue *pq, Request new_req);
Request dequeue_min(PriorityQueue *pq);
void free_priority_queue(PriorityQueue *pq);

#endif
