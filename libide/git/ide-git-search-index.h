/* ide-git-search-index.h
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

#ifndef IDE_GIT_SEARCH_INDEX_H
#define IDE_GIT_SEARCH_INDEX_H

#include "ide-object.h"

G_BEGIN_DECLS

#define IDE_TYPE_GIT_SEARCH_INDEX (ide_git_search_index_get_type())

G_DECLARE_FINAL_TYPE (IdeGitSearchIndex, ide_git_search_index,
                      IDE, GIT_SEARCH_INDEX, IdeObject)

void ide_git_search_index_populate (IdeGitSearchIndex *self,
                                    IdeSearchProvider *provider,
                                    IdeSearchContext  *context,
                                    gsize              max_results,
                                    const gchar       *search_terms);

G_END_DECLS

#endif /* IDE_GIT_SEARCH_INDEX_H */
