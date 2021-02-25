#include "read_file.h"

char* read_file(const char* filename)
{
	FILE* file = fopen(filename,"rb");
	long size = 0;
	char* src = calloc(1,sizeof(*src));

	if(file)
	{
		fseek(file,0,SEEK_END);
		size = ftell(file);
		fseek(file,0,SEEK_SET);

		if(size > 0)
		{
			src = realloc(
				src,
				size*sizeof(*src)
			);
			fread(src,1,size,file);
			return src;
		}
		fprintf(stderr,"Error reading file size.\n");
		exit(EXIT_FAILURE);
	}
	fprintf(stderr,"Error: file %s does not exist.\n",filename);
	exit(EXIT_FAILURE);
}
