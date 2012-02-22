/*
 * SMTPTransport.h
 *
 *  Created on: Feb 22, 2012
 *      Author: dande
 */

#ifndef SMTPTRANSPORT_H_
#define SMTPTRANSPORT_H_

#include <stdio.h>
#include <stdarg.h>

namespace mm_mta {

class SMTPTransport {
public:
	SMTPTransport();
	virtual ~SMTPTransport();

	int smtp_printf(const char*, ...);

	// The transport layer's most low-level functions
	int read(char *, int);
	int write(char *);
};

} /* namespace mm_mta */
#endif /* SMTPTRANSPORT_H_ */
