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
#include <time.h>

static const int kB = 1024*sizeof(char);
static const short HTTP_PORT = 80;
static const char *GOOGLE_COM_IP = "173.194.70.105";

void SocketsExamples::runBasicHttpClient() const {
  static const char *http_get_request = "GET / HTTP/1.1\r\nHost: www.google.com\r\n\r\n";
  int sockfd, read_bytes;
  struct sockaddr_in srv_addr;
  char buffer[1*kB];   //Buffer for 1 kB of data

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
  if(write(sockfd, http_get_request, strlen(http_get_request)*sizeof(*http_get_request)) < 0) {
    perror("Cannot send data through the given socket");
    exit(1);
  }

  // Reading data received from: www.google.com
  while((read_bytes = read(sockfd, buffer, sizeof(buffer))) > 0) {
    write(STDOUT_FILENO, buffer, read_bytes);
  }

  close(sockfd);
}

static const short SERVICE_PORT = 5050;
static const short MAX_BACKLOG_COUNT = 5;

void SocketsExamples::runBasicHttpServer() const {
  int sockfd, clntsockfd, read_bytes;
  struct sockaddr_in srv_addr, clnt_addr;
  char *time_str;
  time_t time_sec;
  static const char *html_start = "<html><body>";
  static const char *html_end = "</body></html>";
  char buffer[1*kB]; // Buffer for 1 kB of data
  socklen_t clnt_size = sizeof(clnt_addr);

  memset(&srv_addr, 0, sizeof(srv_addr));
  srv_addr.sin_family = AF_INET;
  srv_addr.sin_port = htons(SERVICE_PORT);
  srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Cannot open a socket");
    exit(1);
  }

  if(bind(sockfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) < 0) {
    perror("Cannot bind the socket with port and IP address");
    exit(1);
  }

  if(listen(sockfd, MAX_BACKLOG_COUNT) < 0) {
    perror("Cannot listen on this socket");
    exit(1);
  }

  printf("Server is listening on port: %d", SERVICE_PORT);
  // Infinite loop
  while(true) {
    if((clntsockfd = accept(sockfd, (struct sockaddr *)&clnt_addr, &clnt_size)) < 0) { // Very wired API
      perror("Something wrong with accept");
      continue;
    }

    if((read_bytes = read(clntsockfd, buffer, sizeof(buffer))) > 0) {
      write(STDOUT_FILENO, buffer, read_bytes);
      write(clntsockfd, html_start, strlen(html_start) * sizeof(*html_start));
      time_sec = time(NULL); // Get time from system
      time_str = ctime(&time_sec);
      write(clntsockfd, time_str, strlen(time_str) * sizeof(*time_str));
      write(clntsockfd, html_end, strlen(html_end) * sizeof(*html_end));
    }

    close(clntsockfd);
  }
}




