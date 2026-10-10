#include <forge/forge.h>

#include <stdio.h>

char *msgs[] = {
        "To install this for a user, you must install this",
        "package through 'sudo' or 'doas'. If you are root and",
        "install this package, it will be installed to /root.",
        NULL,
};

char **getmsgs(void) { return msgs; }
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
        int ok           = 1;
        const char *user = get_prev_user();

        char *home       = forge_cstr_builder("$DESTDIR/home/", get_prev_user(), NULL);
        char *vimrc      = forge_cstr_builder(home, "/.vimrc", NULL);
        char *mkd        = forge_cstr_builder("mkdir -p ", home, NULL);
        char *cp         = forge_cstr_builder("cp ./.vimrc ", vimrc, NULL);
        char *_chown     = forge_cstr_builder("chown -R ", user, ":", user, " ", vimrc, NULL);

        CMD(mkd,    {ok = 0; goto cleanup;});
        CMD(cp,     {ok = 0; goto cleanup;});
        CMD(_chown, {ok = 0; goto cleanup;});

cleanup:
        free(home);
        free(vimrc);
        free(mkd);
        free(cp);
        free(_chown);

        return ok;
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
