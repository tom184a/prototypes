/*
 * Executor.cc
 *
 *  Created on: 24 lut 2014
 *      Author: tomek
 */
#include <iostream>
#include "socketsexamples.h"
#include "stuffs.h"

using std::cout;
using std::endl;

int main(void) {
  cout << "Executing something" << endl;

  SocketsExamples se;
  Stuffs sf;

  //se.runBasicHttpClient();
  //se.runBasicHttpServer();
  sf.doSth();

  return 0;
}




