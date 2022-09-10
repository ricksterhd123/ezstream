/*
 * Copyright (c) 2007 Moritz Grimm <mgrimm@mrsserver.net>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__

typedef struct playlist *	playlist_t;

/*
 * Initialize the playlist routines. Should be called before any of the other
 * playlist functions.
 */
int		playlist_init(void);

/*
 * Clean up for clean shutdowns. No-op at the moment.
 */
void		playlist_exit(void);

/*
 * Read a playlist file (in .M3U format), and return a new playlist handler
 * on success, or NULL on failure.
 */
playlist_t	playlist_read(const char * /* filename */);

/*
 * For each call to playlist_get_next(), the specified program is run. This
 * program is supposed to print one line to standard output, containing the
 * path and filename of a media file.
 */
playlist_t	playlist_program(const char * /* program name */);

/*
 * Free all memory used by a playlist handler that was created with
 * playlist_read().
 */
void		playlist_free(playlist_t *);

/*
 * Get the next item in the playlist. Returns a NUL-terminated string of a
 * playlist entry, or NULL if the end of the list has been reached.
 */
const char *	playlist_get_next(playlist_t);

/*
 * The functions below work on playlist handlers obtained with playlist_read()
 * and are no-ops (i.e. return failure) for playlists from playlist_program().
 */

/*
 * Skip the playlist item that would be played next.
 */
void		playlist_skip_next(playlist_t);

/*
 * Get the number of items in the playlist.
 */
unsigned long	playlist_get_num_items(playlist_t);

/*
 * Get the current position in the playlist.
 */
unsigned long	playlist_get_position(playlist_t);

/*
 * Search for a given entry in the playlist and reposition to it. Returns 1 on
 * success and 0 on failure. A subsequent call to playlist_get_next() will
 * return this list item again.
 */
int		playlist_goto_entry(playlist_t, const char * /* name */);

/*
 * Rewind the playlist to the beginning, so that it can be replayed. Does
 * not reread the playlist file.
 */
void		playlist_rewind(playlist_t);

/*
 * Reread the playlist file and rewind to the beginning. Equivalent to calling
 * playlist_free() and playlist_read(). Entries will no longer be shuffled
 * after calling this function.
 * Returns 1 on success, and 0 on error.
 */
int		playlist_reread(playlist_t *);

/*
 * Shuffle the entries of the playlist randomly.
 */
void		playlist_shuffle(playlist_t);

/*
 * Return the path where the playlist file or program is located on disk.
 */
const char *	playlist_get_location(playlist_t);

#endif /* __PLAYLIST_H__ */
