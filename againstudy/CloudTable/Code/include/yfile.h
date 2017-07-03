#ifndef YFILE_H_
#define YFILE_H_

#include "global.h"
#include "item.h"

typedef struct _YFile YFile;
YFile* loading_yfile(char* file_path);
YFile* create_new_yfile(char* file_path, ResultSet* resultSet, char* table_name);
ResultSet* query_yfile_by_row_key(YFile* yfile, char* row_key);
ResultSet* query_yfile_by_timestamp(YFile* yfile, long long begin_timestamp, long long end_timestamp);
void refresh_yfile_data_block_cache(YFile* yfile, int hotness_value);
char* get_yfile_metadata(YFile* yfile);

#endif /* YFILE_H_ */
