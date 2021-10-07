#include "qsort.h"

//*************************************************************************************************

/*!
    \brief sorts array
    \param[in] array - ptr to array's start, asize - array's size, esize - array's elem size, scmp - comparator.
    Function the same as classic quick sort.
*/

void qsort_my (void *array, size_t asize, size_t esize, int (*scmp) (const void *, const void *))
{
    void *stdval = array + esize * (asize - 1);
    void *sep = array;

    if (asize > 1)
    {
        for (size_t index = 0; index < asize; index++)
        {    
            if (scmp (stdval, array + esize * index) > 0)
            {
                swapv (sep, array + esize * index, esize);
                sep += esize;
            }
        }

        swapv (sep, stdval, esize);

        qsort_my (array, (sep - array) / esize, esize, scmp);
        qsort_my (sep + esize, (stdval - sep) / esize, esize, scmp);
    }    
}

//*************************************************************************************************

/*!
    \param[in] e1 - first element, e2 - second element, esize - size of elements.
    Function needed for qsort; swaps e1 and e2.
*/

void swapv (void *e1, void *e2, size_t esize)
{
    for (size_t byte = 0; byte < esize; byte++)
    {
        char temp = *((char *) e1 + byte);
        *((char *) e1 + byte) = *((char *) e2 + byte);
        *((char *) e2 + byte) = temp;
    }
}
