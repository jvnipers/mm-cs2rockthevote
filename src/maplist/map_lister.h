#ifndef _INCLUDE_RTV_MAP_LISTER_H_
#define _INCLUDE_RTV_MAP_LISTER_H_

#include <functional>
#include <string>
#include <vector>

struct MapEntry
{
	std::string displayName; // Full display name, e.g. "kz_grotto (T3, Linear)"
	std::string mapName;     // Clean name for changelevel, e.g. "kz_grotto"
	std::string workshopId;  // Workshop ID if present, else empty
	bool isWorkshop = false;
};

class MapLister
{
public:
	// Load maps from file. Returns number of maps loaded, or -1 on error.
	// If file doesn't exist and KzTierMode is set, triggers auto-generate.
	int LoadFromFile(const char *path);

	// Reload using the last used path.
	int Reload();

	// Dynamically add a map (from API lookup / off-maplist nomination).
	// Does not write to disk. Returns pointer to the entry.
	const MapEntry *AddDynamicMap(const MapEntry &entry);

	const std::vector<MapEntry> &GetMaps() const
	{
		return m_maps;
	}

	// Find exact match by display name or map name (case-insensitive).
	const MapEntry *FindExact(const std::string &name) const;

	// Find exact match by workshop ID.
	const MapEntry *FindByWorkshopId(const std::string &workshopId) const;

	// Find all maps whose display/map name contains the query string.
	std::vector<const MapEntry *> FindMatching(const std::string &query) const;

	// Resolve a user input string to a single map (exact first, then partial).
	// Returns nullptr if no match or multiple matches (caller should show menu).
	// outMatches is populated with all partial matches when nullptr is returned.
	const MapEntry *Resolve(const std::string &input, std::vector<const MapEntry *> *outMatches) const;

	bool IsLoaded() const
	{
		return !m_maps.empty();
	}

	// Async API lookups (run on background thread; callback on same thread).
	// DO NOT call game engine APIs from the callback - set a flag and handle on next GameFrame tick.

	// Look up a map by workshop ID via CS2KZ API, then Steam fallback.
	// callback(entry) where entry.mapName is empty on failure.
	void LookupByWorkshopIdAsync(const std::string &workshopId, std::function<void(MapEntry)> callback) const;

	// Look up a map by name via CS2KZ API.
	void LookupByNameAsync(const std::string &name, std::function<void(MapEntry)> callback) const;

	// Fetch all approved maps from CS2KZ API and write maplist.txt.
	// Called automatically when LoadFromFile() returns missing file.
	void GenerateMaplistAsync(const std::string &outputPath) const;

	// Validate all workshop maps via Steam API.
	// Dead maps are reported to server console and optionally Discord webhook.
	void ValidateMapsAsync() const;

private:
	std::vector<MapEntry> m_maps;
	std::string m_lastPath;

	// Parse a single line into a MapEntry. Returns false if line should be
	// skipped.
	static bool ParseLine(const std::string &line, MapEntry &out);

	// Strip the annotation part: "kz_grotto (T3)" -> "kz_grotto"
	static std::string StripAnnotation(const std::string &displayName);

	// Build a MapEntry from a CS2KZ API JSON map object string fragment.
	// Returns false if parsing failed.
	static bool ParseCS2KZMapJson(const std::string &jsonObj, MapEntry &out);
};

extern MapLister g_MapLister;

#endif // _INCLUDE_RTV_MAP_LISTER_H_
