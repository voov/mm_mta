/*
 * main.cpp
 *
 *  Created on: Feb 21, 2012
 *      Author: dande
 */

#include <stdio.h>
#define BUFFER_SIZE 1024
char *code_buffer;


/*
 * Recursive descent parser
 * to parse SMTP commands
 */

// give error messages
void error(const char *s) {
	printf("Error: %s\n", s);
}

// Returns the current character in the buffer
char get_char(bool skip_whitespace=false) {
	if(skip_whitespace && (*code_buffer == ' ' || *code_buffer == '\t'))
	{
		// we have encountered a whitespace character, move the pointer
		// and try again
		code_buffer++;
		return get_char(skip_whitespace);
	}
	return *code_buffer;
}

bool eol() {
	if(get_char() == '\0') return true; // we are at the end of the line
	return false;
}


// Returns if the keyword is equal to the
bool getKeyword(const char *keyword) {
	int i=0;
	while(*keyword != '\0') {
		if(i >= BUFFER_SIZE) break; // do not let a keyword to be bigger than the buffer

		if(eol()) {
			error("Premature end found!");
		}
		if(code_buffer[i++] != *keyword) {
			return false;
		}
		keyword++;
	}
	code_buffer+=i; // step enough characters
	return true;
}

void string() {

}

const char* domain() {
	char r_domain[BUFFER_SIZE];
	int char_counter = 0;
	while(!eol()) {
		// read a character until the end of line
		// no whitespaces in this
		r_domain[char_counter] = get_char(true);
		char_counter++;
		code_buffer++;
	}
	r_domain[char_counter] = '\0'; // must 0 terminate the string
	return r_domain;
}

void helo() {
	getKeyword("HELO");
	const char *cc_domain = domain();
	printf("Connecting to domain: %s\n", cc_domain);
}

void ehlo() {
	getKeyword("EHLO");
	error("EHLO is Not yet supported!");
}

bool mailAddress() {
	if(get_char(true) != '<') return false;
	while(get_char(true) != '>') {
		// read the email address
	}
}

void mailFrom() {
	getKeyword("MAIL FROM:");
	mailAddress();
}

void rcptTo() {
	getKeyword("RCPT TO:");
	mailAddress();
}

void line() {

}


int main() {
	printf("SMTP Teszt");
	code_buffer = "HELO posta.voov.hu";
	helo();
	return 0;
}

