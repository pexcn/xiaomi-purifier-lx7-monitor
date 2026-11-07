#pragma once
#include "Model.h"
#include <cstddef>

namespace Lx7Protocol {
enum class Result { Data, Ignore, Invalid, RpcError };
size_t makeRequest(char* out, size_t capacity, uint32_t requestId);
Result parseResponse(char* json, size_t size, uint32_t requestId, PurifierData& data);
}
