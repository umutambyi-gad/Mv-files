#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>
#include <ctype.h>


const char* videos_ext[] = {".webm", ".mkv", ".flv", ".vob", ".mp4", ".m4p", ".m4v", ".mpg", ".mpeg", ".mpg2", ".3gp", ".asf"};
const char* audios_ext[] = {".mp3", ".aac", ".wav", ".wma", ".flac", ".alac", ".aiff", ".dsd", ".pcm"};
const char* documents_ext[] = {".doc", ".docx", ".html", ".htm", ".odt", ".ods", ".pdf", ".xls", ".xlsx", ".ppt", ".pptx", ".txt"};
const char* images_ext[] = {".tif", ".tiff", ".bmp", ".jpg", ".jpeg", ".gif", ".png", ".eps", ".raw", ".cr2", ".nef", ".sr2", ".orf"};

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
	strcat(strcpy(Music, Home), "/Music"); // Audios only
	
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

