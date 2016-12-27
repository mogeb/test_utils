#include <stdio.h>

#define UNW_LOCAL_ONLY
#include <libunwind.h>

void show_backtrace (void) {
	unw_cursor_t cursor; unw_context_t uc;
	unw_word_t ip, sp;

	unw_getcontext(&uc);
	unw_init_local(&cursor, &uc);
	while (unw_step(&cursor) > 0) {
		unw_get_reg(&cursor, UNW_REG_IP, &ip);
		unw_get_reg(&cursor, UNW_REG_SP, &sp);
		printf ("ip = %lx, sp = %lx\n", (long) ip, (long) sp);
	}
}

void bar(char *str)
{
    volatile int done = 0;
    
    while (done < 1200440) {
        done++;
    }
    printf("%s\n", str);

    done = 0;
    while (done < 203455) {
        done++;
    }

    show_backtrace();
}

void foo()
{
    volatile int done = 0;

    while (done < 2000000) {
        done++;
    }
}

int main()
{
    volatile int i = 0;

    printf("Starting\n");
    foo();
    bar("hello");
    while (i < 900000) {
        i++;
    }
    foo();
    foo();
    i = 0;
    while (i < 5000000) {
        i++;
    }
    bar("ami");
   
    return 0;
}

/*
main
foo
bar
show_backtrace

     sb                    sb
foo bar [  ] foo foo [  ] bar
main
*/