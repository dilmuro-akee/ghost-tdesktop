/*
Ghost Mode options for this fork of Telegram Desktop.

Header-only: each option is an `inline` base::options::toggle, so it registers
itself once and shows up as a switch in Settings > Advanced > Experimental.
Read a value anywhere with e.g. `Ghost::NoReadReceipts.value()`.
*/
#pragma once

#include "base/options.h"
#include "base/flat_set.h"
#include "data/data_msg_id.h"

namespace Ghost {

// Remembers which incoming messages were originally view-once / self-destruct,
// so Forward can re-upload their media (forwarding them by id is rejected by the
// server with MESSAGE_ID_INVALID).
[[nodiscard]] inline base::flat_set<FullMsgId> &ViewOnceIds() {
	static auto ids = base::flat_set<FullMsgId>();
	return ids;
}
inline void RememberViewOnce(FullMsgId id) {
	ViewOnceIds().emplace(id);
}
[[nodiscard]] inline bool IsViewOnce(FullMsgId id) {
	return ViewOnceIds().contains(id);
}


inline const char kNoReadReceipts[] = "ghost-no-read-receipts";
inline const char kHideOnline[] = "ghost-hide-online";
inline const char kStealthTyping[] = "ghost-stealth-typing";
inline const char kAntiDelete[] = "ghost-anti-delete";
inline const char kDownloadRestricted[] = "ghost-download-restricted";
inline const char kSaveViewOnce[] = "ghost-save-view-once";
inline const char kAutoSaveOneTime[] = "ghost-auto-save-one-time";
inline const char kShowEditOriginal[] = "ghost-show-edit-original";
inline const char kVideoPip[] = "ghost-video-pip";

inline base::options::toggle NoReadReceipts({
	.id = kNoReadReceipts,
	.name = "Ghost: No read receipts",
	.description = "Read messages without sending the blue 'read' ticks.",
	.defaultValue = true,
});

inline base::options::toggle HideOnline({
	.id = kHideOnline,
	.name = "Ghost: Hide online status",
	.description = "Always appear offline, even while using the app.",
	.defaultValue = true,
});

inline base::options::toggle StealthTyping({
	.id = kStealthTyping,
	.name = "Ghost: Stealth typing",
	.description = "Never broadcast typing / recording / uploading indicators.",
	.defaultValue = true,
});

inline base::options::toggle AntiDelete({
	.id = kAntiDelete,
	.name = "Ghost: Anti-delete",
	.description = "Keep messages that others delete (your own deletes still work).",
	.defaultValue = true,
});

inline base::options::toggle DownloadRestricted({
	.id = kDownloadRestricted,
	.name = "Ghost: Download restricted content",
	.description = "Allow saving/downloading media from content-protected chats.",
	.defaultValue = true,
});

inline base::options::toggle SaveViewOnce({
	.id = kSaveViewOnce,
	.name = "Ghost: Save one-time media (experimental, unstable)",
	.description = "Render view-once/self-destruct media as normal. NOTE: "
		"Telegram uses single-use file references for these, which can cause "
		"'file reference expired' and repaint loops. Off by default.",
	.defaultValue = false,
});

inline base::options::toggle AutoSaveOneTime({
	.id = kAutoSaveOneTime,
	.name = "Ghost: Auto-save one-time media",
	.description = "When a view-once photo/video/voice/round note arrives, "
		"immediately download it to a \"TelegramGhost\" folder in Downloads "
		"(while its file reference is still valid).",
	.defaultValue = true,
});

inline base::options::toggle ShowEditOriginal({
	.id = kShowEditOriginal,
	.name = "Ghost: Show edited originals",
	.description = "When a message is edited, keep the original text visible.",
	.defaultValue = true,
});

inline base::options::toggle VideoPip({
	.id = kVideoPip,
	.name = "Ghost: Keep video playing (Picture-in-Picture)",
	.description = "When you close the video viewer or open a chat while a "
		"video is playing, keep it in a mini player instead of stopping it.",
	.defaultValue = false,
});

} // namespace Ghost
