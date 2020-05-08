#include <stdio.h>

#include <Elementary.h>

#include "notifiz.h"

struct Notifiz_Context {
  Eo *win;
  Eina_Strbuf *buffer;

  float ratio;
};

static unsigned int _init_count = 0;

Eina_Bool notifiz_init(void)
{
  if (_init_count > 0) return ++_init_count;

  eina_init();
  elm_init(0, NULL);

  _init_count++;

  return EINA_TRUE;
}

Eina_Bool notifiz_shutdown(void)
{
  if (_init_count <= 0)
  {
    fprintf(stderr, ("Notifiz init count not be less than 0 in shutdown."));
    return EINA_FALSE;
  }
  _init_count--;

  elm_shutdown();
  eina_shutdown();

  return EINA_TRUE;
}

Notifiz_Context *
notifiz_context_new(void)
{
  Notifiz_Context *ctx = calloc(1, sizeof(Notifiz_Context));

  ctx->buffer = eina_strbuf_new();
  notifiz_screen_ratio_set(ctx, 0.50);

  return ctx;
}


Eina_Bool
notifiz_screen_ratio_set(Notifiz_Context *ctx, float ratio)
{
  if (!ctx) return EINA_FALSE;

  if (ratio > 1.0) return EINA_FALSE;

  ctx->ratio = ratio;
  return EINA_TRUE;
}

Eina_Bool notifiz_show(Notifiz_Context *ctx)
{
  Evas *evas;
  int scr_w, scr_h;
  int w, h;

  elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

  if (!ctx->win)
  {
    Eo *win, *bg;
    Eo *lb;

    win = elm_win_add(NULL, "App", ELM_WIN_BASIC);
    efl_wref_add(win, &(ctx->win));
    elm_win_autodel_set(win, EINA_TRUE);
    elm_win_borderless_set(ctx->win, EINA_TRUE);
    elm_win_alpha_set(ctx->win, EINA_TRUE);
    elm_win_center(win, EINA_TRUE, EINA_FALSE);

    bg = elm_bg_add(win);
    evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_size_hint_align_set(bg, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_color_set(bg, 0xFF, 0xFF, 0xFF, 0x40);
    evas_object_show(bg);
    elm_win_resize_object_add(win, bg);

    lb = elm_label_add(win);
    elm_object_text_set(lb, eina_strbuf_string_get(ctx->buffer));
    evas_object_size_hint_weight_set(lb, EVAS_HINT_EXPAND, 0);
    evas_object_show(lb);
    elm_win_resize_object_add(win, lb);

    evas_object_size_hint_min_set(bg, 500, 500);
  }

  evas = evas_object_evas_get(ctx->win);
  ecore_evas_screen_geometry_get(ecore_evas_ecore_evas_get(evas), NULL, NULL, &scr_w, &scr_h);

  w = scr_w * ctx->ratio;
  h = scr_h * ctx->ratio;

  evas_object_resize(ctx->win, w, h);
  evas_object_size_hint_min_set(ctx->win, w, h);

  efl_gfx_entity_visible_set(ctx->win, EINA_TRUE);
  return EINA_TRUE;
}

Eina_Bool
notifiz_text_clear(Notifiz_Context *ctx)
{
  if (!ctx) return EINA_FALSE;

  eina_strbuf_reset(ctx->buffer);
  return EINA_TRUE;
}

Eina_Bool
notifiz_text_append(Notifiz_Context *ctx, const char *buffer)
{
  if (!ctx || !buffer) return EINA_FALSE;

  eina_strbuf_append(ctx->buffer, buffer);

  return EINA_TRUE;
}

