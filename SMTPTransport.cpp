/*
 * SMTPTransport.cpp
 *
 *  Created on: Feb 22, 2012
 *      Author: dande
 */

#include "SMTPTransport.h"

namespace mm_mta {

SMTPTransport::SMTPTransport() {
	// TODO Auto-generated constructor stub

}

SMTPTransport::~SMTPTransport() {
	// TODO Auto-generated destructor stub
}

int SMTPTransport::smtp_printf(const char* format, ...) {
	char buffer[256];
	va_list args;
	va_start (args, format);
	vsprintf (buffer,format, args);
	//perror (buffer);
	va_end (args);

	write(buffer);
	return 1;
}

int SMTPTransport::read(char *buffer, int size)
{
	// TODO dummy function to test the SMTP parser
	return 1;
}

int SMTPTransport::write(char *buffer)
{
	// TODO dummy function to test the SMTP parser
	printf("%s", buffer);
	return 1;
}

} /* namespace mm_mta */
