/* ide-source-snippet-completion-item.h
 *
 * Copyright (C) 2013 Christian Hergert <christian@hergert.me>
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

#ifndef IDE_SOURCE_SNIPPET_COMPLETION_ITEM_H
#define IDE_SOURCE_SNIPPET_COMPLETION_ITEM_H

#include <gtksourceview/gtksourcecompletionproposal.h>

#include "ide-source-snippet.h"

G_BEGIN_DECLS

#define IDE_TYPE_SOURCE_SNIPPET_COMPLETION_ITEM            (ide_source_snippet_completion_item_get_type())
#define IDE_SOURCE_SNIPPET_COMPLETION_ITEM(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), IDE_TYPE_SOURCE_SNIPPET_COMPLETION_ITEM, IdeSourceSnippetCompletionItem))
#define IDE_SOURCE_SNIPPET_COMPLETION_ITEM_CONST(obj)      (G_TYPE_CHECK_INSTANCE_CAST ((obj), IDE_TYPE_SOURCE_SNIPPET_COMPLETION_ITEM, IdeSourceSnippetCompletionItem const))
#define IDE_SOURCE_SNIPPET_COMPLETION_ITEM_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  IDE_TYPE_SOURCE_SNIPPET_COMPLETION_ITEM, IdeSourceSnippetCompletionItemClass))
#define IDE_IS_SOURCE_SNIPPET_COMPLETION_ITEM(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IDE_TYPE_SOURCE_SNIPPET_COMPLETION_ITEM))
#define IDE_IS_SOURCE_SNIPPET_COMPLETION_ITEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  IDE_TYPE_SOURCE_SNIPPET_COMPLETION_ITEM))
#define IDE_SOURCE_SNIPPET_COMPLETION_ITEM_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  IDE_TYPE_SOURCE_SNIPPET_COMPLETION_ITEM, IdeSourceSnippetCompletionItemClass))

typedef struct _IdeSourceSnippetCompletionItem        IdeSourceSnippetCompletionItem;
typedef struct _IdeSourceSnippetCompletionItemClass   IdeSourceSnippetCompletionItemClass;
typedef struct _IdeSourceSnippetCompletionItemPrivate IdeSourceSnippetCompletionItemPrivate;

struct _IdeSourceSnippetCompletionItem
{
  GObject parent;

  /*< private >*/
  IdeSourceSnippetCompletionItemPrivate *priv;
};

struct _IdeSourceSnippetCompletionItemClass
{
  GObjectClass parent_class;
};

GType                        ide_source_snippet_completion_item_get_type    (void);
GtkSourceCompletionProposal *ide_source_snippet_completion_item_new         (IdeSourceSnippet *snippet);
IdeSourceSnippet             *ide_source_snippet_completion_item_get_snippet (IdeSourceSnippetCompletionItem *item);
void                         ide_source_snippet_completion_item_set_snippet (IdeSourceSnippetCompletionItem *item,
                                                                            IdeSourceSnippet               *snippet);

G_END_DECLS

#endif /* IDE_SOURCE_SNIPPET_COMPLETION_ITEM_H */
