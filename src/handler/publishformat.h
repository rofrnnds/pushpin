/*
 * Copyright (C) 2016-2017 Fanout, Inc.
 *
 * This file is part of Pushpin.
 *
 * Pushpin is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Pushpin is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PUBLISHFORMAT_H
#define PUBLISHFORMAT_H

#include <QByteArray>
#include <QString>
#include <QVariant>
#include "httpheaders.h"

class PublishFormat
{
public:
	enum Type
	{
		HttpResponse,
		HttpStream,
		WebSocketMessage
	};

	enum Action
	{
		Send,
		Hint,
		Close
	};

	enum MessageType
	{
		Text,
		Binary,
		Ping,
		Pong
	};

	Type type;
	Action action; // response/stream/ws
	int code; // response/ws
	QByteArray reason; // response
	HttpHeaders headers; // response
	QByteArray body; // response/stream/ws
	bool haveBodyPatch; // response
	QVariantList bodyPatch; // response
	MessageType messageType; // ws
	bool haveContentFilters;
	QStringList contentFilters; // response/stream

	PublishFormat() :
		type((Type)-1),
		action(Send),
		code(-1),
		haveBodyPatch(false),
		messageType((MessageType)-1),
		haveContentFilters(false)
	{
	}

	PublishFormat(Type _type) :
		type(_type),
		action(Send),
		code(-1),
		haveBodyPatch(false),
		messageType((MessageType)-1),
		haveContentFilters(false)
	{
	}

	static PublishFormat fromVariant(Type type, const QVariant &in, bool *ok = 0, QString *errorMessage = 0);
};

#endif
