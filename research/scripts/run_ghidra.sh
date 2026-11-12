#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
: "${GHIDRA_INSTALL_DIR:?Set GHIDRA_INSTALL_DIR to Ghidra 12.1.4}"
mkdir -p work/ghidra-project work/ghidra-home work/config work/cache work/evidence
python3 scripts/inventory.py firmware/yunmi.waterpuri.lx7-1.3.9.bin > work/interfaces.json
python3 scripts/prepare_image.py firmware/yunmi.waterpuri.lx7-1.3.9.bin work/extracted > work/evidence/image-map.json
export XDG_CONFIG_HOME="$PWD/work/config"
export XDG_CACHE_HOME="$PWD/work/cache"
export JAVA_TOOL_OPTIONS="${JAVA_TOOL_OPTIONS:+$JAVA_TOOL_OPTIONS }-Duser.home=$PWD/work/ghidra-home"
if [[ -e work/ghidra-project/lx7.gpr ]]; then
    action=(-process lx7-analysis.elf -noanalysis)
else
    action=(-import work/extracted/lx7-analysis.elf -processor Xtensa:LE:32:default -analysisTimeoutPerFile 240)
fi
"$GHIDRA_INSTALL_DIR/support/analyzeHeadless" work/ghidra-project lx7 \
    "${action[@]}" -scriptPath scripts \
    -postScript ExportEvidence.java work/evidence/ghidra \
    > work/evidence/ghidra-run.log 2>&1
