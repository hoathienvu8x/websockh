#include "src/websockh.h"
#include <stdio.h>

int main(){
	SSL_CTX *ssl_ctx = websockh_init_ssl_ctx();
	websockh ws = websockh_create_connection("stream.binance.com", 9443, "/ws/btcusdt@trade", ssl_ctx);
	if (ws == NULL) return  1;
	while (1){
		uint64_t len;
		uint8_t opcode;
		char *msg = websockh_recv(ws, &len, &opcode);
		if (msg){
			if (opcode == 9) websockh_send_pong(ws);
			else  if (opcode == 8) break;
			else{
				printf("%s\n", msg);
				printf("%ld %d\n", len, opcode);
			}
			free(msg);
		}else break; // It return NULL if there is some error
	}
	websockh_close_connection(ws);
	SSL_CTX_free(ssl_ctx);
	return 0;
}
