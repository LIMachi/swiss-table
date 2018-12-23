# swiss-table

C adaptation of the swiss table (flat hash map) presented at CppCon by Google (https://www.youtube.com/watch?v=ncHmEUmJZf4).

This is NOT a complete implementation, it's a proof of concept and will stay that way until I think it's stable and compatible enough.

This first implementation will be using the 42 School's programmation norm (https://cdn.intra.42.fr/pdf/pdf/1065/norme.en.pdf).

Using the defines SWT_KEY_TYPE and SWT_VALUE_TYPE at compile time or by changing them in the headers, you can change the types used as key and value (default to void*).

If present, will use SSE2 instructions, otherwise will use simpler functions.


Implemented functions:

-insert

-find

-delete

-create

-destroy

-clear

-iterate


A basic hash function is provided for testing purpose using FNV-1a (https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function).