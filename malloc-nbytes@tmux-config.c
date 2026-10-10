#include <forge/forge.h>

#include <stdio.h>

char *msgs[] = {
        "To install this for a user, you must install this",
        "package through 'sudo' or 'doas'. If you are root and",
        "install this package, it will be installed to /root.",
        NULL,
};

char **getmsgs(void) { return msgs; }
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
        int ok = 1;
        const char *user = get_prev_user();

        char *home   = forge_cstr_builder("$DESTDIR/home/", get_prev_user(), NULL);
        char *tmux   = forge_cstr_builder(home, "/.tmux.conf", NULL);
        char *mkd    = forge_cstr_builder("mkdir -p ", home, NULL);
        char *cp     = forge_cstr_builder("cp ./.tmux.conf ", tmux, NULL);
        char *_chown = forge_cstr_builder("chown -R ", user, ":", user, " ", tmux, NULL);

        CMD(mkd,    {ok = 0; goto cleanup;});
        CMD(cp,     {ok = 0; goto cleanup;});
        CMD(_chown, {ok = 0; goto cleanup;});

cleanup:
        free(home);
        free(tmux);
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
