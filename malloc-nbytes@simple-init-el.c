#include <forge/forge.h>

#include <stdio.h>

char *msgs[] = {
        "This is a simple version of my Emacs config."
        "There are no packages that need to be installed."
        "To install this for a user, you must install this",
        "package through 'sudo' or 'doas'. If you are root and",
        "install this package, it will be installed to /root.",
        "Make sure to: `" YELLOW BOLD "chown -R <user>:<user> $HOME/.emacs.d" RESET "' !",
        "Uninstalling this package will remove all currently installed",
        "Emacs packages as well as custom-set-variables, so be careful.",
        NULL,
};

char **getmsgs(void) { return msgs; }
char *getname(void) { return "malloc-nbytes@init-el"; }
char *getver(void)  { return "rolling"; }
char *getdesc(void) { return "My Emacss config"; }
char *getweb(void)  { return "https://www.github.com/malloc-nbytes/init.el.git/"; }

char *
download(void)
{
        return git_clone("malloc-nbytes", "init.el");
}

int
install(void)
{
        char *user   = get_prev_user();
        char *home   = forge_cstr_builder("$DESTDIR/home/", user, NULL);
        char *emacsd = forge_cstr_builder(home, "/.emacs.d", NULL);
        char *mkd    = forge_cstr_builder("mkdir -p ", home, NULL);
        char *mkde   = forge_cstr_builder("mkdir -p ", emacsd, NULL);
        char *cp     = forge_cstr_builder("cp ./init.el ./simple/config.org ", emacsd, NULL);
        char *chown  = forge_cstr_builder("chown -R ", user, ":", user, " ", emacsd, NULL);

        CMD(mkd, return 0);
        CMD(mkde, return 0);

        CMD(cp, {
                free(home);
                free(emacsd);
                free(cp);
                free(chown);
                return 0;
        });

        CMD(chown, {
                free(home);
                free(emacsd);
                free(cp);
                free(chown);
                return 0;
        });

        free(home);
        free(emacsd);
        free(mkd);
        free(cp);

        return 1;
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .msgs            = getmsgs,
        .deps            = NULL,
        .download        = download,
        .build           = NULL,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
