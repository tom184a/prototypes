/*
 * SocketsExamples.cc
 *
 *  Created on: 24 lut 2014
 *      Author: tomek
 */
#include "socketsexamples.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static const int kB = 1024*sizeof(char);
static const short HTTP_PORT = 80;
static const char *GOOGLE_COM_IP = "173.194.70.105";
static const char *http_get_request = "GET / HTTP/1.1\r\nHost: www.google.com\r\n\r\n";

void SocketsExamples::runBasicHttpClient() const {
  int sockfd, read_bytes;
  struct sockaddr_in srv_addr;
  char buffer[10*kB];   //Buffer for 10 kB of data

  memset(&srv_addr, 0, sizeof(srv_addr));
  srv_addr.sin_family = AF_INET;
  srv_addr.sin_port = htons(HTTP_PORT);
  inet_pton(AF_INET, GOOGLE_COM_IP, &srv_addr.sin_addr);

  if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Cannot create a socket");
    exit(1);
  }

  if(connect(sockfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) < 0) {
    perror("Cannot connect to specified IP address");
    exit(1);
  }

  // Sending HTTP request to: www.google.com
  if(write(sockfd, http_get_request, sizeof(http_get_request)) < 0) {
    perror("Cannot send data through the given socket");
    exit(1);
  }

  // Reading data received from: www.google.com
  while((read_bytes = read(sockfd, buffer, sizeof(buffer))) > 0) {
    write(STDOUT_FILENO, buffer, read_bytes);
  }

  close(sockfd);
}




