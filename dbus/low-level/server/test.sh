#!/bin/bash

OBJECT_PATH="/template/server/Interface"
MESSAGE="template.server.Interface.Ping"

ping() {
	dbus-send --session --print-reply --dest='template.server.method' $OBJECT_PATH $MESSAGE
}

ping
