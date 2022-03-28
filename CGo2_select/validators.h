
bool v_len_gt_5(const char *parsed){
  bool valid = false;

  valid = ((parsed != NULL) && (strlen(parsed) > 5)) ? true : false;
  return(valid);
}


bool v_len_gt_2(const char *parsed){
  bool valid = false;

  valid = ((parsed != NULL) && (strlen(parsed) > 2)) ? true : false;
  return(valid);
}


bool v_is_set(const char *parsed){
  log_debug("parsed:%s", parsed);
  bool valid = false;

  valid = ((parsed != NULL) && (strlen(parsed) > 0)) ? true : false;
  log_debug("valid?         %s", valid ? AC_GREEN "YES" AC_RESETALL : AC_RED "NO" AC_RESETALL);
  return(valid);
}


bool is_none(const char *parsed){
  bool v = false;

  v = ((v_is_set(parsed)) && strcmp(parsed, "<NONE>") == 0) ? true : false;
  return(v);
}


bool v_is_valid_env(const char *parsed){
  log_debug("env:%s", parsed);

  return((v_is_set(parsed) && v_len_gt_5(parsed) && (!is_none(parsed))) ? true : false);
}


bool v_is_valid_email(const char *parsed){
  return((v_is_set(parsed) && v_len_gt_2(parsed) && (!is_none(parsed)) && ((is_email(parsed) == 0) ? true : false)) ? true : false);
}


bool is_valid_password(const char *parsed){
  return((v_is_set(parsed) && v_len_gt_2(parsed) && (!is_none(parsed))) ? true : false);
}


bool v_ok_logger(const char *parsed){
  log_debug("parsed:%s", parsed);

  return(true);
}


bool v_is_one(const char *parsed){
  log_debug("parsed:%s", parsed);
  bool valid = false;

  valid = ((parsed != NULL) && (strlen(parsed) > 0) && (strcmp(parsed, "1") == 0)) ? true : false;
  log_debug("valid?         %s", valid ? AC_GREEN "YES" AC_RESETALL : AC_RED "NO" AC_RESETALL);
  return(valid);
}


bool v_ok(const char *parsed){
  return(true);
}
