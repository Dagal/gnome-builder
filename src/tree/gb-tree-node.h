/* gb-tree-node.h
 *
 * Copyright (C) 2011 Christian Hergert <chris@dronelabs.com>
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

#ifndef GB_TREE_NODE_H
#define GB_TREE_NODE_H

#include <gtk/gtk.h>

#if 0
#include "gb-project-item.h"
#endif

G_BEGIN_DECLS

#define GB_TYPE_TREE_NODE            (gb_tree_node_get_type())
#define GB_TREE_NODE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GB_TYPE_TREE_NODE, GbTreeNode))
#define GB_TREE_NODE_CONST(obj)      (G_TYPE_CHECK_INSTANCE_CAST ((obj), GB_TYPE_TREE_NODE, GbTreeNode const))
#define GB_TREE_NODE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  GB_TYPE_TREE_NODE, GbTreeNodeClass))
#define GB_IS_TREE_NODE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GB_TYPE_TREE_NODE))
#define GB_IS_TREE_NODE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GB_TYPE_TREE_NODE))
#define GB_TREE_NODE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  GB_TYPE_TREE_NODE, GbTreeNodeClass))

typedef struct _GbTreeNode        GbTreeNode;
typedef struct _GbTreeNodeClass   GbTreeNodeClass;
typedef struct _GbTreeNodePrivate GbTreeNodePrivate;

G_DEFINE_AUTOPTR_CLEANUP_FUNC (GbTreeNode, g_object_unref)

struct _GbTreeNode
{
	GInitiallyUnowned parent;

	/*< private >*/
	GbTreeNodePrivate *priv;
};

struct _GbTreeNodeClass
{
	GInitiallyUnownedClass parent_class;
};

GbTreeNode    *gb_tree_node_new           (void);
void           gb_tree_node_append        (GbTreeNode   *node,
                                           GbTreeNode   *child);
const gchar   *gb_tree_node_get_icon_name (GbTreeNode   *node);
GObject       *gb_tree_node_get_item      (GbTreeNode   *node);
GbTreeNode    *gb_tree_node_get_parent    (GbTreeNode   *node);
GtkTreePath   *gb_tree_node_get_path      (GbTreeNode   *node);
GType          gb_tree_node_get_type      (void);
void           gb_tree_node_prepend       (GbTreeNode  *node,
                                           GbTreeNode   *child);
void           gb_tree_node_remove        (GbTreeNode   *node,
                                           GbTreeNode   *child);
void           gb_tree_node_set_icon_name (GbTreeNode   *node,
                                           const gchar  *icon_name);
void           gb_tree_node_set_item      (GbTreeNode   *node,
                                           GObject      *item);
void           gb_tree_node_expand        (GbTreeNode   *node,
                                           gboolean      expand_ancestors);
void           gb_tree_node_collapse      (GbTreeNode   *node);
void           gb_tree_node_select        (GbTreeNode   *node);
void           gb_tree_node_get_area      (GbTreeNode   *node,
                                           GdkRectangle *area);
void           gb_tree_node_rebuild       (GbTreeNode   *node);
gboolean       gb_tree_node_get_expanded  (GbTreeNode   *node);
void           gb_tree_node_show_popover  (GbTreeNode   *node,
                                           GtkPopover   *popover);
const gchar   *gb_tree_node_get_text      (GbTreeNode   *node);
void           gb_tree_node_set_text      (GbTreeNode   *node,
                                           const gchar  *text);

G_END_DECLS

#endif /* GB_TREE_NODE_H */
