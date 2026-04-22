#include "uhepch.h"
#include "UIID.h"

namespace UHE {
static std::random_device rd;
static std::mt19937_64 s_Engine(rd());
static std::uniform_int_distribution<u64> s_Distribution;

static std::unordered_set<u64, UUID> s_UUIDMap;

 UUID::UUID() 
	 : m_UUID(s_Distribution(s_Engine))
 {

 }

 UUID::UUID(u64 uuid)
 {

 }

 }