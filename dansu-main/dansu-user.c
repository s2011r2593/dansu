#include <stdlib.h>
#include <string.h>

#include "dansu-user.h"
#include "dansu-helpers.h"

uint8_t AddUser(DansuOS* dansu, char* username, char* password) {
	uint64_t idx = dansu->num_users;
	dansu->num_users++;
	dansu->users = (UserBytes*)realloc(dansu->users, dansu->num_users * sizeof(UserBytes));
	CheckAlloc(dansu->users, "Failed to allocate space for new user");

	int username_len = 0;
	do {
		username_len++;
	} while (username_len < 15 && username[username_len] != '\0');
	username[username_len] = '\0';
	for (int i = 0; i < username_len; i++) {
		dansu->users[idx].u.username[i] = username[i];
	}

	dansu->users[idx].u.password = SimpleHash(password);

	return 1;
}
