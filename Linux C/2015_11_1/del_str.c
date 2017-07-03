#include <stdio.h>
#include <string.h>
int find_str(char *src, char *lim_str);

int main(int argc, char *argv[])
{
	char str1[100] = {0};
	char str2[100] = {0};
	int index = 0;
	int str2_len = 0;
	int i = 0;
	int j = 0;

	scanf("%s%s",str1, str2);

	str2_len = strlen(str2);
	index = find_str(str1, str2);
	if (index != -1) {
		j = index + str2_len;

		for (i = index; str1[j]; i++, j++) {
			str1[i] = str1[j];
		}
		str1[i] = '\0';
	}
	
	printf("%s\n", str1);
	return 0;
}


int find_str(char *src, char *lim_str)
{
	int index = -1;
	int i = 0;
	int j = 0;
	int k = 0;
	int flag = 1;

	for (i = 0; src[i]; i++) {
		flag = 1;
		k = i;
		for (j = 0; lim_str[j] && src[k]; j++, k++) {
			if (src[k] != lim_str[j]) {
				flag = 0;
				break;
			}
		}
		if (flag) {
			index = i;
			break;
		}
	}

	return index;
}
