/*
 * In the game of boggler, players searches for words that can be constructed from
 * adjacent letters on the boggle board. So letters can be horizontal, vertical, and
 * diagonal, but they can only be used once. Words must be at least three letters long.
 *
 * If multiple combinations produce the same word, then it will be output multiple
 * times, so pipe this output to sort(1) and then uniq(1), for example:
 *
 * 	$ boggle | sort | uniq
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// The traditional game is 4 x 4
#define M		4
#define	N		4

// The English dictionary
#define	ALPHABET_SIZE	26
#define	IDX(x)		toupper((x)) - 'A'

typedef struct lexicon {
	char		word[M * N];
	int		len;
	struct lexicon	*next;
} lex_t;

// Can be replaced with an extensive file and I/O code to process it
char dbase[][M * N] = { "CAT", "ZIG", "HAT", "THE", "WHAT", "HECK", "SEVEN", "EIGHT",
			"TEKE", "EPSILON", "KAPA", "HOWZIT", "TAU", "THERE", "TEN" };

void
printLexicon(lex_t lexicon[])
{
	for (int i = 0; i < ALPHABET_SIZE; ++i) {
		lex_t *node = &lexicon[i];

		printf("i=%d ", i);
		for (;;) {
			if (strlen(node->word) > 0)
				printf("%s(%d), ", node->word, node->len);
			if (node->next == NULL)
				break;
			node = node->next;
		}
		printf("\b\b  \n");
	}
}

/*
 * Load the lexicon with words from the dictionary database.
 */
void
parse_dbase(lex_t lexicon[])
{
	int idx;
	int num_words = sizeof(dbase) / (M * N);

	for (int i = 0; i < num_words; ++i) {
		lex_t *node = &lexicon[IDX(dbase[i][0])];

		if (strlen(node->word) == 0) {
			strncpy(node->word, dbase[i], sizeof(dbase[i]));
			node->len = strlen(node->word);
			continue;
		}

		while (node->next)
			node = node->next;
		node->next = calloc(1, sizeof(lex_t));
		strncpy(node->next->word, dbase[i], sizeof(dbase[i]));
		node->next->len = strlen(node->next->word);
	}
#if DEBUG
	printLexicon(lexicon);
#endif
}

/*
 * Look up words with the same first letter, and only compare matching string lengths.
 * 
 */
bool
isWord(lex_t *lp, char str[M * N])
{
	int sizestr = strlen(str);

	if (sizestr < 3)	// Per boggle board rules of play
		return(false);

	while (lp != NULL && lp->len > 0) {
		if (sizestr == lp->len && strncmp(lp->word, str, lp->len) == 0)
			return (true);
		lp = lp->next;
	}
	return (false);
}

/*
 * Build candidate strings from the boggle board, but only to the size of the
 * max length of strings in the lexicon that begin with the same first letter.
 */
void
traverse(int i, int j, int max, lex_t *lp, bool visited[M][N],
    char boggle[M][N], char str[M * N]) 
{

	visited[i][j] = true;
	strncat(str, &boggle[i][j], 1);

	if (isWord(lp, str))
		printf("%s\n", str);

	for (int row = i - 1; row <= i + 1 && row < M; row++) {
		if (row < 0)
			continue;
		for (int col = j - 1; col <= j + 1 && col < N; col++) {
			if (col < 0 || visited[row][col]) 
				continue;
			if (strlen(str) < max)
				traverse(row, col, max, lp, visited, boggle, str); 
		}
	}
	  
	str[strlen(str) - 1] = '\0';
	visited[i][j] = false; 
}

/*
 * Max string length for words starting with the specified letter.
 */
int
maxLen(lex_t *lp)
{
	int	max = 0;

	for (lex_t *node = lp; node; node = node->next) {
		if (node->len > max)
			max = node->len;
	}
	return (max);
}

/*
 * Search the lexicon for words that start with the same first letter.
 */
void
search(lex_t lexicon[], char boggle[M][N])
{
	char	str[M * N] = { 0 };
	bool	visited[M][N] = { { false } };

	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			int	idx = IDX(boggle[i][j]);
			int	max = maxLen(&lexicon[idx]);

			if (strlen(lexicon[idx].word) == 0)
				continue;
			traverse(i, j, max, &lexicon[idx], visited, boggle, str); 
		}
	}
}

int
main()
{
	lex_t	lexicon[ALPHABET_SIZE] = { 0 };
	char	boggle[M][N] = { { 'G', 'I', 'Z', 'C' }, 
				 { 'U', 'E', 'K', 'E' }, 
				 { 'C', 'A', 'T', 'N' },
				 { 'H', 'S', 'E', 'D' } }; 

	parse_dbase(lexicon);
	search(lexicon, boggle);
}
