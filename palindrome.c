#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/* Simple minded string reversal */
static void
reverse_str(char *str)
{
	char   tmp;
	int    i, j, len = strlen(str);
		    
	for (i = 0, j = len - 1; i < len && j > i && j > 0; ++i, --j) {
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
	}
}                                                

/* Test obverse and reverse strings for palindrome */
static bool
is_palindrome(const char *str)
{
	char c, *obverse, *reverse;
	int  diff, len;

	// Check for NULL
	if (str == NULL) {
		printf("'' v '' ");
		return (true);
	}

	len = strlen(str);
	obverse = calloc(1, strlen(str) * sizeof(char *));
	reverse = calloc(1, strlen(str) * sizeof(char *));

	// Ignore case, white space, and punctuation
	for (int i = 0, j = 0; i < len; ++i) {
		if (isalnum(str[i])) {
			obverse[j++] = tolower(str[i]);
		}
	}

	strcpy(reverse, obverse);
	reverse_str(reverse);
	printf("'%s' v '%s' ", obverse, reverse);

	diff = strncmp(obverse, reverse, len);
	free(obverse);
	free(reverse);
	return ((diff == 0) ? true : false);
}

static void
palindrome(const char *str)
{
	printf("%s a palindrome.\n", is_palindrome(str) ? "is" : "is not");
}

int
main()
{
	const char 	*one = "Deleveled";
	const char 	*two = "How about that";
	const char 	*three = "Never odd or even";

	palindrome(one);
	palindrome(two);
	palindrome(three);
	palindrome(NULL);
	exit (0);
}
