
typedef void ACTION_FUNCTION_HANDLER(const int argc, const char **args);
typedef void *ACTION_FUNCTION_REF(const int argc, const char **args);
typedef bool ACTION_RESULT_VALIDATOR_FUNCTION_REF(const char *result);


typedef struct ACTION_FUNCTION {
  const char                           *name;
  const char                           *fmt;
  ACTION_FUNCTION_REF                  *func;
  ACTION_RESULT_VALIDATOR_FUNCTION_REF *validator;
  bool                                 valid;
} ACTION_FUNCTION;

typedef struct ACTION_FUNCTION_GROUP {
  const char            *name;
  const ACTION_FUNCTION **items;
} ACTION_FUNCTION_GROUP;


int list_func(){
  fprintf(stderr, "list func.....\n");


  return(0);
}


volatile ACTION_FUNCTION *cur;


char * RunActionName(ACTION_FUNCTION *ActionFunctions, char *name, const int argc, const char **argv){
  int i = 0;

  cur = ActionFunctions;

  while (cur->name) {
    log_debug(cur->name);
    if (!strcmp(cur->name, name)) {
      log_debug("Running function %s with %d args of %d bytes", cur->name, argc, strlen((char *)argv));
      void *res;
      char parsed[1024];
      res = cur->func(argc, argv);
      log_debug("Ended function %s", cur->name);
      sprintf(&parsed, cur->fmt, res);
      cur->valid = cur->validator(parsed);
      log_debug(
        AC_GREEN "validator?            %d|%s", cur->valid, parsed);
      if (parsed != NULL && strlen(parsed) > 0 && cur->valid) {
        log_debug(AC_GREEN "%s %db", cur->name, strlen(parsed));
      }else{
        log_debug(AC_RED "%s %db", cur->name, strlen(parsed));
      }
      return(parsed);
    }
    cur = &ActionFunctions[++i];
  }
  log_error("Failed to find function for name '%s'", name);
  char *r = "";

  return(strdup(r));
}

