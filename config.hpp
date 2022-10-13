#define POP stack_pop(stk)

#define PUSH(num) stack_push(stk, num)

#define JUMP_COND(sign)                \
        if (POP sign POP) {            \
            ip++;                      \
            int a = program->cmd[ip];  \
            ip = a;                    \
        }                              \
        

#define OPERATION(sign)  \
        int a = POP;     \
        int b = POP;     \
        PUSH(b sign a);     \


DEF_CMD(HLT, 0, 0,
        {stack_dtor(stk);})

DEF_CMD(PUSH, 1, 1, 
        {int arg = get_arg(program, program->cmd[ip], &ip);
        PUSH(arg);})

DEF_CMD(ADD, 2, 0, OPERATION(+))

DEF_CMD(SUB, 3, 0, OPERATION(-))

DEF_CMD(MUL, 4, 0, OPERATION(*))

DEF_CMD(DIV, 5, 0, OPERATION(/))

DEF_CMD(OUT, 6, 0,             
        {
        printf("result %d\n", POP);})

DEF_CMD(IN, 7, 0,
        {int a = 0;
        scanf("%d", &a);
        PUSH(a);})

DEF_CMD(JMP, 8, 1, 
        {ip++;
        int a = program->cmd[ip];
        ip = a;})

DEF_CMD(DUP, 9, 0,             
        {int a = POP;
        PUSH(a);
        PUSH(a);})

DEF_CMD(JB, 10, 1, JUMP_COND(<))

DEF_CMD(JBE, 11, 1, JUMP_COND(<=))

DEF_CMD(JA, 12, 1, JUMP_COND(>))

DEF_CMD(JAE, 13, 1, JUMP_COND(>=))

DEF_CMD(JE, 14, 1, JUMP_COND(==))

DEF_CMD(JNE, 15, 1, JUMP_COND(!=))




