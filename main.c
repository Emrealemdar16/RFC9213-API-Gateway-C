#include <stdio.h>
#include "priority_queue.h"
#include "rfc9213_parser.h"

int main() {
    printf("====================================================\n");
    printf("[BASLATILIYOR] RFC 9213 Uyumlu Priority Queue Modulu\n");
    printf("====================================================\n\n");

    // 3 kapasite ile baslatip realloc (dinamik bellek) sistemini test ediyoruz
    PriorityQueue *api_queue = init_priority_queue(3);
    if (!api_queue) {
        printf("[HATA] RAM tahsisi basarisiz.\n");
        return 1;
    }

    printf("[SISTEM] Bellek tahsisi basarili. HTTP Istekleri parse ediliyor...\n\n");

    // FARKLI ONCELIKLERDE ISTELERI EKLÝYORUZ (U=0 EN YUKSEK, U=7 EN DUSUK)
    enqueue_request(api_queue, parse_rfc9213_header(101, "u=4, i", "/api/v1/users"));
    enqueue_request(api_queue, parse_rfc9213_header(102, "u=1", "/api/v1/payments"));
    enqueue_request(api_queue, parse_rfc9213_header(103, "i, u=7", "/api/v1/telemetry"));
    enqueue_request(api_queue, parse_rfc9213_header(104, "u=0, i", "/api/v1/auth/login")); // En acil olan
    enqueue_request(api_queue, parse_rfc9213_header(105, "u=3", "/api/v1/products"));

    printf("--- Islem Sirasi (Min-Heap Mantigina Gore) ---\n");

    while (api_queue->current_size > 0) {
        Request current_req = dequeue_min(api_queue);
        printf("-> Istek ID: %d | Urgency: %d | Incremental: %-5s | Hedef: %s\n",
               current_req.req_id,
               current_req.urgency_level,
               current_req.is_incremental ? "True" : "False",
               current_req.target_url);
    }

    // %15 puanlik bellek yonetimi kismi
    free_priority_queue(api_queue);
    printf("\n[SISTEM] Tum queue bellekten temizlendi. Memory Leak onlendi.\n");

    return 0;
}
