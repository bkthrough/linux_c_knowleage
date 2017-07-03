#ifndef WAL_H_
#define WAL_H_
#include "global.h"
#include "list.h"
#include "item.h"

typedef struct _Wal Wal;
typedef struct _WalItem WalItem;
short get_tablet_id_wal_item(WalItem* walItem);
long long get_item_id_wal_item(WalItem* walItem);
Item* get_item_wal_item(WalItem* walItem);
void free_wal_item_void(void* walItem);
Wal* load_wal(char* file_path);
void append_wal_item(Wal *wal, WalItem* walItem);
WalItem* create_wal_item(short tablet_id, long item_id,Item *item);
void reset_log_wal(Wal *wal);
boolean need_to_reload_wal(Wal *wal);
List* load_log_wal(Wal *wal);
void refresh_wal(Wal *wal, List* walItems);

#endif /* WAL_H_ */
