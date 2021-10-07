int decode (File *file)
{
    wchar_t *buf_dec = calloc (file->size, sizeof (wchar_t));
    if (!buf_dec)
    {
        printf ("Error: decode () line %d:\n", __LINE__ - 3);
        printf ("    can't allocate memory for\n"
                "    buffer with decoded symbols.\n");
        exit (EXIT_FAILURE);
    }
    size_t symb = 0;

    for (size_t let = 0; let < file->size; let++)
    {
        size_t shift    = 7;
        size_t byte_amt = 0;
    
        while (file->buf_char [let] & (1 << shift) && shift)
        {
            byte_amt++;
            shift--;
        }

        if (byte_amt == 1 || byte_amt > 4)
        {
            return 1;
        }

        if (!byte_amt)
        {
            buf_dec [symb] = (wchar_t) file->buf_char [let];
            symb++;
            continue;
        }

        wchar_t code = 0;
        wchar_t fund = 1;

        let += byte_amt - 1;

        for (size_t bit = 0; bit < CODE_POSITIONS; bit++)
        {
            if (bit % 8 == 6)
            {
                bit += 2;
                let--;
            }
            code += fund * ((file->buf_char [let] >> (bit % 8)) & 1);
            fund *= 2;
        }

        let += byte_amt - 1;
        buf_dec [symb] = code;
        symb++;
    }

    free (file->buf_char);

    buf_dec = (wchar_t *) realloc (buf_dec, symb * sizeof (wchar_t));
    if (!buf_dec)
    {
        printf ("Error: decode () line %d:\n", __LINE__);
        printf ("    can't reallocate memory for\n"
                "    buffer with decoded symbols.\n");
        exit (EXIT_FAILURE);
    }

    file->buf = buf_dec;
    file->size = symb;

    return 0;
}
