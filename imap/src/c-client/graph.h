/* ========================================================================
 * Copyright 2021-2026 Eduardo Chappa
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * 
 * ========================================================================
 */


void *graph_parameters (long, void *);
MAILSTREAM *graph_send_open (ADDRESS *);
long graph_send_soutr(void *, char *);
int graph_send_mail(MAILSTREAM *);
char *imap_host (MAILSTREAM *);
