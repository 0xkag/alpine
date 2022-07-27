typedef enum  {Draft, Flagged, Passed, Replied, Seen, Trashed, 
	       EmptyFlag, EndFlags} MdFlagNamesType;

typedef enum {Cur, Tmp, New, EndDir} DirNamesType;

typedef struct courier_local {
  char *name;		/* name of directory/folder */
  int attribute;	/* attributes (children/marked/etc) */
} COURIERLOCAL;

typedef struct courier {
  char *path;			/* Path to collection */
  time_t scantime;		/* time at which information was generated */
  int total;			/* total number of elements in data */
  COURIERLOCAL **data;
} COURIER_S;

typedef struct maildir_file_info {
   char *name;		/* name of the file			   */
   DirNamesType loc;	/* location of this file		   */
   unsigned long pos;	/* place in list where this file is listed */
   off_t size;		/* size in bytes, on disk */
   time_t atime;	/* last access time */
   time_t mtime;	/* last modified time */
   time_t ctime;	/* last changed time */
} MAILDIRFILE;

/* Function prototypes */

DRIVER *maildir_valid (char *name);
MAILSTREAM *maildir_open (MAILSTREAM *stream);
void maildir_close (MAILSTREAM *stream, long options);
long maildir_ping (MAILSTREAM *stream);
void maildir_check (MAILSTREAM *stream);
long maildir_text (MAILSTREAM *stream,unsigned long msgno,STRING *bs,long flags);
char *maildir_header (MAILSTREAM *stream,unsigned long msgno,
		unsigned long *length, long flags);
void maildir_list (MAILSTREAM *stream,char *ref,char *pat);
void *maildir_parameters (long function,void *value);
int maildir_create_folder (char *mailbox);
long maildir_create (MAILSTREAM *stream,char *mailbox);
void maildir_flagmsg (MAILSTREAM *stream,MESSAGECACHE *elt); /*check */
long maildir_expunge (MAILSTREAM *stream, char *sequence, long options);
long maildir_copy (MAILSTREAM *stream,char *sequence,char *mailbox,long options);
long maildir_append (MAILSTREAM *stream,char *mailbox, append_t af, void *data);
long maildir_delete (MAILSTREAM *stream,char *mailbox);
long maildir_rename (MAILSTREAM *stream,char *old,char *new);
long maildir_sub (MAILSTREAM *stream,char *mailbox);
long maildir_unsub (MAILSTREAM *stream,char *mailbox);
void maildir_lsub (MAILSTREAM *stream,char *ref,char *pat);
void courier_list (MAILSTREAM *stream,char *ref, char *pat);

/* utility functions */
void courier_realname (char *name, char *realname);
long maildir_dirfmttest (char *name);
char *maildir_file (char *dst,char *name);
int maildir_select (const struct direct *name);
int maildir_namesort (const struct direct **d1, const struct direct **d2);
unsigned long antoul (char *seed);
unsigned long mdfntoul (char *name);
int courier_dir_select (const struct direct *name);
int courier_dir_sort (const struct direct **d1, const struct direct **d2);
long maildir_canonicalize (char *pattern,char *ref,char *pat);
void maildir_list_work (MAILSTREAM *stream,char *subdir,char *pat,long level);
void courier_list_work (MAILSTREAM *stream,char *subdir,char *pat,long level);
int maildir_file_path(char *name, char *tmp, size_t sizeoftmp);
int maildir_valid_name (char *name);
int maildir_valid_dir (char *name);
int is_valid_maildir (char **name);
int maildir_message_exists(MAILSTREAM *stream,char *name, char *tmp);
char *maildir_remove_root(char *name);
char *maildir_text_work (MAILSTREAM *stream,MESSAGECACHE *elt, unsigned long *length,long flags);
unsigned long  maildir_parse_message(MAILSTREAM *stream, unsigned long msgno, 
						DirNamesType dirtype);
int maildir_eliminate_duplicate (char *name, struct direct ***flist, 
					unsigned long *nfiles);
int maildir_doscandir (char *name, struct direct ***flist, int flag);
unsigned long maildir_scandir (char *name, struct direct ***flist,
			unsigned long *nfiles, int *scand, int flag);
void maildir_parse_folder (MAILSTREAM *stream, int full);
void  md_domain_name (void);
char  *myrootdir (char *name);
char  *mdirpath (void);
int   maildir_initial_check (MAILSTREAM *stream, DirNamesType dirtype);
unsigned long  maildir_parse_dir(MAILSTREAM *stream, unsigned long nmsgs, 
   DirNamesType dirtype, struct direct **names, unsigned long nfiles, int full);
int same_maildir_file(char *name1, char *name2);
int comp_maildir_file(char *name1, char *name2);
int maildir_message_in_list(char *msgname, struct direct **names,
		unsigned long bottom, unsigned long top, unsigned long *pos);
void maildir_getflag(char *name, int *d, int *f, int *r ,int *s, int *t);
int maildir_update_elt_maildirp(MAILSTREAM *stream, unsigned long msgno);
void maildir_abort (MAILSTREAM *stream);
int maildir_contains_folder(char *dirname, char *name);
int maildir_is_dir(char *dirname, char *name);
int maildir_dir_is_empty(char *mailbox);
int maildir_create_work (char *mailbox, int loop);
void maildir_get_file (MAILDIRFILE **mdfile);
void maildir_free_file (void **mdfile);
void maildir_free_file_only (void **mdfile);
int maildir_any_new_msgs(char *mailbox);
void maildir_get_date(MAILSTREAM *stream, unsigned long msgno);
void maildir_fast (MAILSTREAM *stream,char *sequence,long flags);

/* Courier server support */
void courier_free_cdir (COURIER_S **cdir);
COURIER_S *courier_get_cdir (int total);
int courier_search_list(COURIERLOCAL **data, char *name, int first, int last);
COURIER_S *courier_list_dir(char *curdir);
void courier_list_info(COURIER_S **cdirp, char *data, int i);

/* UID Support */
int maildir_can_assign_uid (MAILSTREAM *stream);
void maildir_read_uid(MAILSTREAM *stream, unsigned long *uid_last, 
     			                   unsigned long *uid_validity);
void maildir_write_uid(MAILSTREAM *stream, unsigned long uid_last, 
     			                   unsigned long uid_validity);
unsigned long maildir_get_uid(char *name);
void maildir_delete_uid(MAILSTREAM *stream, unsigned long msgno);
void maildir_assign_uid(MAILSTREAM *stream, unsigned long msgno, unsigned long uid);
void maildir_uid_renew_tempfile(MAILSTREAM *stream);

