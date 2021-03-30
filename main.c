	#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>
#include <ctype.h>

#define len(list) sizeof(list) / sizeof(list[0]);


const char* videos_ext[] = {".webm", ".mkv", ".flv", ".vob", ".mp4", ".m4p", ".m4v", ".mpg", ".mpeg", ".mpg2", ".3gp", ".asf"};
const char* audios_ext[] = {".mp3", ".aac", ".wav", ".wma", ".flac", ".alac", ".aiff", ".dsd", ".pcm"};
const char* documents_ext[] = {".doc", ".docx", ".html", ".htm", ".odt", ".ods", ".pdf", ".xls", ".xlsx", ".ppt", ".pptx", ".txt"};
const char* images_ext[] = {".tif", ".tiff", ".bmp", ".jpg", ".jpeg", ".gif", ".png", ".eps", ".raw", ".cr2", ".nef", ".sr2", ".orf"};

bool endsWith(const char *str, const char *suffix);
char *strlwr(char *str);
char *join(char *firstpath, char *secondpath);

int main() {
	int index;

	struct passwd *pw = getpwuid(getuid());
	char* Home = pw -> pw_dir;
	
	char Downloads[100];
	char Videos[100];
	char Music[100];
	char Pictures[100];
	char Documents[100];

	strcat(strcpy(Downloads, Home), "/Downloads/");

	strcat(strcpy(Documents, Home), "Documents");
	strcat(strcpy(Videos, Home), "Videos");
	strcat(strcpy(Pictures, Home), "Pictures");
	strcat(strcpy(Music, Home), "Music"); // Audios only
	
	DIR* directory;
	struct dirent* dir;
	
	size_t len_videos_ext = len(videos_ext);
	size_t len_audios_ext = len(audios_ext);
	size_t len_documents_ext = len(documents_ext);
	size_t len_images_ext = len(images_ext);
	
	directory = opendir(Downloads);
	if (directory) {
	    	while ((dir = readdir(directory)) != NULL) {
		      char* list = dir -> d_name;
		      strlwr(list);
		      
		      // If any in list of videos extension (videos_ext) matches with the one listed in directory
		      for (index = 0; index < len_videos_ext; index++) {
			  if (endsWith(list, videos_ext[index])) {
				printf("VIDEOS: %s\n\n", join(Downloads, list));
			  }
		      }

		      // If any in list of audios extension (audio_ext) matches with the one listed in directory
		      for (index = 0; index < len_audios_ext; index++) {
			  if (endsWith(list, audios_ext[index])) {
				printf("AUDIOS: %s\n\n", join(Downloads, list));
			  }
		      }

		      // If any in list of documents extension (documents_ext) matches with the one listed in directory
		      for (index = 0; index < len_documents_ext; index++) {
			  if (endsWith(list, documents_ext[index])) {
				printf("DOCUMENTS: %s\n\n", join(Downloads, list));
			  }
		      }

		      // If any in list of images extension (images_ext) matches with the one listed in directory
		      for (index = 0; index < len_images_ext; index++) {
			  if (endsWith(list, images_ext[index])) {
				printf("IMAGES: %s\n\n", join(Downloads, list));
			  }
		      }
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

/* Since strlwr from 'string.h' is not standard I have to implement it by my self */
char *strlwr(char *str) {
  unsigned char *strp = (unsigned char *)str;

  while (*strp) {
     *strp = tolower((unsigned char)*strp);
      strp++;
  }
  return str;
}

/* Function for  joining two string (paths) and return new string */
char *join(char *firstpath, char *secondpath) {
   char fullpath[100];
   strcpy(fullpath, firstpath);
   return strcat(fullpath, secondpath);
}

