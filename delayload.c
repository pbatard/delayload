#include <stdio.h>
#include <windows.h>

// Uncomment the following to use the workaround
//#define WORKAROUND
#ifdef WORKAROUND

#undef DECLSPEC_IMPORT
#ifdef __GNUC__
#define DECLSPEC_IMPORT __attribute__((visibility("hidden")))
#else
#define DECLSPEC_IMPORT __declspec(dllimport)
#endif

#endif	// WORKAROUND

#include <wininet.h>

int main(int argc, char* argv[])
{
	const char* url = "https://www.google.com";
	char hostname[64], urlpath[128];
	URL_COMPONENTSA UrlParts = { sizeof(URL_COMPONENTSA), NULL, 1, (INTERNET_SCHEME)0,
		hostname, sizeof(hostname), 0, NULL, 1, urlpath, sizeof(urlpath), NULL, 1 };

	printf("Delay loading test start\n");

	if (!InternetCrackUrlA(url, (DWORD)strlen(url), 0, &UrlParts))
		printf("Unable to decode URL\n");

	printf("Delay loading test passed!\n");

	return 0;
}
