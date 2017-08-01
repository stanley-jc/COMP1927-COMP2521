// crawl.c ... build a graph of part of the web
// Written by John Shepherd, September 2015
// Uses the cURL library and functions by Vincent Sanders <vince@kyllikki.org>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <curl/curl.h>
#include "stack.h"
#include "set.h"
#include "graph.h"
#include "url.h"
#include "url_file.h"
#include "queue.h"

#define BUFSIZE 1024

void setFirstURL(char *, char *);
void normalise(char *, char *, char *, char *, int);
void strlower(char *);

int main(int argc, char **argv)
{
	URL_FILE *handle;
	char buffer[BUFSIZE];
	char baseURL[BUFSIZE];
	char firstURL[BUFSIZE];
	char next[BUFSIZE];
	int  maxURLs;

	if (argc > 2) {
		strcpy(baseURL,argv[1]);
		setFirstURL(baseURL,firstURL);
		maxURLs = atoi(argv[2]);
		if (maxURLs < 40) maxURLs = 40;
	}
	else {
		fprintf(stderr, "Usage: %s BaseURL MaxURLs\n",argv[0]);
		exit(1);
	}

	// initialise Graph to hold up to maxURLs
	// initialise set of Seen URLs
	Graph newG = newGraph(maxURLs);
	Set seen = newSet();
	Queue ToDo = newQueue();
	// add firstURL to the ToDo list
	enterQueue(ToDo,firstURL);
	// while ToDo list not empty and Graph not filled
	while(!emptyQueue(ToDo) && nVertices(newG) < maxURLs) {
		// grab Next URL from ToDo list
	    strcpy(next,leaveQueue(ToDo));
	    handle = url_fopen(next,"r");
		// if not allowed, continue
	    if(!handle){
	    	fprintf(stderr,"Couldn't open %s\n", next);
	    	continue;
	    }
		// foreach line in the opened URL
	    while(!url_feof(handle)) {
			url_fgets(buffer,sizeof(buffer),handle);
			char *cur, link[BUFSIZE], full_link[BUFSIZE];
			cur = buffer;
			while ((cur = nextURL(cur)) != NULL) {
				getURL(cur, link, BUFSIZE-1);
				normalise(link, next, baseURL, full_link, BUFSIZE-1);	
				// if Graph not filled or both URLs in Graph
				if(nVertices(newG) < maxURLs || isConnected(newG,next,full_link)){
					// add an edge from Next to this URL
					addEdge(newG,next,full_link);
				}
				// if this URL not Seen already
				if (!isElem(seen,full_link)){
					// add it to the Seen set
					// add it to the ToDo list
					insertInto(seen,full_link);
					enterQueue(ToDo,full_link);
				}
				cur += strlen(link);
			}
		}
	    url_fclose(handle);
	    sleep(1);

	}
	printf("base: %s\n",baseURL);
	showGraph(newG,0);

	// You need to modify the code below to implement:
	//
	// add firstURL to the ToDo list
	// initialise Graph to hold up to maxURLs
	// initialise set of Seen URLs
	// while (ToDo list not empty and Graph not filled) {
	//    grab Next URL from ToDo list
	//    if (not allowed) continue
	//    foreach line in the opened URL {
	//       foreach URL on that line {
	//          if (Graph not filled or both URLs in Graph)
	//             add an edge from Next to this URL
	//          if (this URL not Seen already) {
	//             add it to the Seen set
	//             add it to the ToDo list
	//          }
	//       }
    //    }
	//    close the opened URL
	//    sleep(1)
	// }
	/*if (!(handle = url_fopen(firstURL, "r"))) {
		fprintf(stderr,"Couldn't open %s\n", next);
		exit(1);
	}
	while(!url_feof(handle)) {
		url_fgets(buffer,sizeof(buffer),handle);
		//fputs(buffer,stdout);
		strlower(buffer);
		char *cur, link[BUFSIZE], full_link[BUFSIZE];
		cur = buffer;
		while ((cur = nextURL(cur)) != NULL) {
			getURL(cur, link, BUFSIZE-1);
			normalise(link, next, baseURL, full_link, BUFSIZE-1);
			printf("Found %s\n",full_link);
			cur += strlen(link);
		}
	}
	url_fclose(handle);
	sleep(1);
	return 0;*/
	return 0;
}

// normalise(In,From,Base,Out,N)
// - converts the URL in In into a regularised version in Out
// - uses the base URL to handle URLs like "/..."
// - uses From (the URL used to reach In) to handle "../"
//   - assumes that From has already been normalised
void normalise(char *in, char *from, char *base, char *out, int n)
{
	int len;
	char address[BUFSIZE];
	if (strstr(in, "http") != NULL)
		strcpy(out, in);
	else if (in[0] == '/') {
		strcpy(out, base);
		strcat(out, in);
	}
	else if((in[0] == '.' && in[1] == '.') && (in[2] == '/')){
		strcpy(out, base);
		strcat(out, &in[2]);
	}
	else {
		strcpy(address,from);
		len = strlen(address);
		while(address[len-1] != '/'){
			address[len-1] = '\0';
			len--;
		}
		address[len-1] = '\0';
		strcpy(out, address);
		strcat(out, "/");
		strcat(out, in);
	}
}

// setFirstURL(Base,First)
// - sets a "normalised" version of Base as First
// - modifies Base to a "normalised" version of itself
void setFirstURL(char *base, char *first)
{
	char *c;
	if ((c = strstr(base, "/index.html")) != NULL) {
		strcpy(first,base);
		*c = '\0';
	}
	else if (base[strlen(base)-1] == '/') {
		strcpy(first,base);
		strcat(first,"index.html");
		base[strlen(base)-1] = '\0';
	}
	else {
		strcpy(first,base);
		strcat(first,"/index.html");
	}
}

// strlower(Str)
// - set all chars in Str to lower-case
void strlower(char *s)
{
	for ( ; *s != '\0'; s++)
		*s = tolower(*s);
}
