/*
 * SocketsExamples.h
 *
 *  Created on: 24 lut 2014
 *      Author: tomek
 */

#ifndef SOCKETSEXAMPLES_H_
#define SOCKETSEXAMPLES_H_

class SocketsExamples {
public:
  void runBasicHttpClient() const;
  void runBasicHttpServer() const;
  void runSimpleUdpClient(short localPort, short remotePort) const;
  void runSimpleUdpServer(short localPort, short remotePort) const;
};

#endif /* SOCKETSEXAMPLES_H_ */
