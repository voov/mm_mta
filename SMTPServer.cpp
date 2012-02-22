/*
 * SMTPServer.cpp
 *
 *  Created on: Feb 22, 2012
 *      Author: dande
 */

#include "SMTPServer.h"

namespace mm_mta {

SMTPServer::SMTPServer() {
	// get a big enough buffer for the line
	code_buffer = new char[PARSER_BUFFER_SIZE];
}

/**
 * Get the the current character
 */
char SMTPServer::getChar(bool skip_whitespace)
{
	if(skip_whitespace && (*code_buffer == ' ' || *code_buffer == '\t'))
	{
		// we have encountered a whitespace character, move the pointer
		// and try again
		return getNextChar(skip_whitespace);
	}
	return *code_buffer;
}

char SMTPServer::lookAhead(bool skip_whitespace, int k)
{
	if(skip_whitespace && (*code_buffer == ' ' || *code_buffer == '\t')) {
		lookAhead(skip_whitespace, k+1);
	}
	return *(code_buffer+k);
}

/**
 * Increment the code pointer and return the character
 */
char SMTPServer::getNextChar(bool skip_whitespace)
{
	code_buffer++;
	return getChar(skip_whitespace);
}


bool SMTPServer::getKeyword(const char *keyword)
{
	int i=0;
	while(*keyword != '\0') {
		if(i >= PARSER_BUFFER_SIZE) break; // do not let a keyword to be bigger than the buffer

		if(eol()) {
			error("Premature end found!");
		}
		if(getChar() != *keyword) {
			return false;
		}
		keyword++; code_buffer++;
	}
	return true;
}

bool SMTPServer::eol()
{
	if(getChar(true) == '\0') return true;
	if(getChar(true) == '\r' && lookAhead(true) == '\n') return true;

	return false;
}

bool SMTPServer::alfnum() {

}

const char *SMTPServer::domain()
{
	char buffer[PARSER_BUFFER_SIZE];
	int char_counter = 0;
	while(!eol()) {
		buffer[char_counter] = getChar(true);
		char_counter++; getNextChar(true);
	}
	buffer[char_counter] = '\0';
	return buffer;
}

void SMTPServer::helo()
{
	const char *dm;
	if(getKeyword("HELO")) {
		dm = domain();
		smtp_printf("250 At your service %s!\n", dm);
		delete dm;
	}
}

void SMTPServer::ehlo()
{
}

bool SMTPServer::mailAddress()
{
	if(getChar(true) == '<') {
		while(getNextChar(true) != '>') {
			if(eol()) break; // TODO send error here

		}
	}
	return false;
}

void SMTPServer::mailFrom()
{
}

void SMTPServer::rcptTo()
{
}

void SMTPServer::rset()
{
}

void SMTPServer::data()
{
}

void SMTPServer::noop()
{
}

void SMTPServer::quit()
{
}

void SMTPServer::vrfy()
{
}

SMTPServer::~SMTPServer()
{
	// TODO Auto-generated destructor stub
	delete code_buffer;
}

void SMTPServer::strcpy(const char *str)
{
	char *dst = code_buffer;
	const char *src = str;
	while((*dst++ = *src++) != '\0');
}

void SMTPServer::error(const char *str)
{
	printf("Error: %s\r\n", str);
}

void SMTPServer::parseLine(const char *ln)
{
	strcpy(ln); // copy the current line to the code buffer
	helo();
}

} /* namespace mm_mta */
