#include "text.h"

#define ISLET(letter) letter >= L'А' && letter <= L'я'
#define ISSPL(letter) letter == L'Ё' || letter == L'ё'

//*************************************************************************************************

/*!
    The same for scmp() from file scmp_en.c function, but compares russian strings.
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
        while (str1 [pos1] && !isalpha_ru (str1 [pos1]))
                pos1++;

        while (str2 [pos2] && !isalpha_ru (str2 [pos2]))
                pos2++;

        wchar_t let1 = towlower (str1 [pos1]);
        wchar_t let2 = towlower (str2 [pos2]);

        if (let1 != let2)
        {
            if (ISLET(let1) && ISLET(let2))
                return let1 - let2;
            if (ISSPL(let1))
            {
                if (let2 < L'ж') return  1;
                if (let2 > L'е') return -1;
            }
            if (ISSPL(let2))
            {
                if (let1 < L'ж') return -1;
                if (let1 > L'е') return  1;
            }    
        }

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
    The same for scmp_rev() from scmp_en.c fuctions, but compares russian strings.
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
        while (pos1 > 0 && !isalpha_ru(str1[pos1]))
                pos1--;

        while (pos2 > 0 && !isalpha_ru(str2[pos2]))
                pos2--;

        wchar_t let1 = towlower (str1 [pos1]);
        wchar_t let2 = towlower (str2 [pos2]);

        if (let1 != let2)
        {
            if (ISLET(let1) && ISLET(let2))
                return let1 - let2;
            if (ISSPL(let1))
            {
                if (let2 < L'ж') return  1;
                if (let2 > L'е') return -1;
            }
            if (ISSPL(let2))
            {
                if (let1 < L'ж') return -1;
                if (let1 > L'е') return  1;
            }    
        }

        pos1--;
        pos2--;
    }

    return 0;
}
