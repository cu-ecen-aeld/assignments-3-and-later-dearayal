#include <stdio.h>
#include <syslog.h>

int main(int argc, char *argv[]){

	FILE * fp;
	openlog(NULL, 0, LOG_USER);

	syslog(LOG_DEBUG, "%d", argc);	
	for (int i = 1; i < argc; i++){
		syslog(LOG_DEBUG, "%s", argv[i]);
	}
	if (argc != 3 ) {
		syslog(LOG_ERR, "Invalid  Number of arguments: %d", argc);
	  	syslog(LOG_ERR, "Usage: writer <writefile> <writestr>");
		return 1;  // Exits with value 1 error and print statement
	}

	syslog(LOG_DEBUG, "Writing %s to %s", argv[2], argv[1]);
   	fp = fopen (argv[1], "w");
   	fprintf(fp, "%s", argv[2]);
	fclose(fp);
	
	return 0;
}
