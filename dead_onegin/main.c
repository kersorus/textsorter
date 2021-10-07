#include "text.h"
#include <locale.h>
#include "qsort.h"
#include "scmp.h"

//*************************************************************************************************

int main (int argc, char *argv[])
{
    setlocale (LC_CTYPE, "C.UTF-8");

    File file = {0};

    opener     (&file, argc, argv);
    get_file   (&file);
    str_data   (&file);

    print_file (&file, "original", 0);

    qsort_my (file.strs, file.nstr, sizeof (Str), scmp);
    print_file (&file, "text1", 1);

    qsort_my (file.strs, file.nstr, sizeof (Str), scmp_rev);
    print_file (&file, "text2", 1);

    free   (file.buf_char);
    free   (file.buf);
    free   (file.strs);
    fclose (file.text);

    printf ("#  results here:\n"
            "#  1) 'original' <- original text;\n"
            "#  2) 'text1' <- sorted text;\n"
            "#  3) 'text2' <- sorted text (in reverse).\n");

    return 0;
}
