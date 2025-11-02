#include <forge/forge.h>

#include <stdio.h>

char *getname(void) { return "malloc-nbytes@tmux-config"; }
char *getver(void)  { return "1.0.0"; }
char *getdesc(void) { return "My tmux config"; }
char *getweb(void)  { return "https://www.github.com/malloc-nbytes/tmux-config.git/"; }

char *download(void)
{
        return git_clone("malloc-nbytes", "tmux-config");
}

int install(void)
{
        char *home  = forge_cstr_builder("$DESTDIR/home/", get_prev_user(), NULL);
        char *tmux  = forge_cstr_builder(home, "/.tmux.conf", NULL);
        char *mkd   = forge_cstr_builder("mkdir -p ", home, NULL);
        char *cp    = forge_cstr_builder("cp ./.tmux.conf ", tmux, NULL);

        CMD(mkd, return 0);

        CMD(cp, {
                free(home);
                free(tmux);
                free(cp);
                return 0;
        });

        free(home);
        free(tmux);
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
        .download        = download,
        .build           = NULL,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
