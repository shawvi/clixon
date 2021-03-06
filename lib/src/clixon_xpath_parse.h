/*
 *
  ***** BEGIN LICENSE BLOCK *****
 
  Copyright (C) 2009-2018 Olof Hagsand and Benny Holmgren

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

 */
#ifndef _CLIXON_XPATH_PARSE_H_
#define _CLIXON_XPATH_PARSE_H_

/*
 * Types
 */
/* used as non-terminal type in yacc rules */
enum xp_type{
    XP_EXP,
    XP_AND,
    XP_RELEX,
    XP_ADD,
    XP_UNION,
    XP_PATHEXPR,
    XP_LOCPATH,
    XP_ABSPATH,
    XP_RELLOCPATH,
    XP_STEP,
    XP_NODE,
    XP_NODE_FN,
    XP_PRED,
    XP_PRI0,
    XP_PRIME_NR,
    XP_PRIME_STR,
    XP_PRIME_FN,
};

/*! XPATH Parsing generates a tree of nodes that is later traversed
 */
struct xpath_tree{
    enum xp_type      xs_type;
    int               xs_int;
    double            xs_double;
    char             *xs_s0;
    char             *xs_s1;
    struct xpath_tree *xs_c0; /* child 0 */
    struct xpath_tree *xs_c1; /* child 1 */
};
typedef struct xpath_tree xpath_tree;

struct clicon_xpath_yacc_arg{ /* XXX: mostly unrelevant */
    const char           *xy_name;         /* Name of syntax (for error string) */
    int                   xy_linenum;      /* Number of \n in parsed buffer */
    char                 *xy_parse_string; /* original (copy of) parse string */
    void                 *xy_lexbuf;       /* internal parse buffer from lex */
    xpath_tree           *xy_top;
};

/*
 * Variables
 */
extern char *clixon_xpath_parsetext;

/*
 * Prototypes
 */
int xpath_scan_init(struct clicon_xpath_yacc_arg *jy);
int xpath_scan_exit(struct clicon_xpath_yacc_arg *jy);

int xpath_parse_init(struct clicon_xpath_yacc_arg *jy);
int xpath_parse_exit(struct clicon_xpath_yacc_arg *jy);

int clixon_xpath_parselex(void *);
int clixon_xpath_parseparse(void *);
void clixon_xpath_parseerror(void *, char*);

#endif	/* _CLIXON_XPATH_PARSE_H_ */
