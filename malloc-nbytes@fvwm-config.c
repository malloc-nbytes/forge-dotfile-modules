#include <forge/forge.h>

#include <stdio.h>

char *msgs[] = {
        "To install this for a user, you must install this",
        "package through 'sudo' or 'doas'. If you are root and",
        "install this package, it will be installed to /root.",
        NULL,
};

char **getmsgs(void) { return msgs; }
char *getname(void) { return "malloc-nbytes@fvwm-config"; }
char *getver(void)  { return "1.0.0"; }
char *getdesc(void) { return "My FVWM3 config"; }
char *getweb(void)  { return "https://www.github.com/malloc-nbytes/fvwm-config.git/"; }

char *download(void)
{
        return git_clone("malloc-nbytes", "fvwm-config");
}

int install(void)
{
        char *home  = forge_cstr_builder("$DESTDIR/home/", get_prev_user(), NULL);
        char *mkd   = forge_cstr_builder("mkdir -p ", home, "/.fvwm", NULL);
        char *cp    = forge_cstr_builder("cp ./config ", home, "/.fvwm", NULL);

        CMD(mkd, return 0);

        CMD(cp, {
                free(home);
                free(cp);
                return 0;
        });

        free(home);
        free(mkd);
        free(cp);

        return 1;
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = NULL,
        .msgs            = getmsgs,
        .download        = download,
        .build           = NULL,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
