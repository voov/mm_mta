/*
 * main.cpp
 *
 *  Created on: Feb 21, 2012
 *      Author: dande
 */

#include <stdio.h>
#include "SMTPServer.h"


int main() {
	printf("SMTP Teszt\n");
	mm_mta::SMTPServer *serv = new mm_mta::SMTPServer();
	serv->parseLine("HELO posta.voov.hu");
	return 0;
}

