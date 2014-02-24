/*
 * Executor.cc
 *
 *  Created on: 24 lut 2014
 *      Author: tomek
 */
#include <iostream>
#include "socketsexamples.h"

using std::cout;
using std::endl;

int main(void) {
	cout << "Executing something" << endl;

  SocketsExamples se;

  // Start HTTP basic client
  se.runBasicHttpClient();

	return 0;
}




