/* ide-buffer.h
 *
 * Copyright (C) 2015 Christian Hergert <christian@hergert.me>
 *
 * This file is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef IDE_BUFFER_H
#define IDE_BUFFER_H

#include <glib-object.h>

G_BEGIN_DECLS

#define IDE_TYPE_BUFFER               (ide_buffer_get_type ())
#define IDE_BUFFER(obj)               (G_TYPE_CHECK_INSTANCE_CAST ((obj), IDE_TYPE_BUFFER, IdeBuffer))
#define IDE_IS_BUFFER(obj)            (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IDE_TYPE_BUFFER))
#define IDE_BUFFER_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), IDE_TYPE_BUFFER, IdeBufferInterface))

struct _IdeBufferInterface
{
  GTypeInterface parent;
};

GType ide_buffer_get_type (void);

G_END_DECLS

#endif /* IDE_BUFFER_H */