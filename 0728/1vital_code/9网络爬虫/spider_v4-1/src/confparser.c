#include "spider.h"
#include "qstring.h"
#include "confparser.h"
#define INF 0x7FFFFFFF
 
Config * init_config()
{
    Config *conf = (Config *)malloc(sizeof(Config));
    memset(conf, 0, sizeof(Config));
    return conf;
}
//¶þ¼¶Ö¸Õë
void destroy_config(Config **conf)
{
	// char            **seeds;
	// char            *logfile; 
	//char **			 accept_types;
	free(*conf);
	*conf = NULL;
}
void seed_push_back1(Config *conf, char *str)
{
    if(NULL == str)
    {
        SPIDER_LOG(SPIDER_LEVEL_ERROR, "param is null\n");
        return ;
    }
    conf->seeds = (char **)realloc(conf->seeds, (conf->seedcnt+1) * sizeof(char *));
    conf->seeds[conf->seedcnt] = strdup(str);
    conf->seedcnt++;
}
void load_config(Config *conf)
{
    FILE *fp = NULL;
    char buf[MAX_CONF_LEN+1];
    int argc = 0;
    char **argv = NULL;
    int linenum = 0;
    char *line = NULL;
    const char *err = NULL;
    if ((fp = fopen(CONF_FILE, "r")) == NULL) {
        SPIDER_LOG(SPIDER_LEVEL_ERROR, "Can't load conf_file %s", CONF_FILE);	
    } 
    while (fgets(buf, MAX_CONF_LEN+1, fp) != NULL) {
        linenum++;
        line = strim(buf);
        if (line[0] == '#' || line[0] == '\0') 
            continue;
        argv = strsplit(line, '=', &argc, 1);
        if (argc == 2) {
            if (strcasecmp(argv[0], "max_job_num") == 0) {
                conf->max_job_num = atoi(argv[1]);
            } else if (strcasecmp(argv[0], "logfile") == 0) {
                conf->logfile = strdup(argv[1]);
            } else if (strcasecmp(argv[0], "seeds") == 0) {
                seed_push_back1(g_conf, argv[1]);
            } else if (strcasecmp(argv[0], "log_level") == 0) {
                conf->log_level = atoi(argv[1]);
            } else if (strcasecmp(argv[0], "max_depth") == 0) {
                conf->max_depth = atoi(argv[1]);
            } else if (strcasecmp(argv[0], "stat_interval") == 0) {
                conf->stat_interval = atoi(argv[1]);
            } else if (strcasecmp(argv[0], "make_hostdir") == 0) {
                conf->make_hostdir = yesnotoi(argv[1]);
            } else if (strcasecmp(argv[0], "accept_types") == 0) {
            } else {
                err = "Unknown directive"; 
                goto conferr;
            }
        }
        else {
            err = "directive must be 'key=value'"; 
            goto conferr;
        }
    }
#if 0
	int ii;
	for(ii=0; ii<g_conf->seedcnt; ii++)
		SPIDER_LOG(SPIDER_LEVEL_DEBUG, "%s\n", g_conf->seeds[ii]);

#endif
    return;
conferr:
    SPIDER_LOG(SPIDER_LEVEL_ERROR, "Bad directive in %s[line:%d] %s", CONF_FILE, linenum, err);	
}
