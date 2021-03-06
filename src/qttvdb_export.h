/* This file is part of QtTvDB
 *
 * Copyright (C) 2009-2011 Corentin Chary <corentin.chary@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef QTTVDB_EXPORT_H
#define QTTVDB_EXPORT_H

#include <QtCore/qglobal.h>

#ifndef QTTVDB_EXPORT
# if defined(QTTVDB_MAKEDLL)
   /* We are building this library */
#  define QTTVDB_EXPORT Q_DECL_EXPORT
# else
   /* We are using this library */
#  define QTTVDB_EXPORT Q_DECL_IMPORT
# endif
#endif

#endif
