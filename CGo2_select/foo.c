#include "../../log/log.c"
#include "foo.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct ACTION_FUNCTION {
  const char *name;
  int (*func)(const int argc, const char **args);
} null;


int list_func(){
  fprintf(stderr, "list func.....\n");


  return(0);
}

struct ACTION_FUNCTION ActionFunctions[] = {
  { "list", list_func },
  { NULL,   NULL      }
};

struct ACTION_FUNCTION *cur = ActionFunctions;
typedef void ACTION_FUNCTION_HANDLER(const int argc, const char **args);


int RunActionName(char *name, const int argc, const char **argv){
  int                    i    = 0;
  struct ACTION_FUNCTION *cur = ActionFunctions;

  while (cur->name) {
    log_debug(cur->name);
    if (!strcmp(cur->name, name)) {
      log_debug("Running function %s with %d args of %d bytes", cur->name, argc, strlen((char *)argv));
      int res = cur->func(argc, argv);
      if (res == 0) {
        log_debug(AC_GREEN "%s(%d, xxxxxx) => %d", cur->name, argc, res);
      }else{
        log_error(AC_BOLD AC_RED "%s(%d, xxxxxx) => %d", cur->name, argc, res);
      }
      return(res);
    }
    cur = &ActionFunctions[++i];
  }
  log_error("Failed to find function for name '%s'", name);
  return(-1);
}


int main(int argc, char **argv) {
  char *selected_name, *input, *pass;
  int  confirmed;


  RunActionName("list", argc, argv);

  confirmed = do_confirm();
  log_info("confirmed? '%d'", confirmed);

  if (confirmed == 1) {
    selected_name = do_select();
    log_info("selected option '%s'", selected_name);

    input = do_input();
    log_info("input: '%s'", input);
    if (1 == 1) {
      pass = do_password();
      log_info("pass: '%s'", pass);
    }
  }

  return(0);
}
