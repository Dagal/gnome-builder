/* gb-devhelp-view.c
 *
 * Copyright (C) 2014 Christian Hergert <christian@hergert.me>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define G_LOG_DOMAIN "devhelp-view"

#include <glib/gi18n.h>
#include <webkit2/webkit2.h>

#include "gb-devhelp-view.h"
#include "gb-widget.h"

struct _GbDevhelpViewPrivate
{
  /* References owned by view */
  GbDevhelpDocument *document;

  /* References owned by Gtk template */
  WebKitWebView     *web_view1;
  WebKitWebView     *web_view2;

  GtkPaned          *paned;
};

G_DEFINE_TYPE_WITH_PRIVATE (GbDevhelpView, gb_devhelp_view, GB_TYPE_VIEW)

enum {
  PROP_0,
  PROP_DOCUMENT,
  LAST_PROP
};

static GParamSpec *gParamSpecs [LAST_PROP];

GbView *
gb_devhelp_view_new (GbDevhelpDocument *document)
{
  return g_object_new (GB_TYPE_DEVHELP_VIEW,
                       "document", document,
                       NULL);
}

static GbDocument *
gb_devhelp_view_get_document (GbView *view)
{
  g_return_val_if_fail (GB_IS_DEVHELP_VIEW (view), NULL);

  return GB_DOCUMENT (GB_DEVHELP_VIEW (view)->priv->document);
}

static void
gb_devhelp_view_notify_uri (GbDevhelpView     *view,
                            GParamSpec        *pspec,
                            GbDevhelpDocument *document)
{
  const gchar *uri;

  g_return_if_fail (GB_IS_DEVHELP_VIEW (view));
  g_return_if_fail (GB_IS_DEVHELP_DOCUMENT (document));

  uri = gb_devhelp_document_get_uri (document);
  if (uri)
    {
      webkit_web_view_load_uri (view->priv->web_view1, uri);

      if (view->priv->web_view2 != NULL)
        webkit_web_view_load_uri (view->priv->web_view2, uri);
    }
}

static void
gb_devhelp_view_set_document (GbDevhelpView     *view,
                              GbDevhelpDocument *document)
{
  GbDevhelpViewPrivate *priv;

  g_return_if_fail (GB_IS_DEVHELP_VIEW (view));

  priv = view->priv;

  if (priv->document != document)
    {
      if (priv->document)
        {
          g_signal_handlers_disconnect_by_func (priv->document,
                                                G_CALLBACK (gb_devhelp_view_notify_uri),
                                                view);
          g_clear_object (&priv->document);
        }

      if (document)
        {
          priv->document = g_object_ref (document);
          g_signal_connect_object (priv->document,
                                   "notify::uri",
                                   G_CALLBACK (gb_devhelp_view_notify_uri),
                                   view,
                                   G_CONNECT_SWAPPED);
        }

      gb_devhelp_view_notify_uri (view, NULL, document);
      g_object_notify (G_OBJECT (view), "document");
    }
}

static GbView *
gb_devhelp_view_create_split (GbView *view)
{
  GbDevhelpView *self = (GbDevhelpView *)view;
  GbView *ret;

  g_assert (GB_IS_DEVHELP_VIEW (self));

  ret = g_object_new (GB_TYPE_DEVHELP_VIEW,
                      "document", gb_devhelp_view_get_document (view),
                      "visible", TRUE,
                      NULL);

  return ret;
}

static void
gb_devhelp_view_set_split_view (GbView   *view,
                                gboolean  split_view)
{
  GbDevhelpView *self = (GbDevhelpView *)view;
  GbDevhelpViewPrivate *priv;

  g_assert (GB_IS_DEVHELP_VIEW (self));

  g_return_if_fail (GB_IS_DEVHELP_VIEW (view));

  priv = self->priv;

  if (split_view && (priv->web_view2 != NULL))
    return;

  if (!split_view && (priv->web_view2 == NULL))
    return;

  if (split_view)
    {
      priv->web_view2 = g_object_new (WEBKIT_TYPE_WEB_VIEW,
                                      "visible", TRUE,
                                      NULL);
      gtk_container_add_with_properties (GTK_CONTAINER (priv->paned), GTK_WIDGET (priv->web_view2),
                                         "shrink", FALSE,
                                         "resize", TRUE,
                                         NULL);
      gtk_widget_grab_focus (GTK_WIDGET (priv->web_view2));

      gb_devhelp_view_notify_uri (self,
                                  NULL,
                                  GB_DEVHELP_DOCUMENT (gb_devhelp_view_get_document (view)));
    }
  else
    {
      GtkWidget *copy = GTK_WIDGET (priv->web_view2);

      priv->web_view2 = NULL;
      gtk_container_remove (GTK_CONTAINER (priv->paned), copy);
      gtk_widget_grab_focus (GTK_WIDGET (priv->web_view1));
    }
}

static void
gb_devhelp_view_finalize (GObject *object)
{
  GbDevhelpViewPrivate *priv = GB_DEVHELP_VIEW (object)->priv;

  g_clear_object (&priv->document);

  G_OBJECT_CLASS (gb_devhelp_view_parent_class)->finalize (object);
}

static void
gb_devhelp_view_get_property (GObject    *object,
                              guint       prop_id,
                              GValue     *value,
                              GParamSpec *pspec)
{
  GbDevhelpView *self = GB_DEVHELP_VIEW (object);

  switch (prop_id)
    {
    case PROP_DOCUMENT:
      g_value_set_object (value, self->priv->document);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
gb_devhelp_view_set_property (GObject      *object,
                              guint         prop_id,
                              const GValue *value,
                              GParamSpec   *pspec)
{
  GbDevhelpView *self = GB_DEVHELP_VIEW (object);

  switch (prop_id)
    {
    case PROP_DOCUMENT:
      gb_devhelp_view_set_document (self, g_value_get_object (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
gb_devhelp_view_class_init (GbDevhelpViewClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GbViewClass *view_class = GB_VIEW_CLASS (klass);

  object_class->finalize = gb_devhelp_view_finalize;
  object_class->get_property = gb_devhelp_view_get_property;
  object_class->set_property = gb_devhelp_view_set_property;

  view_class->get_document = gb_devhelp_view_get_document;
  view_class->create_split = gb_devhelp_view_create_split;
  view_class->set_split_view =  gb_devhelp_view_set_split_view;

  gParamSpecs [PROP_DOCUMENT] =
    g_param_spec_object ("document",
                         _("Document"),
                         _("The document for the devhelp view."),
                         GB_TYPE_DEVHELP_DOCUMENT,
                         (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));
  g_object_class_install_property (object_class, PROP_DOCUMENT, gParamSpecs [PROP_DOCUMENT]);

  GB_WIDGET_CLASS_TEMPLATE (klass, "gb-devhelp-view.ui");
  GB_WIDGET_CLASS_BIND_PRIVATE (klass, GbDevhelpView, web_view1);
  GB_WIDGET_CLASS_BIND_PRIVATE (klass, GbDevhelpView, paned);

  g_type_ensure (WEBKIT_TYPE_WEB_VIEW);
}

static void
gb_devhelp_view_init (GbDevhelpView *self)
{
  self->priv = gb_devhelp_view_get_instance_private (self);

  gtk_widget_init_template (GTK_WIDGET (self));
}
