#include <forge/forge.h>

#include <stdio.h>

char *msgs[] = {
        "This script uses fzf and alacritty, but I am not requiring",
        "them as dependencies in this package.",
        NULL,
};

char **getmsgs(void) { return msgs; }
char *getname(void) { return "malloc-nbytes@applauncher-script"; }
char *getver(void)  { return "rolling"; }
char *getdesc(void) { return "A simple app launcher script"; }
char *getweb(void)  { return "https://github.com/malloc-nbytes/applauncher-script"; }

char *
download(void)
{
        return git_clone("malloc-nbytes", "applauncher-script");
}

int
install(void)
{
        CMD("chmod +x applauncher-script.sh", return 0);
        return cmd("mv applauncher-script.sh " FORGE_PREFERRED_INSTALL_PREFIX "/bin/applauncher-script");
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
