    v6 = 0;
    v7 = 0;
    v8 = 0;
    v11 = 0;
    scan 11char->Buffer
    if ( strlen(Buffer) == 10 )
    {
        v10 = 0;
        while ( v10 < 10 )      //1:B[0]-=97
        {
        v9 = Buffer[v10];
        v9 -= 97;
        switch ( v9 )
        {
            case 0:
            --v11;

            case 3:
            ++v11;

            case 18:
            v11 += 5;

            case 22:
            v11 -= 5;
        }
    LABEL_11:       //0x18==24
            if ( v11 > 0x18 || byte_402180[v11] == 48 )
            {
                puts("Wrong!");
            }
            ++v10;
        }
        }
        if ( byte_402180[v11] == 42 )
        puts("Right! The flag is md5(your input), see https://www.sojson.com/encrypt_md5.html");
    else
    {
        puts("Wrong!");
    }