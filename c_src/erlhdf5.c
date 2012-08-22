#include <stdio.h>
#include <stdlib.h>
#include "erl_nif.h"
#include "dbg.h"
#include "erlhdf5.h"

void free_res(ErlNifEnv* env, void* obj)
{
}

static int load(ErlNifEnv* env, void** priv, ERL_NIF_TERM load_info)
{
    const char* mod = "erlhdf5";
    const char* name = "FileHandle";
    int flags = ERL_NIF_RT_CREATE | ERL_NIF_RT_TAKEOVER;

    RES_TYPE = enif_open_resource_type(env, mod, name, free_res, flags, NULL);
    check(RES_TYPE, "Failed to open resource type %s", name);

    // Initialize common atoms
    ATOM(ATOM_OK, "ok");
    ATOM(ATOM_ERROR, "error");
    /* ATOM(ATOM_TRUE, "true"); */
    /* ATOM(ATOM_FALSE, "false"); */

    return 0;

 error:
    return -1;
};

// func to convert error message
ERL_NIF_TERM error_tuple(ErlNifEnv* env, char* reason)
{
    ERL_NIF_TERM why = enif_make_string(env, reason, ERL_NIF_LATIN1);
    return enif_make_tuple2(env, ATOM_ERROR, why);
}

static ErlNifFunc nif_funcs[] =
{
  {"h5fcreate", 2, h5fcreate},
  {"h5fopen", 2, h5fopen},
  {"h5fclose", 1, h5fclose},
  {"h5screate", 2, h5screate}
};

ERL_NIF_INIT(erlhdf5, nif_funcs, &load, NULL, NULL, NULL);
