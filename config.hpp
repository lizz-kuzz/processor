#define POP_ stack_pop(stk)

#define PUSH_(num) stack_push(stk, num)

#define JUMP                           \
        ip++;                          \
        int ind = program->cmd[ip];    \
        ip = ind - 1;                  \

#define JUMP_COND(sign)                \
        int a = POP_;                  \
        int b = POP_;                  \
        if (b sign a)                  \
            JUMP                            
        

#define OPERATION(sign)                \
        int a = POP_;                  \
        int b = POP_;                  \
        int c = b sign a;              \
        PUSH_(c);                


DEF_CMD(HLT, 0, 0,
        {
        stack_dtor(stk);
        return 0;
        })

DEF_CMD(PUSH, 1, 1, 
        {
        int arg = get_arg(program, program->cmd[ip], &ip);
        PUSH_(arg);
        })

DEF_CMD(ADD, 2, 0, OPERATION(+))

DEF_CMD(SUB, 3, 0, OPERATION(-))

DEF_CMD(MUL, 4, 0, OPERATION(*))

DEF_CMD(DIV, 5, 0, OPERATION(/))

DEF_CMD(OUT, 6, 0,             
        {
        printf("result %d\n", POP_);
        })

DEF_CMD(IN, 7, 0,
        {
        int a = 0;
        scanf("%d", &a);
        PUSH_(a);
        })

DEF_CMD(JMP, 8, 1, JUMP)

DEF_CMD(DUP, 9, 0,             
        {
        int a = POP;
        PUSH_(a);
        PUSH_(a);
        })

DEF_CMD(JB, 10, 1, JUMP_COND(<))

DEF_CMD(JBE, 11, 1, JUMP_COND(<=))

DEF_CMD(JA, 12, 1, JUMP_COND(>))

DEF_CMD(JAE, 13, 1, JUMP_COND(>=))

DEF_CMD(JE, 14, 1, JUMP_COND(==))

DEF_CMD(JNE, 15, 1, JUMP_COND(!=))

DEF_CMD(POP, 16, 1,  
        {
        int arg = POP_;
        pop_arg(program, program->cmd[ip], arg, &ip);
        })
DEF_CMD(CALL, 17, 1,
        {
        ip++;
        int ind = program->cmd[ip];
        ip++;
        stack_push(&stk_ip, ip);
        ip = ind - 1;  
        })

DEF_CMD(RET, 18, 0,
        {
        ip = stack_pop(&stk_ip) - 1;
        })

DEF_CMD(SQR, 19, 0, 
        {
        int num = POP_;
        num = sqrt(num);
        PUSH_(num);
        })


