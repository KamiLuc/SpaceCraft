#pragma once

struct EventInfo
{
	EventInfo() { this->code = 0; }
	EventInfo(int event) { this->code = event; }
	union {
		int code;
	};
};