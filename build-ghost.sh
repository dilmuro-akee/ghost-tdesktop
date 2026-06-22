#!/bin/bash
# Build the ghost-patched Telegram Desktop using the official prebuilt
# container image (skips the multi-hour library build).
#
# RAM-friendly: limits compile parallelism so the 7.4GB machine survives via
# swap instead of OOM-killing. Bump JOBS if you have more free RAM.
set -e

cd "$(dirname "$0")"
API_ID=11191506
API_HASH=b84a2548b570220a5d97f54332f2d4a9
IMAGE=ghcr.io/telegramdesktop/tdesktop/centos_env:latest
JOBS="${JOBS:-3}"

echo "==> Pulling prebuilt build environment (large, one-time)…"
docker pull "$IMAGE"

echo "==> Building Telegram Desktop (ghost build) with $JOBS parallel jobs…"
docker run --rm -i \
  -u "$(id -u)" \
  -v "$PWD:/usr/src/tdesktop" \
  -e CMAKE_BUILD_PARALLEL_LEVEL="$JOBS" \
  "$IMAGE" \
  /usr/src/tdesktop/Telegram/build/docker/centos_env/build.sh \
  -D TDESKTOP_API_ID="$API_ID" \
  -D TDESKTOP_API_HASH="$API_HASH"

echo ""
echo "==> Done. Binary should be at: $PWD/out/Release/Telegram"
ls -la "$PWD/out/Release/Telegram" 2>/dev/null || echo "(check the out/ directory)"
