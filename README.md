## Mv-files

Mv-files is C script for moving files ends with particular suffix (extension) from one folder to the desired destination on the same file system.

## Why I made this?

What if is you asking me? I will say **Good question**, Since I'm dev I mean Junior one I download bunch of different files
and all of them by default stored in `Downloads` and I know I can select all, <kbd>ctrl</kbd> + <kbd>x</kbd> and <kbd>ctrl</kbd> + <kbd>v</kbd>
where I want but that will still not be the great and I know it doesn't sounds tough because where I pasted it, will still not organised there will
be html docs , videos, audios, xls files, images, etc.
So that's why I created script where you can simply categories files by their extensions and move them where you want by their categories. and also
files can't only be in the Downloads can be everywhere you want it to be. just continue to read and you'll star the repo later.

## Author
**Gitlab** [@umutambyi-gad](https://gitlab.com/umutambyi-gad) <br>
**Website:** [umutambyigad](https://umutambyigad.herokuapp.com) <br>
**Stackoverflow:** [@umutambyi-gad](https://stackoverflow.com/users/13536893/umutambyi-gad) <br>
**Twitter:** [@umutambyi_gad](https://twitter.com/umutambyi_gad) <br>
**Linkedin:**  [@umutambyi-gad](https://www.linkedin.com/in/umutambyi-gad/) <br>
**Dev.to:** [@umutambyigad](https://dev.to/umutambyigad) <br>
**Email:** [umutambyig@gmail.com](mailto:umutambyig@gmail.com) <br>


## Description

This script has pre-defined global constant variables which are (2d arrays). to make it easy it's lists(arrays) of
string of different types of extensions.
```C
const char* videos_ext[] = {".mp4", ".mpg", ...};
const char* audios_ext[] = {".mp3", ".wav", ...};
const char* documents_ext[] = {".docx", ".html", ...};
const char* images_ext[] = {".jpg", ".png", ...};
```
so understandable, `videos_ext` means ***video extensions*** is list of all possible video extensions and you can simply customize them
no big deal.

And also there are another defined global variables which are

```C
char LookUpDirectory[250];
char DestinationForVideos[250];
char DestinationForMusic[250]; // I assume that all musics are audios.
char DestinationForPictures[250];
char DestinationForDocuments[250];
```
Guess the above variable names are so descriptive. Ok but let me explain this in summary.
```C
strcat(strcpy(LookUpDirectory, homeDirectory), "/Downloads/");
```
The above is like an initialization of `LookUpDirectory`. as you can understand `LookUpDirectory` is the directory where to look up
all file that you want to migrate and by default is in the Downloads - `C:/Users/YoungLady/Downloads/` or `/home/kali/Downloads/`.
don't worry about the platform I handled that by joining home directory with downloads where home directory can be different.
so what if you want to change `LookUpDirectory` so simple just comment my line of code or get rid of it and do something like
```C
strcpy(LookUpDirectory, "C/Users/ImDifferent/ForMeLookUpHere"); // I think you don't need to join your path with the home directory
```
then done.
so you can still do the same on destination ones (`DestinationForVideos`, `DestinationForMusic`, ...)
And you can now compile your code that's what I wanted you to know first.
**wait, wait, wait** there are two more important defined macros with bool type as value 
```C
#define show true
#define execute true
```
both by default are `true` so here is what these macros do, if `show` is true the script just print in console all matches
and their categories and after give out an overview of them I called it summary. see the picture bellow -
![when show is true](https://user-images.githubusercontent.com/65312850/113211387-ee759400-9264-11eb-848d-51f395d79548.png)

and if `execute` is true, simple the script will be executed I'll suggest to initialize this to `false` and first checkout the matches where
`show` will be only one set to `true`.
And now you're ready to compile **nothing to wait now.**

## Usage

Just compile the code with your favorite installed compiler here is how I did -
```bash
gcc main.c -o main.exe
```
Thereafter run the `main.exe`, On windows just navigate to its location and double click on generated executable file or run it from your command line like
```bash
main.exe
```
On Linux I think it's something like
```bash
./main.exe
```
Then done. just check if everything goes well and if is not and can't figure out why? you can simply raise an issue I will be right there
## License
This project is under the [MIT](https://github.com/umutambyi-gad/Mv-files/blob/master/LICENSE) License
