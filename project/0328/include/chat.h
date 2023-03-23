#include "../include/protocol.h"
#include "../include/user.h"

void chat(int fd,struct protocol * protocol_ptr, struct user * user_ptr);



void broadcast_mode(int fd,struct protocol * protocol_ptr, struct user * user_ptr);

void whisper_mode();

void command_mode();