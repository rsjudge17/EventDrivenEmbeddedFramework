/*
 * Copyright (C) 2013 Yuriy Kulikov yuriy.kulikov.87@gmail.com
 * Copyright (C) 2013 Alexey Serdyuk
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef HANDLER_H_
#define HANDLER_H_

#include "Message.h"
#include "MsgQueue.h"

typedef struct MESSAGE Message;
typedef struct HANDLER Handler;
typedef struct MSG_QUEUE MsgQueue;

#define NULL_CONTEXT 0

/**
 * The prototype to which handleMessage functions used to process messages must comply.
 * @param msg - message to handle
 * @param *context - context of current Handler. Store variables there
 * @param *handler - pointer to the handler, to modify or look into the queue
 */
typedef void (*HANDLE_MESSAGE_CALLBACK)(Message msg, void *context, Handler *handler);

/** Struct represents handler */
struct HANDLER {
    /** Pointer to queue on which handler posts messages */
    MsgQueue* messageQueue;
    /** Function which handles messages*/
    HANDLE_MESSAGE_CALLBACK handleMessage;
    /** Execution context of current handler, handleMessage should cast it to something */
    void *context;
};

void Handler_init(Handler *handler, MsgQueue *msgQueue, HANDLE_MESSAGE_CALLBACK handleMessage, void *context);
Message * Handler_obtain(Handler *handler, portBASE_TYPE what);
void Handler_sendMessage(Handler *handler, Message * message);
void Handler_sendMessageDelayed(Handler *handler, Message * message, unsigned portLONG);
void Handler_sendEmptyMessage(Handler *handler, portBASE_TYPE what);

#endif /* HANDLER_H_ */
