#include <stdio.h>
#include "ezEvent.h"

typedef struct {
    int a;
    int b;
    int c;
} numbers_t;

void once_foo(void *data)
{
    printf("once_foo called\n");
}

void on_foo(void *data)
{
    numbers_t *num = (Position *) data;

    printf("on_foo:\na: %d\nb: %d\nc: %d\n", num->a, num->b, num->c);
}

void on_bar(void *data)
{
    char *msg = (char *) data;
    printf("on_bar: %s\n", msg);
}

int main(void)
{
    numbers_t theNums = {1, 2, 3};
    Event_s *eventSys = newEvent_s();

    event_once( eventSys, "foo", (void *) once_foo);

    event_on( eventSys, "foo", (void *) on_foo);
    event_on( eventSys, "bar",  on_bar);

    sendEvent( eventSys, "bar", "abcd");
    sendEvent( eventSys, "bar", "ok!");

    sendEvent( eventSys, "foo", (void *)&theNums);
    sendEvent( eventSys, "foo", &(numbers_t) {4, 5, 6});
    
    event_off( eventSys, "bar", (void *) on_bar);
    freeEvent_s( eventSys );
    return 0;
}
