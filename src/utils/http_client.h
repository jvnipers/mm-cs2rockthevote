#ifndef _INCLUDE_RTV_HTTP_CLIENT_H_
#define _INCLUDE_RTV_HTTP_CLIENT_H_

// Minimal async HTTP(S) GET/POST utilities used by the RTV plugin.
// On Windows: WinHTTP.
// On Linux: libcurl.

#include <functional>
#include <string>

// Callback type: (success, responseBody)
using HttpCallback = std::function<void(bool success, std::string body)>;

// GET request. url must be https:// or http://.
// Callback is invoked on a background thread.
void RTV_HttpGet(const std::string &url, HttpCallback callback);

// POST request with JSON body.
void RTV_HttpPost(const std::string &url, const std::string &jsonBody, HttpCallback callback);

// Shutdown: wait for any pending requests to complete (called on plugin unload).
void RTV_HttpShutdown();

#endif // _INCLUDE_RTV_HTTP_CLIENT_H_
