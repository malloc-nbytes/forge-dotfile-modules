#include <forge/forge.h>

#include <stdio.h>

char *getname(void) { return "malloc-nbytes@vim-config"; }
char *getver(void)  { return "1.0.0"; }
char *getdesc(void) { return "My Vim config"; }
char *getweb(void)  { return "https://www.github.com/malloc-nbytes/vim-config.git/"; }

char *download(void)
{
        return git_clone("malloc-nbytes", "vim-config");
}

int install(void)
{
        char *home  = forge_cstr_builder("$DESTDIR/home/", get_prev_user(), NULL);
        char *vimrc = forge_cstr_builder(home, "/.vimrc", NULL);
        char *mkd   = forge_cstr_builder("mkdir -p ", home, NULL);
        char *cp    = forge_cstr_builder("cp ./.vimrc ", vimrc, NULL);

        CMD(mkd, return 0);

        CMD(cp, {
                free(home);
                free(vimrc);
                free(cp);
                return 0;
        });

        free(home);
        free(vimrc);
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
