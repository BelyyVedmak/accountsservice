/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2012 Matthew Monaco
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "util.h"

Config *cfg_init()
{
        gboolean b;
        GKeyFile *f;

        f = g_key_file_new();
        b = g_key_file_load_from_file(f, PATH_CONFIG_FILE, G_KEY_FILE_NONE, NULL);

        if (b) {
                g_key_file_set_list_separator(f, ' ');
                return (Config*) f;
        } else {
                g_key_file_free(f);
                return NULL;
        }
}

void cfg_free(Config *cfg)
{
        GKeyFile *f = (GKeyFile*) cfg;
        g_key_file_free(f);
}

gchar **cfg_get_excludes(Config *cfg)
{
        return g_key_file_get_string_list(cfg, "UserList", "Exclude", NULL, NULL);
}

void cfg_free_excludes(Config *cfg, gchar **e)
{
        g_strfreev(e);
}

uid_t cfg_get_min_uid(Config *cfg)
{
        GKeyFile *f = (GKeyFile*) cfg;
        int i = g_key_file_get_integer(f, "UserList", "MinUID", NULL);
        if (i < 0) i = 0;
        return (uid_t) i;
}

/* vim: set ts=8 sw=8 sts=8 et : */
