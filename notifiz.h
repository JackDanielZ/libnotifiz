#ifndef __NOTIFIZ_H__
#define __NOTIFIZ_H__

#include <Eina.h>

typedef struct Notifiz_Context Notifiz_Context;

Eina_Bool notifiz_init(void);

Eina_Bool notifiz_shutdown(void);

Notifiz_Context *notifiz_context_new(void);

Eina_Bool notifiz_screen_ratio_set(Notifiz_Context *ctx, float ratio);

Eina_Bool notifiz_text_clear(Notifiz_Context *ctx);

Eina_Bool notifiz_text_append(Notifiz_Context *ctx, const char *buffer);

Eina_Bool notifiz_show(Notifiz_Context *ctx);

#endif /* __NOTIFIZ_H__ */
