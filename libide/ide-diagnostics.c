/* ide-diagnostics.c
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

#include "ide-diagnostic.h"
#include "ide-diagnostics.h"

G_DEFINE_BOXED_TYPE (IdeDiagnostics, ide_diagnostics,
                     ide_diagnostics_ref, ide_diagnostics_unref)

struct _IdeDiagnostics
{
  volatile gint  ref_count;
  GPtrArray     *diagnostics;
};

/**
 * _ide_diagnostics_new:
 * @ar: (transfer full) (nullable): an array of #IdeDiagnostic.
 *
 * Creates a new #IdeDiagnostics container structure for @ar.
 * Ownership of @ar is transfered to the resulting structure.
 *
 * Returns: (transfer full): A newly allocated #IdeDiagnostics.
 */
IdeDiagnostics *
_ide_diagnostics_new (GPtrArray *ar)
{
  IdeDiagnostics *ret;

  ret = g_slice_new0 (IdeDiagnostics);
  ret->ref_count = 1;
  ret->diagnostics = ar ? ar : g_ptr_array_new_with_free_func (g_object_unref);

  return ret;
}

IdeDiagnostics *
ide_diagnostics_ref (IdeDiagnostics *self)
{
  g_return_val_if_fail (self, NULL);
  g_return_val_if_fail (self->ref_count > 0, NULL);

  g_atomic_int_inc (&self->ref_count);

  return self;
}

void
ide_diagnostics_unref (IdeDiagnostics *self)
{
  g_return_if_fail (self);
  g_return_if_fail (self->ref_count > 0);

  if (g_atomic_int_dec_and_test (&self->ref_count))
    {
      g_ptr_array_unref (self->diagnostics);
      g_slice_free (IdeDiagnostics, self);
    }
}

/**
 * ide_diagnostics_merge:
 *
 * Copies the contents of @other into @self.
 *
 * This is performed by taking a reference to the immutable #IdeDiagnostic
 * instances.
 */
void
ide_diagnostics_merge (IdeDiagnostics *self,
                       IdeDiagnostics *other)
{
  gsize i;

  g_return_if_fail (self);
  g_return_if_fail (other);

  for (i = 0; i < other->diagnostics->len; i++)
    {
      IdeDiagnostic *diag;

      diag = g_ptr_array_index (other->diagnostics, i);
      g_ptr_array_add (self->diagnostics, ide_diagnostic_ref (diag));
    }
}

/**
 * ide_diagnostics_get_size:
 *
 * Retrieves the number of diagnostics that can be accessed via
 * ide_diagnostics_index().
 *
 * Returns: The number of diagnostics in @self.
 */
gsize
ide_diagnostics_get_size (IdeDiagnostics *self)
{
  g_return_val_if_fail (self, 0);
  g_return_val_if_fail (self->diagnostics, 0);

  return self->diagnostics->len;
}

/**
 * ide_diagnostics_index:
 *
 * Retrieves the diagnostic at @index.
 *
 * Returns: (transfer none): An #IdeDiagnostic.
 */
IdeDiagnostic *
ide_diagnostics_index (IdeDiagnostics *self,
                       gsize           index)
{
  g_return_val_if_fail (self, NULL);
  g_return_val_if_fail (self->diagnostics, NULL);
  g_return_val_if_fail (index < self->diagnostics->len, NULL);

  return g_ptr_array_index (self->diagnostics, index);
}