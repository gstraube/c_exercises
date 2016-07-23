#ifndef AALTO_ARRAYTOOL_H
#define AALTO_ARRAYTOOL_H

#define CHECK(Cond, Msg) if (!(Cond)) printf("%s", Msg);

#define MAKE_ARRAY(Type, N) malloc(N * sizeof(Type));

#define ARRAY_IDX(Type, Array, I) *(((Type*) Array) + I)

#endif
