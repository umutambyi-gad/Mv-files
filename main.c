#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <stdio.h>


int main() {
	struct passwd *pw = getpwuid(getuid());
	char* Home = pw -> pw_dir;
	
	char Downloads[100];
	char Videos[100];
	char Music[100];
	char Pictures[100];
	char Documents[100];

	strcat(strcpy(Downloads, Home), "/Downloads");
	strcat(strcpy(Documents, Home), "/Documents");
	strcat(strcpy(Videos, Home), "/Videos");
	strcat(strcpy(Pictures, Home), "/Pictures");
	strcat(strcpy(Music, Home), "/Music");
	
}

