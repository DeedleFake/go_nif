#include <erl_nif.h>
#include "_go_export.h"

static ErlNifFunc nif_funcs[] = {
	{"add", 2, add},
};

ERL_NIF_INIT(go_nif, nif_funcs, NULL, NULL, NULL, NULL)
