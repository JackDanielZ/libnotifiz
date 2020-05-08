#include <notifiz.h>

#include <Elementary.h>

int main(void)
{
  Notifiz_Context *ctx;

  notifiz_init();

  ctx = notifiz_context_new();

  notifiz_screen_ratio_set(ctx, 0.80);

  notifiz_text_append(ctx, "TOTO<br>TOTO<br><br><br>TOTO<br>TOTO<br>");

  notifiz_show(ctx);

  elm_run();

  notifiz_shutdown();

  return 0;
}
