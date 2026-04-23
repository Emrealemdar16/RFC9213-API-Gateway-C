#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rfc9213_parser.h"

Request parse_rfc9213_header(int id, const char* header_str, const char* path) {
    Request req;
    req.req_id = id;
    req.urgency_level = 3; // RFC 9213 Varsayilan degeri
    req.is_incremental = false;

    strncpy(req.target_url, path, sizeof(req.target_url) - 1);
    req.target_url[sizeof(req.target_url) - 1] = '\0';

    if (!header_str) return req;

    char buffer[256];
    strncpy(buffer, header_str, 255);
    buffer[255] = '\0';

    char *segment = strtok(buffer, ", ");
    while (segment) {
        if (segment[0] == 'u' && segment[1] == '=') {
            int val = atoi(&segment[2]);
            if (val < 0) val = 0;
            if (val > 7) val = 7;
            req.urgency_level = val;
        } else if (segment[0] == 'i' && (segment[1] == '\0' || segment[1] == ' ')) {
            req.is_incremental = true;
        }
        segment = strtok(NULL, ", ");
    }

    return req;
}
