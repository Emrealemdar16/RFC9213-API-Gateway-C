# RFC 9213 Uyumlu API Gateway İstek Zamanlayıcısı

Bu proje, gelen ağ isteklerini (HTTP Requests) geliş sırasına göre değil, **RFC 9213** standardına uygun olarak aciliyet (Urgency) değerlerine göre sıralayan bir API Gateway simülasyonudur. 

## Kullanılan Teknolojiler ve Yapılar
* **Dil:** C Programlama Dili
* **Veri Yapısı:** Priority Queue (Öncelikli Kuyruk)
* **Algoritma:** Min-Heap 
* **Mimari:** Modüler Tasarım (Header ve Source izolasyonu)

## Özellikler
* Gelen string tabanlı HTTP öncelik verilerini (`u=4, i` vb.) ayrıştıran **Parser** modülü.
* O(log n) zaman karmaşıklığı ile çalışan **Min-Heap** algoritması.
* `calloc`, `realloc` ve `free` döngüleriyle sıfır bellek sızıntısı (Zero Memory Leak) garantisi.

## Derleme ve Çalıştırma
Projeyi terminal üzerinden derlemek için aşağıdaki komutu kullanabilirsiniz:
gcc main.c priority_queue.c rfc9213_parser.c -o gateway
./gateway
