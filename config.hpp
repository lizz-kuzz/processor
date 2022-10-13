
DEF_CMD(HLT, 0, 0,
        {stack_dtor(stk);})

DEF_CMD(PUSH, 1, 1, 
        {int arg = get_arg(program, program->cmd[ip], &ip);
        stack_push(stk, arg);})

DEF_CMD(ADD, 2, 0,
        {int a = stack_pop(stk);
        int b = stack_pop(stk);
        stack_push(stk, a + b);})

DEF_CMD(SUB, 3, 0,
        {int a = stack_pop(stk);
        int b = stack_pop(stk);
        stack_push(stk, a - b);})

DEF_CMD(MUL, 4, 0,
        {int a = stack_pop(stk);
        int b = stack_pop(stk);
        stack_push(stk, a * b);})

DEF_CMD(DIV, 5, 0,
        {int a = stack_pop(stk);
        int b = stack_pop(stk);
        stack_push(stk, b / a);})

DEF_CMD(OUT, 6, 0,             
        {int a = stack_pop(stk);
        printf("result %d\n", a);})

DEF_CMD(IN, 7, 0,
        {int a = 0;
        scanf("%d", &a);
        stack_push(stk, a);})

DEF_CMD(JMP, 8, 1, 
        {ip++;
        int a = program->cmd[ip];
        ip = a;})

DEF_CMD(DUP, 9, 0,             
        {int a = stack_pop(stk);
        stack_push(stk, a);
        stack_push(stk, a);})



