#ifndef HF_TLS_H
#define HF_TLS_H

void *create_tcp_tls(int fd);
int tcp_tls_recv(void *ssl,char *data,int len);
int tcp_tls_send(void *ssl,char *data,int len);
int tcp_tls_close(void *ssl);

#endif
