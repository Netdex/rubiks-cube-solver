#include <stdio.h>

#include "ckociemba/search.h"

int main(const int argc, const char *argv[]){
	char *facelets = "UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB";
	char *sol = solution(
		facelets,
		24,
		1000,
		1,
		"cache"
	);
	
	printf("%s\n", sol);
	
	return 0;

}
