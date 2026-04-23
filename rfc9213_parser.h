#ifndef RFC9213_PARSER_H
#define RFC9213_PARSER_H

#include "priority_queue.h"

// Metin ayristirici (Parser) fonksiyonumuzun tanimi
Request parse_rfc9213_header(int id, const char* header_str, const char* path);

#endif
