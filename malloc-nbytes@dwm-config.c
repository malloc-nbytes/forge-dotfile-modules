#include <forge/forge.h>

#include <stdio.h>

char *deps[] = { "suckless@dwm-6.8.0", NULL };

char *msgs[] = {
        "You must have the main repository installed for forge",
        "unless you have a package to install dwm-6.8 called `suckless@dwm-6.8.0`",
        NULL,
};

char **getdeps(void) { return deps; }
char **getmsgs(void) { return msgs; }
char *getname(void) { return "malloc-nbytes@dwm-config"; }
char *getver(void)  { return "1.0.0"; }
char *getdesc(void) { return "My dwm config"; }
char *getweb(void)  { return "https://www.github.com/malloc-nbytes/dwm-config.git/"; }

char *
download(void)
{
        return git_clone("malloc-nbytes", "dwm-config");
}

int
build(void)
{
        int ok = 1;

        // NOTE: hack
        char *src = "/var/cache/forge/sources/dwm-6.8.0";

        char *config = forge_io_resolve_absolute_path("./config.h");
        char *fullgaps = forge_io_resolve_absolute_path("./02-dwm-fullgaps-6.4.diff");
        char *awesomebar = forge_io_resolve_absolute_path("./03-dwm-awesomebar-6.6.diff");
        char *cp_config = forge_cstr_builder("cp ", config, " ", ".", NULL);
        char *patch1 = forge_cstr_builder("patch -p1 < ", fullgaps, NULL);
        char *patch2 = forge_cstr_builder("patch -p1 < ", awesomebar, NULL);

        CD(src, return 0);
        char *orig_config_data = forge_io_read_file_to_cstr("./config.h");
        CMD(cp_config, return 0);

        CMD(patch1, return 0);
        CMD(patch2, return 0);

        if (!make(NULL)) {
                ok = 0;
                goto restore_config;
        }

restore_config:
        (void)forge_io_write_file("./config.h", orig_config_data);

        return ok;
}

int
install(void)
{
        return make("install");
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .deps            = getdeps,
        .msgs            = getmsgs,
        .download        = download,
        .build           = build,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};

