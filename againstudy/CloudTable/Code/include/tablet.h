#ifndef TABLET_H_
#define TABLET_H_
#include "global.h"
#include "item.h"
#define DEFAULT_DATASTORE_FILE_FOLDER "tablet"

typedef struct _Tablet Tablet;
short get_tablet_id(Tablet* tablet);
void set_last_flushed_id(Tablet* tablet, long long last_flushed_id);
long get_last_flushed_id(Tablet* tablet);
void set_max_item_id(Tablet* tablet, long long max_item_id);
char* get_tablet_folder(Tablet* tablet);
Tablet* load_tablet(char *tablet_folder);

/** this method will create the tablet folder, table name file and wal file**/
Tablet* create_tablet(int tablet_id, char *tablet_folder, char *table_name);
char* get_tablet_folder(Tablet *tablet);
boolean match_tablet(Tablet *tablet, char* table_name);
boolean match_tablet_by_table_name(Tablet *tablet, char* table_name);
void put_tablet(Tablet *tablet, long incr_item_id, Item *item);
ResultSet* query_tablet_row_key(Tablet *tablet, char* row_key);
ResultSet* query_tablet_by_timestamp(Tablet *tablet, long long begin_timestamp, long long end_timestamp);
ResultSet* query_tablet_all(Tablet *tablet);
char* get_metadata_tablet(Tablet *tablet);
void refresh_tablet(Tablet *tablet, int hotnessValue);
int get_used_size_tablet(Tablet *tablet);
int get_free_size_tablet(Tablet *tablet);

#endif /* TABLET_H_ */
