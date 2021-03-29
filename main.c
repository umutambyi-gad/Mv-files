#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>


bool endsWith(const char *str, const char *suffix);

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
	
	DIR* directory;
	struct dirent* dir;

	directory = opendir(Downloads);
	if (directory) {
	    	while ((dir = readdir(directory)) != NULL) {
		      char* list = dir -> d_name;
		}
    		closedir(directory);
	}
	return 0;
}

bool endsWith(const char* string, const char* suffix) {
    if (!string || !suffix) return false;
    size_t lenstring = strlen(string);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstring) return false;
    return strncmp(string + lenstring - lensuffix, suffix, lensuffix) == 0;
}

