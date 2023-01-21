#include <stdlib.h>

#include "dansu-user.h"
#include "helpers.h"

// Taken from http://www.cse.yorku.ca/~oz/hash.html
uint64_t SimpleHash(uint8_t* str) {
	uint64_t hash = 5381;
	int c;
	while (c = *str++) {
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}

uint8_t AddUser(DansuOS* dansu, char* username, char* password) {
	int idx = dansu->num_users;
	dansu->num_users++;
	dansu->users = (UserBytes*)realloc(dansu->users, dansu->num_users * sizeof(UserBytes));
	CheckAlloc(dansu->users, "Failed to allocate space for new user");

	int username_len = 0;
	do {
		username_len++;
	} while (username_len < 15 && username[username_len] != '\0');
	username[username_len] = '\0';
	memcpy(dansu->users[idx].u.username, username, username_len);

	dansu->users[idx].u.password = SimpleHash(password);

	return 1;
}
