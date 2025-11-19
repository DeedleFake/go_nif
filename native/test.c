#include <malloc.h>
#include <erl_nif.h>
#include "_cgo_export.h"

#define ok(val) enif_make_tuple2(env, enif_make_atom(env, "ok"), (val))
#define error(val) enif_make_tuple2(env, enif_make_atom(env, "error"), (val))

#define must(check) \
	if (!(check)) { \
		return enif_make_badarg(env); \
	}

#define str_to_binary(str) enif_make_binary(env, &(ErlNifBinary){ .data = (str), .size = strlen((str)) })
#define binary_to_str(binary, result) \
	result = malloc((binary).size + 1); \
	memcpy((result), (binary).data, (binary).size); \
	(result)[(binary).size] = 0

static ERL_NIF_TERM _get_dirty(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
	ErlNifBinary url;
	char *url_str;

	struct get_return rsp;

	must(enif_inspect_binary(env, argv[0], &url));
	binary_to_str(url, url_str);

	rsp = get(url_str);
	free(url_str);
	if (rsp.r1 != NULL) {
		return error(str_to_binary(rsp.r1));
	}

	return ok(str_to_binary(rsp.r0));
}

static ERL_NIF_TERM _get(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
	return enif_schedule_nif(env, "get", ERL_NIF_DIRTY_JOB_IO_BOUND, _get_dirty, argc, argv);
}

static ErlNifFunc nif_funcs[] = {
	{"get", 1, _get},
};

ERL_NIF_INIT(Elixir.GoNif, nif_funcs, NULL, NULL, NULL, NULL)
