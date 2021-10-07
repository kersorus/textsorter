#include "text.h"

#define CODE_POSITIONS 8 * byte_amt - byte_amt - 1

//*************************************************************************************************

/*!
    \param[in] file - struct of type File, that keeps info about sorted file; argc - num of main() args; argv - array w main()'s args (argv[1] - sorted file name).
    Function that open file and allocate buffer for it.
*/

int opener (File *file, int argc, char **argv)
{
    if (argc >= 2)
        file->text = fopen (argv [1], "r");
    else
        file->text = fopen ("text", "r");

    if (!(file->text))
    {
        perror ("problema with reading file");
        exit (EXIT_FAILURE);
    }

    fseek (file->text, 0, SEEK_END);
    file->size = ftell (file->text);
    fseek (file->text, 0, SEEK_SET);
    file->buf_char = (char *) calloc (file->size, sizeof (char));

    if (!(file->buf_char))
    {
        perror ("can't read file into buffer");
        exit (EXIT_FAILURE);
    }

    return 0;
}

//*************************************************************************************************

/*!
    \param[in] file - struct of type File, that keeps info about sorted file.
    Allocates massive for ptrs of string's starts; counts strlen; change '\n' and '\r' to '\0'.
*/

void str_data (File *file)
{
    file->strs = (Str *) calloc (file->nstr, sizeof (Str));
    if (!(file->strs))
    {
        perror ("can't allocate memory for str ptr array:");
        exit (EXIT_FAILURE);
    }

    for (size_t let = 0, num = 0; let < file->size;)
    {
        while (let < file->size && (file->buf [let] == '\n' || file->buf [let] == '\r'))
        {
            file->buf [let] = '\0';
            let++;
            break;
        }

        if (let < file->size)
            file->strs[num].str = file->buf + let;

        size_t len = 0;
        while (let < file->size && file->buf [let] != '\n' && file->buf [let] != '\r')
        {
            let++;
            len++;
        }

        if (let < file->size)
            file->strs[num].slen = len;

        num++;
    }
}

//*************************************************************************************************

/*!
    Reads and decode file to buffer, allocated in opener(); counts string amount.
*/

void get_file (File *file)
{
    size_t nsymb = fread (file->buf_char, sizeof (char), file->size, file->text);
    if (!(nsymb == file->size))
    {
        perror ("fread returned invalid value: %lu; file size = %lu.", nsymb, file->size);
        exit (EXIT_FAILURE);
    }

    for (size_t let = 0; let < file->size;)
    {
        while (let < file->size && (file->buf_char [let] == '\n' || file->buf_char [let] == '\r'))
        {
            let++;
            break;
        }

        if (let < file->size)
            file->nstr++;

        while (let < file->size && file->buf_char [let] != '\n' && file->buf_char [let] != '\r')
            let++;
    }

    file->buf = calloc (file->size, sizeof (wchar_t));
    if (!file->buf)
    {
        perror("can't allocate memory for wchar_t buf");
        exit(EXIT_FAILURE);
    }

    size_t wchars_count = mbstowcs (file->buf, file->buf_char, file->size);
    if (wchars_count == (size_t) -1)
        printf ("Error: decode() returned 1:\n"
                "    unknown file coding system:\n"
                "    byte amount >= 4 or = 1.\n");

    file->buf = realloc (file->buf, wchars_count * sizeof(wchar_t));
    if(!file->buf)
    {
        perror("can't reallocate file.buf");
        exit(EXIT_FAILURE);
    }

    file->size = wchars_count;
}

//*************************************************************************************************

/*!
    Prints file to file w name as the second function arg.
*/

void print_file (File *file, char *name, int param)
{
    FILE *output = fopen (name, "w");

    if (param == 1)
        for (size_t num = 0; num < file->nstr; num++)
            if (line_chk (file->strs[num].str))
                fprintf (output, "%ls\n", formater(file->strs[num].str));
            else
                num++;

    if (param == 0)
        for (size_t num = 0; num < file->nstr; num++)
            fprintf(output, "%ls\n", file->strs[num].str);

    fclose (output);
}

//*************************************************************************************************

/*!
    Function that helps to print text; moves print start of string, that starts from ' ' or '\t'.
*/

wchar_t *formater (wchar_t *str_start)
{
    wchar_t *new = str_start;
    while (*new == '\t'|| *new == ' ')
        new++;

    return new;
}

//*************************************************************************************************

#ifdef EN

/*!
    Checks does line have letters.
*/

int line_chk (wchar_t *line)
{
    int letter = 0;
    for (size_t pos = 0; line [pos]; pos++)
        if (iswalpha (line [pos]))
        {
            letter++;
            break;
        }

    return letter;
}

#endif

//*************************************************************************************************

#ifdef RU

#define ISLET(letter) letter >= L'А' && letter <= L'я'
#define ISSPL(letter) letter == L'Ё' || letter == L'ё'

/*!
    Russian variant for isaplha(); checks is wchar_t symbol russian letter.
*/

int isalpha_ru (wchar_t letter)
{
    return ISLET(letter) || ISSPL(letter);
}

//*************************************************************************************************

/*!
    Checks does line have russian letters.
*/

int line_chk (wchar_t *line)
{
    int letter = 0;
    for (size_t pos = 0; line [pos]; pos++)
        if (isalpha_ru (line [pos]))
        {
            letter++;
            break;
        }

    return letter;
}

#endif
