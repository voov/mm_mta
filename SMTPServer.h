/*
 * SMTPServer.h
 *
 *  Created on: Feb 22, 2012
 *      Author: Daniel Fekete
 *
 *  This should act as an SMTP server, it can parse SMTP commands and act as needed
 *  Compliant with RFC5321 (http://tools.ietf.org/html/rfc5321)
 */

#ifndef SMTPSERVER_H_
#define SMTPSERVER_H_

#include "SMTPTransport.h"

// a 1KB buffer MUST be enough for all standard SMTP lines
#define PARSER_BUFFER_SIZE 1024

namespace mm_mta {

/**
 * The parser part of this class implements a Recursive Descent Parser
 */
class SMTPServer: SMTPTransport {
private:
	char *code_buffer;
	void strcpy(const char *);
protected:

	// parser functions
	char getChar(bool skip_whitespace=false);
	char getNextChar(bool skip_whitespace=false);
	char lookAhead(bool skip_whitespace=false, int k=1);
	bool getKeyword(const char *keyword);
	void error(const char *);

	// symbols
	bool eol();
	bool alfnum();
	const char* domain();

	// SMTP keywords
	void helo();
	void ehlo();
	bool mailAddress();
	void mailFrom();
	void rcptTo();
	void rset();
	void data();
	void noop();
	void quit();
	void vrfy();


public:
	SMTPServer();
	virtual ~SMTPServer();
	void parseLine(const char*); // it is the main executing function
};

} /* namespace mm_mta */
#endif /* SMTPSERVER_H_ */
