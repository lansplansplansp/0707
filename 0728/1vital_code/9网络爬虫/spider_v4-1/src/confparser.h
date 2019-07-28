#ifndef CONFPARSER_H
#define CONFPARSER_H

 
#define MAX_CONF_LEN  1024
#define ITEMS	10
#define CONF_FILE     "spider.conf"

/* see the spiderq.conf to get meaning for each member variable below */
typedef struct Config {
    int              max_job_num;
    char             **seeds;
    int		     seedcnt;
    char             *logfile;
    int              log_level;
    int              max_depth;
    int              make_hostdir;
    int              stat_interval;
    char             **accept_types;
    int              typecnt;
} Config;

/* give default values to member variables in struct Config */
extern Config * init_config();
extern void destroy_config(Config **conf);

/* load configuration in conf file to Config object */
extern void load_config(Config *conf);
extern void seed_push_back2(Config *conf, char *str);

extern void seed_push_back1(Config *conf, char *str);

#endif
