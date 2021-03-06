#ifndef REGION_H_
#define REGION_H_

#include "global.h"

/** The below methods just used for reference, won't directly called **/
#define ADD_NEW_TABLET_REGION_CMD "add_new_tablet"
boolean add_new_tablet_region(char *table_name);
#define PUT_DATA_REGION_CMD "put_data_region"
boolean put_data_region(char *table_name, ResultSet* resultSet);

#define QUERY_ROW_REGION_CMD "query_row_region"
ResultSet* query_row_region(char* table_name, char* row_key);

#define QUERY_ALL_REGION_CMD "query_all_region"
ResultSet* query_all_region(char* table_name);

#define GET_METADATA_REGION_CMD "get_metadata_region"
char* get_metadata_region(char* table_name);

#define AVAILABLE_SPACE_REGION_CMD "available_space_region"
int available_space_region(void);

#define TABLET_USED_SIZE_REGION_CMD "tablet_used_size_region"
int tablet_used_size_region(char* table_name);

#define START_SYNC_REGION_CMD "start_sync_region"
boolean start_sync_region(char* target_conn, char* table_name, long long begin_timestamp, long long end_timestamp);

#endif /* REGION_H_ */
