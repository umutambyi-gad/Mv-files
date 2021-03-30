#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>


#define len(list) sizeof(list) / sizeof(list[0]);


char LookUpDirectory[250]; // Directory to look up all files - By default is /Downloads/
char DestinationForVideos[250]; // Directory to paste all videos founded in the `LookUpDirectory` - By default is /Videos/
char DestinationForMusic[250]; // Directory to paste all music(Audios) founded in the `LookUpDirectory` - By default is /Music/
char DestinationForPictures[250]; // Directory to paste all pictures founded in the `LookUpDirectory` - By default is /Pictures/
char DestinationForDocuments[250]; // Directory to paste all documents founded in the `LookUpDirectory` - By default is /Documents/


/* All possible video extensions */
const char* videos_ext[] = {".webm", ".mkv", ".flv", ".vob", ".mp4", ".m4p", ".m4v", ".mpg", ".mpeg", ".mpg2", ".3gp", ".asf"};

/* All possible audio extensions */
const char* audios_ext[] = {".mp3", ".aac", ".wav", ".wma", ".flac", ".alac", ".aiff", ".dsd", ".pcm"};

/* All possible document extensions */
const char* documents_ext[] = {".doc", ".docx", ".html", ".htm", ".odt", ".ods", ".pdf", ".xls", ".xlsx", ".ppt", ".pptx", ".txt"};

/* All possible image extensions */
const char* images_ext[] = {".tif", ".tiff", ".bmp", ".jpg", ".jpeg", ".gif", ".png", ".eps", ".raw", ".cr2", ".nef", ".sr2", ".orf"};


bool endsWith(const char *str, const char *suffix);
char *strlwr(char *str);
char *join(char *firstpath, char *secondpath);


int main() {
	int index;

	struct passwd *pw = getpwuid(getuid());
	char* homeDirectory = pw -> pw_dir;


	/* 
	Joining home directory with ..., You can simply customize DestinationFor... or LookUpDirectory by initializing them to
	your own destination according to your file system.
		```
		ex. strcpy(LookUpDirectory, "C/Users/HP/Here");
		    strcpy(DestinationForVideos, "D:/musics/videos");
		    strcpy(DestinationForMusic, "D:/musics/audios");
		```
	*/
	strcat(strcpy(LookUpDirectory, homeDirectory), "/Downloads/");
	strcat(strcpy(DestinationForDocuments, homeDirectory), "/Documents/");
	strcat(strcpy(DestinationForVideos, homeDirectory), "/Videos/");
	strcat(strcpy(DestinationForPictures, homeDirectory), "/Pictures/");
	strcat(strcpy(DestinationForMusic, homeDirectory), "/Music/");
	

	DIR* directory;
	struct dirent* dir;
	

	size_t len_videos_ext = len(videos_ext);
	size_t len_audios_ext = len(audios_ext);
	size_t len_documents_ext = len(documents_ext);
	size_t len_images_ext = len(images_ext);
	

	directory = opendir(LookUpDirectory);
	if (directory) {
	    	while ((dir = readdir(directory)) != NULL) {
		      char* list = dir -> d_name; // list of all files founded in look up directory (LookUpDirectory)

		      char *listlwr = (char*) malloc(250 * sizeof(char));
                      strcpy(listlwr, list);
		      strlwr(listlwr);
		      
		      // If any listed file from the look up directory (LookUpDirectory) ends with any of video extensions (videos_ext) list
		      for (index = 0; index < len_videos_ext; index++) {
			  if (endsWith(listlwr, videos_ext[index])) {
				char* source = join(LookUpDirectory, list);
				char*  destination = join(DestinationForVideos, list);
				
				/* moving files from where it was to the desired destination */
				if (rename(source, destination) != 0) perror("Error: \n");
				free(source);
				free(destination);
			  }
		      }

		      // If any listed file from the look up directory (LookUpDirectory) ends with any of audio extensions (audios_ext) list
		      for (index = 0; index < len_audios_ext; index++) {
			  if (endsWith(listlwr, audios_ext[index])) {
				char* source = join(LookUpDirectory, list);
				char*  destination = join(DestinationForMusic, list);

				/* moving files from where it was to the desired destination */
				if (rename(source, destination) != 0) perror("Error: \n");
				free(source);
				free(destination);
			  }
		      }

		      // If any listed file from the look up directory (LookUpDirectory) ends with any of document extensions (documents_ext) list
		      for (index = 0; index < len_documents_ext; index++) {
			  if (endsWith(listlwr, documents_ext[index])) {
				char* source = join(LookUpDirectory, list);
				char*  destination = join(DestinationForDocuments, list);

				/* moving files from where it was to the desired destination */
				if (rename(source, destination) != 0) perror("Error: \n");
				free(source);
				free(destination);
			  }
		      }

		      // If any listed file from the look up directory (LookUpDirectory) ends with any of image extensions (images_ext) list
		      for (index = 0; index < len_images_ext; index++) {
			  if (endsWith(listlwr, images_ext[index])) {
				char* source = join(LookUpDirectory, list);
				char*  destination = join(DestinationForPictures, list);

				/* moving files from where it was to the desired destination */
				if (rename(source, destination) != 0) perror("Error: \n");
				free(source);
				free(destination);
			  }
		      }
		      free(listlwr);
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

/* Function for joining two string (paths) and return new string */
char *join(char *firstpath, char *secondpath) {
   char* fullpath = (char*) malloc(250 * sizeof(char));
   strcpy(fullpath, firstpath);
   return strcat(fullpath, secondpath);
}

