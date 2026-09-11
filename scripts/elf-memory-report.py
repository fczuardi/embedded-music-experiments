#!/usr/bin/env python3
"""Write deterministic ESP32 memory reports from a linked firmware ELF."""

import argparse
import json
from pathlib import Path

from elftools.elf.elffile import ELFFile


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("elf", type=Path)
    parser.add_argument("--markdown", type=Path, required=True)
    parser.add_argument("--json", dest="json_path", type=Path, required=True)
    parser.add_argument("--top", type=int, default=40)
    args = parser.parse_args()

    with args.elf.open("rb") as stream:
        elf = ELFFile(stream)
        sections = []
        iram_section_indexes = set()

        for index, section in enumerate(elf.iter_sections()):
            size = section["sh_size"]
            if not size or not section["sh_flags"] & 0x2:  # SHF_ALLOC
                continue
            entry = {
                "name": section.name,
                "address": section["sh_addr"],
                "size": size,
            }
            sections.append(entry)
            if section.name.startswith(".iram"):
                iram_section_indexes.add(index)

        symbols = []
        symbol_table = elf.get_section_by_name(".symtab")
        if symbol_table is not None:
            for symbol in symbol_table.iter_symbols():
                if symbol["st_shndx"] not in iram_section_indexes:
                    continue
                size = symbol["st_size"]
                if not size:
                    continue
                symbols.append(
                    {
                        "name": symbol.name,
                        "address": symbol["st_value"],
                        "size": size,
                    }
                )

    sections.sort(key=lambda item: item["address"])
    symbols.sort(key=lambda item: (-item["size"], item["name"]))
    iram_sections = [item for item in sections if item["name"].startswith(".iram")]
    iram_used = sum(item["size"] for item in iram_sections)
    report = {
        "elf": args.elf.name,
        "iram_used_bytes": iram_used,
        "iram_sections": iram_sections,
        "allocated_sections": sections,
        "largest_iram_symbols": symbols[: args.top],
    }

    args.json_path.write_text(json.dumps(report, indent=2) + "\n")

    lines = [
        "## ESP32 linked-memory report",
        "",
        f"IRAM sections in ELF: **{iram_used:,} bytes**",
        "",
        "### IRAM sections",
        "",
        "| Section | Address | Bytes |",
        "|---|---:|---:|",
    ]
    lines.extend(
        f"| `{item['name']}` | `0x{item['address']:08x}` | {item['size']:,} |"
        for item in iram_sections
    )
    lines.extend(
        [
            "",
            f"### Largest {min(args.top, len(symbols))} IRAM symbols",
            "",
            "| Symbol | Address | Bytes |",
            "|---|---:|---:|",
        ]
    )
    lines.extend(
        f"| `{item['name'].replace('|', '\\|')}` | `0x{item['address']:08x}` | {item['size']:,} |"
        for item in symbols[: args.top]
    )
    args.markdown.write_text("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
