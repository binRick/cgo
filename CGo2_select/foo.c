#include "../../is-email.c/src/is-email.c"
#include "../../log/log.c"
#include "actions.h"
#include "foo.h"
#include "validators.h"
#include <stdio.h>
#include <stdlib.h>

ACTION_FUNCTION       ActionFunctions[] = {
  { "__test__list", "%s", list_func,   v_ok,              false, NULL },
  { "env",          "%s", do_select,   v_is_valid_env,    false, NULL },
  { "email",        "%s", do_input,    v_is_valid_email,  false, NULL },
  { "password",     "%s", do_password, is_valid_password, false, NULL },
  { "confirm",      "%d", do_confirm,  v_is_one,          false, NULL },
  { NULL },
};

ACTION_FUNCTION_GROUP ActionFunctionGroups[] = {
  { "demo0", {
      &(ActionFunctions[4]),
      NULL,
    }, NULL },
  { "demo5", {
      &(ActionFunctions[1]),
      &(ActionFunctions[2]),
      &(ActionFunctions[3]),
      &(ActionFunctions[4]),
      NULL,
    }, NULL },
  { NULL },
};

char                  *EnabledModeNames[] = {
  "demo0",
  "demo1",
  "demo2",
  NULL,
};


int main(int argc, char **argv) {
  char                  *selected_name, *input, *pass;
  int                   confirmed, cur_id, qty, sqty;
  ACTION_FUNCTION_GROUP *g;
  ACTION_FUNCTION       *items;

  g   = ActionFunctionGroups;
  qty = 0;
  while (g->name != NULL) {
    qty++;
    g++;
  }
  g      = ActionFunctionGroups;
  cur_id = 0;
  bool action_failed = false;

  char **cn;

  cn = EnabledModeNames;
  while ((action_failed == false) && g->name != NULL) {
//  while (cn != NULL){
    bool enabled = (strcmp(g->name, ++cn) == 0) ? true : false;
    log_debug(AC_RESETALL AC_YELLOW AC_REVERSED "[cn:%s] name:%s> enabled:%d" AC_RESETALL, cn, g->name, enabled);
//    if(cn == 0)continue;

    sqty  = 0;
    items = g->items;
    while (items->name != NULL) {
      items++;
      sqty++;
    }
    items = g->items;
    while ((action_failed == false) && items->name != NULL) {
      log_debug("<#%d> %s->%s|fmt:%s|",
                sqty,
                g->name,
                items->name,
                items->fmt
                );

      void *RES = RunActionName(ActionFunctions, items->name, argc, argv);
      bool valid_action_result = false;
      char parsed[1024], res[1024];
      sprintf(&parsed, items->fmt, RES);
      valid_action_result = items->valid;
      log_debug("[%s] valid_action_result> %d", (char *)items->fmt, valid_action_result);
      sprintf(&res, (char *)(items->fmt), RES);
      log_debug("result (%s):%s", (char *)items->fmt, res);
      if (valid_action_result == false) {
        action_failed = true;
      }
      items++;
    }

    log_debug("processssing group #%d/%d with #%d items", cur_id + 1, qty, sqty);

//  cn++;
//  }
    g++;
    cur_id++;
  }
  return(0);
} /* main */
