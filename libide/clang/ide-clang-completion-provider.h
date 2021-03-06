/* ide-clang-completion-provider.h
 *
 * Copyright (C) 2015 Christian Hergert <christian@hergert.me>
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

#ifndef IDE_CLANG_COMPLETION_PROVIDER_H
#define IDE_CLANG_COMPLETION_PROVIDER_H

#include <gtksourceview/gtksourcecompletionprovider.h>

G_BEGIN_DECLS

#define IDE_TYPE_CLANG_COMPLETION_PROVIDER            (ide_clang_completion_provider_get_type())
#define IDE_CLANG_COMPLETION_PROVIDER(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), IDE_TYPE_CLANG_COMPLETION_PROVIDER, IdeClangCompletionProvider))
#define IDE_CLANG_COMPLETION_PROVIDER_CONST(obj)      (G_TYPE_CHECK_INSTANCE_CAST ((obj), IDE_TYPE_CLANG_COMPLETION_PROVIDER, IdeClangCompletionProvider const))
#define IDE_CLANG_COMPLETION_PROVIDER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  IDE_TYPE_CLANG_COMPLETION_PROVIDER, IdeClangCompletionProviderClass))
#define IDE_IS_CLANG_COMPLETION_PROVIDER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IDE_TYPE_CLANG_COMPLETION_PROVIDER))
#define IDE_IS_CLANG_COMPLETION_PROVIDER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  IDE_TYPE_CLANG_COMPLETION_PROVIDER))
#define IDE_CLANG_COMPLETION_PROVIDER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  IDE_TYPE_CLANG_COMPLETION_PROVIDER, IdeClangCompletionProviderClass))

typedef struct _IdeClangCompletionProvider        IdeClangCompletionProvider;
typedef struct _IdeClangCompletionProviderClass   IdeClangCompletionProviderClass;

GType ide_clang_completion_provider_get_type (void);

G_END_DECLS

#endif /* IDE_CLANG_COMPLETION_PROVIDER_H */
