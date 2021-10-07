#include "text.h"

//*************************************************************************************************

/*!
    \param[in] s1 - first string, s2 - second string.
    \return 0 - strings are equal, non-zero positive value - s1 is "bigger" than s2, non-zero negative value - s1 is "lower" than s2.
    Comparator for english strings; compares using alphabet: string is bigger means last unequal symbol of compared strings is farther in alphabet.
*/

int scmp (const void *s1, const void *s2)
{
    if (!s1 || !s2)
    {
        perror ("scmp () received invalid strs: \n");
        exit (EXIT_FAILURE);
    }

    size_t pos1 = 0, pos2 = 0;

    wchar_t *str1 = ((const Str *) s1)->str;
    wchar_t *str2 = ((const Str *) s2)->str;
    
    while (str1 [pos1] && str2 [pos2])
    {
        while (str1 [pos1] && !iswalpha (str1 [pos1]))
                pos1++;

        while (str2 [pos2] && !iswalpha (str2 [pos2]))
                pos2++;

        wchar_t let1 = towlower (str1 [pos1]);
        wchar_t let2 = towlower (str2 [pos2]);

        if (let1 != let2)
            return let1 - let2;

        if (let1 == '\0' || let2 == '\0')
            return 0;

        if (let1 && let2)
        {
            pos1++;
            pos2++;
        }
    }

    return 0;
}

//*************************************************************************************************

/*!
    The same for scmp() function, but compares strings from the end.
*/

int scmp_rev (const void *s1, const void *s2)
{
    if (!s1 || !s2)
    {
        perror ("scmp_rev () received invalid strs: \n");
        exit (EXIT_FAILURE);
    }

    wchar_t *str1 = ((const Str *) s1)->str;
    wchar_t *str2 = ((const Str *) s2)->str;

    int pos1 = ((const Str *) s1)->slen - 1;
    int pos2 = ((const Str *) s2)->slen - 1;

    while (pos1 >= 0 && pos2 >= 0)
    {
        while (pos1 > 0 && !iswalpha (str1 [pos1]))
                pos1--;

        while (pos2 > 0 && !iswalpha (str2 [pos2]))
                pos2--;

        wchar_t let1 = towlower (str1 [pos1]);
        wchar_t let2 = towlower (str2 [pos2]);

        if (let1 != let2)
            return let1 - let2;

        pos1--;
        pos2--;
    }

    return 0;
}
