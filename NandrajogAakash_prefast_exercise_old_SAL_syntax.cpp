#include "stdafx.h"
#include "stdio.h"
#undef __analysis_assume
#include <CodeAnalysis\SourceAnnotations.h>

#define BUF_SIZE 100
#define STR_SIZE 200
void zeroing();
char *my_alloc(size_t size) 
{
	size_t strlen(__in PCSTR s);
	char *ch  = (char *)malloc(size);
	if (ch) // FIXED
	{
	 *ch = NULL;
	 ch[size-1] = NULL; // null terminate here too, to be safe  FIXED
	}
	size_t strlen(__out LPCSTR s);
	return ch;
	}

HRESULT input([SA_Post(Tainted=SA_Yes)]char *buf) {
	return  ((buf) != NULL)?SEVERITY_SUCCESS:SEVERITY_ERROR; //FIXED
	// Configuration Properties>>C/C++>>Preporocessor>>Preprocessor Definitions>> _CRT_SECURE_NO_WARNINGS
}

[returnvalue:SA_Post(Tainted=SA_Yes)]char *do_read() {
	char *buf = my_alloc(STR_SIZE);
	printf("Allocated a string at %p", buf); //FIXED
	if (SUCCEEDED(buf)){ //FIXED
		printf("error!");

		exit(-1);
	}
	if (*buf == NULL) //FIXED
		printf("empty string");

		return buf;
}

void copy_data([SA_Post(Tainted=SA_Yes)]char*buf1,
[SA_Post(Tainted=SA_No)]char *buf2) {
	memcpy(buf2,buf1,STR_SIZE); 
	buf2[STR_SIZE-1] = NULL; // null terminate, just in case
}

void swap([SA_Post(Tainted=SA_Yes)] char *buf1,
[SA_Post(Tainted=SA_No)]char *buf2) {
	char *x = buf1;
	buf2 = buf1;
	buf1 = x;
}

int execute([SA_Pre(Tainted=SA_No)]char *buf) {
	return system( buf); // pass buf as command to be executed by the OS
}

void validate([SA_Pre(Tainted=SA_Yes)][SA_Post(Tainted=SA_No)] char *buf) {

    // This is a magical validation method, which turns tainted data
    // into untainted data, for which the code not shown.
    //
    // A real implementation might for example use a whitelist to filter
    // the string.

}

__checkReturn int test_ready() {
	size_t strlen(__in PCSTR s);
	// code not shown
	size_t strlen(__out LPCSTR s);
	return 1;
}

int APIENTRY WinMain(__out_bcount(s) HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	char *buf1 = do_read();
	char *buf2 = my_alloc(BUF_SIZE);
	if (buf2 ==NULL)
		exit(-1);
	zeroing();
	if (test_ready()) //FIXED

    validate(buf1); //FIXED
	execute(buf1);
	  
        char* buf3 = do_read();
	copy_data(buf3, buf2); 
	execute(buf2);

	char *buf4 = my_alloc(STR_SIZE);
        char *buf5 = do_read();
        swap(buf4, buf5);

		validate(buf4); //FIXED
        execute(buf4);

}

// *****************************************************************

void zero(_Out_cap_(len)int *buf, int len)
{
    int i;
    for(i = 0; i < len; i++) //FIXED
        buf[i] = 0;
}

void zeroboth(_Out_cap_(len) int *buf, int len, 
              _Out_cap_(len) int *buf3, int len3)
{
    int *buf2 = buf;
    int len2 = len;
    zero(buf2, len2);
    zero(buf3, len3);
}

void zeroboth2(_Out_cap_(len) int *buf, int len, 
	      _Out_cap_(len3) int *buf3, int len3)
{
	zeroboth(buf, len3, buf3, len);
}

void zeroing()
{
    int elements[200];
    int oelements[100];
    zeroboth2(elements, 200,oelements, 100);
}
