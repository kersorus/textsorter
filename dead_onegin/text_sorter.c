#include "text.h"
#include <locale.h>
#include "qsort.h"
#include "scmp.h"

//*************************************************************************************************

int main (int argc, char *argv[])
{
    setlocale (LC_CTYPE, "C.UTF-8");

    remove ("log");

    File file = {0};

    opener (&file, argc, argv);
    get_file   (&file);
    str_data   (&file);

    qsort_my (file.strs, file.nstr, sizeof (Str), scmp);
//    qsort (file.strs, file.nstr, sizeof (Str), scmp);
    print_file (&file, "text1");

    qsort_my (file.strs, file.nstr, sizeof (Str), scmp_rev);
//    qsort (file.strs, file.nstr, sizeof (Str), scmp_rev);
    print_file (&file, "text2");

    free (file.buf);
    free (file.strs);
    fclose (file.text);

    printf ("#  results here:\n"
            "#  1) 'text1' <- sorted text;\n"
            "#  2) 'text2' <- sorted text (in reverse).\n");

    return 0;
}
