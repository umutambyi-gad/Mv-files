#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>


#define len(list) sizeof(list) / sizeof(list[0])


#define show true // If show is true script will only show you the matches
#define execute true // If execute is true script will be only executed
/* Notice: if both are true script will show up and be executed */


char LookUpDirectory[250]; // Directory to look up all files - By default is .../Downloads/
char DestinationForVideos[250]; // Directory to paste all videos founded in the `LookUpDirectory` - By default is .../Videos/
char DestinationForMusic[250]; // Directory to paste all music(Audios) founded in the `LookUpDirectory` - By default is .../Music/
char DestinationForPictures[250]; // Directory to paste all pictures founded in the `LookUpDirectory` - By default is .../Pictures/
char DestinationForDocuments[250]; // Directory to paste all documents founded in the `LookUpDirectory` - By default is .../Documents/


/* All possible video extensions */
const char *video_ext[] = {".webm", ".mkv", ".flv", ".vob", ".mp4", ".m4p", ".m4v", ".mpg", ".mpeg", ".mpg2", ".3gp", ".asf"};

/* All possible audio extensions */
const char *audio_ext[] = {".mp3", ".aac", ".wav", ".wma", ".flac", ".alac", ".aiff", ".dsd", ".pcm"};

/* All possible document extensions */
const char *document_ext[] = {".doc", ".docx", ".html", ".htm", ".odt", ".ods", ".pdf", ".xls", ".xlsx", ".ppt", ".pptx", ".txt"};

/* All possible image extensions */
const char *image_ext[] = {".tif", ".tiff", ".bmp", ".jpg", ".jpeg", ".gif", ".png", ".eps", ".raw", ".cr2", ".nef", ".sr2", ".orf"};


bool endsWith(const char *str, const char *suffix);
char *strlwr(char *str);
char *join(char *firstpath, char *secondpath);


int main() {
	int index;
	
	int vid_counter, msc_counter, pic_counter, doc_counter;
	vid_counter = msc_counter = pic_counter = doc_counter = 0;
	
	char vid_list[255][255];
	char msc_list[255][255];
	char pic_list[255][255];
	char doc_list[255][255];

	struct passwd *pw = getpwuid(getuid());
	char *homeDirectory = pw -> pw_dir;


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
	struct dirent *dir;
	
	size_t len_video_ext = len(video_ext); // length of video_ext array (list)
	size_t len_audio_ext = len(audio_ext);
	size_t len_document_ext = len(document_ext);
	size_t len_image_ext = len(image_ext);

	directory = opendir(LookUpDirectory);
	if (directory) {
	    	while ((dir = readdir(directory)) != NULL) {
		      char *list = dir -> d_name; // list of all files founded in look up directory (LookUpDirectory)

		      char *listlwr = (char *)malloc(250 * sizeof(char));
                      strcpy(listlwr, list); // cloning list in listlwr
		      strlwr(listlwr); // lowering listlwr to compare it with lower listed extensions safely
		      
		      // If any listed file from the look up directory (LookUpDirectory) ends with any of video extensions (videos_ext) list
		      for (index = 0; index < len_video_ext; index++) {
			  if (endsWith(listlwr, video_ext[index])) {
				char *source = join(LookUpDirectory, list); // Joining Lookup directory and all files founded in
				char *destination = join(DestinationForVideos, list); // Joining destionation directory and files wanted to be there
				
				/* if show is true script will show up all of matches */
				if (show) {
				   strcpy(vid_list[vid_counter], source);
				   vid_counter++;
				}				

				/* if execute is true move files from where it was to the desired destination */
				if (execute) {
				    if (rename(source, destination) != 0) perror("Error");
				}

				free(source);
				free(destination);
			  }
		      }

		      // If any listed file from the look up directory (LookUpDirectory) ends with any of audio extensions (audios_ext) list
		      for (index = 0; index < len_audio_ext; index++) {
			  if (endsWith(listlwr, audio_ext[index])) {
				char *source = join(LookUpDirectory, list);
				char *destination = join(DestinationForMusic, list);

				/* if show is true script will show up all of matches */
				if (show) {
				   strcpy(msc_list[msc_counter], source);
				   msc_counter++;
				}

				/* if execute is true move files from where it was to the desired destination */
				if (execute) {
				    if (rename(source, destination) != 0) perror("Error");
				}

				free(source);
				free(destination);
			  }
		      }

		      // If any listed file from the look up directory (LookUpDirectory) ends with any of image extensions (images_ext) list
		      for (index = 0; index < len_image_ext; index++) {
			  if (endsWith(listlwr, image_ext[index])) {
				char *source = join(LookUpDirectory, list);
				char *destination = join(DestinationForPictures, list);

				/* if show is true script will show up all of matches */
				if (show) {
				   strcpy(pic_list[pic_counter], source);
				   pic_counter++;
				}

				/* if execute is true move files from where it was to the desired destination */
				if (execute) {
				    if (rename(source, destination) != 0) perror("Error");
				}

				free(source);
				free(destination);
			  }
		      }

		      // If any listed file from the look up directory (LookUpDirectory) ends with any of document extensions (documents_ext) list
		      for (index = 0; index < len_document_ext; index++) {
			  if (endsWith(listlwr, document_ext[index])) {
				char *source = join(LookUpDirectory, list);
				char *destination = join(DestinationForDocuments, list);

				/* if show is true script will show up all of matches */
				if (show) {
				   strcpy(doc_list[doc_counter], source);
				   doc_counter++;
				}

				/* if execute is true move files from where it was to the desired destination */
				if (execute) {
				    if (rename(source, destination) != 0) perror("Error");
				}

				free(source);
				free(destination);
			  }
		      }
		      free(listlwr);
		}
		if (show) {
		   for (index = 0; index < vid_counter; index++) {
		       if (index == 0)
			  printf("----------------------------- VIDEOS ----------------------------------\n\n");

		       printf("%s\n", vid_list[index]);

		       if (index == (vid_counter - 1))
			  printf("\n--------------------------- END OF VIDEOS -----------------------------\n\n\n");
		   }
	           
                   for (index = 0; index < msc_counter; index++) {
		       if (index == 0)
			  printf("----------------------------- AUDIOS ---------------------------------\n\n");

		       printf("%s\n", msc_list[index]);

		       if (index == (msc_counter - 1))
			  printf("\n------------------------- END OF AUDIOS ----------------------------\n\n\n");
		   }

                   for (index = 0; index < pic_counter; index++) {
		       if (index == 0)
			  printf("---------------------------- PICTURES ---------------------------------\n\n");

		       printf("%s\n", pic_list[index]);

		       if (index == (pic_counter - 1))
			  printf("\n--------------------------- END OF PICTURES ---------------------------\n\n\n");
		   }

                   for (index = 0; index < doc_counter; index++) {
		       if (index == 0)
			  printf("------------------------------- DOCUMENTS -----------------------------\n\n");

		       printf("%s\n", doc_list[index]);

		       if (index == (doc_counter - 1))
			  printf("\n--------------------------- END OF DOCUMENTS  -------------------------\n\n\n");
		   }
                   
		   printf("\n--------- SUMMARY ---------\n");
  		   printf("All videos founded: %d\n", vid_counter);
		   printf("All Audios founded: %d\n", msc_counter);
		   printf("All Documents founded: %d\n", doc_counter);
		   printf("All Pictures founded: %d\n", pic_counter);
		   printf("\n---------- END -----------\n\n\n");
		}
    		closedir(directory);
	} else {
          perror("Error");
	}
	return 0;
}


/* Function to check if string ends with given suffix */
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
   char *fullpath = (char *)malloc(250 * sizeof(char));
   strcpy(fullpath, firstpath);
   return strcat(fullpath, secondpath);
}

