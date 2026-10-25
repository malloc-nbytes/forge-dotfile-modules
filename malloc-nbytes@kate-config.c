#include <forge/cstr.h>
#include <forge/forge.h>

char *getname(void) { return "malloc-nbytes@kate-config"; }
char *getver(void)  { return "rolling"; }
char *getdesc(void) { return "Themes for the kate IDE"; }
char *getweb(void)  { return "https://www.github.com/malloc-nbytes/kate-config/"; }

char *
download(void)
{
        return git_clone("malloc-nbytes", "kate-config");
}

int
install(void)
{
        int ok = 1;
        char *user    = get_prev_user();
        char *home    = forge_cstr_builder("$DESTDIR/home/", user, NULL);
        char *kated   = forge_cstr_builder(home, "/.local/share/org.kde.syntax-highlighting", NULL);
        char *mkd     = forge_cstr_builder("mkdir -p ", kated, NULL);
        char *mv      = forge_cstr_builder("cp -r ./themes ", kated, NULL);

        CMD(mkd, {ok = 0; goto done;});
        CMD(mv, {ok = 0; goto done;});
done:
        free(home);
        free(kated);
        free(mkd);
        free(mv);

        return ok;
}

FORGE_GLOBAL pkg package = {
        .name            = getname,
        .ver             = getver,
        .desc            = getdesc,
        .web             = getweb,
        .msgs            = NULL,
        .deps            = NULL,
        .download        = download,
        .build           = NULL,
        .install         = install,
        .uninstall       = NULL,
        .update          = forge_pkg_git_update,
        .get_changes     = forge_pkg_git_pull,
};
