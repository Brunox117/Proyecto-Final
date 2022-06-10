#include <stdio.h>
#include <dirent.h>

int main(void)
{
	char *filename = "listado.txt";
	FILE *fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("Error opening the file %s", filename);
		return -1;
	}
	struct dirent *de;
	DIR *dr = opendir(".");
	if (dr == NULL)
	{
		printf("Error opening the file %s", filename);
		printf("Could not open current directory");
		return 0;
	}
	while ((de = readdir(dr)) != NULL)
	{
		fprintf(fp, "%s\n", de->d_name);
	}
	fclose(fp);
	closedir(dr);
}
