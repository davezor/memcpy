#include <stdio.h>
#include <string.h>
#include <stdint.h>


void *mymemcpy(void *destination, void *source, size_t len) //pointer to copy values to, constant pointer to copy values from, size to copy
{
    size_t i; //iterator

    printf("Source:         %p\n", source);
    printf("Destination:    %p\n", destination);

    if ((sizeof(destination) % sizeof(long) == 0) && (sizeof(source) % sizeof(long) == 0) && (len % sizeof(long) == 0)) //all values are properly aligned and can be read in words instead of bytes
    {
    long *dst = destination;
    long *src = source;

    for (i=0; i<len/sizeof(long); i++)  //iterate over the number of words to be read, a word at a time, should be more efficient
        {
            dst[i] = src[i];
        }

        printf("\n\n len = %d, Done by words \n\n", len);

    } else {    //unaligned values must be read as bytes
        char *dst = destination;
        char *src = source;

        for (i=0; i<len; i++)       //iterate over the number of bytes to be read, a byte at a time
        {
            dst[i] = src[i];
        }

        printf("\n\n len = %d, Done by bytes \n\n", len);
    }

}

//driver
int main() {
	char a[5] = "aaaa";
	char b[5];
	mymemcpy(b, a, 5 * sizeof(char));   //should use the byte branch

	printf("%s", b);
	puts("\n\n");

	char c[8] = "aaaabbb";
	char d[8];
    mymemcpy(d, c, 8 * sizeof(char)); //should use the word branch

	printf("%s\n", d);

	struct struct_a
	{
	    short int t_a;
	    short int t_b;
	    char b[4];
	    double f;
	}struct_1, struct_2;

	struct_1.t_a = 4;
	struct_1.t_b = 99;
	strcpy(struct_1.b, "abc");
	struct_1.f = 99.999999;

	mymemcpy(&struct_2, &struct_1, sizeof(struct_1));   //word branch again

	printf("%d, %d, %s, %f\n", struct_2.t_a, struct_2.t_b, struct_2.b, struct_2.f);


		struct struct_b //example of inefficient memory layout of struct members
	{
	    short int t_a;
	    double f;
	    short int t_b;
	    char b[4];
	}struct_3, struct_4;

	struct_3.t_a = 4;
	struct_3.t_b = 99;
	strcpy(struct_3.b, "abc");
	struct_3.f = 99.999999;

	mymemcpy(&struct_4, &struct_3, sizeof(struct_3));

	printf("%d, %d, %s, %f\n", struct_4.t_a, struct_4.t_b, struct_4.b, struct_4.f);



	return 0;

}
