#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define SARMAG 8
#define ARMAG "!<arch>\n"
#define HEADER_READ_SIZE 60
#define BLOCKSIZE 1024

int main ( int argc, char *argv[])
{

	int inputFd;
	ssize_t numRead;
	char buffer[BLOCKSIZE]; /*File buffer*/
	char ARMAG_BUFFER[SARMAG + 1];
	unsigned long filesize;
	long date;
	struct tm timestruct;
	static char timestr[100];
	struct stat fileStat;

	struct ar_hdr
	{
		char	ar_name[16];
		char	ar_date[12];
		char	ar_uid[6];
		char	ar_gid[6];
		char	ar_mode[8];
		char	ar_size[10];
		char	ar_fmag[2];
	};

	struct ar_hdr *ar;
	ar = (struct ar_hdr *)malloc(sizeof(struct ar_hdr));
	
	if (argc <= 2){
		printf("Usage: %s key afile name ... \n", argv[0]);
	}

	/*Prints out the name of the file*/
	if ((argc == 3) && strcmp(argv[1], "t") == 0){

		inputFd = open(argv[2], O_RDONLY);

		if (inputFd == -1){
			printf("Error opening file %s", argv[1]);
			exit(-1);
		}

		numRead = read(inputFd, buffer, 8);
		if (strncmp(buffer, ARMAG, 8) != 0){

			perror("Unknown archive file \n");
			exit(-1);

		}
		int i = 0;
		while((numRead = read(inputFd, buffer, HEADER_READ_SIZE)) == HEADER_READ_SIZE){
			
			sscanf(buffer, "%s %s %s %s %s %s %s", ar.ar_name, ar.ar_date, ar.ar_uid, ar.ar_gid, ar.ar_mode, ar.ar_size, ar.ar_fmag);
			buffer[numRead] = '\0';
			filesize = strtoul(ar.ar_size, NULL, 10);

			int i = 0;
			while(ar.ar_name[i] != '/'){
				printf("%c", ar.ar_name[i]);
				i++;
			}
			printf("\n");
		
			lseek(inputFd, filesize, SEEK_CUR);
			
			if (filesize % 2 != 0){
				lseek(inputFd, 1, SEEK_CUR);
			}
	
		}	

		exit(EXIT_SUCCESS);

	}/* -t option */

	/* VERBOSE OPTION */
	if ((argc == 3) && strcmp(argv[1], "vt") == 0){

		inputFd = open(argv[2], O_RDONLY);

		if (inputFd == -1){
			printf("Error opening file %s", argv[1]);
			exit(-1);
		}

		numRead = read(inputFd, buffer, 8);
		if (strncmp(buffer, ARMAG, 8) != 0){

			perror("Unknown archive file \n");
			exit(-1);
		}
		int i = 0;
		while((numRead = read(inputFd, buffer, HEADER_READ_SIZE)) == HEADER_READ_SIZE){
			
			sscanf(buffer, "%s %s %s %s %s %s %s", ar.ar_name, ar.ar_date, ar.ar_uid, ar.ar_gid, ar.ar_mode, ar.ar_size, ar.ar_fmag);
			buffer[numRead] = '\0';
			filesize = strtoul(ar.ar_size, NULL, 10);
			
			printf("%s/%s   %s ", ar.ar_uid, ar.ar_gid, ar.ar_size);
			//printf("%s ", ar.ar_date);

			date = strtol(ar.ar_date, NULL, 10);
			timestruct = *localtime(&date);
			strftime(timestr, sizeof(timestr), "%b %e %H:%M %Y", &timestruct);
			printf("%s ", timestr);
		
			int i = 0;
			while(ar.ar_name[i] != '/'){
				printf("%c", ar.ar_name[i]);
				i++;
			}
			printf("\n");
			
			lseek(inputFd, filesize, SEEK_CUR);
			
			if (filesize % 2 != 0){
				lseek(inputFd, 1, SEEK_CUR);
			}
	
		}	

		exit(EXIT_SUCCESS);
	}/* End V OPTION */

	if ((argc == 4) && strcmp(argv[1], "q") == 0){
		inputFd = open(argv[3], O_RDONLY);

		if (stat(argv[3], &fileStat) < 0){
			printf("Error opening file \n");
			exit(-1);
		}

		strcpy(ar.ar_name,argv[3]);
		ar->ar_size = fileStat.st_size;
		/*
		ar.ar_size = fileStat.st_size;
		ar.ar_gid = fileStat.st_gid;
		ar.ar_uid = fileStat.st_uid;
		ar.ar_mode = fileStat.st_mode;
		ar.ar_date = fileStat.st_mtime;
		*/
		printf("File Name: %c \n",ar.ar_name);
		printf("File Size: %d \n",ar.ar_size);
		printf("File Mode: %d \n",fileStat.st_mode);
		printf("File Date: %d \n",fileStat.st_mtime);
		printf("File GID: %d \n",fileStat.st_gid);
		printf("File UID: %d \n",fileStat.st_uid);


		if (inputFd == -1){
			exit(-1);
		}



	}/* End Q OPTION */


}/* End Main */

