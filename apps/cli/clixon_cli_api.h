/*
 *
  ***** BEGIN LICENSE BLOCK *****
 
  Copyright (C) 2009-2017 Olof Hagsand and Benny Holmgren

  This file is part of CLIXON.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  Alternatively, the contents of this file may be used under the terms of
  the GNU General Public License Version 3 or later (the "GPL"),
  in which case the provisions of the GPL are applicable instead
  of those above. If you wish to allow use of your version of this file only
  under the terms of the GPL, and not to allow others to
  use your version of this file under the terms of Apache License version 2, 
  indicate your decision by deleting the provisions above and replace them with
  the  notice and other provisions required by the GPL. If you do not delete
  the provisions above, a recipient may use your version of this file under
  the terms of any one of the Apache License version 2 or the GPL.

  ***** END LICENSE BLOCK *****

  * Note, this is a CLICON API file, only exprorted function prototypes should appear here
 */

#ifndef _CLIXON_CLI_API_H_
#define _CLIXON_CLI_API_H_

/*
 * Constants
 */
/* Max prompt length */
#define CLI_PROMPT_LEN 64
#define CLI_DEFAULT_PROMPT	">"

/* 
 * Function Declarations 
 */
/* cli_plugin.c */
int cli_set_syntax_mode(clicon_handle h, const char *mode);
char *cli_syntax_mode(clicon_handle h);
int cli_syntax_load(clicon_handle h);
int cli_handler_err(FILE *fd);
int cli_set_prompt(clicon_handle h, const char *mode, const char *prompt);
char *cli_prompt(char *fmt);
int cli_exec(clicon_handle h, char *cmd, char **mode, int *result);
int cli_ptpush(clicon_handle h, char *mode, char *string, char *op);
int cli_ptpop(clicon_handle h, char *mode, char *op);

/* cli_handle.c */
char cli_set_comment(clicon_handle h, char c);
char cli_comment(clicon_handle h);
int cli_set_exiting(clicon_handle h, int exiting);
int cli_exiting(clicon_handle h);
clicon_handle cli_handle_init(void);
int cli_handle_exit(clicon_handle h);
cligen_handle cli_cligen(clicon_handle h);

/* cli_common.c */
int cli_notification_register(clicon_handle h, char *stream, enum format_enum format,
			      char *filter, int status, 
			      int (*fn)(int, void*), void *arg);

#define cli_output cligen_output
/* cli_common.c: CLIgen new vector callbacks */
int cli_setv(clicon_handle h, cvec *vars, cvec *argv);
int cli_mergev(clicon_handle h, cvec *vars, cvec *argv);
int cli_delv(clicon_handle h, cvec *vars, cvec *argv);
int cli_debug_cliv(clicon_handle h, cvec *vars, cvec *argv);
int cli_debug_backendv(clicon_handle h, cvec *vars, cvec *argv);
int cli_set_modev(clicon_handle h, cvec *vars, cvec *argv);
int cli_start_shellv(clicon_handle h, cvec *vars, cvec *argv);
int cli_quitv(clicon_handle h, cvec *vars, cvec *argv);
int cli_commitv(clicon_handle h, cvec *vars, cvec *argv);
int cli_validatev(clicon_handle h, cvec *vars, cvec *argv);
int compare_dbsv(clicon_handle h, cvec *vars, cvec *argv);
int load_config_filev(clicon_handle h, cvec *vars, cvec *argv);
int save_config_filev(clicon_handle h, cvec *vars, cvec *argv);
int delete_allv(clicon_handle h, cvec *vars, cvec *argv);
int discard_changesv(clicon_handle h, cvec *vars, cvec *argv);
int cli_notifyv(clicon_handle h, cvec *cvv, cvec *argv);
int cli_lock(clicon_handle h, cvec *cvv, cvec *argv);
int cli_unlock(clicon_handle h, cvec *cvv, cvec *argv);
int cli_copy_object(clicon_handle h, cvec *cvv, cvec *argv);

/* cli_common.c: CLIgen old single arg callbacks */
int cli_set(clicon_handle h, cvec *vars, cg_var *arg);
int cli_merge(clicon_handle h, cvec *vars, cg_var *arg);
int cli_del(clicon_handle h, cvec *vars, cg_var *arg);
int cli_debug_cli(clicon_handle h, cvec *vars, cg_var *arg);
int cli_debug_backend(clicon_handle h, cvec *vars, cg_var *argv);
int cli_set_mode(clicon_handle h, cvec *vars, cg_var *argv);
int cli_start_shell(clicon_handle h, cvec *vars, cg_var *argv);
int cli_quit(clicon_handle h, cvec *vars, cg_var *arg);
int cli_commit(clicon_handle h, cvec *vars, cg_var *arg);
int cli_validate(clicon_handle h, cvec *vars, cg_var *arg);
int compare_dbs(clicon_handle h, cvec *vars, cg_var *arg);
int load_config_file(clicon_handle h, cvec *vars, cg_var *arg);
int save_config_file(clicon_handle h, cvec *vars, cg_var *arg);
int delete_all(clicon_handle h, cvec *vars, cg_var *arg);
int discard_changes(clicon_handle h, cvec *vars, cg_var *arg);
int cli_notify(clicon_handle h, cvec *cvv, cg_var *arg);

/* In cli_show.c */
int expand_dir(char *dir, int *nr, char ***commands, mode_t flags, int detail);
int expandv_dbvar(void *h, char *name, cvec *cvv, cvec *argv, 
		  cvec *commands, cvec *helptexts);
/* cli_show.c: CLIgen new vector arg callbacks */
int show_confv_as_xml(clicon_handle h, cvec *vars, cvec *argv);
int show_confv_as_netconf(clicon_handle h, cvec *vars, cvec *argv);
int show_confv_as_json(clicon_handle h, cvec *vars, cvec *argv);
int show_confv_as_text(clicon_handle h, cvec *vars, cvec *argv);
int show_confv_as_cli(clicon_handle h, cvec *vars, cvec *argv);
int show_confv_as_csv(clicon_handle h, cvec *vars, cvec *argv);
int show_yangv(clicon_handle h, cvec *vars, cvec *argv);
int show_confv_xpath(clicon_handle h, cvec *cvv, cvec *argv);

int show_configuration(clicon_handle h, cvec *cvv, cvec *argv);

/* cli_show.c: CLIgen old single arg callbacks */
int show_conf_as_xml(clicon_handle h, cvec *vars, cg_var *arg);
int show_conf_as_netconf(clicon_handle h, cvec *vars, cg_var *arg);
int show_conf_as_json(clicon_handle h, cvec *vars, cg_var *arg);
int show_conf_as_text(clicon_handle h, cvec *vars, cg_var *arg);
int show_conf_as_cli(clicon_handle h, cvec *vars, cg_var *arg);
int show_conf_as_csv(clicon_handle h, cvec *vars, cg_var *arg);
int show_yang(clicon_handle h, cvec *vars, cg_var *arg);

#endif /* _CLIXON_CLI_API_H_ */
